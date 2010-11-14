// DataFile.h: interface for the CDataFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAFILE_H__3AF7DAD3_0CA6_4931_A8EB_991ED79F3EE1__INCLUDED_)
#define AFX_DATAFILE_H__3AF7DAD3_0CA6_4931_A8EB_991ED79F3EE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataFile  
{
public:
	void Close(void);
	int GetFieldValue(LPCTSTR szName,CString& strValue);
	int GetFieldIndex(LPCTSTR szName);
	bool IsValidFile(void);
	int Open(void);
	int Open(LPCTSTR szFileName);
	int GetSpectrumData(int* pArray,int len);
	
	CDataFile();
	virtual ~CDataFile();
protected:
	int chopFirstCSVField(CString& strLine,CString& strField);
	int readLine(CString& strLine);
	bool gotoSpetrumStart(void);
    CString strFileName;
	FILE* fData;
};

#endif // !defined(AFX_DATAFILE_H__3AF7DAD3_0CA6_4931_A8EB_991ED79F3EE1__INCLUDED_)
