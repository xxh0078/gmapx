#pragma once
#include "VOSBase/VOSDefine.h"
#include "MapBase/MapDefine.h"
#include "MapDisp/MapDisp.h"
#include "MapCtrol/MapCtrl.h"
#include "MapOffSet/MapOffSet.h"
#include "mif/MifMan.h"
//xxh class CGmapxCtrl;
//extern fun_msg g_fun_msg;
class VOS_EXPORT CMapEngine
{
public:
	CMapEngine(void);
	~CMapEngine(void);
public:
	//初始化
	void Init( HWND hwnd );
	//设置消息回调函数
	void SetMsgFun( fun_msg msg );
	//设置地图URL路径
	void SetMapUrl(string strMapURL );
	//设置本地地图文件路径
	void SetMapPath( string strMapPath );
	//设置附件图层路径
	void OpenAddMapLayerPath( string strMapFilesPath );
	//关闭附加层
	void CloseAddMapLayer( );
	//释放
	void Destroy();
	//绘制
	void OnDraw( HDC hdc );
	//设置地图位置
	void SetMapPos( long left, long top, long width, long height, bool bDraw );
	//鼠标消息
	void OnLButtonDown( VOSPoint point );
	void OnLButtonUp( VOSPoint point);
	void OnMouseMove( VOSPoint point);
	void OnMouseWheel( short zDelta, VOSPoint point );
	void OnLButtonDblClk( VOSPoint point );

	//是否点击在poi点上
	bool IsPointIn( VOSPoint point, CMapPoi*& poi );
	//失去焦点
	void OnKillFocus();
	//ontimer
	void OnTimer( unsigned int nIDEvent);
	//缩小
	void OnMapZoomIn( );
	//放大
	void OnMapZoomOut( );

	/*	窗口的消息处理 */
	void MsgProc( ULONG ulID, ULONG wParam, ULONG lParam );
	//刷新屏幕
	void Invalidate();
	//检测点是否在地图上
	bool IsInMap( VOSPoint point );
	//加载mif数据
	bool LoadMifMidData( string strFileName );
	//设置地图显示
	long ShowMapTool(long lType, long lValue);
public:
	//添加图层,返回图层ID,要求new出来不释放
	long CreateMapLeyer();
	//删除图层
	bool DeleteMapLayer( int nID );
	//删除全部图层
	void DeleteAllMapLayer();
	//添加POI点
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID );
	//添加POI点
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName );
	//地图坐标转换为屏幕坐标
	void MapToScreen( double dMapX, double dMapY, long& lScreenX, long& lScreenY );
	//屏幕坐标转换为地图坐标
	void ScreenToMap( long lScreenX, long lScreenY, double& dMapX, double& dMapY );
	//移动地图到
	void MoveMap( double dMapX, double dMapY );
	//移动地图
	void MoveMapBound(double x1, double y1, double x2, double y2);
	//得到地图中心点坐标
	void GetMapCenter( double& dMapX, double& dMapY );
	//设置地图类型 
	void SetMapType( en_MapType eMapType = GMAP_GOOGLE_MAP );
	//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
	long CreateMapRes( string strpath );

	//创建点
	bool CreateMapPoint( long pointID );
	//创建点
	bool CreateMapPoint( long pointid, double x, double y, string strName, string strText, long icoID );
	//检测点是否在地图上的图层点上，并返回图层点ID
	long GetMapPoint( VOSPoint point );
	//设置点位置坐标
	bool SetMapPoint(long pointID, double x, double y);
	//设置点名称，直接显示
	bool SetMapPointName(long pointID, string name );
	//设置点显示文本,鼠标移入显示
	bool SetMapPointText(long pointID, string text );
	//设置点的图标
	bool SetMapPointICO(long pointID, long icoid );
	//删除点
	bool DeleteMapPoint(long pointID);
	//删除全部点信息
	void DeleteAllMapPoint();
	//创建线对象
	bool CreateMapLine( long lineID );
	//为线添加点
	bool AddMapLinePoint( long lineID, double x, double y );
	//设置线名称
	bool SetMapLineName( long lineID, string name );
	//设置线颜色：颜色值为BGR()0xFF0000为蓝色,0x00FF00为绿色,0x0000FF为红色
	bool SetMapLineColor( long lineID, long lineColor );
	//设置线宽度
	bool SetMapLineWidth( long lineID, long lineWidth );
	//删除线
	bool DeleteLine(long lineID);

	//创建多边形对象
	bool CreateMapPolygon(long polygonID );
	//添加点
	bool AddMapPolygonPoint( long polygonID, double x, double y );
	//设置多边形名字
	long SetMapPolygonName(long pid, const char* name );
	//设置多边形颜色
	long SetMapPolygonColor(long pid, long colorbgr);
	//删除多边形对象
	bool DeleteMapPolygon(long polygonID);

	//得到/设置地图显示比例尺
	long GetMapScale();
	void SetMapScale(long scale);
	//设置中心点位置和比例尺
	void SetMapParam(double x, double y, long scale);
	//自动跟踪并移动地图，在地图内部的，不移动地图，超出地图范围的，移动地图
	void AutoMoveMap(double x, double y);
	//绘制半圆
	void CreateMapAround( long rid, double x, double y, long radius, long alpha );
	//设置圆名字
	void SetMapAroundName(long rid, const char* name);
	long SetMapAroundColor(long rid, long colorbgr);
	void DeleteMapAround( long rid );
	//绘制文字
	void CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color);
	void DeleteMapText(long tid);
	//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
	//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
	//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	//删除所型疾?
	void RemoveAllLayer();
	//设置数据源,0为谷歌，7为virtual earth，8为超图，其他暂不支持
	long SetMapRes(long lres );
	//判断是否在地图显示范围内
	bool IsMapPointInMapCreen(double x, double y);
	//设置地图可编辑
	long OpenMapEdit(long type, long id, bool bedit);
	//设置地图工具，地图工具 1为方向测距 2为画线，3为画多边形，4为画巨型,5为画园
	bool SetMapTools(long MapToolType);
	//清楚地图工具以及所操作的地图
	void ClearMapTools();
	//保存工具
	void SaveMapTool();
	//是否显示地图工具栏
	void SetMapToolsBar( bool bShow );
	//注册程序
	long RegisterKey(char* strRegisterKey);

	//得到地图的纠偏数据值
	bool GetMapOffSet( double& lon, double& lan );
	void SetMapScaleBound(long minscale, long maxscale);
	//点是否在地图的多变型工具内
	bool IsInMapToolsPolygon( double dLon, double dLan );
	//根据坐标查询地址
	string GetMapAddress(double dLon, double dLan);
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
	//保存地图
	void SaveMap( const char* strPath );

	long SetMarkFile( const char* strFileName  );
public:
	HWND			m_hwnd;
	CMapCtrl		m_MapCtrl;				//地图控制按钮
	CMapDisp		m_MapDisp;
private:
	
	VOSRect			m_rect;
	HDC				m_memhdc;
	HBITMAP			m_bitmap;
	string			m_strRootPath;
	long			m_lCount;
	BITMAPINFO		bmp_info;
	void*			m_buf;
	agg::rendering_buffer m_rbuf;			//32位位图，每行字节数为width*4。
	CMapOffSet		m_MapOffSet;			//地图纠偏
	CMifMan			m_MifMan;
	//CMapPoi*		m_pSelMapPoi;			//当前被点击的信息点
	HBRUSH			m_hbr;
	CVOSImage		m_ImageMark;
};
