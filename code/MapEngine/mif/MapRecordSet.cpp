#include "stdafx.h"
#include "global.h"
#include "MapField.h"
#include "MapFields.h"
#include "MapTableDesc.h"
#include "MapRecordSet.h"



CMapRecordSet::CMapRecordSet()
{

	m_CacheSize = 50;
	bBOF = FALSE;
	bEOF = FALSE;
	m_bDbfOpen = FALSE;
	iCursorPos = -1;
}

CMapRecordSet::~CMapRecordSet()
{

	Clear();
}

long CMapRecordSet::GetRecordCount()
{

	return m_Header.no_recs; 
}

CMapFields* CMapRecordSet::GetFields(long lIndex)
{
	long lCount;
    CMapFields *fields = NULL;
	CMapFields *pFields;
	lCount = m_Fields.GetSize() - 1; 
    if ( lIndex < 0 || lIndex > lCount )
		return fields;
	pFields = m_Fields.GetAt(lIndex);
	return pFields;
}

CMapTableDesc* CMapRecordSet::GetTableDesc()
{

	return &m_TableDesc;
}

BOOL CMapRecordSet::GetBOF()
{
	return bBOF; 

}

BOOL CMapRecordSet::GetEOF()
{
	return bEOF;

}

int  CMapRecordSet::GetCacheSize()
{
	return m_CacheSize;

}

BOOL CMapRecordSet::SetCacheSize(int& CacheSize)
{
	if ( CacheSize < 0 || CacheSize > MAX_CACH_SIZE )
		return FALSE;
	return TRUE;
}

/*************************************************
  ����:         ��DBF�ļ�
  ����:         �ļ���
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE
*************************************************/
BOOL CMapRecordSet::openDBF(CString& csFileName)
{
	unsigned int  iTemp;
	unsigned long ulReocrdCount;
	unsigned short ulLength,ulRecLength;
	short i,sFieldCount;
	char*  pszBuffer;
	FIELD_ELEMENT *pField,*pOldField;
    CFileException fe;

	//�����ļ�
	if ( !fDbf.Open(csFileName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	m_bDbfOpen = TRUE;
	fDbf.Seek(0L, CFile::begin);
	//�����ļ�ͷ 
	if ( fDbf.Read(&m_Header,sizeof(m_Header)) != sizeof(m_Header))
    	return FALSE;
	ulReocrdCount = m_Header.no_recs; 
	ulLength = m_Header.head_len;
    ulRecLength = m_Header.rec_len; 
   
	//�����ֶθ���
	sFieldCount = (ulLength - sizeof(DBF_HEADER)-1)/sizeof(FIELD_ELEMENT);
	iTemp = sFieldCount * sizeof(FIELD_ELEMENT) + 1;
	pszBuffer = new char[iTemp];
	if ( pszBuffer == NULL )
		return FALSE;
    //�����ֶ�������������(��ṹ)
	if ( fDbf.Read(pszBuffer,iTemp) != iTemp)
    {     
    	delete []pszBuffer;
		return FALSE;
	}	
	for ( i = 0 ; i < sFieldCount ; i++ )
	{
		pField = new FIELD_ELEMENT;
		if ( pField == NULL )
		{
			delete []pszBuffer;
		    m_TableDesc.Clear();     
			return FALSE; 
        } 

		memcpy(pField,pszBuffer+i*sizeof(FIELD_ELEMENT),sizeof(FIELD_ELEMENT));
		if ( i == 0 )
        	pField->ulOffset = 0;
        else
			pField->ulOffset = pOldField->ulOffset + pOldField->ucFieldLength; 
		
		//�ж��ֶ�����
		if ( pField->cFieldType != 'N' && pField->cFieldType != 'F' )
        {   
			pField->ucFieldLength += pField->ucFieldDecimal*256; 
            pField->ucFieldDecimal = 0;           
		}
		pOldField = pField;   
       	m_TableDesc.Add(pField); 
		
    }   
    //�����¼����¼��������
    ReadRecord(0); 
    
	delete []pszBuffer;
	return TRUE;

}

/*************************************************
  ����:         �������ݼ�¼ 
  ����:         ��¼������(��0��ʼ)
  �����        ��
*************************************************/

void CMapRecordSet::ReadRecord(unsigned long lRecordID)
{
	int	   j,iRecordOffset;
	char   *pszBuffer;
	char   szBuff[255];
	double dbValue;
	FIELD_ELEMENT *pField;
	CMapField *pMapField;
	CMapFields *pMapFields;

	VARIANT varValue;

	if( lRecordID < 0 || lRecordID >= m_Header.no_recs)
        return; //��Ч������ֵ

    if ( iCursorPos != lRecordID) //Ҫ��ȡ�ļ�¼δ�ڻ�����
    {
		//�����¼����ļ�ͷ��ƫ����
		iRecordOffset = lRecordID*m_Header.rec_len + m_Header.head_len;
		pszBuffer = new char[ m_Header.rec_len];
        fDbf.Seek(iRecordOffset , CFile::begin);   
		if ( fDbf.Read(pszBuffer,m_Header.rec_len) != m_Header.rec_len)
		{     
    		delete []pszBuffer;
			return ;
		}	
        
	    Clear();
		pMapFields = new CMapFields(); 
		for ( j = 0 ; j < m_TableDesc.GetFieldCount() ; j++)
		{	
			pMapField = new CMapField;
			pField = m_TableDesc.GetDesc(j); 
			pMapField->SetName( pField->szFieldName );
			pMapField->SetType(pField->cFieldType);
			memset(szBuff , 0 , 255);
			//�Թ��ü�¼�Ƿ�ɾ������ֽ�pszBuffer+1
			strncpy(szBuff, pszBuffer+1+pField->ulOffset , pField->ucFieldLength);
			if ( pField->cFieldType == 'N' || pField->cFieldType == 'F' )
			{
				::VariantInit(&varValue);
				dbValue = atof(szBuff );
				if ( pField->ucFieldDecimal == 0 )
				{   
					varValue.bVal = VT_I4;   
					varValue.lVal = (int)dbValue;
					pMapField->SetType(fdInteger);
				}
				else
				{
					varValue.bVal = VT_R8;
					varValue.dblVal = dbValue;
					pMapField->SetType(fdDouble);
		   		}	
				pMapField->SetValue(varValue);
			}
			else if ( pField->cFieldType == 'C' )
			{
				pMapField->SetValueAsString(szBuff);
				pMapField->SetType(fdString);
			}
			else
				pMapField->SetType(fdInvaild);
			pMapFields->Add(pMapField);  
             
		}
		Clear(); //��ջ����������¼�¼
		m_Fields.Add(pMapFields);
		delete []pszBuffer;
		iCursorPos = lRecordID;
	}
	

	
	
	
}
/*************************************************
  ����:         �ƶ�����¼��ͷ��
  ����:         ��
  �����        ��
*************************************************/
void CMapRecordSet::MoveFirst()
{
	 if ( !m_bDbfOpen ) //���ݿ��ļ�δ��
		 return;
	 bBOF = TRUE;
	 bEOF = FALSE;
	 iCursorPos = -1;
	 ReadRecord(0);
	  
}

/*************************************************
  ����:         �ƶ�����¼��β��
  ����:         ��
  �����        ��
*************************************************/
void CMapRecordSet::MoveLast()
{
     if ( !m_bDbfOpen ) 
		 return;
	 bEOF = TRUE;
	 ReadRecord(m_Header.no_recs - 1);  
}

/*************************************************
  ����:         �ƶ�����һ����¼
  ����:         ��
  �����        ��
*************************************************/

void CMapRecordSet::MoveNext()
{
	
	 if ( !m_bDbfOpen ) 
		 return;
	 
	 if ( m_Header.no_recs == 1 )
     {
		 bBOF = TRUE;
		 bEOF = TRUE;
		 return;

     }   
	 if ( iCursorPos < m_Header.no_recs-1)
     {
		 bBOF = FALSE;
		 ReadRecord(iCursorPos + 1);

     } 
	 else
        bEOF = TRUE; 

}

/*************************************************
  ����:         �ƶ�����һ����¼
  ����:         ��
  �����        ��
*************************************************/
void CMapRecordSet::MovePrev()
{
	if ( !m_bDbfOpen ) //���ݿ��ļ�δ��
		 return;
	 
	if ( m_Header.no_recs == 1 )
    {
		 bBOF = TRUE;
		 bEOF = TRUE;
		 return;

    }   
	if ( iCursorPos > 0 )
    {
		 bEOF = FALSE;
		 ReadRecord(iCursorPos - 1);

	} 
	else
        bBOF = TRUE; 


}
/*************************************************
  ����:         �ƶ�iNumRecords����¼
  ����:         �ƶ��ļ�¼�����ƶ����λ��
  �����        ��
*************************************************/

BOOL CMapRecordSet::Move(int iNumRecords , RECORDSTART Start )
{
	int iPos;
	/*if ( bEOF && iNumRecords > 0 ) //�Ѿ�����¼��ĩβ
		return FALSE;
	if ( bBOF && iNumRecords < 0 ) //�Ѿ�����¼��ͷ
		return FALSE;
	if ( iNumRecords == 0 )
		return TRUE;*/

	switch ( Start )
    {
		case BookmarkCurrent:
			iPos = iCursorPos; 
			break;
        case BookmarkLast:
			iPos = m_Header.no_recs - 1;
			break;
        default: // BookmarkFirst
			iPos = 0; 
			break;
	}

	if ( iNumRecords > 0 ) //����ƶ�
    {
		if ( m_Header.no_recs <= (unsigned long)(iPos + iNumRecords))
			return FALSE;
		else
        {
			ReadRecord(iPos + iNumRecords);
			return TRUE;
		}	
	}	
	else
    {
	    if (  (iPos + iNumRecords) < 0 )
			return FALSE;
		else
        {
			ReadRecord(iPos + iNumRecords);
			return TRUE;
		}	
    }
}
/*************************************************
  ����:         ��ռ�¼������
  ����:         ��
  �����        ��
*************************************************/
void CMapRecordSet::Clear()
{
	int i;
	CMapFields *pMapFields;

	for ( i = m_Fields.GetSize() - 1 ; i >=0  ; i-- )
	{	
		pMapFields = m_Fields.GetAt(i);
		delete pMapFields;
	}
	m_Fields.RemoveAll(); 
	
}