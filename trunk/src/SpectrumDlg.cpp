// SpectrumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "Config.h"
#include "SpectrumDlg.h"
#include "SelectList.h"
#include "DataFile.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDlg dialog
char CSpectrumDlg::szDataFilter[] = "Data File|*.???||";
char CSpectrumDlg::szAWSFilter[] = "AWS File(*.aws)|*.aws||";

CSpectrumDlg::CSpectrumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpectrumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrumDlg)
	m_strAGROSS = _T("");
	m_strBGROSS = _T("");
	m_strESCR = _T("");
	m_strSCCR = _T("");
	m_strADPM = _T("");
	m_strAEFF = _T("");
	m_strBDPM = _T("");
	m_strBEFF = _T("");
	//}}AFX_DATA_INIT
	pSpectrumWnd = NULL;
	for(int i = 0;i <4000;i++)
	{
		nSpectrunData[0][i] = 0 ;
	}
	setMF();
}



void CSpectrumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumDlg)
	DDX_Text(pDX, IDC_EDIT_AGROSS, m_strAGROSS);
	DDV_MaxChars(pDX, m_strAGROSS, 20);
	DDX_Text(pDX, IDC_EDIT_BGROSS, m_strBGROSS);
	DDV_MaxChars(pDX, m_strBGROSS, 20);
	DDX_Text(pDX, IDC_EDIT_ESCR, m_strESCR);
	DDV_MaxChars(pDX, m_strESCR, 20);
	DDX_Text(pDX, IDC_EDIT_SCCR, m_strSCCR);
	DDV_MaxChars(pDX, m_strSCCR, 20);
	DDX_Text(pDX, IDC_EDIT_ADPM, m_strADPM);
	DDV_MaxChars(pDX, m_strADPM, 20);
	DDX_Text(pDX, IDC_EDIT_AEFF, m_strAEFF);
	DDV_MaxChars(pDX, m_strAEFF, 20);
	DDX_Text(pDX, IDC_EDIT_BDPM, m_strBDPM);
	DDV_MaxChars(pDX, m_strBDPM, 20);
	DDX_Text(pDX, IDC_EDIT_BEFF, m_strBEFF);
	DDV_MaxChars(pDX, m_strBEFF, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrumDlg, CDialog)
	//{{AFX_MSG_MAP(CSpectrumDlg)
	ON_BN_CLICKED(IDC_BUTTON_AWS_FACTOR, OnButtonAwsFactor)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILEDIA, OnButtonOpenAWD)
	ON_BN_CLICKED(IDC_BUTTON_FILE_OPEN, OnButtonFileOpen)
	ON_BN_CLICKED(IDC_BUTTON_FILE_SAVE, OnButtonFileSave)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDlg message handlers

BOOL CSpectrumDlg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CSpectrumDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	pSpectrumWnd = GetDlgItem(IDC_SPECTRUM);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpectrumDlg::OnButtonAwsFactor() 
{
	::PostMessage(this->GetParent()->m_hWnd,WM_OPEN_DLG,OPEN_AWS_FACTOR,0);
	
}

void CSpectrumDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages
	
	pSpectrumWnd->Invalidate();
	pSpectrumWnd->UpdateWindow();
	
	CDC *pDC = pSpectrumWnd->GetDC();
	CRect rect;
	pSpectrumWnd->GetClientRect(&rect);

	DrawGraph(pDC,0,0,rect.Width(),rect.Height());

	ReleaseDC(pDC);
	
}

HBRUSH CSpectrumDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_SPECTRUM)
	{
		//pDC->SetBkColor(RGB(0,0,0));
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSpectrumDlg::DrawGraph(CDC *pDC, int x, int y, int cx, int cy)
{
	CRect rect = DrawAxis(pDC,x,y,cx,cy);
	DrawData(pDC,rect.left,rect.top,rect.Width(),rect.Height());
}

CRect CSpectrumDlg::DrawAxis(CDC *pDC, int x, int y, int cx, int cy)
{
	CRect rect(x,y,cx,cy);
	pDC->FillSolidRect(&rect,RGB(250,250,150));
	CSize size = pDC->GetTextExtent("000",3);
	rect.DeflateRect(size.cx,size.cy+size.cy/2);
	pDC->FillSolidRect(&rect,RGB(0,0,0));

	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(250,250,150));
	int dx = size.cx/6; //space to border
	int dy = rect.Height()/5;
	CString title;
	for(int i =0;i< 6;i++)
	{
		title.Format("%d",(5-i)*10);
		pDC->TextOut(x+dx,rect.top - size.cy/2 +dy * i, title );
	}
    
	dx = rect.Width() / 4;
	for( i=0;i<5;i++)
	{
		title.Format("%d",i*1000);
		size = pDC->GetTextExtent(title);
		pDC->TextOut(rect.left + i * dx - size.cx/2, rect.bottom , title);
	}

	return rect;

}

void CSpectrumDlg::DrawData(CDC *pDC, int x,int y, int cx, int cy)
{
	CPen pen, *old_pen;
	pen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	old_pen = pDC->SelectObject(&pen);
    int nx,ny;
	for(int i = 0;i<1;i++)
	{
		for(int j=0;j<4000;j++)
		{
            nx = x + j * cx/4000;
			ny = y + cy - nSpectrunData[i][j] * cy / 50;
     		pDC->MoveTo(nx,ny);
  	        pDC->LineTo(nx,ny);
		}
	}
	
	if (old_pen) pDC->SelectObject(old_pen);
}

void CSpectrumDlg::OnButtonOpenAWD() 
{
	CFileDialog dlg(TRUE,"awd");
	dlg.DoModal();

}

void CSpectrumDlg::OnButtonFileOpen() 
{
	CFileDialog dlg(TRUE,NULL,NULL,0,szDataFilter,this->GetParent());
	if (dlg.DoModal() == IDOK)
	{
		LoadData(dlg.GetPathName());
	}
}

void CSpectrumDlg::OnButtonFileSave() 
{
	
	CFileDialog dlg(FALSE,"awd",NULL,0,szAWSFilter,this->GetParent());
	dlg.DoModal();
	
}

void CSpectrumDlg::OnButtonSelect() 
{
	CSelectList dlg(this);
	dlg.DoModal();
}

void CSpectrumDlg::OnButtonDelete() 
{
	CSelectList dlg(this);
	dlg.DoModal();
}

double CSpectrumDlg::Factor(double Y)
{
	double p,q;
	p = pow(10.0,MF_a);
	p *= MF_A;
	p *= pow(Y,3);

	q = pow(10.0,MF_b);
	q *= MF_B;
	q *= pow(Y,2);

	p += q;

	q = pow(10,MF_c);
	q *= MF_C;
	q *= Y;

	p += q;

	q = pow(10,MF_d);
	q *= MF_D;

	return p + q;

}

void CSpectrumDlg::setMF()
{
	Config conf(CONF_FILENAME);
	MF_A = conf.GetMF_A();
	MF_B = conf.GetMF_B();
	MF_C = conf.GetMF_C();
	MF_D = conf.GetMF_D();
	MF_a = conf.GetMF_a();
	MF_b = conf.GetMF_b();
	MF_c = conf.GetMF_c();
	MF_d = conf.GetMF_d();
}

bool CSpectrumDlg::LoadData(LPCTSTR szPath)
{
		CDataFile data;
		while (data.Open(szPath))
		{
			int n = data.GetSpectrumData(&nSpectrunData[0][0],4000); 
			if (n<4000)
			{
				CString strMsg;
				strMsg.Format("Load %d channel data, maybe not correct file format",n);
				MessageBox(strMsg,"Warning",MB_OK);
				return false;
			}

			data.GetFieldValue("A-GROSS",m_strAGROSS);
			data.GetFieldValue("B-GROSS",m_strBGROSS);
			data.GetFieldValue("SCCR",m_strSCCR);
			data.GetFieldValue("ESCR",m_strESCR);
			data.GetFieldValue("A-DPM",m_strADPM);
			if (!m_strADPM.GetLength())	data.GetFieldValue("A-Bq",m_strADPM);
			data.GetFieldValue("B-DPM",m_strBDPM);
			if (!m_strADPM.GetLength())	data.GetFieldValue("B-Bq",m_strADPM);
			data.GetFieldValue("A-EFF",m_strAEFF);
			data.GetFieldValue("B-EFF",m_strBEFF);
			Invalidate();   
			UpdateWindow();
			UpdateData(FALSE);
			return true;
		}

		CString strMsg;
		strMsg.Format("Open %s failed.",szPath);
		MessageBox(strMsg,"Error",MB_OK);
		return false;
}
