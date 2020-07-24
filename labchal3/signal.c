#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIGUSR1 10
#define SIGUSR2 12
#define SIGALRM 14

static int one = 0, two = 0, alrm = 0;

static void handler1(int sig) {
  one++;
}

static void handler2(int sig) {
  two++;
}

static void handleralrm(int sig) {
  alrm++;
}

int main(int argc, char *argv[]) {

   //signal masks
  if (signal(SIGUSR1, handler1) == SIG_ERR) {
    exit(-1);
  }
  if (signal(SIGUSR2, handler2) == SIG_ERR) {
    exit(-1);
  }
  if (signal(SIGALRM, handleralrm) == SIG_ERR) {
    exit(-1);
  }
  int f, e, g;
  //do forks  
  if((f = fork()) == 0){
    printf("%i\n", atoi(argv[1]));
    int s = atoi(argv[1]);
    for(int i = 0; i < s; ++i){
      kill(getppid(), SIGUSR1);
      sleep(1);
    }
    exit(0);
  }
  if(f != 0){
    if((e = fork()) == 0){
      int s = atoi(argv[2]);
      for(int i = 0; i < s; ++i){
        kill(getppid(), SIGUSR2);
        sleep(1);
      }
      exit(0);

    }else{
      if ((g = fork()) == 0){
        int s = atoi(argv[3]);
        for(int i = 0; i < s; ++i){
          kill(getppid(), SIGALRM);
          sleep(1);
         }
        exit(0);
      }
    }
  }

  //don't forget about kill(getppid(), SIGUSR1) for example
  int r = 0;
  while(r < 10){
    sleep(1);
    ++r;
  }

  int wstatus;
  wait(&wstatus);
  printf("\n%i, %i, %i\n", one, two, alrm);
}
