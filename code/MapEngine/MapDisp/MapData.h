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
	//初始化
	void Init( CMapDisp* pMapDisp );
	//释放内存
	void Realse();

	//设置地图路径
	bool SetMapPath( string strMapPath, en_MapType enMapType );

	//得到地图数据块
	CMapBlockUnit* GetMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID );

	//添加地图数据块
	bool AddMapBlockUnit( short sLevel, long lNumX, long lNumY,int iMapID,char* pData, int len );

private:
	bool SaveMapData( short sLevel, long lNumX, long lNumY, char* pData, int len );
	//创建新的地图数据文件
	int OpenMapDataFile( int iFileID );
private:
	string						 m_strMapPath;
	en_MapType					 m_enMapType;
	//-
//	CMapFourTree				m_MapDataIndex;				//地图数据头索引
	CSqliteDB					 m_SqliteDB;				//数据库索引
	//std::map<int, std::map<int,MapBlockHead*>* > m_mapMapIndex[20];		//地图多级列表
	CFourTree					m_MapLoadData;				//加载数据索引
	HANDLE						m_hMapDataMutex;			//地图数据互斥区
	//--
	string						m_strFileIndex;				//索引文件路径
	char*						m_pMapIndexData;			//地图索引数据
	//
	int							m_iNewMapFileID;			//最新的地图文件ID
	CVOSFile					 m_FileData;
public:
	CMapDisp*					m_pMapDisp;
	CMapDataDown				m_MapDataDown;				//地图数据下载类
};
