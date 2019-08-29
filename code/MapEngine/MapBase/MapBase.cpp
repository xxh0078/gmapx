#include "StdAfx.h"
#include "MapBase.h"
#include <stdio.h>
#include "../VOSBase/VOSBase.h"

fun_msg			g_fun_msg;

//en_MapType	g_enMapType;
string		g_strRootPath;

string g_strMapURL = _T("http://mt1.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G");
int	   g_iMapURLParmType = 123; //1表示x,2表示y,3表示z

//经纬度转墨卡托
MapPoint lonLat2Mercator(MapPoint lonLat,long temp )
{
	MapPoint mercator;
	double x = lonLat.x *temp/180;//20037508.34
	double y = log(tan((90+lonLat.y)*M_PI/360))/(M_PI/180);
	y = y *temp/180;
	mercator.x = x;
	mercator.y = y;
	return mercator ;
}
//墨卡托转经纬度
MapPoint Mercator2lonLat(MapPoint  mercator,long temp)
{
	MapPoint lonLat;
	double x = mercator.x/temp*180;
	double y = mercator.y/temp*180;
	y= 180/M_PI*(2*atan(exp(y*M_PI/180))-M_PI/2);
	lonLat.x = x;
	lonLat.y = y;
	return lonLat;
}
//伪经纬度转墨卡托
MapPoint lonLat2Mercator20(MapPoint lonLat )
{
	MapPoint mercator;
	double x = lonLat.x *_MAX_PIXEL_20_/180;//20037508.34
	double y = log(tan((90+lonLat.y)*M_PI/360))/(M_PI/180);
	y = y *_MAX_PIXEL_20_/180;
	mercator.x = x;
	mercator.y = y;
	return mercator ;
}
//伪墨卡托转经纬度
MapPoint Mercator2lonLat20( MapPoint  mercator )
{
	MapPoint lonLat;
	double x = mercator.x/_MAX_PIXEL_20_*180;
	double y = mercator.y/_MAX_PIXEL_20_*180;
	y= 180/M_PI*(2*atan(exp(y*M_PI/180))-M_PI/2);
	lonLat.x = x;
	lonLat.y = y;
	return lonLat;
}
//加密文件名
bool EncryptionFileName( int t, int x, int y, int z , vchar*strFileEncryName,int iLen )
{
	char strFileName[40]= {0};
	char strFileEncryNameTemp[40] = {0};
	sprintf( strFileName,"xxh_%d_%d_%d_%d",t,z,y,x);
	CMD5::GetMD5( (BYTE*)strFileName, strlen( strFileName ) , (BYTE*)strFileEncryName );
	//CVOSUtil::MultiByteToWdieChar( strFileEncryNameTemp,strFileEncryName, iLen );
//	char strFileName[40]= {0};
//	char strFileEncryNameTemp[40] = {0}
	//sprintf( strFileName,"xxh_%d_%d_%d_%d",t,z,y,x);
	//CMD5::GetMD5( (BYTE*)strFileName, strlen( strFileName ) , (BYTE*)strFileEncryNameTemp );
	return 1;
}
CMapBase::CMapBase(void)
{
}

CMapBase::~CMapBase(void)
{
}
//初始化静态资源
void CMapBase::Init( string strRootPath )
{
	//g_strMapURL[0] = _T("http://mt1.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G");
	
}
//设置地图类型SetMap根目录
void CMapBase::SetMapRootPath( string strRootPath )
{
	g_strRootPath = strRootPath;
}
	//得到程序根目录
void CMapBase::GetMapRootPath( string& strMapRootPath )
{
	char strRootPath[512]={0};
	//得到用户根目录
//	::SHGetSpecialFolderPath(NULL,strRootPath,CSIDL_APPDATA,FALSE);
	//得到程序当前目录//GetModuleHandle 
	GetModuleFileName( NULL,strRootPath,256); 
//::GetModuleFileName( NULL, strRootPath, 256 );
	char* pEnd = strrchr( strRootPath,_T('\\'));
	if( pEnd == NULL )
		return;
	pEnd[1]=0;
	strMapRootPath = strRootPath;
}
//得到地图类型根目录
void CMapBase::GetMapTypePath( int iMapType, string& strMapTypePath )
{
	strMapTypePath = g_strRootPath;
#ifndef _ENCRYPTION_FILE_NAME
	strMapTypePath += "瓦片数据\\";
	CreateDirectory( strMapTypePath.c_str() , NULL);
	switch( iMapType )
	{
	case GMAP_GOOGLE_MAP:
		strMapTypePath += _T("普通地图");
		break;
	case GMAP_GOOGLE_IMAGE:;
		strMapTypePath += _T("卫星地图");
		break;
	case GMAP_GOOGLE_MARK:
		{
			//影像标签
			strMapTypePath += _T("卫星标签");
			break;
		}
	case GMAP_GOOGLE_PHYSICAL:
		{
			//影像标签
			strMapTypePath += _T("地形图");
			break;
		}
	default:
		;
	}
	CreateDirectory( strMapTypePath.c_str() , NULL);
#else
	switch( iMapType )
	{
	case GMAP_GOOGLE_MAP:
		strMapTypePath += _T("gugemap");
		break;
	case GMAP_GOOGLE_IMAGE:;
		strMapTypePath += _T("gugeimg");
		break;
	case GMAP_GOOGLE_MARK:
		{
			//影像标签
			strMapTypePath += _T("gugemark");
			break;
		}
	case GMAP_GOOGLE_PHYSICAL:
		{
			//影像标签
			strMapTypePath += _T("gugephysical");
			break;
		}
	case GMAP_CHANGLIAN:
		strMapTypePath += _T("clmap");
		break;
	case GMAP_MAPABC:
		strMapTypePath += _T("mapabc");
		break;
	case GMAP_MAPBAR:
		strMapTypePath += _T("mapbar");
		break;
	case GMAP_MAP365:
		strMapTypePath += _T("map365");
		break;
	case GMAP_VM:
		strMapTypePath += _T("virtualearth");
		break;
	case GMAP_SUPERMAP:
		strMapTypePath += _T("SUPERMAP");
		break;
	case GMAP_MYMAP:
		strMapTypePath += _T("MYMAP");
		break;
	case GMAP_TIANDT:
		strMapTypePath += _T("TIANDT");
		break;
	default:
		;
	}
#endif
	
}
//设置地图类型
void CMapBase::SetMapType( en_MapType eMapType )
{
	string strMapTypePath;
	CMapBase::GetMapTypePath( eMapType, strMapTypePath );
	CreateDirectory( strMapTypePath.c_str(),NULL);
}
/*
//设置地图类型
string CMapBase::GetMapRootPath( char* strRootPath, int iLen )
{
	g_strRootPath = strRootPath;
	return g_strRootPath;
}*/
/*visur map
for (int i = levelOfDetail; i > 0; i--)
{
char digit = '0';
int mask = 1 << (i - 1);
if ((tileX & mask) != 0)
{
digit++;
}
if ((tileY & mask) != 0)
{
digit++;
digit++;
}
quadKey.Append(digit);
            }*/
//wsprintf(strURL,"http://mt%d.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile",
//影响图地址http://mt0.google.cn/vt/lyrs=s@76&gl=cn&x=103&y=50&z=7&s=Galileo
//http://mt2.google.cn/vt/lyrs=s@145&hl=zh-CN&gl=CN&src=app&x=6745&y=3101&z=13&s=
//路况图层http://mt0.google.cn//vt?hl=zh-CN&gl=cn&lyrs=h@142,traffic|seconds_into_week:-1&x=3372&y=1553&z=12&style=15
//	iServerNum,x,y,z);//
//百度地图http://q2.baidu.com/it/u=x=1551;y=314;z=13;v=004;type=web&fm=44
//获得地图URL路径
void CMapBase::GetMapUrlBk( int x, int y, int z, vchar* strUrl, int iLen )
{
	int iServerNum = rand()%4;//产生[0,m)的随机数
	sprintf(strUrl,_T("http://mt%d.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G"),
		iServerNum,x,y,z);//
}
void CMapBase::GetMapUrlMark( int x, int y, int z, vchar* strUrl, int iLen )
{
	int iServerNum = rand()%4;//产生[0,m)的随机数
	sprintf(strUrl,_T("http://mt%d.google.cn/vt/imgtp=png32&lyrs=h@184000000&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile"),
				iServerNum, x,y,z);
}

//获得地图文件路径
void CMapBase::GetMapDataEncryptionPath( int x, int y, int z, int iMapType,string& strRootPath )
{
	vchar temp[33]={0};
	strRootPath =  g_strRootPath;
	strRootPath += _T("\\level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strRootPath += temp;
	memset( temp,0,33);
	EncryptionFileName( iMapType,x,y,z,temp,33);
	CreateDirectory( strRootPath.c_str(),NULL);
	strRootPath += temp;
}
//获得地图文件路径
/*
void CMapBase::GetMapDataPath( int x, int y, int z, string& strRootPath, int iLen )
{
	vchar temp[33]={0};
	strRootPath =  g_strRootPath;
	//创建比例尺文件目录
	strRootPath += _T("\\level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strRootPath += temp;
	CreateDirectory( strRootPath.c_str(),NULL);
	//-----y坐标文件名
	memset( temp,0,33);
	sprintf( temp,_T("%d\\"),y );
	strRootPath += temp;
	CreateDirectory( strRootPath.c_str(),NULL);

	memset( temp,0,33);
	sprintf( temp,_T("%d.png"),x );
	strRootPath += temp;
}*/
//得到像素坐标
void CMapBase::GetMapPoint( int nLevel, MPoint lonLat20, MPoint& lonLat )
{
	lonLat.lX = lonLat20.lX >> (20-nLevel);
	lonLat.lY = lonLat20.lY >> (20-nLevel);
}
//得到20级像素坐标
void CMapBase::GetMapPoint20( int nLevel, MPoint lonLat, MPoint& lonLat20 )
{
	lonLat20.lX = lonLat.lX << (20-nLevel);
	lonLat20.lY = lonLat.lY << (20-nLevel);
}
//得到经纬度坐标
void CMapBase::MapPoint2LonLat( MPoint lonLat20, MapPoint& lonLat )
{
	MapPoint mercator;
	mercator.x = lonLat20.lX - _MAX_PIXEL_20_;
	mercator.y = _MAX_PIXEL_20_ - lonLat20.lY;
	lonLat = Mercator2lonLat20( mercator );
	// 	float itemp =(2<<(m_iLevel-1))*256;
	// 	int i1111 = itemp;
	// 	itemp = itemp/2;
	// 	if( itemp!= 0  )
	// 	{
	// 		mercator.x = m_gptMapCenter.lX + pt.x - m_rcWnd.Width()/2 - itemp;
	// 		mercator.y = itemp - ( m_gptMapCenter.lY + pt.y-m_rcWnd.Height()/2 ) ;
	// 		mpt = Mercator2lonLat( mercator, itemp );
// 	}
}
//得到像素坐标
void CMapBase::GetMapPoint( int nLevel, MapPoint lonLat, MPoint& lonLatout )
{
	MPoint lonLat20;
	CMapBase::LonLat2MapPoint20( lonLat, lonLat20 );
	CMapBase::GetMapPoint( nLevel, lonLat20, lonLatout );
}
//得到20级像素坐标
void CMapBase::LonLat2MapPoint20( MapPoint lonLat, MPoint& lonLat20 )
{
	MapPoint mercator = lonLat2Mercator20( lonLat );
	lonLat20.lX = mercator.x + _MAX_PIXEL_20_;
	lonLat20.lY = _MAX_PIXEL_20_ - mercator.y;
}
//偏移20级像素坐标
void CMapBase::OffsetMapPoint20( int nLevel, VOSPoint offest, VOSPoint& offest20 )
{
	int iTemp=0;
	//--------------------
	if ( offest.x >= 0 )
	{
		offest20.x = offest.x << (20-nLevel);
	}
	else
	{
		iTemp = abs( offest.x );
		offest20.x = (-1)*( iTemp << (20-nLevel) );
	}
	//-----------------------
	if ( offest.y >= 0 )
	{
		offest20.y = offest.y << (20-nLevel);
	}
	else
	{
		iTemp = abs( offest.y );
		offest20.y = (-1)*( iTemp << (20-nLevel) );
	}
}
//写日志
bool CMapBase::WriteLog(string strLog)
{
	/*
	CTime tm = CTime::GetCurrentTime()
	string strFile = g_strRootPath.c_str();
	strFile+="log";
	strFile += tm.Format("%Y%m%d");
	strFile += ".log";
	CVOSFile logfile;
	if( !logfile.Open(strFile.c_str(),fomReadWrite ))
	{
		if(!logfile.Open(strFile.c_str(),fomCreate | fomReadWrite ))
		{
			return false;
		}
	}
	logfile.SeekToEnd();
	logfile.Write(( char*)strLog.c_str(),strLog.length());
	logfile.Write("\r\n",2);
	logfile.Close();*/
	return true;
}
//设置地图URL路径
void CMapBase::SetMapUrl(string strMapURL )
{
	g_strMapURL = strMapURL;
}
double m_PI_180 = 0.017453292519943295769236907684886;
double m_PI = 3.14159265358979323;
double  CMapBase::GetLength(double x1, double y1, double x2, double y2)
{
	if (x1 < -180 || x2 < -180 || x1 > 180 || x2 > 180 || y1 < -90 || y2 < -90 || y1 > 90 || y2 > 90) {
			return 0;
		} else {
			x1=m_PI_180*x1;			
			x2=m_PI_180*x2;		
			y1=m_PI_180*y1;		
			y2=m_PI_180*y2;		
			//double dtemp=Math.sin(x1) * Math.sin(x2)+ Math.cos(x1) * Math.cos(x2) * Math.cos(y1 - y2);
			double dtemp=sin(y1) * sin(y2)+ cos(y1) * cos(y2) * cos(x1 - x2);
			if(dtemp>1.0){
				 return 0.0;
			}
			double dis = 6371137.0 * acos(dtemp);
			return dis;
		}
	return 1;
}
double  CMapBase::GetArea( double* pdX, double* pdY, int iSize )
{
	// 经纬度坐标下的球面多边形
		if( iSize < 3 )
		{
			return 0;
		}
		 
		double dArea = 0;
		
		double LowX=0.0;
		double LowY=0.0;
		double MiddleX=0.0;
		double MiddleY=0.0;            
		double HighX=0.0;
		double HighY=0.0;
		
		double AM = 0.0;        
		double BM = 0.0;    
		double CM = 0.0;            
		
		double AL = 0.0;        
		double BL = 0.0;    
		double CL = 0.0;        

        double AH = 0.0;        
        double BH = 0.0;    
        double CH = 0.0;            

        double CoefficientL = 0.0;
        double CoefficientH = 0.0;        
                    
        double ALtangent = 0.0;        
        double BLtangent = 0.0;    
        double CLtangent = 0.0;    

        double AHtangent = 0.0;        
        double BHtangent = 0.0;    
        double CHtangent = 0.0;
                                
        double ANormalLine = 0.0;        
        double BNormalLine = 0.0;    
        double CNormalLine = 0.0;
	                                            
		double OrientationValue = 0.0;

		double AngleCos = 0.0;

		double Sum1 = 0.0;
		double Sum2 = 0.0;
		double Count2 = 0;
		double Count1 = 0;

		double Sum = 0.0;
		double Radius = 6378137.0;// 6371137f;// 6378000;

		int i = 0;

		double* PointX = new double[iSize + 1];
		double* PointY = new double[iSize + 1];

		int j = 0;
		for (j = 0; j < iSize; j++) {
			//Point2D pnt = Points.get(j);
			PointX[j] = pdX[j] * m_PI_180;
			PointY[j] = pdY[j] * m_PI_180;
		}	

	    for(i=0;i<iSize;i++)
        {
            if(i==0)  // 三角函数部分应该可以优化，待续吧...
            {
                LowX = PointX[iSize-1];// * Math.PI / 180;
                LowY = PointY[iSize-1];// * Math.PI / 180;    
                MiddleX = PointX[0];// * Math.PI / 180;
                MiddleY = PointY[0];// * Math.PI / 180;
                HighX = PointX[1];// * Math.PI / 180;
                HighY = PointY[1];// * Math.PI / 180;
            }
	        else if(i==iSize-1)
	        {
	            LowX = PointX[iSize-2];// * Math.PI / 180;
	            LowY = PointY[iSize-2];// * Math.PI / 180;    
	            MiddleX = PointX[iSize-1];// * Math.PI / 180;
	            MiddleY = PointY[iSize-1];// * Math.PI / 180;            
	            HighX = PointX[0];// * Math.PI / 180;
	            HighY = PointY[0];// * Math.PI / 180;                        
	        }
	        else
	        {
	            LowX = PointX[i-1];// * Math.PI / 180;
	            LowY = PointY[i-1];// * Math.PI / 180;    
	            MiddleX = PointX[i];// * Math.PI / 180;
	            MiddleY = PointY[i];// * Math.PI / 180;            
	            HighX = PointX[i+1];// * Math.PI / 180;
	            HighY = PointY[i+1];// * Math.PI / 180;                            
	        }

            
	        AM = cos(MiddleY) * cos(MiddleX);
	        BM = cos(MiddleY) * sin(MiddleX);
	        CM = sin(MiddleY);
	        AL = cos(LowY) * cos(LowX);
	        BL = cos(LowY) * sin(LowX);
	        CL = sin(LowY);
	        AH = cos(HighY) * cos(HighX);
	        BH = cos(HighY) * sin(HighX);
	        CH = sin(HighY);        
                        
            
	        CoefficientL = (AM*AM + BM*BM + CM*CM)/(AM*AL + BM*BL + CM*CL);
	        CoefficientH = (AM*AM + BM*BM + CM*CM)/(AM*AH + BM*BH + CM*CH);
	        
	        ALtangent = CoefficientL * AL - AM;
	        BLtangent = CoefficientL * BL - BM;
	        CLtangent = CoefficientL * CL - CM;
	        AHtangent = CoefficientH * AH - AM;
	        BHtangent = CoefficientH * BH - BM;
	        CHtangent = CoefficientH * CH - CM;                
            
            
	        //AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent)/(Math.sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * Math.sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent));
	        
	        double dDiv = sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent);
	        if( dDiv < 0.00000000001 )
	        {
	        	continue;
	        }
	        AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent) / dDiv;

	        
	        AngleCos = acos(AngleCos);
	        
	        ANormalLine = BHtangent * CLtangent - CHtangent * BLtangent;
	        BNormalLine = 0 - (AHtangent * CLtangent - CHtangent * ALtangent); 
	        CNormalLine = AHtangent * BLtangent - BHtangent * ALtangent;
	        
	        if(AM!=0)
	        {
	            OrientationValue = ANormalLine/AM;
	        }
	        else if(BM!=0)
	        {
	            OrientationValue = BNormalLine/BM;
	        }
	        else
	        {
	            OrientationValue = CNormalLine/CM;
	        }   
	        if(OrientationValue>0)
	        {
	                Sum1 += AngleCos;
	                Count1 ++;
	        }
	        else
	        {
	                Sum2 += AngleCos;
	                Count2 ++;
	                //Sum +=2*Math.PI-AngleCos;
	        }
            
			if(Sum1>Sum2){
			    Sum = Sum1+(2*m_PI*Count2-Sum2);
			}
			else{
			    Sum = (2*m_PI*Count1-Sum1)+Sum2;
			}
		
			//平方米
			dArea = (Sum-(iSize-2)*m_PI)*Radius*Radius;
        }
        return dArea;
}
double CMapBase::AzimuthAngle(double x1,double y1,double x2,double y2)
{
	 double dx,dy,angle;
	 dx=x2-x1;
	 dy=y2-y1;
	 if( dy == 0 )
	 {
		  if( x2 == x1 )
			 return 0;
		 else if( x2 > x1 )
			 return 90;
		 else
			 return 270;
	 }
	 if( dx == 0 ) 
	 {
		 if( y2 < y1) 
			 return 180;
		 else 
			 return 0;
	 }
	 else if((x2>x1) && (y2>y1)) 
		 angle=atan(dx/dy);
	 else if((x2>x1) && (y2<y1)) 
		 angle=PI/2+atan(-dy/dx);
	 else if((x2<x1) && (y2<y1)) 
		 angle=PI+atan(dx/dy);
	 else if((x2<x1) && (y2>y1)) 
		 angle=3.0*PI/2.0+atan(dy/-dx);

	 return (angle*180/PI);
}
//获得地图文件路径
void CMapBase::GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType )
//void CMapDispLayer::GetMapDataEncryptionPath( int x, int y, int z,int iMapType, string& strMapFilePath )
{
	CMapBase::GetMapTypePath( iMapType, strMapFilePath );
	char temp[33]={0};
	//创建比例尺文件目录
	strMapFilePath += _T("\\level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);
#ifdef _ENCRYPTION_FILE_NAME
	
	memset( temp,0,33);
	EncryptionFileName( iMapType,x,y,z,temp,33);
	strMapFilePath += temp;
#else
	//-----y坐标文件名
	memset( temp,0,33);
	sprintf( temp,_T("%d\\"),y );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);

	memset( temp,0,33);
	sprintf( temp,_T("%d.png"),x );
	strMapFilePath += temp;
#endif
}
//获得地图URL路径
void CMapBase::GetMapUrl( int x, int y, int z,int iMapType, char* strUrl, int iLen )
{
	int iServerNum = rand()%4;//产生[0,m)的随机数
	switch( iMapType )
	{
	case GMAP_GOOGLE_MAP:
		{
			int iServerNum = rand()%4;//产生[0,m)的随机数
			//超图http://file.supermapcloud.com/FileService/image?map=quanguo&type=web&x=26&y=13&z=5
			sprintf(strUrl,_T("http://mt%d.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G"),
				iServerNum,x,y,z);//
			//谷歌地形图http://mt1.google.cn/vt/lyrs=t@129,r@184000000&hl=zh-CN&gl=cn&x=416&y=198&z=9&s=Galile
			//天地图 sprintf(strUrl,_T("http://tile0.tianditu.com/DataServer?T=AB0512_Anno&X=%d&Y=%d&L=%d"),
			//	iServerNum,x,y,z);//
			//http://q1.baidu.com/it/u=x=1;y=0;z=3;v=009;type=web&fm=44
		//	sprintf(strUrl,_T("http://q%d.baidu.com/it/u=x=%d;y=%d;z=%d;v=004;type=web&fm=44"),
		//		iServerNum,x,y,z);//
		}
		break;
	case GMAP_GOOGLE_PHYSICAL:
		{
			int iServerNum = rand()%4;//产生[0,m)的随机数
			//超图http://file.supermapcloud.com/FileService/image?map=quanguo&type=web&x=26&y=13&z=5
			sprintf(strUrl,_T("http://mt%d.google.cn/vt/lyrs=t@129,r@184000000&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile"),
				iServerNum,x,y,z);//
			//谷歌地形图http://mt1.google.cn/vt/lyrs=t@129,r@184000000&hl=zh-CN&gl=cn&x=416&y=198&z=9&s=Galile
			//天地图 sprintf(strUrl,_T("http://tile0.tianditu.com/DataServer?T=AB0512_Anno&X=%d&Y=%d&L=%d"),
			//	iServerNum,x,y,z);//
			//http://q1.baidu.com/it/u=x=1;y=0;z=3;v=009;type=web&fm=44
		//	sprintf(strUrl,_T("http://q%d.baidu.com/it/u=x=%d;y=%d;z=%d;v=004;type=web&fm=44"),
		//		iServerNum,x,y,z);//
		}
		break;
	case GMAP_GOOGLE_IMAGE:
		{
			int iServerNum = rand()%4;//产生[0,m)的随机数
			//http://mt1.google.cn/vt/lyrs=s@58&gl=cn&x=13381&y=7138&z=14&s=Gali
			//wsprintf(strUrl,_T("http://mt0.google.cn/vt/lyrs=s@76&gl=cn&x=103&y=50&z=7&s=Galileo"),
			//http://khm1.google.com/kh/v=58&x=13381&y=7138&z=14&s=Gali
			//http://mt2.google.cn/vt/lyrs=s@115&gl=cn&x=10&y=0&z=6&s=Galile
			///kh?n=404&v=5&t=tqtsq
			//http://khm%d.google.com/kh/v=58&x=%d&y=%d&z=%d&s=Gali
			///vt/lyrs=s@115&gl=cn&x=23&y=6&z=5&s=Gal
			//卫星图 
			///vt/imgtp=png32&lyrs=h@203000000&hl=zh-CN&gl=CN&src=app&x=12&y=7&z=4&s=Gal
			//sprintf(strUrl,_T("http://mt%d.google.cn/vt/lyrs=s@117&gl=cn&x=%d&y=%d&z=%d&s=Galile"),
			//	iServerNum, x,y,z);http://mt0.google.cn/vt/lyrs=s@123&hl=zh-CN&gl=CN&src=app&x=5&y=2&z=3&s=G
			////http://mt2.google.cn/vt/lyrs=s@145&hl=zh-CN&gl=CN&src=app&x=6745&y=3101&z=13&s=
			sprintf(strUrl,_T("http://mt%d.google.cn/vt/lyrs=s@145&hl=zh-CN&gl=CN&src=app&x=%d&y=%d&z=%d&s=G"),
				iServerNum, x,y,z);//s@123
			//http://www.google.cn/maps/vt?lyrs=s@171&gl=cn&x=205847&y=112234&z=18
			sprintf(strUrl,_T("http://www.google.cn/maps/vt?lyrs=s@171&gl=cn&x=%d&y=%d&z=%d"),x,y,z);//s@123
			//标签图/vt/lyrs=m@184000000&hl=zh-CN&gl=cn&x=862&y=409&z=10&s=Gal //
			//sprintf(strUrl,_T("http://mt%d.google.cn/vt/imgtp=png32&lyrs=h@184000000&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile"),
			//	iServerNum, x,y,z);
			sprintf(strUrl,_T("http://webst02.is.autonavi.com/appmaptile?style=6&x=%d&y=%d&z=%d"),x,y,z);//s@123
			
		}
		break;
	case GMAP_GOOGLE_MARK:
		{
			//影像标签
			int iServerNum = rand()%4;//产生[0,m)的随机数
			//http://webst02.is.autonavi.com/appmaptile?x=205873&y=112204&z=18&lang=zh_cn&size=1&scale=1&style=8
			sprintf(strUrl,_T("http://mt%d.google.cn/vt/imgtp=png32&lyrs=h@184000000&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile"),
				iServerNum, x,y,z);
			//高德卫星
			sprintf(strUrl,_T("http://webst02.is.autonavi.com/appmaptile?x=%d3&y=%d&z=%d&lang=zh_cn&size=1&scale=1&style=8"),
				 x,y,z);
		}
		break;
	case GMAP_CHANGLIAN:
		sprintf(strUrl,_T("http://221.238.196.132:8081/gmapdata/level%d/%d/%d.png"),
			z,y,x);
		break;
	case GMAP_MAPABC:
		{
			int iServerNum = rand()%3+1;//产生[0,m)的随机数
			//http://webrd04.is.autonavi.com/appmaptile?x=6743&y=3106&z=13&lang=zh_cn&size=1&scale=1&style=7
			wsprintf(strUrl,"http://webrd0%d.is.autonavi.com/appmaptile?x=%d&y=%d&z=%d&lang=zh_cn&size=1&scale=1&style=7",
					iServerNum,x,y,z);
			break;
		}
	case GMAP_MAPBAR:
		//http://img1.mapbar.com//maplite/mapbank/mapbar/9/46_19/28_49.png
		wsprintf(strUrl,"http://img1.mapbar.com//maplite/mapbank/mapbar/9/46_19/28_49.png",
				x,y,z);
		break;
	case GMAP_MAP365:
		//wsprintf(strUrl,"http://mt%d.google.cn/vt/lyrs=s@76&gl=cn&x=%d&y=%d&z=%d&s=Galileo",
		//		x,y,z);
		break;
	case GMAP_BAIDU_MAP:
		{
			int iServerNum = rand()%4;//产生[0,m)的随机数
			int itemp = 2>>(z-1);
			z = z-1;
			x = x - itemp;
			y = itemp - y;
			sprintf(strUrl,_T("http://q%d.baidu.com/it/u=x=%d;y=%d;z=%d;v=004;type=web&fm=44"),
				iServerNum,x,y,z);//
			
			//	http://q1.baidu.com/it/u=x=1;y=0;z=3;v=009;type=web&fm=44
			//	sprintf(strUrl,_T("http://q%d.baidu.com/it/u=x=%d;y=%d;z=%d;v=004;type=web&fm=44"),
			//		iServerNum,x,y,z);//
		}
		break;
	case GMAP_MYMAP:
		{
			string strMapURL = g_strMapURL;
			char cTemp[20]={0};
			sprintf( cTemp,"%d",x);
			string flag = "%x";  
			string::size_type position = 0;
			while(1)  
			{
				position = strMapURL.find( flag );
				if( position != strMapURL.npos )
				{
					strMapURL.replace( position,2,cTemp,strlen(cTemp));
				}
				else
					break;
			}
			sprintf( cTemp,"%d",y);
			flag = "%y";
			while(1)  
			{
				position = strMapURL.find( flag );
				if( position != strMapURL.npos )
				{
					strMapURL.replace( position,2,cTemp,strlen(cTemp));
				}
				else
					break;
			}
			sprintf( cTemp,"%d",z);
			flag = "%z";  
			position = 0;
			while(1)  
			{
				position = strMapURL.find( flag );
				if( position != strMapURL.npos )
				{
					strMapURL.replace( position,2,cTemp,strlen(cTemp));
				}
				else
					break;
			}
			memset(strUrl,0,iLen);
			strcpy(strUrl,strMapURL.c_str());

		}
		 /*
		//jiage114地址
		switch( g_iMapURLParmType )
		{
		case 123:
			wsprintf(strUrl,g_strMapURL.c_str(),x,y,z);
			break;
		case 132:
			wsprintf(strUrl,g_strMapURL.c_str(),x,z,y);
			break;
		case 213:
			wsprintf(strUrl,g_strMapURL.c_str(),y,x,z);
			break;
		case 231:
			wsprintf(strUrl,g_strMapURL.c_str(),y,z,x);
			break;
		case 312:
			wsprintf(strUrl,g_strMapURL.c_str(),z,x,y);
			break;
		case 321:
			wsprintf(strUrl,g_strMapURL.c_str(),z,y,x);
			break;
		default:
			wsprintf(strUrl,g_strMapURL.c_str(),x,y,z);
			break;
		}*/
			/*
		if( z < 11 )
		{
			wsprintf(strUrl,_T("http://www.gmapx.net:8081/gmapdata/level%d/%d/%d.png"),
				z,y,x);//
		}
		else
		{
			wsprintf(strUrl,_T("http://www.gmapx.net:8088/gmap/gmap?key=111&type=1&x=%d&y=%d&z=%d"),
				x,y,z);//
		}*/
		break;
	case GMAP_VM:
		{
			string str1=_T("http://r1.ortho.tiles.virtualearth.net/tiles/r");
			char ctemp[2]={0};
// 			for (int i = z; i >= 0; i--) 
// 			{
// 				int num2 = ((int)1) << i;
// 				int num = ((x & num2) >> i) | (((y & num2) != 0) ? 2 : 0);
// 				sprintf(ctemp,"%d",num);
// 				str1 += ctemp;
// 			}
			for (int i = z; i > 0; i--)
			{
				char digit = '0';
				int mask = 1 << (i - 1);
				if ((x & mask) != 0)
				{
					digit++;
				}
				if ((y & mask) != 0)
				{
					digit++;
					digit++;
				}
				//sprintf(ctemp,"%d",num);
				str1 += digit;
            }
			str1 += ".png?g=50";
			strcpy( strUrl, str1.c_str());
		}
		break;
	case GMAP_SUPERMAP:
		{
			int iServerNum = rand()%4;//产生[0,m)的随机数
			//超图http://file.supermapcloud.com/FileService/image?map=quanguo&type=web&x=26&y=13&z=5
			//http://t0.supermapcloud.com/FileService/image?map=quanguo&type=web&x=3371&y=1552&z=12
		//	sprintf(strUrl,_T("http://file.supermapcloud.com/FileService/image?map=quanguo&type=web&x=%d&y=%d&z=%d"),
		//		x,y,z);//
			sprintf(strUrl,_T("http://t0.supermapcloud.com/FileService/image?map=quanguo&type=web&x=%d&y=%d&z=%d"),
				x,y,z);//
			//http://q1.baidu.com/it/u=x=1;y=0;z=3;v=009;type=web&fm=44
			//	sprintf(strUrl,_T("http://q%d.baidu.com/it/u=x=%d;y=%d;z=%d;v=004;type=web&fm=44"),
			//		iServerNum,x,y,z);//
		}
		break;
	case GMAP_TIANDT:
		//天地图卫星URL
		sprintf(strUrl,_T("http://tile0.tianditu.com/DataServer?T=A0512_EMap&X=%d&Y=%d&L=%d"),
				x,y,z);//
		//天地图矢量
		//http://tile0.tianditu.com/DataServer?T=A0512_EMap
		//影响注记
		//http://tile0.tianditu.com/DataServer?T=A0610_ImgAnno

		//http://tile6.tianditu.com/tdt/DataServer?T=t_img_271224&X=1686&Y=285&L=11&INDATE=9999-01-01%2000%3A00%3A00
		//参考网址http://user.qzone.qq.com/214010522/infocenter#!app=2&via=QZ.HashRefresh&pos=catalog_private
	default:
		;
	}
}
//加密字符串
void CMapBase::EncryptionString(char* str)
{
	//CVOSUtil::EncryptionString( str,"xiexianghui");
}
//计算网格编号范围
bool CMapBase::GetMapBlockBound( MBound& MapBound20,int nLevel, int& nMinX, int& nMaxX,int& nMinY, int& nMaxY )
{
	if( nLevel < 0 || nLevel > 20 )
		return false;
	nMinX = 0;
	nMaxX = 2<<(nLevel-1);
	nMinY = 0;
	nMaxY = 2<<(nLevel-1);
	if( nLevel > 0 )
	{
		MPoint   mptLT,mptBR;
		CMapBase::GetMapPoint( nLevel, MapBound20.TopLeft(), mptLT );
		CMapBase::GetMapPoint( nLevel, MapBound20.BottomRight(), mptBR );
		nMinX = max( mptLT.lX/256-1,0);			
		nMaxX = min( mptBR.lX/256+1,2<<(nLevel-1));
		nMinY = max( mptLT.lY/256-1,0);			
		nMaxY = min( mptBR.lY/256+1, 2<<(nLevel-1));
	}
	else
	{
		if( nLevel == 0 )
		{
			nMaxX = 0;
			nMaxY = 0;
		}
	}
	return true;
}

//计算点是否在多变型内部
#define MAXSIDENUM 64
MapPoint	polygon[MAXSIDENUM];
const   double   INFINITY     =   1e10;   
const   double   ESP		  =   1e-5;   
const   int   MAX_N           =   1000;
//double	max(double x, double y)
double max1( double x,double y)
{
	return (x > y ? x : y);
}
double min1(double x, double y)
{
	return (x < y ? x : y);
} 
  
//   计算叉乘     |P0P1|   ×   |P0P2|   
double Multiply(MapPoint   p1,   MapPoint   p2,   MapPoint   p0)   
{   
      return   ((p1.x - p0.x) *(p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));   
}   

//   判断线段是否包含点point
bool IsOnline(MapPoint point,MapLineSegment line)
{
	return((fabs(Multiply(line.pt1,line.pt2,point)) < ESP) && ((point.x-line.pt1.x)*(point.x-line.pt2.x)<=0) && ((point.y-line.pt1.y)*(point.y-line.pt2.y)<=0));
}   
    
  //   判断线段相交
bool Intersect(MapLineSegment   L1,   MapLineSegment   L2)
{
	return(   (max(L1.pt1.x,   L1.pt2.x)   >=   min(L2.pt1.x,   L2.pt2.x))   &&   
	  (max(L2.pt1.x,   L2.pt2.x)   >=   min(L1.pt1.x,   L1.pt2.x))   &&   
	  (max(L1.pt1.y,   L1.pt2.y)   >=   min(L2.pt1.y,   L2.pt2.y))   &&   
	  (max(L2.pt1.y,   L2.pt2.y)   >=   min(L1.pt1.y,   L1.pt2.y))   &&   
	  (Multiply(L2.pt1,   L1.pt2,   L1.pt1)   *   Multiply(L1.pt2,   L2.pt2,   L1.pt1)   >=   0)   &&   
	  (Multiply(L1.pt1,   L2.pt2,   L2.pt1)   *   Multiply(L2.pt2,   L1.pt2,   L2.pt1)   >=   0)   
	);
} 
double  CMapBase::GetArea(  vector<MapPoint*>* arr )
{
//	double* pdX, double* pdY;
	int iSize = arr->size();
//	double* pdX = new double(iSize);
//	double* pdX = new double(iSize);
//	double dArea = CMapBase::GetArea( pdX, pdY, iSize );

	// 经纬度坐标下的球面多边形
	if( iSize < 3 )
	{
		return 0;
	}
	MapPoint* pPoint = NULL;
	double dArea = 0;
	
	double LowX=0.0;
	double LowY=0.0;
	double MiddleX=0.0;
	double MiddleY=0.0;            
	double HighX=0.0;
	double HighY=0.0;
	
	double AM = 0.0;        
	double BM = 0.0;    
	double CM = 0.0;            
	
	double AL = 0.0;        
	double BL = 0.0;    
	double CL = 0.0;        

    double AH = 0.0;        
    double BH = 0.0;    
    double CH = 0.0;            

    double CoefficientL = 0.0;
    double CoefficientH = 0.0;        
                
    double ALtangent = 0.0;        
    double BLtangent = 0.0;    
    double CLtangent = 0.0;    

    double AHtangent = 0.0;        
    double BHtangent = 0.0;    
    double CHtangent = 0.0;
                            
    double ANormalLine = 0.0;        
    double BNormalLine = 0.0;    
    double CNormalLine = 0.0;
	                                        
	double OrientationValue = 0.0;

	double AngleCos = 0.0;

	double Sum1 = 0.0;
	double Sum2 = 0.0;
	double Count2 = 0;
	double Count1 = 0;

	double Sum = 0.0;
	double Radius = 6378137.0;// 6371137f;// 6378000;

	int i = 0;

	double* PointX = new double[iSize + 1];
	double* PointY = new double[iSize + 1];
		
	int j = 0;
	for (j = 0; j < iSize; j++) {
		//Point2D pnt = Points.get(j);
		pPoint = arr->at(j);
		PointX[j] = pPoint->x * m_PI_180;
		PointY[j] = pPoint->y * m_PI_180;
	}	

	for(i=0;i<iSize;i++)
    {
        if(i==0)  // 三角函数部分应该可以优化，待续吧...
        {
            LowX = PointX[iSize-1];// * Math.PI / 180;
            LowY = PointY[iSize-1];// * Math.PI / 180;    
            MiddleX = PointX[0];// * Math.PI / 180;
            MiddleY = PointY[0];// * Math.PI / 180;
            HighX = PointX[1];// * Math.PI / 180;
            HighY = PointY[1];// * Math.PI / 180;
        }
	    else if(i==iSize-1)
	    {
	        LowX = PointX[iSize-2];// * Math.PI / 180;
	        LowY = PointY[iSize-2];// * Math.PI / 180;    
	        MiddleX = PointX[iSize-1];// * Math.PI / 180;
	        MiddleY = PointY[iSize-1];// * Math.PI / 180;            
	        HighX = PointX[0];// * Math.PI / 180;
	        HighY = PointY[0];// * Math.PI / 180;                        
	    }
	    else
	    {
	        LowX = PointX[i-1];// * Math.PI / 180;
	        LowY = PointY[i-1];// * Math.PI / 180;    
	        MiddleX = PointX[i];// * Math.PI / 180;
	        MiddleY = PointY[i];// * Math.PI / 180;            
	        HighX = PointX[i+1];// * Math.PI / 180;
	        HighY = PointY[i+1];// * Math.PI / 180;                            
	    }

        
	    AM = cos(MiddleY) * cos(MiddleX);
	    BM = cos(MiddleY) * sin(MiddleX);
	    CM = sin(MiddleY);
	    AL = cos(LowY) * cos(LowX);
	    BL = cos(LowY) * sin(LowX);
	    CL = sin(LowY);
	    AH = cos(HighY) * cos(HighX);
	    BH = cos(HighY) * sin(HighX);
	    CH = sin(HighY);        
                    
        
	    CoefficientL = (AM*AM + BM*BM + CM*CM)/(AM*AL + BM*BL + CM*CL);
	    CoefficientH = (AM*AM + BM*BM + CM*CM)/(AM*AH + BM*BH + CM*CH);
	    
	    ALtangent = CoefficientL * AL - AM;
	    BLtangent = CoefficientL * BL - BM;
	    CLtangent = CoefficientL * CL - CM;
	    AHtangent = CoefficientH * AH - AM;
	    BHtangent = CoefficientH * BH - BM;
	    CHtangent = CoefficientH * CH - CM;                
        
        
	    //AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent)/(Math.sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * Math.sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent));
	    
	    double dDiv = sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent);
	    if( dDiv < 0.00000000001 )
	    {
	        continue;
	    }
	    AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent) / dDiv;

	    
	    AngleCos = acos(AngleCos);
	    
	    ANormalLine = BHtangent * CLtangent - CHtangent * BLtangent;
	    BNormalLine = 0 - (AHtangent * CLtangent - CHtangent * ALtangent); 
	    CNormalLine = AHtangent * BLtangent - BHtangent * ALtangent;
	    
	    if(AM!=0)
	    {
	        OrientationValue = ANormalLine/AM;
	    }
	    else if(BM!=0)
	    {
	        OrientationValue = BNormalLine/BM;
	    }
	    else
	    {
	        OrientationValue = CNormalLine/CM;
	    }   
	    if(OrientationValue>0)
	    {
	            Sum1 += AngleCos;
	            Count1 ++;
	    }
	    else
	    {
	            Sum2 += AngleCos;
	            Count2 ++;
	            //Sum +=2*Math.PI-AngleCos;
	    }
        
		if(Sum1>Sum2){
			Sum = Sum1+(2*m_PI*Count2-Sum2);
		}
		else{
			Sum = (2*m_PI*Count1-Sum1)+Sum2;
		}
	
		//平方米
		dArea = (Sum-(iSize-2)*m_PI)*Radius*Radius;
    }
    return dArea;
}
//计算点是否在多变型内部
bool CMapBase::InPolygon( vector<MapPoint*>* arr, MapPoint point )
{
	int n = arr->size();
	MapPoint* pPoint = NULL;
	if   (n   ==   1)   {   
		pPoint = arr->at(0);
		return   (   (fabs(pPoint->x   -   point.x)   <   ESP)   &&   (fabs(pPoint->y   -   point.y)   <   ESP)   );   
	}   else   if   (n   ==   2)   {   
		MapLineSegment   side;   
		pPoint = arr->at(0);
		side.pt1   =   *pPoint;//polygon[0];   
		pPoint = arr->at(1);
		side.pt2 = *pPoint;//polygon[1];   
		return   IsOnline(point,   side);   
	}   

	int   count   =   0;   
	MapLineSegment   line;   
	line.pt1         =   point;   
	line.pt2.y     =   point.y;   
	line.pt2.x     =   -   INFINITY;   
	for(   int   i   =   0;   i   <   n;   i++   )   {   
		  //   得到多边形的一条边   
		  MapLineSegment   side;
		  pPoint = arr->at(i);
		  side.pt1   =    *pPoint;   
		  pPoint = arr->at((i   +   1)   %   n);
		  side.pt2   =    *pPoint;//(arr[(i   +   1)   %   n]);   

		  if(   IsOnline(point,   side)   )   {   
				  return   true;   
		  }   

		  //   如果side平行x轴则不作考虑   
		  if(   fabs(side.pt1.y   -   side.pt2.y)   <   ESP   )   {   
				  continue;   
		  }   

		  if(   IsOnline(side.pt1,   line)   )   {   
				  if(   side.pt1.y   >   side.pt2.y   )   count++;   
		  }   else   if(   IsOnline(side.pt2,   line)   )   {   
				  if(   side.pt2.y   >   side.pt1.y   )   count++;   
		  }   else   if(   Intersect(line,   side)   )   {   
				  count++;   
		  }   
	}   

	return   (   count   %   2   ==   1   );   
}
bool CMapBase::InPolygon( MapPoint mpt, MapPoint* polygon, int nCount )
{
	int nCross = 0;
	for( int i=0;i<nCount;i++)
	{
		MapPoint p1 = polygon[i];
		MapPoint p2 = polygon[(i+1)%nCount];
		//求解y=p.y与p1p2交点
		if( p1.y == p2.y )
			continue;
		//交点在延长线上
		if( mpt.y < MIN(p1.y,p2.y ) )
			continue;
		if( mpt.y >= MAX(p1.y,p2.y ) )
			continue;
		//求交点坐标
		double x = (double)(mpt.y - p1.y)*(double)(p2.x-p1.x)/(double)(p2.y-p1.y)+p1.x;
		//只统计单边交点
		if( x > mpt.x )
			nCross++;
	}
	return (nCross%2==1);
	/*
	if   (n   ==   1)   {   
		return   (   (fabs(polygon[0].x   -   point.x)   <   ESP)   &&   (fabs(polygon[0].y   -   point.y)   <   ESP)   );   
	}   else   if   (n   ==   2)   {   
		MapLineSegment   side;   
		side.pt1   =   polygon[0];   
		side.pt2   =   polygon[1];   
		return   IsOnline(point,   side);   
	}   

	int   count   =   0;   
	MapLineSegment   line;   
	line.pt1         =   point;   
	line.pt2.y     =   point.y;   
	line.pt2.x     =   -   INFINITY;   
	for(   int   i   =   0;   i   <   n;   i++   )   {   
		  //   得到多边形的一条边   
		  MapLineSegment   side;   
		  side.pt1   =   polygon[i];   
		  side.pt2   =   polygon[(i   +   1)   %   n];   

		  if(   IsOnline(point,   side)   )   {   
				  return   true;   
		  }   

		  //   如果side平行x轴则不作考虑   
		  if(   fabs(side.pt1.y   -   side.pt2.y)   <   ESP   )   {   
				  continue;   
		  }   

		  if(   IsOnline(side.pt1,   line)   )   {   
				  if(   side.pt1.y   >   side.pt2.y   )   count++;   
		  }   else   if(   IsOnline(side.pt2,   line)   )   {   
				  if(   side.pt2.y   >   side.pt1.y   )   count++;   
		  }   else   if(   Intersect(line,   side)   )   {   
				  count++;   
		  }   
	}   

	return   (   count   %   2   ==   1   );  */ 
}

double  CMapBase::GetArea(  vector<MapPoint*>* arr, MapPoint* pMpt  )
{
//	double* pdX, double* pdY;
	int iSize = arr->size()+1;
//	double* pdX = new double(iSize);
//	double* pdX = new double(iSize);
//	double dArea = CMapBase::GetArea( pdX, pdY, iSize );

	// 经纬度坐标下的球面多边形
	if( iSize < 3 )
	{
		return 0;
	}
	MapPoint* pPoint = NULL;
	double dArea = 0;
	
	double LowX=0.0;
	double LowY=0.0;
	double MiddleX=0.0;
	double MiddleY=0.0;            
	double HighX=0.0;
	double HighY=0.0;
	
	double AM = 0.0;        
	double BM = 0.0;    
	double CM = 0.0;            
	
	double AL = 0.0;        
	double BL = 0.0;    
	double CL = 0.0;        

    double AH = 0.0;        
    double BH = 0.0;    
    double CH = 0.0;            

    double CoefficientL = 0.0;
    double CoefficientH = 0.0;        
                
    double ALtangent = 0.0;        
    double BLtangent = 0.0;    
    double CLtangent = 0.0;    

    double AHtangent = 0.0;        
    double BHtangent = 0.0;    
    double CHtangent = 0.0;
                            
    double ANormalLine = 0.0;        
    double BNormalLine = 0.0;    
    double CNormalLine = 0.0;
	                                        
	double OrientationValue = 0.0;

	double AngleCos = 0.0;

	double Sum1 = 0.0;
	double Sum2 = 0.0;
	double Count2 = 0;
	double Count1 = 0;

	double Sum = 0.0;
	double Radius = 6378137.0;// 6371137f;// 6378000;

	int i = 0;

	double* PointX = new double[iSize + 1];
	double* PointY = new double[iSize + 1];
		
	int j = 0;
	for (j = 0; j < iSize-1; j++) {
		//Point2D pnt = Points.get(j);
		pPoint = arr->at(j);
		PointX[j] = pPoint->x * m_PI_180;
		PointY[j] = pPoint->y * m_PI_180;
	}	
	PointX[iSize-1] = pMpt->x*m_PI_180;
	PointY[iSize-1] = pMpt->y*m_PI_180;
	for(i=0;i<iSize;i++)
    {
        if(i==0)  // 三角函数部分应该可以优化，待续吧...
        {
            LowX = PointX[iSize-1];// * Math.PI / 180;
            LowY = PointY[iSize-1];// * Math.PI / 180;    
            MiddleX = PointX[0];// * Math.PI / 180;
            MiddleY = PointY[0];// * Math.PI / 180;
            HighX = PointX[1];// * Math.PI / 180;
            HighY = PointY[1];// * Math.PI / 180;
        }
	    else if(i==iSize-1)
	    {
	        LowX = PointX[iSize-2];// * Math.PI / 180;
	        LowY = PointY[iSize-2];// * Math.PI / 180;    
	        MiddleX = PointX[iSize-1];// * Math.PI / 180;
	        MiddleY = PointY[iSize-1];// * Math.PI / 180;            
	        HighX = PointX[0];// * Math.PI / 180;
	        HighY = PointY[0];// * Math.PI / 180;                        
	    }
	    else
	    {
	        LowX = PointX[i-1];// * Math.PI / 180;
	        LowY = PointY[i-1];// * Math.PI / 180;    
	        MiddleX = PointX[i];// * Math.PI / 180;
	        MiddleY = PointY[i];// * Math.PI / 180;            
	        HighX = PointX[i+1];// * Math.PI / 180;
	        HighY = PointY[i+1];// * Math.PI / 180;                            
	    }

        
	    AM = cos(MiddleY) * cos(MiddleX);
	    BM = cos(MiddleY) * sin(MiddleX);
	    CM = sin(MiddleY);
	    AL = cos(LowY) * cos(LowX);
	    BL = cos(LowY) * sin(LowX);
	    CL = sin(LowY);
	    AH = cos(HighY) * cos(HighX);
	    BH = cos(HighY) * sin(HighX);
	    CH = sin(HighY);        
                    
        
	    CoefficientL = (AM*AM + BM*BM + CM*CM)/(AM*AL + BM*BL + CM*CL);
	    CoefficientH = (AM*AM + BM*BM + CM*CM)/(AM*AH + BM*BH + CM*CH);
	    
	    ALtangent = CoefficientL * AL - AM;
	    BLtangent = CoefficientL * BL - BM;
	    CLtangent = CoefficientL * CL - CM;
	    AHtangent = CoefficientH * AH - AM;
	    BHtangent = CoefficientH * BH - BM;
	    CHtangent = CoefficientH * CH - CM;                
        
        
	    //AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent)/(Math.sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * Math.sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent));
	    
	    double dDiv = sqrt(AHtangent * AHtangent + BHtangent * BHtangent +CHtangent * CHtangent) * sqrt(ALtangent * ALtangent + BLtangent * BLtangent +CLtangent * CLtangent);
	    if( dDiv < 0.00000000001 )
	    {
	        continue;
	    }
	    AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent) / dDiv;

	    
	    AngleCos = acos(AngleCos);
	    
	    ANormalLine = BHtangent * CLtangent - CHtangent * BLtangent;
	    BNormalLine = 0 - (AHtangent * CLtangent - CHtangent * ALtangent); 
	    CNormalLine = AHtangent * BLtangent - BHtangent * ALtangent;
	    
	    if(AM!=0)
	    {
	        OrientationValue = ANormalLine/AM;
	    }
	    else if(BM!=0)
	    {
	        OrientationValue = BNormalLine/BM;
	    }
	    else
	    {
	        OrientationValue = CNormalLine/CM;
	    }   
	    if(OrientationValue>0)
	    {
	            Sum1 += AngleCos;
	            Count1 ++;
	    }
	    else
	    {
	            Sum2 += AngleCos;
	            Count2 ++;
	            //Sum +=2*Math.PI-AngleCos;
	    }
        
		if(Sum1>Sum2){
			Sum = Sum1+(2*m_PI*Count2-Sum2);
		}
		else{
			Sum = (2*m_PI*Count1-Sum1)+Sum2;
		}
	
		//平方米
		dArea = (Sum-(iSize-2)*m_PI)*Radius*Radius;
    }
    return dArea;
}