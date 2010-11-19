// SerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "SerialPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialPort::CSerialPort()
{
	handle = INVALID_HANDLE_VALUE;
	timeout = 20000;
}

CSerialPort::~CSerialPort()
{
	if (handle != INVALID_HANDLE_VALUE)
		Close();
}

int CSerialPort::Open(const char* szDev)
{
	Close();

	if (strDevName != szDev)
		strDevName = szDev;

	handle = CreateFile(szDev,GENERIC_READ|GENERIC_WRITE,
		0,NULL,
		OPEN_EXISTING, 
		0, 
		NULL);
	if(handle ==INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	PurgeComm(handle,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	if (SetCom()) 	return 0;
	else
	{
		Close();
		return -1;
	}
}

bool CSerialPort::SetCom(void)
{
	if (handle == INVALID_HANDLE_VALUE)
		return false;

	DCB dcb;
	BOOL fSuccess = GetCommState(handle, &dcb);
	
	if (!fSuccess) {
		// Handle the error.
		CString strMsg;
		strMsg.Format("GetCommState failed with error %d.",GetLastError());
		AfxMessageBox(strMsg);
		return false;
    }
	
	switch(m_BaudRate)
	{
	case 4800:
		dcb.BaudRate = CBR_4800;
		break;
	case 9600:
		dcb.BaudRate = CBR_9600;
		break;
	case 19200:
		dcb.BaudRate = CBR_19200;
		break;
	default:
		dcb.BaudRate = CBR_9600;
	}
 
	dcb.ByteSize = 7;             // data size, xmit, and rcv
	dcb.Parity = EVENPARITY;        // no parity bit
	dcb.StopBits =TWOSTOPBITS;    // one stop bit
	
	fSuccess = SetCommState(handle, &dcb);
	
	if (!fSuccess) {
		// Handle the error.
		CString strMsg;
		strMsg.Format("SetCommState failed with error %d.\n", GetLastError());
		AfxMessageBox(strMsg);
		return false;
    }
	SetTimeOut(1000000);
	return true;
}

void CSerialPort::SetTimeOut(int usec)
{
	COMMTIMEOUTS co = {0};
	co.ReadIntervalTimeout = usec/1000;
	SetCommTimeouts(handle,&co);
}

void CSerialPort::Lock(void)
{
	//if (flock(handle, LOCK_EX) < 0)
	{
		//ERRTRACE();
	}
}

void CSerialPort::Close()
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		//tcflush(handle, TCIOFLUSH);
		CloseHandle(handle);
		handle = INVALID_HANDLE_VALUE;
	}
}

void CSerialPort::Unlock(void)
{
//	if (flock(handle, LOCK_UN) < 0)
//		ERRTRACE();
}

int CSerialPort::Read(char* buf, int len)
{
	if (len == 0)
		return 0;
	if (handle == INVALID_HANDLE_VALUE)
		Open((LPCTSTR)strDevName);
	unsigned long n;
	do
	{
		if (ReadFile(handle,buf,len,&n,NULL))
			return n;
		else
		{
			m_strErr.FormatMessage("Read");
			break;
		}
	}while(true);
	return 0;
}

int CSerialPort::Write(const char* buf, int len)
{
	if (len == 0)
		return 0;
	if (handle == INVALID_HANDLE_VALUE)
		Open((LPCTSTR)strDevName);

//	DUMP(buf,len);

	unsigned long n ;//write(handle, buf, len);
	if (WriteFile(handle,buf,len,&n,NULL))
		return n;
	else
	{
		m_strErr.FormatMessage("Write");
	}
	return 0;
}
