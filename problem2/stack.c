#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, m ;
int a[100], top;
char b[100];
char stk[100];
int main(){
    freopen("Josephus.out", "r", stdin);
    freopen("answer.out", "w", stdout);
    while(~scanf("%d", & a[ ++ n]));
    n --;
    freopen("CS-EASY-02-2.txt", "r", stdin);
    while(~scanf("%c", & b[ ++ m]));
    m --;
    int pos = 1;
    for(int i = 1; i <= n; i ++){
        if(i & 1){
            for(int j = 1; j <= a[i]; j ++){ 
                if(pos > m)continue;
                stk[++ top] = b[pos], pos ++;
            }
        }
        else {
            for(int j = 1; j <= a[i]; j ++)
                printf("%c", stk[top]), 
                top --;
        }
    }
}