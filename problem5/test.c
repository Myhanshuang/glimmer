#include "head.h"


void read()
{
    freopen("test.in", "r", stdin);
    while (1)
    {
        char op;
        char origin[100];
        if (fgets(origin, 90, stdin) != NULL) // each line
        {
            int pos = 0;
            int lenth = strlen(origin);
            while (pos < lenth && !isop(origin[pos]) && !isdig(origin[pos]))
                pos++;
            // move to the start of op or num
            if (isop(origin[pos]))
                opt[opcnt] = origin[pos], pos++;      // storage the op
            while (pos < lenth && isdig(origin[pos])) // get the num of int
            {
                num[cnt].IntNum[num[cnt].IntLenth] = origin[pos] - '0';
                num[cnt].IntLenth++;
            }
            if (origin[pos] == '.')
            {
                pos++;
                while (pos < lenth && isdig(origin[pos])) // get the num after point
                {
                    num[cnt].PointNum[num[cnt].PointLenth] = origin[pos] - '0';
                    num[cnt].PointLenth++;
                }
            }
            num[cnt].jz = origin[pos];
        }
        else
            break;
    }
}

void print(PointFixedNum *a)
{
    freopen("test.out", "w", stdout);
    if (a->IntLenth == 0 || a->PointLenth == 0)
    {
        printf("0");
        return;
    }
    if (a->sign == -1)
    {
        printf("-");
    }
    for (int i = 0; i < a->IntLenth; i++)
    {
        printf("%d", a->IntNum[i]);
    }
    if (a->IntLenth == 0)
        printf("0");
    if (a->PointLenth != 0)
        printf(".");
    for (int i = 0; i < a->PointLenth; i++)
        printf("%d", a->PointNum[i]);
    printf("%c", a->jz);
}
int main()
{
    read();
    print(&num[1]);
}