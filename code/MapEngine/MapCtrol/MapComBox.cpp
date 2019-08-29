// MapComBox.cpp: implementation of the CMapComBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapComBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapComBox::CMapComBox()
{

}

CMapComBox::~CMapComBox()
{

	
}
void CMapComBox::Create( int left,int top, int width,int height,HWND hWndParent )
{
	m_iLeft = left;
	m_iTop = top;
	m_iWidth= width;
	m_iHeight = height;
	m_hWnd  =CreateWindow(( "ComboBoX "), 
	( "combo1 "), 
	WS_CHILD   |   WS_VSCROLL   |   WS_VISIBLE   |   CBS_DROPDOWNLIST   |   CBS_HASSTRINGS     , 
	left,top,width,height, 
	hWndParent,NULL, 
	NULL,NULL); 

/*	::ShowWindow(m_hWnd,SW_SHOW); 


	((CComboBox*)FromHandle(   m_hWnd   )   )-> AddString(   "aaaaa "   )   ; 
	((CComboBox*)FromHandle(   m_hWnd   )   )-> AddString(   "bbbbb "   )   ; 
	((CComboBox*)FromHandle(   m_hWnd   )   )-> AddString(   "cccccc "   )   ; 

	((CComboBox*)FromHandle(   m_hWnd   )   )-> SetTopIndex(   10     )   ;*/
}
void CMapComBox::SetVisible(bool visible )
{
	if(visible )
		::ShowWindow( m_hWnd,SW_SHOW);
	else
		::ShowWindow( m_hWnd,SW_HIDE);
}