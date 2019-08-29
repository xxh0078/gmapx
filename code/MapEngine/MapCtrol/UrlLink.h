// UrlLink.h: interface for the CUrlLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_URLLINK_H__5FD16372_9579_4A35_9A55_4B4D6B63E40B__INCLUDED_)
#define AFX_URLLINK_H__5FD16372_9579_4A35_9A55_4B4D6B63E40B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "MapCtrol.h"
class CUrlLink  :public  CMapCtrol
{
public:
	CUrlLink();
	virtual ~CUrlLink();
public:
	void SetText( string strText );
	void SetUrl( string strUrl );
	void setPos(short sLeft, short sTop);
	void SetColor( long bgr );
	void OnDraw( HDC hdc );
	//单击属性
	bool IsPointIn( VOSPoint point );
	//单击属性
	void OpenURL();
private:
	string	m_strUrl;
	string	m_strText;
	short	m_sFontSize;
	long	m_lColor;
};

#endif // !defined(AFX_URLLINK_H__5FD16372_9579_4A35_9A55_4B4D6B63E40B__INCLUDED_)
