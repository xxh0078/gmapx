// DlgMoveMap.cpp : implementation file
//

#include "stdafx.h"
#include "testmymap.h"
#include "DlgMoveMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveMap dialog


CDlgMoveMap::CDlgMoveMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMoveMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMoveMap)
	m_dLon = 0.0;
	m_dlan = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgMoveMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMoveMap)
	DDX_Text(pDX, IDC_EDIT1, m_dLon);
	DDX_Text(pDX, IDC_EDIT2, m_dlan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMoveMap, CDialog)
	//{{AFX_MSG_MAP(CDlgMoveMap)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMoveMap message handlers

void CDlgMoveMap::OnButton1() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	g_pGMapX->MoveMap(this->m_dLon,this->m_dlan );
}

void CDlgMoveMap::OnButton2() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	g_pGMapX->SaveMapPoint( m_dLon, m_dlan,"¶¨Î»","",6);
}
