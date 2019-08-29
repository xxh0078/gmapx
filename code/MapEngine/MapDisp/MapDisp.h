#pragma once
#include "MapDataDown.h"
#include "../MapLayer/MapLeyerMan.h"
#include "MapDispLayer.h"
#include "../MapBase/MapUtil.h"
#define _EXTERND_WIDTH_HEIGHT_ 
class CMapDisp
{
public:
	CMapDisp(void);
	~CMapDisp(void);
public:
	//初始化
	void Init( HWND hwnd, HDC dcEngine, string strRootPath, en_MapType eMapType = GMAP_GOOGLE_MAP );
	//设置地图类型 
	void SetMapType( string strRoot, en_MapType eMapType, string strMapName = "", string strMapURL = "" );
	//设置本地地图路径
	void SetMapPath( string strMapPath );
	//设置附件图层路径
	void OpenAddMapLayerPath( string strMapFilesPath );
	//关闭附加层
	void CloseAddMapLayer( );
	//地图移动,参数偏移量
	void OnMoveMap( int iDx, int iDy );
	//地图放大
	void MapZoomIn( VOSPoint pt );
	void MapZoomIn();
	//地图缩小
	void MapZoomOut();
	//地图缩小
	void MapZoomOut( VOSPoint pt );

	//绘制地图
	void DrawMap( HDC hdc );
	//绘制地图
	void DrawMap2StretchDC();
	//窗口大小改变事件
	void OnSize( int cx, int cy );
	//鼠标消息
	void OnLButtonDown( VOSPoint point );
	void OnLButtonUp( VOSPoint point);
	void OnMouseMove( VOSPoint point);
	BOOL OnMouseWheel( short zDelta, VOSPoint pt);
	void OnLButtonDblClk( VOSPoint point );
	//当下载的时候
	void OnDownload( tDownLoadParam* param );
	void OnMapMove( VOSPoint point );
	void OnMapMove( int iDx, int iDy );
	//void OnMapZoomIn( int iZoomLevel,CPoint pt );
	//	void OnMapZoomOut( int iZoomLevel,CPoint pt );

	void OnMapZoomIn( );
	void OnMapZoomOut( );
	void OnMapZoom();
	void OnKillFocus();
	//
	void OnTimer( unsigned int nIDEvent);
	//刷新屏幕
	void Invalidate();
	//
	void realse();
public:
	//移动地图到指定的点
	void MoveMap( MapPoint mpt );

	//移动地图到指定的点
	void MoveMap( MapPoint mpt,long level );

	//设置地图比例尺
	void SetMapLevel( long level);

	//移动地图到一个区域范围
	void MoveMapBound( double x1, double y1, double x2, double y2 );
	//得到地图比例尺
	long GetMapLevel();

	//设置地图默认位置
	void SetMapDefault();

	//得到地图中线点坐标
	void GetMapCenter( MapPoint& mpt );
	
	//地图坐标转换为屏幕坐标
	void MapToScreen( MapPoint mpt, VOSPoint& pt );

	//屏幕坐标转换为地图坐标
	void ScreenToMap( VOSPoint pt, MapPoint& mpt );

	//得到MapBound
	MapBount*	GetMapBound();

	//检查坐标是否在屏幕内
	bool IsMapPointInMapCreen( MapPoint pt );
	//获取显示图层
	CMapDispLayer* GetMapDispLayer( int iMapID );

	//发送消息
	void PostMessageEx( unsigned long message,unsigned long param1, unsigned long param2 );

	//注册程序
	long RegisterKey(char* strRegisterKey);
	//设置比例尺
	void SetMapScaleBound(long minscale, long maxscale);
private:

	//设置MapBound
	void SetMapBound();

	//设置MapBound
	void SetMapBound( MapPoint ptlt, MapPoint ptrb );

	//绘制光标
	//void DrawCursor(CDC* pDC, CPoint pt, float fZoom );

	//检查地图是否出界，出界的给改到正确位置
	bool CheckAndSetMapCenter();

	//获得地图中心点坐标
	MPoint* GetMapCenter();
	
private:
	bool			m_bFlagMoveMap;
	bool			m_bMapAutoMove;
	bool			m_bFlagMoveLayerPoint;
	tagZoomParam	m_ZoomParam;
	VOSPoint		m_pntStart;
	VOSPoint		m_pntSpeed;
	int				m_iSpeedX;
	int				m_iSpeedY;

	long			m_ulSpeedTickCount;	
	long			m_lMapMoveTickCount;
	//CBitmap*		m_bitmap;
	HBITMAP			m_bitmap;
	HDC				m_memDC;
	//CDC*			m_memDC;

	//	CBitmap*		m_bitmapStretch;
	HBITMAP			m_bitmapStretch;
	HDC				m_memDCStretch;
	//	CDC*			m_memDCStretch;
	//MPoint			m_gptMapCenter;
	MPoint			m_MapCenter20;
	
	//	CDownLoad		m_download;
	//CWnd*			m_pWnd;
	HPEN			m_penBg;
	HBRUSH			m_brushBg;
	HDC				m_dcEngine;

//	bool			m_bCanUsed;//使用限制
	HBRUSH			m_hbr;

	BITMAPINFO		bmp_info;
	agg::rendering_buffer m_rbuf; // 32位位图，每行字节数为width*4。
public:
	CMapLeyerMan	m_MapLayerMan;			// 地图图层管理类
	CMapDispLayer	m_MapDispLayer;			// 地图显示图层管理
	CMapDispLayer*	m_pMapDispLayerMark;	// 叠加图层,谷歌影像图的时候才创建
	VOSRect			m_rcWnd;
	int				m_iLevel;
	HWND			m_hwnd;
	en_MapType	    m_enMapType;
	MapBount		m_MapBound;
	long			m_maxLevel;		//最大比例尺
	long			m_minLevel;		//最小比例尺
	HCURSOR			m_hCursor;		//手形光标
	//CMapActive		m_MapActive;
};
