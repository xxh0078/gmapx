// MapPoi.h: interface for the CMapPoi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_)
#define AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MapPoiRes.h"
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class VOS_EXPORT CMapPoi
{
public:
	CMapPoi();
	virtual ~CMapPoi();

	//设置资源ID
	void SetResID( short sResID );

	//设置POIID
	void SetPOIID( short sPOIID );

	//设置POIName
	void SetPoiName( string strName );

	//设置POI文本说明
	void SetPoiText( string strText );

	//设置POIPoint
	void SetMapPoint( double dMapX, double dMapY );

	//设置POIPoint
	void SetMapPoint( MapPoint* Point );
	
	void SetMapAngle( long lAngle);
	//绘制
	void OnDraw( HDC hdc, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes );

	//绘制POIName
	void DrawPoiName( HDC hdc, CMapDisp* pMapDisp );

	//设置名字
	void SetPoiNameVisible( bool bVisible = false );

	//绘制POIName
	void DrawPoiText( HDC hdc , CMapPoiRes* pMapPoiRes );

	//绘制删除按钮
	void DrawDelBtn( HDC hdc , CMapPoiRes* pMapPoiRes );

	//单击属性
	bool IsPointIn( VOSPoint point );
	bool IsPointInDel( VOSPoint point );
	//设置long color
	void SetMapTextColor( long color );
	void SetMapTextOffset( int x, int y );

	//设置地图可编辑
	void OpenEdit( bool bEdit );
public:
	en_PoiType	m_ePoiType;
	MapPoint	m_Point;
	short		m_sResID;
	long		m_sPOIID;
	string		m_strPoiName;
	string		m_strText;
	VOSRect		m_rc;
	VOSRect		m_rcDelBtn;
	int			m_iTextOffsetX;
	int			m_iTextOffsetY;
	long		m_lTextColor;
	bool		m_bDrawPoiName;
	bool		m_bEdit;
	long		m_lAngle;
};

#endif // !defined(AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_)
