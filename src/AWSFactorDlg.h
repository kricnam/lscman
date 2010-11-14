#if !defined(AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_)
#define AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AWSFactorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAWSFactorDlg dialog

class CAWSFactorDlg : public CDialog
{
// Construction
public:
	CAWSFactorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAWSFactorDlg)
	enum { IDD = IDD_DIALOG_AWS_FACTOR };
	CButton	m_btnSave;
	CButton	m_btnOpen;
	CButton	m_btnSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAWSFactorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAWSFactorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSpectrum();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	afx_msg LONG OnHotKey(WPARAM wParam,LPARAM lParam);  
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_)
