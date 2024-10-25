#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ALIGNMENT 8                                                 // 双字对齐
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1)) // 对齐到ALIGNMENT的倍数

#define WSIZE 4                      // 头部或尾部的字节数
#define DSIZE 8                      // 双字大小
#define CHUNKSIZE (1 << 12)          // 扩展堆时的默认大小
#define MINBLOCK (DSIZE + 2 * WSIZE) // 最小块大小

#define MAX(x, y) ((x) > (y) ? (x) : (y)) // 返回最大值

#define PACK_ALLOC(val, alloc) ((val) | (alloc)) // 将 size 和 allocated bit 合并为一个字

#define GET(p) (*(unsigned int *)(p))              // 读地址p处的一个字
#define PUT(p, val) (*(unsigned int *)(p) = (val)) // 向地址p处写一个字

#define GET_SIZE(p) (GET(p) & ~0x07) // 获取块的大小
#define GET_ALLOC(p) (GET(p) & 0x1)  // 获取分配标志

#define HDRP(bp) ((char *)(bp) - WSIZE)                      // 获取头部指针(bp是一个块的有效荷载的起始地址)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // 获取尾部指针

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE((char *)(bp) - WSIZE)) // 获取下一个块的指针
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE((char *)(bp) - DSIZE)) // 获取前一个块的指针

/* 堆管理接口 */
static void *heap_listp; // 堆的开始指针

#define VERBOSE 0 // 默认不输出调试信息

#ifdef DEBUG
#define VERBOSE 1 // 在调试模式下启用调试信息输出

#endif

static void *extend_heap(size_t size);
static void *coalesce(void *bp);
/**
 * @brief 初始化内存分配器
 *
 * @return 成功时返回 0，失败时返回 -1
 */
int mm_init(void)
{
    // 初始化堆
    if ((heap_listp = sbrk(4 * WSIZE)) == (void *)-1)
        return -1;

    // 初始化空闲链表
    PUT(heap_listp, 0);
    PUT(heap_listp + 1 * WSIZE, PACK_ALLOC(8, 1));
    PUT(heap_listp + 2 * WSIZE, PACK_ALLOC(8, 1));
    PUT(heap_listp, PACK_ALLOC(0, 1));
    heap_listp += (2 * WSIZE);
    // printf("faslidfalsndfl\n");
    // 扩展堆
    if (extend_heap(CHUNKSIZE) == NULL)
        return -1;

    return 0;
}

/**
 * @brief 打印当前堆块的状态信息。
 *
 * 根据传入的 verbose 参数决定是否打印堆块信息。此函数用于调试，
 * 以检查堆内存布局、块大小及其分配状态。
 *
 * @param verbose  控制是否打印输出。当 verbose 为 1 时打印信息，为 0 时不打印。
 * @param func     表示调用此函数的上下文或函数名称，用于输出中标识当前的操作阶段。
 */
static void print_heap_blocks(int verbose, const char *func)
{
    if (!verbose)
        return; // 如果不需要输出调试信息，则直接返回

    // printf("I'm here!\n");
    // fflush(stdout);

    char *curbp = (char *)heap_listp;

    printf("\n=========================== %s ===========================\n", func);
    fflush(stdout);

    while (GET_SIZE(HDRP(curbp)) > 0)
    {
        printf("Address: %p\n", curbp);
        fflush(stdout);
        printf("Size: %d\n", GET_SIZE(HDRP(curbp)));
        fflush(stdout);
        printf("Allocated: %d\n", GET_ALLOC(HDRP(curbp)));
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        curbp = NEXT_BLKP(curbp);
    }

    printf("Address: %p\n", curbp);
    fflush(stdout); // Should point to the end of the heap
    printf("Size: 0\n");
    fflush(stdout);
    printf("Allocated: 1\n");
    fflush(stdout);
    printf("=========================== %s ===========================\n", func);
    fflush(stdout);
}

/**
 * @brief 扩展堆的大小以适应请求的内存。
 *
 * 这个函数通过调用 sbrk 来扩展堆的大小。扩展的大小会被调整为CHUNKSIZE的整数倍，以便更好地管理堆内存。
 *
 * @param size 需要扩展的内存大小（以字节为单位）。
 *
 * @note 初始调用mm_init时扩展一个CHUNKSIZE
 * @return 扩展后的内存块的指针，如果扩展失败则返回 NULL。
 */
static void *extend_heap(size_t size)
{
    // 扩展堆的空间
    // 注意字节对齐（要不然宏定义拿来干什么的()
    size_t realsize = ALIGN(size);
    void *temp;
    if ((temp = sbrk(realsize)) == (void *)-1)
    {
        return NULL;
    }
    // printf("sadfilajs\n");
    // succeed
    // 将分配出来的空间接到我们的链表上面去
    // 注意：要符合那张图块的实际情况，有头有尾有效载荷一个不少
    // 尝试合并
    // 同时移动指针，并返回
    PUT(HDRP(temp), PACK_ALLOC(realsize, 0));
    PUT(FTRP(temp), PACK_ALLOC(realsize, 0));
    // printf("daijlsdf");
    return coalesce(temp);
}

/**
 * @brief 在堆中查找合适的空闲块。
 *
 * 这个函数遍历堆中的所有块，寻找一个大小足够且未分配的空闲块。
 *
 * @param size 需要分配的内存块的大小（以字节为单位）。
 *
 * @return 找到的合适的空闲块的指针，如果没有找到则返回 `NULL`。
 */
static void *find_fit(size_t size)
{
    char *start = heap_listp;
    size_t realsize = ALIGN(size);
    while (GET_SIZE(start)) // 当前位置对应的块的大小为零，说明已经超出了分配的范围
    {
        if (GET_SIZE(start) >= realsize)
            return start;
        start = NEXT_BLKP(start);
    }
    return NULL;
}

/**
 * @brief 将内存块分配给用户。
 *
 * 这个函数会根据请求的大小 asize(对齐后的size) 将一个内存块分配给用户。如果分配的块剩余的空间足够大，则将剩余的空间保留为一个新的空闲块。否则，将整个块都分配出去。
 *
 * @param bp 指向要分配的内存块的指针。
 * @param asize 需要分配的内存块的大小（以字节为单位）。
 */
static void place(char *bp, size_t asize)
{
    size_t realsize = ALIGN(asize);
    char *nextblock = bp + realsize + DSIZE + WSIZE;     // 当前指向有效载荷的指针移动有效载荷大小 + 块末尾的一个字 + 块头的一个字 = 下一个块的有效载荷的位置
    if (GET_SIZE(bp) > realsize + DSIZE + WSIZE + WSIZE) // 空间充裕(足够头尾之外还有有效载荷)，分配后抓一个空的新块出来
    {

        PUT(HDRP(bp), PACK_ALLOC(realsize, 1));
        PUT(bp + realsize - DSIZE, PACK_ALLOC(realsize, 1)); // 仿造 FTRP 进行精确的内存操作
        PUT(HDRP(nextblock), PACK_ALLOC(GET_SIZE(bp) - realsize, 0));
        PUT(FTRP(nextblock), PACK_ALLOC(GET_SIZE(bp) - realsize, 0));
        coalesce(nextblock);
    }
    else // 直接塞！
    {
        PUT(HDRP(bp), PACK_ALLOC(GET_SIZE(bp), 1));
        PUT(FTRP(bp), PACK_ALLOC(GET_SIZE(bp), 1));
    }
}

/**
 * @brief 分配一个指定大小的内存块。
 *
 * 这个函数会根据请求的内存大小size来分配内存。如果请求的大小为零，则返回 NULL。首先，函数尝试从空闲块列表中找到一个合适的块，如果找到，则进行分配。如果没有找到合适的块，则会扩展堆的大小，并再次尝试分配内存。
 *
 * @param size 需要分配的内存大小（以字节为单位）。
 *
 * @return 指向分配的内存块的指针，如果分配失败则返回 `NULL`。
 */
void *mm_malloc(size_t size)
{
    if (size == 0)
        return NULL;
    char *op = find_fit(size);
    if (op == NULL) // 堆的空间不够
    {
        op = extend_heap(size);
    }
    place(op, size);
    char a[] = "mm_malloc";
    print_heap_blocks(VERBOSE, a);
    return op;
}

/**
 * @brief 合并相邻的空闲块。
 *
 * 这个函数检查指定块 bp 的前后相邻块的分配状态。如果相邻的块为空闲块，则将这些块合并成一个更大的空闲块，并更新其头部和尾部。函数会返回合并后的空闲块的指针。
 *
 * @param bp 指向要进行合并操作的内存块的指针。
 *
 * @return 合并后的空闲块的指针。
 */
static void *coalesce(void *bp)
{
    char *tmp = bp;
    // go after
    // tmp -> now
    // head -> next_blkp pointer
    while (1)
    {
        // printf("asdf\n");
        char *head = NEXT_BLKP(tmp);
        if (head > heap_listp)
            break;
        // 后面的指针存在
        if (GET_ALLOC(HDRP(head)))
            break; // 后面的块非空
        else       // see picture
        {
            PUT(HDRP(head), PACK_ALLOC((tmp + GET_SIZE(tmp) - head), 0));
            PUT(FTRP(head), PACK_ALLOC((tmp + GET_SIZE(tmp) - head), 0));
            if (GET_SIZE(head) == 0)
                break; // 到结束就返回
            tmp = head;
        }
    }
    // go before
    // tmp -> now
    // head -> prev_blkp pointer
    tmp = bp;
    while (1)
    {

        // printf("asdf\n");
        char *head = PREV_BLKP(tmp);
        if (GET_SIZE(head) == 0)
            break; // 第一块就返回
        // 前面的指针存在
        if (GET_ALLOC(HDRP(head)))
            break; // 前面的块非空
        else       // see picture
        {
            PUT(HDRP(head), PACK_ALLOC((tmp + GET_SIZE(tmp) - head), 0));
            PUT(FTRP(head), PACK_ALLOC((tmp + GET_SIZE(tmp) - head), 0));
            tmp = head;
        }
    }
    return tmp;
}

/**
 * @brief 释放一个已分配的内存块。
 *
 * 这个函数将指定的内存块 ptr 标记为未分配，并尝试将其与相邻的空闲块合并。
 *
 * @param ptr 指向要释放的内存块的指针。
 */
void mm_free(void *ptr)
{
    PUT(HDRP(ptr), PACK_ALLOC(GET_SIZE(ptr), 0));
    PUT(FTRP(ptr), PACK_ALLOC(GET_SIZE(ptr), 0));
    coalesce(ptr);
    char a[] = "mm_free";
    print_heap_blocks(VERBOSE, a);
}

// 测试用例
int main()
{

    if (mm_init() == -1)
    {
        printf("Memory manager initialization failed.\n");
        return -1;
    }

    void *p1 = mm_malloc(8000);
    void *p2 = mm_malloc(200);
    void *p3 = mm_malloc(50);

    mm_free(p2);

    void *p4 = mm_malloc(150);

    mm_free(p1);
    mm_free(p3);
    mm_free(p4);

    return 0;
}