// SelectList.cpp : implementation file
//

#include "stdafx.h"
#include "lsc.h"
#include "SelectList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectList dialog


CSelectList::CSelectList(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectList, CDialog)
	//{{AFX_MSG_MAP(CSelectList)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectList message handlers
