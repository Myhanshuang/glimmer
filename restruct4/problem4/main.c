#include "inc/head.h"
#include "rsc/solve.c"
#include "rsc/io.c"
#include "rsc/basis.c"
int main()
{
    freopen("test//in//test.in", "r", stdin);
    freopen("test//out//test.out", "w", stdout);
    read(&a, &b);
    if (op == '+')
    {
        solve_add(&a, &b, &c);
    }
    else if (op == '-')
    {
        solve_less(&a, &b, &c);
    }
    else if (op == '*')
    {
        solve_multiply(&a, &b, &c);
    }
    else
    {
        solve_div(&a, &b, &c);
    }
    print(&c);
}