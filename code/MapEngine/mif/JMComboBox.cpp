// JMComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMap.h"
#include "JMComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJMComboBox

CJMComboBox::CJMComboBox()
{
 	 m_dwStyle = CBS_OWNERDRAWFIXED|CBS_DROPDOWNLIST|CBS_SIMPLE|WS_VSCROLL\
		         |CBS_NOINTEGRALHEIGHT| WS_BORDER |WS_VISIBLE| WS_CHILD;
	 m_clrHilight		= ::GetSysColor(COLOR_HIGHLIGHT);
     m_clrNormalText	= ::GetSysColor(COLOR_WINDOWTEXT);
     m_clrHilightText	= ::GetSysColor(COLOR_HIGHLIGHTTEXT);
     m_clrBkgnd			= ::GetSysColor(COLOR_MENU);


}

CJMComboBox::~CJMComboBox()
{
}


BEGIN_MESSAGE_MAP(CJMComboBox, CComboBox)
	//{{AFX_MSG_MAP(CJMComboBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMComboBox message handlers

void CJMComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC *pDC   = ::CDC::FromHandle(lpDrawItemStruct->hDC );
	CRect RC   = lpDrawItemStruct->rcItem;
	int iState = lpDrawItemStruct->itemState;
	int iItemID  = lpDrawItemStruct->itemID; 
    CString strText;   
	
	pDC->SetBkMode( TRANSPARENT ); 
    if ( iState == ODS_SELECTED  )
	{
		if ( RC.left != 0 )
		{
			pDC->FillSolidRect(&RC , m_clrBkgnd );
			pDC->SetTextColor(m_clrNormalText); 
		}
		else
        {
			pDC->FillSolidRect(&RC , m_clrHilight );
			pDC->SetTextColor(m_clrHilightText); 	
        } 
	}
	else
    {
		pDC->FillSolidRect( &RC, m_clrBkgnd );
		pDC->SetTextColor( m_clrNormalText );	
    }
	
	if( iItemID >= 0 )
	{
		
		GetLBText( iItemID, strText );
		pDC->DrawText(strText, RC, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
}

void CJMComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if( lpMeasureItemStruct->itemID != unsigned( -1 ) )
	{	
		lpMeasureItemStruct->itemHeight = 16;
		lpMeasureItemStruct->itemWidth = 100;
	}
}

int CJMComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style  = m_dwStyle;  
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CJMComboBox::OnDestroy() 
{
	CComboBox::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CJMComboBox::OnSysColorChange() 
{
	CComboBox::OnSysColorChange();
	
	/*m_clrHilight = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	m_clrShadow	= ::GetSysColor(COLOR_BTNSHADOW);
	m_clrNormal	= ::GetSysColor(COLOR_BTNFACE);*/
	
}
