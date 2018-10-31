#ifndef SCOPED_LOCKER_
#define SCOPED_LOCKER_
/************************
Klassen tager en parameter i konstruktoren.
Den gemmer en private reference til den.
Mutexen bliver frigivet når Destruktoren kaldes.
(Den kaldes automatisk når vi forlader scope)
Der burde være implementeret, cope og assignment ifht.
*************************/
#include <pthread.h>
class scopedLockingIdiom
{
public:
  scopedLockingIdiom(pthread_mutex_t *mut) :mutex_(mut)
  {
    pthread_mutex_lock(mutex_);
  };
  //ScopedLocker(const ScopedLocker&); //Copy constructor
  ~scopedLockingIdiom()
  {
    pthread_mutex_unlock(mutex_);
  };
  //ScopedLocker &operator=(const ScopedLocker&); //assignment operator
private:
  pthread_mutex_t *mutex_; //mutex reference - givet mutex til klassen
};

#endif
