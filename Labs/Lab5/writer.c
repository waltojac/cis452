//Writer file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>


int main (){

	int shmId;
	char *shmPtr;
	key_t set_key;

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
