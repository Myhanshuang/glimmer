#ifndef head
#define head

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct node
{
    char IntNum[40];
    char IntOverflow;
    char PointNum[40];
    char IntLenth;
    char PointLenth;
    char sign;
    char jz; // 进制
} PointFixedNum;
extern PointFixedNum num[100], base, ans;
extern int cnt, opcnt;
extern char opt[100];
int isdig(char x);
void solve_less(PointFixedNum a, PointFixedNum b, PointFixedNum *c);
int findmax(PointFixedNum a, PointFixedNum b);
int isop(char x);
int read();
void print(PointFixedNum a);
void multiply(PointFixedNum a, PointFixedNum b, PointFixedNum *c); // c = a * b;
void add(PointFixedNum a, PointFixedNum b, PointFixedNum *c);      // c = a + b;
void less(PointFixedNum a, PointFixedNum b, PointFixedNum *c);     // c = a - b;
void cpy(PointFixedNum *a, PointFixedNum *b);                      // a = b;
void transform(PointFixedNum *BeiChuShu, int base1, int base2);    // transform beichushu from base1 to base2
void init();
void reverseint(PointFixedNum *a);
void reversedouble(PointFixedNum *b);
void reverse(char *a, int len);
int max(int a, int b);
void swap(char *a, char *b);
void calculate(char op, int t1, int t2, PointFixedNum *temp);
#endif