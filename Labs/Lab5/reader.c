//Reader file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(){
	int shmId;
	char str[64];
	char *shmPtr;
	key_t set_key;

	//get the shmId from the user
	/*
	printf("Please enter the shared memory ID: ");
	fflush(stdout);
	fgets(str, 64, stdin);
	shmId = atoi(str);
	*/

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
