/************************************************************
  文件名: MapPoints.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 点集合对象的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/


#ifndef _MAP_POINTS_H_
#define _MAP_POINTS_H_

//#include "stdafx.h"
#include "..//MapLayer//MapPoint.h"
#include "MapRectangle.h"


class CMapPoints:public CObject {

	DECLARE_DYNAMIC(CMapPoints)
public:
	CMapPoints();
    CMapPoints(CMapPoints& points);
	~CMapPoints();

//Attribute
public:
    long GetCount();
	CMapRectangle GetExtent();
	void SetExtent(CMapRectangle& exent);
//operations
public:
	CMapPoint* Get(long lIndex);
	void Add(CMapPoint* pPoint);
    void Set(long lIndex , CMapPoint* pPoint);
	void Remove(long lIndex);
	void Insert(long lndex , CMapPoint* pPoint);
	void Clear();
private:
	CMapRectangle m_Rectangle;
	CArray<CMapPoint*,CMapPoint*> m_Points; //存储点对象
};

#endif //_MAP_POINTS_H_