#include "../inc/head.h"
void pls(longint *a, longint *b, longint *c) // +
{
    int x = 0;
    c->lenth = max(a->lenth, b->lenth);
    for (int i = 0; i < c->lenth; i++)
    {
        c->num[i] = (x + a->num[i] + b->num[i]) % 10;
        x = (x + a->num[i] + b->num[i]) / 10;
    }
    if (x)
    {
        c->lenth++;
        c->num[c->lenth - 1] = x;
    }
}
void less(longint *a, longint *b, longint *c) // -
{
    c->tag = a->tag;
    c->lenth = a->lenth;
    int x = 0;
    for (int i = 0; i < a->lenth; i++)
    {
        if (a->num[i] + x < b->num[i])
        {
            c->num[i] = a->num[i] - b->num[i] + 10 + x;
            x = -1;
        }
        else
        {
            c->num[i] = a->num[i] - b->num[i] + x;
            x = 0;
        }
    }
    int highest = c->lenth - 1;
    while (c->num[highest] == 0 && highest != 0)
        c->lenth--, highest--; // delete the front 0
}
void addorless(longint *a, longint *b, longint *c) // package + && -
{
    if (a->tag == b->tag)
    {
        c->tag = a->tag;
        pls(a, b, c);
    }
    else
    {
        less(a, b, c);
    }
}
void multiply(longint *a, longint *b, longint *c) // *
{
    if (a->tag == b->tag)
        c->tag = 0;
    else
        c->tag = -1;
    c->lenth = a->lenth + b->lenth + 3;
    for (int i = 0; i < a->lenth; i++)
    {
        for (int j = 0; j < b->lenth; j++)
        {
            int t = c->num[i + j] + (a->num[i] * b->num[j]);
            c->num[i + j] = t % 10;
            c->num[i + j + 1] += t / 10;
        }
    }
    int highest = c->lenth - 1;
    while (c->num[highest] == 0 && c->lenth > 0)
        highest--, c->lenth--; // cut off the front 0
}
void divv(longint *a, longint *b, longint *c) // /
{
    if (a->tag == b->tag)
        c->tag = 0;
    else
        c->tag = -1;
    int pos = 0, len = b->lenth;
    longint temp, res;
    init(&temp);
    init(&res);
    sub(&temp, a, pos, len);
    pos = pos + len - 1;
    res.lenth = 0;
    res.tag = 0; // init res empty
    longint x;
    x.lenth = 2;
    x.num[0] = 1;
    x.num[1] = 0;
    x.tag = 0;
    int f = 0;
    while (pos < a->lenth)
    {
        longint tt;
        if (f) // the first time don't need to do
        {
            solve_multiply(& res, & x, & tt);//res * 10;
            res.num[res.lenth - 1] = a->num[pos]; // get the next number
            cpy(&temp, &res);                     // tt -> temp
            init(&res);
        }
        f++;
        int cnt = 0;
        while (findmax(&temp, b)) // less until temp < b
        {
            int t = b->tag;
            b->tag = 0;
            solve_less(&temp, b, &res);
            b->tag = t;
            cpy(&temp, &res);
            cnt++;
        }
        longint mid = temp;
        temp = *b, *b = mid;
        c->num[c->lenth] = cnt; // get the number
        c->lenth++;
        cpy(&res, &temp);
        pos++;
    }
}
void solve_add(longint *a, longint *b, longint *c)
{
    findmax(a, b);
    reverse(a);
    reverse(b);
    addorless(a, b, c);
    reverse(a);
    reverse(b);
    reverse(c);
}
void solve_less(longint *a, longint *b, longint *c) // less could turn to add
{
    if (b->tag == -1)
    {
        b->tag = 0;
        solve_add(a, b, c);
    }
    else
    {
        b->tag = -1;
        solve_add(a, b, c);
    }
}
void solve_multiply(longint *a, longint *b, longint *c) // c must return to 0;
{
    init(c);
    findmax(a, b);
    reverse(a);
    reverse(b);
    multiply(a, b, c);
    reverse(a);
    reverse(b);
    reverse(c);
}
void solve_div(longint *a, longint *b, longint *c)
{
    divv(a, b, c);
}