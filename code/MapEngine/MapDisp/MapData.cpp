#include "stdafx.h"
#include "MapData.h"
#include "MapDispLayer.h"
#include "MapDisp.h"

//#define FILEMAXSIZE 1847*1024*1024	
#define FILEMAXSIZE 2048*1024*1024-1


MapBlockHead* g_pMapBlockHead = NULL;
// CDlgQuery �Ի���
static int _sql_callback(void * notused, int argc, char ** argv, char ** szColName)
{
    int i;
    for ( i=0; i < argc; i++ )
    {
        TRACE( "%s = %s\n", szColName[i], argv[i] == 0 ? "NUL" : argv[i] );
    }
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

CMapData::CMapData(void)
{
	//m_iBlockCount = 0;
	m_pMapDisp = NULL;
	m_pMapIndexData = NULL;
	m_iNewMapFileID = 0;
	m_enMapType = GMAP_FILES;
}
CMapData::~CMapData(void)
{
	Realse();
}
void CMapData::Init( CMapDisp* pMapDisp )
{
	m_pMapDisp = pMapDisp;
	m_hMapDataMutex = CreateMutex( NULL,false,NULL );
	m_MapDataDown.Init(this);
}
//�ͷ��ڴ�
void CMapData::Realse()
{
	//m_MapDataIndex.ClearAll();
	if( m_pMapIndexData )
	{
		free( m_pMapIndexData );
		m_pMapIndexData = NULL;
	}
	if( m_hMapDataMutex )
	{
		CloseHandle( m_hMapDataMutex );
		m_hMapDataMutex = NULL;
	}
	m_MapLoadData.ClearAll();
	m_SqliteDB.CloseDB();
}

//���õ�ͼ·��
bool CMapData::SetMapPath( string strMapPath, en_MapType enMapType )
{
	m_strMapPath = strMapPath;
	if( m_enMapType == enMapType )
		return true;
	m_MapDataDown.SetMapType( enMapType );
	//��ͼ�������
	//m_MapDataIndex.ClearAll();
	m_SqliteDB.CloseDB();
	//��ͼ��������
	//m_strFileIndex = m_strMapPath;
	//m_strFileIndex += "\\gm.g4i";	
	//m_MapDataIndex.OpenTreeFile( m_strFileIndex );

	//m_MapDataIndex.OpenTreeFile( strMapPath );
	//m_MapDataIndex.Create(20);
	//
	//���Դ���
	/*MapBlockHead Block;
	Block.sLevel = 4;
	Block.lNumX = 10;
	Block.lNumY = 5;
	m_MapDataIndex.AddData( Block.sLevel, Block.lNumX, Block.lNumY, &Block );
	MapBlockHead* pBlockHead1 = (MapBlockHead*)m_MapDataIndex.GetData( Block.sLevel, Block.lNumX, Block.lNumY );
	*/
	//ɾ����������
	m_MapLoadData.ClearAll();
	m_MapLoadData.Create(20);
	//
	m_enMapType = enMapType;

	//��ȡ��������
	m_pMapIndexData = NULL;
	m_iNewMapFileID = 0;

	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	m_SqliteDB.OpenDB( strDBIndex, "gmapindex" );

	/*
	m_strFileIndex = m_strMapPath;
	m_strFileIndex += "\\gm.g4i";
	//��ͼ��������
	m_MapDataIndex.OpenTreeFile( m_strFileIndex );
	*/
	/*
	CVOSFile fileIndex;
	if( fileIndex.Open( m_strFileIndex.c_str(), fomReadWrite ) )
	{
		int iLen = fileIndex.GetLength();
		m_pMapIndexData = (char*)malloc( iLen );
		char* pTemp = m_pMapIndexData;
		int iReadLen = 0;
		while( iReadLen < iLen )
		{
			iReadLen = fileIndex.Read( pTemp,iLen-iReadLen ); 
			pTemp += iReadLen;
		}
		//�����ͼ��������
		long lTime = ::GetTickCount();
		m_MapDataIndex.Create( m_pMapIndexData, iLen );
		
		//char ch[64];
		
		pTemp = m_pMapIndexData;
		while( pTemp - m_pMapIndexData < iLen )
		{
			MapBlockHead* pBlock = (MapBlockHead*)pTemp;
			//sprintf( ch,"%d_%d_%d",pBlock->sLevel,pBlock->lNumY,pBlock->lNumX );
			if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
			{
				pTemp+=sizeof(MapBlockHead);
				continue;
			}
			m_MapDataIndex.AddData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY, pBlock );
			MapBlockHead* pBlock1 = (MapBlockHead*)m_MapDataIndex.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
			m_iNewMapFileID = MAX( m_iNewMapFileID, pBlock->sFileID );
			pTemp+=sizeof(MapBlockHead);
		}
		lTime = ::GetTickCount()-lTime;
		fileIndex.Close();
	}
	else
	{
		if( !fileIndex.Open( m_strFileIndex.c_str(), fomReadWrite|fomCreate ) )
		{
			string strLog  = "�޷�������ͼ���ݣ�";
			strLog += m_strFileIndex;
			CVOSUtil::MessageBox( strLog.c_str(),"������ʾ" );
			return false;
		}
		//fileIndex.Write( m_data, 24 );
		fileIndex.Close();
	}*/
	return true;
}

//�õ���ͼ���ݿ�
CMapBlockUnit* CMapData::GetMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID )
{
	if( WaitForSingleObject( m_hMapDataMutex,
				INFINITE ) == WAIT_OBJECT_0 )
	{
		char ch[64];
		sprintf( ch,"%d_%d_%d", sLevel, lNumX, lNumY );
		//map<string,CMapBlockUnit*>::iterator it;
		CMapBlockUnit* pBlock = (CMapBlockUnit*)m_MapLoadData.GetData( sLevel, lNumX, lNumY );
		//����ڴ����У���ֱ��ʹ��
		if( pBlock )
		{
			ReleaseMutex( m_hMapDataMutex );
			return pBlock;
		}
		if( g_pMapBlockHead )
		{
			delete g_pMapBlockHead;
			g_pMapBlockHead = NULL;
		}
		int iRet = m_SqliteDB.QueryData( sLevel, lNumX, lNumY, _sql_callback );
		//tTree4Node* pNode = m_MapDataIndex.GetData( sLevel, lNumX, lNumY );
		//��������������������
		if( iRet )
		{
			char* pData = (char*)malloc(g_pMapBlockHead->lFileSize);
			char strPath[256]={0};
			sprintf( strPath, "%s\\%d.gd",m_strMapPath.c_str(),g_pMapBlockHead->sFileID );
			CVOSFile fileData;
			if( fileData.Open( strPath, fomReadWrite ) )
			{
				fileData.Seek( g_pMapBlockHead->lFilePos, fspBegin );
				int len = fileData.Read( pData, g_pMapBlockHead->lFileSize );
				if( len == g_pMapBlockHead->lFileSize )
				{
					pBlock = new CMapBlockUnit();
					if( pBlock->LoadImg( pData, len ) )
					{
						fileData.Close();
						free( pData );
						m_MapLoadData.AddData( sLevel, lNumX, lNumY, pBlock );
						ReleaseMutex( m_hMapDataMutex );
						return pBlock;
					}
					delete pBlock;
				}
				free( pData );
				fileData.Close();
			}
		}
		ReleaseMutex( m_hMapDataMutex );
		//������û���ҵ�������������б�
		if( this->m_enMapType == GMAP_FILES )
			return NULL;
		m_MapDataDown.AddDownLoadList( lNumX,lNumY,sLevel,iMapID);
	}
	return NULL;
}

//��ӵ�ͼ���ݿ�
bool CMapData::AddMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID, char* pData, int len )
{
	CMapBlockUnit* pBlock = new CMapBlockUnit();
	pBlock->lLevel = sLevel;
	pBlock->lNumX = lNumX;
	pBlock->lNumY = lNumY;
	if( WaitForSingleObject( m_hMapDataMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		if( m_enMapType != iMapID )
		{
			ReleaseMutex( m_hMapDataMutex );
			delete pBlock;
			return false;
		}
		if( !pBlock->LoadImg( pData, len ) )
		{
			ReleaseMutex( m_hMapDataMutex );
			delete pBlock;
			return false;
		}
		//������ڴ�
		m_MapLoadData.AddData( sLevel, lNumX, lNumY, pBlock );
		//����
		SaveMapData( sLevel, lNumX, lNumY, pData, len );
		//--
		ReleaseMutex( m_hMapDataMutex );
	}
	return true;
}
bool CMapData::SaveMapData( short sLevel, long lNumX, long lNumY, char* pData, int len )
{
	char strPath[256]={0};
	sprintf( strPath,"%s\\%d.gd",m_strMapPath.c_str(), m_iNewMapFileID );
	CVOSFile fileData;
	if( !fileData.Open( strPath, fomReadWrite ) )
	{
		if( !fileData.Open( strPath, fomReadWrite|fomCreate ) )
		{
			string strLog  = "�޷������ͼ���ݣ�";
			strLog += strPath;
			CVOSUtil::MessageBox( strLog.c_str(),"������ʾ" );
			return false;
		}
	}
	unsigned long iFileLen  = fileData.GetLength();
	if( iFileLen > FILEMAXSIZE-len )
	{
		m_iNewMapFileID++;
		fileData.Close();
		sprintf( strPath,"%s\\%d.gd",m_strMapPath.c_str(), m_iNewMapFileID );
		if( !fileData.Open( strPath, fomReadWrite|fomCreate ) )
		{
			string strLog  = "�޷������ͼ���ݣ�";
			strLog += strPath;
			CVOSUtil::MessageBox( strLog.c_str(),"������ʾ" );
			return false;
		}
		iFileLen  = 0;
	}
	//�����ļ�
	fileData.SeekToEnd();
	fileData.Write( pData, len );
	fileData.Close();

	//������������
	MapBlockHead mapBlockUnit;
	mapBlockUnit.lNumX=lNumX;				//X������
	mapBlockUnit.lNumY=lNumY;				//Y������
	mapBlockUnit.sLevel=sLevel;				//������
    mapBlockUnit.sFileID=m_iNewMapFileID;	//�ļ�ID���ļ���ID����
	mapBlockUnit.lFilePos=iFileLen;			//�ļ�λ��
	mapBlockUnit.lFileSize=len;				//�ļ���С
	
	this->m_SqliteDB.WriteEnd( &mapBlockUnit );
	/*
	CVOSFile fileIndex; 
	if( fileIndex.Open( m_strFileIndex.c_str(), fomReadWrite ) )
	{
		fileIndex.SeekToEnd();
		fileIndex.Write( &mapBlockUnit,sizeof( MapBlockHead ) );
		fileIndex.Close();
	}*/
	return true;
}
//�����µĵ�ͼ�����ļ�
int CMapData::OpenMapDataFile( int iFileID )
{
	char chtmep[10];
	sprintf( chtmep, "\\%d.gd", iFileID );
	string strFileData = m_strMapPath;
	strFileData += chtmep;
	//-
	m_FileData.Close();
	if( !m_FileData.Open( strFileData.c_str(), fomReadWrite ) )
	{
		if( !m_FileData.Open( strFileData.c_str(), fomReadWrite|fomCreate ) )
		{
			::MessageBox( NULL,_T("�򿪴����ļ�ʧ�ܣ�ϵͳ�˳�!"),_T("������ʾ"),MB_OK );
			::exit(0);
			return -1;
		}
	}
	return iFileID;
}