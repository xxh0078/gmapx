#include "stdafx.h"
#include "MapParts.h"

IMPLEMENT_DYNAMIC(CMapParts,CObject)
CMapParts::CMapParts()
{


}

CMapParts::CMapParts(CMapParts& Parts)
{
   int i,iCount;
   CMapPoints *pPoints;
   
   iCount = Parts.GetCount() - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
		pPoints = new CMapPoints(*Parts.Get(i));
		m_Parts.Add(pPoints); 	
		
   } 
}

CMapParts::~CMapParts()
{
	Clear();
}

long CMapParts::GetCount()
{

	return m_Parts.GetSize(); 
}

void CMapParts::Add(CMapPoints* pPoints)
{
	if ( pPoints == NULL )
		return;
	m_Parts.Add(pPoints); 

}

void CMapParts::Set(long lIndex, CMapPoints* pPoints)
{
	long lCount;
	CMapPoints* pOldPoints;

	if ( pPoints == NULL )
		return;
	
	lCount  = m_Parts.GetSize() - 1;
	if ( lIndex < 0 || lIndex > lCount )
		return;
	pOldPoints = m_Parts.GetAt(lIndex);
	m_Parts.SetAt(lIndex , pPoints);
	delete pOldPoints;
	

}

void CMapParts::Remove(long lIndex)
{
	long lCount;
	CMapPoints *pPoints;
	
	lCount  = m_Parts.GetSize() - 1;
	if ( lIndex < 0 || lIndex > lCount )
		return;
	pPoints = m_Parts.GetAt(lIndex);  
    m_Parts.RemoveAt(lIndex,1);   
	delete pPoints; 

}

void CMapParts::Insert(long lIndex, CMapPoints* pPoints)
{
	int iCount;
	
	iCount = m_Parts.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return ;
	m_Parts.InsertAt(lIndex,pPoints);

}

CMapPoints* CMapParts::Get(long lIndex)
{

	int iCount;
    CMapPoints  *pPts=NULL;

	iCount = m_Parts.GetSize()-1;
	if ( lIndex < 0 || lIndex > iCount )
		return pPts;
    pPts = m_Parts.GetAt(lIndex);
	return pPts;
}

void CMapParts::Clear()
{
	long i,lCount;
	CMapPoints* pPoints;

	lCount  = m_Parts.GetSize() - 1;
	for(i = lCount ; i >= 0 ; i-- )
	{
		pPoints = m_Parts.GetAt(i);
		delete pPoints;
    }  
	m_Parts.RemoveAll(); 

}