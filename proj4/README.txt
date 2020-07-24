----------------------------------------Code Overview
The code flow is pretty simple...
The main thread calls jimmy_fallon, where it initializes the global semaphores. Then, it creates the number of threads specified in
argv and stores references to them. Then, it blocks by looping through and calling pthread_join on all of the threads. Lastly, it 
destroys the semaphores.

Each other thread calls the phonecall function, where it gets an id and waits for a phone connection, being careful in checking or 
incrementing the 'next_id' and 'connected' (# of connected calls) variables using the connected_lock binary semaphore. It sleeps for
a second in between attempts to be connected. Then, it waits to correct to an operator using the operator semaphore. It simulates 
ordering a ticket with sleep(1). Then, uses connected_lock to decrement 'connected' (hangs up) and exits.

----------------------------------------Video Link (Youtube)
https://youtu.be/0Tub8fMKmkY

----------------------------------------Project Requirements
Binary semaphores are used properly to protect critical regions of code.
  Binary semaphore connected_lock is initialized in jimmy_fallon(), then used when connecting a customer to a phone line and when hanging up
  (also, for interacting with with next_id).

  Calling: 
    while(1){
      sem_wait(&connected_lock);
      if(connected == NUM_LINES){
        sem_post(&connected_lock);
        printf("\nThread %i is calling line, busy signal", (int)tid);
        sleep(1);
      } else{
        ++connected;
        sem_post(&connected_lock);
        break;
      }
    }

  Hanging up:
    sem_wait(&connected_lock);
    --connected;
    sem_post(&connected_lock);
    printf("\nThread %i has hung up!\n", (int)tid);

A counting semaphore is used properly to restrict the use of resources (operators).
  The semaphore 'operators' is declared with 3 operators, then is used to simulate ticket ordering:

  sem_wait(&operators);
    printf("\nThread %i is speaking to operator", (int)tid);
    sleep(1); //simulate ticket ordering
  sem_post(&operators);

All semaphores are correctly initialized and destroyed.
  They are created at beginning of jimmy_fallon and destroyed at the end of the function, with error checking on creation and destruction.

A thread function exists and is implemented properly.
  Yes, void* phonecall(void* vargp);

A global integer next_id exists and is properly updated in the thread function.
  Yes, a local id is assigned to each thread with a placeholder value of -1. In the connected_lock portion of the thread function, the id is set
  and next_id is incremented:
    if(id == -1){
      id = next_id;
      ++next_id;
    }

The phonecall thread properly updates the shared state for the number of callers in a critical section.
  Yes, if connected != NUM_LINES, then connected is incremented and is not decremented again until the thread has finished communicating
  with the operator.

The program properly prints output with the caller’s id.
  Yes, in every line of output in phonecall.

The static modifier is used properly for both the thread local variables as well as any globals.
  Yes, static variables are used as is defined in the instructions and the additional next_id variable is a static variable.