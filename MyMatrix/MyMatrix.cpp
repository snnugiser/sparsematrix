#include "MyMatrix.h"


MyMatrix::MyMatrix(void)
{
  this->rows = 0;
  this->cols = 0;
  this->nums = 0;
}
MyMatrix::MyMatrix(vector<MyMap> m)
{
  //  m.length

}

MyMatrix::~MyMatrix(void)
{
}
int MyMatrix::set_value(int r,int c,double value)
{
  int i = 0;
  int k = 0;

  if ( r >= this->rows || c >= this->cols)
    return 0;
  while(k < this->
}
