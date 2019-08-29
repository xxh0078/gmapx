#if !defined(AFX_DLGMAPSYMBOL_H__78A908F3_FCF6_424F_AD02_99F0DE54E799__INCLUDED_)
#define AFX_DLGMAPSYMBOL_H__78A908F3_FCF6_424F_AD02_99F0DE54E799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapSymbol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSymbol dialog

class CDlgMapSymbol : public CDialog
{
// Construction
public:
	CDlgMapSymbol(CWnd* pParent = NULL);   // standard constructor

	static CString GetInputText();
	static int GetICOID();
	static CString m_strInputText;
	static int m_iICOID;
// Dialog Data
	//{{AFX_DATA(CDlgMapSymbol)
	enum { IDD = IDD_DLGMAPSYMBOL };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapSymbol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMapSymbol)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPSYMBOL_H__78A908F3_FCF6_424F_AD02_99F0DE54E799__INCLUDED_)
