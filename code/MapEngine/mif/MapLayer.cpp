#include "stdafx.h"
#include "MapLayer.h"
#include "MapPoint.h"
#include "MapPoints.h"
#include "MapLine.h"
#include "MapPolygon.h"
#include "MapRecordSet.h"
#include "MapTableDesc.h"


CMapLayer::CMapLayer()
{
	m_bVisible = TRUE;
	m_Valid = FALSE;
	m_csLayerName = _T("");
	m_pRender = new CMapRender;
    m_pRender->SetRenderType(SIMPLE_RENDER);  
}

CMapLayer::~CMapLayer()
{
     
	 
	if ( m_pRender != NULL )
		delete m_pRender;

}
BOOL CMapLayer::LoadData(CString& csFileName)
{
	CString csDbfName;
	if (m_shpFile.ReadShp(csFileName))   
    {
		m_Valid = TRUE;
	
		return TRUE;
    } 
	else
    {    
		m_Valid = FALSE;
		return FALSE;
    
	} 
   

}
CMapRectangle CMapLayer::GetExtent()
{

	return m_shpFile.GetExtent();
}



long CMapLayer::GetShpType()
{
	return m_shpFile.GetShpType(); 
}

BOOL CMapLayer::GetVisible()
{
	return m_bVisible;
}

void CMapLayer::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

void CMapLayer::SetLayerName(CString& csLayerName )
{

	m_csLayerName = csLayerName;
}

CString CMapLayer::GetLayerName()
{
	
	return m_csLayerName;
}

void CMapLayer::SetExtent(CMapRectangle& extent )
{
	
	m_shpFile.SetExtent(extent); 
	 
}

void CMapLayer::SetShpType(int lShpType )
{
	m_shpFile.SetShpType(lShpType); 
		
}
int CMapLayer::SearchShape(CMapPoint& pt )
{

      if ( GetShpType() != POLYGON )
		  return -1;
	  else
      {  
		 return m_shpFile.SearchShape(pt);   
	  } 

}
void CMapLayer::SetRender(CMapRender* pRender )
{
	if ( m_pRender != NULL )
		delete m_pRender;
	m_pRender = pRender;

}

void CMapLayer::DrawLayer(CDC*pDC , DrawParam& draw)
{

	m_shpFile.DrawShp(pDC , m_pRender ,  draw );

}

void CMapLayer::FlashShp(CDC*pDC , DrawParam& draw , int iIndex)
{
	m_shpFile.FlashShp(pDC,draw,iIndex);


}