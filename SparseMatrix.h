#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <vector>
#include "Trituple.h"
#include "pair.h"
#define MAX_LINE  100 000;
using namespace std;
// ϵ������Ĵ洢


class CSparseMatrix
{
 public:
  //  CSparseMatrix(void);    //�ղ�����ʼ��
  ~CSparseMatrix(void);
  CSparseMatrix(const CSparseMatrix &A);
  CSparseMatrix( const int maxrow = 0,const int maxcol = 0,const int maxterm = 0 );    //��ʼ��
  bool insert_data(unsigned int r,unsigned int c, double v);                          //�����в���Ԫ��
  bool insert_data(Trituple t);                                      //�����в���Ԫ��
  CSparseMatrix Minus();                    //��-A
  CSparseMatrix Transpose();                                         // ϵ������ת��
  CSparseMatrix Transpose2();                                        //ת��
  double cal(CSparseMatrix *A,CSparseMatrix *B,const unsigned int i,const unsigned int j);
  bool sort();                                                    //����Ԫ�鰴���к�����
  //  bool RowCol();
  CSparseMatrix operator*( CSparseMatrix &A);
  bool calRowStart();
  unsigned int find(const unsigned int i);         //���ҵ�i�е�λ��
  double get_value(const int i,const int j);
  //  bool Order();                                                   //����
  // ����ϡ���������ӣ����ڶ���ϡ������е���������ȫ����������һ��ϡ�������
  bool smCat( CSparseMatrix& sm );
  bool matrixPrint();
  CSparseMatrix operator+( CSparseMatrix &A);
  bool set_rowcol(unsigned int i,unsigned int j);
  inline  unsigned int get_rows(){return this->Rows;}
  inline unsigned int get_cols(){return this->Cols;}
  vector<Trituple> smArray;  // ����Ԫ���ŵķ���Ԫ��
 private:
  unsigned int Rows,Cols,Terms;   // ϵ��������������ͷ���Ԫ�صĸ���
  vector<Mypair> rowStart;
};
double cal(const CSparseMatrix *A,const CSparseMatrix *B,const unsigned int i,const unsigned int j);
#endif
