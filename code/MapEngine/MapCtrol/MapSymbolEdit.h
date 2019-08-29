// MapSymbolEdit.h: interface for the CMapSymbolEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPSYMBOLEDIT_H__B3BCE485_ABC7_4E96_B738_E0C95FC50355__INCLUDED_)
#define AFX_MAPSYMBOLEDIT_H__B3BCE485_ABC7_4E96_B738_E0C95FC50355__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapEdit.h"
#include "MapComBox.h"

#include "../VOSBase/VOSBase.h"
class CMapSymbolEdit  
{
public:
	CMapSymbolEdit();
	virtual ~CMapSymbolEdit();
	void Create( int left,int top, int width,int height,HWND hWndParent );
	void SetPos( int left,int top);
	virtual void DestroyWnd() ;
	void OnDraw(HDC hdc);
	void SetVisible(bool visible );
	//单击属性
	bool IsPointIn( VOSPoint point );
	//是否显示
	bool IsVisible();
private:
	VOSRect	m_rect;
	HWND  m_hWndParent;
	HBRUSH m_hbr;
	//是否可见
	bool  m_bVisible;
	//
	CMapEdit m_MapEditName;
	CMapEdit m_MapEditPinyin;
	CMapEdit m_MapEditAddress;
	CMapEdit m_MapEditPhone;
	CMapEdit m_MapEditCityCode;
	CMapEdit m_MapEditClassCode;
};

#endif // !defined(AFX_MAPSYMBOLEDIT_H__B3BCE485_ABC7_4E96_B738_E0C95FC50355__INCLUDED_)
