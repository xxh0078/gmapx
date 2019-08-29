#if !defined(AFX_DLGMAPLEGEND_H__905FA4BF_E5DF_4024_BDE6_AB8C26A414CF__INCLUDED_)
#define AFX_DLGMAPLEGEND_H__905FA4BF_E5DF_4024_BDE6_AB8C26A414CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapLegend.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMapLegend

class CDlgMapLegend : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgMapLegend)

// Construction
public:
	CDlgMapLegend(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDlgMapLegend(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapLegend)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgMapLegend();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgMapLegend)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPLEGEND_H__905FA4BF_E5DF_4024_BDE6_AB8C26A414CF__INCLUDED_)
