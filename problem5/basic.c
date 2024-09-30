#include "head.h"

void transform(PointFixedNum *a)
{
    if (a->jz == 2) // 2 -> 10
    {

    }
    else// 10 -> 2
    {
        
    }
}

int isop(char x){
    switch(x){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 1;
        default :
            return 0;
        }
}
int isdigit(char x){
    if(x >= '0' &&  x <= '9')
        return 1;
    return 0;
}