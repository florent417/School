#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NRTHREADS 2

unsigned int shared = 0;

void* incrementer(void* arg)
{
  for (size_t i = 0; i < 10; i++)
  {
    shared++;
    sleep(1);
  }

  pthread_exit(NULL);
}

void* reader(void* arg)
{
  for (size_t i = 0; i < 10; i++)
  {
    printf("Shared int is = %d\n", shared);
    sleep(1);
  }

  pthread_exit(NULL);
}

int main(void)
{
  pthread_t threads[NRTHREADS];
  int rc;

  printf("In main: creating threads reader, and incrementer\n");
  rc = pthread_create(&threads[0], NULL, reader, NULL);
  if (rc)
  {
    printf("ERROR, return code from pthread_create() is %d\n", rc);
  }

  rc = pthread_create(&threads[1], NULL, incrementer, NULL);
  if (rc)
  {
    printf("ERROR, return code from pthread_create() is %d\n", rc);
  }

  for (int i = 0; i < NRTHREADS; i++)
  {
    rc = pthread_join(threads[i], NULL);
    printf("Shutting thread %d down\n", i+1);
  }
}
