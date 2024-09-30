#include "inc/head.h"
#include "rsc/io.c"
#include "rsc/basis.c"
#include "rsc/solve.c"
int main()
{
    freopen("test//in//sample1.in", "r", stdin);
    freopen("test//out//sample1.out", "w", stdout);
    scanf("%s", a.num);
    scanf("%s", b.num);
    // init lenth
    a.lenth = strlen(a.num);
    b.lenth = strlen(b.num);
    // check flag
    check_flag(&a);
    check_flag(&b);
    // reverse
    findmax(&a, &b); // make sure the bigger is at front
    reverse(&a);
    reverse(&b);
    addorless(&a, &b, &c);
    reverse(&c);
    if (c.tag != 0)
    {
        if (c.lenth != 1 || c.num[0] != '0')
            printf("-");
    }
    for (int i = 0; i < c.lenth; i++)
        printf("%c", c.num[i]);
}