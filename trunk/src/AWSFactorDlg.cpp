// AWSFactorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "AWSFactorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAWSFactorDlg dialog


CAWSFactorDlg::CAWSFactorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAWSFactorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAWSFactorDlg)
	//}}AFX_DATA_INIT
}


void CAWSFactorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAWSFactorDlg)
	DDX_Control(pDX, IDC_BUTTON_FILE_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_FILE_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAWSFactorDlg, CDialog)
	//{{AFX_MSG_MAP(CAWSFactorDlg)
	ON_BN_CLICKED(IDC_BUTTON_SPECTRUM, OnButtonSpectrum)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAWSFactorDlg message handlers

BOOL CAWSFactorDlg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CAWSFactorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	RegisterHotKey(this->m_hWnd, 0x2000, MOD_CONTROL | MOD_ALT, 'C');
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAWSFactorDlg::OnButtonSpectrum() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_SPECTRUM,0);
	
}

LONG CAWSFactorDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
   
	GetParent()->SetWindowText("AWS Factor Setting");
	m_btnSet.ShowWindow(TRUE);
	m_btnSave.ShowWindow(TRUE);
    return 0;     
}

void CAWSFactorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	UnregisterHotKey(this->m_hWnd,0x2000);   
	
}

void CAWSFactorDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	m_btnSet.ShowWindow(FALSE);
}

void CAWSFactorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (!bShow)
	{
		m_btnSet.ShowWindow(bShow);
		m_btnSave.ShowWindow(bShow);
	}
}
