// AWSFile.cpp: implementation of the CAWSFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "AWSFile.h"
#include "Config.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define   ABS(x)   (x)> 0?(x):-(x)
#define   SWAP(a,b)   {temp=(a);(a)=(b);(b)=temp;}

void   solve(double   **a,double   *b,double   *x,int   n)
{
	int   i,j,k,ik;
	double   mik,temp;
	for(k=0;k <n;k++)
	{
		mik=-1;
		for(i=k;i <n;i++)
			if(ABS(a[i][k])> mik)
			{
				mik=ABS(a[i][k]);
				ik=i;
			}
			for(j=k;j <n;j++)
				SWAP(a[ik][j],a[k][j]);
			SWAP(b[k],b[ik]);
			b[k]/=a[k][k];
			for(i=n-1;i>=k;i--)
				a[k][i]/=a[k][k];
			for(i=k+1;i<n;i++)
			{
				b[i]-=a[i][k]*b[k];
				for(j=n-1;j>=k;j--)
					a[i][j]-=a[i][k]*a[k][j];
			}
	}
	for(i=n-1;i>=0;i--)
	{
		x[i]=b[i];
		for(j=i+1;j <n;j++)
			x[i]-=a[i][j]*x[j];
	}
}

void   linear(double   **x,double   *y,double   *beta,int   n,int   p)
{
	double   **a,*b;
	int   i,j,k;
	
	a=new   double*[n];
	
	for(i=0;i <n;i++)
		a[i]=new   double[p];

	for(i=0;i <n;i++)
		for(j=0;j <p;j++)
		{
			a[i][j]=0;
			for(k=0;k <n;k++)
				a[i][j]+=x[k][i]*x[k][j];
		}
	
	b=new   double[p];
	for(i=0;i <p;i++)
	{
		b[i]=0;
		for(j=0;j <n;j++)
			b[i]+=x[j][i]*y[j];
	}
	solve(a,b,beta,p);

	delete b;
	for(i=0;i<n;i++) delete a[i];
	delete a;
}

void   polyfit(double   *x,double   *y,double   *beta,int   n,int   p)
{
	int   i,j;
	double   **xx;
	xx=new   double*[n];
	for(i=0;i <n;i++)
	{
		xx[i]=new   double[p];
		for(j=0;j <p;j++)
			xx[i][j]=pow(x[i],j);
	}
	linear(xx,y,beta,n,p);
	for(i=0;i<n;i++) delete xx[i];
	delete xx;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAWSFile::CAWSFile()
{

}

CAWSFile::~CAWSFile()
{

}

bool CAWSFile::ReadData(LPCTSTR szFile,AWS_Setting& set)
{
	Config conf(szFile);
	char buf[1024];
	if (conf.ReadKey("ACH_LL",buf,1024))
		set.nAch_LL = atoi(buf);
	else return false;

	if (conf.ReadKey("ACH_UL",buf,1024))
		set.nAch_UL = atoi(buf);
	else return false;

	if (conf.ReadKey("BCH_LL",buf,1024))
		set.nBch_LL = atoi(buf);
	else return false;

	if (conf.ReadKey("BCH_UL",buf,1024))
		set.nBch_UL = atoi(buf);
	else return false;

	if (conf.ReadKey("A_DPM",buf,1024))
		set.nA_DPM = atoi(buf);
	else return false;

	if (conf.ReadKey("B_DPM",buf,1024))
		set.nB_DPM = atoi(buf);
	else return false;

	CString strKey;
	for(int i=0;i<10;i++)
	{
		strKey.Format("A_RATIO_%d",i);
		if (conf.ReadKey(strKey,buf,1024))
			set.sample.dA_ratio[i] = atof(buf);
		else return false;

		strKey.Format("A_CPM_%d",i);
		if (conf.ReadKey(strKey,buf,1024))
			set.sample.dA_CPM[i] = atof(buf);
		else return false;

		strKey.Format("B_RATIO_%d",i);
		if (conf.ReadKey(strKey,buf,1024))
			set.sample.dB_ratio[i] = atof(buf);
		else return false;

		strKey.Format("B_CPM_%d",i);
		if (conf.ReadKey(strKey,buf,1024))
			set.sample.dB_CPM[i] = atof(buf);
		else return false;
	}

	return true;
}

bool CAWSFile::WriteFile(LPCTSTR szPath, AWS_Setting &set)
{
	FILE* file = fopen(szPath,"w");
	if (file==NULL) return false;

	CString strLine;

	strLine.Format("ACH_LL=%d\nACH_UL=%d\nBCH_LL=%d\nBCH_UL=%d\n",
		set.nAch_LL,set.nAch_UL,set.nBch_LL,set.nBch_UL);
	fputs((LPCTSTR)strLine,file);
	strLine.Format("A_DPM=%u\nB_DPM=%u\n",
		set.nA_DPM,set.nB_DPM);
	fputs((LPCTSTR)strLine,file);

	for(int i=0;i<10;i++)
	{
		strLine.Format("A_RATIO_%d=%G\nA_CPM_%d=%G\nB_RATIO_%d=%G\nB_CPM_%d=%G\n",
			i,set.sample.dA_ratio[i],
			i,set.sample.dA_CPM[i],
			i,set.sample.dB_ratio[i],
			i,set.sample.dB_CPM[i]);
		fputs((LPCTSTR)strLine,file);
	}

	fclose(file);
	return true;
}

bool CAWSFile::CalculateCoefficient(AWS_Setting &set, AWS_CalCo &co)
{
	for(int i=0;i<10;i++)
	{
		co.cal.dA_Eff[i] = set.sample.dA_CPM[i] / set.nA_DPM;
		co.cal.dB_Eff[i] = set.sample.dB_CPM[i] / set.nB_DPM;
		co.cal.dBA_CPM[i]= set.sample.dB_CPM[i]/set.sample.dA_CPM[i];
	}
	try
	{
		polyfit(set.sample.dA_ratio,co.cal.dA_Eff,co.dAch_co,10,4);
		polyfit(set.sample.dB_ratio,co.cal.dB_Eff,co.dBch_co,10,4);
		polyfit(set.sample.dA_ratio,co.cal.dBA_CPM,co.d_BA_co,10,4);
	}
	catch(...)
	{
		return false;
	}

	return true;
}
