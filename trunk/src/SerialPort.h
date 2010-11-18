// SerialPort.h: interface for the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALPORT_H__343ABFDB_E6D8_4FD9_8D16_E72B4D6E162C__INCLUDED_)
#define AFX_SERIALPORT_H__343ABFDB_E6D8_4FD9_8D16_E72B4D6E162C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSerialPort  
{
public:
	CSerialPort();
	virtual ~CSerialPort();
	int Open(const char* szDev);
	void Close();
	bool SetCom(void);
	virtual int Open(void) {return Open((LPCTSTR)strDevName);};
	virtual int Read(char* buf,int len);
	virtual int Write(const char* buf,int len);
	virtual void Lock(void);
	virtual void Unlock(void);
	virtual bool IsOpen() { return handle == (HANDLE)-1;};
	const char* GetPort(void) {return (LPCTSTR)strDevName;};
	virtual void SetTimeOut(int usec) {timeout= usec;};
	int m_BaudRate;
protected:
	HANDLE handle;
	int timeout;
	CString strDevName;
};

#endif // !defined(AFX_SERIALPORT_H__343ABFDB_E6D8_4FD9_8D16_E72B4D6E162C__INCLUDED_)
