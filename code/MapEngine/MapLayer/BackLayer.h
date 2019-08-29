// BackLayer.h: interface for the CBackLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_)
#define AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapLayer.h"
// POINT 结构体定义
typedef VOS_EXPORT struct _mapPOI
{ 
	double dx;
	double dy;
	string strICO;
	string strName;
	string strText;
	_mapPOI()
	{
		dx =0;
		dy =0;
	}
} mapPOI, *LPmapPOI; 
// 线 结构体定义
typedef VOS_EXPORT struct _mapLine
{ 
	vector<MapPoint*> m_arrMapPoint;
	_mapLine()
	{
	}
} mapLine, *LPmapLine; 

class CBackLayer : public CMapLayer
{
public:
	CBackLayer();
	virtual ~CBackLayer();

	//加载地图数据
	void Load( string strFilePath,CMapPoiRes* pRes );
	//加载KML格式地图
	bool LoadKML();
	//添加地图信息点
	bool SaveMapPoint( double x, double y, string strName, string strText, long icoID );

	//添加地图线,
	bool SaveMapLine( string strMapPoints, string strName, long width, long bgrcolor  );
	
	//添加地图文本信息
	bool SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor );

	//清除地图保存信息
	bool ClearMapSaveData();

	//保存所有地图点
	void SaveAllMapPoint();
	void SaveAllMapLine();
	void SaveAllMapText();
	void SaveAllMapPolygon();
	//得到当前位置的信息ID,0为无数据，1为点信息，2为线信息
	int GetLocID( long& lID, VOSPoint point );
private:
	
	//读取所有地图点
	bool ReadMapPoint();
	bool ReadMapLine();
	bool ReadMapPolygon();
	bool ReadMapText();
	bool ReadMap123();
	bool LoadMap2000();
	//解析
	char* ParseMapPoint(char* pBuf, int iLen, int nIndex );
	//解析
	char* ParseMapLine(char* pBuf, int iLen, int nIndex );
	char* ParseMapPolygon(char* pBuf, int iLen, int nIndex );
	//解析
	char* ParseMapText(char* pBuf, int iLen, int nIndex );
	//解析KML格式地图
	bool ParseKML( char* pData, int nlen );
	char* ParasKMLData( char* pData, int nlen );
private:
	string m_strFilePath;
//	vector<mapPOI*> m_arrMapPoi;
//	vector<mapLine*> m_arrMapLine;
	CMapPoiRes*		 m_pMapPoiRes;
	long			 m_lICOID;
	long			 m_lID;
};

#endif // !defined(AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_)
