#pragma once
#include "MapBlockUnit.h"
#include "..\VOSBase\VOSDefine.h"
#include "..\MapBase\FourTree.h"
//#include "..\MapBase\MapFourTree.h"
#include "..\MapBase\SqliteDB.h"
#include "MapDataDown.h"
class CMapDisp;
//--
class CMapData
{
public:
	CMapData(void);
	~CMapData(void);
	//��ʼ��
	void Init( CMapDisp* pMapDisp );
	//�ͷ��ڴ�
	void Realse();

	//���õ�ͼ·��
	bool SetMapPath( string strMapPath, en_MapType enMapType );

	//�õ���ͼ���ݿ�
	CMapBlockUnit* GetMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID );

	//��ӵ�ͼ���ݿ�
	bool AddMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID,char* pData, int len );

private:
	bool SaveMapData( short sLevel, long lNumX, long lNumY, char* pData, int len );
	//�����µĵ�ͼ�����ļ�
	int OpenMapDataFile( int iFileID );
private:
	string						 m_strMapPath;
	en_MapType					 m_enMapType;
	//-
//	CMapFourTree				m_MapDataIndex;				//��ͼ����ͷ����
	CSqliteDB					 m_SqliteDB;				//���ݿ�����
	//std::map<int, std::map<int,MapBlockHead*>* > m_mapMapIndex[20];		//��ͼ�༶�б�
	CFourTree					m_MapLoadData;				//������������
	HANDLE						m_hMapDataMutex;			//��ͼ���ݻ�����
	//--
	string						m_strFileIndex;				//�����ļ�·��
	char*						m_pMapIndexData;			//��ͼ��������
	//
	int							m_iNewMapFileID;			//���µĵ�ͼ�ļ�ID
	CVOSFile					 m_FileData;
public:
	CMapDisp*					m_pMapDisp;
	CMapDataDown				m_MapDataDown;				//��ͼ����������
};
