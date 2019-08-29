// MapData.h: interface for the CMapData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDATA_H__6B905513_11F3_4FB0_ACFC_757E06127C36__INCLUDED_)
#define AFX_MAPDATA_H__6B905513_11F3_4FB0_ACFC_757E06127C36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "../MapBase/FourTree.h"
#include "../MapBase/MapFourTree.h"
#include "../MapBase/SqliteDB.h"

struct tLevelParam
{
	long	m_lMinX ;
	long	m_lMaxX ;
	long	m_lMinY ;
	long	m_lMaxY ;
	double  m_dCount;	//��ǰ����������Ҫ���صĵ�ͼ��������
	double	m_dPos;		//��ǰ���������Ѿ����صĵ�ͼ����
	long	m_lx;		//��ǰ���������Ѿ����ص�Xλ��
	long	m_ly;		//��ǰ���������Ѿ����ص�Yλ��
	bool	m_bDownLoad;	//�Ƿ�����
};

class CMapData  
{
public:
	CMapData();
	virtual ~CMapData();
	//��ʼ��
	bool Init( const char* strMapPath );
	//�ͷ��ڴ�
	void Realse();

	//�����غõ�����
	bool OpenMapData( const char* strMapPath );

	//�����غõ�����
	bool OpenMapData();

	//�������ݿ�����
	bool CreateDBIndex();

	//�����Ĳ�������
	bool CreateMapFourTree();

	//�ر����غõ�����
	void CloseMapData();

	//�������ݱ����߳�
	void StartSaveProc();
	//���
	bool AddMapFile();

	//��ѯ�����Ƿ����
	MapBlockHead* GetMapData( short sLevel, long lNumX, long lNumY );

public:
	//�������ݱ���Ⱥ���
	//���
	bool AddMapData( MapBlockData* pData );
	

	//��ͼ������������
	void SaveMap4Tree();

	//�����������,��������
	int  WriteMapData( );

	//���ݱ����߳�
	static unsigned long __stdcall MapDataProc( void* pParameter );

	//ִ���߳�
	int Run();

	//��������߳�
	static unsigned long __stdcall AddMapFileProc( void* pParameter );

	//��������߳�
	static unsigned long __stdcall CreateDBProc( void* pParameter );

	//��������߳�
	static unsigned long __stdcall CheckMapDataProc( void* pParameter );
	//
	bool GetNextPosition( int& x, int& y, int& z );
	//�������
	bool CheckMapData();
private:

	//���µĵ�ͼ�����ļ�
	bool OpenMapDataFile( int iFileID );
	//�����µĵ�ͼ�����ļ�
	bool CreateMapDataFile( int iFileID );
	
public:

	//��ǰ�ļ�����
	int m_ix;
	int m_iy;
	int m_iz;
	
	//�����߷�Χ
	int			m_iMinLevel;
	int			m_iMaxLevel;

	tLevelParam					m_LevelParam[20];
	
	string						 m_strMapPath;
	en_MapType					 m_enMapType;
//	CVOSFile					 m_FileIndex;
	CVOSFile					 m_FileData;

	int							 m_iMapFileID;
	unsigned long 				 m_iMapOffSet;

	//
	list<MapBlockData*>			 m_arrMapData;				//�ȴ����������б�
	HANDLE						 m_hMapDataMutex;			//�̻߳�����

	bool						 m_bExitProc;				//�Ƿ��߳��˳�
	char						 m_strLog[256];
	CTime						 m_TimeLog;
	
	//�Ѿ��������ݱ�
	//CFourTree					 m_FourTree;				//��ͼ�Ĳ�����	
	CSqliteDB					 m_SqliteDB;				//���ݿ�����

	string						 m_strAddMapPath;
};

#endif // !defined(AFX_MAPDATA_H__6B905513_11F3_4FB0_ACFC_757E06127C36__INCLUDED_)
