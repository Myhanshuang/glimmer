#include <stdio.h>

char a[1000];
int lenth;
int main()
{
    freopen("test//in//step1.in", "r", stdin);
    freopen("test//out//step1.out", "w", stdout);
    while (~scanf("%c", &a[++lenth]))
        ;
    lenth--;
    for (int i = 1; i <= lenth; i++)
        printf("%c", a[i]);
}