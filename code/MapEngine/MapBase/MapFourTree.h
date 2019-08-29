// MapFourTree.h: interface for the CMapFourTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED11_)
#define AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED11_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapDefine.h"
//四叉树节点结果
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
	void Create()
	{
		m_lChild00 = 0;
		m_lChild01 = 0;
		m_lChild10 = 0;
		m_lChild11 = 0;
		m_lFileID = 0;
		m_lFilePos = 0;
		m_lFileSize = 0;
	}

	//设置节点数据地址和长度
	void SetNodeData( long lFID, long  lFPos, long lFSize )
	{
		m_lFileID = lFID;
		m_lFilePos = lFPos;
		m_lFileSize = lFSize;
	}
	//创建子节点00
	tTree4Node* CreateNode00( int iPos,char* pData )
	{
		m_lChild00 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}
	//创建子节点01
	tTree4Node* CreateNode01( int iPos,char* pData )
	{
		m_lChild01 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}//创建子节点00
	tTree4Node* CreateNode10( int iPos,char* pData )
	{
		m_lChild10 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}//创建子节点00
	tTree4Node* CreateNode11( int iPos,char* pData )
	{
		m_lChild11 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}
};

//地图四叉树
class CMapFourTree  
{
public:
	CMapFourTree();
	virtual ~CMapFourTree();

	//创建四叉树
	bool Create( int iCount );
	
	//打开文件
	bool OpenTreeFile( string strFileName );
	//添加数据
	tTree4Node* SetData( long lDepth, long lNumX, long lNumY, long lFID, long  lFPos, long lFSize );

	//得到数据
	tTree4Node* GetData( long lDepth, long lNumX, long lNumY );

	//删除节点数据，不删除子节点
	bool DeleteData( long lDepth, long lNumX, long lNumY );

	//清除全部数据和子节点
	void ClearAll();
	
	//计算节点数量
	unsigned long GetDataCount();
	//计算数据大小
	long GetLength();
	//保存树
	bool SaveTree( string strFileName );
public:
	char*			m_pData;
	long			m_lDataSize;
	//--
	int				m_iPos;
	int				m_iCount;
	tTree4Node*		m_Tree4Root;
	long			m_lDepth;
};

#endif // !defined(AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED_)
