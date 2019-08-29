#include "StdAfx.h"
#include "MapDataDown.h"
#include "../MapBase/MapBase.h"
#include "../MapDisp/MapDisp.h"
#pragma comment(lib,"wininet.lib")
#include <afxinet.h>

//保存下载位置
void SaveDownPosition( int x, int y, int z )
{
	string strFileName = "c:\\pos.dat";
	CVOSFile fileWrite; 
    if( fileWrite.Open(strFileName.c_str(), fomReadWrite|fomCreate) )
    {
		fileWrite.Write( (char*)&x,4);
		fileWrite.Write( (char*)&y,4);
		fileWrite.Write( (char*)&z,4);
		fileWrite.Close();
	}
}

bool m_bExitProc = false;
CMapDataDown::CMapDataDown(void)
{
	m_bExitProc = false;
	m_pMapDisp = NULL;
}

CMapDataDown::~CMapDataDown(void)
{
	m_bExitProc = true;
	m_pMapDisp = NULL;
}
void CMapDataDown::Init( CMapDisp* pMapDisp )
{
	SaveDownPosition( 53985,22911  ,16);
	m_pMapDisp = pMapDisp;
	m_hDownLoadMutex = CreateMutex( NULL,false,NULL );
//	InitializeCriticalSection( &m_cs );
	DWORD dwThreadID = 0;
	//CreateDirectory( _T("gmapdata"), NULL);
	//	Init_CUtilMD5( &m_UtilMD5 );
#ifdef _ENCRYPTION_FILE_NAME
	HANDLE h = ::CreateThread( NULL,0 ,&CMapDataDown::DownLoadProc,this,0,&dwThreadID );
	CloseHandle( h );
#endif
}
void CMapDataDown::realse()
{
	m_bExitProc = true;
	m_pMapDisp = NULL;
	ClearDownLoadList();
}

//添加下载项到下载列表列表
bool CMapDataDown::AddDownLoadList( int x, int y, int z,int iMapID )
{
	bool bRet = false;
//	EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end(); ++it)
		{
			CDownLoadParam* downloadparam = *it;
			if ( downloadparam->iX == x && downloadparam->iY == y && downloadparam->iZ == z && iMapID == downloadparam->iMapID ) 
			{
				ReleaseMutex( m_hDownLoadMutex );
				//LeaveCriticalSection( &m_cs );
				return bRet;
			}
		}
//		TRACE("add x=%d,y=%d.z=%d m_iDownLoadCount=%d \r\n",x,y,z, m_iDownLoadCount);
		CDownLoadParam* downloadparam = new CDownLoadParam();
		downloadparam->iX = x;
		downloadparam->iY = y;
		downloadparam->iZ = z;
		downloadparam->iState = 0;
		downloadparam->iMapID = iMapID;
		m_arrDownLoadParam.push_back(downloadparam);
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hDownLoadMutex );
	}
	bRet =true;
	return bRet;
}

//从下载列表获取一个下载项，并置该下载项为下载状态
bool CMapDataDown::GetNoDownLoadList( CDownLoadParam*& param )
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end(); ++it)
		{
			param = *it;
			if ( param->iState == 0 ) 
			{
				//LeaveCriticalSection( &m_cs );
				ReleaseMutex( m_hDownLoadMutex );
				return true;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hDownLoadMutex );
	}
	return false;
}
//得到一个正在下载的列表
bool CMapDataDown::GetDownLoadList( CDownLoadParam*& param )
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end(); ++it)
		{
			param = *it;
			if ( param->iState == 1 ) 
			{
				//LeaveCriticalSection( &m_cs );
				ReleaseMutex( m_hDownLoadMutex );
				return true;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hDownLoadMutex );
	}
	return false;
}
//删除一个下载项
bool CMapDataDown::RemoveDownLoadList( int x, int y, int z )
{
//	TRACE("remove x=%d,y=%d.z=%d m_iDownLoadCount=%d \r\n",x,y,z, m_iDownLoadCount);
	bool bRet = false;
	return bRet;
}
//清除列表
bool CMapDataDown::ClearDownLoadList()
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		CDownLoadParam* param=NULL;
		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end(); ++it)
		{
			param = *it;
			delete param;
		}
		m_arrDownLoadParam.clear();
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hDownLoadMutex );
	}
	return true;
}
	
	//清除没有开始下载的列表
bool CMapDataDown::ClearNoDownLoadList()
{
//	EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hDownLoadMutex,
		100 ) == WAIT_OBJECT_0 )
	{
		CDownLoadParam* param=NULL;
		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end();)
		{
			param = *it;
			if( param->iState == 0 || param->iState == 3) 
			{
				delete param;
				it = m_arrDownLoadParam.erase(it);
			}
			else
			{
				 ++it;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hDownLoadMutex );
	}
	return true;
}
//重命名下载后的文件名
bool CMapDataDown::RenameDownLoadFile( CDownLoadParam* pParam )
{
//	CDownLoadParam* param = NULL;
///	bool	bret = false;
//	EnterCriticalSection( &m_cs );
////	if( WaitForSingleObject( m_hDownLoadMutex,
////		100 ) == WAIT_OBJECT_0 )
//	{
//		for (list<CDownLoadParam*>::iterator it = m_arrDownLoadParam.begin(); it != m_arrDownLoadParam.end();)
//		{
//			param = *it;
//			if( param->iX == pParam->iX && pParam->iY == param->iY && param->iZ == pParam->iZ ) 
//			{
//				it = m_arrDownLoadParam.erase(it);
//				break;
//			}
//			else
//			{
//				 ++it;
//			}
//		}
//		LeaveCriticalSection( &m_cs );
//	//	ReleaseMutex( m_hDownLoadMutex );
// 	}
	string strFilePathUse,strFilePathDown;
//	CMapBase::GetMapDataEncryptionPath( pParam->iX,pParam->iY,pParam->iZ,strFilePathUse,256);
	if( !m_pMapDisp )
		return false;
	CMapBase::GetMapDataPath( pParam->iX,pParam->iY,pParam->iZ, strFilePathUse , pParam->iMapID);
	strFilePathDown = strFilePathUse + _T("1");
	CVOSFile::Rename( strFilePathDown.c_str(), strFilePathUse.c_str() );
	pParam->iState = 3;
	return true;
}
//
bool CMapDataDown::bLoacked()
{
	return 1;
}
//下载线程
unsigned long __stdcall CMapDataDown::DownLoadProc( void* pParameter )
{
	CMapDataDown* pDownLoad = (CMapDataDown*)pParameter;
	CDownLoadParam* pParam = NULL;
	MemoryStruct chunk;
	chunk.memory = (char*)malloc(1024*1024); //最大内存不超过1M
	while ( !m_bExitProc ) 
	{
		pParam = NULL;
		try
		{
			if( pDownLoad->GetNoDownLoadList( pParam ) )
			{
				pParam->iState = 1;
				//下载
				CMapBase::WriteLog("DownLoadProc");
				//开始下载
				pDownLoad->DownLoadMap( pParam, &chunk );
		//		TRACE("SendMessage x=%d,y=%d.z=%d m_iDownLoadCount=%d \r\n",pParam->iX,pParam->iY,pParam->iZ, pDownLoad->m_iDownLoadCount);
				if(m_bExitProc)
				{
					free( chunk.memory );
					return 0;
				}
				if( pDownLoad->m_pMapDisp != NULL )
				{
					if( pDownLoad->m_pMapDisp->m_hwnd != 0 )
					{
						pParam->iState = 2;
						PostMessage( pDownLoad->m_pMapDisp->m_hwnd,WM_DOWNLOAD_MESSAGE,0, (long)pParam );
					}
				}
			}
			Sleep(100);
		}
		catch ( ... ) {
			if(m_bExitProc)
			{
				free( chunk.memory );
				return 0;
			}
		}
	}
	free( chunk.memory );
	return 1;
}
int InterNet_httpget(CString strURL,struct MemoryStruct *chunk )
{
	HINTERNET internet=InternetOpen("HTTP Downloader 1", INTERNET_OPEN_TYPE_PRECONFIG, 
        NULL, NULL, NULL);
    if(!internet)
	{
        throw "InternetOpen error!";
		return 1 ;
	}
    //打开一个http url地址
    HINTERNET file_handle = InternetOpenUrl(internet, strURL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if(!file_handle)
	{
        //throw "InternetOpenUrl error! - Maybe you should add Http:// or Ftp://";
		return 2 ;
	}
	chunk->size = 0;
	char* ptemp = chunk->memory;
	int b=false;
	unsigned long ilen = 0 ;
	while(1)
	{
		if ( chunk->size >1024*1023 )
		{
			break;
		}
		b = InternetReadFile( file_handle, ptemp, 1024, &ilen);
		if(!b )
		{
			//throw "InternetReadFile error!";
			break;
		}
		if( ilen <= 0 )
		{
			break;
		}
		ptemp += ilen;
		chunk->size += ilen;
	}
	//关闭连接
	InternetCloseHandle(internet);
	return 0;
}
//获取谷歌常规地图
bool CMapDataDown::DownLoadMap( CDownLoadParam* pParam,struct MemoryStruct *chunk)
{
//	vchar strSentence[256], strFileDirect[256];
	vchar strURL[256];
	int iServerNum = rand()%4;//产生[0,m)的随机数  
//	sprintf(strFileDirect,_T("gmapdata/level%d",z);

	string strWriteName;
	if( !m_pMapDisp )
		return false;
	CMapBase::GetMapDataPath( pParam->iX,pParam->iY,pParam->iZ, strWriteName,pParam->iMapID );
	//CMapBase::GetMapDataEncryptionPath( pParam->iX,pParam->iY,pParam->iZ,strWriteName,256);
	strWriteName += _T("1") ;

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
	memset(strURL,0,256);
	CMapBase::GetMapUrl( pParam->iX,pParam->iY,pParam->iZ,pParam->iMapID,strURL,256 );
	//CMapBase::GetMapUrl(pParam->iX,pParam->iY,pParam->iZ,strURL,256);
//	if( pParam->iMapType )
//		CMapBase::GetMapUrlMark(pParam->iX,pParam->iY,pParam->iZ,strURL,256);
//	else
//		CMapBase::GetMapUrl(pParam->iX,pParam->iY,pParam->iZ,strURL,256);
	//内存
	chunk->size = 0;
	int errcode= InterNet_httpget(strURL,chunk);
//	int errcode= curl_httpget(strURL,chunk,NULL);
//	if(!chunk.memory)
//		return false;
	if(!errcode)
	{
		if ( strstr( chunk->memory,"html" ) ){

			CMapBase::GetMapUrlBk(pParam->iX,pParam->iY,pParam->iZ,strURL,256);
			errcode= InterNet_httpget(strURL,chunk);
		//	errcode= curl_httpget(strURL,chunk,NULL);
			if(errcode)
			{
				return false;
			}
		}
		CVOSFile fileWrite; 
		if( fileWrite.Open( strWriteName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
		{
			fileWrite.Write( chunk->memory, chunk->size );
			fileWrite.Close();
			//AfxMessageBox("下载完毕");
		}
		else
		{
			//AfxMessageBox("本地文件"+strWriteName+"打开出错."); 
		}
	}
	return 1;
}