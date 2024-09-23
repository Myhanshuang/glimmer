#include <stdio.h>
#include <string.h>
#include<stdlib.h>

char op;
char origin[1000];
typedef struct node{
    char num[1000];
    int tag;
    int lenth;
}longint;
int max(int a, int b){return a > b ? a : b;}
longint a, b, c;
int isd(char x){
    if(x >= '0' && x <= '9')return 1;
    return 0;
}
void read(longint *a, longint *b){
    gets(origin);
    int pos = 0, max_lenth = strlen(origin);
    while(origin[pos] != '-' && origin[pos] != '+' && !isd(origin[pos]))pos ++;
    if(!isd(origin[pos])) {
        a -> tag = (origin[pos] == '-') ? -1 : 0; 
        while(!isd(origin[pos])) pos ++;
    }
    while(isd(origin[pos]) && pos < max_lenth){
        a -> num [a -> lenth] = origin[pos];
        a -> lenth ++;
        pos ++;
    }
    while(origin[pos] != '+' && origin[pos] != '-' && origin[pos] != '*' && origin[pos] != '/')pos ++;
    op = origin[pos];
    pos ++;
    while(origin[pos] != '-' && origin[pos] != '+' && !isd(origin[pos]))pos ++;
    if(!isd(origin[pos])) {
        b -> tag = (origin[pos] == '-') ? -1 : 0; 
        while(!isd(origin[pos])) pos ++;
    }
    while(isd(origin[pos]) && pos < max_lenth){
        b -> num [b -> lenth] = origin[pos];
        b -> lenth ++;
        pos ++;
    }
    for(int i = 0; i < a -> lenth; i ++)
        a -> num[i] -= '0';
    for(int i = 0; i < b -> lenth; i ++)
        b -> num[i] -= '0';
}
void print(longint *a){
    if(a -> tag != 0){
        if(a -> num[0] !=0 || a -> lenth != 1)printf("-");
    }
    for(int i = 0; i < a -> lenth; i ++)
        printf("%d", a -> num[i]);
}
void pls(longint* a, longint* b, longint* c){// +
    int x = 0;
    c -> lenth = max(a -> lenth, b -> lenth);
    for(int i = 0; i < c -> lenth; i ++){
        c -> num[i] = (x + a -> num[i] + b -> num[i]) % 10 ;
        x = (x + a -> num[i] + b -> num[i]) / 10;
    }
    if(x) {
        c -> lenth ++;
        c -> num[c -> lenth - 1] = x ;
    }
}
int findmax(longint *a, longint* b){// swap to let the bigger at the front without sign
    if(a -> lenth > b -> lenth){
        return 1;
    }
    else if(a -> lenth < b -> lenth){
        longint *c;
        c = (longint *)malloc(sizeof (longint));
        *c = *a;
        *a = *b;
        *b = *c;
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
    c -> tag = a -> tag ;
    c -> lenth = a -> lenth;
    int x = 0;
    for(int i = 0; i < a -> lenth; i ++){
        if(a -> num[i] + x < b -> num[i]){
            c -> num[i] = a -> num[i] - b -> num[i] + 10 + x;
            x = -1;
        }
        else {
            c -> num[i] = a -> num[i] - b -> num[i] + x ;
            x = 0;
        }
    }
    int highest = c -> lenth - 1;
    while(c -> num[highest] == 0 && highest != 0)c -> lenth -- , highest --;
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
void multiply(longint * a, longint * b, longint * c){
    if(a -> tag == b -> tag) c -> tag = 0;
    else c -> tag = -1 ;
    c -> lenth = a -> lenth + b -> lenth + 10;
    for(int i = 0; i <= a -> lenth; i ++){
        for(int j = 0; j <= b -> lenth; j ++){
            c -> num[i + j] += a -> num[i]  * b -> num[j] ;
        }
    }
    for(int i = 0; i < c -> lenth; i ++){
        if(c -> num[i] >= 10){
            c -> num[i + 1] += c -> num[i] / 10;
            c -> num[i] = c -> num[i] % 10;
        }
    }
    int highest = c -> lenth - 1;
    while(c -> num[highest] == 0 && c -> lenth > 1)highest --, c -> lenth --;
}
void init(longint * a){
    memset(a, 0, sizeof a);
}
void sub(longint * a, longint * b, int pos, int len){
    init(a);
    a -> lenth = len;
    a -> tag = 0;
    for(int i = pos ; i < pos + len ; i ++){
        a -> num[i] = b -> num[i];
    }
}
void cpy(longint * a, longint * b){
    init(a);
    a -> tag = b -> tag;
    a -> lenth = b -> lenth;
    for(int i = 0; i < b -> lenth; i ++){
        a -> num[i] = b -> num[i];
    }
}
void solve_add(longint * a, longint * b, longint * c){
    findmax(a, b);
    reverse(a); reverse(b);
    add(a, b, c);
    reverse(a); reverse(b);
    reverse(c);
}
void solve_less(longint * a, longint * b, longint * c){
    if(b -> tag == -1){
        b -> tag = 0;
        solve_add(a, b, c);
    }
    else {
        b -> tag = -1; 
        solve_add(a, b, c);
    }
}
void solve_multiply(longint * a, longint * b, longint * c){// c must return to 0;
    init(c);
    findmax(a, b);
    reverse(a); reverse(b);
    multiply(a, b, c);
    reverse(a); reverse(b);
    reverse(c);
}
void move_left(longint  * a){
    a -> lenth ++;
}
void divv(longint * a, longint * b, longint *c){
    if(a -> tag == b -> tag) c -> tag = 0;
    else c -> tag = -1;
    int pos = 0, len = b -> lenth;
    longint temp , res;
    init(& temp); init(& res);
    sub(& temp , a , pos, len);
    pos = pos + len - 1;
    res.lenth = 0; res.tag = 0; //init res empty
    longint x; x.lenth = 2; x.num[0] = 1; x.num[1] = 0; x.tag = 0;
    int f = 0;
    while(pos < a -> lenth){
        longint tt;
        if(f){
            // solve_multiply(& res, & x, & tt);//res * 10;//here boom!!!! // why boom?
            move_left(& res);
            res.num[res.lenth - 1] = a -> num[pos];
            cpy(& temp, & res);// tt -> temp
            init(& res);
        }
        f ++;
        int cnt = 0;
        while(findmax(& temp, b)){
            int t = b -> tag ;
            b -> tag = 0;
            solve_less(& temp , b, & res);
            b -> tag = t;
            cpy(& temp, & res);
            cnt ++;
        }
        longint  mid = temp; temp = *b , *b = mid;
        c -> num[c -> lenth] = cnt;
        c -> lenth ++;
        cpy(& res , & temp);
        pos ++ ;
    }
}
void solve_div(longint * a, longint * b, longint * c){
    divv(a, b, c);
}
int main(){
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    read(& a, & b);
    if(op == '+'){
        solve_add(& a, & b, & c);
    }
    else if(op == '-'){
        solve_less(& a, & b, & c);
    }
    else if(op == '*'){
        solve_multiply(& a, & b, & c);
    }
    else {
        solve_div(& a, & b, & c);
    }
    print(& c);
}