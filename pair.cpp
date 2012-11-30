#include "pair.h"
Mypair::Mypair(void)
{
}
Mypair::Mypair(unsigned int rn,unsigned int sn)
{
  this->rn = rn;
  this->start = sn;
}
/*
unsigned int Mypair::find(unsigned int i)
{

}*/

bool Mypair::setStart(unsigned int rn,unsigned int sn)
{
  this->rn = rn;
  this->start = sn;
  return 0;
}
Mypair::~Mypair()
{
}

