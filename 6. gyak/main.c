#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 8 sleep for details.
#include <pthread.h>
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThread(void *vargp)
{
    int wait_time;
    wait_time = 8;
    sleep(wait_time);
    printf("Thread is sleeping %d sec \n", wait_time);
    return NULL;
}
   
int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThread, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}