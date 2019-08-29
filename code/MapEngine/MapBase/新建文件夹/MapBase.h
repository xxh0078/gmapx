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



