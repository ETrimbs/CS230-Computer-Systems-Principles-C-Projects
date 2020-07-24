#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>   /* exit functions */
#include <string.h>
#include <unistd.h>   /* open, read */
#include "word.h"

#define BufSize       1 * sizeof(char) //read one char at a time
#define Env           "WORD_FREAK"
#define STDIN_FILENO  0
#define MaxWordLength 100
#define MaxWords      1000


void countWordsFD(int fd);

//wrapper method for to get file descriptor and call countWordsFD
void countWordsPointer(char* filePointer);

/* 
  Attempt to read file(s) in from argv, else from environment, else from stdin via pipe,
  then executes either a helper function or countWords directly.
*/
void wordFreak(int arg, char** argv);