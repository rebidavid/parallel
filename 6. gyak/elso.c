#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

const int N_THREADS = 60;

/**
 * Wait random time.
 */
void* wait_random_time(void* _)
{
  pthread_t thread;
  int wait_time;

  thread = pthread_self();
  wait_time = 1;
  printf("[%p] Wait %d seconds ...\n", thread.p, wait_time);
  sleep(wait_time);
  printf("[%p] Ready!\n", thread.p);
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int i;

  int count=0; // counter 

  printf(":: Start threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_create(&threads[i], NULL, wait_random_time, NULL);
     count+=1;
  }

  printf(":: Join threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
   
  }

  printf(":: Ready.\tcount: %d\n", count);


  return 0;
}