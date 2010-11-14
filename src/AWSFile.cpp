// AWSFile.cpp: implementation of the CAWSFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "AWSFile.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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
		set.dA_DPM = atof(buf);
	else return false;

	if (conf.ReadKey("B_DPM",buf,1024))
		set.dB_DPM = atof(buf);
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
	strLine.Format("A_DPM=%G\nB_DPM=%G\n",
		set.dA_DPM,set.dB_DPM);
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
