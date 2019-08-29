// MapDown.cpp: implementation of the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapDown.h"
//#include "MapBase.h"
#pragma comment(lib,"wininet.lib")
#include   <wininet.h> 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//char g_strLog[256];
CMapDown::CMapDown()
{
//	m_bLog = false;
	m_bExitProc = true;
}

CMapDown::~CMapDown()
{
	m_bExitProc = true;
	CloseHandle( m_hDownMutex );
}
//��ʼ��
bool CMapDown::Init()
{
	//�����̻߳�����
	m_hDownMutex = CreateMutex( NULL,false,NULL );
	//Ĭ���ļ�·��
	memset( m_strRootPath, 0, 256 );
	GetModuleFileName(AfxGetInstanceHandle(),m_strRootPath,256); 
	char* pEnd = strrchr( m_strRootPath,_T('\\'));
	if( pEnd == NULL )
		return false;
	pEnd[1]=0;
	
	//�����ļ���
	string strDirectPath = m_strRootPath;
	strDirectPath+= "down";
	CreateDirectory( strDirectPath.c_str() , NULL);

	//��ȡ�����ļ�
	string strFileName = m_strRootPath;
	strFileName += "downparam.ini";
	//
	if( !ReadConf( strFileName ) )
	{
		m_bFinish = true;
		m_bExitProc = true;
		return false;
	}
	//--
	if( CreateDirectory( m_strMapPath.c_str() , NULL) )
	{
		//return true;
	}
	m_MapData.Init( m_strMapPath.c_str() ); 

	//����������ط�Χ
	CMapBase::LonLat2MapPoint20( m_mapBound.TopLeft(), m_MapCenter20TopLeft );
	CMapBase::LonLat2MapPoint20( m_mapBound.BottomRight(), m_MapCenter20BottomRight );
	m_MBound20.left = m_MapCenter20TopLeft.lX;
	m_MBound20.right = m_MapCenter20BottomRight.lX;
	m_MBound20.top = m_MapCenter20TopLeft.lY;
	m_MBound20.bottom = m_MapCenter20BottomRight.lY;

	//�������ز���
	int nMinX,nMaxX,nMinY,nMaxY;
	//m_dMaxCount = 0;
	//m_dCount = 0;
	int i=0;
	for( i=m_MapData.m_iMinLevel;i<= m_MapData.m_iMaxLevel;i++)
	{
		if( i == 0 )
		{
			nMinX = 0;
			nMinY = 0;
			nMaxX = 0;
			nMaxY = 0;
		}
		else if( i < 8 )
		{
			nMinX = 0;
			nMinY = 0;
			nMaxX = (2<<i-1)-1;
			nMaxY = (2<<i-1)-1;
		}
		else
		{
			CMapBase::GetMapBlockBound( m_MBound20,i,nMinX,nMaxX,nMinY,nMaxY );
		}
		m_MapData.m_LevelParam[i].m_lMinX = nMinX;
		m_MapData.m_LevelParam[i].m_lMaxX = nMaxX;
		m_MapData.m_LevelParam[i].m_lMinY = nMinY;
		m_MapData.m_LevelParam[i].m_lMaxY = nMaxY;
		m_MapData.m_LevelParam[i].m_dCount = (nMaxX-nMinX+1);
		m_MapData.m_LevelParam[i].m_dCount *= (nMaxY-nMinY+1);
		m_MapData.m_LevelParam[i].m_dPos = 0;
	//	m_dMaxCount += m_LevelParam[i].m_dCount;
	}
	//��ʼ�����ز���
	m_MapData.m_iz = m_MapData.m_iMinLevel;
	m_MapData.m_ix = m_MapData.m_LevelParam[m_MapData.m_iz].m_lMinX;
	m_MapData.m_iy = m_MapData.m_LevelParam[m_MapData.m_iz].m_lMinY;

	//��ͼ�洢
	if( !m_MapData.OpenMapData() )
		return false;
	DownFirstData();
	
}
//��ȡ�����ļ�
bool CMapDown::ReadConf( string strFileName )
{
	string strMapName;
	int lMapType;
	int Minlevel;
	int Maxlevel;
	float x1;
	float x2;
	float y1;
	float y2;
	string strMapPath;

	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite ) )
	{
		return false;
	}
	char chData[1024];
	file.Read( chData, 1024 );
	file.Close();
	//���������ļ�
	//����
	char* pTemp = chData;
	char* pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	strMapName = pTemp;
	pTemp = pTemp1+1;
	//--����
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	lMapType = atoi( pTemp );
	pTemp = pTemp1+1;
	//--��С������
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	Minlevel = atoi( pTemp );
	pTemp = pTemp1+1;
	//--��������
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	Maxlevel = atoi( pTemp );
	pTemp = pTemp1+1;
	//--��С����
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	x1 = atof( pTemp );
	pTemp = pTemp1+1;
	//--��󾭶�
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	x2 = atof( pTemp );
	pTemp = pTemp1+1;
	//--��Сά��
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	y1 = atof( pTemp );
	pTemp = pTemp1+1;
	//--���ά��
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	y2 = atof( pTemp );
	pTemp = pTemp1+1;
	//--����·��
	pTemp1 = strstr( pTemp, "," );
	if( !pTemp1 )
		return false;
	pTemp1[0]=0;
	strMapPath = pTemp;
	pTemp = pTemp1+1;
	//--
	return SetParam( strMapName, lMapType, Minlevel, Maxlevel, x1,x2, y1,y2,strMapPath,false );
}
//���������ļ�
bool CMapDown::WriteConf( string strFileName )
{
	CVOSFile file;
	if( !file.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
	{
		::MessageBox( NULL,_T("�򿪴����ļ�ʧ�ܣ�ϵͳ�˳�!"),_T("������ʾ"),MB_OK );
		::exit(0);
		return false;
	}
	char chData[1024];
	sprintf( chData,"%s,%d,%d,%d,%f,%f,%f,%f,%s,",m_strMapName.c_str(),m_lMapType,m_MapData.m_iMinLevel,m_MapData.m_iMaxLevel,
		m_mapBound.left,m_mapBound.right,m_mapBound.bottom,m_mapBound.top,m_strMapPath.c_str());
	file.Write( chData, strlen( chData ) );
	//
	file.Close();
	return true;
}
//��ʼ��
bool CMapDown::SetParam( string strMapName, int lMapType, int Minlevel, int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath, bool bWrite )
{
	//����
	m_strMapName = strMapName;
	//���õ�ͼ����
	m_lMapType = lMapType;
	//���ò���
	if( Minlevel > Maxlevel )
		return false;
	if( Minlevel < 0 )
		Minlevel = 0;
	if( Minlevel >20 )
		Minlevel = 20;
	if( Maxlevel < 0 )
		Maxlevel = 0;
	if( Maxlevel >20 )
		Maxlevel = 20;
	m_MapData.m_iMinLevel = Minlevel;
	m_MapData.m_iMaxLevel = Maxlevel;
	
	//���ط�Χ
	m_mapBound.left = x1;
	m_mapBound.right = x2;
	m_mapBound.top = y2;
	m_mapBound.bottom = y1;
	//���ص�ͼĿ¼
	m_strMapPath = strMapPath;
	//���������ļ�
	if( bWrite )
	{
		//
		string strFileName = m_strRootPath;
		strFileName += "downparam.ini";
		//���������ļ�
		WriteConf( strFileName );
	}
	return true;
}
//��������
void CMapDown::Start( int nThreadNum )
{
	m_bFinish = false;
	m_bExitProc = false;

	//���������߳�
	m_MapData.StartSaveProc();
	DWORD dwThreadID = 0;
	for( int i=0;i<nThreadNum;i++ )
	{
		HANDLE h = ::CreateThread( NULL,0 ,&CMapDown::DownLoadProc,this,0,&dwThreadID );
		CloseHandle( h );
	}
}
//ֹͣ����
void CMapDown::Stop( )
{
	m_bExitProc = true;
	Sleep(1000);
}
//ɾ������
void CMapDown::Delete( )
{
	if( IsDown() )
		Stop();
	string strFileName = m_strRootPath;
	strFileName += "downparam.ini";
	CFile::Remove( strFileName.c_str() );
	//::MessageBox( NULL,_T("�򿪴����ļ�ʧ�ܣ�ϵͳ�˳�!"),_T("������ʾ"),MB_OK );
}
//�����߳�
unsigned long __stdcall CMapDown::DownLoadProc( void* pParameter )
{
	CMapDown* pMapDown = (CMapDown*)pParameter;
	return pMapDown->Run();
}
//ֹͣ����
int CMapDown::Run( )
{
	int i=0;
	int x,y,z;
	char strURL[256];
	while( !m_bExitProc )
	{
		if( WaitForSingleObject( m_hDownMutex,
		INFINITE ) == WAIT_OBJECT_0 )
		{
			while( GetNextPosition( x, y, z ) )
			{
				if( m_bFinish )
				{
					char strLog[256];
					sprintf( strLog, " DOWN FINISH OK! %d_%d_%d!!!", m_MapData.m_iz, m_MapData.m_iy, m_MapData.m_ix );
					g_pView->AddLog( strLog );
					return 1;
				}
			}
			ReleaseMutex( m_hDownMutex );
			if( z==4 && x==12&&y==5)
			{
				z=4;
			}
			CMapBase::GetMapUrl( x, y, z,m_lMapType,strURL,256);
			DownLoad( strURL, x, y, z );
		}
		Sleep(100);
	}
	return 1;
}
//�������λ��
bool CMapDown::GetNextPosition( int& x, int& y, int& z )
{
	return m_MapData.GetNextPosition( x, y , z );
}

//�����ļ�
bool CMapDown::DownLoad( const char* strURL, int x, int y, int z )
{
	char strLog[256];
	char chFileName[256];
	//int iTimes = 0;
	//if( GetDownLoadPath( strURL, strFileName ) )
	{
		//�ڴ�
		MemoryStruct chunk;
		chunk.memory = NULL;
	//	int errcode= InterNet_httpget(strURL,&chunk);
		int errcode= curl_httpget(strURL,&chunk,NULL);
		if( chunk.size == 0 )
		{
			chunk.memory = NULL;
			sprintf( strLog, " Down %d_%d_%d ʧ��! ", z, y, x );
			g_pView->AddLog( strLog );
			return false;
		}
		if(!errcode)
		{
			if ( strstr( chunk.memory,"html" ) ){
				if(chunk.memory)
				{
					free(chunk.memory);
					chunk.memory = NULL;
					sprintf( strLog, " Down %d_%d_%d ������! ", z, y, x );
					g_pView->AddLog( strLog );
					return true;
				}
				//sprintf(m_pLog,"\n����ҳ��,�����ڸõ�ַ������ʧ��\n");
//				sprintf(m_pLog,"����z=%d y=%d x=%d ʧ�ܣ��������޴��ļ� \n",z,y,x);
//				WriteLog((char*)m_pLog);
				//WriteLog(strURL.c_str());
///				g_pGmapdownDlg->AddLog( m_pLog );
//				WriteLog(strFileName.c_str());
	//			CMapBase::GetMapUrlBk(x,y,z,strURL,256);
	//			errcode= InterNet_httpget(strURL,&chunk);
				//	errcode= curl_httpget(strURL,&chunk,NULL);
				//if(errcode)
				//{
					//printf("����z=%d y=%d x=%d ʧ�ܣ��������޴��ļ� \n",z,y,x);
					//WriteLog(m_pLog);
					//return true;
				//}
			}
			MapBlockData* pMapData = new MapBlockData();
			pMapData->sLevel = z;
			pMapData->lNumX = x;
			pMapData->lNumY = y;
			pMapData->pData = (char*)malloc( chunk.size );
			memcpy( pMapData->pData, chunk.memory, chunk.size );
			pMapData->lDataLenth = chunk.size;
			//this->m_MapData.AddMapData( pMapData );
			m_MapData.m_LevelParam[pMapData->sLevel].m_dPos++;
			CVOSFile fileWrite; 
			string strFileName = m_strMapPath;
			if( z < 10 )
				sprintf( chFileName,"\\L0%d",z);
			else
				sprintf( chFileName,"\\L%d",z);
			strFileName += chFileName;
			CreateDirectory( strFileName.c_str() , NULL);

			if( y < 10 )
				sprintf( chFileName,"\\R0%x",y);
			else
				sprintf( chFileName,"\\R%x",y);
			strFileName += chFileName;
			CreateDirectory( strFileName.c_str() , NULL);
			
			sprintf( chFileName,"\\C%x.png",x);
			strFileName += chFileName;
			if( fileWrite.Open( strFileName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
			{
				fileWrite.Write( chunk.memory, chunk.size );
				fileWrite.Close();
				//AfxMessageBox("�������");
			}
			else
			{
				//AfxMessageBox("�����ļ�"+strWriteName+"�򿪳���."); 
			}
			if(chunk.memory)
			{
				free(chunk.memory);
				chunk.memory = NULL;
			}
			//sprintf(m_pLog,"z=%d y=%d x=%d ok \n",z,y,x);
			//printf(m_pLog);
			//WriteLog(m_pLog);
			sprintf( strLog, " Down %d_%d_%d ok! ", z, y, x );
			g_pView->AddLog( strLog );
			return true;
		}
		else
		{
			if(chunk.memory)
				free(chunk.memory);
			//if( errcode == 6 )
			sprintf( strLog, " Down %d_%d_%d error! ", z, y, x );
			g_pView->AddLog( strLog );
			return false;
		}
	}

}

//���
bool CMapDown::AddMapData( string strPath )
{
	m_MapData.m_strAddMapPath = strPath;
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapData::AddMapFileProc,&m_MapData,0,&dwThreadID );
	CloseHandle( h );
	return true;
}
//���
bool CMapDown::CreateDBIndex()
{
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapData::CreateDBProc,&m_MapData,0,&dwThreadID );
	CloseHandle( h );
	return true;
}
bool CMapDown::CheckMapData()
{
	DWORD dwThreadID = 0;
	HANDLE h = ::CreateThread( NULL,0 ,&CMapData::CheckMapDataProc,&m_MapData,0,&dwThreadID );
	CloseHandle( h );
	return true;
}
//���ص�һ������
bool CMapDown::DownFirstData()
{
	//��������Ƿ�����
	if( this->m_MapData.GetMapData( m_MapData.m_iz, m_MapData.m_ix, m_MapData.m_iy ) )
	{
		m_MapData.m_LevelParam[m_MapData.m_iz].m_dPos++;
		return true;
	}
	else
	{
		char strURL[256];
		CMapBase::GetMapUrl( m_MapData.m_ix, m_MapData.m_iy, m_MapData.m_iz,m_lMapType,strURL,256);
		return DownLoad( strURL, m_MapData.m_ix, m_MapData.m_iy, m_MapData.m_iz );
	}
}