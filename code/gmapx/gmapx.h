#if !defined(AFX_GMAPX_H__673466AE_2873_421A_A70D_CC71E652EF04__INCLUDED_)
#define AFX_GMAPX_H__673466AE_2873_421A_A70D_CC71E652EF04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// gmapx.h : main header file for GMAPX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGmapxApp : See gmapx.cpp for implementation.

class CGmapxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMAPX_H__673466AE_2873_421A_A70D_CC71E652EF04__INCLUDED)
