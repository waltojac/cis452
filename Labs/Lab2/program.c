/** 
 * Authors: Ben LaFeldt & Jake Walton
 * CIS 452
 * Purpose: Simple Shell program for Lab 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array_push(char*** arr, int size, char* c);

int main (){
	char input[64];
	char** cmd_args = NULL;

	//User Prompt
	printf("Enter command: ");

	//Get User Input
	fgets(input, 64, stdin);

	//Parse input
	char* token = strtok(input, " \n");
	printf("Next token: %s\n", token);
	int count = 1;

	//empty array of cmd arguments
	cmd_args = (char**)malloc(sizeof(char*)*0);

	//If the current token exits, push onto array and get next one
	while(token != NULL) {
		array_push(&cmd_args, count, token);
		count = count + 1;
		token = strtok(NULL, " "); 
		printf("Next token: %s\n", token);
	}

	free(cmd_args);
	return 0;
}

int array_push(char*** arr, int size, char* c) {
	char** tmp = (char**)malloc(sizeof(*arr));
	tmp = *arr;
	*arr = malloc(sizeof(char*)*size);
	
	int i;
	for(i = 0; i < size-1; i++)
	{
		*arr[i] = (char*)malloc(sizeof(char*));
		strcpy(*arr[i], tmp[i]);
	}
	*arr[size-1] = (char*)malloc(sizeof(char*));
	strcpy(*arr[size-1], c);
	free(tmp);
	return 1;
}
