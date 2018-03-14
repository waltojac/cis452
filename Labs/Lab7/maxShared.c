#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>


int main () 
{ 
	int shmId; 
	char *shmPtr;
	int flag = 1;
	unsigned long long count = 4096l;

	while(flag == 1){
		if ((shmId = shmget (IPC_PRIVATE, count, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
			flag = 2;
			break;
		} 
		if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
	   		perror ("can't attach\n"); 
	   		exit (1); 
		}
		if (shmdt (shmPtr) < 0) { 
	   		perror ("just can't let go\n"); 
	   		exit (1); 
		}  
		if (shmctl (shmId, IPC_RMID, 0) < 0) { 
	   		perror ("can't deallocate\n"); 
	   		exit(1); 
		}
		printf("\nCount: %llu", count);
		count += 1000;
	}
	count -= 1000;
	while(flag == 2){
		if ((shmId = shmget (IPC_PRIVATE, count, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
			printf("\nMax Count: %llu\n", count - 1);
			perror ("i can't get no..\n"); 
			exit(0);
		} 
		if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
	   		perror ("can't attach\n"); 
	   		exit (1); 
		}
		if (shmdt (shmPtr) < 0) { 
	   		perror ("just can't let go\n"); 
	   		exit (1); 
		}  
		if (shmctl (shmId, IPC_RMID, 0) < 0) { 
	   		perror ("can't deallocate\n"); 
	   		exit(1); 
		}
		printf("\nCount: %llu", count);
		count += 1;
	}
    	return 0; 
}
