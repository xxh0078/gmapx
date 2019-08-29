// InputBox.cpp : implementation file
//

#include "stdafx.h"
#include "gmapx.h"
#include "InputBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputBox dialog
CString CInputBox::m_strInputText = "";
CInputBox::CInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(CInputBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputBox)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputBox)
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputBox, CDialog)
	//{{AFX_MSG_MAP(CInputBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputBox message handlers

void CInputBox::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData();
	CInputBox::m_strInputText = this->m_strText;
	CDialog::OnOK();
}

CString CInputBox::GetInputText()
{
	return CInputBox::m_strInputText;
}

void CInputBox::OnCancel() 
{
	// TODO: Add extra cleanup here
	CInputBox::m_strInputText = "";
	CDialog::OnCancel();
}
