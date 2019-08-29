#if !defined(AFX_GMAPXPPG_H__99DFFB2F_CF60_4680_BDC6_D7189BF16DEE__INCLUDED_)
#define AFX_GMAPXPPG_H__99DFFB2F_CF60_4680_BDC6_D7189BF16DEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GmapxPpg.h : Declaration of the CGmapxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CGmapxPropPage : See GmapxPpg.cpp.cpp for implementation.

class CGmapxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGmapxPropPage)
	DECLARE_OLECREATE_EX(CGmapxPropPage)

// Constructor
public:
	CGmapxPropPage();

// Dialog Data
	//{{AFX_DATA(CGmapxPropPage)
	enum { IDD = IDD_PROPPAGE_GMAPX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CGmapxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMAPXPPG_H__99DFFB2F_CF60_4680_BDC6_D7189BF16DEE__INCLUDED)
