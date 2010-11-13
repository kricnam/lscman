// DataFile.cpp: implementation of the CDataFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "DataFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataFile::CDataFile()
{
	fData = NULL;
	strFileName.Empty();
}

CDataFile::~CDataFile()
{

}


int CDataFile::GetSpectrumData(int *pArray, int len)
{
	if (fData==NULL) return 0;
	CString strLine;
	CString strField;
	int n=0;
	
	try
	{
		if (IsValidFile())
		{
			gotoSpetrumStart();
			while(!feof(fData))
			{
				readLine(strLine);
				while(strLine.GetLength())
				{
					if (chopFirstCSVField(strLine,strField))
					{
						pArray[n++] = atoi(LPCTSTR(strField));
					}
					
				};
			};
		}
		else
		{
			return 0;
		}
	}
	catch(...)
	{
		return n;
	}
	return n;
}

int CDataFile::Open(LPCTSTR szFileName)
{
	if (fData != NULL)
	{
		fclose(fData);
		fData = NULL;
	}
	strFileName = szFileName;
	return Open();
}

int CDataFile::Open()
{
	fData = fopen((LPCTSTR)strFileName,"r");
	if (fData == NULL)
	{
		perror((LPCTSTR)strFileName);
		return -1;
	}
	return 0;
}

bool CDataFile::IsValidFile()
{
	if (fData)
	{
		try
		{
			fseek(fData,0,SEEK_SET);
			char buf[1024];
			if (fgets(buf,1024,fData) &&
				fgets(buf,1024,fData))
			{
				if (strstr(buf,"MY NO")
					&& strstr(buf,"TIME")
					&& strstr(buf,"SCCR"))
				{
					if (fgets(buf,1024,fData)
						&& fgets(buf,1024,fData)
						&& !feof(fData))
						return true;
				}
			}
		}
		catch(...)
		{
			return false;
		}
	}
	return false;
}

bool CDataFile::gotoSpetrumStart()
{
	if (fData)
	{
		CString strLine;
		if (readLine(strLine)
			&&readLine(strLine))
			return true;
	}
	return false;
}

int CDataFile::readLine(CString &strLine)
{
	if (fData)
	{
		char buf[1024]={0};
		if (fgets(buf,1024,fData))
		{
			strLine = buf;
		}
	}
	return 0;
}

int CDataFile::chopFirstCSVField(CString& strLine,CString& strField)
{
	if (strLine.GetLength())
	{
		strField.Empty();
		int n=strLine.Find(',');
		if ( n < 0) 
		{
			return -1;
		}

		if (n > 0)
		{
			strField = strLine.Left(n);
		}

		strLine = strLine.Right(strLine.GetLength()-n-1);

		return n;
	}

	return 0;
}
