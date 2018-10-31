#pragma once
#include "Message.h"
#include "MsgQueue.h"

struct Point3D : public Message
{
  int x;
  int y;
  int z;
};
