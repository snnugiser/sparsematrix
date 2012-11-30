#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include "SparseMatrix.h"
#include "pair.h"
//#include "cal.h"
using namespace std;
/*CSparseMatrix::CSparseMatrix(void)
{
  this->Rows = 0;
  this->Cols = 0;
  this->Terms = 0;
}*/

CSparseMatrix::CSparseMatrix(const int maxrow ,const int maxcol ,const int maxterm  )
{
  Rows = maxrow;
  Cols = maxcol;
  Terms = maxterm;
}
CSparseMatrix::CSparseMatrix(const CSparseMatrix &A)
{
    this->Rows = A.Rows;
    this->Cols = A.Cols;
    this->Terms = A.Terms;
    this->smArray = A.smArray;
    this->rowStart = A.rowStart;
}
CSparseMatrix::~CSparseMatrix(void)
{
}
bool CSparseMatrix::insert_data(unsigned int r , unsigned int c ,double v)
{
  if(v == 0) return 0;
  Trituple t(r,c,v);
  this->insert_data(t);
  
}
bool CSparseMatrix::insert_data(Trituple t)
{
  if(t.get_value() == 0) return 0;
  //  for(vector<Trituple>::iterator ix = this->smArray.begin(); ix != this->smArray.end();++ix)
  vector<Trituple>::iterator ix = this->smArray.begin();
  if(ix == this->smArray.end())
    {
      this->smArray.insert(ix,t);
      return 0;
    }
  while(ix != this->smArray.end())
    {
      //      cout<<"while"<<endl;
      if(ix->befor(t))
	{
	  ++ix;
          //          cout<<"in while ix->befor(t)"<<endl;
          continue;

	}
      //cout<<"before break"<<endl;
      break;

    }
  //cout<<"skip out while"<<endl;
  
  if (t == *ix)
    {
      //cout<<"t==ix"<<endl;
      return 0;
    }
  if( ix->addr_same(t) )
    {
      //cout<<"addr_same"<<endl;
      //      ix->get_value = t->get_value;
      ix->set_value3 (ix->row,ix->col, t.get_value());
      return 0;
    }
  //cout<<"befor insert"<<endl;
  this->smArray.insert(ix,t);
  //cout<<"insert"<<endl;
  this->calRowStart();
  //  this->RowCol();
  //cout<<"inser_datae"<<endl;
  ( this->Terms)++;
  //cout<<"there is "<<this->Terms <<"cell in the matrix"<<endl;
  this->calRowStart();
  return 0;
}
CSparseMatrix CSparseMatrix::Minus()
{
  CSparseMatrix res(*this);
  //  res.matrixPrint();
  vector<Trituple>::iterator it = res.smArray.begin();
  for(vector<Trituple>::iterator ix = this->smArray.begin() ;ix != this->smArray.end(); ++ix)
    {
      it->set_value(ix->get_value()*(-1));
      //      cout<<"matrix value"<< ix->get_value()<<endl;
      ++it;
    }
  return res;
}
CSparseMatrix CSparseMatrix::operator+( CSparseMatrix &A)
{
  if(A.Rows != this->Rows) throw -1;
  CSparseMatrix C(*this);
  double v=0;
  vector<Trituple>::iterator ixA = A.smArray.begin();
  vector<Trituple>::iterator ixB = this->smArray.begin();
  unsigned int rA = ixA->row;
  unsigned int rB = ixB->row;
  //  unsigned
  while(ixA != A.smArray.end() && ixB != this->smArray.end())
    {
      if(ixA->row == ixB->row && ixA->col == ixB->col)
	{
	  v = ixA->Value + ixB->Value;
	  C.insert_data(ixA->row,ixA->col,v);
	  ++ixA;
	  ++ixB;
	  continue;
	}

      if(ixA->row == ixB->row)
	if(ixA->col > ixB->col)
          {
            C.insert_data(ixB->row,ixB->col,ixB->Value);
            ++ixB;
          }
	else
          {
            C.insert_data(ixA->row,ixA->col,ixB->Value);
            ++ixA;
          }
      if(ixA->row > ixB->row)
        {
          C.insert_data(ixB->row,ixB->col,ixB->Value);
          ++ixB;
        }
      if(ixA->row < ixB->row)
        {
          C.insert_data(ixA->row,ixA->col,ixA->Value);
          ++ixA;
        }
    }
  return C;
}
CSparseMatrix CSparseMatrix::Transpose() /* ÏµÊý¾ØÕó×ªÖÃ */
{
  int* rowSize = new int[Cols];    // ¸¨ÖúÊý×é£¬Í³¼Æ¸÷ÁÐ·ÇÁãÔªËØ¸öÊý
  int* rowStart = new int[Cols];   // ¸¨ÖúÊý×é£¬Í³¼Æ×ªÖÃºó¸÷ÐÐ´æ·ÅÎ»ÖÃ

  CSparseMatrix b(Cols,Rows);      // ´æ·Å×ªÖÃ½á¹û
  b.Rows = Cols;  b.Cols = Rows;  b.Terms = Terms;
  b.smArray.resize(Terms);

  if (Terms > 0)
    {
      for (int i = 0;i < Cols;i ++)
	{
	  rowSize[i] = 0;
	}
      for (int i = 0;i < Terms;i ++)
	{
	  rowSize[smArray[i].col]++;
	}
      rowStart[0] = 0;
      for (int i = 1;i < Cols;i ++)
	{
	  rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	}
      for (int i = 0;i < Terms;i ++)
	{
	  int j = rowStart[smArray[i].col];
	  b.smArray[j].row = smArray[i].col;
	  b.smArray[j].col = smArray[i].row;
	  b.smArray[j].Value = smArray[i].Value;
	  rowStart[smArray[i].col]++;
	}
    }
  delete[] rowSize;
  delete[] rowStart;
  return b;
}
CSparseMatrix CSparseMatrix::Transpose2()
{
  CSparseMatrix B = *this;

  int temp=0;
  for(vector<Trituple>::iterator it = B.smArray.begin();it != B.smArray.end();++it)
    {
      temp = it->row;
      it->row = it->col;
      it->col = temp;
    }
  //  cout<<"berofe sort"<<endl;
  B.sort();
  //  cout<<"after sort"<<endl;
  return B;
}
bool CSparseMatrix::sort()
{
  //cout<<"begin sort"<<endl;
  vector<Trituple>::iterator it = this->smArray.begin();//it != this->smArray.end();++it)
  int mark = 0;
  Trituple temp = *it;
  for(vector<Trituple>::size_type ix = 0 ;ix != this->smArray.size() ;++ix)
    {
      if (temp.after(*it))
	{
	  temp = *it;
	  break;
	}
      ++it;
    }
  //cout<<"print first"<<endl;
  //  temp.print();
  it = this->smArray.begin();
  for(vector<Trituple>::size_type ix = 1; ix != this->smArray.size();++ix)
    {
      vector<Trituple>::size_type j = ix;
      temp = *(it+ix);
      //cout<<"temp:"<<endl;
      //      temp.print();
      //cout<<"it+j"<<endl;
      //      (it+j)->print();
      while(temp.befor(*(it+j-1)))
	{
          //  temp.print();
          //cout<<"before"<<endl;
          //          (it+j)->print();
	  *(it+j) = *(it+j-1);
	  --j;
	}
	*(it+j) = temp;
	//      ++it;
        //cout<<"thie"<<ix <<"th sort"<<endl;
        //    this->matrixPrint();
    }
  this->calRowStart();
  return 0;
}
bool CSparseMatrix::smCat( CSparseMatrix& sm )
{
  int oldRows = Rows;
  Rows  += sm.Rows;
  Terms += sm.Terms;

  // Ä¿Ç°Çé¿öÏÂ£¬Ä¬ÈÏÁ½¸öÏ¡Êè¾ØÕóµÄÁÐÊýÊÇÏàÍ¬µÄ
  // Èç¹û²»ÏàÍ¬Ôò²»½øÐÐ¾ØÕóµÄ¿½±´
  /*if ( Cols != sm.Cols )
    {
    return false;
    }*/

  int sm_terms = sm.Terms;
  for ( int i = 0;i < sm_terms;i ++ )
    {
      sm.smArray.at( i ).row += oldRows;
      smArray.push_back( sm.smArray.at( i ) );
    }

  return true;
}

bool CSparseMatrix::calRowStart()
{
  int rs = 0;
  //  int cs = 0;
  int rstart=0;
  //const unsigned int num = this->Rows;
  bitset<100000> Rlist;
  vector<Mypair> temp;
  this->rowStart.swap(temp);
  //  bitset<num> Clist;
  for(vector<Trituple>::iterator ix=this->smArray.begin();ix != this->smArray.end();++ix)
    {
      int r = ix->row;
      //      int c = ix->col;
      //cout<<"ix-row"<< r <<endl;
      if (Rlist[r] == 0)
	{
          //cout<<"rlist r" <<Rlist[r] <<endl;
	  Mypair pr(r,rstart);
	  Rlist[r]=1;
	  this->rowStart.push_back(pr);
	  rs++;
	}
      /*
      if (Clist[c] == 0)
	{
	  Clist[c] = 1;
	  cs++;
	  }*/
      rstart++;
    }
  
  //  this->Rows = rs;
  //  this->Cols = cs;
  return 0;
  }
double CSparseMatrix::get_value(const int i,const int j)     //ÓÃ¶þ·Ö²éÕÒÖØÐ´Õâ¸öº¯Êý
{
  /*
  int start;
  bool ok=0;
  for(vector<Mypair>::iterator ix = this->rowStart.begin(); ix != this->rowStart.end();++ix)
    {
      if(ix->rowNum() == i)
	{
	  start = ix->startNum();
	  ok = 1;
	}
    }
  if(ok ==0) return 0;
  vector<Trituple>::iterator it = this->smArray.begin()+start;
  while(1)
    {
      if(it->col == j )
	return it->Value;
      ++it;
      if(it->row !=i)
	return 0;
        }*/
  //  return 0;
  vector<Trituple>::iterator first = this->smArray.begin();
  vector<Trituple>::iterator last = this->smArray.end()-1;
  vector<Trituple>::iterator  mid = last;
  unsigned int length;
  //cout<<"begin while"<<endl;
  while(mid != first)
    {
      //cout<<"mid:"<<mid->row <<","<< mid->col <<","<<mid->Value<<endl;
      //cout<<"first:"<<first->row <<","<< first->col <<","<<first->Value<<endl;
      //cout<<"last:"<<last->row <<","<< last->col <<","<<last->Value<<endl;
      length = (last - first)/2;
      //cout<<"last-last/2:"<<length<<endl;
      if(mid->addr_same(i,j)) return mid->Value;
      if(mid->after(i,j))
        {
          //cout<<"mid->after i j"<<endl;
          last = mid;
        }else
        if(mid->befor(i,j))
        {
          //cout<<"mid before ij"<<endl;
          //cout<<"mid:"<<mid->row <<","<< mid->col <<","<<mid->Value<<endl;
          //cout<<"first:"<<first->row <<","<< first->col <<","<<first->Value<<endl;
          //cout<<"last:"<<last->row <<","<< last->col <<","<<last->Value<<endl;
          first = mid;
        }
      mid = first + length;
    }
  if(first->addr_same(i,j))
    {
      return first->Value;
    }
  if(last->addr_same(i,j))
    return last->Value;
  return 0;
     
}
//double cal(const CSparseMatrix *A,const CSparseMatrix *B,const unsigned int i,const unsigned int j);
CSparseMatrix CSparseMatrix::operator*( CSparseMatrix &A)
 {
   // if(A.get_cols() != this->get_rows()) throw -1;
   CSparseMatrix B,C;
   if(A.Cols != this->Rows) throw -1;
   //cout<<"begin multiply"<<endl;
   B = A.Transpose2();
   cout<<"transp A "<<endl;
   B.matrixPrint();
   this->matrixPrint();
   //cout<<"transpose2"<<endl;
   vector<unsigned int> rowA;
   vector<unsigned int> rowB;
   unsigned int i=0;
   unsigned int j=0;
   double v = 0;
   for(vector<Mypair>::iterator ixA = this->rowStart.begin();ixA != this->rowStart.end(); ++ixA)
     {
       i = ixA->rowNum();
       for(vector<Mypair>::iterator ixB = B.rowStart.begin();ixB != B.rowStart.end(); ++ixB)
	 {
	   j = ixB->rowNum();
           //cout<<"calculate the i j value"<<endl;
	   v = this->cal(this,&B,i,j);////////////¼ÆËãÃ¿¾ØÕóÒ»¸öÔªËØÖµ
           //cout<<"begin insert data"<<endl;
	   C.insert_data(i,j,v);
	 }
     }
   return C;
   
 }

/*
 bool tell(bitset<MAX_LINE> * bitA, bitset<MAX_LINE>* bitB,vector<unsigned int> *ij)
 {
   bitset<MAX_LINE> temp1 = *bitA;
   bitset<MAX_LINE> temp2 ;
   int i = 0;
   int j = 0;
   site_t count = 0;
   vector<site_t> loc;
   while(temp.any())
     {
       temp2 = temp1;
       temp2 &=bitB;
       //       count = temp2.count();
       find(temp2,loc);
       temp >>=1;
     }
   while(temp.any())
     temp<<(1);
     }*/
 /*
 size_t find(bitset<MAX_LINE> * bitA,vector<site_t> * loc)
 {
 
   
   for(size_t i = 0; i != bitA->count; ++i)
     {
       if(*bitA[i] == 1)
	 loc->push_back(i);
     }
   
 }
*/
 unsigned int CSparseMatrix::find(const unsigned int i)
 {
   
   vector<Mypair>::iterator first = this->rowStart.begin();
   //   cout<<"first:"<<first->startNum()<<endl;
   vector<Mypair>::iterator last = this->rowStart.end()-1;
   vector<Mypair>::size_type mark;
   vector<Mypair>::iterator here = last;
   while(last - first > 1)
     {
       mark  = (last - first)/2;
       here = first +mark;
       /*       cout<<"first:"<<first - this->rowStart.begin()<<endl;
       cout<<"last:"<<last - this->rowStart.begin()<<endl;
       cout<<"here:"<<here - this->rowStart.begin()<<endl;*/
       if( here->rowNum() == i)
	 return here->startNum();
       if( here->rowNum() > i)
	 last = here;
       else
         if( here->rowNum() < i)
           first = here;
       /*       cout<<"first:"<<first - this->rowStart.begin()<<endl;
       cout<<"last:"<<last - this->rowStart.begin()<<endl;
       cout<<"here:"<<here - this->rowStart.begin()<<endl;*/
     }
   if(first->rowNum() == i)
       return first->startNum();
   if(last->rowNum() == i)
     return last->startNum();
   return last->startNum();
 }
bool CSparseMatrix::set_rowcol(unsigned int r,unsigned int c)
{
  this->Rows = r;
  this->Cols = c;
}
double CSparseMatrix::cal(CSparseMatrix *A,CSparseMatrix *B,const unsigned int i,const unsigned int j)
 {
   /*
     i:矩阵A中第i行
     j:矩阵B中第j行
     返回值:矩阵A第i行和矩阵B第j行的内积
    */
   /*for(unsigned int locA = A->rowStart.find(i);(locA != A->Terms)&&(locA != A->rowStart.find(i+1));++locA)
     for(unsigned int locB = B->rowStart.find(j);(locB != B->Terms)&&(locB != B->rowStart.find(i+1));++locB);++locB)
   {
     
   }*/
   cout<<"i:"<<i<<endl;
   cout<<"j:"<<j<<endl;
   unsigned int locA = A->find(i);
   unsigned int locB = B->find(j);
   unsigned int len ;
   vector<Trituple>::iterator ixA = A->smArray.begin()+ locA;
   vector<Trituple>::iterator ixB = B->smArray.begin()+ locB;
   double res = 0;
   unsigned int p;
   p = locA <= locB? locA:locB;
   cout<<"p:"<<p<<endl;

   //cout<<"locA:"<<locA<<endl;
   //cout<<"locB:"<<locB<<endl;
   vector<Trituple>::iterator lastA = A->smArray.end()-1;
   vector<Trituple>::iterator lastB = B->smArray.end()-1;
   cout<<"find(i+1):"<<A->find(i+1)<<endl;
   cout<<"find(j+1):"<<A->find(j+1)<<endl;
   //   while(p <= A->smArray.size()   && p <= B->smArray.size()   && p != A->find(i+1) && p != B->find(j+1))
   do{
     if(ixA->get_row() != i || ixB->get_row() != j                                                                                                                                                                                                                                                                                                                                   )
       break;
       /*
       cout<<"i:"<<i<<"\tj:"<<j<<endl;
       cout<<"matrix A here:"<<ixA - A->smArray.begin()<<endl;
       cout<<"matrix B here:"<<ixB - B->smArray.begin()<<endl;
       cout<<"A->find(i)"<<A->find(i)<<endl;
       cout<<"B->find(j)"<<B->find(j)<<endl;
       cout<<"A->find(i+1)"<<A->find(i+1)<<endl;
       cout<<"B->find(j+1)"<<B->find(j+1)<<endl;*/
     if(ixA->get_col() == ixB->get_col()  )
	 {
           cout<<"ixA->row:"<<ixA->get_row()<<"\tixA->col:"<<ixA->get_col()<<endl;
           cout<<"ixB->row:"<<ixB->get_row()<<"\tixB->col:"<<ixB->get_col()<<endl;
           cout<<"p:"<<p<<endl;
	   res += ixA->get_value() * ixB->get_value();
           cout<<"res:"<<res<<endl;
	   ++ixA;
	   ++ixB;
	   ++p;
	   continue;
	 }
     //       cout<<"ixA-col:"<<ixA->get_col()<< "\t"<<"ixB-col:"<<ixB->get_col()<<endl;
       cout<<"ixA->row:"<<ixA->get_row()<<"\tixA->col:"<<ixA->get_col()<<endl;
       cout<<"ixB->row:"<<ixB->get_row()<<"\tixB->col:"<<ixB->get_col()<<endl;
       cout<<"p:"<<p<<endl;
       if(ixA->get_col() < ixB->get_col())
	 ++ixA;
       if(ixB->get_col() > ixB->get_col())
	 ++ixB;
       ++p;
       //cout<<"p:"<<p<<endl;
   }while( p > A->smArray.size() || p > B->smArray.size() || p == A->find(i+1) || p == B->find(j+1));
 
     //cout<<"res "<<endl;
   return res;
 }
bool CSparseMatrix::matrixPrint()
{
  for(vector<Trituple>::iterator it = this->smArray.begin();it != this->smArray.end();++it)
    cout<<"("<< it->row << "," << it->col << "," << it->Value<<")"<<endl;
  for(vector<Mypair>::iterator ix = this->rowStart.begin() ; ix != this->rowStart.end() ; ++ix)
    cout<<"the "<< ix->rn <<"row begin from "<< ix->start <<endl;
}
