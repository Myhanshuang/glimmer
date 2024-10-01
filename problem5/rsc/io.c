#include "../inc/head.h"
#include "define.c"
/*
void read()
{
    FILE *fp = NULL;
    fp = fopen("/test/test.in", "r");
    while (1)
    {
        char op;
        char origin[100];
        if (fgets(origin, 90, fp) != NULL) // each line
        {
            int pos = 0;
            int lenth = strlen(origin);
            while (pos < lenth && !isop(origin[pos]) && !isdig(origin[pos]))
                pos++;
            // move to the start of op or num
            if (isop(origin[pos]))
                opt[opcnt] = origin[pos], pos++;        // storage the op
            while (pos < lenth && isdig(origin[pos])) // get the num of int
            {
                num[cnt].IntNum[num[cnt].IntLenth] = origin[pos] - '0';
                num[cnt].IntLenth++;
            }
            if (origin[pos] == '.')
            {
                pos++;
                while (pos < lenth && isdig(origin[pos])) // get the num of int
                {
                    num[cnt].PointNum[num[cnt].PointLenth] = origin[pos] - '0';
                    num[cnt].PointLenth++;
                }
            }
            num[cnt].jz = origin[pos];
        }
        else
            break;
    }
    fclose(fp);
}

void print(PointFixedNum *a)
{
    if (a->IntLenth == 0 || a->PointLenth == 0)
    {
        FILE *fp = fopen("/test/test.out", "a");
        fprintf(fp, "0");
        fclose(fp);
        return;
    }
    if (a->sign == -1)
    {
        FILE *fp = fopen("/test/test.out", "a");
        fprintf(fp, "-");
        fclose(fp);
    }
    FILE *fp = fopen("/test/test.out", "a");
    for (int i = 0; i < a->IntLenth; i++)
    {
        fprintf(fp, "%d", a->IntNum[i]);
    }
    if (a->IntLenth == 0)
        fprintf(fp, "0");
    if (a->PointLenth != 0)
        fprintf(fp, ".");
    for (int i = 0; i < a->PointLenth; i++)
        fprintf(fp, "%d", a->PointNum[i]);
    fprintf(fp, "%c", a->jz);
    fclose(fp);
}
*/

int read()
{
    while (1)
    {
        char origin[100];
        memset(origin, 0, sizeof origin);
        if (fgets(origin, 90, stdin) != NULL) // each line
        {
            int pos = 0;
            int lenth = strlen(origin);
            while (pos < lenth && !isop(origin[pos]) && !isdig(origin[pos]))
                pos++;
            // move to the start of op or num
            if (isop(origin[pos]))
                opt[opcnt++] = origin[pos], pos += 2; // storage the op
            // 格式有空格，要跳过！！！
            while (pos < lenth && isdig(origin[pos])) // get the num of int
            {
                num[cnt].IntNum[num[cnt].IntLenth] = origin[pos] - '0';
                num[cnt].IntLenth++;
                if (num[cnt].IntLenth > 32)
                    return 1;
                pos++;
            }
            if (origin[pos] == '.')
            {
                pos++;
                while (pos < lenth && isdig(origin[pos])) // get the num after point
                {
                    num[cnt].PointNum[num[cnt].PointLenth] = origin[pos] - '0';
                    num[cnt].PointLenth++;
                    if (num[cnt].PointLenth > 32)
                        return 1;
                    pos++;
                }
            }
            num[cnt].jz = origin[pos];
            cnt++;
        }
        else
            break;
    }
    return 0;
}

void print(PointFixedNum a)
{
    // 特判啥也没有
    if (a.IntLenth == 0 && a.PointLenth == 0)
    {
        printf("0");
        return;
    }
    // 输出符号
    if (a.sign == -1)
    {
        printf("-");
    }
    // 输出整数部分
    for (int i = 0; i < a.IntLenth; i++)
    {
        printf("%d", a.IntNum[i]);
    }
    // 是否有小数部分
    if (a.IntLenth == 0)
        printf("0");
    if (a.PointLenth != 0)
        printf(".");
    for (int i = 0; i < a.PointLenth; i++)
        printf("%d", a.PointNum[i]);
    // 进制
    printf("%c", a.jz);
    puts("");
}