#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	DIR *dirPtr;
	struct dirent *entryPtr;

	dirPtr = opendir (".");

	struct stat statBuf;

	while ((entryPtr = readdir (dirPtr))) {

		if(stat(entryPtr->d_name, &statBuf) < 0){
			perror("invalid file name\n");
			exit(1);
		}
		printf ("%-20s\t%d\n", entryPtr->d_name, (int)(statBuf.st_size));
	}



	closedir (dirPtr);
	return 0;
} 
