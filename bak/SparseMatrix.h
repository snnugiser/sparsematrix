#pragma once
#include <vector>

// ϵ������Ĵ洢

class Trituple;  // ��ǰ����
class CSparseMatrix
{
public:
	~CSparseMatrix(void);
	CSparseMatrix( int maxrow = 0,int maxcol = 0,int maxterm = 0 );
	CSparseMatrix Transpose();  // ϵ������ת��

	// ����ϡ���������ӣ����ڶ���ϡ������е���������ȫ����������һ��ϡ�������
	bool smCat( CSparseMatrix& sm );

public:
	int Rows,Cols,Terms;   // ϵ��������������ͷ���Ԫ�صĸ���
	std::vector<Trituple> smArray;  // ����Ԫ���ŵķ���Ԫ��	
};

class Trituple   // ��Ԫ��
{
	friend class CSparseMatrix;  // ��Ԫ��
public:
	int row,col;
	double Value;
};


