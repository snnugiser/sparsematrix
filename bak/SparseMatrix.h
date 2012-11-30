#pragma once
#include <vector>

// 系数矩阵的存储

class Trituple;  // 超前声明
class CSparseMatrix
{
public:
	~CSparseMatrix(void);
	CSparseMatrix( int maxrow = 0,int maxcol = 0,int maxterm = 0 );
	CSparseMatrix Transpose();  // 系数矩阵转置

	// 两个稀疏矩阵的连接，将第二个稀疏矩阵中的所有内容全部拷贝到第一个稀疏矩阵中
	bool smCat( CSparseMatrix& sm );

public:
	int Rows,Cols,Terms;   // 系数矩阵的行列数和非零元素的个数
	std::vector<Trituple> smArray;  // 按三元组存放的非零元素	
};

class Trituple   // 三元组
{
	friend class CSparseMatrix;  // 友元类
public:
	int row,col;
	double Value;
};


