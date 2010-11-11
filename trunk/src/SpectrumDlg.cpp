// SpectrumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "SpectrumDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDlg dialog


CSpectrumDlg::CSpectrumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpectrumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrumDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pSpectrumWnd = NULL;
	for(int i = 0;i <4000;i++)
	{
		nSpectrunData[0][i] = 20 + sin(i *3.14 /180) * 20;
	}
}


void CSpectrumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrumDlg, CDialog)
	//{{AFX_MSG_MAP(CSpectrumDlg)
	ON_BN_CLICKED(IDC_BUTTON_AWS_FACTOR, OnButtonAwsFactor)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
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
