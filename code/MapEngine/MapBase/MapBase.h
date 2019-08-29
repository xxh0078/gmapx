#pragma once
#include "../VOSBase/VOSDefine.h"
#include "MapDefine.h"

#define _BLOCK_SIZE 512

#define _LEVEL3_X	90
#define _LEVEL3_Y	40

#define _LEVEL4_X	45
#define _LEVEL4_Y	20

#define _BLOCK_MAX_NUM	1024

#define _MAP_MOVE_TIMER_PROC  0x00002000
#define _MAP_MOVE_TIMER		  50

#define _MAP_ZOOM_TIMER_PROC  0x00002001
#define _MAP_ZOOM_TIMER		  50

#define _ZOOM_MAX_COUNT	5


extern fun_msg			g_fun_msg;

//#define _MAP_MOVE_TIMER		  200
/*
*	网络类型
*/
struct tagZoomParam
{
	int		iZoomLevel;
	bool	bOnZoom;
	POINT	point;
	tagZoomParam()
	{
		iZoomLevel = 0;
		bOnZoom = false;
	}
	~tagZoomParam()
	{
		bOnZoom = false;
		iZoomLevel = 0;
	}
};

#include <math.h>
#define M_PI 3.1415926
//伪经纬度转墨卡托
MapPoint lonLat2Mercator(MapPoint lonLat,long temp );
//伪墨卡托转经纬度
MapPoint Mercator2lonLat( MapPoint  mercator,long temp);

//伪经纬度转墨卡托
MapPoint lonLat2Mercator20(MapPoint lonLat );
//伪墨卡托转经纬度
MapPoint Mercator2lonLat20( MapPoint  mercator );

//加密文件名
bool EncryptionFileName( int t, int x, int y, int z , vchar*strFileEncryName,int iLen );


class CMapBase
{
public:
	CMapBase(void);
	~CMapBase(void);
	//初始化静态资源
	static void Init( string strRootPath );
	//设置地图类型
	static void SetMapType( en_MapType eMapType );
	//设置地图根目录
	static void SetMapRootPath( string strRootPath );
	//得到程序根目录
	static void GetMapRootPath( string& strMapRootPath );
	//得到地图类型根目录
	static void GetMapTypePath( int iMapType, string& strMapTypePath );
	//获得地图文件加密路径
	static void GetMapDataEncryptionPath( int x, int y, int z, int iMapType, string& strRootPath );
	//获得地图文件路径
	//static void GetMapDataPath( int x, int y, int z, string& strRootPath, int iLen );
	//获得地图URL路径
	//static void GetMapUrl( int x, int y, int z, vchar* pUrl,int iLen );
	//数据错误时使用备份网址
	static void GetMapUrlBk( int x, int y, int z, char* strUrl, int iLen );
	//获得谷歌地图标签层
	static void GetMapUrlMark( int x, int y, int z, char* strUrl, int iLen );
	//得到像素坐标
	static void GetMapPoint( int nLevel, MPoint lonLat20, MPoint& lonLat );
	//得到20级像素坐标
	static void GetMapPoint20( int nLevel, MPoint lonLat, MPoint& lonLat20 );

	//得到像素坐标
	static void GetMapPoint( int nLevel, MapPoint lonLat,  MPoint& lonLatout );
	//得到20级像素坐标
	static void LonLat2MapPoint20( MapPoint lonLat, MPoint& lonLat20 );
	//得到经纬度坐标
	static void MapPoint2LonLat( MPoint lonLat20, MapPoint& lonLat );
	//偏移20级像素坐标
	static void OffsetMapPoint20( int nLevel, VOSPoint offest, VOSPoint& offest20 );
	//写日志
	static bool  WriteLog(string strLog);
	//设置地图URL路径
	static void SetMapUrl(string strMapURL );
	//计算2点之间的距离
	static double  GetLength(double x1, double y1, double x2, double y2);
	static double  GetArea( double* pdX, double* pdY, int iSize );
	static double AzimuthAngle(double x1,double y1,double x2,double y2);
	//获得地图文件路径
//	void CMapBase::GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType )
	static void GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType );
	//获得地图URL路径
	static void GetMapUrl( int x, int y, int z,int iMapType, char* strUrl, int iLen  );
	//加密字符串
	static void EncryptionString(char* str);

	//计算网格编号范围
	static bool GetMapBlockBound( MBound& MapBound20,int nLevel, int& nMinX, int& nMaxX,int& nMinY, int& nMaxY );
	//计算点是否在多变型内部
	static bool InPolygon( vector<MapPoint*>* arr, MapPoint mpt );
	static bool InPolygon( MapPoint mpt, MapPoint* polygon, int nCount );
	static double  GetArea(  vector<MapPoint*>* arr );
	static double  GetArea(  vector<MapPoint*>* arr, MapPoint* pMpt );
};
