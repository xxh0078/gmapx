// DlgMapText.cpp : implementation file
//

#include "stdafx.h"
#include "gmapx.h"
#include "DlgMapText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapText dialog


CDlgMapText::CDlgMapText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMapText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMapText)
	m_strText = _T("");
	m_fLon = 0.0f;
	m_fLan = 0.0f;
	m_lFontSize = 0;
	m_lBGRColor = 0;
	//}}AFX_DATA_INIT
}


void CDlgMapText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapText)
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	DDV_MaxChars(pDX, m_strText, 30);
	DDX_Text(pDX, IDC_EDIT2, m_fLon);
	DDV_MinMaxFloat(pDX, m_fLon, -180.f, 180.f);
	DDX_Text(pDX, IDC_EDIT3, m_fLan);
	DDV_MinMaxFloat(pDX, m_fLan, -90.f, 90.f);
	DDX_Text(pDX, IDC_EDIT4, m_lFontSize);
	DDV_MinMaxLong(pDX, m_lFontSize, 0, 64);
	DDX_Text(pDX, IDC_EDIT5, m_lBGRColor);
	DDV_MinMaxLong(pDX, m_lBGRColor, 0, 16777215);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMapText, CDialog)
	//{{AFX_MSG_MAP(CDlgMapText)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapText message handlers

void CDlgMapText::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMapText::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}
