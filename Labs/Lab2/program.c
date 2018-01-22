/**
 * Authors: Ben LaFeldt & Jake Walton
 * CIS 452
 * Purpose: Simple Shell program for Lab 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
  char input[64];
  char* token;
  int count = 1;
  int end = 1;
  char* args[20];
  //User Prompt
  printf("Enter command: ");

  //Get User Input
  fgets(input, 64, stdin);

  //========Testing==========

  //Parse input
  args[0] = strtok(input, " ");
  printf("First token: %s\n", token);
  //Calls to strtok after the first need to have
  //NULL as the string. Token will return null if
  //there are no more.
  //puts arguments into an array
  while (end)
  {
    args[count] = strtok (NULL, " ");
    count++;
    if (args[count - 1] == 0)
    {
      count -= 2;
      end = 0;
    }
  }

  printf("\nSec: %s ", args[1]);
  printf("\nThird: %s ", args[2]);

  return 0;
}
