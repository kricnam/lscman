// SpectrumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSC.h"
#include "Config.h"
#include "SpectrumDlg.h"
#include "SelectList.h"
#include "DataFile.h"
#include "AWSFile.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int round(double x)
{
	double i = ceil(x);
	return ((i-x)>0.5)?(int)i:(int)(i-1);
}

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
	m_strCurveName = _T("");
	m_strAchLL = _T("");
	m_strAchUL = _T("");
	m_strBchLL = _T("");
	m_strBchUL = _T("");
	//}}AFX_DATA_INIT
	pSpectrumWnd = NULL;
	setMF();
	nActiveIndex = 0;
	rgb.push_back(RGB(200,200,100));
	rgb.push_back(RGB(200,155,200));
	rgb.push_back(RGB(100,200,200));
	rgb.push_back(RGB(100,200,100));
	rgb.push_back(RGB(200,100,100));
	bLog = false;
}



void CSpectrumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumDlg)
	DDX_Control(pDX, IDC_BUTTON_LOG, m_btnLog);
	DDX_Control(pDX, IDC_SPIN_BU, m_spinBU);
	DDX_Control(pDX, IDC_SPIN_BL, m_spinBL);
	DDX_Control(pDX, IDC_SPIN_AU, m_spinAU);
	DDX_Control(pDX, IDC_SPIN_AL, m_spinAL);
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
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strCurveName);
	DDX_Text(pDX, IDC_EDIT_ACHLL, m_strAchLL);
	DDX_Text(pDX, IDC_EDIT_ACHUL, m_strAchUL);
	DDX_Text(pDX, IDC_EDIT_BCHLL, m_strBchLL);
	DDX_Text(pDX, IDC_EDIT_BCHUL, m_strBchUL);
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
	ON_BN_CLICKED(IDC_BUTTON_AWS, OnButtonAws)
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
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
	m_spinAL.SetRange(1,4000);
	m_spinAU.SetRange(1,4000);
	m_spinBL.SetRange(1,4000);
	m_spinBU.SetRange(1,4000);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpectrumDlg::OnButtonAwsFactor() 
{
	UpdateData();
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
	if (listData.size())
	{
		if (bLog)
			DrawDataLog(pDC,rect.left,rect.top,rect.Width(),rect.Height());
		else
			DrawData(pDC,rect.left,rect.top,rect.Width(),rect.Height());
	}
}

CRect CSpectrumDlg::DrawAxis(CDC *pDC, int x, int y, int cx, int cy)
{
	if (bLog) return DrawLogAxis(pDC,x,y,cx,cy);

	int nScaleMax = GetScaleMax();
	int nScaleCount = AxisYScaleCount(nScaleMax,0);
	CString title;
	CRect rect(x,y,cx,cy);
	title.Format("%d",nScaleMax*100);
	pDC->FillSolidRect(&rect,RGB(250,250,150));
	CSize size = pDC->GetTextExtent(title);
	rect.DeflateRect(size.cx,size.cy+size.cy/2);
	pDC->FillSolidRect(&rect,RGB(0,0,0));

	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(250,250,150));
	int dx = size.cx/6; //space to border
	int dy = rect.Height()/nScaleCount;
	
	
	for(int i =0;i <= nScaleCount ;i++)
	{
		title.Format("%2d",(nScaleCount-i)*(nScaleMax/nScaleCount));
		pDC->TextOut(x+dx,rect.top - size.cy/2 + dy * i, title );
	}
    
	dx = rect.Width() / 4;
	for( i=0;i<5;i++)
	{
		title.Format("%d",i*1000);
		size = pDC->GetTextExtent(title);
		pDC->TextOut(rect.left + i * dx - size.cx/2, rect.bottom , title);
	}
	pDC->TextOut(rect.left + 4 * dx + size.cx/2, rect.bottom,"ch");

	return rect;

}

CRect CSpectrumDlg::DrawLogAxis(CDC *pDC, int x, int y, int cx, int cy)
{
	CString title;
	int nScaleMax = GetScaleMax();
	int nScaleCount;
	if (nScaleMax<100)
		nScaleCount = 5;
	else
		nScaleCount = AxisYScaleCount(log10(nScaleMax),(double)0);
	title.Format("%d",nScaleMax*100);
	CRect rect(x,y,cx,cy);
	pDC->FillSolidRect(&rect,RGB(250,250,150));
	CSize size = pDC->GetTextExtent(title);
	rect.DeflateRect(size.cx,size.cy+size.cy/2);
	pDC->FillSolidRect(&rect,RGB(0,0,0));

	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(250,250,150));
	
	double nLogCount = log10(nScaleMax);
	
	int dx = size.cx/6; //space to border
	double dy = rect.Height()/nLogCount;
	int nScale;
	for(int i =0;i<nScaleCount;i++)
	{
		if (nScaleMax < 100)
		{
			nScale = (i==nScaleCount)?1:(nScaleCount-i)*(nScaleMax/nScaleCount);
		}
		else
		{
			nScale = (int)pow(10,(nScaleCount-1-i));
		}
		title.Format("%d",nScale);
		pDC->TextOut(x+dx,rect.bottom - dy * log10(nScale) - size.cy/2, title );
	}
    
	dx = rect.Width() / 4;
	for( i=0;i<5;i++)
	{
		title.Format("%d",i*1000);
		size = pDC->GetTextExtent(title);
		pDC->TextOut(rect.left + i * dx - size.cx/2, rect.bottom , title);
	}
	pDC->TextOut(rect.left + 4 * dx + size.cx/2, rect.bottom,"ch");

	return rect;

}

void CSpectrumDlg::DrawData(CDC *pDC, int x,int y, int cx, int cy)
{
	CPen pen, *old_pen;
	pen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	old_pen = pDC->SelectObject(&pen);
	list<RawData>::iterator it;

	int nx,ny;
	double dy = (double)cy / GetScaleMax();
	for(it=listData.begin();it!=listData.end();it++)
	{
		CPen* pPen = new CPen;
		pPen->CreatePen(PS_SOLID,3,(*it).rgb);
		pDC->SelectObject(pPen);
			for(int j=0;j<4000;j++)
			{
				nx = x + j * cx/4000;
				ny = y + cy - round((*it).nSpetrum[j] * dy);
				pDC->MoveTo(nx,ny);
				pDC->LineTo(nx,ny);
			}
		pDC->SelectObject(&pen);
		pPen->DeleteObject();
		delete pPen;
	}
	
	if (old_pen) pDC->SelectObject(old_pen);
	DrawLegend(pDC,x,y,cx,cy);
}

void CSpectrumDlg::DrawDataLog(CDC *pDC, int x,int y, int cx, int cy)
{
	CPen pen, *old_pen;
	pen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	old_pen = pDC->SelectObject(&pen);
	list<RawData>::iterator it;

	double dy = cy / log10(GetScaleMax());
	int nx,ny;
	for(it=listData.begin();it!=listData.end();it++)
	{
		CPen* pPen = new CPen;
		pPen->CreatePen(PS_SOLID,3,(*it).rgb);
		pDC->SelectObject(pPen);
			for(int j=0;j<4000;j++)
			{
				if ((*it).nSpetrum[j]==0) continue;
				nx = x + j * cx/4000;
				ny = y + cy - log10((*it).nSpetrum[j]) * dy;
				pDC->MoveTo(nx,ny);
				pDC->LineTo(nx,ny);
			}
		pDC->SelectObject(&pen);
		pPen->DeleteObject();
		delete pPen;
	}
	
	if (old_pen) pDC->SelectObject(old_pen);
	DrawLegend(pDC,x,y,cx,cy);
}

void CSpectrumDlg::DrawLegend(CDC *pDC, int x,int y, int cx, int cy)
{
	int nx,ny;
	int spaceX,spaceY;
	spaceX = pDC->GetTextExtent("M").cx;
	spaceY = pDC->GetTextExtent("M").cy;

	CRect rect(x+(cx*4)/5,y+cy/7,x+cx-cx/20,y+cy/7+7*spaceY);
	pDC->FillSolidRect(&rect,RGB(255,255,255));
	
	pDC->SetBkColor(RGB(255,255,255));

	nx = rect.left+ spaceX;
	ny = rect.top+ spaceY;
	for(int i=0;i<listData.size();i++)
	{
		if(i>4) break;
		RawData& data = GetListItem(i);
		CString str = data.strName;
		int dx,dy;
		dx = pDC->GetTextExtent(str).cx;
		dy = pDC->GetTextExtent(str).cy;
		if (dx > rect.Width()-2*spaceX)
		{
			formatString(str,dx, rect.Width()-2*spaceX);
		}
		
		if (i==nActiveIndex) 
		{
			pDC->SetTextColor(RGB(0,0,0));
			pDC->TextOut(nx - spaceX/2,ny,"*");
		}
		pDC->SetTextColor(data.rgb);
		pDC->TextOut(nx,ny,str);
		ny += dy;
	}
}

void CSpectrumDlg::OnButtonOpenAWD() 
{
	CFileDialog dlg(TRUE,"awd",NULL,0,"AWS File(*.aws)|*.aws||",this->GetParent());
	if (dlg.DoModal()==IDOK)
	{
		m_strCurveName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CSpectrumDlg::OnButtonFileOpen() 
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT ,szDataFilter,this->GetParent());
	TCHAR szFileName[5*(MAX_PATH+1)+1]={0};
	dlg.m_ofn.lpstrFile = szFileName;
	dlg.m_ofn.nMaxFile = 5*(MAX_PATH+1);
	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
        int iCtr = 0;
		CString fileName[5];
        while(fileNamesPosition != NULL)
        {
              fileName[iCtr] = dlg.GetNextPathName(fileNamesPosition);
              iCtr++;
			  if (iCtr==5) break;
        }  

		int i=0;
		while(iCtr--)
		{
			if (listData.size() > 4)
			{
				MessageBox("Open too many files, olny 5 file can be displayed.");
				break;
			}
			int n;
			if (isOpenedAt(fileName[i],n))
				deleteData(n);
			if (!LoadData(fileName[i++])) return;
		};

		if (i)
		{
			setActiveData(listData.front());
			nActiveIndex = 0;
			Invalidate();   
			UpdateWindow();
			UpdateData(FALSE);
		}
	}
}

void CSpectrumDlg::OnButtonFileSave() 
{
	if (0==listData.size()) return;
	UpdateData();
	RawData& data = GetListItem(nActiveIndex);
	CDataFile Data;
	CString strPath = data.strPath;
	char ext[_MAX_EXT]={0};
	
	_splitpath(strPath, NULL, NULL, NULL, ext );
	strPath = strPath.Left(strPath.GetLength()-strlen(ext));
	strPath += "_AWS";
	strPath += ext;
	CString strExt = ext;
	strExt.TrimLeft(".");
	
	CFileDialog dlg(FALSE,strExt,strPath,OFN_OVERWRITEPROMPT,NULL,this->GetParent());
	
	if (dlg.DoModal()!=IDOK) return;
    strPath = dlg.GetPathName();
	if (Data.Open(data.strPath))
	{
		if (Data.Load())
		{
			Data.SetDPM(m_strADPM,m_strBDPM);
			Data.SetEff(m_strAEFF,m_strBEFF);

			if (Data.SaveAs(strPath))
				AfxMessageBox("Successfully saved " + strPath);
			else
				AfxMessageBox("Failed to save " + strPath);
		}
		else
			AfxMessageBox(CString("Failed to load data from ") + data.strPath);
	}
	else
	{
		AfxMessageBox("Failed to open raw data file" + data.strPath);
	}
}

void CSpectrumDlg::OnButtonSelect() 
{
	CSelectList dlg(this);
	list<RawData>::iterator it;
	int i=0;
	for(it=listData.begin();it!=listData.end();it++)
	{
		dlg.m_strList[i++]=((*it).strName);
		if (i>4) break;
	}
	dlg.m_nSelIndex = nActiveIndex;
	if (dlg.DoModal()==IDOK)
	{
		nActiveIndex = dlg.m_nSelIndex;
		Invalidate();
		UpdateWindow();
	}
}

void CSpectrumDlg::OnButtonDelete() 
{
	CSelectList dlg(this);
	dlg.m_strTitle = "Delete";
		list<RawData>::iterator it;
	int i=0;
	for(it=listData.begin();it!=listData.end();it++)
	{
		dlg.m_strList[i++]=((*it).strName);
		if (i>4) break;
	}
	dlg.m_nSelIndex = nActiveIndex;
	if (dlg.DoModal()==IDOK)
	{
		deleteData(dlg.m_nSelIndex);
		if (listData.size())
		{
			setActiveData(GetListItem(nActiveIndex));
		}
		else
		{
			RawData data;
			setActiveData(data);
		}
		UpdateData(FALSE);
		Invalidate();
		UpdateWindow();
		
	}
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
		CString strMsg;
		strMsg.Empty();
		RawData rawData;
		
		char szName[_MAX_FNAME]={0};
		char ext[_MAX_EXT]={0};

		_splitpath(szPath, NULL, NULL, szName, ext );

		while (data.Open(szPath))
		{
			rawData.strName = szName;
			rawData.strName+= ext;
			rawData.strPath = szPath;
			memset(rawData.nSpetrum,0,4000);
			int n = data.GetSpectrumData(rawData.nSpetrum,4000); 
			//TODO implement the load process by CDataFile Class
			if (n<4000)
			{
				strMsg.Format("Load %d channel data, maybe not correct file format",n);
				MessageBox(strMsg,"Warning",MB_OK);
				return false;
			}

			if (!data.GetFieldValue("A-GROSS",rawData.strAGROSS))
				strMsg+="[A-GROSS] ";
			if (!data.GetFieldValue("B-GROSS",rawData.strBGROSS))
				strMsg+="[B-GROSS] ";
			if (!data.GetFieldValue("SCCR",rawData.strSCCR))
				strMsg+="[SCCR] ";
			if (!data.GetFieldValue("ESCR",rawData.strESCR))
				strMsg+="[ESCR] ";

			if (data.GetFieldIndex("A-DPM"))
			{
				data.GetFieldValue("A-DPM",rawData.strADPM);
			}
			else if(data.GetFieldIndex("A-Bq"))
			{
				data.GetFieldValue("A-Bq",rawData.strADPM);
			}
			else
				strMsg+="[A-DPM] ";

			if (data.GetFieldIndex("B-DPM"))
			{
				data.GetFieldValue("B-DPM",rawData.strBDPM);
			}
			else if(data.GetFieldIndex("B-Bq"))
			{
				data.GetFieldValue("B-Bq",rawData.strBDPM);
			}
			else
				strMsg+="[B-DPM] ";
			
			if (!data.GetFieldValue("A-EFF",rawData.strAEFF))
				strMsg+="[A-EFF] ";
			
			if (!data.GetFieldValue("B-EFF",rawData.strBEFF))
				strMsg+="[B-EFF] ";

			if (!data.GetFieldValue("TIME",rawData.strTime))
				strMsg+="[TIME] ";

			if (strMsg.GetLength()) 
			{
				strMsg+="fiels not found.";
				break;
			}
			rawData.rgb = rgb.front();
			rgb.pop_front();
			listData.push_front(rawData);
			return true;
		}

		if (strMsg.IsEmpty()) strMsg.Format("Open %s failed.",szPath);
		MessageBox(strMsg,"Error",MB_OK);
		return false;
}

void CSpectrumDlg::OnButtonAws() 
{
	if (m_strCurveName.IsEmpty()) return;
	CAWSFile awsFile;
	AWS_Setting set;
	AWS_CalCo co;
	UpdateData();
	awsFile.ReadData(m_strCurveName,set);
	if (awsFile.CalculateCoefficient(set,co))
	{
		double factor = Factor(atof(m_strESCR));

		if (m_strAchLL.IsEmpty())
		{
			m_strAchLL.Format("%d",set.nAch_LL);
			m_strAchUL.Format("%d", round(set.nAch_UL * factor));
			m_strBchLL.Format("%d", round(set.nBch_LL * factor));
			m_strBchUL.Format("%d",round(set.nBch_UL * factor));
		}
		

		factor = atof(m_strESCR);
		double y,fAEff,fBEff;
		double z,Z;
		y = co.dAch_co[0] + factor * co.dAch_co[1] + pow(factor,2) * co.dAch_co[2] + pow(factor,3)*co.dAch_co[3];
		m_strAEFF.Format("%G",y);
		fAEff = y;
		
		y = co.dBch_co[0] + factor * co.dBch_co[1] + pow(factor,2) * co.dBch_co[2] + pow(factor,3)*co.dBch_co[3];
		m_strBEFF.Format("%G",y);
		fBEff = y;

		y = co.d_BA_co[0] + factor * co.d_BA_co[1] + pow(factor,2) * co.d_BA_co[2] + pow(factor,3)*co.d_BA_co[3];
        DWORD sum = ChanelSum(atoi(m_strAchLL),atoi(m_strAchUL));
		m_strAGROSS.Format("%d",sum);
		Z = sum/m_nTime;
		sum = ChanelSum(atoi(m_strBchLL),atoi(m_strBchUL));
		m_strBGROSS.Format("%d",sum);
		z = sum/m_nTime;
		
		Z = (Z-(1/y)*z)/fAEff;	
		z = z/fBEff;
		m_strADPM.Format("%G",Z);
		m_strBDPM.Format("%G",z);
	}	
	UpdateData(FALSE);
}

RawData& CSpectrumDlg::GetListItem(int n)
{
	list<RawData>::iterator it;
	int i=0;
	for(it=listData.begin();it!=listData.end();it++)
	{
		if(i++==n) return (*it);
	}
	return listData.back();
}

void CSpectrumDlg::formatString(CString &str,int dx, int cx)
{
	int pDX;
	pDX = dx / str.GetLength();
	int n = cx / pDX;
	CString strF;
	strF = str;
	LPCTSTR pChar = strF;
	for(int i=0;i<n-5;i++)
	{
		pChar = CharNext(pChar);
		if ((pChar - (LPCTSTR)strF)> (n-5))
		{
			pChar = CharPrev(strF,pChar);
			break;
		}
		if ((pChar - (LPCTSTR)strF)== (n-5))
			break;
	}
	strF = strF.Left(pChar-strF);
	strF += "~";
	strF += str.Right(n - strF.GetLength());
	str = strF;
}

void CSpectrumDlg::deleteData(int n)
{
	list<RawData>::iterator it;
	int i=0;

	for(it=listData.begin();it!=listData.end();it++)
	{
		if(i++==n) 
		{
			rgb.push_back((*it).rgb);
			listData.erase(it);
			break;
		}
	}

	if(nActiveIndex >= n) nActiveIndex--;

	if (!(nActiveIndex < listData.size()))
		nActiveIndex = listData.size() - 1;
	if (nActiveIndex < 0 ) nActiveIndex = 0;
}

void CSpectrumDlg::setActiveData(RawData &data)
{
	m_strESCR = data.strESCR;
	m_strSCCR = data.strSCCR;
	m_strAEFF = data.strAEFF;
	m_strBEFF = data.strBEFF;
	m_strADPM = data.strADPM;
	m_strBDPM = data.strBDPM;
	m_strAGROSS =data.strAGROSS;
	m_strBGROSS=data.strBGROSS;
	m_nTime = atoi(data.strTime);
}

bool CSpectrumDlg::isOpenedAt(LPCTSTR szPath,int& n)
{
	list<RawData>::iterator it;
	int i=0;

	for(it=listData.begin();it!=listData.end();it++)
	{
		if ((*it).strPath == szPath)
		{
			n = i;
			return true;
		}
		i++;
	}
	return false;
}

DWORD CSpectrumDlg::ChanelSum(int nLL, int nLU)
{
	RawData& data = GetListItem(nActiveIndex);

	if (nLL < 0) nLL = 1;
	if (nLU > 3999) nLU = 3999;

	int sum = 0;

	for(int i = nLL-1;i<=nLU;i++)
	{
		sum+=data.nSpetrum[i];
	}

	return sum;
}

void CSpectrumDlg::OnButtonLog() 
{
	if (bLog)
	{
		bLog = false;
		m_btnLog.SetWindowText("&LOG");
	}
	else
	{
		bLog = true;
		m_btnLog.SetWindowText("&LIN");
	}
	Invalidate();
	UpdateWindow();
}

int CSpectrumDlg::GetMaxCount(void)
{
	list<RawData>::iterator it;
	int i=0;
	int nMax = 0;
	for(it=listData.begin();it!=listData.end();it++)
	{
		for(i=0;i<4000;i++)
			nMax = max((*it).nSpetrum[i],nMax);
	}

	if (nMax < 50) nMax = 50;
	return nMax;

}

int CSpectrumDlg::GetScaleMax()
{
   int nScaleMax = GetMaxCount();

   if (nScaleMax>50)
	{
		//make the Scale 100 times
		nScaleMax = ((nScaleMax/100) + ((nScaleMax%100)?1:0))*100;
	}
   return nScaleMax;
}

int CSpectrumDlg::AxisYScaleCount(int nMax, int nMin)
{
	int count = nMax - nMin;
	
	double div = pow(10, floor(log10(count)-1));
	while (count>10)
	{
		count =(nMax-nMin)/div;
		if (count > 10) div+=div;
	};
	if (count * div < 100)
	{
		div =10;
		count = (nMax - nMin)/div;
	}
	if (count==0)
	{
		count=1;
	}
	return count;
}

int CSpectrumDlg::AxisYScaleCount(double nMax, double nMin)
{
	int count = floor(nMax) - ceil(nMin)+1;
	
	return count;
}

void CSpectrumDlg::OnButtonPrint() 
{
	CDC dc;
	CPrintDialog printDlg(FALSE);
	if (printDlg.DoModal() != IDOK)
		return;
	
	dc.Attach(printDlg.GetPrinterDC());
	
	//绑定一个打印机DC到CDC
	
	dc.m_bPrinting=TRUE;
	
	DOCINFO di; //初始化打印机的DOCINFO
	memset(&di,0,sizeof (DOCINFO));
	di.cbSize=sizeof (DOCINFO);
	
	BOOL bPrintingOK=dc.StartDoc(&di); //开始一个打印任务
	

}