// MapDataIndex.h: interface for the CMapDataIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDATAINDEX_H__833A2630_C43E_4917_ADA9_9DF3F2BF21D6__INCLUDED_)
#define AFX_MAPDATAINDEX_H__833A2630_C43E_4917_ADA9_9DF3F2BF21D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\VOSBase\VOSDefine.h"
#include "../VOSBase/VOSFile.h"
#include "MapFourTree.h"
#include "MapBlockUnit.h"

//四叉树索引
struct tTree4Node
{
	long  m_lChild00;	//子00的偏移地址
	long  m_lChild01;	//子01的偏移地址
	long  m_lChild10;	//子10的偏移地址
	long  m_lChild11;	//子11的偏移地址
	long  m_lFileID;	//文件ID
	long  m_lFilePos;	//文件位置
	long  m_lFileSize;	//文件大小
	//构造函数
	tTree4Node()
	{
		m_lChild00 = 0;
		m_lChild01 = 0;
		m_lChild10 = 0;
		m_lChild11 = 0;
		m_lFileID = 0;
		m_lFilePos = 0;
		m_lFileSize = 0;
	}
	//创建子节点数据。
	int CreateNode( int iDepth, int lNumX, int lNumY, long lFID, long  lFPos, long lFSize, int lStart )
	{
		return 1;
	}
	//设置节点数据地址和长度
	void SetNodeData( long lFID, long  lFPos, long lFSize )
	{
		m_lFileID = lFID;
		m_lFilePos = lFPos;
		m_lFileSize = lFSize;
	}
};

class CMapDataIndex  
{
public:
	CMapDataIndex();
	virtual ~CMapDataIndex();

	//设置地图索引文件路径
	bool Init( const char* strPath );
	//设置地图索引文件路径
	bool Init4( const char* strPath );
	//退出释放数据
	void Realse();
	//查询数据是否存在
	MapBlockHead* GetMapData( short sLevel, long lNumX, long lNumY );

	//添加数据到索引short sLevel, long lNumX, long lNumY,int iMapID, char* pData, int len
	bool AddMapData( short sLevel, long lNumX, long lNumY, short sFileID, long lFilePos, long lFileSize );
	//删除某层数据
	bool DeleteMapData( short sLevel, long lNumX, long lNumY );
private:
	char		m_strPath[256];
	char*		m_data;
	long		m_length;
	CVOSFile	m_file; 
	std::map<int, std::map<int,MapBlockHead*>* > m_mapMapIndex[20];		//地图多级列表
	tTree4Node*	m_pTree4Root;
};

#endif // !defined(AFX_MAPDATAINDEX_H__833A2630_C43E_4917_ADA9_9DF3F2BF21D6__INCLUDED_)
