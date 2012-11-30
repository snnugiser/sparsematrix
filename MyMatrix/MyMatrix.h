#ifndef MYMATRIX_H
#define MYMATRIX_H
#include <vector>
#include <bitset>
#include "MyPair.h"
using namespace std;
class MyMatrix
{
public:
  MyMatrix(void);
  MyMatrix(vector<MyMap> m);
  ~MyMatrix(void);
  int set_value(int r,int c,double value);
 private:
  int rows;                    //行数
  int cols;                    //列数
  int nums;                    //非零元素个数
  vector<double> data;
  vector<pair> p;
};

#endif 
