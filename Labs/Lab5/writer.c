//Writer file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void sigHandler(int sigNum);
char *shmPtr;
int shmId;
key_t set_key;

int main (){
	signal(SIGINT,sigHandler);

	//create key
	set_key = ftok("/home/waltojac/Documents/cis452/Labs/Lab5", 'a');

	if((shmId = shmget(set_key, 4096, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0 ) {
		perror("Error creating shared memory\n");
		exit(1);
	}

	if((shmPtr = shmat(shmId, 0, 0)) == (void*) -1) {
		perror("Can't attach\n");
		exit(1);
	}

	int offset = 8;
	*(shmPtr + offset - 1) = '\0';
	char * msg = shmPtr + offset;
	*shmPtr = 0;
	int turn;

	while(1){
		printf("\nTurn: %d", turn);
		while (*shmPtr == 1);
		printf("\nWriter in critical section...");
		printf("\nEnter message: ");
		fflush(stdout);
		fgets(msg, 64, stdin);
		//CS
		//write to shmPtr

		*shmPtr = 1;
	}

	return 0;
}

void sigHandler(int sigNum){
	if(sigNum == SIGINT){
		//detach
		printf("Writer detaching from shared memory\n");
		if (shmdt(shmPtr) < 0){
			perror("Can't detach.");
			exit(1);
		}
		printf("Writer deallocating shared memory\n");
		//Deallocate
		if (shmctl (shmId, IPC_RMID, 0) < 0){
			perror("Can't deallocate.");
			exit(1);
		}
		printf("Exiting Writer...\n");
		exit(0);
	}

}
