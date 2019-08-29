// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MAP_DOWN_TASK_)
#define _MAP_DOWN_TASK_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "../VOSBase/VOSFile.h"
#include "../VOSBase/VOSURL.h"
#include "../VOSBase/MD5.h"
#include "../MapActive/MapActive.h"
#include "MapData.h"
class CMapDownParam
{
public:
	long lMapType;
	long Minlevel;
	long Maxlevel;
	long lLevel[20];
	float x1;
	float x2;
	float y1;
	float y2;
	char strMapPath[256];
	char strMapName[64];
	bool bFinish;
	void GetString( string& str )
	{
		char chTemp[512]={0};
		sprintf( chTemp, "%s_%d_%d_%f_%f_%f_%f_%s",strMapName,Minlevel,Maxlevel,x1,x2,y1,y2,strMapPath );
		str = chTemp;
	}
};
class CLevelParam
{
public:
	long	m_lMinX ;
	long	m_lMaxX ;
	long	m_lMinY ;
	long	m_lMaxY ;
	double  m_dCount;	//��ǰ����������Ҫ���صĵ�ͼ��������
	double	m_dPos;		//��ǰ���������Ѿ����صĵ�ͼ����
	long	m_lx;		//��ǰ���������Ѿ����ص�Xλ��
	long	m_ly;		//��ǰ���������Ѿ����ص�Yλ��
};

class CMapDownTask  
{
public:
	CMapDownTask();
	virtual ~CMapDownTask();

	//���һ����������
	bool CreateTask( int lMapType, int Minlevel, int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath,string strMapName );

	//ɾ������
	bool DeleteTask( );
	
	//�õ�������Ϣ
	bool GetTask( int& lMapType, int& Minlevel, int& Maxlevel, float& x1,float& x2, float& y1,float& y2,string& strMapPath,string& strMapName );
	bool GetTaskParam( int nID, CMapDownParam& param );
	//��������
	void Start( int nThreadNum = 5 );

	//ֹͣ����
	void Stop( );
	//��ͣ
	void Pause();

	//�õ�����·��
	bool GetDownLoadPath( string& strURL, int &x,int &y,int &z );

	//�õ���ͼ����·��
	void GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType  );
	//�õ��������ص�λ��
	void GetDownPos(int &x,int &y,int &z);
	//�õ������������
	void GetMapDownParam(CMapDownParam& param);
	//�����߳�
	static unsigned long __stdcall DownLoadProc( void* pParameter );

	//�õ����صĵ�ͼ·��
	void GetMapPath( string& strMapPath );

	//����Ҫ���ص��ܵ��ļ�����
	double GetDownLoadMaxCount();
	double GetDownLoadCount();
	//������ʾ����
	void SetViewDC( HDC hdc );

	//�������
	bool CheckData();
private:

	//����
	void DownLoad();
	
	//д��־
	void WriteLog(const char* pLog );
	//��ȡ�ȸ賣���ͼ
	bool GetMap(  int x, int y, int z, int iMapType  );

	//��õ�ǰbound
	void GetLevelBound( int z );

	//����������·��
	void CreateLevelDir(int iLevel );

	//����Ѿ����صĵ�ͼ������Ϣ
	bool CheckedMapData( char* strPath );

	//����ϴ�����λ��
	//bool GetDownPosition( int& x, int& y, int& z );

	//�������λ��
	bool GetNextDownPosition( int& x, int& y, int& z );

	//��������λ��
	//void SaveDownPosition( int x, int y, int z );

	//�����ļ�
	bool DownLoad( string& strURL, int x, int y, int z );
	//�Ƿ�ֹͣ����
	bool IsStop();
	//��������λ��
	void DrawDownPos();
private:
	//��ǰ�ļ�����
	int m_ix;
	int m_iy;
	int m_iz;

	//��ͼ����
	//en_MapType	    m_enMapType;
	//ת����ķ�Χ
	int m_iMinX ;
	int m_iMaxX ;
	int m_iMinY ;
	int m_iMaxY ;

	//�����߷�Χ
	int m_iMinLevel;
	int m_iMaxLevel;
	//��γ�ȷ�Χ
	MapBount m_mapBound;
	MBound	 m_MBound20;
	MPoint	 m_MapCenter20TopLeft;
	MPoint	 m_MapCenter20BottomRight;
	//��ͼ��·��
	string	m_strMapPath;
	string	m_strMapTaskPath;
	string	m_strMapName;
	//д��־
	char     m_pLog[256];
	CVOSFile m_fileLog;
	bool     m_bLog;
	//��ͼ����
	long     m_lMapType;
	//�̻߳�����
	HANDLE	m_hDownLoadMutex;				// �̻߳�����
	bool	m_bExitProc;
	int		m_nState;						//״̬
	CLevelParam m_LevelParam[20];			//ÿһ����Ҫ�����������Ͳ���
	double		m_dMaxCount;				//�ܵ���������
	double		m_dCount;					//�ܵ���������
	CMapData	m_MapData;
public:
	bool		m_bFinish;					//�����Ƿ����
};

#endif // !defined(_MAP_DOWN_TASK_)
