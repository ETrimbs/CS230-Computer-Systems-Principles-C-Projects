// PRIVATE BEGIN
#include <stdio.h>
#include <unistd.h>

extern char** environ;
// PRIVATE END

// goal: print the environment variables to the file "env.txt", one per line
// (If envp is NULL, the file should be empty, opening in write mode will do that.)
// example:
//   inputs:
//     envp/environ = {"E1=2","E2=7",NULL}
//   outputs:
//     env.txt as a string would be "E1=2\nE2=7\n"
// example:
//   inputs:
//     envp/environ = {NULL} or NULL
//   outputs:
//     env.txt as a string would be ""
//
// TODO: write and complete the main function

int main()
{
  FILE* file = fopen("./env.txt", "w");
  int i = 0; 
  while(environ[i] != NULL){
    fprintf(file, "%s\n", environ[i]);
    ++i;
  }
  fclose(file);
}
