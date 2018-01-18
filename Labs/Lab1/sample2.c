#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int main()
{
	char *data1, *data2;
	int i;

	mtrace();

	do {
		data1 = malloc (SIZE);
		printf ("Please input your eos username: ");
		scanf ("%s", data1);
		if (!strcmp (data1, "quit")) {
			free (data1);
			break;
		}
		data2 = malloc (SIZE);
		for (i=0; i<SIZE; i++)
			data2[i] = data1[i];
		free (data1);
		printf ("data2 :%s:\n", data2);
		free (data2);
	} while (1);

	muntrace();
	return 0;
}
