#ifndef PAIR_H
#define PAIR_H
class Mypair{
  friend class CSparseMatrix;
 private:
  unsigned int rn;
  unsigned int start;
 public:
  inline  unsigned int rowNum(){return this->rn;};
  inline  unsigned int startNum(){return this->start;};
  //  unsigned int find(unsigned int i);//���Ҿ����е�i�еĵ�ַ  note:i�ᳬ��
  Mypair(void);
  bool  setStart(unsigned int rn,unsigned int sn);
  Mypair(unsigned int rn,unsigned int sn);
  ~Mypair(void);
};
#endif
