// GmapxPpg.cpp : Implementation of the CGmapxPropPage property page class.

#include "stdafx.h"
#include "gmapx.h"
#include "GmapxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CGmapxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGmapxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CGmapxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGmapxPropPage, "GMAPX.GmapxPropPage.1",
	0xb5bd0c51, 0x1716, 0x4f89, 0x99, 0x6c, 0xec, 0x38, 0xb4, 0x29, 0xba, 0x18)


/////////////////////////////////////////////////////////////////////////////
// CGmapxPropPage::CGmapxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGmapxPropPage

BOOL CGmapxPropPage::CGmapxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GMAPX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxPropPage::CGmapxPropPage - Constructor

CGmapxPropPage::CGmapxPropPage() :
	COlePropertyPage(IDD, IDS_GMAPX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CGmapxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxPropPage::DoDataExchange - Moves data between page and properties

void CGmapxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGmapxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxPropPage message handlers
