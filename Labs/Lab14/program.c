/*
 * Title: Random number generator.
 * Authors: Jacob Walton and Ben LaFeldt
 * Date: 4/18/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
	
	int count = 0;
	int randSeed;

	//get the seed for random( from /dev/random)
	int randFile = open("/dev/random", O_RDONLY);
	read(randFile, &randSeed, sizeof(int));
	srandom(randSeed);
	close(randFile);
	
	while (count < 10){
		printf("%ld\n", random());
		count++;
	}
	return 0;
}
