// FileSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "FileSettingDlg.h"
#include "EnumSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSettingDlg dialog


CFileSettingDlg::CFileSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSettingDlg)
	m_strFileName = _T("");
	m_DataCollectionByNo = 1;
	//}}AFX_DATA_INIT
}


void CFileSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSettingDlg)
	DDX_Control(pDX, IDC_COMBO_COMNO, m_ComboComNo);
	DDX_Control(pDX, IDC_LIST_SET, m_ListSet);
	DDX_Control(pDX, IDC_COMBO_MYNO, m_ComboMyNo);
	DDX_Control(pDX, IDC_COMBO_EXTEN, m_ComboExtension);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Radio(pDX, IDC_RADIO_COLLECTION_YES, m_DataCollectionByNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSettingDlg)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILEDIA, OnButtonOpenFiledia)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_DATA_COLLECTION, OnButtonDataCollection)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_COMCONF, OnButtonComconf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSettingDlg message handlers

BOOL CFileSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitExtensionComboBox();
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	m_listImage.Create(2,20,ILC_COLOR24|ILC_MASK,1,0);
	m_listImage.Add(&bmp,RGB(255,255,255));
	m_ListSet.SetImageList(&m_listImage, LVSIL_SMALL);
	InitListCtrl();
	InitListData();
	InitComNo();
	if (m_ComboComNo.GetCount() > 0)
	{
		m_ComboComNo.SetCurSel(0);
	}
	m_ComboMyNo.SetCurSel(0);
	m_ComboExtension.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFileSettingDlg::PreTranslateMessage(MSG* pMsg) 
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

void CFileSettingDlg::InitExtensionComboBox()
{
	for (int i = 0; i < 999; i++)
	{
		CString strNo;
		strNo.Format("%03d",i+1);
		m_ComboExtension.AddString(strNo);
	}
}

void CFileSettingDlg::OnButtonOpenFiledia() 
{
	UpdateData(TRUE);
	CString strFileName,strFName,strExt;
	m_ComboExtension.GetWindowText(strExt);
	CFileDialog FDlg(FALSE,strExt,"",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"All File(*.*)|*.*||",NULL);
	if (FDlg.DoModal() == IDOK)
	{
		strFileName = FDlg.GetPathName();
		strFName = FDlg.GetFileName();
		m_strFileName = strFileName;
		UpdateData(FALSE);
	}
	else
	{
		return;
	}
	
}

void CFileSettingDlg::InitListCtrl()
{
	int nWidth = 30;
	
	LV_COLUMN lvcColumn;
	lvcColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcColumn.fmt  = LVCFMT_LEFT;
	
	lvcColumn.pszText	= "MY No.";
	lvcColumn.iSubItem	= 0;
	lvcColumn.cx		= 2*nWidth;
	m_ListSet.InsertColumn(0, &lvcColumn );
	
	lvcColumn.fmt  = LVCFMT_CENTER;
	lvcColumn.pszText	= "Data collection";
	lvcColumn.iSubItem	= 1;
	lvcColumn.cx		= 4*nWidth;
	m_ListSet.InsertColumn(1, &lvcColumn );
	
	lvcColumn.fmt  = LVCFMT_LEFT;
	lvcColumn.pszText	= "File Name";
	lvcColumn.iSubItem	= 2;
	lvcColumn.cx		= 11*nWidth;
	m_ListSet.InsertColumn(2, &lvcColumn );
	
	lvcColumn.fmt  = LVCFMT_CENTER;
	lvcColumn.pszText	= "Extension";
	lvcColumn.iSubItem	= 2;
	lvcColumn.cx		= 80;
	m_ListSet.InsertColumn(3, &lvcColumn );
	
	m_ListSet.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

void CFileSettingDlg::InitListData()
{
	for (int i = 0; i < 12; i++)
	{
		g_SetArray[i+1].m_strID.Format("%d",i+1);
		g_SetArray[i+1].m_DataCollection = FALSE;
		g_SetArray[i+1].m_strFileName = "";
		g_SetArray[i+1].m_Extension = "";
		m_ListSet.InsertItem(i,g_SetArray[i+1].m_strID);
		if (g_SetArray[i+1].m_DataCollection)
		{
			m_ListSet.SetItemText(i,1,"o");
		}
		else
		{
			m_ListSet.SetItemText(i,1,"-");
		}
		m_ListSet.SetItemText(i,2,g_SetArray[i+1].m_strFileName);
		m_ListSet.SetItemText(i,3,g_SetArray[i+1].m_Extension);
	}
}

void CFileSettingDlg::UpdateListItem(int MYNo)
{
	if (g_SetArray[MYNo].m_DataCollection)
	{
		m_ListSet.SetItemText(MYNo-1,1,"o");
	}
	else
	{
		m_ListSet.SetItemText(MYNo-1,1,"-");
	}
	m_ListSet.SetItemText(MYNo-1,2,g_SetArray[MYNo].m_strFileName);
	m_ListSet.SetItemText(MYNo-1,3,g_SetArray[MYNo].m_Extension);
}

void CFileSettingDlg::OnButtonSet() 
{
	UpdateData(TRUE);
	int i = m_ComboMyNo.GetCurSel();
	i++;
	g_SetArray[i].m_strFileName = m_strFileName;
	m_ComboExtension.GetWindowText(g_SetArray[i].m_Extension);
	if (m_DataCollectionByNo == 0)
	{
		g_SetArray[i].m_DataCollection = TRUE;
	}
	else
	{
		g_SetArray[i].m_DataCollection = FALSE;
	}
	UpdateListItem(i);
}

void CFileSettingDlg::OnButtonDataCollection() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_DATA_COLLECTION,0);
}

void CFileSettingDlg::InitComNo()
{
	CString strNo,strName;
	CArray<SSerInfo,SSerInfo&> asi;
	try
	{
		EnumSerialPorts(asi,TRUE);
		for (int i=0; i < asi.GetSize(); i++) 
		{
			strName = asi[i].strFriendlyName;
			int idx = strName.Find("(COM");
			if (idx > 0)
			{
				int last = strName.Find(")",idx+1);
				if (last > 0)
				{
					strNo = strName.Mid(idx + 1,last - idx - 1);
					m_ComboComNo.AddString(strNo);
				}
			}
			
		}
	}
	catch(CString strErr)
	{
		AfxMessageBox(strErr);
	}
}

void CFileSettingDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

HBRUSH CFileSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}



void CFileSettingDlg::OnButtonComconf() 
{
	COMMCONFIG conf={0};
	CString strPort;
	conf.dwSize = sizeof(COMMCONFIG);
	conf.wVersion = 1;
	conf.dwProviderSize = 1;
	conf.dcb.BaudRate = CBR_9600;
	conf.dcb.ByteSize = 7;
	conf.dcb.Parity = EVENPARITY;        // no parity bit
	conf.dcb.StopBits =TWOSTOPBITS;    // one stop bit
	int n;
	n = m_ComboComNo.GetCurSel();
	if (n == CB_ERR)
	{
		m_ComboComNo.GetEditSel();
	}
	else
		m_ComboComNo.GetLBText(n,strPort);

	if (CommConfigDialog(strPort,GetSafeHwnd(),&conf))
	{
		m_cdcConf = conf.dcb;
	}
	else
	{
		CErrorMsg msg;
		msg.GetErrorMsg("COM conf");
		AfxMessageBox(msg);
	}
}
