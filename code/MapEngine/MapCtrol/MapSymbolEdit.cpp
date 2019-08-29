// MapSymbolEdit.cpp: implementation of the CMapSymbolEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapSymbolEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapSymbolEdit::CMapSymbolEdit()
{

}

CMapSymbolEdit::~CMapSymbolEdit()
{

}
void CMapSymbolEdit::Create( int left,int top, int width,int height,HWND hWndParent )
{
	this->m_rect.left = left;
	this->m_rect.top = top;
	this->m_rect.right = left+width;
	this->m_rect.bottom = top+height;
	m_hWndParent = hWndParent;
	m_hbr = CreateSolidBrush(RGB(255,255,255));
	m_MapEditName.Create( left+10,top+30,200,30,m_hWndParent);
	m_MapEditPinyin.Create( left+10,top+70,200,30,m_hWndParent);

	m_MapEditAddress.Create( left+10,top+110,200,30,m_hWndParent);
	m_MapEditPhone.Create( left+10,top+150,200,30,m_hWndParent);
	m_MapEditCityCode.Create( left+10,top+190,200,30,m_hWndParent);
	m_MapEditClassCode.Create( left+10,top+230,200,30,m_hWndParent);
	/*
	HWND hwndEdit=CreateWindow("edit",NULL,
	WS_CHILD|WS_VISIBLE|WS_BORDER,
	20,70,100,25,m_pMapEngine->m_hwnd,NULL,NULL,NULL);
	  HWND hButton=CreateWindow("button","确定",
	WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
	350,70,80,25,m_pMapEngine->m_hwnd,NULL,NULL,NULL);
	  */
}
void CMapSymbolEdit::SetPos( int left,int top)
{
	int width = m_rect.width();
	int height = m_rect.height();
	this->m_rect.left = left;
	this->m_rect.top = top;
	this->m_rect.right = left+width;
	this->m_rect.bottom = top+height;
	m_MapEditName.SetPos( left+10,top+30 );
	m_MapEditPinyin.SetPos( left+10,top+70 );

	m_MapEditAddress.SetPos( left+10,top+110 );
	m_MapEditPhone.SetPos( left+10,top+150 );
	m_MapEditCityCode.SetPos( left+10,top+190 );
	m_MapEditClassCode.SetPos( left+10,top+230 );
}
void CMapSymbolEdit::OnDraw(HDC hdc)
{
	if( m_bVisible )
	{
		::FillRect( hdc,&m_rect,m_hbr);
	}
}
void CMapSymbolEdit::SetVisible(bool visible )
{
	m_MapEditName.SetVisible( visible );
	m_MapEditPinyin.SetVisible( visible );
	m_MapEditAddress.SetVisible( visible );
	m_MapEditPhone.SetVisible( visible );
	m_MapEditCityCode.SetVisible( visible );
	m_MapEditClassCode.SetVisible( visible );
	m_bVisible = visible;
}
//单击属性
bool CMapSymbolEdit::IsPointIn( VOSPoint point )
{
	return this->m_rect.IsPointIn( point );
}
void CMapSymbolEdit::DestroyWnd()
{
	
}
//是否显示
bool CMapSymbolEdit::IsVisible()
{
	return this->m_bVisible;
}
