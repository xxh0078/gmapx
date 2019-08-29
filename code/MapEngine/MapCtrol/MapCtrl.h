#pragma once
#include "MapWnd.h"
#include "MapButton.h"
#include "SlideButton.h"
#include "UrlLink.h"
#include "../MapDisp/MapDisp.h"
//#include "../MapEngine.h"
#include "MapDirRule.h"
#include "MapSymbolEdit.h"
#include "MapToolLine.h"
#include "MapToolPolygon.h"
#include "MapToolRect.h"
#include "MapToolAround.h"
#include "MarkMapPoint.h"
class CMapEngine;
class CMapCtrl : public CMapWnd
{
public:
	CMapCtrl(void);
	~CMapCtrl(void);
	//初始化资源文件根目录
	bool Init( CMapEngine* pMapEngine, vchar* pRootPath, HWND hwnd , long left, long top );
	//设置rc
	void SetMapRect( VOSRect& rcWnd );
	//绘制
	void OnDraw( HDC hdc,agg::rendering_buffer* rbuf  );
	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//
	void CheckAndSetMapLevel( VOSPoint point );
	void OnMoveOut();

	//设置地图工具，地图工具 1为方向测距 2为画线，3为画多边形，4为画巨型,5为画园,6为标记点
	bool SetMapTools(long MapToolType);
	//清楚地图工具以及所操作的地图
	void ClearMapTools();
	//是否显示
	void SetMapToolsBar( bool bShow );
	//设置比例尺
	void SetMapScaleBound(long minscale, long maxscale);

	//命令
	void OnCommand( int id, int param1,int param2 );

	//地图缩放功能
	void OnMapZoom( ); 
	//保存工具
	void SaveMap();
	//
	void SetVisible( bool bVisible );
	void SetVisible1( bool bVisible );
private:
	//设置CtrlButton基准位置 
	void SetBasePos( long left, long top );
private:
	CMapEngine* m_pMapEngine;
	//地图显示
	CMapDisp*	m_pMapDisp;
	//控件
	CMapButton	m_btnLeft;
	CMapButton	m_btnRight;
	CMapButton	m_btnUp;
	CMapButton	m_btnDown;
	//CMapButton	m_btnCenter;
	CMapButton	m_btnZoomIn;
	CMapButton	m_btnZoomOut;
	CSlideButton	m_btnZoomBk;
//	CMapButton	m_btnZoomMove;
	//测距工具
	CMapButton	m_btnRule;
//	CMapButton	m_btnMapRect;
//	CMapButton	m_btnLine;
//	CMapButton	m_btnPolygon;
//	CMapButton	m_btnSymbol;
	CMapButton	m_btnClean;
//	CMapButton	m_btnMapSat;

#ifdef GMAP_VIEW_QQ
	CUrlLink	m_urlDemo;
#endif
#ifdef GMAP_VIEW_URL
	CUrlLink	m_urlCopyRight;
//	CMapButton	m_btnCopyRight;
#endif
	//拖动
	long		m_left;
	long		m_top;
	long		m_interval;		//位置间隔
	VOSRect*	m_pRectBk;		//滚动背景区域
	long		m_level;		//比例尺
	long		m_maxLevel;		//最大比例尺
	long		m_minLevel;		//最小比例尺
	bool		m_flagMove;
	//
	
	//
	VOSRect		m_rcWnd;
//	CArray<CMapButton*,CMapButton*> m_ArrMapCtrl;
	CMapLayer*  m_pMapLayer;
//	long		m_lLayerID;
	long		m_lLineIDRule;	//测距线编号
	//工具标志,0，无工具状态，1：方向测距工具,2，画线，2画多边形
	int				m_iFlagTools;
	CMapDirRule		m_mapDirRule;
	VOSPoint		m_pntMouse;

//	bool			m_bMapSat;		//是否是卫星地图
public:
	CMapToolLine	m_MapToolLine;
	CMapToolPolygon m_MapToolPolygon;
	CMapToolRect	m_MapToolRect;
	CMapToolAround	m_MapToolAround;
	CMapButton*		m_pButtonCurr;
	//CVOSImage		m_ImageMark;
	CMarkMapPoint	m_MarkMapPoint;
	CVOSImage		m_ImageDel;

	bool			m_bVisible;
	bool			m_bVisible1;
};
