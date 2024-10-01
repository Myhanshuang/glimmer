#include "inc/head.h"
#include "rsc/io.c"
#include "rsc/basic.c"
#include "rsc/cal.c"
int main()
{
    freopen("test/in/test.in", "r", stdin);
    freopen("test/out/task2_1.out", "w", stdout);
    // 函数名称 read == init
    // init 我习惯性拿去做初始化了，而不是读入
    // 果咩
    if (read()) // init()
    {
        printf("Do not act as ccf, give me the right input!!!!");
        return 0;
    }
    for (int i = 0; i < cnt; i++)
    {
        if (num[i].jz == 'B')
            transform(&num[i], 2, 10);
        print(num[i]);
    }
}