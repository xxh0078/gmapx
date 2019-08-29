
#ifndef	__MAP_DEFINE_H__
#define	__MAP_DEFINE_H__
#include "../VOSBase/VOSBase.h"
//地图背景色
#define COLORRBG RGB(230,230,230)
//自定义消息
#define WM_DOWNLOAD_MESSAGE		(WM_USER+123) 
#define WM_MAPMOVE_MESSAGE		(WM_USER+125) 
#define WM_MAP_ZOOM_MESSAGE		(WM_USER+126)
#define WM_MAP_ONINIT			(WM_USER+127)
#define WM_MAP_TOOLS_MESSAGE	(WM_USER+128)
#define WM_MAP_POIINFO_MESSAGE	(WM_USER+129)
#define WM_MAP_DCCLICK_POIINFO_MESSAGE	(WM_USER+130)


#define _MAP_TIMER_PROC  0x00002000
#define _MAP_TIMER		  100
#define _MAP_TIMER_PROC1  0x00002001
#define _MAP_TIMER1		  500
#define _MAP_TIMER_PROC2  0x00002002
#define _MAP_TIMER2		  300

//
//通用消息响应
typedef  void ( *fun_msg )( long, long, long , const char* );
#define MAP_TOOL_MESSAGE	0x00000010				//地图工具消息

//地图结构
typedef enum
{
	GMAP_GOOGLE_MAP = 0,			//谷歌一般地图
	GMAP_GOOGLE_IMAGE = 1,			//谷歌影像地图
	GMAP_GOOGLE_MARK = 2,			//谷歌影像注记图层
	GMAP_GOOGLE_PHYSICAL  = 3,		//谷歌地形地形图
	GMAP_GOOGLE_IMAGEMARK  = 4,		//谷歌混合影像图
	GMAP_BAIDU_MAP = 5,				//百度地图数据
	GMAP_VM	= 6,					//VIRTUALEARTH
	GMAP_MYMAP = 7,					//下载地图
	GMAP_CHANGLIAN = 8,				//畅联万方地图数据
	GMAP_MAPABC = 9,				//MapABC地图
	GMAP_MAPBAR = 10,				//MAPBAR地图
	GMAP_MAP365 = 11,				//MAP365地图
	GMAP_TIANDT = 12,				//天地图
	GMAP_SUPERMAP = 13,				//超图地图
	GMAP_FILES = 14					//文件地图
}en_MapType;

//地图结构
typedef enum
{
	MAP_POI_INFO = 0,			//POI信息
	MAP_POI_POINT = 1			//一般POI点
}en_PoiType;

#define	_MAX_MAP_LEVEL_		19
#define	_MIN_MAP_LEVEL_		1

#define _MAX_PIXEL_20_ 134217728//20级一半的像素,//地球周长一半为：20037508.34，

// POINT 结构体定义
typedef VOS_EXPORT struct _mPoint
{ 
	long lX;		// X 轴坐标
	long lY;		// Y 轴坐标
	_mPoint()
	{
		lX =0;
		lY =0;
	}
} MPoint, *LPMPoint; 

// MBOUND 结构体定义
typedef struct VOS_EXPORT _mBound
{ 
	long left;	//  左
	long top;	//	上
	long right;	//	右
	long bottom; //	下
	_mBound()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	long width()
	{
		return right - left;
	}
	long height()
	{
		return bottom - top;
	}
	MPoint TopLeft()
	{
		MPoint pt;
		pt.lX = left;
		pt.lY = top;
		return pt;
	}
	MPoint BottomRight()
	{
		MPoint pt;
		pt.lX = right;
		pt.lY = bottom;
		return pt;
	}
} MBound, *LPMBound; 
// POINT 结构体定义
typedef VOS_EXPORT struct _mapPoint
{ 
	double x;		// X 轴坐标
	double y;		// Y 轴坐标
	_mapPoint(){
		x = 0;
		y = 0;
	}
} MapPoint, *LPMapPoint; 
//线段
struct	MapLineSegment   
{
	MapPoint   pt1;
	MapPoint	pt2;  
};
// POINT 结构体定义
typedef VOS_EXPORT struct _mapBound
{ 
	double left;		// X 轴坐标
	double top;			// X 轴坐标
	double right;		// Y 轴坐标
	double bottom;		// Y 轴坐标
	_mapBound()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	double Width()
	{
		return right - left;
	}
	double Height()
	{
		return bottom - top;
	}
	bool IsPointIn( MapPoint point )
	{
		if ( point.x < left )
			return false;
		if ( point.x >= right )
			return false;
		if ( point.y < bottom )
			return false;
		if ( point.y >= top )
			return false;
		
		return true;
	}
	MapPoint TopLeft()
	{
		MapPoint pt;
		pt.x = left;
		pt.y = top;
		return pt;
	}
	MapPoint BottomRight()
	{
		MapPoint pt;
		pt.x = right;
		pt.y = bottom;
		return pt;
	}
} MapBount, *LPMapBount; 

typedef struct _MapBlockUnit{
	long		lNumX;				//X方向编号
	long		lNumY;				//Y方向编号
	short		sLevel;				//比例尺
    short		sFileID;			//文件ID，文件以ID命名
	long		lFilePos;			//文件位置
	long		lFileSize;			//文件大小
}MapBlockHead;

typedef struct _MapBlockData{
	long		lNumX;				//X方向编号
	long		lNumY;				//Y方向编号
	short		sLevel;				//比例尺
	char*		pData;				//数据
	long		lDataLenth;			//大小
}MapBlockData;

#endif		//__MAP_DEFINE_H__