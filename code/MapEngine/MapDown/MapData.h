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
	double  m_dCount;	//当前比例尺下需要下载的地图数据总数
	double	m_dPos;		//当前比例尺下已经下载的地图数量
	long	m_lx;		//当前比例尺下已经下载的X位置
	long	m_ly;		//当前比例尺下已经下载的Y位置
	bool	m_bDownLoad;	//是否下载
};

class CMapData  
{
public:
	CMapData();
	virtual ~CMapData();
	//初始化
	bool Init( const char* strMapPath );
	//释放内存
	void Realse();

	//打开下载好的数据
	bool OpenMapData( const char* strMapPath );

	//打开下载好的数据
	bool OpenMapData();

	//创建数据库索引
	bool CreateDBIndex();

	//创建四叉树索引
	bool CreateMapFourTree();

	//关闭下载好的数据
	void CloseMapData();

	//启动数据保存线程
	void StartSaveProc();
	//添加
	bool AddMapFile();

	//查询数据是否存在
	MapBlockHead* GetMapData( short sLevel, long lNumX, long lNumY );

public:
	//下载数据保存等函数
	//添加
	bool AddMapData( MapBlockData* pData );
	

	//地图数据索引保存
	void SaveMap4Tree();

	//保存多条数据,返回条数
	int  WriteMapData( );

	//数据保存线程
	static unsigned long __stdcall MapDataProc( void* pParameter );

	//执行线程
	int Run();

	//添加数据线程
	static unsigned long __stdcall AddMapFileProc( void* pParameter );

	//添加数据线程
	static unsigned long __stdcall CreateDBProc( void* pParameter );

	//添加数据线程
	static unsigned long __stdcall CheckMapDataProc( void* pParameter );
	//
	bool GetNextPosition( int& x, int& y, int& z );
	//检测数据
	bool CheckMapData();
private:

	//打开新的地图数据文件
	bool OpenMapDataFile( int iFileID );
	//创建新的地图数据文件
	bool CreateMapDataFile( int iFileID );
	
public:

	//当前文件索引
	int m_ix;
	int m_iy;
	int m_iz;
	
	//比例尺范围
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
	list<MapBlockData*>			 m_arrMapData;				//等待保存数据列表
	HANDLE						 m_hMapDataMutex;			//线程互斥区

	bool						 m_bExitProc;				//是否线程退出
	char						 m_strLog[256];
	CTime						 m_TimeLog;
	
	//已经存在数据表
	//CFourTree					 m_FourTree;				//地图四叉搜索	
	CSqliteDB					 m_SqliteDB;				//数据库索引

	string						 m_strAddMapPath;
};

#endif // !defined(AFX_MAPDATA_H__6B905513_11F3_4FB0_ACFC_757E06127C36__INCLUDED_)
