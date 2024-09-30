#include"head.h"
typedef struct node
{
    char IntNum[32];
    char IntOverflow;
    char PointNum[32];
    char IntLenth;
    char PointLenth;
    char sign;
    char jz;//进制
}PointFixedNum;
PointFixedNum num[100];
int cnt = 0, opcnt = 0;
char opt[100];