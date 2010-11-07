#if !defined(AFX_DATACOLLECTIONDLG_H__A17B0148_F445_4D87_9680_B4D64B73D864__INCLUDED_)
#define AFX_DATACOLLECTIONDLG_H__A17B0148_F445_4D87_9680_B4D64B73D864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataCollectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionDlg dialog

class CDataCollectionDlg : public CDialog
{
// Construction
public:
	CDataCollectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataCollectionDlg)
	enum { IDD = IDD_DIALOG_DATA_COLLECTION };
	CEdit	m_EditStatus;
	CString	m_strCurrentTime;
	CString	m_strFileName;
	CString	m_strStartTime;
	CString	m_strStatus;
	CString	m_strMYNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataCollectionDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataCollectionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFileSetting();
	afx_msg void OnButtonAwsFactor();
	afx_msg void OnButtonShutDown();
	afx_msg void OnButtonSpectrum();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATACOLLECTIONDLG_H__A17B0148_F445_4D87_9680_B4D64B73D864__INCLUDED_)
