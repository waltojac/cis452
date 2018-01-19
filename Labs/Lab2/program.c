#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){
    //variables
	char input[64];
    char *args[20];
    int end = 1;
    int count = 0;


	printf("Enter command: ");
	scanf("%[^\n]s", input);
	printf("\n%s\n", input);

    //puts arguments into an array
    while (end){
         strcpy(args[count], strtok (input, " "));
        count++;
        if (args[count-1] == NULL){
            count -= 2;
            end = 0;
        }
    }

    printf("\n%s, %s, %s\n", args[0], args[1], args[2]);

	return 0;
}
