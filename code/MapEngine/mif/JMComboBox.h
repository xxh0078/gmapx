#if !defined(AFX_JMCOMBOBOX_H__577FB600_46CF_4F40_A96C_AEB16D77FE1B__INCLUDED_)
#define AFX_JMCOMBOBOX_H__577FB600_46CF_4F40_A96C_AEB16D77FE1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JMComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJMComboBox window

class CJMComboBox : public CComboBox
{
// Construction
public:
	CJMComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT     m_ID;
	CWnd* m_wndParent;

	COLORREF	m_clrHilight;
	COLORREF	m_clrNormalText;
	COLORREF	m_clrHilightText;
	COLORREF	m_clrBkgnd;
public:
	virtual ~CJMComboBox();

protected:
	DWORD				m_dwStyle;
	// Generated message map functions
protected:
	//{{AFX_MSG(CJMComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMCOMBOBOX_H__577FB600_46CF_4F40_A96C_AEB16D77FE1B__INCLUDED_)
