#pragma once
#include "Message.h"
#include <deque>
#include <iostream>
#include <stdio.h>
#include <pthread.h>

class MsgQueue
{
public:
  MsgQueue(unsigned long maxSize);
  void send(unsigned long id, Message* msg = NULL);
  Message * receive(unsigned long& id);
  ~MsgQueue();

private:
    struct Item
    {
      unsigned long id_;
      Message * msg_;
    };
    //Container with messages
    std::deque<Item *> MsgQ_;
    //Plus other variables
    unsigned long mxSize_=10;
    //Conditional and mutex
    pthread_cond_t cond_Receive = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond_Send = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
};
