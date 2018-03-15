#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
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



	long pageSize = sysconf(_SC_PAGESIZE);
	printf("\nPage Size: %ld\n", pageSize);
	printf("\nNumber of Pages: %ld\n", sysconf(_SC_PHYS_PAGES));
	

	//clock resolution
	clockid_t *clockid;
	struct timespec *timestats;

	clockid = (clockid_t*)malloc(sizeof(clockid_t));
	timestats = (struct timespec*)malloc(sizeof(struct timespec));

	//Get ID of current CPU Clock
	if(clock_getcpuclockid(0, clockid) < 0) {
		fprintf(stderr, "Error getting clock ID");
	}


	//Get resolution of clock
	if(clock_getres(*clockid, timestats) < 0) {
		fprintf(stderr, "Error getting clock resolution");
	}

	printf("\n--- Clock Resolution ---\n");
	printf("Seconds: %d\n", (int)(timestats->tv_sec));
	printf("nanoseconds: %ld\n", timestats->tv_nsec);
	
	free(timestats);
	free(clockid);

	return 0;

}
