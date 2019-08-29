// DlgMapSymbol.cpp : implementation file
//

#include "stdafx.h"
#include "gmapx.h"
#include "DlgMapSymbol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSymbol dialog

CString CDlgMapSymbol::m_strInputText="";
int CDlgMapSymbol::m_iICOID=5;
CDlgMapSymbol::CDlgMapSymbol(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMapSymbol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMapSymbol)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMapSymbol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapSymbol)
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMapSymbol, CDialog)
	//{{AFX_MSG_MAP(CDlgMapSymbol)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSymbol message handlers

void CDlgMapSymbol::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData();
	CDlgMapSymbol::m_strInputText = this->m_strText;
	CDialog::OnOK();
}

void CDlgMapSymbol::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDlgMapSymbol::m_strInputText = "";
	CDialog::OnCancel();
}

void CDlgMapSymbol::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	CDlgMapSymbol::m_iICOID=4;
}

void CDlgMapSymbol::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	CDlgMapSymbol::m_iICOID=5;
}

void CDlgMapSymbol::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	CDlgMapSymbol::m_iICOID=6;
}

void CDlgMapSymbol::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	CDlgMapSymbol::m_iICOID=7;
}

void CDlgMapSymbol::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	g_pGmapxCtrl->m_pMapEngine->m_MapDisp.m_MapLayerMan.m_MapPoiRes.DrawAutoSize( dc.GetSafeHdc(),4,110,100);
	g_pGmapxCtrl->m_pMapEngine->m_MapDisp.m_MapLayerMan.m_MapPoiRes.DrawAutoSize( dc.GetSafeHdc(),5,300,100);
	g_pGmapxCtrl->m_pMapEngine->m_MapDisp.m_MapLayerMan.m_MapPoiRes.DrawAutoSize( dc.GetSafeHdc(),6,110,150);
	g_pGmapxCtrl->m_pMapEngine->m_MapDisp.m_MapLayerMan.m_MapPoiRes.DrawAutoSize( dc.GetSafeHdc(),7,300,150);
	// Do not call CDialog::OnPaint() for painting messages
}
