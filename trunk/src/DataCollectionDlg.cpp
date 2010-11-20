// DataCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "DataCollectionDlg.h"
#include "SerialPort.h"
#include "Packet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT CommThreadProc( LPVOID pParam )
{
	//Open Port;
	CDataCollectionDlg& UI=*(CDataCollectionDlg*)pParam;;
	CPacket packet;
	do
	{
		if (packet.ReceiveFrame(UI.m_port)>0)
		{
			if (!UI.m_port.IsOpen()) return 0;
			switch(packet.GetPacketType())
			{
				case TYPE_GROUP:
					packet.SendAck(UI.m_port);
				    packet.SendCmd(UI.m_port);
				    UI.SaveData(packet.GetData());
				    break;
				case TYPE_TITLE:
				case TYPE_DATA:
				case TYPE_SPECTRUM:
					UI.SaveData(packet.GetData());
					packet.SendAck(UI.m_port);
					break;
				default:
					if (packet.IsValid())
						packet.SendAck(UI.m_port);
			}
		}
	}while(UI.m_port.IsOpen());
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionDlg dialog


CDataCollectionDlg::CDataCollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataCollectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataCollectionDlg)
	m_strCurrentTime = _T("");
	m_strFileName = _T("");
	m_strStartTime = _T("");
	m_strStatus = _T("");
	m_strMYNo = _T("");
	//}}AFX_DATA_INIT
	pWorking = NULL;
}


void CDataCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataCollectionDlg)
	DDX_Control(pDX, IDC_EDIT_STATUS, m_EditStatus);
	DDX_Text(pDX, IDC_EDIT_CURRENT_TIME, m_strCurrentTime);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_START_TIME, m_strStartTime);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_STATIC_MYNO, m_strMYNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataCollectionDlg, CDialog)
	//{{AFX_MSG_MAP(CDataCollectionDlg)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SETTING, OnButtonFileSetting)
	ON_BN_CLICKED(IDC_BUTTON_AWS_FACTOR, OnButtonAwsFactor)
	ON_BN_CLICKED(IDC_BUTTON_SHUT_DOWN, OnButtonShutDown)
	ON_BN_CLICKED(IDC_BUTTON_SPECTRUM, OnButtonSpectrum)
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionDlg message handlers

BOOL CDataCollectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataCollectionDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
			break;
		case VK_ESCAPE:
			return TRUE;
			break;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDataCollectionDlg::OnButtonFileSetting() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_FILE_SETTING,0);
	
}

void CDataCollectionDlg::OnButtonAwsFactor() 
{

	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_AWS_FACTOR,0);
}

void CDataCollectionDlg::OnButtonShutDown() 
{
	if (MessageBox("Do you really want to quit?","Quit",MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
	
}

void CDataCollectionDlg::OnButtonSpectrum() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_SPECTRUM,0);
}

HBRUSH CDataCollectionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	int nID = pWnd->GetDlgCtrlID();
	if (nID == IDC_EDIT_STATUS)
	{
		if (m_strStatus == "Received")
		{
			pDC->SetBkColor(RGB(0,255,0));
		}
		else if (m_strStatus == "Send")
		{
			pDC->SetBkColor(RGB(255,0,0));
		}
		else
		{

		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDataCollectionDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow && !m_strDev.IsEmpty() && !pWorking)
	{
		m_port.m_dcb = m_dcb;
		if (m_port.Open(m_strDev)<0)
		{
			AfxMessageBox(m_port.m_strErr+" for "+m_strDev);
			return;
		}
		pWorking = AfxBeginThread(CommThreadProc,this);
	}

}

void CDataCollectionDlg::OnClose() 
{
	if (pWorking)
	{
		m_port.Close();
	}
	CDialog::OnClose();
}

void CDataCollectionDlg::SetStatus(CPacket &packet)
{

}

void CDataCollectionDlg::SaveData(CString &str)
{
	FILE* file=fopen(strCurrentFile,"w+");
	if(file==NULL) return;
	fprintf(file,"%s",(LPCTSTR)str);
	fclose(file);
}
