// MapText.h: interface for the CMapText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_)
#define AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class CMapText  
{
public:
	CMapText();
	virtual ~CMapText();
	void Draw( HDC hdc, CMapDisp* pMapDisp );
	//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
	//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
	//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
	bool SetMapTextFont(long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	long		tid;
	MapPoint	m_Point;
	string		text;
	long		color;//gbr
	long		m_size;
	long		m_width;
	long		m_escapement;
	long		m_orientation;
	long		m_weight;
	long		m_Italic;
	long		m_underline;
	long		m_strikeOut;
	LPCTSTR		m_fontname;

};

#endif // !defined(AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_)
