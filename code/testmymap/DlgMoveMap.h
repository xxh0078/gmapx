#if !defined(AFX_DLGMOVEMAP_H__BDF6A3EE_2191_4C9B_8F1E_782D1D3C31D3__INCLUDED_)
#define AFX_DLGMOVEMAP_H__BDF6A3EE_2191_4C9B_8F1E_782D1D3C31D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMoveMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveMap dialog

class CDlgMoveMap : public CDialog
{
// Construction
public:
	CDlgMoveMap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMoveMap)
	enum { IDD = IDD_DLGMOVEMAP };
	double	m_dLon;
	double	m_dlan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMoveMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMoveMap)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOVEMAP_H__BDF6A3EE_2191_4C9B_8F1E_782D1D3C31D3__INCLUDED_)
