#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "Vector.hpp"
#include <iostream>

Vector shared;
pthread_mutex_t mut;

void* writer(void* arg)
{
  int id = *(int*)arg;
  pthread_mutex_lock(&mut);
  if(!shared.setAndTest(id))
  {
    printf("Error on thread %d\n", id);
  }
  sleep(1/100);

  pthread_mutex_unlock(&mut);

  pthread_exit(NULL);
}

int NRTHREADS;

int main(void)
{
  std::cout<<"Skriv antal threads: mellem 1 og 100\n";
  std::cin >> NRTHREADS;
  NRTHREADS = (0 < NRTHREADS <= 100? NRTHREADS:10);
  std::cout << "Antal threads som oprettes: " << NRTHREADS << std::endl;
  pthread_t threads[NRTHREADS];

  int rc;

  for (int i = 0; i < NRTHREADS; i++)
  {
    printf("In main: creating thread %d\n", i+1);

    int* id = new int(i+1);
    rc = pthread_create(&threads[i], NULL, writer, id);
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
  return 0;
}
