#include <stdio.h>
#include <string.h>

char op;

typedef struct node
{
    char num[1000];
    int tag; // sign
    int lenth;
} longint;
longint a, b;
int isdigit(char x)
{
    if (x >= '0' && x <= '9')
        return 1;
    return 0;
}
char origin[1000];
void read()
{
    gets(origin); // read a line
    int pos = 0, max_lenth = strlen(origin);
    while (origin[pos] != '-' && origin[pos] != '+' && !isdigit(origin[pos]))// move to sign
        pos++; 
    if (!isdigit(origin[pos]))
    {
        a.tag = (origin[pos] == '-') ? -1 : 0;
        while (!isdigit(origin[pos]))
            pos++;
    } 
    while (isdigit(origin[pos]) && pos < max_lenth)// get the first number
    {
        a.num[a.lenth] = origin[pos];
        a.lenth++;
        pos++;
    } 
    while (origin[pos] != '+' && origin[pos] != '-' && origin[pos] != '*' && origin[pos] != '/')// move to op
        pos++; 
    op = origin[pos];
    while (origin[pos] != '-' && origin[pos] != '+' && !isdigit(origin[pos]))// move to second sign
        pos++; 
    if (!isdigit(origin[pos]))// get the second sign
    {
        b.tag = (origin[pos] == '-') ? -1 : 0;
        while (!isdigit(origin[pos]))
            pos++;
    } 
    while (isdigit(origin[pos]) && pos < max_lenth)// get the second number
    {
        b.num[b.lenth] = origin[pos];
        b.lenth++;
        pos++;
    } 
}

void print(longint *a)
{
    if (a->tag != 0)
    {
        if (a->num[0] != 0 || a->lenth != 1)
            printf("-");
    }
    for (int i = 0; i < a->lenth; i++)
        printf("%c", a->num[i]);
}

int main()
{
    freopen("fetch.in", "r", stdin);
    freopen("fetch.out", "w", stdout);

    read();

    print(&a);
    puts("");
    print(&b);
    puts("");
    printf("%c", op);
}