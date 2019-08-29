// FourTree.h: interface for the CFourTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOURTREE_H__DF109424_1777_428A_A5D2_22048EF7B4FC__INCLUDED111_)
#define AFX_FOURTREE_H__DF109424_1777_428A_A5D2_22048EF7B4FC__INCLUDED111_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapDefine.h"
//四叉树节点结果
struct TreeNode4
{
	TreeNode4* m_child00;	//子00数据指针
	TreeNode4* m_child01;	//子01数据指针
	TreeNode4* m_child10;	//子10数据指针
	TreeNode4* m_child11;	//子11数据指针
	void*	   m_data;		//数据结构体
	TreeNode4()
	{
		m_child00 = NULL;	//子00的内存偏移地址
		m_child01 = NULL;	//子01的内存偏移地址
		m_child10 = NULL;	//子10的内存偏移地址
		m_child11 = NULL;	//子11的内存偏移地址
		m_data = NULL;		//数据地址
	}
	//添加子节点
	void AddTree00( TreeNode4* node )
	{
		m_child00 = node;
	}
	void AddTree01( TreeNode4* node )
	{
		m_child01 = node;
	}
	void AddTree10( TreeNode4* node )
	{
		m_child10 = node;
	}
	void AddTree11(  TreeNode4* node )
	{
		m_child11 = node;
	}
	//设置节点数据
	void SetNodeData( void* data )
	{
		m_data = data;
	}
	//只删除节点数据
	void DeleteNodeData()
	{
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
		}
	}
	//清除索引
	void Clear()
	{
		if( m_data )
		{
			m_data = NULL;
		}
		//清除子节点数据
		if( m_child00 )
		{
			m_child00->Clear();
			delete m_child00;
			m_child00 = NULL;
		}
		if( m_child01 )
		{
			m_child01->Clear();
			delete m_child01;
			m_child01 = NULL;
		}
		if( m_child10 )
		{
			m_child10->Clear();
			delete m_child10;
			m_child10 = NULL;
		}
		if( m_child11 )
		{
			m_child11->Clear();
			delete m_child11;
			m_child11 = NULL;
		}
	}
	//删除所有数据
	void DeleteAll()
	{
		//清除数据
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
		}
		//清除子节点数据
		if( m_child00 )
		{
			m_child00->DeleteAll();
			delete m_child00;
			m_child00 = NULL;
		}
		if( m_child01 )
		{
			m_child01->DeleteAll();
			delete m_child01;
			m_child01 = NULL;
		}
		if( m_child10 )
		{
			m_child10->DeleteAll();
			delete m_child10;
			m_child10 = NULL;
		}
		if( m_child11 )
		{
			m_child11->DeleteAll();
			delete m_child11;
			m_child11 = NULL;
		}
	}
};
/*
struct TreeNode4
{
	TreeNode4* m_child00;	//子00数据指针
	TreeNode4* m_child01;	//子01数据指针
	TreeNode4* m_child10;	//子10数据指针
	TreeNode4* m_child11;	//子11数据指针
	MapBlockHead*	 m_data;		//数据结构体
	TreeNode4()
	{
		m_child00 = NULL;	//子00的内存偏移地址
		m_child01 = NULL;	//子01的内存偏移地址
		m_child10 = NULL;	//子10的内存偏移地址
		m_child11 = NULL;	//子11的内存偏移地址
		m_data = NULL;		//数据地址
	}
	//添加子节点
	void AddTree00( TreeNode4* node )
	{
		m_child00 = node;
	}
	void AddTree01( TreeNode4* node )
	{
		m_child01 = node;
	}
	void AddTree10( TreeNode4* node )
	{
		m_child10 = node;
	}
	void AddTree11(  TreeNode4* node )
	{
		m_child11 = node;
	}
	//设置节点数据
	void SetNodeData( MapBlockHead* data )
	{
		m_data = data;
	}
	//只删除节点数据
	void DeleteNodeData()
	{
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
		}
	}
	//清除全部数据
	void ClearAll()
	{
			//清除数据
		if( m_data )
		{
			//delete m_data;
			//m_data = NULL;
		}
		//清除子节点数据
		if( m_child00 )
		{
			m_child00->ClearAll();
			delete m_child00;
			m_child00 = NULL;
		}
		if( m_child01 )
		{
			m_child01->ClearAll();
			delete m_child01;
			m_child01 = NULL;
		}
		if( m_child10 )
		{
			m_child10->ClearAll();
			delete m_child10;
			m_child10 = NULL;
		}
		if( m_child11 )
		{
			m_child11->ClearAll();
			delete m_child11;
			m_child11 = NULL;
		}
	}
	//计算节点数量
	unsigned long GetDataCount( )
	{
		unsigned long ulCount = 1;
		if( m_child00 )
		{
			ulCount += m_child00->GetDataCount();
		}
		if( m_child01 )
		{
			ulCount += m_child01->GetDataCount();
		}
		if( m_child10 )
		{
			ulCount += m_child10->GetDataCount();
		}
		if( m_child11 )
		{
			ulCount += m_child11->GetDataCount();
		}
		return ulCount;
	}
};
*/
class CFourTree  
{
public:
	CFourTree();
	virtual ~CFourTree();
	//创建四叉树
	void Create( long lDepth );
	//添加数据
	void AddData( long lDepth, long lNumX, long lNumY, MapBlockHead* data );

	//得到数据
	MapBlockHead* GetData( long lDepth, long lNumX, long lNumY );

	//删除节点数据，不删除子节点
	bool DeleteData( long lDepth, long lNumX, long lNumY );

	//清除全部数据和子节点
	void ClearAll();
	
	//计算节点数量
	unsigned long GetDataCount();
public:
	TreeNode4*		m_Tree4Root;
	long			m_lDepth;
};

#endif // !defined(AFX_FOURTREE_H__DF109424_1777_428A_A5D2_22048EF7B4FC__INCLUDED_)
