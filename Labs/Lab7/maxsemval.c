#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

int main() {
	printf("Testing semaphore counting limit\n");

	int semId;
	

	//Create semaphore
	semId = semget(IPC_PRIVATE, 1, (IPC_CREAT | IPC_EXCL | 0600));
	if(semId < 0) {
		fprintf(stderr, "Valueof errno: %d\n", errno);
		exit(errno);
	}

	//Initialize semaphore to max size
	if( semctl(semId, 0, SETVAL, 32766) < 0) {
		fprintf(stderr, "Valueof errno: %d\n", errno);
		exit(errno);
	}

	//Increase semaphore
	struct sembuf sop;
	sop.sem_num = 0;
	sop.sem_op = 1;
	sop.sem_flg = 0;
	int val = semctl(semId, 0, GETVAL);
	while(1) {
		printf("Val is %d\n", val);
		if( semop(semId, &sop, 1) < 0) {
			fprintf(stderr, "Valueof errno: %d\n", errno);
			if(errno == ERANGE) {
				fprintf(stderr, "Out of range.\n");
			}
			//Remove semaphore
			semctl(semId, 0, IPC_RMID);
			exit(errno);
		}
		
		val = semctl(semId, 0, GETVAL);
		if( val < 0) {
			fprintf(stderr, "Valueof errno: %d\n", errno);
			//Remove semaphore
			semctl(semId, 0, IPC_RMID);
			exit(errno);
		}
	}

	//Remove semaphore
	semctl(semId, 0, IPC_RMID);


	return 0;
	

}
