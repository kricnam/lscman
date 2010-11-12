// DataCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "DataCollectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
