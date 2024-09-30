#ifndef head
#define head
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node
{
    char num[1000];
    int tag; // sign
    int lenth;
} longint;
extern char op;
extern char origin[1000];
extern longint a, b, c;
int max(int a, int b);
int isd(char x); // isdigit
void read(longint *a, longint *b);
void print(longint *a);
void pls(longint *a, longint *b, longint *c); // +
int findmax(longint *a, longint *b);          // swap to let the bigger at the front without sign while if no swap return 1
void less(longint *a, longint *b, longint *c);
void add(longint *a, longint *b, longint *c);
void check_flag(longint *a);
void reverse(longint *a);
void multiply(longint *a, longint *b, longint *c);
void init(longint *a);                              // a = 0
void sub(longint *a, longint *b, int pos, int len); // get a part of b
void cpy(longint *a, longint *b);                   // a = b;
void divv(longint *a, longint *b, longint *c);      // /
void solve_add(longint *a, longint *b, longint *c);
void solve_less(longint *a, longint *b, longint *c); // less could turn to add
void solve_multiply(longint *a, longint *b, longint *c);
void solve_div(longint *a, longint *b, longint *c);
#endif