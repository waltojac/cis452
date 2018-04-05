#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define SIZE 16

struct sembuf sops[3];

void Wait(int semId);
void Signal(int semId);

int main (int argv, char * args[])
{
	int status;
	long int i, loop, temp, *shmPtr;
	int shmId;
	pid_t pid;
	int semId;


	printf("Creating semaphore\n");
	//create semaphore
	semId = semget (IPC_PRIVATE, 1, 0600);

	printf("Initializing semaphore\n");
	//initialize semaphore
	semctl (semId, 0, SETVAL, 1);

    // get value of loop variable (from command-line argument)
	loop = atoi(args[1]);
	printf("\nLoop: %ld\n", loop);

	printf("Creating shared memory\n");

   if ((shmId = shmget (IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
   }
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) {
      perror ("can't attach\n");
      exit (1);
   }

   shmPtr[0] = 0;
   shmPtr[1] = 1;

   if (!(pid = fork())) {
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[0] and shmPtr[1]
			   // CS
			Wait(semId);

			temp = shmPtr[0];
			shmPtr[0] = shmPtr[1];
			shmPtr[1] = temp;

			Signal(semId);
      }
      if (shmdt (shmPtr) < 0) {
         perror ("just can't let go\n");
         exit (1);
      }
      exit(0);
   }
   else
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[1] and shmPtr[0]
			   // CS
			Wait(semId);

			temp = shmPtr[1];
			shmPtr[1] = shmPtr[0];
			shmPtr[0] = temp;

			Signal(semId);
      }

   wait (&status);
   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

   if (shmdt (shmPtr) < 0) {
      perror ("just can't let go\n");
      exit (1);
   }
   if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit(1);
   }

	//free semaphore
	semctl(semId, 0, IPC_RMID);
   return 0;
}

void Wait(int semId) {

	// Decrement val by 1
	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;
/*
	// Wait for val to become 0
	sops[1].sem_num = 0;
	sops[1].sem_op = 0;
	sops[1].sem_flg = 0;

	*/
	if(semop(semId, sops, 1) < 0) {
		perror("semop");
		exit(1);
	}
}

void Signal(int semId) {

	// Increment value by 1
	sops[2].sem_num = 0;
	sops[2].sem_op = 1;
	sops[2].sem_flg = 0;

	if(semop(semId, sops + 2, 1) < 0) {
		perror("semop");
		exit(1);
	}
}
