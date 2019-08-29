#include "stdafx.h"
#include "global.h"
#include "MapPoint.h"

IMPLEMENT_DYNAMIC(CMapPoint,CObject) 

CMapPoint::CMapPoint()
{
    m_bStatus = 0;
	m_uiIndex = 0;
	m_dbX = 0.0;
	m_dbY = 0.0;

}

CMapPoint::CMapPoint(CMapPoint& pt)
{
   	m_bStatus = pt.m_bStatus;
	m_uiIndex = pt.m_uiIndex;
	m_dbX = pt.m_dbX;
	m_dbY = pt.m_dbY ;
	 



}

CMapPoint::~CMapPoint()
{


}
/*****************************************************************************
  描述:   两点距离
  参数: 　点对象
  返回值  距离

******************************************************************************/
double CMapPoint::Distance(CMapPoint& pt )
{
	return(sqrt((pt.GetX()-m_dbX)*(pt.GetX()-m_dbX)+(pt.GetY()-m_dbY)*(pt.GetY()-m_dbY)));
}

bool  CMapPoint::IsEqual(CMapPoint& pt )
{

	if ( fabs(m_dbX-pt.GetX()) < EP && fabs(m_dbY-pt.GetY()) < EP )
		return TRUE;
	else
		return FALSE;


}

/*****************************************************************************
  描述: 判断指定点是否在线段上
  参数: 　p1 --- 线段起点　p2 --- 线段终点
  返回值  在线段上 返回TRUE 否则返回FALSE

******************************************************************************/

bool   CMapPoint::IsPointInLine(CMapPoint& p1 , CMapPoint& p2 )
{
	 double dblMulti;
	 // 判断点是否在外接矩形范围内 
	 if ( m_dbX < min(p1.GetX() ,p2.GetX()) || m_dbX > max(p1.GetX() ,p2.GetX())
	  || m_dbY <  min(p1.GetY() ,p2.GetY()) || m_dbY > max(p1.GetY() ,p2.GetY()))
		return FALSE;
     //计算叉积  
	 dblMulti = (double)((m_dbX -p1.GetX())*(p2.GetY() -p1.GetY())-(p2.GetX()-p1.GetX())*(m_dbY -p1.GetY()));	 
     if ( dblMulti == 0 )
		 return TRUE;
	 else
		 return FALSE;

}   