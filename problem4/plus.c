#include <stdio.h>
#include <string.h>
int max(int a, int b) { return a > b ? a : b; }
int n, m, p;
char a[2000], b[2000], c[2000];

int main()
{
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    scanf("%s", a);
    scanf("%s", b);
    n = strlen(a);
    m = strlen(b);
    for (int i = 0; i < n / 2; i++)// reverse a
    {
        char temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    } 
    for (int i = 0; i < m / 2; i++)// reverse b
    {
        char temp = b[i];
        b[i] = b[m - i - 1];
        b[m - i - 1] = temp;
    } 
    p = max(n, m);
    int x = 0;
    for (int i = 0; i < p; i++)// plus
    {
        c[i] = (x + a[i] - '0' + b[i] - '0') % 10 + '0';
        x = (x + a[i] - '0' + b[i] - '0') / 10;
    } 
    for (int i = 0; i < p / 2; i++)// reverse c
    {
        char temp = c[i];
        c[i] = c[p - i - 1];
        c[p - i - 1] = temp;
    } 
    for (int i = 0; i < p; i++)
        printf("%c", c[i]);
}