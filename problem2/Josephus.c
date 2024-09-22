#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}Listnode;
int a[100];
Listnode * h;
int lenth;
void insert_tail(int data){
    Listnode *temp = h;
    while(temp -> next != NULL)
        temp = temp -> next;
    Listnode *newnode;
    newnode = (Listnode *)malloc(sizeof (Listnode));
    newnode -> next = NULL;
    newnode -> data = data;
    temp -> next = newnode;
    lenth ++;
}
void init(){
    h = (Listnode*)malloc(sizeof(Listnode));
    h -> next = NULL;
}
int main(){
    freopen("sample.out", "r", stdin);
    freopen("Josephus.out", "w", stdout);
    init();
    int cnt = 1, pos = 0;
    while(scanf("%d", &a[cnt]) == 1) {
        cnt ++;
        if(a[cnt - 1] == 3)pos = cnt -1;
    }
    cnt --;
    for(int i = pos; i <= cnt; i ++)
        insert_tail(a[i]);
    for(int i = 1;i < pos; i ++)
        insert_tail(a[i]);
    Listnode *p = h;
    while(p -> next != NULL)p = p -> next;
    p -> next = h -> next;
    Listnode *temp = h -> next;
    int t = 1;
    while(temp -> next != temp){
        for(int i = 1; i < t; i ++){
            p = temp ;
            temp = temp -> next;
        }
        printf("%d ", temp -> data);
        p -> next = temp -> next ;
        temp = temp -> next;
        t ++;
    }
    printf("%d", temp -> data);
    // Listnode *start = h -> next;
    // int t = 1;
    // Listnode *temp = start;
    // while(temp -> next != temp){
    //     temp = start;
    //     for(int i = 1; i < t; i ++){
    //         p = temp;
    //         temp = temp -> next;
    //     }
    //     printf("%d ", temp -> data);
    //     if(temp == start) start = temp -> next;
    //     p -> next = temp -> next;
    //     t ++;
    // }
    // printf("%d", start -> data);
}