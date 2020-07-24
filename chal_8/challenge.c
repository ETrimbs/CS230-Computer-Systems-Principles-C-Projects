#include "challenge.h"

extern char** environ;

// goal: fork the process and have the child execute a process
// param argv: the argument vector for the process to be executed
// assumptions:
//   the first argument of argv is the file name of the executable
//   argv is null terminated
//
// TODO: complete the function
//   fork
//   exec (child), probably most convenient to use execvp
//   have the parent wait on the child
void fork_exec(char** argv){
  int status;
  int cid = fork();
  if(cid == -1){
    exit(0);
  }

  if(cid == 0){//child
    if(argv[0] != NULL){
      // int execve(const char *pathname, char *const argv[], char *const envp[]);
      if(execve(argv[0], argv, environ) == -1){
        exit(1);
      }
    }
  }
  else{
    wait(&status);
  }
}
