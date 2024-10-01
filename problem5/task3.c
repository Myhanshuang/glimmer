#include "inc/head.h"
#include "rsc/io.c"
#include "rsc/basic.c"
#include "rsc/cal.c"
int main()
{
    freopen("test/in/test.in", "r", stdin);
    freopen("test/out/task3.out", "w", stdout);

    if (read()) // init()
    {
        printf("Do not act as ccf, give me the right input!!!!");
        return 0;
    }
    // 进制转换
    for (int i = 0; i < cnt; i++)
        if (num[i].jz == 'B')
            transform(&num[i], 2, 10);
    // 栈+队列模拟计算
    int stk[100], idx = 0, idx2 = 0;
    char stk2[100];
    memset(stk2, 0, sizeof stk2);
    memset(stk, 0, sizeof stk);
    // 用栈处理乘法优先级
    for (int i = 0; i < cnt; i++)
    {
        if (i == 0)
            stk[++idx] = i;

        else if (opt[i - 1] != '*')
            stk[++idx] = i, stk2[++idx2] = opt[i - 1];
        else
        {
            int t = stk[idx];
            PointFixedNum temp;
            init(&temp);
            multiply(num[t], num[i], &temp);
            num[t] = temp;
        }
    }
    int t1, t2, t;
    // 用队列思想顺序计算
    for (int i = 1; i <= idx; i++)
    {
        if (i == 1)
            t1 = stk[1];
        else
        {
            char op = stk2[i - 1];
            t2 = stk[i];
            // printf("%d %d \n", t1, t2);
            // print(num[t1]);
            // print(num[t2]);
            PointFixedNum temp;
            init(&temp);
            calculate(op, t1, t2, &temp);
            // print(temp);
            // puts("");
            t = t1;
            num[t1] = temp;
        }
    }
    print(num[t]);
}