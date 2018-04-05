#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//initialized globals
int g1 = 1;
int g2 = 1;
int g3 = 1;

//unitialized globals
int j;
int k;
int l;

int main(){
	printf("\nInit Globals: %p, %p, %p", &g1, &g2, &g3);
	printf("\nUnInit Globals: %p, %p. %p", &j, &k, &l);
	
	int a = 0;
	int b = 0;
	int c = 0;

	printf("\nStack: %p, %p, %p", &a, &b, &c);


	int *d = (int*)malloc(sizeof(int));
	int *e = (int*)malloc(sizeof(int));
	int *f = (int*)malloc(sizeof(int));
	printf("\nHeap: %p, %p, %p\n", d, e, f);

	printf("PID: %d\n", getpid());

	fflush(stdout);
	pause();
	return 0;

}
