#if !defined(AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_)
#define AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AWSFactorDlg.h : header file
//
#include "AWSFile.h"
/////////////////////////////////////////////////////////////////////////////
// CAWSFactorDlg dialog

class CAWSFactorDlg : public CDialog
{
// Construction
public:
	CAWSFactorDlg(CWnd* pParent = NULL);   // standard constructor

	CEdit editSample[10][7];
	CStatic lbl[10];
// Dialog Data
	//{{AFX_DATA(CAWSFactorDlg)
	enum { IDD = IDD_DIALOG_AWS_FACTOR };
	CStatic	m_stcOrg;
	CButton	m_btnSave;
	CButton	m_btnOpen;
	CButton	m_btnSet;
	double	m_ADPM;
	int		m_nAchUL;
	int		m_nAchLL;
	double	m_BDPM;
	int		m_nBchLL;
	int		m_nBchUL;
	double	m_dBA_a;
	double	m_dBA_b;
	double	m_dBA_d;
	double	m_dBA_c;
	double	m_dBch_a;
	double	m_dBch_b;
	double	m_dBch_c;
	double	m_dBch_d;
	double	m_dAch_a;
	double	m_dAch_b;
	double	m_dAch_c;
	double	m_dAch_d;
	CString	m_strCurveName;
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
	void EnableItems(BOOL bEnable);
	void OpenFile(void);
	void LoadCalCo(AWS_CalCo& co);
	void LoadData(AWS_Setting& set);
	void LoadData(AWS_Setting& set,AWS_CalCo& co);
	void GetSetting(AWS_Setting& set);

	// Generated message map functions
	//{{AFX_MSG(CAWSFactorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSpectrum();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonFileSave();
	afx_msg void OnButtonFileOpen();
	//}}AFX_MSG
	afx_msg LONG OnHotKey(WPARAM wParam,LPARAM lParam);  
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWSFACTORDLG_H__3751029E_51EC_46A2_8CBD_9BA957D895AF__INCLUDED_)
