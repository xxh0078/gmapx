#include "StdAfx.h"
#include "MapDataDown.h"
#include "MapData.h"
#include "MapDisp.h"
CMapDataDown::CMapDataDown(void)
{
	m_bExitProc = false;
}

CMapDataDown::~CMapDataDown(void)
{
	m_bExitProc = true;
	Realse();
}
//��ʼ��
void CMapDataDown::Init( CMapData* pMapData )
{
	m_pMapData = pMapData;
	m_hLoadMutex = CreateMutex( NULL,false,NULL );
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapDataDown::Worker,this,0,&dwThreadID );
	CloseHandle( h );
}
//��������
bool CMapDataDown::SetMapType( en_MapType enMapType )
{
	m_enMapType = enMapType;
	return 1;
}
//�ͷ��ڴ�
void CMapDataDown::Realse()
{
	CloseHandle(m_hLoadMutex);
	ClearDownLoadList();
}
//�������������б��б�
bool CMapDataDown::AddDownLoadList( int x, int y, int z,int iMapID )
{
	bool bRet = false;
	if( m_enMapType != iMapID )
		return bRet;
//	EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		/*if( m_listDownLoadParam.size() > 2 )
		{
			ReleaseMutex( m_hLoadMutex );
			return bRet;
		}*/
		for (list<tDownLoadParam*>::iterator it = m_listDownLoadParam.begin(); it != m_listDownLoadParam.end(); ++it)
		{
			tDownLoadParam* downloadparam = *it;
			if ( downloadparam->iX == x && downloadparam->iY == y && downloadparam->iZ == z && iMapID == downloadparam->iMapID ) 
			{
				ReleaseMutex( m_hLoadMutex );
				//LeaveCriticalSection( &m_cs );
				return bRet;
			}
		}
//		TRACE("add x=%d,y=%d.z=%d m_iDownLoadCount=%d \r\n",x,y,z, m_iDownLoadCount);
		tDownLoadParam* downloadparam = new tDownLoadParam();
		downloadparam->iX = x;
		downloadparam->iY = y;
		downloadparam->iZ = z;
		downloadparam->iState = 0;
		downloadparam->iMapID = iMapID;
		m_listDownLoadParam.push_back(downloadparam);
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hLoadMutex );
	}
	bRet =true;
	return bRet;
}

//�������б��ȡһ����������ø�������Ϊ����״̬
bool CMapDataDown::GetNoDownLoadList( tDownLoadParam*& param )
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		for (list<tDownLoadParam*>::iterator it = m_listDownLoadParam.begin(); it != m_listDownLoadParam.end(); ++it)
		{
			param = *it;
			if ( param->iState == 0 ) 
			{
				//LeaveCriticalSection( &m_cs );
				ReleaseMutex( m_hLoadMutex );
				return true;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hLoadMutex );
	}
	return false;
}
//�õ�һ���������ص��б�
bool CMapDataDown::GetDownLoadList( tDownLoadParam*& param )
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		for (list<tDownLoadParam*>::iterator it = m_listDownLoadParam.begin(); it != m_listDownLoadParam.end(); ++it)
		{
			param = *it;
			if ( param->iState == 1 ) 
			{
				//LeaveCriticalSection( &m_cs );
				ReleaseMutex( m_hLoadMutex );
				return true;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hLoadMutex );
	}
	return false;
}
//����б�
bool CMapDataDown::ClearDownLoadList()
{
	//EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		tDownLoadParam* param=NULL;
		for (list<tDownLoadParam*>::iterator it = m_listDownLoadParam.begin(); it != m_listDownLoadParam.end(); ++it)
		{
			param = *it;
			delete param;
		}
		m_listDownLoadParam.clear();
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hLoadMutex );
	}
	return true;
}
	
	//���û�п�ʼ���ص��б�
bool CMapDataDown::ClearNoDownLoadList()
{
//	EnterCriticalSection( &m_cs );
	if( WaitForSingleObject( m_hLoadMutex,
		100 ) == WAIT_OBJECT_0 )
	{
		tDownLoadParam* param=NULL;
		for (list<tDownLoadParam*>::iterator it = m_listDownLoadParam.begin(); it != m_listDownLoadParam.end();)
		{
			param = *it;
			if( param->iState == 0 || param->iState == 2 ) 
			{
				delete param;
				it = m_listDownLoadParam.erase(it);
			}
			else
			{
				 ++it;
			}
		}
		//LeaveCriticalSection( &m_cs );
		ReleaseMutex( m_hLoadMutex );
	}
	return true;
}
bool CMapDataDown::DownLoadMapData( short sLevel, long lNumX, long lNumY,int iMapID,struct MemoryStruct *chunk )
{
	vchar strURL[256];
	//int iServerNum = rand()%4;//����[0,m)�������  
	memset(strURL,0,256);
	CMapBase::GetMapUrl( lNumX,lNumY,sLevel,iMapID,strURL,256 );
	//�ڴ�
	chunk->size = 0;
	int errcode= InterNet_httpget(strURL,chunk);
	if(!errcode)
	{
		if ( strstr( chunk->memory,"html" ) ){
			return false;
			CMapBase::GetMapUrlBk(lNumX,lNumY,sLevel,strURL,256);
			errcode= InterNet_httpget(strURL,chunk);
			if(errcode)
			{
				return false;
			}
		}
	}
	if( chunk->size == 0 )
		return false;
	return true;
}
//�����߳�
unsigned long __stdcall CMapDataDown::Worker( void* pParameter )
{
	CMapDataDown* pMapDataDown = (CMapDataDown*)pParameter;
	return pMapDataDown->RUN();
}
int CMapDataDown::RUN()
{
	tDownLoadParam* pParam = NULL;
	MemoryStruct chunk;
	chunk.memory = (char*)malloc(1024*1024); //����ڴ治����1M
	while ( !m_bExitProc ) 
	{
		//pParam = NULL;
		try
		{
			if( GetNoDownLoadList( pParam ) )
			{
				pParam->iState = 1;
				//����
				CMapBase::WriteLog("DownLoadProc");
				//��ʼ����
				if( !DownLoadMapData( pParam->iZ,pParam->iX,pParam->iY,pParam->iMapID, &chunk ) )
				{
					Sleep(100);
					pParam->iState = 0;
					continue;
				}
		//		TRACE("SendMessage x=%d,y=%d.z=%d m_iDownLoadCount=%d \r\n",pParam->iX,pParam->iY,pParam->iZ, pDownLoad->m_iDownLoadCount);
				if( m_bExitProc)
				{
					free( chunk.memory );
					return 0;
				}
				if( m_pMapData != NULL )
				{
					if( m_pMapData->m_pMapDisp )
					{
						pParam->iState = 2;
						m_pMapData->AddMapBlockUnit( pParam->iZ,pParam->iX,pParam->iY,pParam->iMapID, chunk.memory,chunk.size );
						m_pMapData->m_pMapDisp->Invalidate();
						//pDownLoad->m_pMapDisp->In
						//PostMessage( pDownLoad->m_pMapDisp->m_hwnd,WM_DOWNLOAD_MESSAGE,0, (long)pParam );
					}
				}
			}
			Sleep(100);
		}
		catch ( ... ) {
			if( m_bExitProc )
			{
				free( chunk.memory );
				return 0;
			}
		}
	}
	free( chunk.memory );
	return 1;
}
