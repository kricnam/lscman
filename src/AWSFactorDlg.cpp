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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAWSFactorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAWSFactorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAWSFactorDlg, CDialog)
	//{{AFX_MSG_MAP(CAWSFactorDlg)
	ON_BN_CLICKED(IDC_BUTTON_SPECTRUM, OnButtonSpectrum)
	ON_WM_DESTROY()
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
	
	// TODO: Add extra initialization here
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
   
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_AWS_FACTOR_SETTING,0);
	
    return 0;     
}

void CAWSFactorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	UnregisterHotKey(this->m_hWnd,0x2000);   
	
}
