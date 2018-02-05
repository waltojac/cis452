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

//usage statistics
int requests;
float totalAccessTime;

char* input;

//thread mutex variable
pthread_mutex_t lock;


int main(){
	
	//usage statistics initialization
	requests = 0;
	totalAccessTime = 0;
	

	//Install signal   handlers
	signal(SIGINT, sigHandler);

	//variables
	pthread_t thread1;  // thread ID holder 
	int status;         // captures any error code

	if (pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init failed.\n");
		return 1;
	}

	while(1){
		//user input
		input = (char*)malloc(sizeof(char)*64);
		
		//User Prompt
		printf("Enter filename: ");
	
		//grab string                         
		fgets(input, 64, stdin);	

		//spawn child and send filename
		if ((status = pthread_create(&thread1, NULL, worker, input)) != 0){
			fprintf(stderr, "Thread create error %d: %s\n",status, strerror(status));
			exit(1);
		}	

		requests++;

		if(pthread_detach(thread1)) {
			fprintf(stderr, "Error detaching thread\n");
			exit(1);
		}
	
		//repeat
	}
}

void* worker(void* args){
	pthread_mutex_lock(&lock);

	char * data = (char*)args;
	//Desired file found
	int prob = rand() % 10;
	
	//for 20% probability
	if(prob < 2) {
		printf("File \"%s\" not in cache, searching Hard Drive...\n", data);
		int sleepnum = rand() % 4 + 7;
		sleep(sleepnum);
		totalAccessTime += (float)sleepnum;
		printf("File \"%s\" found in Hard Drive\n", data);
	} 
	//for 80% probability
	else {
		sleep(1);
		totalAccessTime += 1.0;
		printf("File \"%s\" found in cache\n", data);
	}
	pthread_mutex_unlock(&lock);

	return args;
}

void sigHandler(int sigNum){
	if (sigNum == SIGINT){
		//graceful shutdown
		free(input);
		printf("\nTotal number of file requests received: %d\n", requests);
		printf("Average file access time: %f seconds.\n", totalAccessTime/requests);
		printf("\nShutting down... \n");
		exit(0);
	}

}
