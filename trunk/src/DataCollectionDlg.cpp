// DataCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "DataCollectionDlg.h"
#include "SerialPort.h"
#include "Packet.h"
#include "DataFile.h"
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
			//UI.SetStatus(packet);
			UI.PostMessage(WM_UPDATE_DATA,(WPARAM)&packet,NULL);
			if (!UI.m_port.IsOpen()) return 0;
			switch(packet.GetPacketType())
			{
				case TYPE_GROUP:
					packet.SendAck(UI.m_port);
					if (UI.NeedCollect(packet.GetMYNo()))
					{
						packet.SendCmd(UI.m_port);
						UI.SaveData(packet);
					}
				    break;
				case TYPE_TITLE:
				case TYPE_DATA:
				case TYPE_SPECTRUM:
					UI.SaveData(packet);
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
	m_strFileName = _T("");
	m_strMYNo = _T("");
	m_strStartTime = _T("");
	m_strStatus = _T("Unreceived");
	m_strCurrentTime = _T("");
	//}}AFX_DATA_INIT
	pWorking = NULL;
}


void CDataCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataCollectionDlg)
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_STATIC_MYNO, m_strMYNo);
	DDX_Text(pDX, IDC_STATIC_STARTTIME, m_strStartTime);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_STATIC_CURRENTTIME, m_strCurrentTime);
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
	ON_WM_TIMER()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPDATE_DATA,OnUpdateData)
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
	HBRUSH brush_green = ::CreateSolidBrush(RGB(0,255,0));
    LOGBRUSH log={0};
	int nID = pWnd->GetDlgCtrlID();
	if (nID == IDC_STATIC_STATUS)
	{
		if (m_strStatus == "Received")
		{
			pDC->SetBkColor(RGB(0,255,0));
			return brush_green;
		}
		else
		{
			::GetObject(hbr,sizeof(log),&log);
			pDC->SetBkColor(log.lbColor);
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

	if (bShow)
	{
		SetTimer(1,1000,0);
	}
	else
	{
		KillTimer(1);
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
	if (packet.GetPacketType() == TYPE_GROUP)
	{
		m_strMYNo = packet.GetMYNo();
		m_strStatus = "Received";
		m_strStartTime = packet.GetDate() + " " + packet.GetTime();
	}

	if (packet.GetPacketType() == TYPE_UNKNOW
		|| packet.GetPacketType() == TYPE_END)
	{
		m_strMYNo.Empty();
		m_strStatus = "Unreceived";
		m_strStartTime.Empty();
	}

	if (IsWindowVisible())	UpdateData(FALSE);

}

void CDataCollectionDlg::SaveData(CPacket& packet)
{
	CDataFile file;
	if (packet.GetPacketType() == TYPE_GROUP)
	{
		m_strMYNo = packet.GetMYNo();
		m_strFileName.Empty();
		for(int i=0;i<12;i++)
		{
			if (g_SetArray[i].m_strID == m_strMYNo &&
				g_SetArray[i].m_DataCollection)
			{
				m_strFileName = g_SetArray[i].m_strFileName+"."+
					g_SetArray[i].m_Extension;
				g_SetArray[i].m_Extension.Format("%.03d",
					atoi(g_SetArray[i].m_Extension));
				
				break;
			}
		}
		UpdateData(FALSE);
	}

	if (NeedCollect(m_strMYNo))
		file.Save(m_strCurrentFile,packet);
}

void CDataCollectionDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent = 1)
	{
		CTime now = CTime::GetCurrentTime();
		m_strCurrentTime = now.Format("%Y/%m/%d %H:%M:%S");
		UpdateData(FALSE);
	}
	
	CDialog::OnTimer(nIDEvent);
}

bool CDataCollectionDlg::NeedCollect(CString &strMYNo)
{
		for(int i=0;i<12;i++)
		{
			if (g_SetArray[i].m_strID == strMYNo)
			{
				return g_SetArray[i].m_DataCollection==TRUE;
			}
		}
		return false;
}

BOOL CDataCollectionDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

LRESULT CDataCollectionDlg::OnUpdateData(WPARAM wParam, LPARAM lParam)
{
	CPacket& packet=*(CPacket*)wParam;
	SetStatus(packet);
	return 0;
}