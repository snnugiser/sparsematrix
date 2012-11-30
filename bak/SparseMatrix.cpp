#include "StdAfx.h"
#include "SparseMatrix.h"

CSparseMatrix::CSparseMatrix( int maxrow /*= 0*/,int maxcol /*= 0*/,int maxterm /*= 0*/ )
{
	Rows = maxrow;
	Cols = maxcol;
	Terms = maxterm;
}

CSparseMatrix::~CSparseMatrix(void)
{
}

CSparseMatrix CSparseMatrix::Transpose() /* ϵ������ת�� */
{
	int* rowSize = new int[Cols];    // �������飬ͳ�Ƹ��з���Ԫ�ظ���
	int* rowStart = new int[Cols];   // �������飬ͳ��ת�ú���д��λ��

	CSparseMatrix b(Cols,Rows);      // ���ת�ý��
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

bool CSparseMatrix::smCat( CSparseMatrix& sm )
{
	int oldRows = Rows;
	Rows  += sm.Rows;
	Terms += sm.Terms;

	// Ŀǰ����£�Ĭ������ϡ��������������ͬ��
	// �������ͬ�򲻽��о���Ŀ���
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