// MapDown.cpp: implementation of the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapdown.h"
#include "MapDown.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapDown::CMapDown()
{
	m_ix = 0;
	m_iy = 0;
	m_iz = 4;
}

CMapDown::~CMapDown()
{
	m_ix = 0;
	m_iy = 0;
	m_iz = 4;
}
//初始化临时文件
void CMapDown::Init( CWnd* pWnd, float x1,float x2, float y1,float y2,long level,string strIndex)
{
	//初始化根目录
	memset( m_strRootPath, 0, 255 );
	GetModuleFileName(AfxGetInstanceHandle(),m_strRootPath,256); 
	char* pEnd = strrchr( m_strRootPath,_T('\\'));
	if( pEnd == NULL )
		return;
	pEnd[1]=0;
	strcat( m_strRootPath, "\\gugemap\\");
	CreateDirectory( m_strRootPath, NULL);
	//创建比例尺文件夹
	CreateLevelDir(level);
	//
	m_pWnd = pWnd;
	m_strIndex = strIndex.c_str();
	//初始化
	m_mapBound.left = x1;
	m_mapBound.right = x2;
	m_mapBound.top = y1;
	m_mapBound.bottom = y2;
	m_iz = level;
	GetLevelBound(  m_iz );

	this->GetDownPosition( this->m_ix,this->m_iy,this->m_iz );
	//创建比例尺文件夹
	CreateLevelDir(m_iz);
	//
//	

//	m_hDownLoadMutex = CreateMutex( NULL,false,NULL );
	
	Start();
}
//创建比例尺路径
void CMapDown::CreateLevelDir(int iLevel )
{
	//比例尺路径
	char strLevelPath[256] ={0}; 
	char strTemp[20]={0};
	sprintf(strTemp,"level%d\\",iLevel);
	strcpy( strLevelPath, m_strRootPath );
	strcat( strLevelPath, strTemp );
	CreateDirectory(strLevelPath, NULL);
}
void CMapDown::Start( )
{
	m_bExitProc = false;
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapDown::DownLoadProc,this,0,&dwThreadID );
	CloseHandle( h );
}
void CMapDown::Stop( )
{
	m_bExitProc = true;
}
void CMapDown::Draw( HDC hdc, int left,int top )
{
	m_strView.Format("z=%d,y=%d,x=%d",m_iz,m_iy,m_ix);
//	::SetTextColor( hdc, RGB(0,0, 255));
//	SetBkMode(hdc,TRANSPARENT);
	::TextOut(hdc,left,top,m_strView.GetBuffer(0),m_strView.GetLength());
}
//获得地图文件路径
void GetMapDatapath( int x, int y, int z, string& strRootPath, int iLen )
{
	vchar temp[33]={0};
	strRootPath += _T("level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strRootPath += temp;
	memset( temp,0,33);
	EncryptionFileName( GMAP_GOOGLE_MAP,x,y,z,temp,33);
	CreateDirectory( strRootPath.c_str(),NULL);
	strRootPath += temp;
}
//获取谷歌常规地图
bool CMapDown::GetMap(  int x, int y, int z  )
{
	//	vchar strSentence[256], strFileDirect[256];
	vchar strURL[256];
	int iServerNum = rand()%4;//产生[0,m)的随机数  
//	sprintf(strFileDirect,_T("gmapdata/level%d",z);

	string strWriteName = this->m_strRootPath;
	GetMapDatapath( x,y,z,strWriteName,256);
	
	//GetEncryptionFileName( 1,x,y,z,strWriteName );
//	GetEncryptionFileName( x,y,z,strWriteName);
//	sprintf(strWriteName,"gmapdata/level%d/%d_%d.dat1",z,y,x);
	//sprintf(strURL,"http://mt%d.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=Galile",
	//影响图地址http://mt0.google.cn/vt/lyrs=s@76&gl=cn&x=103&y=50&z=7&s=Galileo
	//路况图层http://mt0.google.cn//vt?hl=zh-CN&gl=cn&lyrs=h@142,traffic|seconds_into_week:-1&x=3372&y=1553&z=12&style=15
	//	iServerNum,x,y,z);//
	//http://www.jiage114.net/gmapdata\level3/1_1.png
	//sprintf(strURL,"http://mt%d.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%d&y=%d&z=%d&s=G",
	//	iServerNum,x,y,z);//
//sprintf(strURL,"http://221.238.196.132:8081/gmapdata/level%d/%d/%d.png",
//		z,y,x);
	/*
	//jiage114地址
	if( z < 11 )
	{
		sprintf(strURL,"http://www.jiage114.net/gmapdata/level%d/%d/%d.png",
		z,y,x);//
	}
	else
	{
		sprintf(strURL,"http://www.jiage114.net:8088/gmap/gmap?key=111&type=1&x=%d&y=%d&z=%d",
		x,y,z);//
	}*/
	//sprintf(strURL,"http://www.jiage114.net:8088/gmap/gmap?key=111&type=1&x=%d&y=%d&z=%d",
	//	x,y,z);
//	sprintf(strURL,"http://mt%d.google.cn/vt/lyrs=s@76&gl=cn&x=%d&y=%d&z=%d&s=Galileo",
//		iServerNum,x,y,z);//
	//CreateDirectory(strFileDirect, NULL);
//	char pBuffer[1024];
	//获取地图url
	CMapBase::GetMapUrl(x,y,z,strURL,256);
	//内存
	MemoryStruct chunk;
//	int errcode= InterNet_httpget(strURL,&chunk);
	int errcode= curl_httpget(strURL,&chunk,NULL);
	if(!errcode)
	{
		if ( strstr( chunk.memory,"html" ) ){
			if(chunk.memory)
				free(chunk.memory);
			CMapBase::GetMapUrlBk(x,y,z,strURL,256);
			//	errcode= InterNet_httpget(strURL,&chunk);
			errcode= curl_httpget(strURL,&chunk,NULL);
			if(errcode)
			{
				return false;
			}
		}
		CVOSFile fileWrite; 
		if( fileWrite.Open( strWriteName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
		{
			fileWrite.Write( chunk.memory, chunk.size );
			fileWrite.Close();
			//AfxMessageBox("下载完毕");
		}
		else
		{
			//AfxMessageBox("本地文件"+strWriteName+"打开出错."); 
		}
	}
	if(chunk.memory)
		free(chunk.memory);
	return 1;
}
//得到当前比例尺的范围
void CMapDown::GetLevelBound( int z )
{
	float itemp =(2<<(z-1))*256;
	itemp = itemp/2;
	
	m_iMinX = 0;
	m_iMaxX = 2<<(z-1);
	m_iMinY = 0;
	m_iMaxY = 2<<(z-1);
	if ( z > 3 && itemp > 0 )
	{
		//计算精度纬度范围内的网格数量
		MapPoint gplt = lonLat2Mercator(m_mapBound.TopLeft(),itemp );
		MapPoint gprb = lonLat2Mercator(m_mapBound.BottomRight(),itemp );
		m_iMinX = ( itemp + gplt.x )/256;
		m_iMaxX = (itemp + gprb.x)/256;
		m_iMinY = (itemp - gplt.y)/256;
		m_iMaxY = (itemp - gprb.y)/256;
	}
}
//获得上次下载位置
bool CMapDown::GetDownPosition( int& x, int& y, int& z )
{
	CFile fileWrite; 
	CString strFileName = m_strRootPath;
	strFileName+=m_strIndex;
	if( fileWrite.Open( strFileName, CFile::modeRead ) )
	{
		fileWrite.Read( &x,4);
		fileWrite.Read( &y,4);
		fileWrite.Read( &z,4);
		fileWrite.Close();
		m_ix = x;
		m_iy = y;
		m_iz = z;
	}
	m_pWnd->Invalidate(false);
	return 1;
}
//获得下载位置
bool CMapDown::GetNextDownPosition( int& x, int& y, int& z )
{

	bool bRet = false;
	/*	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{*/
		this->SaveDownPosition(x,y,z);
		m_ix++;
		if ( m_ix < m_iMinX )
		{
			m_ix = m_iMinX;
			//x = m_ix;
		}
		if ( m_ix > m_iMaxX )
		{
			m_iy++;
			m_ix = m_iMinX;
		}
		if ( m_iy < m_iMinY )
		{
			m_iy = m_iMinY;
		}
		if ( m_iy > m_iMaxY )
		{
			m_iz++;
			GetLevelBound(m_iz);
			m_ix = m_iMinX;
			m_iy = m_iMinY;
			CreateLevelDir(m_iz);
		}
		x = m_ix;
		y = m_iy;
		z = m_iz;
	//	ReleaseMutex( m_hDownLoadMutex );
	//}
	return bRet;
}
//保存下载位置
void CMapDown::SaveDownPosition( int x, int y, int z )
{
	CString strFileName = m_strRootPath;
	strFileName+=m_strIndex;
	CFile fileWrite; 
    if( fileWrite.Open(strFileName, CFile::modeWrite|CFile::modeCreate) )
    {
		fileWrite.Write( &x,4);
		fileWrite.Write( &y,4);
		fileWrite.Write( &z,4);
		fileWrite.Close();
	}
	this->m_pWnd->Invalidate();
}
//下载数据线程
unsigned long __stdcall CMapDown::DownLoadProc( void* pParameter )
{
	CMapDown* pDownLoad = (CMapDown*)pParameter;
	//GetNextDownPosition( pDownLoad->m_ix, pDownLoad->m_iy,pDownLoad->m_iz);
	int ix = pDownLoad->m_ix;
	int iy = pDownLoad->m_iy;
	int iz = pDownLoad->m_iz;
	pDownLoad->GetNextDownPosition( ix,iy,iz);
	while( !pDownLoad->m_bExitProc )
	{
		//GetNextDownPosition();
		if( pDownLoad->GetMap(ix,iy,iz) )
		{
			pDownLoad->GetNextDownPosition( ix,iy,iz);
			if ( iz > 20 ) {
				return 1;
			}
		}
	}
	return 1;
}