// MapData.cpp: implementation of the CMapData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapdown.h"
#include "MapData.h"
//#include "../../gmapdown/gmapdownDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define TEMPDATASIZE 200*1024*1024
#define TEMPDATAINDEXSIZE 2*1024*1024
#define FILEMAXSIZE 2048*1024*1024-1

MapBlockHead* g_pMapBlockHead = NULL;
// CDlgQuery 对话框
static int _sql_callback(void * notused, int argc, char ** argv, char ** szColName)
{
    /*
	int i;
    for ( i=0; i < argc; i++ )
    {
        TRACE( "%s = %s\n", szColName[i], argv[i] == 0 ? "NUL" : argv[i] );
    }*/
	if( argc != 6 )
	{
		return 0;
	}
	g_pMapBlockHead = new MapBlockHead();
	g_pMapBlockHead->sLevel = atoi(argv[0]);
	g_pMapBlockHead->lNumX = atoi(argv[1]);
	g_pMapBlockHead->lNumY = atoi(argv[2]);
	g_pMapBlockHead->sFileID = atoi(argv[3]);
	g_pMapBlockHead->lFilePos = atoi(argv[4]);
	g_pMapBlockHead->lFileSize = atoi(argv[5]);
    return 1;
}	
CMapData::CMapData()
{
//	m_pDataTemp = (char*)malloc( TEMPDATASIZE );
//	m_pDataIndex = (char*)malloc( TEMPDATAINDEXSIZE ); 
	m_iMapFileID = 0;
	m_bExitProc = true;
}

CMapData::~CMapData()
{
	/*int iDataLen = TEMPDATASIZE;
	int iIndexLen = TEMPDATAINDEXSIZE;
	int iCount = GetMapData( m_pDataTemp, iIndexLen, m_pDataIndex, iDataLen );
	if( iCount > 0 )
	{
		SaveMapData( m_pDataIndex, iIndexLen, m_pDataTemp, iDataLen );
	}*/
	Realse();
//	free( m_pDataTemp );
//	free( m_pDataIndex );
	
}
bool CMapData::Init( const char* strMapPath )
{
	//创建互斥区
	m_hMapDataMutex = CreateMutex( NULL,false,NULL );
	m_strMapPath = strMapPath;
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"启动");
	return true;
}
//启动数据保存线程
void CMapData::StartSaveProc()
{
	//int len = 1024*1024*1000*2;
	m_bExitProc = false;
	//--
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapData::MapDataProc,this,0,&dwThreadID );
	CloseHandle( h );
}
//打开下载好的数据
bool CMapData::OpenMapData()
{
	//创建文件夹
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}

	//初始化文件索引管理
//	m_FourTree.Create(20);
	m_iMapOffSet = 0;
	m_iMapFileID = 0;

	//读取索引数据
	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	m_SqliteDB.OpenDB( strDBIndex, "gmapindex" );
	//--数据文件
	char chtmep[10];
	sprintf( chtmep, "\\%d.gd", m_iMapFileID );
	string strFileData = m_strMapPath;
	strFileData += chtmep;
	
	//提示是否续传
	/*
	m_FileIndex.Close();
	if( m_FileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		if( ::MessageBox( NULL,_T("是否打开历史数据!"),_T("警告提示"),MB_YESNO ) == IDNO )
		{
			m_FileIndex.Close();
			if( ::MessageBox( NULL,_T("是否删除历史文件!"),_T("警告提示"),MB_YESNO ) == IDYES )
			{
				CVOSFile::Remove( strFileIndex.c_str() );
				CVOSFile::Remove( strFileData.c_str() );
			}
			return false;
		}
	}
	else
	{
		if( !m_FileIndex.Open( strFileIndex.c_str(), fomReadWrite|fomCreate ) )
		{
			CVOSUtil::MessageBox( "打开文件失败，请关闭相关进程或重启电脑后再试！","提示" );
			return false;
		}
	}
	
	//如果续传
	int iLen = m_FileIndex.GetLength();
	if( iLen % sizeof( MapBlockHead ) != 0 )
	{
		ASSERT( 0 );
	}
	char* pData = (char*)malloc( iLen );
	char* pTemp = pData;
	int iReadLen = 0;
	while(1)
	{
		iReadLen = m_FileIndex.Read( pTemp,iLen ); 
		pTemp += iReadLen;
		if( iReadLen >= iLen )
			break;
	}
	//int iiii=0;
	pTemp = pData;
	int iCount=0;
	while( pTemp - pData < iLen )
	{
		MapBlockHead* pBlock = (MapBlockHead*)pTemp;
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			pTemp+=sizeof(MapBlockHead);
			continue;
		}
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			::MessageBox( NULL,_T("数据被破坏，续传失败!"),_T("警告提示"),MB_YESNO );
		}
		//加载已经存在的数据
		m_iMapFileID = pBlock->sFileID;
		m_FourTree.AddData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY, pBlock );
		m_LevelParam[pBlock->sLevel].m_dPos++;
		iCount++;
		//--
		//MapBlockHead* pBlock1 = (MapBlockHead*)m_FourTree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
		pTemp+=sizeof(MapBlockHead);
	}
	*/
	//打开数据文件
	OpenMapDataFile( m_iMapFileID );
	return true;
}
//创建数据库索引
bool CMapData::CreateDBIndex()
{
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"正在创建数据库索引！");
	//创建文件夹
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}
	//读取索引数据
	string strFileIndex = m_strMapPath;
	strFileIndex += "\\gm.gi";

	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	CSqliteDB sqliteDB;
	sqliteDB.CreateDB( strDBIndex, "gmapindex" );
	//提示是否续传
	CVOSFile fileIndex;
	if( !fileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		CVOSUtil::MessageBox( "打开文件失败，请关闭相关进程或重启电脑后再试！","提示" );
	}

	//如果续传
	int iLen = fileIndex.GetLength();
	if( iLen % sizeof( MapBlockHead ) != 0 )
	{
		ASSERT( 0 );
	}
	char* pData = (char*)malloc( iLen );
	if( pData == NULL )
	{
		fileIndex.Close();
		m_TimeLog = CTime::GetCurrentTime();
		strcpy( m_strLog,"系统内存不足!");
		return false;
	}
	char* pTemp = pData;
	int iReadLen = 0;
	while(1)
	{
		iReadLen = fileIndex.Read( pTemp,iLen ); 
		if( iReadLen <= 0 )
			return false;
		pTemp += iReadLen;
		if( iReadLen >= iLen )
			break;
	}
	//int iiii=0;
	int iCount=0;
	pTemp = pData;
	strcpy( m_strLog, "正在向数据库添加数据，请不要关闭程序！" );
	sqliteDB.BeginTansaction();
	while( pTemp - pData < iLen )
	{
		MapBlockHead* pBlock = (MapBlockHead*)pTemp;
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			pTemp+=sizeof(MapBlockHead);
			continue;
		}
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			::MessageBox( NULL,_T("数据被破坏，续传失败!"),_T("警告提示"),MB_YESNO );
		}
		//加载已经存在的数据
		m_iMapFileID = pBlock->sFileID;
		//--
		//MapBlockHead* pBlock1 = (MapBlockHead*)m_FourTree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
//		map4Tree.SetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY, pBlock->sFileID, pBlock->lFilePos, pBlock->lFileSize );
		//tTree4Node* pNodeNew = map4Tree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
		
		sqliteDB.Write( pBlock );
		m_LevelParam[pBlock->sLevel].m_dPos++;
		pTemp+=sizeof(MapBlockHead);
	}
	fileIndex.Close();
	sqliteDB.EndTansaction();
	strcpy( m_strLog,"正在创建数据库索引!");
	sqliteDB.CreateIndex();
	sqliteDB.CloseDB();
	free( pData );
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"创建数据库索引完成!");
	CVOSUtil::MessageBox("创建数据库索引完成","提示");
	return true;
}
//创建四叉树索引
bool CMapData::CreateMapFourTree()
{
	//创建文件夹
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}
	//读取索引数据
	string strFileIndex = m_strMapPath;
	strFileIndex += "\\gm.gi";

	string strFileIndex4 = m_strMapPath;
	strFileIndex4 += "\\gm.g4i";
	
	//提示是否续传
	CVOSFile fileIndex;
	if( !fileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		CVOSUtil::MessageBox( "打开文件失败，请关闭相关进程或重启电脑后再试！","提示" );
	}

	//如果续传
	int iLen = fileIndex.GetLength();
	if( iLen % sizeof( MapBlockHead ) != 0 )
	{
		ASSERT( 0 );
	}
	CMapFourTree map4Tree;
	map4Tree.Create( iLen/sizeof(MapBlockHead)*2 );
	char* pData = (char*)malloc( iLen );
	char* pTemp = pData;
	int iReadLen = 0;
	while(1)
	{
		iReadLen = fileIndex.Read( pTemp,iLen ); 
		if( iReadLen <= 0 )
			return false;
		pTemp += iReadLen;
		if( iReadLen >= iLen )
			break;
	}
	//int iiii=0;
	int iCount=0;
	pTemp = pData;
	while( pTemp - pData < iLen )
	{
		MapBlockHead* pBlock = (MapBlockHead*)pTemp;
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			pTemp+=sizeof(MapBlockHead);
			continue;
		}
		if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
		{
			::MessageBox( NULL,_T("数据被破坏，续传失败!"),_T("警告提示"),MB_YESNO );
		}
		//加载已经存在的数据
		m_iMapFileID = pBlock->sFileID;
		//--
		//MapBlockHead* pBlock1 = (MapBlockHead*)m_FourTree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
		map4Tree.SetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY, pBlock->sFileID, pBlock->lFilePos, pBlock->lFileSize );
		//tTree4Node* pNodeNew = map4Tree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
		iCount++;
		pTemp+=sizeof(MapBlockHead);
	}
	fileIndex.Close();
	map4Tree.SaveTree( strFileIndex4 );
	free( pData );
	return true;
}
//添加
bool CMapData::AddMapFile()
{
	/*
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"正在检测已经当前目录下的数据!");
	while( CheckMapData() )
	{
		;
	}
	*/
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"开始拷贝需要添加的数据，请不要关闭程序!");
	//检测当前文件名
	m_iMapFileID = 0;
	m_FileData.Close();
	while( OpenMapDataFile( m_iMapFileID ) )
	{	
		m_FileData.Close();
		m_iMapFileID++;	
	}
	//开始拷贝文件
	int iOldMapFileID = 0;
	CVOSFile fileData;
	char* pData = (char*)malloc( TEMPDATAINDEXSIZE );
	int iDataLen = 0;
	__int64 iLog1111=0;
	while( 1 )
	{
		char chTemp[20];
		sprintf(chTemp,"\\%d.gd",iOldMapFileID);
		string strFileData= m_strAddMapPath;
		strFileData += chTemp;
		if( !fileData.Open( strFileData.c_str(), fomReadWrite ) )
		{
			if( iOldMapFileID == 0 )
			{
				strcpy( m_strLog,"读取文件错误，请重新选择目录!");
				return false;
			}
			break;
		}
		if( !CreateMapDataFile( m_iMapFileID+iOldMapFileID ) )
		{
			fileData.Close();
			break;
		}
		while(1)
		{
			int iLen = fileData.Read( pData, TEMPDATAINDEXSIZE );
			iLog1111 += iLen;
			sprintf( m_strLog, "正在拷贝数据：%llu，请不要关闭程序,", iLog1111 );
			if( iLen <= 0 )
			{
				break;
			}
			int iLen1 = m_FileData.Write( pData, iLen );
			if( iLen1 != iLen )
			{
				::MessageBox( NULL,_T("数据被破坏，续传失败!"),_T("警告提示"),MB_YESNO );
				return false;
			}
		}
		m_FileData.Close();
		fileData.Close();
		iOldMapFileID++;
	}
	free( pData );

	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"正在重建数据索引，请不要关闭程序!");

	CVOSFile fileIndex;
	//读取索引数据
	string strFileIndex = m_strAddMapPath;
	strFileIndex += "\\gm.gi";
	if( !fileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
		return false;
	int iLen = fileIndex.GetLength();
	if( iLen % sizeof( MapBlockHead ) != 0 )
	{
		ASSERT( 0 );
	}
	char* pHead = (char*)malloc( iLen );
	int iReadLen = 0;
	char* pTemp = pHead;
	while(1)
	{
		iReadLen = fileIndex.Read( pTemp,iLen ); 

		int iiiiierror = ::GetLastError();
		pTemp += iReadLen;
		if( iReadLen >= iLen )
			break;
	}

	//读取头索引
	MapBlockHead* pBlockHead = (MapBlockHead*)pHead;
	m_SqliteDB.CloseDB();
	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	m_SqliteDB.OpenDB( strDBIndex, "gmapindex" );
	m_SqliteDB.DeleteIndex();
	m_SqliteDB.BeginTansaction();
	strcpy( m_strLog, "正在向数据库添加数据，请不要关闭程序！" );
	while( (char*)pBlockHead - pHead < iLen )
	{
		if( pBlockHead->sLevel > 20 || pBlockHead->sLevel < 0 )
		{
			pBlockHead++;
			continue;
		}
		//
		if( pBlockHead->lFileSize > TEMPDATASIZE )
		{
			pBlockHead++;
			continue;
		}
/*		
		if( GetMapData( pBlockHead->sLevel, pBlockHead->lNumX, pBlockHead->lNumY ) )
		{
			pBlockHead++;
			continue;
		}
		*/
		
		//数据头数据
		pBlockHead->sFileID += m_iMapFileID;
		//存储索引
		m_SqliteDB.Write( pBlockHead );
		//--
		m_LevelParam[pBlockHead->sLevel].m_dPos++;
		pBlockHead++;
	}
	m_SqliteDB.EndTansaction();
	strcpy( m_strLog,"正在重建数据索引，请不要关闭程序!");
	m_SqliteDB.CreateIndex();
	CloseMapData();
	strcpy( m_strLog,"合并完成!");
	CVOSUtil::MessageBox("合并完成！","提示");
	return true;
}
unsigned long __stdcall CMapData::CreateDBProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	pMapData->CreateDBIndex();
	return 1;
}
//添加数据线程
unsigned long __stdcall CMapData::AddMapFileProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	pMapData->AddMapFile();
	return 1;
}
//添加数据线程
unsigned long __stdcall CMapData::CheckMapDataProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	strcpy( pMapData->m_strLog,"正在检测已经当前目录下的数据!");
	while( 1 )
	{
		if( pMapData->CheckMapData() )
			;
	}
	strcpy( pMapData->m_strLog,"检测完毕!");
	return 1;
}
//释放内存
void CMapData::Realse()
{
	m_bExitProc = true;
	CloseHandle( m_hMapDataMutex );
}

//创建新的地图数据文件
bool CMapData::CreateMapDataFile( int iFileID )
{
	char chtmep[10];
	sprintf( chtmep, "\\%d.gd", iFileID );
	string strFileData = m_strMapPath;
	strFileData += chtmep;
	if( !m_FileData.Open( strFileData.c_str(), fomReadWrite|fomCreate ) )
	{
		return false;
	}
	return true;
}
//打开地图数据文件
bool CMapData::OpenMapDataFile( int iFileID )
{
	char chtmep[10];
	sprintf( chtmep, "\\%d.gd", iFileID );
	string strFileData = m_strMapPath;
	strFileData += chtmep;
	m_FileData.Close();
	if( !m_FileData.Open( strFileData.c_str(), fomReadWrite ) )
	{
		return false;
	}
	return true;
}
//地图数据索引保存
void CMapData::SaveMap4Tree()
{

}
//打开下载好的数据
bool CMapData::OpenMapData( const char* strMapPath )
{
	m_strMapPath = strMapPath;
	return OpenMapData();
}

//关闭下载好的数据
void CMapData::CloseMapData()
{
	m_FileData.Close();
	m_SqliteDB.CloseDB();
//	m_FileIndex.Close();
}
//查询数据是否存在
MapBlockHead* CMapData::GetMapData( short sLevel, long lNumX, long lNumY )
{
	if( g_pMapBlockHead )
	{
		delete g_pMapBlockHead;
		g_pMapBlockHead = NULL;
	}
	int iRet = m_SqliteDB.QueryData( sLevel, lNumX, lNumY, _sql_callback );
	return g_pMapBlockHead;
}
bool CMapData::AddMapData( MapBlockData* pData )
{
	if( WaitForSingleObject( m_hMapDataMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		//char ch[64];
		//sprintf( ch,"addmapdata %d_%d_%d",pData->sLevel,pData->lNumY,pData->lNumX );
		//g_pGmapdownDlg->AddLog( ch );
		m_arrMapData.push_back( pData );
		ReleaseMutex( m_hMapDataMutex );
		return true;
	}
	return false;
}
//保存多条数据,返回条数
int  CMapData::WriteMapData( )
{
	int iCount =0;
	if( WaitForSingleObject( m_hMapDataMutex,
				INFINITE ) == WAIT_OBJECT_0 )
	{
		m_FileData.SeekToEnd();
		m_SqliteDB.BeginTansaction();
		ulong iFileLength = m_FileData.GetLength();
		MapBlockData* pMapData = NULL;
		MapBlockHead mapBlockHead;
		for (list<MapBlockData*>::iterator it = m_arrMapData.begin(); it != m_arrMapData.end(); ++it)
		{
			pMapData = *it;
			//如果数据超出范围，则跳出循环
			/*if( pDataTemp - pData > iDataLen - pMapData->lDataLenth 
				|| pIndexTemp - pIndex > iIndexLen - sizeof(MapBlockHead)  )
			{
				break;
			}*/
			//超过文件大小，则换文件
			while( iFileLength+pMapData->lDataLenth > FILEMAXSIZE )
			{	
				m_FileData.Close();
				m_iMapFileID++;
				if( !OpenMapDataFile( m_iMapFileID ) )
				{
					//创建新文件
					if( !CreateMapDataFile( m_iMapFileID ) )
					{
						::MessageBox( NULL,_T("创建文件失败，系统退出!"),_T("警告提示"),MB_OK );
						::exit(0);
						return 0;
					};
					iFileLength = 0;
				}
				iFileLength = m_FileData.GetLength();
			}
			
			//数据体数据
			iCount++;
			//数据头数据
			mapBlockHead.lNumX = pMapData->lNumX;
			mapBlockHead.lNumY = pMapData->lNumY;
			mapBlockHead.sLevel = pMapData->sLevel;
			mapBlockHead.sFileID = m_iMapFileID;
			mapBlockHead.lFilePos = iFileLength;
			mapBlockHead.lFileSize = pMapData->lDataLenth;
			//存储数据
			iFileLength += m_FileData.Write( pMapData->pData, pMapData->lDataLenth );
			m_SqliteDB.Write( &mapBlockHead );
			//删除存好的数据
			if( pMapData->pData )
				free( pMapData->pData );
			delete pMapData;
		}
		//--
		m_arrMapData.clear();
		ReleaseMutex( m_hMapDataMutex );
		m_FileData.Flush();
		m_SqliteDB.EndTansaction();
	}
	return iCount;
}
//保存地图数据
/*bool CMapData::SaveMapData( MapBlockData* pMapData )
{
	int len = m_FileData.SeekToEnd();
	int len1 = m_FileData.Write( pMapData->pData, pMapData->lDataLenth );
	if( len1 != pMapData->lDataLenth )
		return false;
	m_FileData.Flush();
	MapBlockHead mapBlockUnit;
	mapBlockUnit.lNumX = pMapData->lNumX;
	mapBlockUnit.lNumY = pMapData->lNumY;
	mapBlockUnit.sLevel = pMapData->sLevel;
	mapBlockUnit.sFileID = m_iMapFileID;
	mapBlockUnit.lFilePos = len;
	mapBlockUnit.lFileSize = pMapData->lDataLenth;

	m_FileIndex.SeekToEnd();
	int len2 = m_FileIndex.Write( &mapBlockUnit,sizeof( MapBlockHead ) );
	if( len2 != sizeof( MapBlockHead ) )
		return false;
	m_FileIndex.Flush();
	return true;
}*/
//下载线程
unsigned long __stdcall CMapData::MapDataProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	return pMapData->Run();
}
//执行线程
int CMapData::Run()
{
	Sleep( 10000 );
	int iDataLen = TEMPDATASIZE;
	int iIndexLen = TEMPDATAINDEXSIZE;
	int iCount = 0;
	while( !m_bExitProc )
	{
		iDataLen = TEMPDATASIZE;
		iIndexLen = TEMPDATAINDEXSIZE;
		iCount = WriteMapData();
		Sleep( 60000 );
	}
	CloseMapData();
	return 1;
}
//获得下载位置
bool CMapData::GetNextPosition( int& x, int& y, int& z )
{
	m_ix++;
	//检测X坐标情况
	if ( m_ix > m_LevelParam[m_iz].m_lMaxX )
	{
		m_iy++;
		m_ix = m_LevelParam[m_iz].m_lMinX;
		//检测Y坐标情况
		if( m_iy > m_LevelParam[m_iz].m_lMaxY )
		{
			m_iz++;
			m_iy = m_LevelParam[m_iz].m_lMinY;
			//检测Z坐标情况
			if( m_iz > m_iMaxLevel )
			{
				return true;
			}
			m_ix = m_LevelParam[m_iz].m_lMinX;
			m_iy = m_LevelParam[m_iz].m_lMinY;
		}
	}
	x = m_ix;
	y = m_iy;
	z = m_iz;
	//检测数据是否下载
	if( this->GetMapData( m_iz, m_ix, m_iy ) )
	{
		m_LevelParam[m_iz].m_dPos++;
		m_LevelParam[m_iz].m_bDownLoad = true;
		return true;
	}
	else
	{
		m_LevelParam[m_iz].m_bDownLoad = false;
		return false;
	}
}
//检测数据
bool CMapData::CheckMapData()
{
	m_ix++;
	//检测X坐标情况
	if ( m_ix > m_LevelParam[m_iz].m_lMaxX )
	{
		m_iy++;
		m_ix = m_LevelParam[m_iz].m_lMinX;
		//检测Y坐标情况
		if( m_iy > m_LevelParam[m_iz].m_lMaxY )
		{
			m_iz++;
			m_iy = m_LevelParam[m_iz].m_lMinY;
			//检测Z坐标情况
			if( m_iz > m_iMaxLevel )
			{
				return true;
			}
			m_ix = m_LevelParam[m_iz].m_lMinX;
			m_iy = m_LevelParam[m_iz].m_lMinY;
		}
	}
	//检测数据是否下载
	if( this->GetMapData( m_iz, m_ix, m_iy ) )
	{
		m_LevelParam[m_iz].m_dPos++;
		m_LevelParam[m_iz].m_bDownLoad = true;
		return true;
	}
	else
	{
		m_LevelParam[m_iz].m_bDownLoad = false;
		return false;
	}
}
