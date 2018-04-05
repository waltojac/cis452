//Authors: Ben LaFeldt & Jacob Walton
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	LPSYSTEM_INFO sysinfo;
	sysinfo = (LPSYSTEM_INFO)malloc(sizeof(SYSTEM_INFO));
	
	GetSystemInfo(sysinfo);
	printf("Page Size: %d\n", sysinfo->dwPageSize);


	
	PMEMORY_BASIC_INFORMATION basicmeminfo;
	basicmeminfo = (PMEMORY_BASIC_INFORMATION)malloc(sizeof(MEMORY_BASIC_INFORMATION64));
	void* chunk;
	chunk = (void*)malloc(1048576);
	printf("-----Before-----\n");
	VirtualQuery(chunk, basicmeminfo, sizeof(MEMORY_BASIC_INFORMATION64));
	switch (basicmeminfo->State)
	{
	case 0x1000:
		printf("State: Committed\n");
		break;
	case 0x10000:
		printf("State: Free\n");
		break;
	case 0x2000:
		printf("State: Reserve\n");
		break;
	default:
		printf("Switch failed\n");
		printf("State: %lu\n", basicmeminfo->State);
		break;
	}
	
	free(chunk);
	printf("-----After-----\n");
	VirtualQuery(chunk, basicmeminfo, sizeof(MEMORY_BASIC_INFORMATION64));
	switch (basicmeminfo->State)
	{
	case 0x1000:
		printf("State: Committed\n");
		break;
	case 0x10000:
		printf("State: Free\n");
		break;
	case 0x2000:
		printf("State: Reserve\n");
		break;
	default:
		printf("Switch failed\n");
		printf("State: %lu\n", basicmeminfo->State);
		break;
	}

	free(basicmeminfo);
	free(sysinfo);

	//Extra Credit

	PSIZE_T mincachesize;
	PSIZE_T maxcachesize;

	mincachesize = (PSIZE_T)malloc(sizeof(SIZE_T));
	maxcachesize = (PSIZE_T)malloc(sizeof(SIZE_T));

	GetSystemFileCacheSize(mincachesize, maxcachesize, NULL);

	printf("-----Extra Credit-----\n");
	printf("Minimum File Cache Size: %lu Bytes\n", *mincachesize);
	printf("Maximumm File Cache Size: %lu Bytes\n", *maxcachesize);

	return 0;
}