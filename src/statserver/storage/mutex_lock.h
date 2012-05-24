#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

namespace flstorage
{
class RWLock
{
 public:
  RWLock()
  {
    if (pthread_rwlock_init(&lock_, NULL) != 0)
    {
      abort();
    }
  }

  void WLock()
  {
    pthread_rwlock_wrlock(&lock_);
  }

  void RLock()
  {
    pthread_rwlock_rdlock(&lock_);
  }

  void UnLock()
  {
    pthread_rwlock_unlock(&lock_);
  }

  ~RWLock() 
  {
    pthread_rwlock_destroy(&lock_);
  }

 private:
  pthread_rwlock_t lock_;
};

class Mutex
{
 public:
  Mutex()
  {
    if (pthread_mutex_init(&lock_, NULL) != 0)
    {
      abort();
    }
    if (pthread_cond_init(&cond_, NULL) != 0)
    {
      abort();
    }
  }

  void Lock()
  {
    pthread_mutex_lock(&lock_);
  }

  void UnLock()
  {
    pthread_mutex_unlock(&lock_);
  }

  void Wait(time_t second)
  {
    struct timeval tv;
    struct timespec ts;
    gettimeofday(&tv, NULL);
    ts.tv_sec = tv.tv_sec + second;
    pthread_cond_timedwait(&cond_, &lock_, &ts); 
  }

  void Signal()
  {
    pthread_cond_signal(&cond_); 
  }

  ~Mutex() 
  {
    pthread_mutex_destroy(&lock_);
    pthread_cond_destroy(&cond_);
  }

 private:
  pthread_mutex_t lock_;
  pthread_cond_t cond_;
};



}

#endif

