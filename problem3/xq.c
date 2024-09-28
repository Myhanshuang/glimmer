#include <stdio.h>
#include <stdlib.h>

const int constValue = 100;
const char* constString = "Hello, World!";
int globalVar = 10;

void function(int arg) {
    int localVar = 20;
    int *ptr = malloc(sizeof(int));
    *ptr = 30;
    printf("localVar: %p\n", & localVar);
    printf("ptr:%p\n", & ptr);
    puts("");
    free(ptr);
}

int main() {
    freopen("place.out", "w", stdout);
    
    static int staticVar = 40;
    int localVarMain = 50;
    function(60);
    printf("constValue: %p\n", & constValue);
    printf("constString: %p\n", & constString);
    puts("");
    printf("globalVar: %p\n", & globalVar);
    printf("staticVar: %p\n", & staticVar);
    puts("");
    printf("localVarMain: %p\n", & localVarMain);
    return 0;
}