#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]){
	
	if (argc < 4){
		printf("Invalid arguments. Function requires 3 arguments.\n");
		printf("Please enter -h (hard link) or -s (soft link) for the first arg, filename for second, and the link name for the third.\n");
		exit(1);
	}else if (argc > 4){
		printf("Invalid arguments. Function requires 3 arguments.\n");
		printf("Please enter -h (hard link) or -s (soft link) for the first arg, filename for second, and the link name for the third.\n");
		exit(1);
	}
	
	char * option = argv[1];
	
	if (!strcmp(option, "-h")){
		//hard link
		if (link(argv[2], argv[3]) < 0){
			perror("Error creating hard link.\n");
			exit(2);
		} 
		printf("Hard link %s to %s created.\n", argv[3], argv[2]);
	} else if (!strcmp(option, "-s")){
		//soft link
		if (symlink(argv[2], argv[3]) < 0){
			perror("Error creating soft link.\n");
			exit(2);
		}
		printf("Soft link %s to %s created.\n", argv[3], argv[2]);
	} else {
		printf("Invalid option. Please enter -h (hard link) or -s (soft link) for the second argument.\n");
		exit(0);
	}

	return 0;
}
