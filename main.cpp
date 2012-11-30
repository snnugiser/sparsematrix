#include<fstream>
#include<iostream>
#include "SparseMatrix.h"
#include "Trituple.h"
int main()
{
  CSparseMatrix A;
  Trituple t;
  unsigned int rows;
  unsigned int cols;
  fstream infile;
  infile.open("data.dat",fstream::in);

  if(!infile)
    {
      cerr<<"error:unable to open input file:"
          <<endl;
      return -1;
    }
  infile>>rows>>cols;
  //  cout<<"begin read data"<<endl;
  unsigned int r;
  unsigned int c;
  double v;
  do{
    infile>>r>>c>>v;
    t.set_value3(r,c,v);
    A.insert_data(r,c,v);
    //   cout<<"succefully!"<<endl;
  }while(!infile.eof());
  infile.close();
  cout<<"the matrix A's cell is "<<endl;
  A.matrixPrint();
  CSparseMatrix B = A.Minus();
  cout<<"the matrix B's cell is"<<endl;
  B.matrixPrint();
  B=B.Transpose2();

  CSparseMatrix C = A*B;
  cout<<"the matrix C's cell is"<<endl;
  C.matrixPrint();


}

