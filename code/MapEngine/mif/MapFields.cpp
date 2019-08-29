#include "stdafx.h"
#include "MapField.h"
#include "MapFields.h"
 
CMapFields::CMapFields()
{

}

CMapFields::CMapFields(CMapFields& fields )
{
   int i,iCount;
   
   CMapField *pField;
   
   iCount = m_Fields.GetSize() - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
		pField = new CMapField(*(fields.GetField(i)));
		m_Fields.Add(pField); 	
   }	

}

CMapFields::~CMapFields()
{
	Clear();
}


short CMapFields::GetCout()
{

	return m_Fields.GetSize(); 
}

void CMapFields::Add(CMapField* pField)
{
	if ( pField == NULL )
		return;
	m_Fields.Add( pField );
}


void CMapFields::Remove(short sIndex)
{
	int iCount;
	CMapField *pField;
	
	iCount = m_Fields.GetSize()-1;
	if ( sIndex < 0 || sIndex > iCount )
		return ;
	pField = m_Fields.GetAt( sIndex );  
    m_Fields.RemoveAt(sIndex,1);   
	delete pField; 
}

void CMapFields::Insert(short sIndex, CMapField* pField)
{

	int iCount;
	
	iCount = m_Fields.GetSize()-1;
	if ( sIndex < 0 || sIndex > iCount )
		return ;
	m_Fields.InsertAt(sIndex,pField);

}

CMapField* CMapFields::GetField(short sIndex)
{
	int iCount;
	CMapField  *pField = NULL;

	iCount = m_Fields.GetSize()-1;
	if ( sIndex < 0 || sIndex > iCount )
		return pField;
    pField = m_Fields.GetAt(sIndex);
	return pField;

}

void CMapFields::Clear()
{
	long i,lCount;
	CMapField* pField;

	lCount  = m_Fields.GetSize() - 1;
	for(i = lCount ; i >= 0 ; i-- )
	{
		pField = m_Fields.GetAt(i);
		delete pField;
    }  
	m_Fields.RemoveAll(); 

}