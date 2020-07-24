#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

static sem_t connected_lock;
static sem_t operators;
static int NUM_OPERATORS = 3;
static int NUM_LINES = 5;
static int connected = 0;    // Callers that are connected
static int next_id = 0;

/*
Here is a sketch of the phonecall thread function algorithm:

Print that an attempt to connect has been made.
Check if the connection can be made:
You'll need to test connected in a critical section
If the line is busy, exit the critical section, print a message, and try again
If the line is not busy, update connected, exit the critical section, and print a message, and continue to the next step.
Wait for an operator to be available (use a counting semaphore)
Print a message that the order is being taken by an operator
Simulate a ticket order by sleeping for a few seconds (sleep(3))
Print a message that the order is complete (and update the semaphore)
Update connected (using a binary semaphore)
Print a message that the call is over                */
void* phonecall(void* vargp){
  int id = -1;

  while(1){
    sem_wait(&connected_lock);
    if(id == -1){
      id = next_id;
      ++next_id;
    }
    if(connected == NUM_LINES){
      sem_post(&connected_lock);
      printf("\nThread %i is calling line, busy signal", id);
      sleep(1);
    } else{
      ++connected;
      sem_post(&connected_lock);
      break;
    }
  }
  printf("\nThread %i has available line, call ringing", id);

  sem_wait(&operators);
    printf("\nThread %i is speaking to operator", id);
    sleep(3); //simulate ticket ordering
  sem_post(&operators);

  printf("\nThread %i has bought a ticket!", id);

  sem_wait(&connected_lock);
  --connected;
  sem_post(&connected_lock);
  printf("\nThread %i has hung up!\n", id);
}

void jimmy_fallon(int n_callers){
  int er;
  
  if((er = sem_init(&operators, 0, 3)) != 0){
    printf("\nError initializing operators semaphore.\n");
    exit(1);
  }
   if((er = sem_init(&connected_lock, 0, 1)) != 0){
    printf("\nError initializing connected_lock semaphore.\n");
    exit(2);
  }

  pthread_t callers[n_callers];

  for(int i = 0; i < n_callers; ++i){
    if((er = pthread_create(&callers[i], NULL, &phonecall, NULL)) != 0){
      printf("\nError %i creating thread.\n", er);
      exit(3);
    }
  }

  for(int i = 0; i < n_callers; ++i){
    if((er = pthread_join(callers[i], NULL)) != 0){
      printf("\nError %i joining thread %i.\n", er, (int)callers[i]);
      exit(4);
    }
  }

  if((er = sem_destroy(&operators)) != 0){
    printf("\nError destroying operators semaphore.\n");
    exit(5);
  }
  if((er = sem_destroy(&connected_lock)) != 0){
    printf("\nError destroying connected_lock semaphore.\n");
    exit(6);
  }
}

int main(int argc, char **argv){
  if(argc > 1){
    jimmy_fallon(atoi(argv[1]));
  }
  else{
    printf("\nPlease supply in argv the number of callers.\n");
  }
}