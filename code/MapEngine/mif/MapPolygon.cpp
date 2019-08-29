#include "stdafx.h"
#include "global.h"
#include "MapPolygon.h"

IMPLEMENT_DYNAMIC(CMapPolygon,CObject)

CMapPolygon::CMapPolygon()
{


}

CMapPolygon::CMapPolygon(CMapPolygon& mappolygon )
{

   int i,iCount;
   CMapParts *pParts;
   
   iCount = m_Polygon.GetSize() - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
		pParts = new CMapParts(*mappolygon.GetParts(i));
		m_Polygon.Add(pParts); 	
   }
}

CMapPolygon::~CMapPolygon()
{

     Clear();
}

long CMapPolygon::GetCount()
{

	return m_Polygon.GetSize(); 
}

CMapRectangle CMapPolygon::GetExtent()
{

    return m_Extent;
}

void CMapPolygon::SetExtent(CMapRectangle& extent)
{
	m_Extent.SetLeft( extent.GetLeft());
	m_Extent.SetRight( extent.GetRight());
	m_Extent.SetTop(extent.GetTop());
    m_Extent.SetBottom(extent.GetBottom());
}

CMapParts* CMapPolygon::GetParts(long lIndex)
{

	int iCount;
    CMapParts  *pParts;

	iCount = m_Polygon.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return NULL;
    pParts = m_Polygon.GetAt(lIndex);
	return pParts;
}

double CMapPolygon::GetArea()
{

	return 0;
}

void CMapPolygon::Add(CMapParts* pParts)
{

    if ( pParts == NULL )
		return;
	m_Polygon.Add( pParts );

}

void CMapPolygon::Set(long lIndex , CMapParts* pParts)
{
	
	int iCount;
	CMapParts *pOldParts;

	if ( pParts == NULL )
		return;

	iCount = m_Polygon.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
    pOldParts = m_Polygon.GetAt( lIndex );
    m_Polygon.SetAt(lIndex,pParts);
    delete pOldParts; 
}

void CMapPolygon::Remove(long lIndex)
{
	int iCount;
	CMapParts *pParts;
	
	iCount = m_Polygon.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	pParts = m_Polygon.GetAt( lIndex );  
    m_Polygon.RemoveAt(lIndex,1);   
	delete pParts; 
}

void CMapPolygon::Insert(long lIndex , CMapParts* pParts)
{
	int iCount;
	
	iCount = m_Polygon.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	m_Polygon.InsertAt(lIndex,pParts);
}

void CMapPolygon::Clear()
{

   int i,iCount;
   CMapParts *pParts;
   
   iCount = m_Polygon.GetSize() - 1;
   for ( i = iCount ; i >= 0   ; i-- )
   {
		pParts = m_Polygon.GetAt(i);
		delete pParts;
   } 
   m_Polygon.RemoveAll(); 
}

/*************************************************
  描述:         判断点是否在多边形内 
  输入:         点对象
  输出：        在返回TRUE 不在返回FALSE
*************************************************/
BOOL CMapPolygon::IsPointIn(CMapPoint& pt )
{
    int i,j,k,iNumber;
	double dblTemp;
	CMapParts*  pParts;
	CMapPoints* pPoints;
	CMapPoint  *ptFirst,*ptSecond;
	CMapPoint	ptInfint;
	
	iNumber = 0;
	//不在矩形范围内直接返回 
	if ( !m_Extent.IsPointIn(pt) ) 
		  return FALSE;
	//做一条通过pt点的射线
	dblTemp = pt.GetY();
	ptInfint.SetY( dblTemp );
	dblTemp = infinity;
	ptInfint.SetX(dblTemp);
	//获得复合多边形的每一个多边形
	for ( i = 0 ; i < m_Polygon.GetSize() ; i++ )
    {
		pParts = (CMapParts*)m_Polygon.GetAt(i); 
		//获得一个多边形的点集合
		for ( j = 0 ; j < pParts->GetCount() ; j++ )
		{	
			pPoints = (CMapPoints*)pParts->Get(j);
			//获得每个点集合的顶点坐标
			for ( k = 0 ; k < pPoints->GetCount() - 1 ; k++ )
			{
				ptFirst  = (CMapPoint*)pPoints->Get(k);
				ptSecond = (CMapPoint*)pPoints->Get(k+1);
				if (pt.IsPointInLine(*ptFirst,*ptSecond) )
					return TRUE; //该点在多边形边上
                if ( ptSecond->GetY() == ptFirst->GetY() )
					continue;  //略过水平边
				
				if ( ptFirst->IsPointInLine(  pt , ptInfint ))
				{
					//边与射线相交于边第一个顶点
					if ( ptFirst->GetY() > ptSecond->GetY() )
						iNumber++;	
				}
				else if( ptSecond->IsPointInLine( pt , ptInfint ))
				{
					//边与射线相交于边的第二个顶点
					if ( ptFirst->GetY() > ptSecond->GetY() )
					    iNumber++;	
	
				} //判断是否有公共交点
				else if ( isIntersect(pt,ptInfint,*ptFirst,*ptSecond) )
						iNumber++ ; 
			} 
		} 
		
	} 
	if ( iNumber % 2 )
		return TRUE;
    else
	    return FALSE;
}

/*****************************************************************************
  描述:  判断两条直线是否相交 且交点不是顶点
  参数: p1 --- 线段起点 p2 ---线段终点 　p3 --- 线段起点　p4 --- 线段终点
  返回值  在直线上 返回TRUE 否则返回FALSE
******************************************************************************/

BOOL CMapPolygon::isIntersect(CMapPoint& p1 , CMapPoint& p2 , CMapPoint& p3 , CMapPoint& p4 )
{
	double dblMulti,dblTmp1,dblTmp2;
	//顶点相交
	if ( p1.IsEqual(p3) || p1.IsEqual(p4) || p2.IsEqual(p3) || p2.IsEqual(p4) )
		return FALSE;
    //判断两条线段外接矩形是否相交
	if ( min(p1.GetX(),p2.GetX()) > max(p3.GetX(),p4.GetX()) || max(p1.GetX(),p2.GetX())
		< min(p3.GetX(),p4.GetX()) || min(p1.GetY(),p2.GetY()) > max(p3.GetY(),p4.GetY())
		|| max(p1.GetY(),p2.GetY()) < min(p3.GetY(),p4.GetY()))
		return FALSE;
    //计算叉积  
	dblTmp1 = (double)((p1.GetX() - p3.GetX())*(p4.GetY()-p3.GetY()) - (p4.GetX()-p3.GetX())*(p1.GetY() - p3.GetY()));
	dblTmp2 = (double)((p4.GetX() -p3.GetX())*(p2.GetY() - p3.GetY()) - (p2.GetX()-p3.GetX())*(p4.GetY()-p3.GetY()));        ;
	dblMulti = dblTmp1 * dblTmp2;
	
	if ( dblMulti >= 0 )
		return TRUE;
	else
		return FALSE;

}
