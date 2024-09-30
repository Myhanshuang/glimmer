#include "..\inc\head.h"
void init(longint *a) // reset to 0
{
    memset(a, 0, sizeof a);
}
void sub(longint *a, longint *b, int pos, int len) // get a part of b
{
    init(a);
    a->lenth = len;
    a->tag = 0;
    for (int i = pos; i < pos + len; i++)
    {
        a->num[i] = b->num[i];
    }
}
void cpy(longint *a, longint *b) // a = b;
{
    init(a);
    a->tag = b->tag;
    a->lenth = b->lenth;
    for (int i = 0; i < b->lenth; i++)
    {
        a->num[i] = b->num[i];
    }
}

void check_flag(longint *a) // as name introduce
{
    if (a->num[0] == '-')
    {
        a->tag = -1;
        for (int i = 0; i < a->lenth - 1; i++)
            a->num[i] = a->num[i + 1];
        a->lenth--;
    }
}
void reverse(longint *a) // as the name introduce
{
    for (int i = 0; i < a->lenth / 2; i++)
    {
        char temp = a->num[i];
        a->num[i] = a->num[a->lenth - i - 1];
        a->num[a->lenth - i - 1] = temp;
    }
}

int findmax(longint *a, longint *b) // swap to let the bigger at the front without sign while if no swap return 1
{
    if (a->lenth > b->lenth)
    {
        return 1;
    }
    else if (a->lenth < b->lenth)
    {
        longint *c;
        c = (longint *)malloc(sizeof(longint));
        *c = *a;
        *a = *b;
        *b = *c;
        return 0;
    }
    for (int i = 0; i < a->lenth; i++)
    {
        if (a->num[i] > b->num[i])
        {
            return 1;
        }
        else if (a->num[i] < b->num[i])
        {
            longint *c;
            c = (longint *)malloc(sizeof(longint));
            *c = *a;
            *a = *b;
            *b = *c;
            return 0;
        }
    }
    return 1;
}

int max(int a, int b) { return a > b ? a : b; }
int isd(char x) // isdigit
{
    if (x >= '0' && x <= '9')
        return 1;
    return 0;
}