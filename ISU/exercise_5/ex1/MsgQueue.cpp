#include "MsgQueue.h"

using namespace std;

MsgQueue::MsgQueue(unsigned long maxSize)
:mxSize_(maxSize)
{}

void MsgQueue::send(unsigned long id, Message * msg)
{
  pthread_mutex_lock(&mut);

  //Blocks if the size of the queue is bigger than the maxsize
  while(MsgQ_.size() == mxSize_)
    pthread_cond_wait(&cond_Send, &mut);

  Item *item;
  item->msg_ = msg;
  item->id_ = id;
  MsgQ_.push_back(item);
  pthread_cond_signal(&cond_Receive);
  pthread_mutex_unlock(&mut);
}

Message * MsgQueue::receive(unsigned long& id)
{
  pthread_mutex_lock(&mut);

  //Blocks if queue is empty
  while(MsgQ_.empty())
    pthread_cond_wait(&cond_Receive, &mut);

  // New object of item is made. It's members are assigned
  //to the parameter and the message at front of the
  //Message queue.
  Item* item = MsgQ_.front();
  MsgQ_.pop_front();

  id = item->id_;
  Message * Msg = item->msg_;

  pthread_cond_signal(&cond_Send);
  pthread_mutex_unlock(&mut);


  return Msg;
}

MsgQueue::~MsgQueue(){}
