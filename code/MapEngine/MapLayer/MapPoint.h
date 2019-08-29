#pragma once
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
class VOS_EXPORT CMapPoint: public MapPoint
{
public:
	CMapPoint(void);
	~CMapPoint(void);
public:
	void   SetX(double& dbX ) { m_Point.x = dbX;};
	void   SetY(double& dbY ) { m_Point.y = dbY;};
	void   SetIndex(unsigned int uiIndex ) { m_uid = uiIndex ; };
	unsigned int GetIndex() { return m_uid; }; 
//	void   SetStatus(bool& bStatus) { m_bStatus = bStatus;};
	double GetX() { return m_Point.x;};
	double GetY() { return m_Point.y;};
	double Distance(CMapPoint& pt );
 // 	bool   GetStatus() { return m_bStatus;};
	bool   IsEqual(CMapPoint& pt );
	bool   IsPointInLine(CMapPoint& p1 , CMapPoint& p2 );
public:
	MapPoint	m_Point;
	long		m_uid;
	string		m_strPoiName;	//默认显示
	string		m_strText;		//鼠标移动显示
	VOSRect		m_rc;
};

