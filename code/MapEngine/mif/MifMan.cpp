// MifMan.cpp: implementation of the CMifMan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmap.h"
#include "MifMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMifMan::CMifMan()
{
	m_pMapLeyerMan = NULL;
}

CMifMan::~CMifMan()
{
	m_pMapLeyerMan = NULL;
}
bool CMifMan::Init( CMapLeyerMan* pMapLeyerMan )
{
	m_pMapLeyerMan = pMapLeyerMan;
	m_iID = 0;
	return true;
}
bool CMifMan::loaddata( string strfile )
{
//	m_pMapLeyerMan->ClearAllMapLayer();
	string strFileMif = strfile;
	strFileMif += ".mif";
	string strFileMid = strfile;
	strFileMid += ".mid";
	this->loadmif(strFileMif);
	this->loadmid(strFileMid);
/*	if ( this->m_arrMifPoint.size() ==  this->m_arrMidPoint.size() ) {
		for ( int i=0;i<m_arrMifPoint.size();i++) {
			m_arrMifPoint[i].strText = m_arrMidPoint[i].strText;
		}
		return true;
	}*/
	return false;
}
char* GetPoint( char* pData, mifPoint& mifpoint )
{
	char* pTemp = pData;
	char* pTempData = NULL;
	char cTemp[20];
	//经度
	pTemp = strstr(pTemp,"Point ");
	if ( pTemp == NULL ) {
		return NULL;
	}
	pTempData = pTemp + 6;
	//经度
	pTemp = strchr(pTempData, 0x20);	//空格
	if ( pTemp == NULL ) {
		return NULL;
	}
	memset(cTemp,0,20);
	memcpy( cTemp, pTempData, pTemp - pTempData );
	mifpoint.dx = atof( cTemp ); 
	//纬度
	pTempData = pTemp + 1;
	pTemp = strstr(pTempData, "\r\n");	//回车换行
	if ( pTemp == NULL ) {
		return NULL;
	}
	memset(cTemp,0,20);
	memcpy( cTemp, pTempData, pTemp - pTempData );
	mifpoint.dy = atof( cTemp );
	
	
	return pTemp+2;
}
char* GetPointName( char* pData, mifPoint& mifpoint )
{
	char* pTemp = pData;
	char* pTempData = NULL;
	char cTemp[50];
	//名字
	pTemp = strchr(pTemp,0x22);	//引号
	if ( pTemp == NULL ) {
		return NULL;
	}
	pTempData = pTemp + 1;
	//经度
	pTemp = strchr(pTempData, 0x22);	//引号
	if ( pTemp == NULL ) {
		return NULL;
	}
	memset(cTemp,0,50);
	memcpy( cTemp, pTempData, pTemp - pTempData );
	mifpoint.strText = cTemp;
//	pTemp ++;
//	if ( *pTemp != '\r') {
//		return pTemp;
//	}
//	pTemp ++;
//	if ( *pTemp != '\n') {
//		return pTemp;
//	}
	return pTemp+2;
}
bool CMifMan::loadmif(string strfile )
{
//DATA区图形对象
//l 点（point）  
//l 直线（line）  
//l 折线（polyline）  
//l 区域（region）  
//l 圆弧（arc）  
//l 文本（text）  
//l 矩形（rectangle）  
//l 圆角矩形（rounded  rectangle）  
//l 椭圆（ellipse）

	CVOSFile file;
	if(!file.Open( strfile.c_str(), fomOnlyRead ))
		return false;
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	memset( Buffer, 0, iLen+1 );
	char* pTemp = Buffer;
	int i = 0;
	while ( 1 ) {
		i ++;
		if ( i==13 ) {
			i ++;
		}
		int iReadlen = file.Read( pTemp, 1024 );
		if ( iReadlen <= 0 ) {
			break;
		}
		pTemp += iReadlen;
	}
	file.Close();
	string strCombine = Buffer;
	/*
	pTemp = Buffer;
	string str1 = Buffer;
	int iiii = str1.length();
	this->m_arrMifPoint.clear();
	mifPoint mifpoint;
	while ( 1 ) 
	{
		pTemp = GetPoint( pTemp, mifpoint );
		if ( pTemp == NULL ) {
			break;
		}
		i ++;
		if( i == 2179 )
		{
			this->m_arrMifPoint.push_back( mifpoint );
		}
		else
			this->m_arrMifPoint.push_back( mifpoint );
	}

	int iCOunt11 = m_arrMifPoint.size();
	*/

		//文件头各元素的值
	//Version Charset Delimiter CoordSys Columns

	int iIndex1;//元素的起始位置
	int iIndex2;//元素的结束位置
	int iIndex3;//行尾\r\n的位置
	int iIndexT;//元素对应内容的起始位置

	//版本号 Version
	iIndex1 = strCombine.find("Version");
	if(iIndex1 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	//MIFFile.Close();
	iIndex2 = iIndex1 + 7;

	if(iIndex2 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	else
	{
//		bFileOpened = TRUE;

		iIndex3 = strCombine.find("\r\n", iIndex2 + 1);
		if(iIndex3 == -1)
		{
			//MIFFile.Close();
			return false;
		}
		iIndexT = iIndex2 + 1;
		
		strVer = strCombine.substr(iIndexT, iIndex3 - iIndexT);
		//MyRefresh();
		//AfxMessageBox(strVer);
	}

	//字符集 Charset
	iIndex1 = strCombine.find("Charset");
	if(iIndex1 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	//MIFFile.Close();
	iIndex2 = iIndex1 + 7;

	if(iIndex2 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	else
	{
//		bFileOpened = TRUE;

		iIndex3 = strCombine.find("\r\n", iIndex2 + 1);
		if(iIndex3 == -1)
		{
			//MIFFile.Close();
			return false;
		}
		iIndexT = iIndex2 + 1 + 1;
		
		strCharset = strCombine.substr(iIndexT, iIndex3 - 1 - iIndexT);
		//MyRefresh();
		//AfxMessageBox(strCharset);
	}

	//分隔符 Delimiter
	iIndex1 = strCombine.find("Delimiter");
	if(iIndex1 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	//MIFFile.Close();
	iIndex2 = iIndex1 + 9;

	if(iIndex2 == -1)
	{
		//MIFFile.Close();
		return false;
	}
	else
	{
//		bFileOpened = TRUE;

		iIndex3 = strCombine.find("\r\n", iIndex2 + 1);
		if(iIndex3 == -1)
		{
			//MIFFile.Close();
			return false;
		}
		iIndexT = iIndex2 + 1 + 1;
		
		strDelimiter = strCombine.substr(iIndexT, iIndex3 - 1 - iIndexT);
		//MyRefresh();
		//AfxMessageBox(strCharset);
	}

	//DATA区图形对象
//l 点（point）  
//l 直线（line）  
//l 折线（polyline）  
//l 区域（region）  
//l 圆弧（arc）  
//l 文本（text）  
//l 矩形（rectangle）  
//l 圆角矩形（rounded  rectangle）  
//l 椭圆（ellipse）

	int nLength;         //文件总长
	int nCountPoint=0;   //Point 计数
	int nCountLine=0;    //Line
	int nCountPline=0;   //Pline
	int nCountRegion=0;  //Region
	int PointIndex[10240] = {NULL};//存放 Point字串的位置
	int LineIndex[10240] = {NULL};
	int PlineIndex[10240] = {NULL};
	int RegionIndex[10240] = {NULL};

	nLength = strCombine.length();

	//获取Point位置
	for( i=0;i<nLength-5;i++)
	{
		if(strCombine.substr(i,5)=="Point")
		{
			PointIndex[nCountPoint]=i;
			nCountPoint++;
		}
	}
	//Line
	for(int iL=0;iL<nLength-4;iL++)
	{
		if(strCombine.substr(iL,4)=="Line")
		{
			LineIndex[nCountLine]=iL;
			nCountLine++;
		}
	}
	//Pline
	for(int iPl=0;iPl<nLength-5;iPl++)
	{
		if(strCombine.substr(iPl,5)=="Pline")
		{
			PlineIndex[nCountPline]=iPl;
			nCountPline++;
		}
	}
	//Region
	for(int iR=0;iR<nLength-6;iR++)
	{
		if(strCombine.substr(iR,6)=="Region")
		{
			RegionIndex[nCountRegion]=iR;
			nCountRegion++;
		}
	}
	//CString strStatus;
	//strStatus.Format("各图形对象数目\r\n\r\nPoint：%d\r\nLine：%d\r\nPline：%d\r\nRegion：%d",
//	strStatus.Format("Point:%d  Line:%d  Pline:%d  Region:%d",
//		nCountPoint,nCountLine,nCountPline,nCountRegion);

	bool bFileOpened = TRUE;
	//MyRefresh();
	//AfxMessageBox(strStatus);

	//头信息
/*xxh	CClientDC dc(this);
	if(bFileOpened)
	{
		dc.ExtTextOut(1, 0, ETO_OPAQUE, NULL, "版    本："+strVer, NULL);
		dc.ExtTextOut(1, 16, ETO_OPAQUE, NULL, "\r\n", NULL);
		dc.ExtTextOut(1, 16, ETO_OPAQUE, NULL, "字符集："+strCharset, NULL);
		dc.ExtTextOut(1, 32, ETO_OPAQUE, NULL, "\r\n", NULL);
		dc.ExtTextOut(1, 32, ETO_OPAQUE, NULL, "分隔符："+strDelimiter, NULL);
		dc.ExtTextOut(1, 48, ETO_OPAQUE, NULL, "\r\n", NULL);
		dc.ExtTextOut(1, 48, ETO_OPAQUE, NULL, strStatus, NULL);
	}*/
	//绘制各元素
	int nScale=10; //比例
	int nDeltaX=120;//偏移量
	int nDeltaY=20;
	//Point
	int iIndexPointXStart;  //point.x开始位置
	int iIndexPointXEnd;    //point.x结尾位置
	string strPointX;      //Point.x

	int iIndexPointYStart;  //point.y开始位置
	int iIndexPointYEnd;    //point.y结尾位置
	string strPointY;      //Point.y
	for(int count=0;count<nCountPoint;count++)
	{
		iIndexPointXStart = PointIndex[count]+5+1;
		iIndexPointXEnd = strCombine.find(" ",iIndexPointXStart);
		strPointX = strCombine.substr( iIndexPointXStart, iIndexPointXEnd-iIndexPointXStart );

		iIndexPointYStart = iIndexPointXEnd + 1;
		iIndexPointYEnd = strCombine.find("\r\n",iIndexPointYStart);
		strPointY = strCombine.substr( iIndexPointYStart, iIndexPointYEnd-iIndexPointYStart );

		m_iID++;
		this->m_pMapLeyerMan->CreatMapPoint( m_iID,atof(strPointX.c_str()),atof(strPointY.c_str()),"","",4 );
		/*
		int ptx,pty;
		
		ptx = (atof(strPointX)-nDeltaX)*nScale;
		pty = (atof(strPointY)-nDeltaY)*nScale;*/
		//ptx = (atof(strPointX)-(int)atof(strPointX))*400;
		//pty = (atof(strPointY)-(int)atof(strPointY))*400;

	/*	dc.MoveTo(ptx,pty-5);
		dc.LineTo(ptx,pty+5);

		dc.MoveTo(ptx-5,pty);
		dc.LineTo(ptx+5,pty);*/
	}

	//Line
	int iIndexLineX1Start;  //point1.x第一点开始位置
	int iIndexLineX1End;    //point1.x结尾位置
	string strLineX1;      //Point1.x

	int iIndexLineY1Start;
	int iIndexLineY1End;
	string strLineY1;

	int iIndexLineX2Start;  //point2.x第二点开始位置
	int iIndexLineX2End;
	string strLineX2;

	int iIndexLineY2Start;
	int iIndexLineY2End;
	string strLineY2;
	for(int countL=0;countL<nCountLine;countL++)
	{
		iIndexLineX1Start = LineIndex[countL]+4+1;
		iIndexLineX1End = strCombine.find(" ",iIndexLineX1Start);
		strLineX1 = strCombine.substr(iIndexLineX1Start,iIndexLineX1End-iIndexLineX1Start);

		iIndexLineY1Start = iIndexLineX1End+1;
		iIndexLineY1End = strCombine.find(" ",iIndexLineY1Start);
		strLineY1 = strCombine.substr(iIndexLineY1Start,iIndexLineY1End-iIndexLineY1Start);
		
		iIndexLineX2Start = iIndexLineY1End+1;
		iIndexLineX2End = strCombine.find(" ",iIndexLineX2Start);
		strLineX2 = strCombine.substr(iIndexLineX2Start,iIndexLineX2End-iIndexLineX2Start);

		iIndexLineY2Start = iIndexLineX2End+1;
		iIndexLineY2End = strCombine.find("\r\n",iIndexLineY2Start);
		strLineY2 = strCombine.substr(iIndexLineY2Start,iIndexLineY2End-iIndexLineY2Start);
		
		m_iID++;
		this->m_pMapLeyerMan->CreatMapLine( m_iID );
		m_pMapLeyerMan->AddMapLinePoint( m_iID,atof(strLineX1.c_str()),atof(strLineY1.c_str()) );
		m_pMapLeyerMan->AddMapLinePoint( m_iID,atof(strLineX2.c_str()),atof(strLineY2.c_str()) );
		/*
		int ptx1,pty1,ptx2,pty2;
		ptx1 = (atof(strLineX1)-nDeltaX)*nScale;
		pty1 = (atof(strLineY1)-nDeltaY)*nScale;
		ptx2 = (atof(strLineX2)-nDeltaX)*nScale;
		pty2 = (atof(strLineY2)-nDeltaY)*nScale;
		*/
	//	dc.MoveTo(ptx1,pty1);
	//	dc.LineTo(ptx2,pty2);

		//dc.MoveTo((ptx1+361100.141088+200000)/2000,(pty1+406844.7804)/2000);
		//dc.LineTo((ptx2+361100.141088+200000)/2000,(pty2+406844.7804)/2000);
	}
	//Region
	CPoint numpts[1024];       //每个分区的节点数，设最大1024
	int iIndexRegionStart;  //分区值的开始位置
	int iIndexRegionEnd;    //分区值的结尾位置
	int iIndexNumptsEnd;    //节点值的结尾位置,开始位置为iIndexRegionEnd+4
	int iIndexX;            //point.x位置
	int RegionXEnd;         //point.x尾位置
	int iIndexY;            //point.y位置
	string strRegionPointX;            //point.x
	string strRegionPointY;            //point.y
	string strPolygons;    //分区值
	string strNumpts;      //节点值


	for(int countR=0;countR<nCountRegion;countR++)
	{
		iIndexRegionStart = RegionIndex[countR] + 6 + 2;//两个空格
		iIndexRegionEnd = strCombine.find("\r\n",RegionIndex[countR]);
		strPolygons = strCombine.substr(iIndexRegionStart,iIndexRegionEnd-iIndexRegionStart);
		//if(strPolygons=="1")
		{
			iIndexNumptsEnd = strCombine.find("\r\n",iIndexRegionEnd + 4);
			//strNumpts个节点
			strNumpts = strCombine.substr(iIndexRegionEnd + 4,
				iIndexNumptsEnd-(iIndexRegionEnd + 4));
			iIndexX = iIndexNumptsEnd+2;
			m_iID++;
			this->m_pMapLeyerMan->CreatMapPolygon( m_iID );
		//	m_pMapLeyerMan->setc( m_iID, 0XFF0000);
			for(int countNumpts=0;countNumpts<atoi(strNumpts.c_str());countNumpts++)
			{
				//point.x
				RegionXEnd=strCombine.find(" ",iIndexX);
				strRegionPointX = strCombine.substr(iIndexX,RegionXEnd-iIndexX);
				//point.y
				strRegionPointY=strCombine.substr(RegionXEnd+1,
					strCombine.find("\r\n",iIndexX)-(RegionXEnd+1));
				iIndexX = strCombine.find("\r\n",iIndexX) + 2;
				m_pMapLeyerMan->AddMapPolygonPoint( m_iID,atof(strRegionPointX.c_str()),atof(strRegionPointY.c_str())  );
			//	numpts[countNumpts].x=(atof(strRegionPointX)-nDeltaX)*nScale;
			//	numpts[countNumpts].y=(atof(strRegionPointY)-nDeltaY)*nScale;
			}
		//xxh	dc.Polygon(numpts, atoi(strNumpts));
		}	
	//	else
	//	{
	//	}
	}

	//Pline 暂未处理 MULTIPLE
	CPoint numPlinepts[1024];//节点数，设最大1024
	int iIndexPlineStart;   //Pline 节点数开始位置
	int iIndexPlineEnd;  
	string strPlineNmupts; //Pline 节点个数

	int PlineXEnd;//point.x尾位置
	string strPlinePointX;//point.x	
	string strPlinePointY;//point.y

	for(int countPL=0;countPL<nCountPline;countPL++)
	{
		iIndexPlineStart = PlineIndex[countPL] + 5 + 1;//一个空格
		iIndexPlineEnd = strCombine.find("\r\n",PlineIndex[countPL]);
		strPlineNmupts = strCombine.substr(iIndexPlineStart,iIndexPlineEnd-iIndexPlineStart);
		m_iID++;
		this->m_pMapLeyerMan->CreatMapLine( m_iID );
		m_pMapLeyerMan->SetMapLineColor( m_iID, 0XFF0000);
		for(int countPlineNumpts=0;countPlineNumpts<atoi(strPlineNmupts.c_str());countPlineNumpts++)
		{
			PlineXEnd=strCombine.find(" ",iIndexPlineEnd+2);
			//point.x
			strPlinePointX = strCombine.substr(iIndexPlineEnd+2,PlineXEnd-(iIndexPlineEnd+2));
			//point.y
			strPlinePointY=strCombine.substr(PlineXEnd+1,
				strCombine.find("\r\n",iIndexPlineEnd+2)-(PlineXEnd+1));
			iIndexPlineEnd= strCombine.find("\r\n",iIndexPlineEnd+2);
			m_pMapLeyerMan->AddMapLinePoint( m_iID,atof(strPlinePointX.c_str()),atof(strPlinePointY.c_str()) );
		//	numPlinepts[countPlineNumpts].x=(atof(strPlinePointX)-nDeltaX)*nScale;
		//	numPlinepts[countPlineNumpts].y=(atof(strPlinePointY)-nDeltaY)*nScale;
		}

	//xxh	dc.Polyline(numPlinepts, atoi(strPlineNmupts));
	}
	
	return true;
}
bool CMifMan::loadmid(string strfile )
{
	//读取数据
	CVOSFile file;
	if(!file.Open( strfile.c_str(), fomOnlyRead ))
		return false;
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	char* pTemp = Buffer;
	while ( 1 ) {
		int iReadlen = file.Read( pTemp, 1024 );
		if ( iReadlen <= 0 ) {
			break;
		}
		pTemp += iReadlen;
	}
	file.Close();
	pTemp++;
	pTemp = 0;
	pTemp = Buffer;
	//-------------处理数据
	this->m_arrMidPoint.clear();
	mifPoint mifpoint;
	int i = 0;
	while ( 1 ) 
	{
		pTemp = GetPointName( pTemp, mifpoint );
		if ( pTemp == NULL ) {
			break;
		}
		//this->m_arrMidPoint.push_back( mifpoint );
		i++;
		this->m_pMapLeyerMan->SetMapPointName( i,mifpoint.strText );
	}
	int iCount = m_arrMidPoint.size();
	return true;
}