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
  ����:   �������
  ����: �������
  ����ֵ  ����

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
  ����: �ж�ָ�����Ƿ����߶���
  ����: ��p1 --- �߶���㡡p2 --- �߶��յ�
  ����ֵ  ���߶��� ����TRUE ���򷵻�FALSE

******************************************************************************/

bool   CMapPoint::IsPointInLine(CMapPoint& p1 , CMapPoint& p2 )
{
	 double dblMulti;
	 // �жϵ��Ƿ�����Ӿ��η�Χ�� 
	 if ( m_dbX < min(p1.GetX() ,p2.GetX()) || m_dbX > max(p1.GetX() ,p2.GetX())
	  || m_dbY <  min(p1.GetY() ,p2.GetY()) || m_dbY > max(p1.GetY() ,p2.GetY()))
		return FALSE;
     //������  
	 dblMulti = (double)((m_dbX -p1.GetX())*(p2.GetY() -p1.GetY())-(p2.GetX()-p1.GetX())*(m_dbY -p1.GetY()));	 
     if ( dblMulti == 0 )
		 return TRUE;
	 else
		 return FALSE;

}   