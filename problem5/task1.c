#include "inc/head.h"
#include "rsc/io.c"
#include "rsc/basic.c"
#include "rsc/cal.c"
int main()
{
    freopen("test/in/test.in", "r", stdin);
    freopen("test/out/task1.out", "w", stdout);
    // 进制转换功能已集成至 transform 函数，此处仅作展示，将所有输入转换为二进制
    if (read())
    {
        printf("Do not act as ccf, give me the right input!!!!");
        return 0;
    }
    for (int i = 0; i < cnt; i++)
    {
        if (num[i].jz == 'D')
            transform(&num[i], 10, 2);
        print(num[i]);
    }
}