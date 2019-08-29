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
  描述:         读入Shp、shx文件 格式 参阅ESRI技术白皮书
  输入:         文件名(全路径) 
  输出：        成功返回TRUE 失败返回FALSE
*************************************************/


BOOL CShpFile::ReadShp(CString& csFileName)
{
	int	  iTemp;
	CString csShxName;
	CFileException fe;
    SHPHEADER varHeader;
	
	//打开主文件
	if ( !fShp.Open(csFileName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	bShpOpen = TRUE;
    
	//打开索引文件
	csShxName = csFileName.Left(csFileName.GetLength() - 3);
	
	csShxName = csShxName + "shx";
    if ( !fShx.Open(csShxName, CFile::modeRead|CFile::shareDenyWrite,&fe))
		return FALSE;
	bShxOpen = TRUE;
       

	TRY
    {
	    //读主文件头 长100字节
		if ( fShp.Read(&varHeader , sizeof(SHPHEADER))!= sizeof(SHPHEADER))
			return FILE_READERR;
		
        iTemp = varHeader.iFileCode; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&iTemp);
		if ( iTemp != 9994 ) //是否是shp文件
			return FILE_CODEERR;
        if ( varHeader.iVersion != FILE_VERSION ) //文件版本是否正确
			return FILE_VERSIONERR;
        
		//shp 类型  		
		m_shpType = varHeader.iShpType;  
		m_shpFileLength = varHeader.iFileLength;
	    if ( !m_bBigEndian )
			SwapWord(sizeof(int),&m_shpFileLength);
		
		//保存数据最大矩形范围
		m_Extent.SetLeft(varHeader.dbXMin);
		m_Extent.SetRight(varHeader.dbXMax);
		m_Extent.SetTop(varHeader.dbYMin);
		m_Extent.SetBottom(varHeader.dbYMax);
        
		//读索引文件头 长100字节
		if ( fShx.Read(&varHeader , sizeof(SHPHEADER))!= sizeof(SHPHEADER))
			return FILE_READERR;
		iTemp = varHeader.iFileCode; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&iTemp);
		if ( iTemp != 9994 ) //是否是shx文件
			return FILE_CODEERR;
        if ( varHeader.iVersion != FILE_VERSION ) //文件版本是否正确
			return FILE_VERSIONERR;
		m_shxFileLength = varHeader.iFileLength; 
		if ( !m_bBigEndian )
			SwapWord(sizeof(int),&m_shxFileLength);
		//通过索引文件计算主文件记录个数 文件长度数值以16位计
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
  描述:         读入DBF文件格式 
  输入:         文件名(全路径) 
  输出：        成功返回TRUE 失败返回FALSE
*************************************************/
BOOL CShpFile::ReadDBF(CString& csFileName)
{
	CString csDbfName;
	BOOL bResult;
	//创建记录集对象
	pRecordSet = new CMapRecordSet;
	ASSERT ( pRecordSet != NULL ); 
	csDbfName = csFileName.Left(csFileName.GetLength() - 3);
	csDbfName = csDbfName + "dbf";
	//打开DBF文件
	bResult =  pRecordSet->openDBF(csDbfName); 
    if ( !bResult )
		delete pRecordSet;
	return bResult;
}

/*************************************************
  描述:         获得当前地图文件最大矩形范围 
  输入:         无
  输出：        地图矩形范围   
*************************************************/

CMapRectangle CShpFile::GetExtent()
{
	return m_Extent;
}

/*************************************************
  描述:         设置地图文件最大矩形范围 
  输入:         地图矩形范围
  输出：        无   
*************************************************/
void CShpFile::SetExtent(CMapRectangle& extent )
{
	m_Extent.SetLeft(extent.GetLeft());  
    m_Extent.SetRight(extent.GetRight());
	m_Extent.SetTop(extent.GetTop()); 
    m_Extent.SetBottom(extent.GetBottom());
}

/*************************************************
  描述:         设置Shp对象类型 
  输入:         shp 类型
  输出：        无   
*************************************************/
void CShpFile::SetShpType(int& iShpType)
{
	m_shpType = iShpType;
}

/*************************************************
  描述:         读入Shp对象坐标 
  输入:         无
  输出：        成功返回TRUE 失败返回FALSE  
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
				//读入点记录
				for ( i = 1 ; i <= m_iRecordCount ; i++ ) 
				{	
					iLength = SetRecordPos(i);
					if ( iLength <= 0 )
						return FALSE;

					//获得记录头信息
					if (!GetRecordHeader(RecordHeader))
						return FALSE;
					//记录内容长度是否与shp实体大小一致,索引记录长度是否与记录内容长度一致				
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
					//类型是否匹配
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
		    
			pszBuffer = new char [MAX_BUFFER_SIZE]; //分配缓冲区
			if ( pszBuffer == NULL )
				return FALSE;
			memset(pszBuffer , 0 , MAX_BUFFER_SIZE);
            
			//读入线记录
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
				//获得记录头信息
				if (!GetRecordHeader(RecordHeader))
					return FALSE;
				if ( !GetShpInfo(shpIn))
					return FALSE;
				 if (shpIn.ishpType != POLYLINE )//类型不匹配
                 {  
                      delete pLine;
					  continue;
				 }
				 if ( shpIn.iNumParts*sizeof(int) > MAX_BUFFER_SIZE )
                 {
					 //多义线段数大于最大缓冲区长度,忽略该对象
					 delete pLine;
					 continue;
                 } 
				 //计算对象内容实际长度
				 j = sizeof(SHPINFO) + shpIn.iNumParts*sizeof(int) ;
				 j += shpIn.iNumPoints*sizeof(SHPPOINT);  
                 
				 //判断实际长度是否与索引文件中记录的一致 
				 if ( RecordHeader.iContentLength*2 != j )
                 {
				     delete pLine;
					 continue;
				 }	 
				 //设置shp矩形范围
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
				 //读入多义线段索引
				 if ( fShp.Read(pIParts,shpIn.iNumParts*4) != (uint)(shpIn.iNumParts*4))
				 {
					delete pLine;
					return FALSE;
				 }

				 //点坐标存储所占字节数
				 iLength = shpIn.iNumPoints*sizeof(SHPPOINT);
				 //初始化缓冲区数据
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
					    k = pIParts[j];        //本段第一个顶点索引
					    m = shpIn.iNumPoints ; //下一个段第一个顶点索引 
                    }
              	    else
                    {
						k = pIParts[j];
						m = pIParts[j+1];
					}
					//处理第i段的顶点
				    for ( ; k < m ; k++)
                    {   
						pPoint = new CMapPoint();
						if ( pPoint == NULL )
							return FALSE;
						
						//需要读入数据更新缓冲区
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
						//需要读入数据更新缓冲区
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
			pszBuffer = new char [MAX_BUFFER_SIZE]; //分配缓冲区
			if ( pszBuffer == NULL )
				return FALSE;
			memset(pszBuffer , 0 , MAX_BUFFER_SIZE);
            
			//读入多边形记录
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
				//获得记录头信息
				if (!GetRecordHeader(RecordHeader))
					return FALSE;
				if ( !GetShpInfo(shpIn))
					return FALSE;
				 if (shpIn.ishpType != POLYGON )//类型不匹配
                 {  
                      delete pPolygon;
					  continue;
				 }
				 if ( shpIn.iNumParts*sizeof(int) > MAX_BUFFER_SIZE )
                 {
					 //复合多边型中的多边形个数大于最大缓冲区长度,忽略该对象
					 delete pPolygon;
					 continue;
                 } 
				 //计算对象内容实际长度
				 j = sizeof(SHPINFO) + shpIn.iNumParts*sizeof(int) ;
				 j += shpIn.iNumPoints*sizeof(SHPPOINT);  
                 
				 //判断实际长度是否与索引文件中记录的一致 
				 if ( RecordHeader.iContentLength*2 != j )
                 {
				     delete pPolygon;
					 continue;
				 }	 
				 //设置shp矩形范围
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
				 //读入复合多边型段索引
				 if ( fShp.Read(pIParts,shpIn.iNumParts*4) != (uint)(shpIn.iNumParts*4))
				 {
					delete pPolygon;
					return FALSE;
				 }

				 //点坐标存储所占字节数
				 iLength = shpIn.iNumPoints*sizeof(SHPPOINT);
				 //初始化缓冲区数据
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
					    k = pIParts[j];        //本段第一个顶点索引
					    m = shpIn.iNumPoints ; //下一个段第一个顶点索引 
                    }
              	    else
                    {
						k = pIParts[j];
						m = pIParts[j+1];
					}
					//处理第i段的顶点
				    for ( ; k < m ; k++)
                    {   
						pPoint = new CMapPoint();
						if ( pPoint == NULL )
							return FALSE;
						
						//需要读入数据更新缓冲区
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
						//需要读入数据更新缓冲区
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
  描述:         计算每条shp对象相对文件头的偏移量
  输入:         记录索引值(从零开始)
  输出：        该shp对象数据在文件中的位置  
*************************************************/
int CShpFile::SetRecordPos( int iRecord )
{
    unsigned int iOffset,iTmp;
	SHXRECORD shxRD;

	if ( iRecord < 0 )
		return 0;
    //获得索引文件记录偏移量相对文件头
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
  描述:         获得每条shp对象记录记录头的信息
  输入:         记录头结构对象
  输出：        成功返回TRUE 失败返回FALSE    
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
  描述:         获得每条shp对象描述信息
  输入:         描述信息结构对象
  输出：        成功返回TRUE 失败返回FALSE    
*************************************************/

BOOL CShpFile::GetShpInfo(SHPINFO& varInfo)
{

	if(fShp.Read(&varInfo,sizeof(varInfo))!= sizeof(varInfo))
		return FALSE;
	return TRUE;
}

/*************************************************
  描述:         读入点对象数据
  输入:         数据缓冲区指针 缓冲区最大32K 
                如果超出需要分多次读取，要读取的长度、
				是否已读取完成
  输出：        读取数据的实际长度   
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
  描述:         根据点对象查找shp对象是否选中
  输入:         点对象
  输出：        查找到shp对象的索引值 返回值-表示未查找到   
*************************************************/
int CShpFile::SearchShape(CMapPoint& pt )
{
	/*xxh
	unsigned long iCount;
	POSITION pos;
    CMapPolygon *pPolygon;

	if ( GetShpType() != POLYGON ) //只判断多边形对象
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
