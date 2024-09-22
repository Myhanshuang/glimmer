#include <stdio.h>
#include <stdlib.h>
int lenth;
typedef struct node{
    int data;
    struct node *next;
}Listnode;

Listnode *h;

void insert_head_or_tail(int pos, int dataa){
    if(pos == 1){
        Listnode * newnode;
        newnode = (Listnode *)malloc(sizeof(Listnode));
        newnode -> next = h -> next ;
        h -> next = newnode;
        newnode -> data = dataa;
    }
    else {
        Listnode *temp = h;
        while(temp -> next != NULL)
            temp = temp -> next;
        Listnode *newnode;
        newnode = (Listnode*)malloc(sizeof (Listnode));
        newnode -> data = dataa;
        temp -> next = newnode;
        newnode -> next = NULL;
    }
    lenth ++;
}
void delet(int pos){
    if(pos > lenth + 1)return ;
    Listnode *p = h;

    for(int i = 1; i < pos; i ++)
        p = p -> next;
    Listnode *temp = p;
    p = p -> next;
    temp -> next = p -> next;
    free(p);
}
void print(){
    Listnode *a = h -> next;
    while(a != NULL){
        printf("%d ", a -> data);
        a = a -> next ;
    }
}
void init(){
    lenth = 0;
    h = (Listnode*)malloc(sizeof(Listnode));
    h -> next = NULL;
    insert_head_or_tail(1, 1);
}

int main(){

    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    init();

    while(1){
        char op;
        int a, b, c;
        scanf(" %c", & op);
        if(op == 'C') {
            print();
            Listnode * temp = h;
            while(temp -> next != NULL)
                temp = temp -> next;
            temp -> next = h;
            return 0;
        }
        else if(op == 'T'){
            scanf("%d%d%d", & a, & b, & c);
            insert_head_or_tail(lenth + 1, a);
            insert_head_or_tail(lenth + 1, b);
            insert_head_or_tail(lenth + 1, c);
        }
        else if(op == 'H'){
            scanf("%d%d%d", & a, & b, & c);
            insert_head_or_tail(1, c);
            insert_head_or_tail(1, b);
            insert_head_or_tail(1, a);
        }
        else if(op == 'D'){
            scanf("%d", & a);
            delet(a);
            lenth --;
        }
    }
}