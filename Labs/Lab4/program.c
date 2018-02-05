/**
 * Authors: Ben LaFeldt and Jacob Walton
 * Date: 2018-02-08
 * Purpose: Lab program to simulate a multi-threaded file server.
 * Title: Lab 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void* worker(void* args);
void sigHandler(int sigNum);


int main(){
	//Install signal handlers
	signal(SIGINT, sigHandler);

	//variables
	char input[64];

	//grab a string
	printf("Enter filename: ");
	
	//grab string
	fgets(input, 64, stdin);	

	//spawn child and send filename
	
	
	//repeat
}

void* worker(void* args){


}

void sigHandler(int sigNum){
	if (sigNum == SIGINT){
		//graceful shutdown
	}

}
