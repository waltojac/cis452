/**
 * Authors: Ben LaFeldt & Jake Walton
 * CIS 452
 * Purpose: Simple Shell program for Lab 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mcheck.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int array_push(char*** arr, int size, char* c);
int free_arr(char*** arr, int size);

int main (){

	char input[64];
	char** cmd_args = NULL;
	pid_t pid;
	int status;

	//User Prompt
	printf("Enter command: ");

	//Get User Input
	fgets(input, 64, stdin);

	//Parse input
	char* token = strtok(input, " \n");
	int count = 1;

	//empty array of cmd arguments
	cmd_args = (char**)malloc(sizeof(char*)*1);

	//If the current token exits, push onto array and get next one
	while(token != NULL) {
		array_push(&cmd_args, count, token);
		count = count + 1;
		token = strtok(NULL, " \n"); 
	}

	//Spawn child process
	pid = fork();
	if(pid < 0)
	{
		fprintf(stderr, "An error occurred while forking");
		return -1;
	} else if (pid) {
		waitpid(pid, &status, 0);
	} else {
		printf("cmd_args[2]: %s\n", cmd_args[2]);
		execvp(cmd_args[0], &cmd_args[0]);
		/*
		printf("Exec fail\n");
		*/
		printf("Error: %s\n", strerror(errno));
		exit(errno);
	}


	free_arr(&cmd_args, count);
	return 0;
}

int array_push(char*** arr, int size, char* c) {
	char** tmp = (char**)malloc(sizeof(char*)*(size-1));
	memcpy(&tmp, arr, (sizeof(char*)*(size-1)));
	*arr = (char**)malloc(sizeof(char*)*size);
	
	int i;
	for(i = 0; i < (size-1); i++)
	{
		(*arr)[i] = (char*)malloc(sizeof(char*));
		strcpy((*arr)[i], tmp[i]);
	}
	(*arr)[size-1] = (char*)malloc(sizeof(char*));
	strcpy((*arr)[size-1], c);
	free(tmp);
	return 1;
}

int free_arr(char*** arr, int size) {
	int i;
	for(i = 0; i < size-1; i++)
	{
		char* currentPtr = (*arr)[i];
		free(currentPtr);
	}
	//free(arr);
	return 1;
}
