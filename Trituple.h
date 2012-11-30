#ifndef TRITUPLE_H
#define TRITUPLE_H
#include<iostream>
#include<vector>
using namespace std;
class Trituple   // ÈýÔª×é
{
  friend class CSparseMatrix;  // ÓÑÔªÀà
 public:
  Trituple(void);
  Trituple(const unsigned int r , const unsigned int c , const   double v);
  inline bool print(){cout<<"("<< this->row<<","<< this->col<<","<< this->Value<<")" <<endl;};
  inline bool operator== ( const Trituple & t1)
  {
    return ((t1.row == this->row)&&(t1.col == this->col)&&(t1.Value == this->Value));
  }
  inline bool operator!= (const Trituple & t1)
  {
    return !(*this == t1);
  }
  inline bool addr_same(unsigned int i,unsigned int j)
  {
    return (i == this->row) && (j == this->col);
  }
  inline bool addr_same (const Trituple &t)              //ÅÐ¶ÏÈýÔª×éÔÚ¾ØÕóÖÐÎ»ÖÃÊÇ·ñÏàÍ¬
  {
    return (t.row == this->row) && (t.col == this->col);
  }
  inline bool after(unsigned int i,unsigned int j)
  {
    return (this->row > i) || ((this->row == i ) && (this->col > j));
  }
  inline bool after(const Trituple & t)
  {
    return (this->row > t.row) ||  ( ( this->row == t.row ) && ( this->col > t.col));
  }
  inline bool befor(unsigned int i,unsigned int j)
  {
    return (this->row < i) || ((this->row == i) && (this->col < j));
  }
  inline bool befor(const Trituple & t)
  {
    return (this->row < t.row) || ((this->row == t.row )&&( this->col < t.col) );
  }
  inline double get_value(){return this->Value;}
  bool set_value3(const unsigned int r,const unsigned int c,const double v);
  bool set_value(const double v);
  inline unsigned int get_row(){return this->row;};
  inline  unsigned int get_col(){return this->col;};
  //  inline double get_value(){return this->Value;};
 private:
  unsigned   int row;
  unsigned  int col;
  double Value;
  
};

#endif
