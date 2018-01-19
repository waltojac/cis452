#include <stdio.h>
#include <stdlib.h>

int main (){
	char input[64];
	printf("Enter command: ");
	scanf("%[^\n]s", input);
	printf("\n%s\n", input);




	return 0;
}
