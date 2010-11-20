// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lsc.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacket::CPacket()
{

}

CPacket::~CPacket()
{

}

int CPacket::ReceiveFrame(CSerialPort &port)
{
	char c=0;
	strData.Empty();
	do
	{
		if (port.Read(&c,1)<0) 
			return -1;
		else
			return 0;
	}while(c != STX);

	strData+=c;
	CTime start = CTime::GetCurrentTime();
	CTime now;
	CTimeSpan pause;
	do
	{
		int n = port.Read(&c,1);
		if (n<0)
			return -1;
		else if (n)
		{
			start = CTime::GetCurrentTime();
			strData+=c;
		}
		now = CTime::GetCurrentTime();
		pause = now - start;
		if (pause.GetTotalSeconds() > 5)
		{
			strData.Empty();
			return 0;
		}
	}while(c!=ETX);

	return strData.GetLength();
}

int CPacket::SendData(CSerialPort &port)
{
	return port.Write(strData,strData.GetLength());
}

char CPacket::GetPacketType()
{
	if (strData.IsEmpty()) return 0;
	if (!IsValid()) return 0;
	return strData.GetAt(1);
}

bool CPacket::IsValid()
{
	if (strData.IsEmpty()) return false;
	int len = strData.GetLength();
	if (len == sizeof(CPMDPM_Data_Packet)
		|| len == sizeof(DataTitle_Packet)
		|| len == sizeof(GroupCondition_Packet)
		|| len == sizeof(Spectrum_Packet)
		|| len == sizeof(Command_Packet))
	{
		if(strData.GetAt(strData.GetLength()-2)==0x0A
			&& strData.GetAt(strData.GetLength()-3)==0x0D)
			return true;
	}
	return false;
}

void CPacket::SendAck(CSerialPort &port)
{
	strData.Empty();
	strData = ACK;
	port.Write(strData,1);
}

void CPacket::SendCmd(CSerialPort &port)
{
	strData.Empty();
	Command_Packet cmd;
	cmd.head = STX;
	cmd.type = TYPE_SPECTRUM;
	cmd.endCR = 0x0D;
	cmd.endLF = 0x0A;
	cmd.tail = ETX;
	port.Write((const char*)&cmd,4);
}

CString CPacket::GetData()
{
	CString str;
	if (IsValid())
	{
		str = strData.Mid(1,strData.GetLength()-2);
	}
	return str;
}
