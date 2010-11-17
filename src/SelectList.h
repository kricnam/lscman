#if !defined(AFX_SELECTLIST_H__55092DB7_9F98_43C2_A413_192351CAF4EF__INCLUDED_)
#define AFX_SELECTLIST_H__55092DB7_9F98_43C2_A413_192351CAF4EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectList dialog

class CSelectList : public CDialog
{
// Construction
public:
	CSelectList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectList)
	enum { IDD = IDD_DIALOG_LIST };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectList)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTLIST_H__55092DB7_9F98_43C2_A413_192351CAF4EF__INCLUDED_)
