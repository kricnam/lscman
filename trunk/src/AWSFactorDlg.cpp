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
	m_ADPM = 0.0;
	m_nAchUL = 0;
	m_nAchLL = 0;
	m_BDPM = 0.0;
	m_nBchLL = 0;
	m_nBchUL = 0;
	m_dAcha = 0.0;
	m_bAchc = 0.0;
	m_dAchb = 0.0;
	m_dAchd = 0.0;
	m_dBA_a = 0.0;
	m_dBA_b = 0.0;
	m_dBA_d = 0.0;
	m_dBA_c = 0.0;
	m_dBch_a = 0.0;
	m_dBch_b = 0.0;
	m_dBch_c = 0.0;
	m_dBch_d = 0.0;
	//}}AFX_DATA_INIT
}


void CAWSFactorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAWSFactorDlg)
	DDX_Control(pDX, IDC_STATIC_ORG, m_stcOrg);
	DDX_Control(pDX, IDC_BUTTON_FILE_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_FILE_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Text(pDX, IDC_EDIT_ADPM, m_ADPM);
	DDX_Text(pDX, IDC_EDIT_AUL, m_nAchUL);
	DDX_Text(pDX, IDC_EDIT_ALL, m_nAchLL);
	DDX_Text(pDX, IDC_EDIT_BDPM, m_BDPM);
	DDX_Text(pDX, IDC_EDIT_BLL, m_nBchLL);
	DDX_Text(pDX, IDC_EDIT_BUL, m_nBchUL);
	DDX_Text(pDX, IDC_EDIT_ACHA, m_dAcha);
	DDX_Text(pDX, IDC_EDIT_ACHC, m_bAchc);
	DDX_Text(pDX, IDC_EDIT_ACHB, m_dAchb);
	DDX_Text(pDX, IDC_EDIT_ACHD, m_dAchd);
	DDX_Text(pDX, IDC_EDIT_BAA, m_dBA_a);
	DDX_Text(pDX, IDC_EDIT_BAB, m_dBA_b);
	DDX_Text(pDX, IDC_EDIT_BAD, m_dBA_d);
	DDX_Text(pDX, IDC_EDIT_BAC, m_dBA_c);
	DDX_Text(pDX, IDC_EDIT_BCHA, m_dBch_a);
	DDX_Text(pDX, IDC_EDIT_BCHB, m_dBch_b);
	DDX_Text(pDX, IDC_EDIT_BCHC, m_dBch_c);
	DDX_Text(pDX, IDC_EDIT_BCHD, m_dBch_d);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAWSFactorDlg, CDialog)
	//{{AFX_MSG_MAP(CAWSFactorDlg)
	ON_BN_CLICKED(IDC_BUTTON_SPECTRUM, OnButtonSpectrum)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_FILE_SAVE, OnButtonFileSave)
	ON_BN_CLICKED(IDC_BUTTON_FILE_OPEN, OnButtonFileOpen)
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
	CRect rect;
	m_stcOrg.GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	for(int j=0;j<10;j++)
	{
	  CRect rect0,rectL;
	  rect.OffsetRect(0,rect.Height()+2);
	  rect0 = rect;
	  CString strLabel;
	  strLabel.Format("SAMPLE-%d",j+1);
	  rectL = rect;
	  rectL.OffsetRect(-1*rect.Width()-4,0);
	  lbl[j].Create(strLabel,WS_CHILD|WS_VISIBLE|SS_RIGHT,rectL,this);
	  lbl[j].SetFont(m_stcOrg.GetFont());
	  ULONG style;
	  style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_RIGHT;
	  for(int i=0;i<7;i++)
	  {
		  editSample[j][i].Create(style,
		  rect0,this,IDC_EDIT_SAMPLE+j*10+i);
	      editSample[j][i].SetFont(m_stcOrg.GetFont());
		  rect0.OffsetRect(rect.Width()+1,0);
		  switch(i)
		  {
		  case 1:
			  rect0.OffsetRect(rect.Width()/2,0);
			  break;
		  case 3:
			  rect0.OffsetRect(rect.Width(),0);
			  style |= ES_READONLY;
			  break;
		  }

	  };
	}
	RegisterHotKey(this->m_hWnd, 0x2000, MOD_CONTROL | MOD_ALT, 'C');
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAWSFactorDlg::OnButtonSpectrum() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_SPECTRUM,0);
	UpdateData();
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



void CAWSFactorDlg::OnButtonFileSave() 
{
	CFileDialog dlg(FALSE,"awd",NULL,0,"AWS File(*.aws)|*.aws||",this->GetParent());
	if (dlg.DoModal()==IDOK)
	{
		CAWSFile awsFile;
		AWS_Setting set;
		GetSetting(set);
		awsFile.WriteFile(dlg.GetPathName(),set);
	}
}

void CAWSFactorDlg::GetSetting(AWS_Setting &set)
{
	UpdateData();
	set.nAch_LL = m_nAchLL;
	set.nAch_UL = m_nAchUL;
	set.nBch_LL = m_nBchLL;
	set.nBch_UL = m_nBchUL;
	set.dA_DPM = m_ADPM;
	set.dB_DPM = m_BDPM;

	CString strVal;
	for(int i=0;i<10;i++)
	{
		editSample[i][0].GetWindowText(strVal);
		set.sample.dA_ratio[i] = atof((LPCTSTR)strVal);
		editSample[i][1].GetWindowText(strVal);
		set.sample.dA_CPM[i] = atof((LPCTSTR)strVal);
		editSample[i][2].GetWindowText(strVal);
		set.sample.dB_ratio[i] = atof((LPCTSTR)strVal);
		editSample[i][3].GetWindowText(strVal);
		set.sample.dB_CPM[i] = atof((LPCTSTR)strVal);
	}
}

void CAWSFactorDlg::OnButtonFileOpen() 
{
	CFileDialog dlg(TRUE,"awd",NULL,0,"AWS File(*.aws)|*.aws||",this->GetParent());
	if (dlg.DoModal()==IDOK)
	{
		CAWSFile awsFile;
		AWS_Setting set;
		awsFile.ReadData(dlg.GetPathName(),set);
		LoadData(set);
	}
}

void CAWSFactorDlg::LoadData(AWS_Setting &set)
{
	
	m_nAchLL = set.nAch_LL ;
	m_nAchUL = 	set.nAch_UL;
	m_nBchLL = set.nBch_LL;
	m_nBchUL = set.nBch_UL;
	m_ADPM = set.dA_DPM ;
	m_BDPM = set.dB_DPM; 
	
	CString strVal;
	for(int i=0;i<10;i++)
	{
		strVal.Format("%G",set.sample.dA_ratio[i]);
		editSample[i][0].SetWindowText(strVal);
		strVal.Format("%G",set.sample.dA_CPM[i]);
		editSample[i][1].SetWindowText(strVal);
		strVal.Format("%G",set.sample.dB_ratio[i]);
		editSample[i][2].SetWindowText(strVal);
		strVal.Format("%G",set.sample.dB_CPM[i] );
		editSample[i][3].SetWindowText(strVal);
	}
	UpdateData(FALSE);
}
