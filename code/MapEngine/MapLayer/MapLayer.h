#pragma once
#include "MapPoi.h"
#include "MapPoint.h"
#include "MapLine.h"
#include "MapAround.h"
#include "MapText.h"
#include "MapPolygon.h"
#define _MAX_MAP_POIT 1024
class VOS_EXPORT CMapLayer
{
public:
	CMapLayer(void);
	~CMapLayer(void);
public:
	//创建点对象
	bool CreatMapPoint( long pointid );
	bool CreatMapPoint( long pointid, double x, double y, string strName, string strText, short icoID );
	void SetMapPointTextColor( long pointID,long color );
	void SetMapPointTextOffset( long pointID,int x, int y);
	bool SetMapPointAngle( long pointID, long lAngle );
	//创建线对象
	bool CreatMapLine(short lineID );
	bool AddMapLinePoint( short lineID, MapPoint* pPoint );
	bool SetMapLineName( short lineID, string name );
	bool SetMapLineColor( short lineID, long lineColor );
	bool SetMapLineWidth( short lineID, long lineWidth );
	bool SetMapLineVisible( long lineID, long lVisible );
	//删除全部
	void RemoveAll();
	//绘制
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp,CMapPoiRes* pMapPoiRes );
	void OnDrawTip( HDC hdc,CMapDisp* pMapDisp );
	//检测
	bool IsPointIn( VOSPoint point,  CMapPoi*& poi );
	bool IsPointInDel( VOSPoint point,  int& type, int& id );
	bool IsPointIn( VOSPoint point );
	//设置是否显示
	void SetVisible( bool bVisible );
	//设置是否显示
	bool GetVisible( );

	//图层ID
	void SetLayerID( long lID );
	//得到图层ID
	long GetLayerID( );

	//得到编号ID的点
	CMapPoi* GetMapPoi( long lid );
	//删除一个点
	bool DeleteMapPoint(long pointID);
	//删除全部点信息
	void DeleteAllMapPoint();
	//删除一个线
	bool DeleteMapLine(long lineID);
	//绘制POI名字
	void DrawPoiText( long pointID, CMapDisp* pMapDisp );

	//绘制半圆
	bool CreateMapAround( long uid, double x, double y, long radius, long alpha );
	long SetMapAroundColor(long rid, long colorbgr);
	bool DeleteMapAround( long uid );
	//绘制文字
	bool CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color = RGB(0,0,0));
	bool DeleteMapText(long tid);
	//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
	//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
	//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);

	//创建多边形对象
	bool CreatMapPolygon(short polygonID );
	//添加点
	bool AddMapPolygonPoint( short polygonID, MapPoint* pPoint );
	//删除多边形对象
	bool DeleteMapPolygon(short polygonID);
	//
	CMapLine* GetMapLine(short lid);
	CMapPolygon* GetMapPolygon(short pid);

	//设置地图可编辑
	long OpenMapEdit( long type, long id, bool bedit);
	//设置多边形名字
	long SetMapPolygonName(long pid, const char* name );
	//设置多边形颜色
	long SetMapPolygonColor(long pid, long colorbgr);
	//设置圆名字
	void SetMapAroundName(long rid, const char* name );
protected:
	//CArray<CMapPoi*,CMapPoi*> m_arrPoi;
	list<CMapPoi*> m_arrPoi;
	list<CMapLine*> m_arrLine;
	list<CMapPolygon*> m_arrPolygon;
	list<CMapAround*> m_arrAround;
	list<CMapText*> m_arrMapText;
	HBRUSH		m_brushFont;
	bool		m_bVisible;
	long		m_llayerID;
};
