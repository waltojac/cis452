#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
/*	
	//create and allocate the structure for num of processes
	struct rlimit *nproc;
	nproc = (struct rlimit *)malloc(sizeof(struct rlimit));
	
	//check the limit of the resource NPROC
	getrlimit(RLIMIT_NPROC, nproc);

	
	printf("\n--- Number of Processes ---\n");
	printf("Hard limit:\t%d\n", (int)(nproc->rlim_max));
	printf("Soft limit:\t%d\n", (int)(nproc->rlim_cur));

	//deallocate nproc
	free(nproc);
*/	
	//create and allocate the structure for num of processes
	struct rlimit *fsize;
	fsize = (struct rlimit *)malloc(sizeof(struct rlimit));
	
	//check the limit of the resource NPROC
	getrlimit(RLIMIT_FSIZE, fsize);
	
	printf("\n--- File size ---\n");
	printf("Hard limit:\t%lu\n", (unsigned long)(fsize->rlim_max));
	printf("Soft limit:\t%lu\n", (unsigned long)(fsize->rlim_cur));
	
	free(fsize);

	return 0;

}
