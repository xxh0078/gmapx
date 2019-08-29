// EasyMap.h : main header file for the EASYMAP application
//

#if !defined(AFX_EASYMAP_H__D3188882_1F71_4B05_B953_FB89542FB813__INCLUDED_)
#define AFX_EASYMAP_H__D3188882_1F71_4B05_B953_FB89542FB813__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyMapApp:
// See EasyMap.cpp for the implementation of this class
//

class CEasyMapApp : public CWinApp
{
public:
	CEasyMapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyMapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEasyMapApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYMAP_H__D3188882_1F71_4B05_B953_FB89542FB813__INCLUDED_)
