/** 
 * Authors: Ben LaFeldt & Jake Walton
 * CIS 452
 * Purpose: Simple Shell program for Lab 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
	char input[64];
	char* token;

	//User Prompt
	printf("Enter command: ");

	//Get User Input
	fgets(input, 64, stdin);

	//========Testing==========

	//Parse input
	token = strtok(input, " ");
	printf("First token: %s\n", token);
	//Calls to strtok after the first need to have
	//NULL as the string. Token will return null if 
	//there are no more.
	token = strtok(NULL, " "); 
	printf("Second token: %s\n", token);
	//=========================


	return 0;
}
