#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t entry_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t exit_Mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t entry_Cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t exit_Cond = PTHREAD_COND_INITIALIZER;

bool entryDoorOpen = false;
bool exitDoorOpen = false;

bool carWaitingToEnter = false;
bool carWaitingToExit = false;

int NUMTHREADS;


void* entryGuard (void* arg) {
  while (1) {
    pthread_mutex_lock(&entry_Mutex);
    while (carWaitingToEnter == false)
      pthread_cond_wait(&entry_Cond,&entry_Mutex);
    entryDoorOpen = true;
    cout << "Opening entry door." << endl;
    pthread_cond_signal(&entry_Cond);
    while(carWaitingToEnter)
      pthread_cond_wait(&entry_Cond, &entry_Mutex);
    entryDoorOpen = false;
    cout << "Closing entry door." << endl;
    pthread_mutex_unlock(&entry_Mutex);
  }
}

void* exitGuard (void* arg) {
  while (1) {
    pthread_mutex_lock(&exit_Mutex);
    while (carWaitingToExit == false)
      pthread_cond_wait(&exit_Cond,&exit_Mutex);
    exitDoorOpen = true;
    cout << "Opening exit door." << endl;
    pthread_cond_signal(&exit_Cond);
    while(carWaitingToExit)
      pthread_cond_wait(&exit_Cond, &exit_Mutex);
    exitDoorOpen = false;
    cout << "Closing exit door." << endl;
    pthread_mutex_unlock(&exit_Mutex);
  }
}

void* Car (void* arg) {
  //Noget id til bilen
  int carID;

  while(1) {
    pthread_mutex_lock(&entry_Mutex);
    cout << "Car ID: " << carID <<" requesting to enter" << endl;
    carWaitingToEnter = true;
    pthread_cond_signal(&entry_Cond);
    while (entryDoorOpen == false)
      pthread_cond_wait(&entry_Cond,&entry_Mutex);
    carWaitingToEnter = false;
    cout << "Car ID: " << carID <<" has parked" << endl;
    pthread_cond_signal(&entry_Cond);
    pthread_mutex_unlock(&entry_Mutex);
    //tjek funktionen
    sleep(3);

    pthread_mutex_lock(&exit_Mutex);
    cout << "Car ID: " << carID <<" requesting to exit" << endl;
    carWaitingToExit = true;
    pthread_cond_signal(&exit_Cond);
    while (exitDoorOpen == false)
      pthread_cond_wait(&exit_Cond,&exit_Mutex);
    carWaitingToExit = false;
    cout << "Car ID: " << carID <<" has left the building" << endl;
    pthread_cond_signal(&exit_Cond);
    pthread_mutex_unlock(&exit_Mutex);
    //tjek funktionen
    sleep(3);
  }
}

int main(){
  // User input number of threads
  cout << "Skriv antal af threads: mellem 1 og 100" << endl;
  cin >> NUMTHREADS;
  NUMTHREADS = (0 < NUMTHREADS < 100 ? NUMTHREADS : 10);

  pthread_t threads[NUMTHREADS+2];

  int err;

  cout << "Creating pthreads for entry- and exit guards" << endl;

  err = pthread_create(&threads[0], NULL, entryGuard, nullptr);
  err = pthread_create(&threads[1], NULL, exitGuard, nullptr);

  for(int i = 2; i < NUMTHREADS; i++) {
    cout << "Creationg pthreads for car with car ID: ";
    cout << carID << endl;
    err = pthread_create(&threads[i], NULL, Car, &carID);
  }

  for (int i = 0; i < NUMTHREADS+2; i++) {
    err = pthread_join(threads[i], NULL);
    cout << "Shutting down thread " << i+1 << endl;
  }

}
