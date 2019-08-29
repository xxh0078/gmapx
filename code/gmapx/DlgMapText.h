#if !defined(AFX_DLGMAPTEXT_H__93A5D024_9D64_4489_8F93_5BA8E5060347__INCLUDED_)
#define AFX_DLGMAPTEXT_H__93A5D024_9D64_4489_8F93_5BA8E5060347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMapText dialog

class CDlgMapText : public CDialog
{
// Construction
public:
	CDlgMapText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMapText)
	enum { IDD = IDD_DLGMAPTEXT };
	CString	m_strText;
	float	m_fLon;
	float	m_fLan;
	long	m_lFontSize;
	long	m_lBGRColor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMapText)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPTEXT_H__93A5D024_9D64_4489_8F93_5BA8E5060347__INCLUDED_)
