// DlgProperty.cpp : implementation file
//

#include "stdafx.h"
#include "gmapx.h"
#include "DlgProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProperty dialog


CDlgProperty::CDlgProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProperty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProperty)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProperty, CDialog)
	//{{AFX_MSG_MAP(CDlgProperty)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProperty message handlers
