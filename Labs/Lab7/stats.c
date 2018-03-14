#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
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

	//create and allocate the structure for num of processes
	struct rlimit *fsize;
	fsize = (struct rlimit *)malloc(sizeof(struct rlimit));
	
	//check the limit of the resource NPROC
	getrlimit(RLIMIT_FSIZE, fsize);
	
	printf("\n--- File size ---\n");
	printf("Hard limit:\t%llu\n", (unsigned long long)(fsize->rlim_max));
	printf("Soft limit:\t%llu\n", (unsigned long long)(fsize->rlim_cur));
	
	free(fsize);

	
	//create and allocate the structure for num of files
	struct rlimit *nofile;
	nofile = (struct rlimit *)malloc(sizeof(struct rlimit));
	
	//check the limit of the resource NPROC
	getrlimit(RLIMIT_NOFILE, nofile);
	
	printf("\n--- Number of Files ---\n");
	printf("Hard limit:\t%d\n", (int)(nofile->rlim_max));
	printf("Soft limit:\t%d\n", (int)(nofile->rlim_cur));
	free(nofile);

	//create and allocate the structure for num of files
	struct rlimit *as;
	as = (struct rlimit *)malloc(sizeof(struct rlimit));
	
	//check the limit of the resource NPROC
	getrlimit(RLIMIT_MEMLOCK, as);
	
	printf("\n--- Number of Pages ---\n");
	printf("Hard limit:\t%d\n", (int)(as->rlim_max)/4096);
	printf("Soft limit:\t%d\n", (int)(as->rlim_cur)/4096);


	return 0;

}
