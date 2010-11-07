// LSCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "LSCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSCDlg dialog

CLSCDlg::CLSCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLSCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLSCDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLSCDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLSCDlg, CDialog)
	//{{AFX_MSG_MAP(CLSCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OPEN_DLG,OnOpenDlg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSCDlg message handlers

BOOL CLSCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	this->GetWindowRect(&m_IniRect);
	m_FileSettingDlg.Create(IDD_DIALOG_FILE_SETTING,this);
	m_FileSettingDlg.ShowWindow(SW_SHOW);
	this->SetWindowText("File Setting");

	m_DataCollectionDlg.Create(IDD_DIALOG_DATA_COLLECTION,this);
	m_DataCollectionDlg.ShowWindow(SW_HIDE);
	m_AWSFactorDlg.Create(IDD_DIALOG_AWS_FACTOR,this);
	m_AWSFactorDlg.ShowWindow(SW_HIDE);
	m_AWSFactorSttingDlg.Create(IDD_DIALOG_AWS_FACTOR_SETTING,this);
	m_AWSFactorSttingDlg.ShowWindow(SW_HIDE);
	m_SpectrumDlg.Create(IDD_DIALOG_SPECTRUM,this);
	m_SpectrumDlg.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLSCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLSCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CLSCDlg::PreTranslateMessage(MSG* pMsg) 
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


void CLSCDlg::OnOpenDlg(WPARAM wParam, LPARAM lParam)
{
	m_FileSettingDlg.ShowWindow(SW_HIDE);
	m_DataCollectionDlg.ShowWindow(SW_HIDE);
	m_AWSFactorDlg.ShowWindow(SW_HIDE);
	m_AWSFactorSttingDlg.ShowWindow(SW_HIDE);
	m_SpectrumDlg.ShowWindow(SW_HIDE);
	CRect rect;
	switch (wParam)
	{
		case OPEN_FILE_SETTING:
			m_FileSettingDlg.ShowWindow(SW_SHOW);
			this->SetWindowText("File Setting");
			m_FileSettingDlg.GetClientRect(&rect);
			break;
		case OPEN_DATA_COLLECTION:
			m_DataCollectionDlg.ShowWindow(SW_SHOW);
			this->SetWindowText("Data Collection");
			m_DataCollectionDlg.GetClientRect(&rect);
			break;
		case OPEN_AWS_FACTOR:
			m_AWSFactorDlg.ShowWindow(SW_SHOW);
			this->SetWindowText("AWS Factor");
			m_AWSFactorDlg.GetClientRect(&rect);
			break;
		case OPEN_AWS_FACTOR_SETTING:
			m_AWSFactorSttingDlg.ShowWindow(SW_SHOW);
			this->SetWindowText("AWS Factor Stting");
			m_AWSFactorSttingDlg.GetClientRect(&rect);
			break;
		case OPEN_SPECTRUM:
			m_SpectrumDlg.ShowWindow(SW_SHOW);
			this->SetWindowText("Spectrum");
			m_SpectrumDlg.GetClientRect(&rect);
			break;
		default:
			break;
	}
	CRect rc,rc2;
	this->GetWindowRect(&rc);
	this->GetClientRect(&rc2);

	rc.bottom = rc.top + rect.bottom + (rc.Height() - rc2.Height());
	rc.right = rc.left + rect.right + (rc.Width() - rc2.Width());
	MoveWindow(&rc);
}
