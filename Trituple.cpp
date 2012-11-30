#include <iostream>
#include "Trituple.h"
using namespace std;
Trituple::Trituple(void)
{
}
Trituple::Trituple(const unsigned int r, const unsigned int c,const double v)
{
  this->row = r;
  this->col = c;
  this->Value = v;
}
bool Trituple::set_value3(const unsigned int r,const unsigned int c,const double v)
{
  //  cout<<"set Trituple"<<endl;
  this->row = r;
  this->col = c;
  this->Value = v;
  /*  cout<<this->row<<endl
      <<this->col<<endl
      <<this->Value<<endl;
      cout<<"set Trituple end"<<endl;*/
}
bool Trituple::set_value(const double v)
{
  this->Value = v;
}

