/**
 * Authors: Ben LaFeldt, Jake Walton
 * Date: 2018-02-01
 * Purpose: Lab Program demonstrating Communicating Processes
 * CIS 452
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Signal Handlers (SIGUSR1=30,10,16, SIGUSR2=31,12,17, SIGINT=2)
//SIGTERM kills the process it is sent to.
void sigHandler(int); 

// Globals
pid_t parent_pid;
pid_t child1_pid;
int status;
//pid_t child2_pid;

int main() {
	//Install signal handlers
	signal(SIGINT, sigHandler);
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);

	parent_pid = getpid();
	//Spawn child process
	child1_pid = fork();
	if(child1_pid < 0) {
		perror("An error occurred while forking");
		exit(1);
	} else if(child1_pid == 0) {	//Child Process
		srand(getpid());
		int sigs[2] = {SIGUSR1, SIGUSR2};
		while(1) {
			sleep(rand()%(6));
			kill(parent_pid, sigs[rand()%(2)]);	
		}

	} else {	// parent
		printf("spawned child PID# %d\n", child1_pid);
		printf("waiting...\t");
		fflush(stdout);
		wait(&status);
	}
	return 0;
}

void sigHandler(int sigNum) 
{
	switch(sigNum) {
		case SIGINT:
			if(child1_pid != 0) {
				printf(" received. Shutting down...\n");
			}

			exit(0);
			break;
		case SIGUSR1:
			//TODO: handle this signal
			printf("received a SIGUSR1 signal\n");
			printf("waiting...\t");
			fflush(stdout);
		case SIGUSR2:
			//TODO: handle this signal
			printf("received a SIGUSR2 signal\n");
			printf("waiting...\t");
			fflush(stdout);
	}
}
