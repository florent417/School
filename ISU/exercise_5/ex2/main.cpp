#include "Message.h"
#include "MsgQueue.h"
#include "Point3D.h"
#include <unistd.h>
#include <stdlib.h>

enum
{
  ID_READY,
};

//The only event handler in this case
void printCoordinates(Point3D * p)
{
  printf("Point coordinates: x:%d y:%d z:%d\n", p->x, p->y, p->z);
}

//Dispatcher, dispatches to a certain event handler
void dispatcher(Message* msg, unsigned long id)
{
  switch(id)
  {
    case ID_READY:
    {
      Point3D* point = static_cast<Point3D*>(msg);
      printCoordinates(point);
    }
      break;

    default:
      break;
  }
}

//Receiver and sender functions are events
void* ReceiverFunc(void* arg)
{
  MsgQueue* messageQ= static_cast<MsgQueue*>(arg);

  while(1)
  {
    unsigned long id;
    Message* msg = messageQ->receive(id);
    dispatcher(msg,id);
    delete msg;
  }
}

void* SenderFunc(void* arg)
{
  MsgQueue* msgQ= static_cast<MsgQueue*>(arg);
  while(1)
  {
    Point3D* p = new Point3D;
    //Assigning random coordinates
    p->x = rand()%10;
    p->y = rand()%10;
    p->z = rand()%10;

    msgQ->send(ID_READY, p);

    sleep(2);
  }
}

int main(void)
{
  MsgQueue msgQ(5);

  pthread_t receiverThd;
  pthread_t senderThd;

  pthread_create(&receiverThd, NULL, ReceiverFunc, &msgQ);
  pthread_create(&senderThd, NULL, SenderFunc, &msgQ);

  pthread_join(senderThd, NULL);
  pthread_join(receiverThd, NULL);

  return 0;
}
