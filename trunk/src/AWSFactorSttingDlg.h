#if !defined(AFX_AWSFACTORSTTINGDLG_H__0B667AA4_B413_4AEB_BBF8_4FDF2C87B5AB__INCLUDED_)
#define AFX_AWSFACTORSTTINGDLG_H__0B667AA4_B413_4AEB_BBF8_4FDF2C87B5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AWSFactorSttingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAWSFactorSttingDlg dialog

class CAWSFactorSttingDlg : public CDialog
{
// Construction
public:
	CAWSFactorSttingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAWSFactorSttingDlg)
	enum { IDD = IDD_DIALOG_AWS_FACTOR_SETTING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAWSFactorSttingDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAWSFactorSttingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWSFACTORSTTINGDLG_H__0B667AA4_B413_4AEB_BBF8_4FDF2C87B5AB__INCLUDED_)
