// SerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "SerialPort.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define STX 0x02
#define ETX 0x03
#define ACK 0x06

void CSerialPort::DUMP(const char* szTitle,const char* szBuf,int nLen)
{
	FILE* logFile = fopen("./lsc_debug.log","a");
	if (logFile)
	{
		fprintf(logFile,"%u: %s\t",clock(),szTitle);
		for(int i=0;i < nLen ; i++)
		{
			char c = szBuf[i];
			switch(c)
			{
			case STX:
				c = '^';
				break;
			case ETX:
			case '\r':
			case '\n':
				c = '$';
				break;
				
			}
			fputc(c,logFile);
		}
		fputc(0x0A,logFile);
		fclose(logFile);
	}
	else
		AfxMessageBox("fail to open log file");

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialPort::CSerialPort()
{
	handle = INVALID_HANDLE_VALUE;
	memset(&m_dcb,0,sizeof(m_dcb));
	m_dcb.BaudRate = CBR_9600;
	m_dcb.ByteSize = 7;
	m_dcb.Parity = EVENPARITY;        // no parity bit
	m_dcb.StopBits =TWOSTOPBITS;    // one stop bit
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
		m_strErr.GetErrorMsg("Open");
		return -1;
	}

	PurgeComm(handle,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	if (SetCom()) 	return 0;
	else Close();
	return -1;
}

bool CSerialPort::SetCom(void)
{
	if (handle == INVALID_HANDLE_VALUE)
		return false;

	//Set buffer size
	if (!SetupComm(handle,2048,2048)) return false;

	//Set baud rate, etc.
	DCB dcb;
	BOOL fSuccess = GetCommState(handle, &dcb);
	
	if (!fSuccess) {
		// Handle the error.
		m_strErr.GetErrorMsg("SetCom");
		return false;
    }

	fSuccess = SetCommState(handle, &m_dcb);
	
	if (!fSuccess) {
		// Handle the error.
		m_strErr.GetErrorMsg("SetCom");
		return false;
    }
	
	SetTimeOut(1000000);
	return true;
}

void CSerialPort::SetTimeOut(int usec)
{
	COMMTIMEOUTS co = {0};
	co.ReadIntervalTimeout = 0;
	co.ReadTotalTimeoutConstant = usec/1000;
	co.ReadTotalTimeoutMultiplier = 10000 / ((m_dcb.BaudRate)?m_dcb.BaudRate:1);
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
		PurgeComm(handle,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
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
	{
		if (Open((LPCTSTR)strDevName)<0)
			return -1;
	}

	unsigned long n;
	do
	{
		if (ReadFile(handle,buf,len,&n,NULL))
		{
			if (n) DUMP("R>",buf,n);
			return n;
		}
		else
		{
			m_strErr.GetErrorMsg("Read");
			DUMP("RX", (LPCTSTR)m_strErr, m_strErr.GetLength());
			break;
		}
	}while(true);
	return -1;
}

int CSerialPort::Write(const char* buf, int len)
{
	if (len == 0)
		return 0;
	if (handle == INVALID_HANDLE_VALUE)
	{
		if (Open((LPCTSTR)strDevName)<0) return -1;
	}

	DUMP("W>",buf,len);
	unsigned long n ;//write(handle, buf, len);
	if (WriteFile(handle,buf,len,&n,NULL))
	{
		return n;
	}
	else
	{
		m_strErr.GetErrorMsg("Write");
		DUMP("WX", (LPCTSTR)m_strErr, m_strErr.GetLength());
	}
	return -1;
}
