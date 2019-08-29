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
  ����:   �㵽�߾���
  ����: ����
  ����ֵ  ����

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
				//����㵽�߶���С����
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
  ����:    ����㵽�߶���С����
  ����: �� p1 --- �߶���㡡p2 --- �߶��յ�
  ����ֵ:  �ڵ㵽�߶���С����  

******************************************************************************/
double CMapLine::ptToSegment(CMapPoint& pt,CMapPoint& ptStart,CMapPoint& ptEnd)
{
	double dblDist,dblX,dblY,k;
	CMapPoint pPlumb;

	if ( pt.IsPointInLine(ptStart, ptEnd) )
		return 0.0; //����ֱ����
    if ( fabs(ptEnd.GetX() - ptStart.GetX()) <= EP )
	{
		dblX = ptStart.GetX();
		dblY = pt.GetY();
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.GetY() > min(ptStart.GetY(), ptEnd.GetY()) && pPlumb.GetY()
			< max(ptStart.GetY(), ptEnd.GetY()))
        {
			//�������߶η�Χ��
			return fabs(pPlumb.GetX() -pt.GetX());  
        } 
		else
        {   //�ж��߶ε��ĸ��˵��봹��ȽϽ�,Ȼ�������������
            if ( fabs(pPlumb.GetY() - ptStart.GetY()) < fabs(pPlumb.GetY() - ptEnd.GetY()))
			   dblDist = pt.Distance(ptStart); 
			else
			   dblDist = pt.Distance(ptEnd); 
        } 
		//�߶�Ϊ��ֱ���    	
    } else if ( fabs(ptEnd.GetY() - ptStart.GetY()) <= EP )
    {
		//�߶�Ϊˮƽ���
		dblX = pt.GetX();
		dblY = ptStart.GetY();
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.GetX() > min(ptStart.GetX(), ptEnd.GetX()) && pPlumb.GetX()
			< max(ptStart.GetX(), ptEnd.GetX()))
        {
			//�������߶η�Χ��
			return fabs(pPlumb.GetY() -pt.GetY());  
        } 
		else
        {   //�ж��߶ε��ĸ��˵��봹��ȽϽ�,Ȼ�������������
            if ( fabs(pPlumb.GetX() - ptStart.GetX()) < fabs(pPlumb.GetX() - ptEnd.GetX()))
			   dblDist = pt.Distance(ptStart); 
			else
			   dblDist = pt.Distance(ptEnd); 
        } 
    } 
	else
    {
		//�߶���б״̬
		k = (double)((ptEnd.GetY() - ptStart.GetY() ) /(ptEnd.GetX() - ptStart.GetX()));
		// ���㴹������
		dblX = (k*k*ptStart.GetX() + k*(pt.GetY()-ptStart.GetY())+pt.GetX())/(k*k+1);    
		dblY = k*(dblX-ptStart.GetX()) + ptStart.GetY(); 
		pPlumb.SetX(dblX);
		pPlumb.SetY(dblY);
		if ( pPlumb.IsPointInLine(ptStart,ptEnd) )
        {
			//�������߶���
		    dblDist = pt.Distance(pPlumb);  	
        }  
		else
        {
			//�ж��߶ε��ĸ��˵��봹��ȽϽ�,Ȼ�������������
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