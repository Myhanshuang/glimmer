#include "inc/head.h"
#include "rsc/io.c"
#include "rsc/basic.c"
#include "rsc/cal.c"
int main()
{
    freopen("test/in/test.in", "r", stdin);
    freopen("test/out/preclass.out", "w", stdout);
    if (read())
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