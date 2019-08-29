#include "stdafx.h"
#include "Global.h"
#include "MapLine.h"

IMPLEMENT_DYNAMIC(CMapLine,CObject)
CMapLine::CMapLine()
{


}

CMapLine::CMapLine(CMapLine& mapline )
{

   int i,iCount;
   CMapParts *pParts;
   
   iCount = m_Line.GetSize() - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
		pParts = new CMapParts(*(mapline.GetParts(i)));
		m_Line.Add(pParts); 	
   }
}

CMapLine::~CMapLine()
{

     Clear();
}

long CMapLine::GetCount()
{

	return m_Line.GetSize(); 
}

CMapRectangle CMapLine::GetExtent()
{

    return m_Extent;
}

void CMapLine::SetExtent(CMapRectangle& extent)
{
	m_Extent.SetLeft( extent.GetLeft());
	m_Extent.SetRight( extent.GetRight());
	m_Extent.SetTop(extent.GetTop());
    m_Extent.SetBottom(extent.GetBottom());
}

CMapParts* CMapLine::GetParts(long lIndex)
{

	int iCount;
	CMapParts  *pParts = NULL;

	iCount = m_Line.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return pParts;
    pParts = m_Line.GetAt(lIndex);
	return pParts;
}

double CMapLine::GetLength()
{

	return 0;
}
/*****************************************************************************
  描述:   点到线距离
  参数: 　点
  返回值  距离

******************************************************************************/
double CMapLine::Distance(CMapPoint& pt )
{

	int i,j,k;
	double dblMinDist,dblDist;
    CMapParts  *pParts;
	CMapPoints *pPoints;
	CMapPoint  *pPoint1,*pPoint2;
	
	dblMinDist =  infinity;
	dblDist =  infinity;
	for ( i = 0 ; i < m_Line.GetSize() ; i++ )
	{
		pParts = (CMapParts*)m_Line.GetAt(i);
		for ( j = 0 ; j < pParts->GetCount() ; j++)
		{
			pPoints = (CMapPoints*)pParts;
			for( k = 0 ; k < pPoints->GetCount() - 1 ; k++)
			{
				pPoint1 = (CMapPoint*)pPoints->Get(k);
				pPoint2 = (CMapPoint*)pPoints->Get(k+1);
				//计算点到线段最小距离
				dblDist = ptToSegment(pt,*pPoint1,*pPoint2);
                if ( dblDist <= EP )
					return 0.0;
				else if ( dblDist < dblMinDist )
                    dblMinDist = dblDist;

            }    
		}
    }  
	return dblMinDist;
}
/*****************************************************************************
  描述:    计算点到线段最小距离
  参数: 　 p1 --- 线段起点　p2 --- 线段终点
  返回值:  在点到线段最小距离  

******************************************************************************/
double CMapLine::ptToSegment(CMapPoint& pt,CMapPoint& ptStart,CMapPoint& ptEnd)
{
	double dblDist,dblX,dblY,k;
	CMapPoint pPlumb;

	if ( pt.IsPointInLine(ptStart, ptEnd) )
		return 0.0; //点在直线上
    if ( fabs(ptEnd.GetX() - ptStart.GetX()) <= EP )
	{
		dblX = ptStart.GetX();
		dblY = pt.GetY();
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.GetY() > min(ptStart.GetY(), ptEnd.GetY()) && pPlumb.GetY()
			< max(ptStart.GetY(), ptEnd.GetY()))
        {
			//垂足在线段范围内
			return fabs(pPlumb.GetX() -pt.GetX());  
        } 
		else
        {   //判断线段的哪个端点离垂足比较近,然后计算两点间距离
            if ( fabs(pPlumb.GetY() - ptStart.GetY()) < fabs(pPlumb.GetY() - ptEnd.GetY()))
			   dblDist = pt.Distance(ptStart); 
			else
			   dblDist = pt.Distance(ptEnd); 
        } 
		//线段为垂直情况    	
    } else if ( fabs(ptEnd.GetY() - ptStart.GetY()) <= EP )
    {
		//线段为水平情况
		dblX = pt.GetX();
		dblY = ptStart.GetY();
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.GetX() > min(ptStart.GetX(), ptEnd.GetX()) && pPlumb.GetX()
			< max(ptStart.GetX(), ptEnd.GetX()))
        {
			//垂足在线段范围内
			return fabs(pPlumb.GetY() -pt.GetY());  
        } 
		else
        {   //判断线段的哪个端点离垂足比较近,然后计算两点间距离
            if ( fabs(pPlumb.GetX() - ptStart.GetX()) < fabs(pPlumb.GetX() - ptEnd.GetX()))
			   dblDist = pt.Distance(ptStart); 
			else
			   dblDist = pt.Distance(ptEnd); 
        } 
    } 
	else
    {
		//线段倾斜状态
		k = (double)((ptEnd.GetY() - ptStart.GetY() ) /(ptEnd.GetX() - ptStart.GetX()));
		// 计算垂足坐标
		dblX = (k*k*ptStart.GetX() + k*(pt.GetY()-ptStart.GetY())+pt.GetX())/(k*k+1);    
		dblY = k*(dblX-ptStart.GetX()) + ptStart.GetY(); 
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.IsPointInLine(ptStart,ptEnd) )
        {
			//垂足在线段上
		    dblDist = pt.Distance(pPlumb);  	
        }  
		else
        {
			//判断线段的哪个端点离垂足比较近,然后计算两点间距离
			if ( pPlumb.Distance(ptStart) < pPlumb.Distance(ptEnd))
               dblDist = pt.Distance(ptStart); 
			else
			   dblDist = pt.Distance(ptEnd); 
 				
			
		} 
    }
	return dblDist;
}



void CMapLine::Add(CMapParts* pParts)
{

    if ( pParts == NULL )
		return;
	m_Line.Add( pParts );

}

void CMapLine::Set(long lIndex , CMapParts* pParts)
{
	
	int iCount;
	CMapParts *pOldParts;

	if ( pParts == NULL )
		return;

	iCount = m_Line.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
    pOldParts = m_Line.GetAt( lIndex );
    m_Line.SetAt(lIndex,pParts);
    delete pOldParts; 
}

void CMapLine::Remove(long lIndex)
{
	int iCount;
	CMapParts *pParts;
	
	iCount = m_Line.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	pParts = m_Line.GetAt( lIndex );  
    m_Line.RemoveAt(lIndex,1);   
	delete pParts; 
}

void CMapLine::Insert(long lIndex , CMapParts* pParts)
{
	int iCount;
	
	iCount = m_Line.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	m_Line.InsertAt(lIndex,pParts);
}

void CMapLine::Clear()
{

   int i,iCount;
   CMapParts *pParts;
   
   iCount = m_Line.GetSize() - 1;
   for ( i = iCount ; i >= 0   ; i-- )
   {
		pParts = m_Line.GetAt(i);
		delete pParts;
   } 
   m_Line.RemoveAll(); 
}