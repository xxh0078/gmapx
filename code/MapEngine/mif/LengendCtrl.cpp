// LengendCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "LengendCtrl.h"
#include "MapRender.h"
#include "DlgMapUnique.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLengendCtrl

CLengendCtrl::CLengendCtrl()
{
	 m_clrHilight		= ::GetSysColor(COLOR_HIGHLIGHT);
     m_clrNormalText	= ::GetSysColor(COLOR_WINDOWTEXT);
     m_clrHilightText	= ::GetSysColor(COLOR_HIGHLIGHTTEXT);
     m_clrBkgnd			= ::GetSysColor(COLOR_MENU);

}

CLengendCtrl::~CLengendCtrl()
{
}


BEGIN_MESSAGE_MAP(CLengendCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CLengendCtrl)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLengendCtrl message handlers

void CLengendCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC   = ::CDC::FromHandle(lpDrawItemStruct->hDC );
	CRect RC   = lpDrawItemStruct->rcItem;
	UINT iState = lpDrawItemStruct->itemState;
	int iItemID  = lpDrawItemStruct->itemID; 
	int iWidth[2];
	CRect rcColor,rcButton,rcText;
	CString csText;
	COLORREF clr;
    CDlgMapUnique *pDlg = (CDlgMapUnique*)GetParent();
	
	if ( iItemID >= 0 && iItemID  < GetItemCount())
	{	
		RENDERINFO* pInfo = pDlg->m_pRender->GetByIndex(iItemID);
	
		clr = pInfo->clr;
		iWidth[0] = GetColumnWidth(0);
		iWidth[1] = GetColumnWidth(1);
		rcText = RC;
		rcText.right = rcText.left  + iWidth[0]; 
		rcColor = RC;
		rcColor.left = rcText.right + 1;
		rcColor.right = rcColor.left + GetColumnWidth(1) - 20;
		rcButton = RC;
		rcButton.left = rcColor.left + GetColumnWidth(1) - 20;
		csText = GetItemText(iItemID,0);
		pDC->TextOut( rcText.left+4,rcText.top,csText);
		pDC->FillSolidRect(&rcColor,clr);
		pDC->MoveTo(rcColor.left,rcColor.top);
		pDC->LineTo(rcColor.right,rcColor.top);
		pDC->LineTo(rcColor.right,rcColor.bottom);  
		pDC->FillSolidRect(&rcButton,m_clrBkgnd); 
		pDC->Draw3dRect(&rcButton,::GetSysColor(COLOR_BTNHILIGHT),::GetSysColor(COLOR_BTNSHADOW)); 
		pDC->SetPixel(rcButton.left + 5 , rcButton.top + 5 ,RGB(0,0,0)); 
		pDC->SetPixel(rcButton.left + 10 , rcButton.top + 5 ,RGB(0,0,0));
		pDC->SetPixel(rcButton.left + 15 , rcButton.top + 5 ,RGB(0,0,0));
		
	}

	
}

void CLengendCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or ll default
	
}	

BOOL CLengendCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	/*cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED;*/
	
	return CListCtrl::PreCreateWindow(cs);
}

void CLengendCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int i,iCount;
	CString csValue;
    CRect rcHot; 
	COLORREF clr;
	RENDERINFO* pInfo;

	iCount = GetItemCount();
		
	for ( i = 0 ; i < iCount ; i++ )
	{
		GetItemRect(i,&rcHot,LVIR_BOUNDS);
		rcHot.left = rcHot.right - 20;
		if ( rcHot.PtInRect(point ))
		{
			CColorDialog dlgColor(0,CC_FULLOPEN|CC_RGBINIT,this);
			if ( dlgColor.DoModal() == IDOK )
            {  
				clr = dlgColor.GetColor();
				CDlgMapUnique *pDlg = (CDlgMapUnique*)GetParent(); 
	            pInfo = pDlg->m_pRender->GetByIndex(i);
			    pInfo->clr = clr; 
		        rcHot.left = GetColumnWidth(0);
				rcHot.right = rcHot.right - 20;
				InvalidateRect(&rcHot,TRUE);
			}	
	        break;
        }    

    }    
	CListCtrl::OnLButtonDblClk(nFlags, point);
}
