/* multiple Producer-consumer_problem */
/* http://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem 
   fillCount is the number of items already in the buffer and available to
   be read, while emptyCount is the number of available spaces in the buffer
   where items could be written. fillCount is incremented and emptyCount
   decremented when a new item is put into the buffer. If the producer tries
   to decrement emptyCount when its value is zero, the producer is put to
   sleep. The next time an item is consumed, emptyCount is incremented and
   the producer wakes up. The consumer works analogously.

   Multicore Application Programming Darryl Gove 2010 Addison-Wesley
   PThreads Programming Dick Buttlar Brad Nichols 1996 O'Reilly 
   http://en.wikipedia.org/wiki/POSIX_Threads
   http://en.wikipedia.org/wiki/Semaphore_%28programming%29
   https://computing.llnl.gov/tutorials/pthreads/
   http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
   http://software.intel.com/en-us/intel-parallel-studio-xe/ $1599
   http://en.wikipedia.org/wiki/OpenMP 2013
   http://en.wikipedia.org/wiki/Unified_Parallel_C 2005
   http://en.wikipedia.org/wiki/Message_Passing_Interface 
   http://en.wikipedia.org/wiki/Open_MPI 2013
   http://en.wikipedia.org/wiki/Simple_Linux_Utility_for_Resource_Management
*/

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atoi, rand */
#include <unistd.h>     /* sleep */
#include <pthread.h>
#include <semaphore.h>

/* Main parses argv, runs initializeData, pthread_creates producer, consumer,
   sleeps and then exits.

   initializeData runs pthread_mutex_init, sem_init full (count) to 0,
   sem_init empty to BUFFER_SIZE, pthread_attr_init and sets counter to 0.

   producer sleeps, sem_waits on (dec) empty, locks mutex, calls insert_item,
   unlocks mutex, sem_posts (inc) full in a while true loop.

   consumer sleeps, sem_waits on (dec) full, locks mutex, calls remove_item,
   unlocks mutex, sem_posts (inc) empty in a while true loop.

   insert_item verifies counter < BUFFER_SIZE, copies item to buffer[counter]
   and increments counter or returns -1 if counter >= BUFFER_SIZE.

   remove_item verifies counter > 0, copies buffer[counter-1] to item
   and decrements counter or returns -1 if counter <= 0.
*/   

typedef int buffer_item;
#define BUFFER_SIZE 5
#define RAND_DIVISOR 100000000
#define TRUE 1

/* The mutex lock */
pthread_mutex_t mutex;
/* the semaphores */
/*
  sem_wait  suspends  the calling thread until the semaphore
  pointed to by sem has non-zero count. It  then  atomically
  decreases the semaphore count.
  sem_post  atomically  increases the count of the semaphore
  pointed to by sem.  This function  never  blocks  and  can
  safely be used in asynchronous signal handlers.
*/
sem_t full, empty;

/* the buffer */
buffer_item buffer[BUFFER_SIZE];
/* buffer counter */
int counter;

pthread_t tid;       /* Thread ID */
pthread_attr_t attr; /* Set of thread attributes */

void *producer(void *param); /* the producer thread */
void *consumer(void *param); /* the consumer thread */

void initializeData() {
  /* Create the mutex lock */
  pthread_mutex_init(&mutex, NULL);

  /* Create the full semaphore and initialize: 0 full slots  */
  sem_init(&full, 0, 0);
  /* Create the empty semaphore and initialize: BUFFER_SIZE empty slots */
  sem_init(&empty, 0, BUFFER_SIZE);

  /* Set the default attributes */
  pthread_attr_init(&attr);
  /* init buffer */
  counter = 0;
}

/* Add an item to the buffer */
int insert_item(buffer_item item) {
  /* When the buffer is not full add the item and increment the counter*/
  if(counter < BUFFER_SIZE) {
    buffer[counter] = item;
    counter++;
    return 0;
  } else { /* Error the buffer is full */ return -1; }
}

void *producer(void *param) {
  buffer_item item;

  while(TRUE) {
    int rNum = rand() / RAND_DIVISOR; /* sleep for a random period of time */
    sleep(rNum);

    /* generate a random number: stdlib.h RAND_MAX is 2147483647 */
    item = rand();

    /* acquire (suspend if 0, dec) the empty sem (was init to BUFFER_SIZE) */
    if (sem_trywait(&empty)) {
      printf("producer waiting: counter is %d\n", counter);
    }
    sem_wait(&empty);

    pthread_mutex_lock(&mutex); /* acquire the mutex lock */
    if(insert_item(item)) {
      fprintf(stderr, "Producer report error condition\n");
    } else { printf("producer produced %d\n", item); }
    pthread_mutex_unlock(&mutex); /* release the mutex lock */

    /* signal (inc) the full sem (slot count was init to 0) */
    sem_post(&full);
  }
}

/* Remove an item from the buffer */
int remove_item(buffer_item *item) {
  /* When the buffer is not empty remove the item and decrement the counter */
  if(counter > 0) {
    *item = buffer[(counter-1)];
    counter--;
    return 0;
  } else { /* Error buffer empty */ return -1; }
}

void *consumer(void *param) {
  buffer_item item;

  while(TRUE) {
    /* sleep for a random period of time */
    int rNum = rand() / RAND_DIVISOR;
    sleep(rNum);

    /* acquire (suspend if 0, dec) the full sem (slot count was init to 0) */
    if (sem_trywait(&full)) {
      printf("consumer waiting: counter is %d\n", counter);
    }
    sem_wait(&full);

    pthread_mutex_lock(&mutex); /* acquire the mutex lock */
    if(remove_item(&item)) {
      fprintf(stderr, "Consumer report error condition\n");
    } else {      printf("consumer consumed %d\n", item); }
    pthread_mutex_unlock(&mutex); /* release the mutex lock */ 

    /* signal (inc) the empty sem (slot count was init to BUFFER_SIZE) */
    sem_post(&empty);
  }
}

int main(int argc, char *argv[]) {
  /* Loop counter */
  int i, mainSleepTime, numProd, numCons;

  /* Verify the correct number of arguments were passed in */
  if(argc != 4) {
    fprintf(stderr, "USAGE: %s sleep-secs producers consumers\n", argv[0]);
    return 0;
  }

  mainSleepTime = atoi(argv[1]); /* Time in seconds for main to sleep */
  numProd = atoi(argv[2]); /* Number of producer threads */
  numCons = atoi(argv[3]); /* Number of consumer threads */

  initializeData(); /* Initialize the app */
  printf("Starting %d producer threads\n", numProd);
  for(i = 0; i < numProd; i++) { /* Create the thread */
    pthread_create(&tid,&attr,producer,NULL);
  }
  printf("Starting %d consumer threads\n", numCons);
  for(i = 0; i < numCons; i++) { /* Create the thread */
    pthread_create(&tid,&attr,consumer,NULL);
  }

  printf("Sleeping for %d seconds\n", mainSleepTime);
  sleep(mainSleepTime);
  printf("Exit the program\n");
  exit(0);
}
