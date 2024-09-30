#include <stdio.h>
#include <string.h>
#include "inc\head.h"
#include "rsc\io.c"
#include "rsc\basis.c"
int main()
{
    freopen("test//in//fetch.in", "r", stdin);
    freopen("test//out//fetch.out", "w", stdout);
    read(&a, &b);
    print(&a);
    puts("");
    print(&b);
    puts("");
    printf("%c", op);
}