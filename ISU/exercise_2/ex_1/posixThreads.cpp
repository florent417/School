#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NRTHREADS 2


typedef struct info {
  int id;
} threadData;

threadData threadDataArray[NRTHREADS];

void* print10Times(void* arg){
  threadData *myData;
  myData = (threadData*)arg;
  int id;
  id = myData->id;

  for (size_t i = 0; i < 10; i++)
  {
    printf("Hello world, it's thread %d\n", id);
    sleep(1);
  }

  pthread_exit(NULL);
}

int main(void)
{
  pthread_t threads[NRTHREADS];
  int rc, j;
  for (j = 0; j < NRTHREADS; j++)
  {
    threadDataArray[j].id = j+1;
    printf("In main: creating thread %d\n", j+1);
    rc = pthread_create(&threads[j], NULL, print10Times, (void*)&threadDataArray[j]);
    if (rc)
    {
      printf("ERROR, return code from pthread_create() is %d\n", rc);
    }
  }

  for (int i = 0; i < NRTHREADS; i++)
  {
    rc = pthread_join(threads[i], NULL);
    printf("Shutting thread %d down\n", i+1);
  }
}
