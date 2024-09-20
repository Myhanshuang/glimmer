#include<stdio.h>
int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}
int main(){
    int m, n;
    scanf("%d %d", & m, & n);
    printf("%d", gcd(m, n));
}
