//Writer file

#include <stdio.h>
#include <stdlib.h>



int main (){

	int shmId;
	char *shmPtr;

	if((shmId = shmget(IPC_PRIVATE, 4096, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0 ) {
		perror("Error creating shared memory\n");
		exit(1);
	}
	printf("Shared memory ID: %d\n", shmId);

	if((shmPtr = shmat(shmId, 0, 0)) == (void*) -1) {
		perror("Can't attach\n");
		exit(1);
	}

	return 0;
}
