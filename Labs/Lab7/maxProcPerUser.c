#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int numProc = 0;
	pid_t child_pid;
	int flag = 1;
	pid_t parentPid = getpid();

	while(flag){
		if (getpid() == parentPid)
			child_pid = fork();
		if (child_pid < 0){			//error
			flag = 0;
		}
		numProc++;
	}

	if (getpid() == parentPid){
		printf("Number of processes: %d", numProc);
		fflush(stdout);
	}

	exit(0);

}
