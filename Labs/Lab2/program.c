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
  //variables
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

  //Parse first input
  args[0] = strtok(input, " ");

  //Calls to strtok after the first need to have
  //NULL as the string. Token will return null if
  //there are no more.This loop puts rest of arguments
  //into an array.
  while (end)
  {
    args[count] = strtok (NULL, " ");
    count++;
    //Check if all arguments have been tokenized.
    //strtok() will return 0 if there is no string left.
    if (args[count - 1] == 0)
    {
      count -= 2;
      end = 0;
    }
  }

  //print for testing of array
  printf("\nFirst: %s ", args[0]);
  printf("\nSec: %s ", args[1]);
  printf("\nThird: %s ", args[2]);

  return 0;
}
