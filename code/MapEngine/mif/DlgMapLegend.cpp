// DlgMapLegend.cpp : implementation file
//

#include "stdafx.h"
#include "easymap.h"
#include "DlgMapLegend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapLegend

IMPLEMENT_DYNAMIC(CDlgMapLegend, CPropertySheet)

CDlgMapLegend::CDlgMapLegend(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDlgMapLegend::CDlgMapLegend(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDlgMapLegend::~CDlgMapLegend()
{
}


BEGIN_MESSAGE_MAP(CDlgMapLegend, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgMapLegend)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapLegend message handlers
