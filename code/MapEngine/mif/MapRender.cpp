#include "stdafx.h"
//#include "global.h"
#include "MapRender.h"
extern UINT MapRand(UINT nMax);

CMapRender::CMapRender()
{
	m_SimpleRender.FillColor = RGB(MapRand(255),MapRand(255),MapRand(255));
	m_SimpleRender.OutlineColor = RGB(0,0,0);
	m_SimpleRender.iIndex = 0;	
	m_RenderType = SIMPLE_RENDER;
	m_FieldIndex = -1;

}


CMapRender::~CMapRender()
{

	Clear();
}

void CMapRender::Add(RENDERINFO& rInfo )
{
	int i;
	RENDERINFO* pInfo;

	for ( i = m_Render.GetSize() - 1 ; i >= 0 ; i--)
    {

		pInfo = (RENDERINFO*)m_Render.GetAt(i);
	    if ( pInfo->csValue == rInfo.csValue )
			return;   
	} 
	pInfo = new RENDERINFO;
    if ( pInfo == NULL )
		return;
	pInfo->csValue = rInfo.csValue; 
    pInfo->clr =  rInfo.clr;
	m_Render.Add(pInfo); 


}

void  CMapRender::RemoveByValue(CString& csValue)
{
	int i;
	RENDERINFO* pInfo;

	for ( i = m_Render.GetSize() - 1 ; i >= 0 ; i--)
    {

		pInfo = (RENDERINFO*)m_Render.GetAt(i);
	    if ( pInfo->csValue == csValue )
        {   
			delete pInfo;
			m_Render.RemoveAt(i);
			break;
        }  
    } 

}

void  CMapRender::RemoveByIndex(int iIndex )
{


	RENDERINFO* pInfo;

	if ( iIndex < 0 || iIndex >= m_Render.GetSize())
		return ;
	
	pInfo = (RENDERINFO*)m_Render.GetAt(iIndex);
	delete pInfo;
	m_Render.RemoveAt(iIndex);


}

int  CMapRender::GetCount()
{

	return m_Render.GetSize();
	

}


RENDERINFO* CMapRender::GetByValue(CString& csValue)
{
	int i;
	RENDERINFO* pInfo;

	for ( i = m_Render.GetSize() - 1 ; i >= 0 ; i--)
    {

		pInfo = (RENDERINFO*)m_Render.GetAt(i);
	    if ( pInfo->csValue == csValue )
			return pInfo;
    } 
	return NULL;



}

RENDERINFO* CMapRender::GetByIndex(int iIndex)
{
	
	RENDERINFO* pInfo;

	if ( iIndex < 0 || iIndex >= m_Render.GetSize())
		return NULL;
	
	pInfo = (RENDERINFO*)m_Render.GetAt(iIndex);
	return pInfo;
}

void CMapRender::Clear()
{
	int i;
	RENDERINFO* pInfo;

	for ( i = m_Render.GetSize() - 1 ; i >= 0 ; i--)
    {

		pInfo = (RENDERINFO*)m_Render.GetAt(i);
		delete pInfo; 
    } 
	m_Render.RemoveAll(); 


}

void CMapRender::SetSimpleRender( SIMPLERENDER& simpleRender )
{
	m_SimpleRender.FillColor = simpleRender.FillColor;
	m_SimpleRender.OutlineColor = simpleRender.OutlineColor;
	m_SimpleRender.iIndex = simpleRender.iIndex;
		
 
}
void CMapRender::GetSimpleRender( SIMPLERENDER& simpleRender )
{

	simpleRender.FillColor  =	m_SimpleRender.FillColor; 
	simpleRender.OutlineColor = m_SimpleRender.OutlineColor;
	simpleRender.iIndex = m_SimpleRender.iIndex ;


}

void CMapRender::SetFieldIndex(int iIndex)
{
	m_FieldIndex = iIndex;

}

int CMapRender::GetFieldIndex()
{
	return m_FieldIndex ;

}

void CMapRender::Clone(CMapRender *pRender)
{
	int i;
	SIMPLERENDER simple;
	RENDERINFO   *pInfo;
	RENDERINFO   InfoNew;
	if ( pRender == NULL )
		return;
	pRender->SetRenderType(GetRenderType());
    GetSimpleRender(simple); 
	pRender->SetSimpleRender(simple);
	pRender->SetFieldIndex(GetFieldIndex());
	
    for ( i = 0 ; i < m_Render.GetSize() ; i++ )  	
    {
		pInfo = (RENDERINFO*)m_Render.GetAt(i);
		InfoNew.csValue = pInfo->csValue;
		InfoNew.clr  = pInfo->clr;
        pRender->Add(InfoNew);   

    }    
}