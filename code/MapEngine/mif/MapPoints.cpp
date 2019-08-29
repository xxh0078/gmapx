#include "stdafx.h"
#include "MapPoints.h"

IMPLEMENT_DYNAMIC(CMapPoints,CObject)

CMapPoints::CMapPoints()
{


}


CMapPoints::CMapPoints(CMapPoints& points)
{
   int i,iCount;
   CMapPoint *pPoint;
   
   iCount = points.GetCount() - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
	  pPoint = new CMapPoint(*points.Get(i));
	  Add(pPoint); 	
   }
     

}

CMapPoints::~CMapPoints()
{
   Clear();

}

long CMapPoints::GetCount()
{

   return m_Points.GetSize();  
}

CMapRectangle CMapPoints::GetExtent()
{

	return m_Rectangle;
}


void CMapPoints::SetExtent(CMapRectangle& exent)
{

	m_Rectangle.SetLeft( exent.GetLeft());
	m_Rectangle.SetRight( exent.GetRight());
	m_Rectangle.SetTop(exent.GetTop());
    m_Rectangle.SetBottom(exent.GetBottom());
    	
}

CMapPoint* CMapPoints::Get(long lIndex)
{
	int iCount;
	CMapPoint  *pPt = NULL;

	iCount = m_Points.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return pPt;
    pPt = m_Points.GetAt(lIndex);
	return pPt;
		
}

void CMapPoints::Add(CMapPoint* pPoint)
{
	if ( pPoint == NULL )
		return;
	m_Points.Add( pPoint );

}

void CMapPoints::Set(long lIndex , CMapPoint* pPoint)
{
	int iCount;
	CMapPoint *pPt;

	if ( pPoint == NULL )
		return;

	iCount = m_Points.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
    pPt = m_Points.GetAt( lIndex );
    m_Points.SetAt(lIndex,pPoint);
    delete pPt; 

}

void CMapPoints::Remove(long lIndex)
{
	int iCount;
	CMapPoint *pPt;
	
	iCount = m_Points.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	pPt = m_Points.GetAt( lIndex );  
    m_Points.RemoveAt(lIndex,1);   
	delete pPt; 

}

void CMapPoints::Insert(long lIndex , CMapPoint* pPoint)
{
	int iCount;
	
	iCount = m_Points.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	m_Points.InsertAt(lIndex,pPoint);
	
}

void CMapPoints::Clear()
{
   int i,iCount;
   CMapPoint *pPoint;
   
   iCount = m_Points.GetSize() - 1;
   for ( i = iCount ; i >= 0   ; i-- )
   {
		pPoint = m_Points.GetAt(i);
		delete pPoint;
   } 
   m_Points.RemoveAll(); 


}