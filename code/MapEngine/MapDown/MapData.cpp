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
// CDlgQuery �Ի���
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
	//����������
	m_hMapDataMutex = CreateMutex( NULL,false,NULL );
	m_strMapPath = strMapPath;
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"����");
	return true;
}
//�������ݱ����߳�
void CMapData::StartSaveProc()
{
	//int len = 1024*1024*1000*2;
	m_bExitProc = false;
	//--
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapData::MapDataProc,this,0,&dwThreadID );
	CloseHandle( h );
}
//�����غõ�����
bool CMapData::OpenMapData()
{
	//�����ļ���
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}

	//��ʼ���ļ���������
//	m_FourTree.Create(20);
	m_iMapOffSet = 0;
	m_iMapFileID = 0;

	//��ȡ��������
	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	m_SqliteDB.OpenDB( strDBIndex, "gmapindex" );
	//--�����ļ�
	char chtmep[10];
	sprintf( chtmep, "\\%d.gd", m_iMapFileID );
	string strFileData = m_strMapPath;
	strFileData += chtmep;
	
	//��ʾ�Ƿ�����
	/*
	m_FileIndex.Close();
	if( m_FileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		if( ::MessageBox( NULL,_T("�Ƿ����ʷ����!"),_T("������ʾ"),MB_YESNO ) == IDNO )
		{
			m_FileIndex.Close();
			if( ::MessageBox( NULL,_T("�Ƿ�ɾ����ʷ�ļ�!"),_T("������ʾ"),MB_YESNO ) == IDYES )
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
			CVOSUtil::MessageBox( "���ļ�ʧ�ܣ���ر���ؽ��̻��������Ժ����ԣ�","��ʾ" );
			return false;
		}
	}
	
	//�������
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
			::MessageBox( NULL,_T("���ݱ��ƻ�������ʧ��!"),_T("������ʾ"),MB_YESNO );
		}
		//�����Ѿ����ڵ�����
		m_iMapFileID = pBlock->sFileID;
		m_FourTree.AddData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY, pBlock );
		m_LevelParam[pBlock->sLevel].m_dPos++;
		iCount++;
		//--
		//MapBlockHead* pBlock1 = (MapBlockHead*)m_FourTree.GetData( pBlock->sLevel, pBlock->lNumX, pBlock->lNumY );
		pTemp+=sizeof(MapBlockHead);
	}
	*/
	//�������ļ�
	OpenMapDataFile( m_iMapFileID );
	return true;
}
//�������ݿ�����
bool CMapData::CreateDBIndex()
{
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"���ڴ������ݿ�������");
	//�����ļ���
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}
	//��ȡ��������
	string strFileIndex = m_strMapPath;
	strFileIndex += "\\gm.gi";

	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	CSqliteDB sqliteDB;
	sqliteDB.CreateDB( strDBIndex, "gmapindex" );
	//��ʾ�Ƿ�����
	CVOSFile fileIndex;
	if( !fileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		CVOSUtil::MessageBox( "���ļ�ʧ�ܣ���ر���ؽ��̻��������Ժ����ԣ�","��ʾ" );
	}

	//�������
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
		strcpy( m_strLog,"ϵͳ�ڴ治��!");
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
	strcpy( m_strLog, "���������ݿ�������ݣ��벻Ҫ�رճ���" );
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
			::MessageBox( NULL,_T("���ݱ��ƻ�������ʧ��!"),_T("������ʾ"),MB_YESNO );
		}
		//�����Ѿ����ڵ�����
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
	strcpy( m_strLog,"���ڴ������ݿ�����!");
	sqliteDB.CreateIndex();
	sqliteDB.CloseDB();
	free( pData );
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"�������ݿ��������!");
	CVOSUtil::MessageBox("�������ݿ��������","��ʾ");
	return true;
}
//�����Ĳ�������
bool CMapData::CreateMapFourTree()
{
	//�����ļ���
	if( !CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
		//return false;
	}
	//��ȡ��������
	string strFileIndex = m_strMapPath;
	strFileIndex += "\\gm.gi";

	string strFileIndex4 = m_strMapPath;
	strFileIndex4 += "\\gm.g4i";
	
	//��ʾ�Ƿ�����
	CVOSFile fileIndex;
	if( !fileIndex.Open( strFileIndex.c_str(), fomReadWrite ) )
	{
		CVOSUtil::MessageBox( "���ļ�ʧ�ܣ���ر���ؽ��̻��������Ժ����ԣ�","��ʾ" );
	}

	//�������
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
			::MessageBox( NULL,_T("���ݱ��ƻ�������ʧ��!"),_T("������ʾ"),MB_YESNO );
		}
		//�����Ѿ����ڵ�����
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
//���
bool CMapData::AddMapFile()
{
	/*
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"���ڼ���Ѿ���ǰĿ¼�µ�����!");
	while( CheckMapData() )
	{
		;
	}
	*/
	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"��ʼ������Ҫ��ӵ����ݣ��벻Ҫ�رճ���!");
	//��⵱ǰ�ļ���
	m_iMapFileID = 0;
	m_FileData.Close();
	while( OpenMapDataFile( m_iMapFileID ) )
	{	
		m_FileData.Close();
		m_iMapFileID++;	
	}
	//��ʼ�����ļ�
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
				strcpy( m_strLog,"��ȡ�ļ�����������ѡ��Ŀ¼!");
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
			sprintf( m_strLog, "���ڿ������ݣ�%llu���벻Ҫ�رճ���,", iLog1111 );
			if( iLen <= 0 )
			{
				break;
			}
			int iLen1 = m_FileData.Write( pData, iLen );
			if( iLen1 != iLen )
			{
				::MessageBox( NULL,_T("���ݱ��ƻ�������ʧ��!"),_T("������ʾ"),MB_YESNO );
				return false;
			}
		}
		m_FileData.Close();
		fileData.Close();
		iOldMapFileID++;
	}
	free( pData );

	m_TimeLog = CTime::GetCurrentTime();
	strcpy( m_strLog,"�����ؽ������������벻Ҫ�رճ���!");

	CVOSFile fileIndex;
	//��ȡ��������
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

	//��ȡͷ����
	MapBlockHead* pBlockHead = (MapBlockHead*)pHead;
	m_SqliteDB.CloseDB();
	string strDBIndex = m_strMapPath;
	strDBIndex += "\\gmi.db";
	m_SqliteDB.OpenDB( strDBIndex, "gmapindex" );
	m_SqliteDB.DeleteIndex();
	m_SqliteDB.BeginTansaction();
	strcpy( m_strLog, "���������ݿ�������ݣ��벻Ҫ�رճ���" );
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
		
		//����ͷ����
		pBlockHead->sFileID += m_iMapFileID;
		//�洢����
		m_SqliteDB.Write( pBlockHead );
		//--
		m_LevelParam[pBlockHead->sLevel].m_dPos++;
		pBlockHead++;
	}
	m_SqliteDB.EndTansaction();
	strcpy( m_strLog,"�����ؽ������������벻Ҫ�رճ���!");
	m_SqliteDB.CreateIndex();
	CloseMapData();
	strcpy( m_strLog,"�ϲ����!");
	CVOSUtil::MessageBox("�ϲ���ɣ�","��ʾ");
	return true;
}
unsigned long __stdcall CMapData::CreateDBProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	pMapData->CreateDBIndex();
	return 1;
}
//��������߳�
unsigned long __stdcall CMapData::AddMapFileProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	pMapData->AddMapFile();
	return 1;
}
//��������߳�
unsigned long __stdcall CMapData::CheckMapDataProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	strcpy( pMapData->m_strLog,"���ڼ���Ѿ���ǰĿ¼�µ�����!");
	while( 1 )
	{
		if( pMapData->CheckMapData() )
			;
	}
	strcpy( pMapData->m_strLog,"������!");
	return 1;
}
//�ͷ��ڴ�
void CMapData::Realse()
{
	m_bExitProc = true;
	CloseHandle( m_hMapDataMutex );
}

//�����µĵ�ͼ�����ļ�
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
//�򿪵�ͼ�����ļ�
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
//��ͼ������������
void CMapData::SaveMap4Tree()
{

}
//�����غõ�����
bool CMapData::OpenMapData( const char* strMapPath )
{
	m_strMapPath = strMapPath;
	return OpenMapData();
}

//�ر����غõ�����
void CMapData::CloseMapData()
{
	m_FileData.Close();
	m_SqliteDB.CloseDB();
//	m_FileIndex.Close();
}
//��ѯ�����Ƿ����
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
//�����������,��������
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
			//������ݳ�����Χ��������ѭ��
			/*if( pDataTemp - pData > iDataLen - pMapData->lDataLenth 
				|| pIndexTemp - pIndex > iIndexLen - sizeof(MapBlockHead)  )
			{
				break;
			}*/
			//�����ļ���С�����ļ�
			while( iFileLength+pMapData->lDataLenth > FILEMAXSIZE )
			{	
				m_FileData.Close();
				m_iMapFileID++;
				if( !OpenMapDataFile( m_iMapFileID ) )
				{
					//�������ļ�
					if( !CreateMapDataFile( m_iMapFileID ) )
					{
						::MessageBox( NULL,_T("�����ļ�ʧ�ܣ�ϵͳ�˳�!"),_T("������ʾ"),MB_OK );
						::exit(0);
						return 0;
					};
					iFileLength = 0;
				}
				iFileLength = m_FileData.GetLength();
			}
			
			//����������
			iCount++;
			//����ͷ����
			mapBlockHead.lNumX = pMapData->lNumX;
			mapBlockHead.lNumY = pMapData->lNumY;
			mapBlockHead.sLevel = pMapData->sLevel;
			mapBlockHead.sFileID = m_iMapFileID;
			mapBlockHead.lFilePos = iFileLength;
			mapBlockHead.lFileSize = pMapData->lDataLenth;
			//�洢����
			iFileLength += m_FileData.Write( pMapData->pData, pMapData->lDataLenth );
			m_SqliteDB.Write( &mapBlockHead );
			//ɾ����õ�����
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
//�����ͼ����
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
//�����߳�
unsigned long __stdcall CMapData::MapDataProc( void* pParameter )
{
	CMapData* pMapData = (CMapData*)pParameter;
	return pMapData->Run();
}
//ִ���߳�
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
//�������λ��
bool CMapData::GetNextPosition( int& x, int& y, int& z )
{
	m_ix++;
	//���X�������
	if ( m_ix > m_LevelParam[m_iz].m_lMaxX )
	{
		m_iy++;
		m_ix = m_LevelParam[m_iz].m_lMinX;
		//���Y�������
		if( m_iy > m_LevelParam[m_iz].m_lMaxY )
		{
			m_iz++;
			m_iy = m_LevelParam[m_iz].m_lMinY;
			//���Z�������
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
	//��������Ƿ�����
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
//�������
bool CMapData::CheckMapData()
{
	m_ix++;
	//���X�������
	if ( m_ix > m_LevelParam[m_iz].m_lMaxX )
	{
		m_iy++;
		m_ix = m_LevelParam[m_iz].m_lMinX;
		//���Y�������
		if( m_iy > m_LevelParam[m_iz].m_lMaxY )
		{
			m_iz++;
			m_iy = m_LevelParam[m_iz].m_lMinY;
			//���Z�������
			if( m_iz > m_iMaxLevel )
			{
				return true;
			}
			m_ix = m_LevelParam[m_iz].m_lMinX;
			m_iy = m_LevelParam[m_iz].m_lMinY;
		}
	}
	//��������Ƿ�����
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
