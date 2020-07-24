#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Thread routine prototype.
void *thread(void *vargp);

int main(int argc, char **argv) {
  int threads;

  if(argc < 2)
    threads = 5;
  else
    threads = atoi(argv[1]);
  
  pthread_t tids[threads];
  printf("Hello from the main thread.\n");

  for(int i = 0; i<threads; ++i){
    printf("Creating thread %i.\n", i+1);
    pthread_create(&tids[i], NULL, thread, NULL);
  }
  
  // Wait and join two threads.
  printf("Main thread is going to wait on peer threads.\n");
  for(int i = 0; i<threads; ++i){
    pthread_join(tids[i], NULL);
  } 
  printf("Peer threads have completed.\n"); 
  return EXIT_SUCCESS;
}

void *thread(void *vargp) {
  // This thread gets the thread ID of the calling thread. Unlike the
  // process ID of a process, the thread ID is only unique to the
  // process that created it.
  sleep(1);
  pthread_t tid = pthread_self();
  printf("Hello from thread %u.\n", (unsigned int)tid);
  return NULL;
}
