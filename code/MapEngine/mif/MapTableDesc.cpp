#include "stdafx.h"
#include "MapField.h"
#include "MapTableDesc.h"



CMapTableDesc::CMapTableDesc()
{


}

CMapTableDesc::CMapTableDesc(CMapTableDesc& tblDesc)
{

   int i,iCount;
   FIELD_ELEMENT *pField,*pSource;
   
   iCount = tblDesc.GetFieldCount()  - 1;
   for ( i = 0 ; i <= iCount ; i++ )
   { 
		pField = new  FIELD_ELEMENT;
		pSource = tblDesc.GetDesc(i); 
        strcpy(pField->szFieldName,pSource->szFieldName);
		pField->cFieldType = pSource->cFieldType; 
		pField->ucFieldDecimal = pSource->ucFieldDecimal;
		pField->ucFieldLength = pSource->ucFieldLength;
		pField->ulOffset = pSource->ulOffset;
		pField->cProductionIndex = pSource->cProductionIndex;
		pField->dbaseiv_id = pSource->dbaseiv_id;
		strcpy(pField->reserved1 , pField->reserved1);
		strcpy(pField->reserved2 , pField->reserved2);
		m_fieldsDesc.Add(pField); 	
   }
}
CMapTableDesc::~CMapTableDesc()
{
	Clear();  

}

short CMapTableDesc::GetFieldCount()
{
	return m_fieldsDesc.GetSize(); 

}

void CMapTableDesc::SetFieldCount(short sCount)
{


}
	
CString CMapTableDesc::GetFieldName(short sIndex)
{
	int iCount;
	FIELD_ELEMENT *pField;
	
	iCount = m_fieldsDesc.GetSize()  - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return _T("");
    pField = m_fieldsDesc.GetAt(sIndex);
	CString csName(pField->szFieldName); 
	return csName; 
}

void CMapTableDesc::SetFieldName(short sIndex, LPCTSTR lpszNewValue)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return ;
    pField = m_fieldsDesc.GetAt(sIndex);
	strcpy(pField->szFieldName , lpszNewValue); 

}

long CMapTableDesc::GetFieldType(short sIndex)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize()  - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return INVALID_VALUE;
    pField = m_fieldsDesc.GetAt(sIndex);
	return pField->cFieldType; 

}

void CMapTableDesc::SetFieldType(short sIndex, long nNewValue)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return;
    pField = m_fieldsDesc.GetAt(sIndex);
	pField->cFieldType  = (unsigned char )nNewValue; 


}

short CMapTableDesc::GetFieldPrecision(short sIndex)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return INVALID_VALUE;
    pField = m_fieldsDesc.GetAt(sIndex);
	return pField->ucFieldDecimal; 

}

void CMapTableDesc::SetFieldPrecision(short sIndex, short nNewValue)
{
    int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return;
    pField = m_fieldsDesc.GetAt(sIndex);
	pField->ucFieldDecimal  = (unsigned char)nNewValue; 

}

short CMapTableDesc::GetFieldLength(short sIndex)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return INVALID_VALUE;
    pField = m_fieldsDesc.GetAt(sIndex);
	return pField->ucFieldLength; 
}

void CMapTableDesc::SetFieldLength(short sIndex, short nNewValue)
{

    int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return;
    pField = m_fieldsDesc.GetAt(sIndex);
	pField->ucFieldLength  = (unsigned char)nNewValue; 
}

/*short CMapTableDesc::GetFieldScale(short sIndex)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return INVALID_VALUE;
    pField = m_fieldsDesc.GetAt(sIndex);
	return pField->sfdScale; 

}

void CMapTableDesc::SetFieldScale(short sIndex, short nNewValue)
{
	int iCount;
	FIELD_ELEMENT* pField;

	iCount = m_fieldsDesc.GetSize() - 1;
	if ( sIndex < 0 || sIndex > iCount )
		return;
    pField = m_fieldsDesc.GetAt(sIndex);
	pField->sfdScale  = nNewValue;

}*/

FIELD_ELEMENT* CMapTableDesc::GetDesc(short sIndex)
{
	int iCount;
	FIELD_ELEMENT*  pDesc = NULL;

	iCount = m_fieldsDesc.GetSize()-1;
	if ( sIndex < 0 || sIndex > iCount )
		return pDesc;
    pDesc = m_fieldsDesc.GetAt(sIndex);
	return pDesc;
}
void CMapTableDesc::Add(FIELD_ELEMENT* pfdDesc)
{

    if ( pfdDesc == NULL )
		return;
	m_fieldsDesc.Add( pfdDesc);
}

void CMapTableDesc::Remove(short sIndex)
{
	int iCount;
	FIELD_ELEMENT* pfdDesc;
	
	iCount = m_fieldsDesc.GetSize()-1;
	if ( sIndex < 0 || sIndex > iCount )
		return ;
	pfdDesc = m_fieldsDesc.GetAt( sIndex );  
    m_fieldsDesc.RemoveAt(sIndex,1);   
	delete pfdDesc; 
}

void CMapTableDesc::Insert(short sindex,FIELD_ELEMENT* pfdDesc)
{
	int iCount;
	
	iCount = m_fieldsDesc.GetSize()-1;
	if ( sindex < 0 || sindex > iCount )
		return ;
	m_fieldsDesc.InsertAt(sindex,pfdDesc);

}

void CMapTableDesc::Clear()
{
   int i,iCount;
   FIELD_ELEMENT *pfdDesc;
   
   iCount = m_fieldsDesc.GetSize() - 1;
   for ( i = iCount ; i >= 0   ; i-- )
   {
		pfdDesc = m_fieldsDesc.GetAt(i);
		delete pfdDesc;
   } 
   m_fieldsDesc.RemoveAll(); 
}