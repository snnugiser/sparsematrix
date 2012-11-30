//#include "StdAfx.h"
#include "HybridR.h"
#include "Function.h"
//#include "Const.h"
//#include <cmath>
#include <iostream>
#include <fstream>
#include "Matrix.h"

//using namespace std;
CHybridR::CHybridR(void)
{

}
CHybridR::~CHybridR(void)
{

}

void CHybridR::HRegula( const double* Tec,const CSparseMatrix& A, 
				  const std::vector<double>& Ne,std::vector<double>& NeNew)
{
	int totalGrid = A.Cols;
	int RayNo=A.Rows;
	int cnt=0;//��������
	int itol=30;

	std::vector<double> NeTemp(totalGrid);


	int Nx,Ny,Nz;//�ֱ��Ǿ��ȡ�γ�ȡ��߶ȷ����������
	Nx=21;Ny=21;Nz=19;
	int NN,dline,dcol1,dxcol2,dycol2,dzcol2;
	double alpha;//TV���򻯲���
	double beta; //Tihkonov���򻯲���
	alpha=0.01;beta=0.005;
	
	///////////////////////////////TV���򻯱���
	NN=(Nx-1)*(Ny-1)*(Nz-1);
	//matrix Dx(NN,totalGrid);//��̬������һ��double�;��󣬲���ÿһ��Ԫ�س�ʼ��Ϊ0
	//matrix Dy(NN,totalGrid);
	//matrix Dz(NN,totalGrid);
	//matrix DPsi(NN,NN);
	double NN1=0,NN2=0,NN3=0;

	///////////////////////////////Tihkonov���򻯱���	
	//matrix L2(totalGrid-2,totalGrid);


	//////////////////////////////////////////////////////
    //������ת��Ϊ����
	///////////////////////////////////////////////////
	//matrix XX1(totalGrid,1); //�����ܶ�
	//matrix YY(RayNo,1);  //TEC
	//matrix AA(RayNo,totalGrid);//ϵ������A
	/*for (int i=1; i<=totalGrid; i++)
	{
		XX1(i,1)=Ne[i-1];
	}*/

	/*for (int i=1; i<=RayNo; i++)
	{
		YY(i,1)=Tec[i-1];
	}

	for (int i=0; i<A.Terms; i++)
	{
		AA(A.smArray[i].row+1,A.smArray[i].col+1)=A.smArray[i].Value;
	}*/
    //////////////////////////////////////////////////
	//matrix Pxtemp;
	vector Pxtemp(totalGrid);
	
	for (int i=1; i<=totalGrid; i++)
	{
		Pxtemp[i]=Ne[i-1];
	}

	double err=0;
	double sum=0;
	double avererr=0;

	do 
	{
		cnt++;
		matrix alphaMu,betaLL,AM;
		vector MM,Gamma,Phi;
		vector XX(totalGrid);
		XX=Pxtemp;

		//////////////////////////////////////////////alpha*TV(x) ������
		matrix Dx(NN,totalGrid);//��̬������һ��double�;��󣬲���ÿһ��Ԫ�س�ʼ��Ϊ0
		matrix Dy(NN,totalGrid);
		matrix Dz(NN,totalGrid);
		matrix DPsi(NN,NN);
		for (int k=2;k<=Nz;k++)
		{
			for (int j=2;j<=Ny;j++)
			{
				for (int i=2;i<=Nx;i++)
				{

					dline=(i-1)*(j-1)*(k-1);
					dcol1=(k-1)*Nx*Ny+(j-1)*Nx+i;
					dxcol2=(k-1)*Nx*Ny+(j-1)*Nx+i-1;
					dycol2=(k-1)*Nx*Ny+(j-2)*Nx+i;
					dzcol2=(k-2)*Nx*Ny+(j-1)*Nx+i;

					Dx(dline,dcol1)=1; Dx(dline,dxcol2)=-1;
					Dy(dline,dcol1)=1; Dy(dline,dycol2)=-1;
					Dz(dline,dcol1)=1; Dz(dline,dzcol2)=-1;

					NN1=XX[dcol1]-XX[dxcol2];
					NN2=XX[dcol1]-XX[dycol2];
					NN3=XX[dcol1]-XX[dzcol2];
					DPsi(dline,dline)=1/sqrt(pow(NN1,2)+pow(NN2,2)+pow(NN3,2)+1e-008);

				}
			}
		}
		matrix Mu,Mu1,Mux,Muy,Muz,Dxtemp,Dytemp,Dztemp;//���嶯̬���� ʵ��Mx=Dx'dia()Dx+Dy'dia()Dy+Dz'dia()Dz
		Dxtemp.Mult(Dx,DPsi,1,0); 
		Dytemp.Mult(Dy,DPsi,1,0); 
		Dztemp.Mult(Dz,DPsi,1,0);
		Mux.Mult(Dxtemp,Dx);      Muy.Mult(Dytemp,Dy);      Muz.Mult(Dztemp,Dz);
		Mu1.Plus(Mux,Muy);
		Mu.Plus(Mu1,Muz);// Mx
		alphaMu.Mult(Mu,alpha);//alphaMu=alpha*Mx

		vector Muxx;
		Muxx.Mult(Mu,XX);
		MM.Mult(Muxx,alpha);// MM=alpha*Mx*X

		Dx.Destroy();
		Dy.Destroy();
		Dz.Destroy();
		DPsi.Destroy();Mu.Destroy();Mu1.Destroy();Mux.Destroy();Muy.Destroy();Muz.Destroy();Dxtemp.Destroy();Dytemp.Destroy();Dztemp.Destroy();Muxx.Destroy();
		////////////////////////////////////////////////////////
		///////////////////////////////////////////////////beta*||Lx||2 ������
		matrix L2(totalGrid-2,totalGrid);
		for (int i=3;i<=totalGrid; i++)
		{
			
			L2(i-2,i-2)=1;
			L2(i-2,i-1)=-2;
			L2(i-2,i)=1;

		}
		matrix LL;
		vector LLx;
		LL.Mult(L2,L2,1,0);//L'L
		betaLL.Mult(LL,beta);//betaLL=beta*L'*L

		LLx.Mult(LL,XX);
		Gamma.Mult(LLx,beta);//Gamma=beta*L'L*X 

		L2.Destroy();LL.Destroy();LLx.Destroy();
		///////////////////////////////////////////////////////
		/////////////////////////////////////////////////A'Ax-A'y
		//matrix YY(RayNo,1);  //TEC
		vector YY(RayNo);
		matrix AA(RayNo,totalGrid);//ϵ������A
		for (int i=1; i<=RayNo; i++)
		{
			YY[i]=Tec[i-1];
		}

		for (int i=0; i<A.Terms; i++)
		{
			AA(A.smArray[i].row+1,A.smArray[i].col+1)=A.smArray[i].Value;
		}
		
		vector AMx,Ay;
		AM.Mult(AA,AA,1,0);//AM=A'*A
		AMx.Mult(AM,XX);
		Ay.Mult(AA.Turn(),YY);
		Phi.Sub(AMx,Ay);//Phi=A'Ax-A'y

		YY.Destroy();AA.Destroy();AMx.Destroy();Ay.Destroy();
		/////////////////////////////////////////////////////
		matrix GradH,GradH1,InvGradH;
		vector GradJ,GradJ1,CC;
		
		GradJ1.Plus(Phi,Gamma);
		GradJ.Plus(GradJ1,MM);//GradJ=Phi+MM+Gamma

		GradH1.Plus(AM,betaLL);
		GradH.Plus(GradH1,alphaMu);//GradH=AM+alphaMu+betaLL

		GradJ1.Destroy();GradH1.Destroy();Phi.Destroy();Gamma.Destroy();MM.Destroy();AM.Destroy();betaLL.Destroy();alphaMu.Destroy();
		bool how=InvGradH.Invers(GradH);
		if (!how)
		{
			std::cout<<"�˾��󲻿���"<<endl;
			return;
		}
		GradH.Destroy();

		////////////////////////////////////////////
		//XX-=CC.Mult(InvGradH,GradJ);
		CC.Mult(InvGradH,GradJ);
		Pxtemp.Sub(XX,CC);
		CC.Destroy();
		///////////////////////////////////////////
vv
		for (int i=1; i<=totalGrid; i++)
		{
			NeTemp[i-1]=XX[i];
			NeNew[i-1]=Pxtemp[i];
		}
		
	   //////////////////////////////////////////////////////////////////////////////////	

		// ����ǰ�����ε��������������ֵ���
		err = fabs(NeNew[0] - NeTemp[0]);
		for (int iii = 0;iii < totalGrid;iii ++)   
		{
			if (fabs(NeNew[iii] - NeTemp[iii]) > err)
			{
				err = fabs(NeNew[iii] - NeTemp[iii]);
			}
		}
		//����ƽ�����
				
		for (int ii = 0;ii < totalGrid;ii ++)
		{
			sum += fabs( NeNew[ii] - Ne[ii] );
		}
		avererr=sum/totalGrid;
		std::cout << cnt << ":" << err <<"ƽ����"<<avererr<< endl;	
	} while (err > 6e-003 && cnt < itol);

	std::cout << "����������" << cnt << " err:" << err << "avererr:"<<avererr<<endl;
	//���������
	double Mse=0,Msesum=0;
	for (int ii=0;ii<totalGrid;ii++)
	{
		Msesum+=(NeNew[ii] - NeTemp[ii])*(NeNew[ii] - NeTemp[ii]);
	}
	Mse=sqrt(Msesum/totalGrid);
	std::cout<<"����"<<Mse<<endl;
	std::cout<<"����������"<<cnt<<endl;


}
