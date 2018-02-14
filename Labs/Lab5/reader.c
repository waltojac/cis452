//Reader file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

void sigHandler(int sigNum);

int shmId;
char str[64];
char *shmPtr;
key_t set_key;


int main(){

	signal(SIGINT, sigHandler);

	//create key
	set_key = ftok("/home/waltojac/Documents/cis452/Labs/Lab5", 'a');

	if((shmId = shmget(set_key, 4096, S_IRUSR|S_IWUSR)) < 0 ) {
		perror("Error creating shared memory\n");
		exit(1);
	}
	

	if ((shmPtr = shmat(shmId, 0, 0)) == (void*) -1){
		perror("Can't attach\n");
		exit(1);
	}
	
	int offset = 8;
	char * msg = shmPtr + offset;
	int turn;

	printf("Reader setup complete.\n");
	while(1){
		while(*shmPtr == 0);
		//CS
		//read from shmPtr
		printf("%s", msg);
		*shmPtr = 0;
	}

	printf("%s", shmPtr);

	return 0;
}

void sigHandler(int sigNum){
	if(sigNum == SIGINT){
		//detach
		printf("Reader detaching from shared memory\n");
		if (shmdt(shmPtr) < 0){
			perror("Can't detach.");
			exit(1);
		}
		printf("Reader deallocating shared memory\n");
		if (shmctl (shmId, IPC_RMID, 0) < 0){
			perror("Can't deallocate.");
			exit(1);
		}
		printf("Exiting Reader...\n");
		exit(0);

	}

}
