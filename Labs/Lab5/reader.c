//Reader file
#include <stdio.h>
#include <stdlib.h>


int main(){
	int shmId;
	char str[64];
	char *shmPtr;

	//get the shmId from the user
	printf("Please enter the shared memory ID: \n");
	fgets(str, 64, stdin);
	shmId = atoi(str);

	if ((shmPtr = shmat(shmId, 0, 0)) == (void*) -1){
		perror("Can't attach\n");
		exit(1);
	}
	
	printf("%s", shmPtr);

	return 0;
}
