// BackLayer.cpp: implementation of the CBackLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "BackLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBackLayer::CBackLayer()
{
	m_lID = 0;
}

CBackLayer::~CBackLayer()
{
	m_lID = 0;
}
//加载地图数据
void CBackLayer::Load( string strFilePath,CMapPoiRes* pRes )
{
	m_pMapPoiRes = pRes;
	m_lICOID = m_pMapPoiRes->CreateRes( "point.png" );
	CreateDirectory( strFilePath.c_str(),NULL);
	m_strFilePath = strFilePath;
	RemoveAll();
	ReadMapPoint();
	ReadMapLine();
	ReadMapPolygon();
	ReadMapText();
	ReadMap123();
	LoadMap2000();
	//CreateMapText(100,116,39,"大家好！",14 );
	//SaveAllMapText();
//	SaveAllMapLine();
	//LoadKML();
}
bool CBackLayer::LoadKML()
{
	string strFileName = m_strFilePath;
	strFileName += "map.kml";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
		return false;
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	memset( Buffer, 0, iLen+1 );
	char* pTemp = Buffer;
	while ( 1 ) {
		int iReadlen = file.Read( pTemp, 1024 );
		if ( iReadlen <= 0 ) {
			break;
		}
		pTemp += iReadlen;
	}
	file.Close();
	this->ParseKML( Buffer, iLen );
	free( Buffer );
	return true;
}

//1为点，2为线,3为多边形，0为其他
int CheckKMLDataType( char* pData, int nlen )
{
	//类型
	char* pTemp = strstr( pData, "<Point>" );
	if( pTemp )
		return 1;
	pTemp = strstr( pData, "<LineString>" );
	if( pTemp )
		return 2;
	pTemp = strstr( pData, "<LinearRing>" );
	if( pTemp )
		return 3;
	return 0;
}
char* CBackLayer::ParasKMLData( char* pData, int nlen )
{
	//开始位置
	char* pTemp = strstr( pData, "<Placemark>" );
	if( pTemp == NULL )
		return NULL;
	pTemp += 10;
	//结束位置
	char* pTempEnd = strstr( pTemp, "</Placemark>" );
	if( pTempEnd == NULL )
		return NULL;
	pTempEnd[0] = 0;

	char chTemp[100];
	//中间处理
	//名字
	char* pTemp1 = strstr( pTemp, "<name>" );
	if( pTemp1 == NULL )
		return NULL;
	pTemp1 += 6;
	//--
	pTemp = strstr( pTemp1, "</name>" );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	CVOSUtil::UTF8ToGB2312( pTemp1, chTemp, pTemp - pTemp1 );
	string strName = chTemp;
	pTemp += 7;
	//类型
	int itype = CheckKMLDataType( pTemp, nlen );
	//点
	if( itype == 1 )
	{
		//点
		pTemp1 = strstr( pTemp, "<coordinates>" );
		if( pTemp1 == NULL )
			return NULL;
		pTemp1 += 13;
		//--
		pTemp = strstr( pTemp1, "," );
		if( pTemp == NULL )
			return NULL;
		pTemp[0]=0;
		double dLon = atof( pTemp1 );
		pTemp1 = pTemp+1;
		//--
		pTemp = strstr( pTemp1, "," );
		if( pTemp == NULL )
			return NULL;
		pTemp[0]=0;
		pTemp += 1;
		double dLan = atof( pTemp1 );

		CreatMapPoint( m_lID++, dLon, dLan, strName,"",m_lICOID );
	}
	return pTempEnd+12;
}
bool CBackLayer::ParseKML( char* pData, int nlen )
{
	char* pTemp = pData;
	int i = 0;
	while( 1 )
	{
		/*if( i > 5000 )
		{
			break;
		}*/
		pTemp = ParasKMLData( pTemp, nlen );
		if( pTemp == NULL )
			break;
		i++;
	}
	return true;
}
//添加地图信息点
bool CBackLayer::SaveMapPoint( double x, double y, string strName, string strText, long icoID )
{
	int count = this->m_arrPoi.size();
	CreatMapPoint( count, x,y,strName,strText,icoID );
	SaveAllMapPoint();
	return true;
}
//添加地图线
bool CBackLayer::SaveMapLine( string strMapPoints, string strName, long width, long bgrcolor )
{
	/*
	string strFileName = m_strFilePath;
	strFileName += "mapline.txt";
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite ) )
	{
		if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			return false;
	}
	file.SeekToEnd();
	*/
	char* chTemp =new char[ strMapPoints.length()+512];
	sprintf( chTemp, "mapline:{%s,%d,%d,{%s}}\r\n",strName.c_str(),width,bgrcolor,strMapPoints.c_str() );
	//file.Write( chTemp, strlen( chTemp ) );
	//file.Close();
	//long pointid, double x, double y, string strName, string strText, short icoID
	int count = this->m_arrLine.size();
	CreatMapLine( count );
	//AddMapLinePoint();
	ParseMapLine( chTemp, strlen(chTemp) ,count );
	delete chTemp;
	SaveAllMapLine();
	return true;
}
//添加地图文本信息
bool CBackLayer::SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor )
{
	int count = this->m_arrMapText.size();
	CreateMapText( count, x, y , strText.c_str(), fontsize, bgrcolor );
	SaveAllMapText();
	return true;
}
//清除地图保存信息
bool CBackLayer::ClearMapSaveData()
{
	//
	RemoveAll();

	string strFileName = m_strFilePath;
	strFileName += "mappoint.txt";
	CVOSFile::Remove( strFileName.c_str() );
	CVOSFile file;
	if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
		file.Close();

	//
	string strFileName1 = m_strFilePath;
	strFileName1 += "mapline.txt";
	CVOSFile::Remove( strFileName1.c_str() );
	CVOSFile file1;
	if( file1.Open( strFileName1.c_str(), fomReadWrite|fomCreate ) )
		file1.Close();
	return true;
}
void CBackLayer::SaveAllMapPoint()
{
	string strFileName = m_strFilePath;
	strFileName += "mappoint.txt";
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
		return;
	char chTemp[1024]={0};
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		string strICOName = m_pMapPoiRes->GetResName( poi->m_sResID );
		sprintf( chTemp, "%d,%s,%f,%f,%s\r\n",poi->m_sPOIID,poi->m_strPoiName.c_str(),poi->m_Point.x,poi->m_Point.y,
		strICOName.c_str() );
		file.Write( chTemp, strlen( chTemp ) );
    }
	file.Close();	
}
void CBackLayer::SaveAllMapText()
{
	string strFileName = m_strFilePath;
	strFileName += "maptext.txt";
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
		return;
	char chTemp[1024]={0};
	for (list<CMapText*>::iterator it = m_arrMapText.begin(); it != m_arrMapText.end(); ++it)
    {
        CMapText* pMapText = *it;
		sprintf( chTemp, "%d,%s,%f,%f,%d,%d\r\n",pMapText->tid, pMapText->text.c_str(),pMapText->m_Point.x,pMapText->m_Point.y, pMapText->m_size, pMapText->color );
		file.Write( chTemp, strlen( chTemp ) );
    }
	file.Close();
	list<CMapText*> m_arrMapText;
}
void CBackLayer::SaveAllMapLine()
{
	string strFileName = m_strFilePath;
	strFileName += "mapline.txt";
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
		return;
	char chTemp[64];
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		MapPoint* pPoint = NULL;
		sprintf( chTemp, "%d,%s,%d,%d,",line->m_lineid,line->m_strname.c_str(),line->m_width,line->m_color);
		string strData = chTemp;
		int i=0;
		for (vector<MapPoint*>::iterator it = line->m_arrPoint.begin(); it != line->m_arrPoint.end(); ++it)
		{
			pPoint = *it;
			if( i == 0 )
				sprintf( chTemp, "%f,%f",pPoint->x,pPoint->y);
			else
				sprintf( chTemp, ",%f,%f",pPoint->x,pPoint->y);
			i++;
			strData += chTemp;
		}
		strData += "\r\n";
		file.Write( (void*)strData.c_str(), strData.length() );
    }
	file.Close();
}
void CBackLayer::SaveAllMapPolygon()
{
	string strFileName = m_strFilePath;
	strFileName += "mappolygon.txt";
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
		return;
	char chTemp[64];
	for (list<CMapPolygon*>::iterator it = m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        CMapPolygon* pPolygon = *it;
		MapPoint* pPoint = NULL;
		sprintf( chTemp, "{%d,%s,%d,%d,{",pPolygon->m_polygonID,pPolygon->m_strname.c_str(),pPolygon->m_width,pPolygon->m_color);
		string strData = chTemp;
		int i=0;
		for (vector<MapPoint*>::iterator it = pPolygon->m_arrPoint.begin(); it != pPolygon->m_arrPoint.end(); ++it)
		{
			pPoint = *it;
			if( i == 0 )
				sprintf( chTemp, "%f,%f",pPoint->x,pPoint->y);
			else
				sprintf( chTemp, ";%f,%f",pPoint->x,pPoint->y);
			i++;
			strData += chTemp;
		}
		strData += "}}\r\n";
		file.Write( (void*)strData.c_str(), strData.length() );
    }
	file.Close();
}
char* CBackLayer::ParseMapPoint(char* pBuf, int iLen,int nIndex )
{
	char* pTemp = strstr( pBuf, "mappoint:{" );
	if( pTemp == NULL )
		return NULL;
	//---名字
	char* pTemp1 = pTemp + strlen("mappoint:{");
	pTemp = strstr( pBuf, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;

	string strName = pTemp1;
	//经度
	pTemp1 = pTemp+1;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	double dLon = atof( pTemp1 );
	//纬度
	pTemp1 = pTemp+1;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	double dLan = atof( pTemp1 );
	//图标名称
	pTemp1 = pTemp+1;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;

	string strICOName = pTemp1;
	//文本
	pTemp1 = pTemp+1;
	pTemp = strstr( pTemp1, "}" );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	string strText = pTemp1;
	//--
	long sICOID = m_pMapPoiRes->CreateRes( strICOName );
	CreatMapPoint( nIndex, dLon, dLan, strName,strText,sICOID );
	pTemp++;
	return pTemp;
}
bool CBackLayer::ReadMapLine()
{
	string strFileName = m_strFilePath;
	strFileName += "mapline.txt";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	//--
	string strdata = Buffer;
	std::vector<std::string> v_strtext = STR_Split( strdata, "\r\n" );
	int isize =  v_strtext.size();
	for( int i=0;i< v_strtext.size();i++ )
	{
		std::vector<std::string> v_str = STR_Split( v_strtext[i], "," );
		if( v_str.size() > 5 )
		{
			//CreateMapText(i,atof(v_str[2].c_str()),atof( v_str[3].c_str() ),v_str[1].c_str(),atoi(v_str[4].c_str()),atoi(v_str[5].c_str()) );
			//long sICOID = m_pMapPoiRes->CreateRes( v_str[4].c_str() );
			//CreatMapPoint( i, atof(v_str[2].c_str()),atof( v_str[3].c_str() ), v_str[1].c_str(),"",sICOID );
			CreatMapLine( i );
			SetMapLineName( i,v_str[1].c_str());
			SetMapLineWidth( i,atoi(v_str[2].c_str()));
			SetMapLineColor( i,atoi(v_str[3].c_str()));
			for( int j=4;j<v_str.size(); )
			{
				MapPoint* pNew = new MapPoint(); 
				pNew->x = atof(v_str[j].c_str());
				pNew->y = atof(v_str[j+1].c_str());
				AddMapLinePoint( i, pNew );
				j+=2;
			}
		}
	}
	/*
	char* pTemp=Buffer;
	int nIndex=0;
	char* pTemp1=NULL;
	while( pTemp )
	{
		pTemp1 = strstr( pTemp, "}}" );
		if( pTemp1 == NULL )
			break;
		pTemp1[1]=0;
		ParseMapLine( pTemp, iLen,nIndex );
		pTemp = pTemp1+2;
		nIndex++;
	}*/
	free( Buffer );
	return true;
}
bool CBackLayer::ReadMapPolygon()
{
	string strFileName = m_strFilePath;
	strFileName += "mappolygon.txt";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	char* pTemp=Buffer;
	int nIndex=0;
	char* pTemp1=NULL;
	while( pTemp )
	{
		pTemp1 = strstr( pTemp, "}}" );
		if( pTemp1 == NULL )
			break;
		pTemp1[1]=0;
		ParseMapPolygon( pTemp, iLen,nIndex );
		pTemp = pTemp1+2;
		nIndex++;
	}
	free( Buffer );
	return true;
}
//解析
char* CBackLayer::ParseMapLine(char* pBuf, int iLen, int nIndex )
{
	char* pTemp = strstr( pBuf, "{" );
	if( pTemp == NULL )
		return NULL;
	//---编号
	char* pTemp1 = pTemp + strlen("{");
	pTemp = strstr( pBuf, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	string strName = pTemp1; 
	long llineid = atoi( pTemp1 );
	pTemp++;
	//---名字
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	strName = pTemp1;
	pTemp++;
	//--
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	long lwidth = atoi( pTemp1 );
	pTemp++;
	//--
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	long lcolor = atoi( pTemp1 );
	pTemp++;
	//--
	CreatMapLine( nIndex );

	while( pTemp )
	{
		//经度
		pTemp1 = pTemp+1;
		pTemp = strstr( pTemp1, "," );
		if( pTemp == NULL )
			break;
		pTemp[0]=0;
		double dLon = atof( pTemp1 );
		//纬度
		pTemp1 = pTemp+1;
		pTemp = strstr( pTemp1, ";" );
		if( pTemp == NULL )
		{
			pTemp = strstr( pTemp1, "}" );
			if( pTemp == NULL )
			{
				break;
			}
		}
		pTemp[0]=0;
		double dLan = atof( pTemp1 );
		pTemp1 = pTemp+1;

		MapPoint* pNew = new MapPoint(); 
		pNew->x = dLon;
		pNew->y = dLan;
		AddMapLinePoint( nIndex, pNew );
	}
	SetMapLineName( nIndex,strName);
	SetMapLineWidth( nIndex,lwidth);
	SetMapLineColor( nIndex,lcolor);
	return pTemp;
}
//解析
char* CBackLayer::ParseMapPolygon(char* pBuf, int iLen, int nIndex )
{
	char* pTemp = strstr( pBuf, "{" );
	if( pTemp == NULL )
		return NULL;
	//---编号
	char* pTemp1 = pTemp + strlen("{");
	pTemp = strstr( pBuf, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	string strName = pTemp1; 
	long llineid = atoi( pTemp1 );
	pTemp++;
	//---名字
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	strName = pTemp1;
	pTemp++;
	//--
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	long lwidth = atoi( pTemp1 );
	pTemp++;
	//--
	pTemp1 = pTemp;
	pTemp = strstr( pTemp1, "," );
	if( pTemp == NULL )
		return NULL;
	pTemp[0]=0;
	long lcolor = atoi( pTemp1 );
	pTemp++;
	//--
	CreatMapPolygon( nIndex );

	while( pTemp )
	{
		//经度
		pTemp1 = pTemp+1;
		pTemp = strstr( pTemp1, "," );
		if( pTemp == NULL )
			break;
		pTemp[0]=0;
		double dLon = atof( pTemp1 );
		//纬度
		pTemp1 = pTemp+1;
		pTemp = strstr( pTemp1, ";" );
		if( pTemp == NULL )
		{
			pTemp = strstr( pTemp1, "}" );
			if( pTemp == NULL )
			{
				break;
			}
		}
		pTemp[0]=0;
		double dLan = atof( pTemp1 );
		pTemp1 = pTemp+1;

		MapPoint* pNew = new MapPoint(); 
		pNew->x = dLon;
		pNew->y = dLan;
		AddMapPolygonPoint( nIndex, pNew );
	}
	SetMapPolygonName( nIndex,strName.c_str());
	//SetMapLineWidth( nIndex,lwidth);
	SetMapPolygonColor( nIndex,lcolor);
	return pTemp;
}
bool CBackLayer::ReadMapPoint()
{
	string strFileName = m_strFilePath;
	strFileName += "mappoint.txt";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	string strdata = Buffer;
	std::vector<std::string> v_strtext = STR_Split( strdata, "\r\n" );
	int isize =  v_strtext.size();
	for( int i=0;i< v_strtext.size();i++ )
	{
		std::vector<std::string> v_str = STR_Split( v_strtext[i], "," );
		if( v_str.size() == 5 )
		{
			//CreateMapText(i,atof(v_str[2].c_str()),atof( v_str[3].c_str() ),v_str[1].c_str(),atoi(v_str[4].c_str()),atoi(v_str[5].c_str()) );
			long sICOID = m_pMapPoiRes->CreateRes( v_str[4].c_str() );
			CreatMapPoint( i, atof(v_str[2].c_str()),atof( v_str[3].c_str() ), v_str[1].c_str(),"",sICOID );
		}
	}
	free( Buffer );
	return true;
}
bool CBackLayer::ReadMapText()
{
	string strFileName = m_strFilePath;
	strFileName += "maptext.txt";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	string strdata = Buffer;
	std::vector<std::string> v_strtext = STR_Split( strdata, "\r\n" );
	int isize =  v_strtext.size();
	for( int i=0;i< v_strtext.size();i++ )
	{
		std::vector<std::string> v_str = STR_Split( v_strtext[i], "," );
		if( v_str.size() == 6 )
		{
			CreateMapText(i,atof(v_str[2].c_str()),atof( v_str[3].c_str() ),v_str[1].c_str(),atoi(v_str[4].c_str()),atoi(v_str[5].c_str()) );
		}
	}
	free( Buffer );
	return true;
}
bool CBackLayer::ReadMap123()
{
	string strFileName = m_strFilePath;
	strFileName += "水文站.csv";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	long sICOID = m_pMapPoiRes->CreateRes( "1.png" );
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	string strdata = Buffer;
	std::vector<std::string> v_strtext = STR_Split( strdata, "\r\n" );
	int isize =  v_strtext.size();
	for( int i=0;i< v_strtext.size();i++ )
	{
		std::vector<std::string> v_str = STR_Split( v_strtext[i], "," );
		isize =  v_str.size();
		if( v_str.size() >= 29 )
		{
			
			CreatMapPoint( i, atof(v_str[22].c_str()), atof(v_str[23].c_str()), v_str[6].c_str(),"",sICOID );
			//CreateMapText(i,atof(v_str[2].c_str()),atof( v_str[3].c_str() ),v_str[1].c_str(),atoi(v_str[4].c_str()),atoi(v_str[5].c_str()) );
		}
	}
	free( Buffer );
	return true;
}
bool CBackLayer::LoadMap2000()
{
	return false;
	string strFileName = m_strFilePath;
	strFileName += "2000.txt";
	CVOSFile file;
	if(!file.Open( strFileName.c_str(), fomOnlyRead ))
	{
		if( file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
			file.Close();
		return false;
	}
	int iLen = file.GetLength();
	char* Buffer = (char* )malloc( iLen+1 );
	file.Read( Buffer, iLen );
	file.Close();
	string strdata = Buffer;
	std::vector<std::string> v_strtext = STR_Split( strdata, "\r\n" );
	int isize =  v_strtext.size();
	for( int i=0;i< v_strtext.size();i++ )
	{
		std::vector<std::string> v_str = STR_Split( v_strtext[i], "," );
		isize =  v_str.size();
		if( v_str.size() >= 29 )
		{
			CreatMapLine( i );
			MapPoint* pNew = new MapPoint(); 
			pNew->x = atof( v_str[22].c_str() );
			pNew->y = atof( v_str[22].c_str() );
			AddMapLinePoint( i, pNew );
			SetMapLineName( i,v_str[6] );
			SetMapLineWidth( i,atoi( v_str[6].c_str() ) );
			SetMapLineColor( i,atoi( v_str[6].c_str() ) );
		}
	}
	free( Buffer );
	return true;
}
//得到当前位置的信息ID,0为无数据，1为点信息，2为线信息
int CBackLayer::GetLocID( long& lID, VOSPoint point )
{
	CMapPoi* poi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->IsPointIn( point ) )
		{
			lID = poi->m_sPOIID;
			return 1;
		}
    }

	//画线
	CMapLine* pline = NULL;
	for (list<CMapLine*>::iterator itline = m_arrLine.begin(); itline != m_arrLine.end(); ++itline)
    {
        pline = *itline;
		if ( pline->IsPointIn( point ) )
		{
			lID = pline->m_lineid;
			return 2;
		}
    }
	return 0;
}