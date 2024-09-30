#include "../inc/head.h"
#include"define.c"
void read(longint *a, longint *b) // read the op & number
{
    gets(origin); // read a line
    int pos = 0, max_lenth = strlen(origin);
    while (origin[pos] != '-' && origin[pos] != '+' && !isd(origin[pos]))
        pos++;
    if (!isd(origin[pos]))
    {
        a->tag = (origin[pos] == '-') ? -1 : 0;
        while (!isd(origin[pos]))
            pos++;
    }
    while (isd(origin[pos]) && pos < max_lenth) // get the first number
    {
        a->num[a->lenth] = origin[pos];
        a->lenth++;
        pos++;
    }
    while (origin[pos] != '+' && origin[pos] != '-' && origin[pos] != '*' && origin[pos] != '/') // move to op
        pos++;
    op = origin[pos];
    pos++;
    while (origin[pos] != '-' && origin[pos] != '+' && !isd(origin[pos])) // move to second sign
        pos++;
    if (!isd(origin[pos])) // get the second sign
    {
        b->tag = (origin[pos] == '-') ? -1 : 0;
        while (!isd(origin[pos]))
            pos++;
    }
    while (isd(origin[pos]) && pos < max_lenth) // get the second number
    {
        b->num[b->lenth] = origin[pos];
        b->lenth++;
        pos++;
    }
    for (int i = 0; i < a->lenth; i++) // turn to %d
        a->num[i] -= '0';
    for (int i = 0; i < b->lenth; i++)
        b->num[i] -= '0';
}
void print(longint *a) // print out the big number
{
    if (a->tag != 0)
    {
        if (a->num[0] != 0 || a->lenth != 1)
            printf("-");
    }
    for (int i = 0; i < a->lenth; i++)
        printf("%d", a->num[i]);
}