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
  描述:         打开DBF文件
  输入:         文件名
  输出：        成功返回TRUE 失败返回FALSE
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

	//打开主文件
	if ( !fDbf.Open(csFileName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	m_bDbfOpen = TRUE;
	fDbf.Seek(0L, CFile::begin);
	//读入文件头 
	if ( fDbf.Read(&m_Header,sizeof(m_Header)) != sizeof(m_Header))
    	return FALSE;
	ulReocrdCount = m_Header.no_recs; 
	ulLength = m_Header.head_len;
    ulRecLength = m_Header.rec_len; 
   
	//计算字段个数
	sFieldCount = (ulLength - sizeof(DBF_HEADER)-1)/sizeof(FIELD_ELEMENT);
	iTemp = sFieldCount * sizeof(FIELD_ELEMENT) + 1;
	pszBuffer = new char[iTemp];
	if ( pszBuffer == NULL )
		return FALSE;
    //读入字段描述部分数据(表结构)
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
		
		//判断字段类型
		if ( pField->cFieldType != 'N' && pField->cFieldType != 'F' )
        {   
			pField->ucFieldLength += pField->ucFieldDecimal*256; 
            pField->ucFieldDecimal = 0;           
		}
		pOldField = pField;   
       	m_TableDesc.Add(pField); 
		
    }   
    //读入记录到记录集缓冲区
    ReadRecord(0); 
    
	delete []pszBuffer;
	return TRUE;

}

/*************************************************
  描述:         读入数据记录 
  输入:         记录的索引(从0开始)
  输出：        无
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
        return; //无效的索引值

    if ( iCursorPos != lRecordID) //要读取的记录未在缓存中
    {
		//计算记录相对文件头的偏移量
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
			//略过该记录是否删除标记字节pszBuffer+1
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
		Clear(); //清空缓冲区加入新记录
		m_Fields.Add(pMapFields);
		delete []pszBuffer;
		iCursorPos = lRecordID;
	}
	

	
	
	
}
/*************************************************
  描述:         移动到记录集头部
  输入:         无
  输出：        无
*************************************************/
void CMapRecordSet::MoveFirst()
{
	 if ( !m_bDbfOpen ) //数据库文件未打开
		 return;
	 bBOF = TRUE;
	 bEOF = FALSE;
	 iCursorPos = -1;
	 ReadRecord(0);
	  
}

/*************************************************
  描述:         移动到记录集尾部
  输入:         无
  输出：        无
*************************************************/
void CMapRecordSet::MoveLast()
{
     if ( !m_bDbfOpen ) 
		 return;
	 bEOF = TRUE;
	 ReadRecord(m_Header.no_recs - 1);  
}

/*************************************************
  描述:         移动到下一条记录
  输入:         无
  输出：        无
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
  描述:         移动到上一条记录
  输入:         无
  输出：        无
*************************************************/
void CMapRecordSet::MovePrev()
{
	if ( !m_bDbfOpen ) //数据库文件未打开
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
  描述:         移动iNumRecords条记录
  输入:         移动的记录数、移动相对位置
  输出：        无
*************************************************/

BOOL CMapRecordSet::Move(int iNumRecords , RECORDSTART Start )
{
	int iPos;
	/*if ( bEOF && iNumRecords > 0 ) //已经到记录集末尾
		return FALSE;
	if ( bBOF && iNumRecords < 0 ) //已经到记录集头
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

	if ( iNumRecords > 0 ) //向后移动
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
  描述:         清空记录缓冲区
  输入:         无
  输出：        无
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