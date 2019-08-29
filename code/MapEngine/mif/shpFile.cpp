#include "stdafx.h"
#include <d3dtypes.h>
#include "shpFile.h"
#include "../MapLayer/MapLeyerMan.h"
//#include "MapPoint.h"
#include "MapPoints.h"
#include "MapParts.h"
//#include "MapPolygon.h"
#include "MapFields.h"


CShpFile::CShpFile() 
{
	int i;
	bShpOpen = FALSE;
	bShxOpen = FALSE;
	m_shpType = NULLSHP;

	/* -------------------------------------------------------------------- */
            /*	Establish the byte order on this machine.			*/
    /* -------------------------------------------------------------------- */
    i = 1;
    if( *((uchar *) &i) == 1 )
		m_bBigEndian = FALSE;
	else
		m_bBigEndian = TRUE;
}

CShpFile::~CShpFile()
{
/*	
	 CMapPoint*    pPt;
	 CMapPoints*   pPts;
	 CMapLine*     pLine;
	 CMapPolygon*  pPolygon;

	 while(!m_ObList.IsEmpty())
	 {
		switch ( m_shpType )
        {  
			case POINT:
				pPt =(CMapPoint*)m_ObList.RemoveTail();
				delete pPt;
				break;
            case MULTIPOINT:
				pPts =(CMapPoints*)m_ObList.RemoveTail();
				delete pPts;
				break;

			case POLYLINE:
                pLine =(CMapLine*)m_ObList.RemoveTail();
				delete pLine;
				break;
			case POLYGON:
                pPolygon =(CMapPolygon*)m_ObList.RemoveTail();
				delete pPolygon;
				break;
            default:
				m_ObList.RemoveTail();
				break;
 
		}
     }    
	 if ( bShpOpen )
		fShp.Close();
	 if (bShxOpen)
		fShx.Close();
	 if ( pRecordSet )
		 delete pRecordSet;
		 */
	 
}

/*************************************************
  ����:         ����Shp��shx�ļ� ��ʽ ����ESRI������Ƥ��
  ����:         �ļ���(ȫ·��) 
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE
*************************************************/


BOOL CShpFile::ReadShp(CString& csFileName)
{
	int	  iTemp;
	CString csShxName;
	CFileException fe;
    SHPHEADER varHeader;
	
	//�����ļ�
	if ( !fShp.Open(csFileName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	bShpOpen = TRUE;
    
	//�������ļ�
	csShxName = csFileName.Left(csFileName.GetLength() - 3);
	
	csShxName = csShxName + "shx";
    if ( !fShx.Open(csShxName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	bShxOpen = TRUE;
       

	TRY
    {
	    //�����ļ�ͷ ��100�ֽ�
		if ( fShp.Read(&varHeader , sizeof(SHPHEADER))!= sizeof(SHPHEADER))
			return FILE_READERR;
		
        iTemp = varHeader.iFileCode; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&iTemp);
		if ( iTemp != 9994 ) //�Ƿ���shp�ļ�
			return FILE_CODEERR;
        if ( varHeader.iVersion != FILE_VERSION ) //�ļ��汾�Ƿ���ȷ
			return FILE_VERSIONERR;
        
		//shp ����  		
		m_shpType = varHeader.iShpType;  
		m_shpFileLength = varHeader.iFileLength;
	    if ( !m_bBigEndian )
			SwapWord(sizeof(int),&m_shpFileLength);
		
		//�������������η�Χ
		m_Extent.SetLeft(varHeader.dbXMin);
		m_Extent.SetRight(varHeader.dbXMax);
		m_Extent.SetTop(varHeader.dbYMin);
		m_Extent.SetBottom(varHeader.dbYMax);
        
		//�������ļ�ͷ ��100�ֽ�
		if ( fShx.Read(&varHeader , sizeof(SHPHEADER))!= sizeof(SHPHEADER))
			return FILE_READERR;
		iTemp = varHeader.iFileCode; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&iTemp);
		if ( iTemp != 9994 ) //�Ƿ���shx�ļ�
			return FILE_CODEERR;
        if ( varHeader.iVersion != FILE_VERSION ) //�ļ��汾�Ƿ���ȷ
			return FILE_VERSIONERR;
		m_shxFileLength = varHeader.iFileLength; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&m_shxFileLength);
		//ͨ�������ļ��������ļ���¼���� �ļ�������ֵ��16λ��
		m_iRecordCount = ((m_shxFileLength - 50 )*2)/sizeof(SHXRECORD);
		
		if ( !ReadRecord() )
			return FILE_READERR;
         if ( !ReadDBF(csFileName))
			 return FALSE;
	}
	CATCH(CFileException ,eload)
    {
		fShp.Abort();
		return FALSE;
    }
	END_CATCH
	
	
	return TRUE;

}
/*************************************************
  ����:         ����DBF�ļ���ʽ 
  ����:         �ļ���(ȫ·��) 
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE
*************************************************/
BOOL CShpFile::ReadDBF(CString& csFileName)
{
	CString csDbfName;
	BOOL bResult;
	//������¼������
	pRecordSet = new CMapRecordSet;
	ASSERT ( pRecordSet != NULL ); 
	csDbfName = csFileName.Left(csFileName.GetLength() - 3);
	csDbfName = csDbfName + "dbf";
	//��DBF�ļ�
	bResult =  pRecordSet->openDBF(csDbfName); 
    if ( !bResult )
		delete pRecordSet;
	return bResult;
}

/*************************************************
  ����:         ��õ�ǰ��ͼ�ļ������η�Χ 
  ����:         ��
  �����        ��ͼ���η�Χ   
*************************************************/

CMapRectangle CShpFile::GetExtent()
{
	return m_Extent;
}

/*************************************************
  ����:         ���õ�ͼ�ļ������η�Χ 
  ����:         ��ͼ���η�Χ
  �����        ��   
*************************************************/
void CShpFile::SetExtent(CMapRectangle& extent )
{
	m_Extent.SetLeft(extent.GetLeft());  
    m_Extent.SetRight(extent.GetRight());
	m_Extent.SetTop(extent.GetTop()); 
    m_Extent.SetBottom(extent.GetBottom());
}

/*************************************************
  ����:         ����Shp�������� 
  ����:         shp ����
  �����        ��   
*************************************************/
void CShpFile::SetShpType(int& iShpType)
{
	m_shpType = iShpType;
}

/*************************************************
  ����:         ����Shp�������� 
  ����:         ��
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE  
*************************************************/

BOOL CShpFile::ReadRecord()
{
	int i,j,k,m;
	int iDataLen,iLength,iIndex;
	int *pIParts;
	double dbTmp;
	char *pszBuffer,*lpVer;
	BOOL bEof;
	SHPINFO shpIn;
	SHPRECORDHEADER RecordHeader;
    CMapRectangle objRectangle;    
	CMapPoint   *pPoint;
	CMapPoints  *pPoints;
	CMapParts   *pParts;
	CMapLine    *pLine;
	CMapPolygon *pPolygon;

	bEof = FALSE;
	switch ( m_shpType )
	{
		case NULLSHP:	
			return FALSE;
			break;
        case POINT:
			{
				
				SHPPTCONTENT point;
				//������¼
				for ( i = 1 ; i <= m_iRecordCount ; i++ ) 
				{	
					iLength = SetRecordPos(i);
					if ( iLength <= 0 )
						return FALSE;

					//��ü�¼ͷ��Ϣ
					if (!GetRecordHeader(RecordHeader))
						return FALSE;
					//��¼���ݳ����Ƿ���shpʵ���Сһ��,������¼�����Ƿ����¼���ݳ���һ��				
					if ( RecordHeader.iContentLength*2 != sizeof(point)||
						RecordHeader.iContentLength*2 != iLength)
						return FALSE;
					if(fShp.Read(&point,sizeof(point))!= sizeof(point))
							return FALSE;
					pPoint = new CMapPoint;
					iIndex = i - 1;
					pPoint->m_uid = iIndex;
				    pPoint->SetIndex(iIndex); 
					if ( pPoint == NULL )
						return FALSE;
					//�����Ƿ�ƥ��
					if ( point.iShpType != m_shpType) 
						return FALSE;
                    pPoint->SetX(point.dbX );
					pPoint->SetY(point.dbY );
					m_ObList.AddTail((CObject*)pPoint);  
					//m_arrShpPoint.push_back( *pPoint );	    
				 } 
			} 	
			break;
        case POLYLINE:
		    
			pszBuffer = new char [MAX_BUFFER_SIZE]; //���仺����
			if ( pszBuffer == NULL )
				return FALSE;
			memset(pszBuffer , 0 , MAX_BUFFER_SIZE);
            
			//�����߼�¼
			for ( i = 1 ; i <= m_iRecordCount ; i++ ) //m_iRecordCount
			{	
			
				iLength = SetRecordPos(i);
				if ( iLength <= 0 )
					return FALSE;

				pLine = new CMapLine();
				iIndex = i - 1;
				pLine->m_lineid = iIndex; 
				if ( pLine == NULL )
					return FALSE;
				//��ü�¼ͷ��Ϣ
				if (!GetRecordHeader(RecordHeader))
					return FALSE;
				if ( !GetShpInfo(shpIn))
					return FALSE;
				 if (shpIn.ishpType != POLYLINE )//���Ͳ�ƥ��
                 {  
                      delete pLine;
					  continue;
				 }
				 if ( shpIn.iNumParts*sizeof(int) > MAX_BUFFER_SIZE )
                 {
					 //�����߶���������󻺳�������,���Ըö���
					 delete pLine;
					 continue;
                 } 
				 //�����������ʵ�ʳ���
				 j = sizeof(SHPINFO) + shpIn.iNumParts*sizeof(int) ;
				 j += shpIn.iNumPoints*sizeof(SHPPOINT);  
                 
				 //�ж�ʵ�ʳ����Ƿ��������ļ��м�¼��һ�� 
				 if ( RecordHeader.iContentLength*2 != j )
                 {
				     delete pLine;
					 continue;
				 }	 
				 //����shp���η�Χ
				 objRectangle.SetLeft(shpIn.Box[0].dbX);
				 objRectangle.SetTop(shpIn.Box[0].dbY);
				 objRectangle.SetRight(shpIn.Box[1].dbX);
				 objRectangle.SetBottom(shpIn.Box[1].dbY);
	//xxh			 pLine->SetExtent(objRectangle);
				 pIParts = new int[shpIn.iNumParts];
				 if ( pIParts == NULL )
                 {
					delete pLine;
					return FALSE;
				 }
				 //��������߶�����
				 if ( fShp.Read(pIParts,shpIn.iNumParts*4) != (uint)(shpIn.iNumParts*4))
				 {
					delete pLine;
					return FALSE;
				 }

				 //������洢��ռ�ֽ���
				 iLength = shpIn.iNumPoints*sizeof(SHPPOINT);
				 //��ʼ������������
				 iDataLen = ReadPoint(pszBuffer,iLength,bEof);
				 if ( iDataLen < 0 )
                 {
					  delete pLine;
					  delete pIParts;
					  return FALSE;
				 
				 }	 
				 lpVer = pszBuffer;
				 for ( j = 0 ;  j < shpIn.iNumParts ; j++ )
				 {
					 
					pParts  = new CMapParts();
					pPoints = new CMapPoints();
 					if ( pParts == NULL || pPoints == NULL)
						return FALSE;
					if ( j == shpIn.iNumParts - 1 )
                    {
					    k = pIParts[j];        //���ε�һ����������
					    m = shpIn.iNumPoints ; //��һ���ε�һ���������� 
                    }
              	    else
                    {
						k = pIParts[j];
						m = pIParts[j+1];
					}
					//�����i�εĶ���
				    for ( ; k < m ; k++)
                    {   
						pPoint = new CMapPoint();
						if ( pPoint == NULL )
							return FALSE;
						
						//��Ҫ�������ݸ��»�����
						if ( lpVer == pszBuffer + iDataLen && !bEof)
						{
							iDataLen = ReadPoint(pszBuffer,iLength,bEof);
							if ( iDataLen < 0 )
							{
								delete pPoint;
								delete pPoints;
								delete pLine;
								delete pIParts;
								
								return FALSE;
				 
							}	 
							lpVer = pszBuffer;
						}	
						dbTmp = *(double*)lpVer;
					    pPoint->SetX(dbTmp);
                        lpVer += 8;
						//��Ҫ�������ݸ��»�����
						if ( lpVer == pszBuffer + iDataLen && !bEof)
						{
							iDataLen = ReadPoint(pszBuffer,iLength,bEof);
							if ( iDataLen < 0 )
							{
								delete pPoint;
								delete pPoints;
								delete pLine;
								delete pIParts;
								return FALSE;
				 
							}	 
							lpVer = pszBuffer;
						}	
						dbTmp = *(double*)(lpVer);
						lpVer += 8;
                        pPoint->SetY(dbTmp); 
						pPoints->Add(pPoint); 
						
					}  
                    pParts->Add(pPoints);   
//xxh				    pLine->Add(pParts); 

				 }
				 m_ObList.AddTail( (CObject*)pLine);
				 delete []pIParts;
			
            }
			delete []pszBuffer;

			break;
        /*
		case POLYGON:
			pszBuffer = new char [MAX_BUFFER_SIZE]; //���仺����
			if ( pszBuffer == NULL )
				return FALSE;
			memset(pszBuffer , 0 , MAX_BUFFER_SIZE);
            
			//�������μ�¼
			for ( i = 1 ; i <= m_iRecordCount ; i++ ) //m_iRecordCount
			{	
				iLength = SetRecordPos(i);
				if ( iLength <= 0 )
					return FALSE;

				pPolygon = new CMapPolygon();
				iIndex = i - 1;
                pPolygon->SetIndex(iIndex);
				if (pPolygon == NULL )
					return FALSE;
				//��ü�¼ͷ��Ϣ
				if (!GetRecordHeader(RecordHeader))
					return FALSE;
				if ( !GetShpInfo(shpIn))
					return FALSE;
				 if (shpIn.ishpType != POLYGON )//���Ͳ�ƥ��
                 {  
                      delete pPolygon;
					  continue;
				 }
				 if ( shpIn.iNumParts*sizeof(int) > MAX_BUFFER_SIZE )
                 {
					 //���϶�����еĶ���θ���������󻺳�������,���Ըö���
					 delete pPolygon;
					 continue;
                 } 
				 //�����������ʵ�ʳ���
				 j = sizeof(SHPINFO) + shpIn.iNumParts*sizeof(int) ;
				 j += shpIn.iNumPoints*sizeof(SHPPOINT);  
                 
				 //�ж�ʵ�ʳ����Ƿ��������ļ��м�¼��һ�� 
				 if ( RecordHeader.iContentLength*2 != j )
                 {
				     delete pPolygon;
					 continue;
				 }	 
				 //����shp���η�Χ
				 objRectangle.SetLeft(shpIn.Box[0].dbX);
				 objRectangle.SetTop(shpIn.Box[0].dbY);
				 objRectangle.SetRight(shpIn.Box[1].dbX);
				 objRectangle.SetBottom(shpIn.Box[1].dbY); 
				 pPolygon->SetExtent(objRectangle);
				 pIParts = new int[shpIn.iNumParts];
				 if ( pIParts == NULL )
                 {
					delete pPolygon;
					return FALSE;
				 }
				 //���븴�϶���Ͷ�����
				 if ( fShp.Read(pIParts,shpIn.iNumParts*4) != (uint)(shpIn.iNumParts*4))
				 {
					delete pPolygon;
					return FALSE;
				 }

				 //������洢��ռ�ֽ���
				 iLength = shpIn.iNumPoints*sizeof(SHPPOINT);
				 //��ʼ������������
				 iDataLen = ReadPoint(pszBuffer,iLength,bEof);
				 if ( iDataLen < 0 )
                 {
					  delete pPolygon;
					  delete pIParts;
					  return FALSE;
				 
				 }	 
				 lpVer = pszBuffer;
				 for ( j = 0 ;  j < shpIn.iNumParts ; j++ )
				 {
					pParts  = new CMapParts();
					pPoints = new CMapPoints();
 					if ( pParts == NULL || pPoints == NULL)
						return FALSE;
					if ( j == shpIn.iNumParts - 1 )
                    {
					    k = pIParts[j];        //���ε�һ����������
					    m = shpIn.iNumPoints ; //��һ���ε�һ���������� 
                    }
              	    else
                    {
						k = pIParts[j];
						m = pIParts[j+1];
					}
					//�����i�εĶ���
				    for ( ; k < m ; k++)
                    {   
						pPoint = new CMapPoint();
						if ( pPoint == NULL )
							return FALSE;
						
						//��Ҫ�������ݸ��»�����
						if ( lpVer == pszBuffer + iDataLen && !bEof)
						{
							iDataLen = ReadPoint(pszBuffer,iLength,bEof);
							if ( iDataLen < 0 )
							{
								delete pPolygon;
								delete pIParts;
								return FALSE;
				 
							}	 
							lpVer = pszBuffer;
						}	
						dbTmp = *(double*)lpVer;
					    pPoint->SetX(dbTmp);
                        lpVer += 8;
						//��Ҫ�������ݸ��»�����
						if ( lpVer == pszBuffer + iDataLen && !bEof)
						{
							iDataLen = ReadPoint(pszBuffer,iLength,bEof);
							if ( iDataLen < 0 )
							{
								delete pPolygon;
								delete pIParts;
								return FALSE;
				 
							}	 
							lpVer = pszBuffer;
						}	
						dbTmp = *(double*)(lpVer);
                        pPoint->SetY(dbTmp); 
						pPoints->Add(pPoint); 
						lpVer += 8;
						
					}  
                    pParts->Add(pPoints);   
				    pPolygon->Add(pParts); 

				 }
				 m_ObList.AddTail( pPolygon);
			     delete []pIParts;
            }
			delete []pszBuffer;
			break;*/
		default:
			return FALSE;
			break;

    }    
	return TRUE;   
	
}

/*************************************************
  ����:         ����ÿ��shp��������ļ�ͷ��ƫ����
  ����:         ��¼����ֵ(���㿪ʼ)
  �����        ��shp�����������ļ��е�λ��  
*************************************************/
int CShpFile::SetRecordPos( int iRecord )
{
    unsigned int iOffset,iTmp;
	SHXRECORD shxRD;

	if ( iRecord < 0 )
		return 0;
    //��������ļ���¼ƫ��������ļ�ͷ
	if (iRecord == 1 )
    	iOffset = sizeof(SHPHEADER)  ;	 
	else
		iOffset = sizeof(SHPHEADER) + (iRecord-1)*sizeof(shxRecord) ;
	if ( iOffset > m_shxFileLength*2 - sizeof(shxRecord) )
		return 0;
	fShx.Seek( iOffset , CFile::begin );
	int m = sizeof(shxRD);
	fShx.Read( &shxRD , sizeof(shxRD));
	iTmp = shxRD.iOffset;
	SwapWord(sizeof(int),&iTmp);
	fShp.Seek(iTmp*2 ,  CFile::begin );
	iTmp = shxRD.iContentLength;
	SwapWord(sizeof(int),&iTmp);
   
	
	return iTmp*2;	
}

/*************************************************
  ����:         ���ÿ��shp�����¼��¼ͷ����Ϣ
  ����:         ��¼ͷ�ṹ����
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE    
*************************************************/

BOOL CShpFile::GetRecordHeader(SHPRECORDHEADER& RecordHeader )
{
	int iLength,iNum;

	if(fShp.Read(&RecordHeader,sizeof(RecordHeader))!= sizeof(RecordHeader))
		return FALSE;
	if ( !m_bBigEndian )
    {  
		iNum    = RecordHeader.iRecordNum;
        iLength = RecordHeader.iContentLength;
		SwapWord(sizeof(int),&iLength);
		SwapWord(sizeof(int),&iNum);
		RecordHeader.iRecordNum = iNum;
        RecordHeader.iContentLength = iLength;
	}
    return TRUE;


}
/*************************************************
  ����:         ���ÿ��shp����������Ϣ
  ����:         ������Ϣ�ṹ����
  �����        �ɹ�����TRUE ʧ�ܷ���FALSE    
*************************************************/

BOOL CShpFile::GetShpInfo(SHPINFO& varInfo)
{

	if(fShp.Read(&varInfo,sizeof(varInfo))!= sizeof(varInfo))
		return FALSE;
	return TRUE;
}

/*************************************************
  ����:         ������������
  ����:         ���ݻ�����ָ�� ���������32K 
                ���������Ҫ�ֶ�ζ�ȡ��Ҫ��ȡ�ĳ��ȡ�
				�Ƿ��Ѷ�ȡ���
  �����        ��ȡ���ݵ�ʵ�ʳ���   
*************************************************/

int  CShpFile::ReadPoint(char* pszBuffer,int& iLength,BOOL& bEof)
{
	if ( iLength > MAX_BUFFER_SIZE)
    {
		iLength -= MAX_BUFFER_SIZE;
		if ( fShp.Read(pszBuffer,MAX_BUFFER_SIZE) != MAX_BUFFER_SIZE )
			return FILE_READERR;
		bEof = FALSE;
		return MAX_BUFFER_SIZE;
    }
    else
    {   
		if ( fShp.Read(pszBuffer,iLength) != (uint)iLength )
			return FILE_READERR;
		bEof = TRUE;
		return iLength;
	}     
}


/*************************************************
  ����:         ���ݵ�������shp�����Ƿ�ѡ��
  ����:         �����
  �����        ���ҵ�shp���������ֵ ����ֵ-��ʾδ���ҵ�   
*************************************************/
int CShpFile::SearchShape(CMapPoint& pt )
{
	/*xxh
	unsigned long iCount;
	POSITION pos;
    CMapPolygon *pPolygon;

	if ( GetShpType() != POLYGON ) //ֻ�ж϶���ζ���
		return -1;
	iCount = m_ObList.GetCount()-1;
	
	for ( pos = m_ObList.GetHeadPosition()  ; pos != NULL ;  )
    {
		pPolygon = (CMapPolygon*)m_ObList.GetAt(pos);
		if ( pPolygon->IsPointIn(pt) )
		 	return pPolygon->GetIndex(); 
		m_ObList.GetNext(pos); 
    } */
	return -1;

}
