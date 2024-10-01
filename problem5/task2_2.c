#include "inc/head.h"
#include "rsc/cal.c"
#include "rsc/basic.c"
#include "rsc/io.c"

int main()
{
    //example 1 & 2 & 3

    // freopen("test/in/test2_2_1.in", "r", stdin);
    // freopen("test/out/task2_2_1.out", "w", stdout);
    // if(read())return 0;
    // init(& ans);
    // if(opt[0] == '+') add(num[0], num[1], &ans);
    // else if(opt[0] == '-') solve_less(num[0], num[1], & ans);
    // else if(opt[0] == '*') multiply(num[0], num[1], & ans);
    // print(ans);

    freopen("test/in/test2_2_2.in", "r", stdin);
    freopen("test/out/task2_2_2.out", "w", stdout);
    if (read())
        return 0;
    init(&ans);
    if (opt[0] == '+')
        add(num[0], num[1], &ans);
    else if (opt[0] == '-')
        solve_less(num[0], num[1], &ans);
    else if (opt[0] == '*')
        multiply(num[0], num[1], &ans);
    print(ans);

    // freopen("test/in/test2_2_3.in", "r", stdin);
    // freopen("test/out/task2_2_3.out", "w", stdout);
    // if(read())return 0;
    // init(& ans);
    // if(opt[0] == '+') add(num[0], num[1], &ans);
    // else if(opt[0] == '-') solve_less(num[0], num[1], & ans);
    // else if(opt[0] == '*') multiply(num[0], num[1], & ans);
    // print(ans);
}