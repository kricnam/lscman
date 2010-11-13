#if !defined(AFX_SPECTRUMDLG_H__54AE311D_C503_43CD_8339_AC9875BE6351__INCLUDED_)
#define AFX_SPECTRUMDLG_H__54AE311D_C503_43CD_8339_AC9875BE6351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDlg dialog

class CSpectrumDlg : public CDialog
{
// Construction
public:
	CSpectrumDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpectrumDlg)
	enum { IDD = IDD_DIALOG_SPECTRUM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int nSpectrunData[5][4000];
	void DrawData(CDC *pDC,int x,int y, int cx,int cy);
	CRect DrawAxis(CDC *pDC, int x, int y, int cx, int cy);
	void DrawGraph(CDC* pDC, int x, int y, int cx, int cy);
	CWnd * pSpectrumWnd;

	// Generated message map functions
	//{{AFX_MSG(CSpectrumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAwsFactor();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonOpenAWD();
	afx_msg void OnButtonFileOpen();
	afx_msg void OnButtonFileSave();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	static char szDataFilter[];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMDLG_H__54AE311D_C503_43CD_8339_AC9875BE6351__INCLUDED_)
