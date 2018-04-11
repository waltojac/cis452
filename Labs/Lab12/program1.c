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

struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];

int depthFirstSearch(DIR* dir, char* option);

int main(int argc, char* argv[]){
	
	if(argc < 2) {
		return 1;
	}

	DIR *dir = opendir(argv[1]);

	/* Loop through directory entries. */
	while ((dp = readdir(dir)) != NULL) {

		/* Get entry's information. */
		if (stat(dp->d_name, &statbuf) == -1)
			continue;

		/* Print out mode of file*/
		printf(" %d", statbuf.st_mode);

		/* Print out owner's name*/
		printf(" %-8d", statbuf.st_uid);

		/* Print out group name*/
		printf(" %-8d", statbuf.st_gid);

		/* Print size of file. */
		printf(" %9jd", (intmax_t)statbuf.st_size);

		/* Print modification date of file. */
		tm = localtime(&statbuf.st_mtime);
		strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
		printf(" %s %s\n", datestring, dp->d_name);


	}
	return 0;
}

int depthFirstSearch(DIR* dir, char* option) {
		

}
