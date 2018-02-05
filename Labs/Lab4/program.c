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
	//Install signal   handlers
	signal(SIGINT, sigHandler);

	//variables
	pthread_t thread1;  // thread ID holder 
	int status;         // captures any error code
	

	while(1){
		//user input
		char * input = (char*)malloc(sizeof(char)*64);
		
		//User Prompt
		printf("Enter filename: ");
	
		//grab string                         
		fgets(input, 64, stdin);	

		//spawn child and send filename
		if ((status = pthread_create(&thread1, NULL, worker, input)) != 0){
			fprintf(stderr, "Thread create error %d: %s\n",status, strerror(status));
			exit(1);
		}	
		
		sleep(3);
		free(input);
		//repeat
	}
}

void* worker(void* args){
	sleep(2);
	printf("\nRecieved: %s\n", (char*)args);
	return args;
}

void sigHandler(int sigNum){
	if (sigNum == SIGINT){
		//graceful shutdown
		printf("\nShutting down... \n");
		exit(0);
	}

}
