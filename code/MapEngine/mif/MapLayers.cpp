#include "stdafx.h"
#include "MapLayers.h"

CMapLayers::CMapLayers()
{


}

CMapLayers::~CMapLayers()
{
	Clear();

}

short CMapLayers::GetCount()
{
	return m_Layers.GetSize();
}

void CMapLayers::SetCount(short sCount)
{

}

CMapLayer* CMapLayers::GetAt(short sIndex)
{

	int iCount;
    CMapLayer *pLayer;
   
    iCount = m_Layers.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount)
		return NULL;
	pLayer = m_Layers.GetAt(sIndex);
	return pLayer;
}

BOOL CMapLayers::Add(CMapLayer* pMapLayer)
{
	if ( pMapLayer == NULL )
		return FALSE;
	if (!m_Layers.Add( pMapLayer ))
		return FALSE;
	return TRUE;

}

void CMapLayers::Remove(short sIndex)
{
	int iCount;
    CMapLayer *pLayer;
   
    iCount = m_Layers.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount)
		return;

	pLayer = m_Layers.GetAt(sIndex);
	m_Layers.RemoveAt(sIndex);
	delete pLayer;

}

void CMapLayers::Clear()
{
   int i,iCount;
   CMapLayer *pLayer;
   
   iCount = m_Layers.GetSize() - 1;
   for ( i = iCount ; i >= 0   ; i-- )
   {
		pLayer = m_Layers.GetAt(i);
		delete pLayer;
   } 
   m_Layers.RemoveAll(); 

}

void CMapLayers::MoveTo(short fromIndex, short toIndex)
{
	int iCount;
    CMapLayer *pLayer;
   
    iCount = m_Layers.GetSize() - 1;
	if ( fromIndex < 0 || fromIndex > iCount)
		return;
    if ( toIndex < 0 || toIndex > iCount)
		return;
	pLayer = m_Layers.GetAt(fromIndex);
	m_Layers.RemoveAt(fromIndex);
    m_Layers.InsertAt(toIndex, pLayer); 

}

void CMapLayers::MoveToTop(short sIndex)
{
	int iCount;
    CMapLayer *pLayer;
   
    iCount = m_Layers.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount)
		return;
	pLayer = m_Layers.GetAt(sIndex);
	m_Layers.RemoveAt(sIndex);
    m_Layers.InsertAt(0, pLayer); 

}

void CMapLayers::MoveToBottom(short sIndex)
{
	int iCount;
    CMapLayer *pLayer;
   
    iCount = m_Layers.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount)
		return;
	pLayer = m_Layers.GetAt(sIndex);
	m_Layers.RemoveAt(sIndex);
    m_Layers.InsertAt(iCount, pLayer); 

}

void CMapLayers:: GetAllExtent(CMapRectangle& rc)
{
	short i;
	CMapLayer *pLayer;
	     
    for ( i = 0 ; i < m_Layers.GetSize() ; i++ )
	{
		pLayer = m_Layers.GetAt(i);
		CMapRectangle extent(pLayer->GetExtent());
		if ( i == 0 )
		{
			rc.SetLeft(extent.GetLeft());
			rc.SetRight(extent.GetRight());
			rc.SetTop(extent.GetTop());
			rc.SetBottom(extent.GetBottom());  
		}
		else
        { 
           if ( extent.GetLeft() < rc.GetLeft() )
			   rc.SetLeft(extent.GetLeft());
		   if ( extent.GetRight() > rc.GetRight() )
			   rc.SetRight(extent.GetRight());
           if ( extent.GetTop() < rc.GetTop() )
			   rc.SetTop(extent.GetTop());
		   if ( extent.GetBottom() > rc.GetBottom() )
			   rc.SetBottom(extent.GetBottom());
 
		} 
     }  
       
  
}