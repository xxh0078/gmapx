#include "stdafx.h"
#include "JMCoolMenu.h"

#define RGB_BUTTON_BLACK    (GetSysColor(COLOR_WINDOWFRAME))
#define RGB_BUTTON_WHITE    (GetSysColor(COLOR_BTNHIGHLIGHT))
#define RGB_BUTTON_LIGHT    (GetSysColor(COLOR_BTNFACE))
#define RGB_BUTTON_DARK     (GetSysColor(COLOR_BTNSHADOW))
#define RGB_MENU_FACE       (GetSysColor(COLOR_MENU))
#define RGB_MENUTEXT_BACK   (GetSysColor(COLOR_HIGHLIGHT))
#define RGB_MENU_TEXT       (GetSysColor(COLOR_MENUTEXT))

CJMCoolMenu::CJMCoolMenu()
{

	m_clrHilight		= ::GetSysColor(COLOR_HIGHLIGHT);
    m_clrNormalText	    = ::GetSysColor(COLOR_WINDOWTEXT);
    m_clrHilightText	= ::GetSysColor(COLOR_HIGHLIGHTTEXT);
    m_clrBkgnd			= ::GetSysColor(COLOR_MENU);
	m_pImageList = NULL;
	//CreatePopupMenu(); 
	

}


CJMCoolMenu::~CJMCoolMenu()
{
	int i;
	STRMENUINFO* pInfo; 
	if ( m_pImageList != NULL )
		delete m_pImageList;
	DestroyMenu();
    for ( i = m_MenuInfo.GetSize()-1 ; i>=0 ; i-- )
	{
		pInfo = (STRMENUINFO*)m_MenuInfo.GetAt(i);
		delete pInfo;
	}
	m_MenuInfo.RemoveAll(); 
    
}

void CJMCoolMenu::SetImageList(CImageList *pImageList)
{

	m_pImageList = pImageList;
}

void CJMCoolMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC   = ::CDC::FromHandle(lpDrawItemStruct->hDC );
	CRect RC   = lpDrawItemStruct->rcItem;
	UINT iState = lpDrawItemStruct->itemState;
	int iItemID  = lpDrawItemStruct->itemID; 
	CRect rcImage,rcText;
	CString strText;
	CPoint pt;
	STRMENUINFO* pInfo; 
    
	rcImage = RC; 
	rcImage.right = RC.left + 16;
	rcText = RC;
	rcText.left = rcImage.right + 10;

	
	pDC->SetBkMode( TRANSPARENT ); 
    if ( iState & ODS_SELECTED  )
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
		pDC->FillSolidRect(&RC, m_clrBkgnd );
		pDC->SetTextColor( m_clrNormalText );	
    }
	
   if( iItemID >= 0 )
	{
		 
	   for ( int i = 0 ; i < m_MenuInfo.GetSize(); i++ )
	   {	   
	        pInfo = m_MenuInfo.GetAt(i);
			if ( pInfo->MenuID == (long)iItemID )
			{	
		   
				if ( m_pImageList != NULL )
				{
					if (pInfo->ImageIndex >= 0 && pInfo->ImageIndex < m_pImageList->GetImageCount())
					{	
						pt = RC.TopLeft();
						pt.Offset(5,5);
						m_pImageList->Draw(pDC,pInfo->ImageIndex,pt,ILD_TRANSPARENT);
					}		
				}
			    strText = pInfo->csTitle;
		        pDC->DrawText(strText, rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			    break;
			}
		}
	}



}


void CJMCoolMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{

	lpMeasureItemStruct->itemHeight = 20;
	lpMeasureItemStruct->itemWidth = 100; 
}

void CJMCoolMenu::AddMenuInfo(STRMENUINFO* pInfo)
{
	
	 if ( pInfo == NULL )
		 return;
	 m_MenuInfo.Add(pInfo );  


}

