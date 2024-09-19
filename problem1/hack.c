#include <stdio.h>

int main(){
	printf("Show me your code,please.");
	while(1){
		int code;
		scanf("%d", & code);
		if(code >=  100000 && code <= 999999)
		{
			printf("I am super hacker!");
			return 0;
		}
		else printf("Fake code!");
	}
}
