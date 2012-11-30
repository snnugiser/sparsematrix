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
  int rows;                    //����
  int cols;                    //����
  int nums;                    //����Ԫ�ظ���
  vector<double> data;
  vector<pair> p;
};

#endif 
