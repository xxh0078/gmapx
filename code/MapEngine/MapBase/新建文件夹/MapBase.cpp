#include "StdAfx.h"
#include "MapBase.h"
#include <stdio.h>
#include "../VOSBase/VOSBase.h"

fun_msg			g_fun_msg;

//en_MapType	g_enMapType;
string		g_strRootPath;

string g_strMapURL = _T("http://mt1.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G");
int	   g_iMapURLParmType = 123; //1表示x,2表示y,3表示z

//经纬度转墨卡托
MapPoint lonLat2Mercator(MapPoint lonLat,long temp )
{
	MapPoint mercator;
	double x = lonLat.x *temp/180;//20037508.34
	double y = log(tan((90+lonLat.y)*M_PI/360))/(M_PI/180);
	y = y *temp/180;
	mercator.x = x;
	mercator.y = y;
	return mercator ;
}
//墨卡托转经纬度
MapPoint Mercator2lonLat(MapPoint  mercator,long temp)
{
	MapPoint lonLat;
	double x = mercator.x/temp*180;
	double y = mercator.y/temp*180;
	y= 180/M_PI*(2*atan(exp(y*M_PI/180))-M_PI/2);
	lonLat.x = x;
	lonLat.y = y;
	return lonLat;
}
//伪经纬度转墨卡托
MapPoint lonLat2Mercator20(MapPoint lonLat )
{
	MapPoint mercator;
	double x = lonLat.x *_MAX_PIXEL_20_/180;//20037508.34
	double y = log(tan((90+lonLat.y)*M_PI/360))/(M_PI/180);
	y = y *_MAX_PIXEL_20_/180;
	mercator.x = x;
	mercator.y = y;
	return mercator ;
}
//伪墨卡托转经纬度
MapPoint Mercator2lonLat20( MapPoint  mercator )
{
	MapPoint lonLat;
	double x = mercator.x/_MAX_PIXEL_20_*180;
	double y = mercator.y/_MAX_PIXEL_20_*180;
	y= 180/M_PI*(2*atan(exp(y*M_PI/180))-M_PI/2);
	lonLat.x = x;
	lonLat.y = y;
	return lonLat;
}