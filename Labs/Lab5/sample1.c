#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

#define FOO 4096

int main () 
{ 
	int shmId; 
	char *shmPtr;

	if ((shmId = shmget (IPC_PRIVATE, FOO, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
		perror ("i can't get no..\n"); 
		exit (1); 
	} 
	if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
		perror ("can't attach\n"); 
		exit (1); 
	}
	printf ("value a: %lu\t value b: %lu\n", (unsigned long) shmPtr, (unsigned long) shmPtr + FOO);

	//Edited for Question 4 ---------------
	struct shmid_ds* buf;
	buf = (struct shmid_ds*)malloc(sizeof(struct shmid_ds));
	if(shmctl( shmId, IPC_STAT, buf) < 0)
	{
		perror("Error getting statistics\n");
		exit(1);
	}
	printf("Shared memory segment size: %ld\n", buf->shm_segsz);
	free(buf);

	//-------------------------------------

	if (shmdt (shmPtr) < 0) { 
		perror ("just can't let go\n"); 
		exit (1); 
	} 
	if (shmctl (shmId, IPC_RMID, 0) < 0) { 
		perror ("can't deallocate\n"); 
		exit(1); 
	}

	return 0; 
}
