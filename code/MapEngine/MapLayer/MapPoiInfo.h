// MapPoiInfo.h: interface for the CMapPoiInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_)
#define AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include "MapPoi.h"
class CMapDisp;
class CMapPoiInfo  
{
public:
	CMapPoiInfo();
	virtual ~CMapPoiInfo();
	//初始化
	void Init( CMapDisp* pMapDisp, const char* strPath );
	//绘制
	void Draw( HDC hdc, CMapDisp* pMapDisp );

	//设置地图POI信息
	void SetPoiInfo( CMapPoi* pPOI );
	
	//单击属性
	bool IsPointIn( VOSPoint point );

	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);

	//关闭
	void Close();
public:
	CMapPoi*	m_pPOI;
	CVOSImage	m_image;
	CMapDisp*	m_pMapDisp;
	VOSRect		m_rect;			//信息显示窗口位置
	VOSRect		m_rcClose;		//关闭按钮位置
	VOSRect		m_rcText;		//文本显示区域
	/*
	string		m_strText;		//鼠标移动显示
	MapPoint	m_Point;		//
	bool		m_bDraw;		//	
	short		m_poiid;
	CMapPoiRes*	m_pMapPoiRes;
	bool		m_bFirstSHow;
	*/
};

#endif // !defined(AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_)
