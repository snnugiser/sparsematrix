#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <vector>
#include "Trituple.h"
#include "pair.h"
#define MAX_LINE  100 000;
using namespace std;
// 系数矩阵的存储


class CSparseMatrix
{
 public:
  //  CSparseMatrix(void);    //空参数初始化
  ~CSparseMatrix(void);
  CSparseMatrix(const CSparseMatrix &A);
  CSparseMatrix( const int maxrow = 0,const int maxcol = 0,const int maxterm = 0 );    //初始化
  bool insert_data(unsigned int r,unsigned int c, double v);                          //矩阵中插入元素
  bool insert_data(Trituple t);                                      //矩阵中插入元素
  CSparseMatrix Minus();                    //求-A
  CSparseMatrix Transpose();                                         // 系数矩阵转置
  CSparseMatrix Transpose2();                                        //转置
  double cal(CSparseMatrix *A,CSparseMatrix *B,const unsigned int i,const unsigned int j);
  bool sort();                                                    //对三元组按行列号排序
  //  bool RowCol();
  CSparseMatrix operator*( CSparseMatrix &A);
  bool calRowStart();
  unsigned int find(const unsigned int i);         //查找第i行的位置
  double get_value(const int i,const int j);
  //  bool Order();                                                   //排序
  // 两个稀疏矩阵的连接，将第二个稀疏矩阵中的所有内容全部拷贝到第一个稀疏矩阵中
  bool smCat( CSparseMatrix& sm );
  bool matrixPrint();
  CSparseMatrix operator+( CSparseMatrix &A);
  bool set_rowcol(unsigned int i,unsigned int j);
  inline  unsigned int get_rows(){return this->Rows;}
  inline unsigned int get_cols(){return this->Cols;}
  vector<Trituple> smArray;  // 按三元组存放的非零元素
 private:
  unsigned int Rows,Cols,Terms;   // 系数矩阵的行列数和非零元素的个数
  vector<Mypair> rowStart;
};
double cal(const CSparseMatrix *A,const CSparseMatrix *B,const unsigned int i,const unsigned int j);
#endif
