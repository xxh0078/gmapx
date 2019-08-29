// MapDown.cpp: implementation of the CMapDownTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapDownTask.h"
//#include "MapBase.h"
#pragma comment(lib,"wininet.lib")
#include   <wininet.h> 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int InterNet_httpget(string strURL,struct MemoryStruct *chunk )
{
	HINTERNET internet=InternetOpen("HTTP Downloader", INTERNET_OPEN_TYPE_PRECONFIG, 
        NULL, NULL, NULL);
    if(!internet)
	{
        throw "InternetOpen error!";
		return 1 ;
	}
    //��һ��http url��ַ
    HINTERNET file_handle = InternetOpenUrl(internet, strURL.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if(!file_handle)
	{
        //throw "InternetOpenUrl error! - Maybe you should add Http:// or Ftp://";
		return 2 ;
	}
	chunk->size = 0;
	chunk->memory = (char*)malloc( 1024*1023 );
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
	//�ر�����
	InternetCloseHandle(internet);
	if( !chunk->memory )
		return 10;
	return 0;
}
CMapDownTask::CMapDownTask()
{
	m_ix = 0;
	m_iy = 0;
	m_iz = 4;
	m_bLog = false;
	m_nState = 0;
	m_dMaxCount = 0;
	m_dCount = 0;
}

CMapDownTask::~CMapDownTask()
{
	m_ix = 0;
	m_iy = 0;
	m_iz = 4;
	m_bLog = false;
}
//��������
void CMapDownTask::Start( int nThreadNum )
{
	if( m_nState == 2 )
	{
		m_nState = 1;
		return;
	}
	m_nState = 1;
	m_bExitProc = false;
	DWORD dwThreadID = 0;
	for( int i=0;i<nThreadNum;i++ )
	{
		HANDLE h = ::CreateThread( NULL,0 ,&CMapDownTask::DownLoadProc,this,0,&dwThreadID );
		CloseHandle( h );
	}
}

//ֹͣ����
void CMapDownTask::Stop( )
{
	m_bExitProc  = true;
	m_nState = 3;
}
//��ͣ
void CMapDownTask::Pause()
{
	m_nState = 2;
}
//���һ����������
bool CMapDownTask::CreateTask( int lMapType,int Minlevel,int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath,string strMapName )
{

	char strLog[256]="����Ѿ����صĵ�ͼ���ݣ�";
	sprintf( strLog,"��������:%s%s,type=%d,level(%d-%d),x(%f-%f),y(%f-%f)",strMapPath.c_str(),strMapName.c_str(),
		lMapType,Minlevel,Maxlevel,x1,x2,y1,y2 );
//	g_pGmapdownDlg->AddLog( strLog );

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
	m_iMinLevel = Minlevel;
	m_iMaxLevel = Maxlevel;

	//���ص�ͼĿ¼
	m_strMapPath = strMapPath;
	m_strMapName = strMapName;

	m_strMapTaskPath = m_strMapPath;
	//m_strMapTaskPath += "\\";
	m_strMapTaskPath += strMapName;
	
	if( CreateDirectory( m_strMapTaskPath.c_str() , NULL) )
	{
		//return true;
	}

	//��ͼ�洢
	m_MapData.Init( m_strMapTaskPath.c_str() );

	//���ط�Χ
	m_mapBound.left = x1;
	m_mapBound.right = x2;
	m_mapBound.top = y2;
	m_mapBound.bottom = y1;

	CMapBase::LonLat2MapPoint20( m_mapBound.TopLeft(), m_MapCenter20TopLeft );
	CMapBase::LonLat2MapPoint20( m_mapBound.BottomRight(), m_MapCenter20BottomRight );
	m_MBound20.left = m_MapCenter20TopLeft.lX;
	m_MBound20.right = m_MapCenter20BottomRight.lX;
	m_MBound20.top = m_MapCenter20TopLeft.lY;
	m_MBound20.bottom = m_MapCenter20BottomRight.lY;

	//�������ز���
	int nMinX,nMaxX,nMinY,nMaxY;
	m_dMaxCount = 0;
	m_dCount = 0;
	int i=0;
	for( i=m_iMinLevel;i<= m_iMaxLevel;i++)
	{
		CMapBase::GetMapBlockBound( m_MBound20,i,nMinX,nMaxX,nMinY,nMaxY );
		m_LevelParam[i].m_lMinX = nMinX;
		m_LevelParam[i].m_lMaxX = nMaxX;
		m_LevelParam[i].m_lMinY = nMinY;
		m_LevelParam[i].m_lMaxY = nMaxY;
		m_LevelParam[i].m_dCount = (nMaxX-nMinX+1);
		m_LevelParam[i].m_dCount *= (nMaxY-nMinY+1);
		m_dMaxCount += m_LevelParam[i].m_dCount;
	}
	//-----------
	//����ʱ��������ؼ�¼
	//this->GetDownPosition( this->m_ix,this->m_iy,this->m_iz );
//	m_MapData.GetMapPos( m_iz, m_ix, m_iy );
	//m_iz = m_iMinLevel;
//	GetLevelBound( m_iz );

	//����zĿ¼���ݸ���
	for( i=m_iMinLevel;i< m_iz;i++)
	{
		m_dCount += m_LevelParam[i].m_dCount;
	}
	//����y��Ŀ¼���ݸ���
	if( m_iy - m_LevelParam[m_iz].m_lMinY > 0 )
	{
		m_dCount = (m_iy - m_LevelParam[m_iz].m_lMinY)*(m_LevelParam[m_iz].m_lMaxX-m_LevelParam[m_iz].m_lMinX);
	}
//	for( i=m_LevelParam[m_iz].m_lMinY;i< m_iy;i++)
//	{
//		m_dCount += (m_iy - m_LevelParam[m_iz].m_lMinY)*(m_LevelParam[m_iz].m_lMaxX-m_LevelParam[m_iz].m_lMinX);
//	}
	//---
	double dTemp1 = m_ix-m_LevelParam[m_iz].m_lMinX;
	if( dTemp1 < 0 )
	{
		dTemp1 = 0;
	}
	m_dCount += dTemp1;
	//�����������ļ���
	CreateLevelDir(m_iz);

	//����������
	m_hDownLoadMutex = CreateMutex( NULL,false,NULL );

	this->m_bFinish = false;
	return true;
}
//ɾ������
bool CMapDownTask::DeleteTask( )
{
	this->Stop();
	/*Sleep(1000);
	string strTemp = m_strMapTaskPath;
	strTemp += "\\pos.dat";
	CVOSFile::Remove( strTemp.c_str() );*/
	return false;
}
//�õ�������Ϣ
bool CMapDownTask::GetTask( int& lMapType,int& Minlevel,int& Maxlevel, float& x1,float& x2, float& y1,float& y2,string& strMapPath,string& strMapName )
{
	lMapType = m_lMapType;
	Minlevel = m_iMinLevel;
	Maxlevel = m_iMaxLevel;
	x1 = m_mapBound.left;
	x2 = m_mapBound.right;
	y2 = m_mapBound.top;
	y1 = m_mapBound.bottom;
	strMapPath = m_strMapPath;
	strMapName = m_strMapName;
	return true;
}
//�õ�����·��
bool CMapDownTask::GetDownLoadPath( string& strURL, int &x,int &y,int &z )
{
	bool nRet = false;
	if( WaitForSingleObject( m_hDownLoadMutex,
		INFINITE ) == WAIT_OBJECT_0 )
	{
		if( GetNextDownPosition( m_ix,m_iy,m_iz ) )
		{
			x = m_ix;
			y = m_iy;
			z = m_iz;
			//GetMapDataPath( m_ix,m_iy,m_iz,strFileName,m_lMapType );
			char strURL1[256];
			CMapBase::GetMapUrl( m_ix,m_iy,m_iz,m_lMapType,strURL1,256);
			strURL = strURL1;
			nRet = true;
		}
		ReleaseMutex( m_hDownLoadMutex );
	}		
	return nRet;
}
//�õ���ͼ����·��
void CMapDownTask::GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType  )
{
	strMapFilePath = m_strMapTaskPath;
	//CMapBase::GetMapTypePath( iMapType, strMapFilePath );
	char temp[33]={0};
	//�����������ļ�Ŀ¼
	strMapFilePath += _T("\\level");
	sprintf( temp,_T("%d\\"),z );
	//strcat( pPath, temp );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);
	//-----y�����ļ���
	memset( temp,0,33);
	sprintf( temp,_T("%d\\"),y );
	strMapFilePath += temp;
	CreateDirectory( strMapFilePath.c_str(),NULL);

	memset( temp,0,33);
	sprintf( temp,_T("%d.png"),x );
	strMapFilePath += temp;

}
//����������·��
void CMapDownTask::CreateLevelDir(int iLevel )
{
	/*
	//������·��
	char strLevelPath[256] ={0}; 
	char strTemp[20]={0};
	sprintf(strTemp,"level%d\\",iLevel);
	strcpy( strLevelPath, m_strRootPath );
	strcat( strLevelPath, strTemp );
	CreateDirectory(strLevelPath, NULL);*/
}
//�õ��������ص�λ��
void CMapDownTask::GetDownPos(int &x,int &y,int &z)
{
	x = this->m_ix;
	z = this->m_iz;
	y = this->m_iy;
}
//�õ������������
void CMapDownTask::GetMapDownParam(CMapDownParam& param)
{
	param.lMapType = this->m_lMapType;
	param.Maxlevel = this->m_iMaxLevel;
	param.Minlevel = this->m_iMinLevel;
	param.x1 = m_mapBound.left;
	param.x2 = m_mapBound.right;
	param.y1 = m_mapBound.bottom;
	param.y2 = m_mapBound.top;
	param.bFinish = m_bFinish;
	memset( param.strMapPath, 0 ,  256 );
	memcpy( param.strMapPath, this->m_strMapPath.c_str() ,  m_strMapPath.size() );
	memset( param.strMapName, 0 ,  64 );
	memcpy( param.strMapName, m_strMapName.c_str() ,  m_strMapName.size() );

}
//��ȡ�ȸ賣���ͼ
bool CMapDownTask::GetMap(  int x, int y, int z, int iMapType  )
{
	//	vchar strSentence[256], strFileDirect[256];
	char strURL[256];
	int iServerNum = rand()%4;//����[0,m)�������  
//	sprintf(strFileDirect,_T("gmapdata/level%d",z);

	string strWriteName ;//= this->m_strRootPath;
	CMapBase::GetMapDataPath(x,y,z,strWriteName,m_lMapType );
	//��ȡ��ͼurl
	CMapBase::GetMapUrl(x,y,z,iMapType,strURL,256);
	//�ڴ�
	MemoryStruct chunk;
	chunk.memory = NULL;
//	int errcode= InterNet_httpget(strURL,&chunk);
	int errcode= curl_httpget(strURL,&chunk,NULL);
	if(!errcode)
	{
		if ( strstr( chunk.memory,"html" ) ){
			if(chunk.memory)
			{
				free(chunk.memory);
			}
//			CMapBase::GetMapUrlBk(x,y,z,strURL,256);
//			errcode= InterNet_httpget(strURL,&chunk);
			//	errcode= curl_httpget(strURL,&chunk,NULL);
			//if(errcode)
			//{
				printf("����z=%d y=%d x=%d ʧ�ܣ��������޴��ļ� \n",z,y,x);
				WriteLog(m_pLog);
//				g_pGmapdownDlg->AddLog( m_pLog );
				return true;
			//}
		}
		MapBlockData* pMapData = new MapBlockData();
		pMapData->sLevel = z;
		pMapData->lNumX = x;
		pMapData->lNumY = y;
		pMapData->pData = (char*)malloc( chunk.size );
		memcpy( pMapData->pData, chunk.memory, chunk.size );
		pMapData->lDataLenth = chunk.size;
		this->m_MapData.AddMapData( pMapData );
		/*CVOSFile fileWrite; 
		if( fileWrite.Open( strWriteName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
		{
			fileWrite.Write( chunk.memory, chunk.size );
			fileWrite.Close();
			//AfxMessageBox("�������");
		}
		else
		{
			//AfxMessageBox("�����ļ�"+strWriteName+"�򿪳���."); 
		}*/
		if(chunk.memory)
			free(chunk.memory);
		sprintf(m_pLog,"z=%d y=%d x=%d ok \n",z,y,x);
		printf(m_pLog);
		WriteLog(m_pLog);
		return true;
	}
	else
	{
		if(chunk.memory)
			free(chunk.memory);
		sprintf(m_pLog,"�����޷�����,�ȴ�����!\n");
		printf(m_pLog);
		WriteLog(m_pLog);
		return false;
	}
	
}
//�õ���ǰ�����ߵķ�Χ
void CMapDownTask::GetLevelBound( int z )
{	
	CMapBase::GetMapBlockBound( m_MBound20,z, m_iMinX,m_iMaxX,m_iMinY,m_iMaxY);
	/*
	m_iMinX = 0;
	m_iMaxX = 2<<(z-1);
	m_iMinY = 0;
	m_iMaxY = 2<<(z-1);
	if ( z > 0 )
	{
		//���㾫��γ�ȷ�Χ�ڵ���������
		//MapPoint gplt = lonLat2Mercator(m_mapBound.TopLeft(),itemp );
		//MapPoint gprb = lonLat2Mercator(m_mapBound.BottomRight(),itemp );

		MPoint   mptLT,mptBR;
		CMapBase::GetMapPoint( z, m_MapCenter20TopLeft, mptLT );
		CMapBase::GetMapPoint( z, m_MapCenter20BottomRight, mptBR );

		m_iMinX = max( mptLT.lX/256-1,0);			
		//max(( itemp + gplt.x )/256-1,0);
		m_iMaxX = min( mptBR.lX/256+1,2<<(z-1));
		m_iMinY = max( mptLT.lY/256-1,0);			
		//max((itemp - gplt.y)/256+1,0);
		m_iMaxY = min( mptBR.lY/256+1, 2<<(z-1));
	}
	else
	{
		if( z == 0 )
		{
			m_iMaxX = 0;
			m_iMaxY = 0;
		}
		if( z == 1 )
		{
			m_iMaxX = 1;
			m_iMaxY = 1;
		}
	}*/
}
void CMapDownTask::WriteLog( const char* pLog )
{
	if( m_bLog )
	{
		//m_fileLog.Write( (char*)pLog,strlen(pLog));
		//m_fileLog.Flush();
		string strFileNameLog = m_strMapTaskPath;
		strFileNameLog += "\\down.log";
		if( m_fileLog.Open(strFileNameLog.c_str(),fomReadWrite ) )
		{
			m_fileLog.SeekToEnd();
			m_fileLog.Write((char*)pLog,strlen(pLog));
			m_fileLog.Close();
			m_bLog = true;
		}
	}
	else
	{
		string strFileNameLog = m_strMapTaskPath;
		strFileNameLog += "\\down.log";
		if( CVOSFile::IsExit( strFileNameLog.c_str() ) )
		{
			if( m_fileLog.Open(strFileNameLog.c_str(),fomReadWrite ) )
			{
				m_fileLog.SeekToEnd();
				m_fileLog.Write((char*)pLog,strlen(pLog));
				m_fileLog.Close();
				m_bLog = true;
			}
		}
		else
		{
			if( m_fileLog.Open(strFileNameLog.c_str(),fomReadWrite|fomCreate) )
			{
				m_fileLog.Write((char*)pLog,strlen(pLog));
				m_fileLog.Close();
				m_bLog = true;
			}	
		}
	}
	
}
//�������λ��
bool CMapDownTask::GetNextDownPosition( int& x, int& y, int& z )
{
	m_ix++;
	if ( m_ix < m_iMinX )
	{
		m_ix = m_iMinX;
		//x = m_ix;
	}
	if ( m_ix >= m_iMaxX )
	{
		m_iy++;
		m_ix = m_iMinX;
	}
	if ( m_iy < m_iMinY )
	{
		m_iy = m_iMinY;
	}
	if ( m_iy >= m_iMaxY )
	{
		m_iz++;
		if( m_iz < m_iMinLevel )
			m_iz = m_iMinLevel;
		GetLevelBound(m_iz);
		m_ix = m_iMinX;
		m_iy = m_iMinY;
		if( m_iz > m_iMaxLevel )
		{
			Stop();
			m_bFinish = true;
			return false;
		}
		CreateLevelDir(m_iz);
	}
	x = m_ix;
	y = m_iy;
	z = m_iz;
	
	if( z < m_iMinLevel || z > m_iMaxLevel )
		return false;
	else
	{
		m_dCount++;
		return true;
	}
}
//
void CMapDownTask::DownLoad()
{
	int ix = m_ix;
	int iy = m_iy;
	int iz = m_iz;
	GetMap(ix,iy,iz,m_lMapType);
	GetNextDownPosition( ix,iy,iz);
	sprintf( m_pLog,"download:z=%d,y=%d,x=%d",iz,iy,ix);
//	g_pGmapdownDlg->AddLog( m_pLog );
	//g_pGmapdownDlg->UpDateLog( m_pLog );
//	while( !m_bExitProc )
	{
		//GetNextDownPosition();
		if( GetMap(ix,iy,iz,m_lMapType) )
		{
			GetNextDownPosition( ix,iy,iz);
			if ( iz > m_iMaxLevel ) {
				return;
			}
		}
	}
}
//�õ����صĵ�ͼ·��
void CMapDownTask::GetMapPath( string& strMapPath )
{
	strMapPath = this->m_strMapPath;
	strMapPath += this->m_strMapName;
	strMapPath += _T("\\level%z\\%y\\%x.png");
}

//��������λ��
void CMapDownTask::DrawDownPos()
{

}
//����Ҫ���ص��ܵ��ļ�����
double CMapDownTask::GetDownLoadMaxCount()
{
	return this->m_dMaxCount;
}
double CMapDownTask::GetDownLoadCount()
{
	return m_dCount;
}
//�Ƿ�ֹͣ����
bool CMapDownTask::IsStop()
{
	return m_bExitProc;
}
//�����ļ�
bool CMapDownTask::DownLoad( string& strURL, int x, int y, int z )
{
	//int iTimes = 0;
	//if( GetDownLoadPath( strURL, strFileName ) )
	{
		//�ڴ�
		MemoryStruct chunk;
		chunk.memory = NULL;
	//	int errcode= InterNet_httpget(strURL,&chunk);
		int errcode= curl_httpget(strURL.c_str(),&chunk,NULL);
		if( chunk.size == 0 )
		{
			chunk.memory = NULL;
			return false;
		}
		if(!errcode)
		{
			if ( strstr( chunk.memory,"html" ) ){
				if(chunk.memory)
				{
					free(chunk.memory);
					chunk.memory = NULL;
					return true;
				}
				//sprintf(m_pLog,"\n����ҳ��,�����ڸõ�ַ������ʧ��\n");
				sprintf(m_pLog,"����z=%d y=%d x=%d ʧ�ܣ��������޴��ļ� \n",z,y,x);
				WriteLog((char*)m_pLog);
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
			this->m_MapData.AddMapData( pMapData );
			/*CVOSFile fileWrite; 
			if( fileWrite.Open( strFileName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
			{
				fileWrite.Write( chunk.memory, chunk.size );
				fileWrite.Close();
				//AfxMessageBox("�������");
			}
			else
			{
				//AfxMessageBox("�����ļ�"+strWriteName+"�򿪳���."); 
			}*/
			if(chunk.memory)
			{
				free(chunk.memory);
				chunk.memory = NULL;
			}
			//sprintf(m_pLog,"z=%d y=%d x=%d ok \n",z,y,x);
			//printf(m_pLog);
			//WriteLog(m_pLog);
			return true;
		}
		else
		{
			if(chunk.memory)
				free(chunk.memory);
			//if( errcode == 6 )
				return false;
		}
	}

}
//���������߳�
unsigned long __stdcall CMapDownTask::DownLoadProc( void* pParameter )
{
	CMapDownTask* pMapDownTask = (CMapDownTask*)pParameter;
	//GetNextDownPosition( pDownLoad->m_ix, pDownLoad->m_iy,pDownLoad->m_iz)
	//pDownLoad->GetNextDownPosition( ix,iy,iz);
	string strURL,strFileName;
	int i=0;
	int x,y,z;
	while( !pMapDownTask->m_bExitProc )
	{
		if( pMapDownTask->m_nState == 2 )
		{
			Sleep(100);
			continue;
		}
		//
		if( pMapDownTask->GetDownLoadPath( strURL, x,y,z ) )
		{
			i=0;
			while( !pMapDownTask->m_bExitProc )
			{
				//sprintf( pMapDownTask->m_pLog,"download:z=%d,y=%d,x=%d",z,y,x);
				//g_pGmapdownDlg->UpDateLog( pMapDownTask->m_pLog );
				if( pMapDownTask->DownLoad(strURL,x,y,z) )
				{
					break;
				}
				else
				{
					i++;
					Sleep(i*100);
					if( i >= 30 )
						i=30;
					if( i == 29 )
					{
						sprintf(pMapDownTask->m_pLog,"\r\n�õ�ַ�������ʧ�ܣ���������!\r\n");
						//g_pGmapdownDlg->AddLog( pMapDownTask->m_pLog );
						//g_pGmapdownDlg->AddLog( strURL.c_str() );
						//g_pGmapdownDlg->AddLog( strFileName.c_str() );
						pMapDownTask->WriteLog(pMapDownTask->m_pLog);
						pMapDownTask->WriteLog(strURL.c_str());
						pMapDownTask->WriteLog(strFileName.c_str());
						break;
					}
				}
			}
			/*if( !pMapDownTask->DownLoad(strURL,strFileName) )
			{
				Sleep(500);
				if( !pMapDownTask->DownLoad(strURL,strFileName) )
				{
					sprintf(pMapDownTask->m_pLog,"\r\n�õ�ַ����ʧ��!\r\n");
					pMapDownTask->WriteLog(pMapDownTask->m_pLog);
					pMapDownTask->WriteLog(strURL.c_str());
					pMapDownTask->WriteLog(strFileName.c_str());
				}
			}*/
		}
		Sleep(100);
		//GetNextDownPosition();
		/*if( pDownLoad->GetMap(ix,iy,iz,pDownLoad->m_lMapType) )
		{
			pDownLoad->GetNextDownPosition( ix,iy,iz);
			if ( iz > 20 ) {
				return 1;
			}
		}*/
	}
	return 1;
}