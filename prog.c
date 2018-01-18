#include <stdio.h>
#include <stdlib.h>

int main (){
	char input[64];
	printf("Hello. I am artificial intelligence.\n JK Enter command: ");
	scanf("%[^\n]s", input);
	printf("\n%s\n", input); 	
	

	return 0;
}
