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
	if (handle > 0)
		Close();
}

int CSerialPort::Open(const char* szDev)
{
	Close();

	if (strDevName != szDev)
		strDevName = szDev;

	handle = CreateFile(szDev,GENERIC_READ|GENERIC_WRITE,
		0,NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);
	if(handle ==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Failed to open COM port");
		return -1;
	}

	SetCom();
	return 0;
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
	return true;
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
	if (handle > 0)
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
	if (handle == (HANDLE) -1)
		Open((LPCTSTR)strDevName);
	int try_again = 2;
	int n;
	do
	{
		//n = read(handle, buf, len);
		if (n > 0)
			return n;
		if (n == -1)
		{
			//ERRTRACE();
			Close();
			return 0;
		}
		if (try_again--)
		{
			//usleep(timeout);
			continue;
		}
	} while (try_again);
	return n;
}

int CSerialPort::Write(const char* buf, int len)
{
	if (len == 0)
		return 0;
	if (handle == (HANDLE)-1)
		Open((LPCTSTR)strDevName);

//	DUMP(buf,len);

	int n ;//write(handle, buf, len);
	//tcdrain(handle);
	if (n > 0)
		return n;
	if (n == -1)
	{
		//ERRTRACE();
		Close();
	}
	return 0;
}
