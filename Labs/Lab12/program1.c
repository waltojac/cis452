#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];

int depthFirstSearch(DIR* dir, char* option);

int main(int argc, char* argv[]){
	
	if(argc < 3) {
		printf("Need 3 arguments: name [-i, -j] filepath\n");
		return 1;
	}

	DIR *dir = opendir(argv[2]);

	if (!strcmp(argv[1], "-n")) {
		stat(argv[2], &statbuf);
		printf("Total: %d\n", (int)(statbuf.st_blocks));
	}

	/* Loop through directory entries. */
	while ((dp = readdir(dir)) != NULL) {

		char* filename;
		filename = (char*)calloc(256, sizeof(char));

		strcat(filename, argv[2]);
		strcat(filename, dp->d_name);

		/* Get file's information. */
		if (stat(filename, &statbuf) == -1){
			free(filename);
			perror("Exit reason: \n");
			continue;
		}

		//printf("File in question: %s\n", filename);
		if (!strcmp(argv[1], "-n")) {
			
			/* Print out UID */
			printf("%d", statbuf.st_uid);

			/* Print out GID */
			printf(" %d", statbuf.st_gid);

			/* Print size of file. */
			printf(" %jd", (intmax_t)statbuf.st_size);

			/* Print modification date of file. */
			tm = localtime(&statbuf.st_mtime);
			strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
			printf(" %s", datestring);
			
			/* Print filename */
			printf(" %s\n", dp->d_name);

		} else if (!strcmp(argv[1], "-i")) {
			
			/* Print out inode # */
			printf("%d", (int)(statbuf.st_ino));

			/* Print filename */
			printf(" %s\n", dp->d_name);
		}
		

		free(filename);

	}
	//perror("Exit reason: \n");
	closedir(dir);
	return 0;
}

