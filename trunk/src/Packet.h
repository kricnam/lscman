// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__A288B744_8E7D_4BB6_AEEA_92E6690BAE5D__INCLUDED_)
#define AFX_PACKET_H__A288B744_8E7D_4BB6_AEEA_92E6690BAE5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct {
	char head;
	char type;
	char sp0;
	char Group[2+1+25+3+4+3+3+3+6+3+3+1+5+3+10+3+5+2];
	char endCR;
	char endLF;
	char tail;
} GroupCondition_Packet;

typedef struct {
	char head;
	char type;
	char sp0;
	char Title[9+3+9+3+9+3+1+3+13*(9+3)+9+2];
	char endCR;
	char endLF;
	char tail;
} DataTitle_Packet;

typedef struct {
	char MYNo[2];
	char sp0;
	char SN[3];
	char sp1;
	char RN[3];
	char sp2;
	char ESCR_SCCR[5];
	char sp3[2];
	char SP;
	char sp4[2];
	char TIME[8];
	char sp5;
	char A_GROSS[7];
	char sp6;
	char A_CPM[9];
	char sp7;
	char A_DPM[9];
	char sp8;
	char A_EFF[9];
	char sp9;
	char B_CROSS[7];
	char sp10;
	char B_CPM[9];
	char sp11;
	char B_DPM[9];
	char sp12;
	char B_EFF[9];
	char sp13;
	char C_GROSS[7];
	char sp14;
	char C_CPM[9];
	char sp15;
	char C_DPM[9];
	char sp16;
	char C_EFF[9];
	char sp17;
	char ESCR_SCCR[9];
	char sp18[2];
	char DATE[10];
	char sp19[3];
	char TIME[5];
	char sp20[3];
	char OPT1[9];
	char sp21[3];
	char OPT2[9];
	char sp22[1];
} CPMDPM_Field;

typedef struct {
	char head;
	char type;
	char sp0;
	CPMDPM_Field Data;
	char endCR;
	char endLF;
	char tail;
} CPMDPM_Data_Packet;

typedef struct
{
	char head;
	char type;
	char sp0;
	char No[3];
	char sp1;
	char Data[70];
	char endCR;
	char endLF;
	char tail;
} Spectrum_Packet;

class CPacket  
{
public:
	CPacket();
	virtual ~CPacket();

};

#endif // !defined(AFX_PACKET_H__A288B744_8E7D_4BB6_AEEA_92E6690BAE5D__INCLUDED_)
