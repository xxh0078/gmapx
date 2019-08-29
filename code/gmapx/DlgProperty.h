#if !defined(AFX_DLGPROPERTY_H__9AE21538_EFC8_496C_889A_A08A86F84E3C__INCLUDED_)
#define AFX_DLGPROPERTY_H__9AE21538_EFC8_496C_889A_A08A86F84E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProperty.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgProperty dialog

class CDlgProperty : public CDialog
{
// Construction
public:
	CDlgProperty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProperty)
	enum { IDD = IDD_DLGPROPERTY };
	CListCtrl	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProperty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProperty)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPERTY_H__9AE21538_EFC8_496C_889A_A08A86F84E3C__INCLUDED_)
