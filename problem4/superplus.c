#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int max(int a, int b){return a > b ? a : b;}
int n, m , p;
typedef struct node{
    char num[2000];
    int tag;
    int lenth;
}longint;
longint a, b, c;
void pls(longint* a, longint* b, longint* c){// +
    int x = 0;
    c -> lenth = max(a -> lenth, b -> lenth);
    for(int i = a -> lenth ; i < c -> lenth; i ++)
        a -> num[i] = '0';
    for(int i = b -> lenth ; i < c -> lenth; i ++)
        b -> num[i] = '0';
    for(int i = 0; i < max(a -> lenth, b -> lenth); i ++){
        c -> num[i] = (x + a -> num[i] - '0' + b -> num[i] - '0') % 10 + '0';
        x = (x + a -> num[i] - '0' + b -> num[i] - '0') / 10;
    }
    if(x) {
        c -> lenth ++;
        c -> num[c -> lenth - 1] = x + '0';
    }
}
int findmax(longint *a, longint* b){// swap to let the bigger at the front
    if(a -> lenth > b -> lenth)return 1;
    else if(a -> lenth < b -> lenth){
        longint *c = a;
        a = b;
        b = c;
        return 0;
    }
    for(int i = 0 ; i < a -> lenth; i ++){
        if(a -> num[i] > b -> num[i]){
            return 1;
        }
        else if(a -> num[i] < b -> num[i]){
            longint *c ;
            c = (longint*)malloc(sizeof (longint));
            *c = *a;
            *a = *b;
            *b = *c;
            return 0;
        }
    }
    return 1;
}
void less(longint* a, longint* b, longint* c){// - 
    c -> tag = a -> tag;
    c -> lenth = a -> lenth;
    int x = 0;
    for(int i = b -> lenth; i < a -> lenth; i ++)
        b -> num[i] = '0';
    for(int i = 0; i < a -> lenth; i ++){
        if(a -> num[i] + x < b -> num[i]){
            c -> num[i] = a -> num[i] - b -> num[i] + 10 + x + '0';
            x = -1;
        }
        else {
            c -> num[i] = a -> num[i] - b -> num[i] + x + '0';
            x = 0;
        }
    }
    int highest = c -> lenth - 1;
    while(c -> num[highest] == '0' && highest != 0)c -> lenth -- , highest --;
}  
void add(longint* a, longint* b, longint* c){//package + && -
    if(a -> tag == b -> tag){
        c -> tag = a -> tag;
        pls(a, b, c);
    }
    else {
        less(a, b, c);
    }
}
void check_flag(longint *a){//as name introduce
    if(a -> num[0] == '-'){
        a -> tag = -1;
        for(int i = 0; i < a -> lenth - 1; i ++)
            a -> num[i] = a -> num[i + 1];
        a -> lenth --;
    }
}
void reverse(longint * a){// as the name introduce
    for(int i = 0; i < a -> lenth / 2; i ++){
        char temp = a -> num[i];
        a -> num[i] = a -> num[a -> lenth - i - 1];
        a -> num[a -> lenth - i - 1] = temp;
    }
}
int main(){
    freopen("sample1.in", "r", stdin);
    freopen("sample1.out", "w", stdout);
    scanf("%s", a.num); scanf("%s", b.num);
    //init lenth
    a.lenth = strlen(a.num); b.lenth = strlen(b.num);
    //check flag
    check_flag(& a); check_flag(& b);
    //reverse
    findmax(& a, & b);
    reverse(& a); reverse(& b);
    add(& a, & b, & c);
    reverse(& c);
    if(c.tag != 0){
        if(c.lenth != 1 || c.num[0] != '0')
        printf("-");
    }
    for(int i = 0; i < c.lenth; i ++)
        printf("%c", c.num[i]);
}