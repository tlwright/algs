/* multiple producer consumer */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atoi, rand */
#include <unistd.h>     /* sleep */
#include <pthread.h>
#include <semaphore.h>

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

  /* Create the full semaphore and initialize to 0 */
  sem_init(&full, 0, 0);
  /* Create the empty semaphore and initialize to BUFFER_SIZE  */

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
  } else { /* Error the buffer is full */
    return -1;
  }
}

void *producer(void *param) {
  buffer_item item;

  while(TRUE) {
    int rNum = rand() / RAND_DIVISOR; /* sleep for a random period of time */
    sleep(rNum);

    /* generate a random number: stdlib.h RAND_MAX is 2147483647 */
    item = rand();

    /* acquire (suspend if 0, dec) the empty sem (was init to BUFFER_SIZE) */
    sem_wait(&empty);
    pthread_mutex_lock(&mutex); /* acquire the mutex lock */

    if(insert_item(item)) {
      fprintf(stderr, "Producer report error condition\n");
    } else { printf("producer produced %d\n", item); }

    pthread_mutex_unlock(&mutex); /* release the mutex lock */
    /* signal (inc) the full sem (was init to 0) */
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
  } else { /* Error buffer empty */
    return -1;
  }
}

void *consumer(void *param) {
  buffer_item item;

  while(TRUE) {
    /* sleep for a random period of time */
    int rNum = rand() / RAND_DIVISOR;
    sleep(rNum);

    /* acquire (suspend if 0, dec) the full sem (was init to 0) */
    sem_wait(&full);
    pthread_mutex_lock(&mutex); /* acquire the mutex lock */

    if(remove_item(&item)) {
      fprintf(stderr, "Consumer report error condition\n");
    } else {      printf("consumer consumed %d\n", item); }

    pthread_mutex_unlock(&mutex); /* release the mutex lock */ 
    /* signal (inc) the empty sem (was init to BUFFER_SIZE) */
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

  /* Initialize the app */
  initializeData();
  printf("Starting %d producer threads\n", numProd);
  for(i = 0; i < numProd; i++) {
    /* Create the thread */
    pthread_create(&tid,&attr,producer,NULL);
  }
  printf("Starting %d consumer threads\n", numCons);
  for(i = 0; i < numCons; i++) {
    /* Create the thread */
    pthread_create(&tid,NULL,consumer,NULL);
  }

  printf("Sleeping for %d seconds\n", mainSleepTime);
  sleep(mainSleepTime);
  printf("Exit the program\n");
  exit(0);
}
