// MapLeyerMan.h: interface for the CMapLeyerMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_)
#define AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "../MapDisp/MapDisp.h"
//#include "MapPoiRes.h"
#include "MapLayer.h"
#include "BackLayer.h"
#include "MapPoiInfo.h"
#define _MAX_MAP_LAYER_ 2
class CMapLeyerMan  
{
public:
	CMapLeyerMan();
	virtual ~CMapLeyerMan();

	//初始化
	bool Init( CMapDisp* pMapDisp, string strRootPath );
	void Realse();
	//添加图层
	long AddMapLayer( CMapLayer* pMapLayer );

	//删除图层
	bool DeleteMapLayer( int nID );

	//设置图层是否显示
	bool SetMapLayerVisible( int nID, bool bVisible );

	//删除图层
	void DeleteMapLayer( CMapLayer* pMapLayer );

	//添加涂层点
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID );

	//添加涂层点
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName );

	//删除全部图层
	void ClearAllMapLayer();

	//绘制
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf );

	//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
	long CreateRes( string strpath );
	//创建点对象
	bool CreatMapPoint(long id );
	bool CreatMapPoint( long pointid, double x, double y, string strName, string strText, long icoID );
	bool SetMapPoint(long pointID, double x, double y);
	bool SetMapPointName(long pointID, string name );
	bool SetMapPointText(long pointID, string text );
	void SetMapPointTextColor( long pointID,long color );
	void SetMapPointTextOffset( long pointID,int x, int y);
	bool SetMapPointAngle( long pointID, long lAngle );

	bool SetMapPointICO(long pointID, long icoid );
	bool DeleteMapPoint(long pointID);
	//删除全部点信息
	void DeleteAllMapPoint();
	//创建线对象
	bool CreatMapLine(long lineID );
	bool AddMapLinePoint( long lineID, double x, double y);
	bool AddMapLinePoint( long lineID, MapPoint Point );
	bool SetMapLineName( long lineID, string name );
	bool SetMapLineColor( long lineID, long lineColor );
	bool SetMapLineWidth( long lineID, long lineWidth );
	bool SetMapLineVisible( long lineID, long lVisible );
	bool DeleteLine(long lineID);

	//创建多边形对象
	bool CreatMapPolygon(long polygonID );
	//添加点
	bool AddMapPolygonPoint( long polygonID, double x, double y );
	//删除多边形对象
	bool DeleteMapPolygon(long polygonID);

	//绘制半圆
	void CreateMapAround( long uid, double x, double y, long radius, long alpha );
	long SetMapAroundColor(long rid, long colorgbr);
	void DeleteMapAround( long uid );
	//绘制文字
	void CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color);
	void DeleteMapText(long tid);
	//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
	//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
	//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	
	//响应鼠标移动事件
//	bool IsPointIn( VOSPoint point );

	//点击处理，检测是否击中图层，如果击中，检测是否是，是返回poiid，不是，返回poid为-1
	//bool OnClick( VOSPoint point, CMapPoi*& poi );
	//检测点是否在poi点上
	bool IsPointIn( VOSPoint point, CMapPoi*& poi );

	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnMouseWheel( short zDelta, VOSPoint pt);
	bool OnLButtonDblClk( VOSPoint point );

	//添加地图信息点
	bool SaveLocMapPoint( double x, double y, string strName, string strText, long icoID );
	//添加地图线,
	bool SaveLocMapLine( string strMapPoints, string strName, long width, long bgrcolor  );
	//添加地图文本信息
	bool SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor );
	//清除地图保存信息
	bool ClearLocMapData();
	//删除一个点
	bool DeleteLocMapPoint(long pointID);
	//删除一个线
	bool DeleteLocMapLine(long lineID);
	//得到当前位置的信息ID,0为无数据，1为点信息，2为线信息
	int GetLocID( long& lID, VOSPoint point );
	//设置地图可编辑
	long OpenMapEdit(long type, long id, bool bedit);
	//设置多边形名字
	long SetMapPolygonName(long pid, const char* name  );
	//设置多边形颜色
	long SetMapPolygonColor(long pid, long colorbgr);
	//设置圆名字
	void SetMapAroundName(long rid, const char* name );
public:
	CBackLayer	m_backLayer;
	CMapPoiRes	m_MapPoiRes;
private:
	CMapDisp*	m_pMapDisp;
	vector<CMapLayer*>	m_arrMapLayers;
	CMapPoiInfo	m_MapPoiInfo;
	CMapLayer	m_userLayer;
	long		m_lmaxID;
	HCURSOR		m_hCursor;		//手形光标
	
	CMapPoi*	m_pLastPoi;
	bool		m_bDown;
public:
	CMapLayer	m_ToolsLayer;
	CVOSImage	m_ImageBk;
};

#endif // !defined(AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_)
