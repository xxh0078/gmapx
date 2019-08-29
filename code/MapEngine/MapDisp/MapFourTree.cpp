// MapFourTree.cpp: implementation of the CMapFourTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapFourTree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapFourTree::CMapFourTree()
{
	m_Tree4Root = NULL;
}

CMapFourTree::~CMapFourTree()
{
	Clear();
}
//初始化
void CMapFourTree::Create()
{
	Clear();
	m_Tree4Root = new TreeNode4();
}

//添加数据
void CMapFourTree::AddData( long lDepth, long lNumX, long lNumY, void* data )
{
	//检测是否有数据存在
	if( lDepth==4 && lNumX==12 && lNumY==5 )
	{
		TRACE("AddData %d %d %d ===%d\n",lDepth,lNumX,lNumY,data);
	}
	TreeNode4* pNewNode = NULL;
	TreeNode4* node = m_Tree4Root;
	if( lDepth == 0 )
	{
		if( m_Tree4Root->m_data )
		{
			delete m_Tree4Root->m_data;
			m_Tree4Root->m_data = NULL;
		}
		m_Tree4Root->m_data = data;
		return;
	}
	for( int i=0;i<lDepth;i++ )
	{
		if( node == NULL )
			return;
		//int tttx = lNumX>>(lDepth-i-1)&0x01;
		//int ttty = lNumY>>(lDepth-i-1)&0x01;
		if( lNumX>>(lDepth-i-1)&0x01 )
		{
			if( lNumY>>(lDepth-i-1)&0x01 )
			{
				if( node->m_child11 )
				{
					node = node->m_child11;
				}
				else
				{
					pNewNode = new TreeNode4();
					node->AddTree11( pNewNode );
					node = pNewNode;
				}
			}
			else
			{
				if( node->m_child10 )
				{
					node = node->m_child10;
				}
				else
				{
					pNewNode = new TreeNode4();
					node->AddTree10( pNewNode );
					node = pNewNode;
				}
			}
		}
		else
		{
			if( lNumY>>(lDepth-i-1)&0x01 )
			{
				if( node->m_child01 )
					node = node->m_child01;
				else
				{
					pNewNode = new TreeNode4();
					node->AddTree01( pNewNode );
					node = pNewNode;
				}
			}
			else
			{
				if( node->m_child00 )
					node = node->m_child00;
				else
				{
					pNewNode = new TreeNode4();
					node->AddTree00( pNewNode );
					node = pNewNode;
				}
			}
		}
	}
	//TRACE("AddData %d %d %d ===%d ok\n",lDepth,lNumX,lNumY,data);
	node->SetNodeData( data );
	//TRACE("AddData %d %d %d ===%d ok\n",lDepth,lNumX,lNumY,data);
}

//得到数据
void* CMapFourTree::GetData( long lDepth, long lNumX, long lNumY )
{
	//TRACE("getdata %d %d %d\n",lDepth,lNumX,lNumY);
	//检测是否有数据存在
	TreeNode4* node = m_Tree4Root;
	for( int i=0;i<lDepth;i++ )
	{
		if( node == NULL )
			return NULL;
		int tttx = lNumX>>(lDepth-i-1)&0x01;
		int ttty = lNumY>>(lDepth-i-1)&0x01;
		if( lNumX>>(lDepth-i-1)&0x01 )
		{
			if( lNumY>>(lDepth-i-1)&0x01 )
			{
				if( node->m_child11 )
					node = node->m_child11;
				else
					return NULL;
			}
			else
			{
				if( node->m_child10 )
					node = node->m_child10;
				else
					return NULL;
			}
		}
		else
		{
			if( lNumY>>(lDepth-i-1)&0x01 )
			{
				if( node->m_child01 )
					node = node->m_child01;
				else
					return NULL;
			}
			else
			{
				if( node->m_child00 )
					node = node->m_child00;
				else
					return NULL;
			}
		}
	}
	if( node == NULL )
		return NULL;
	//TRACE("getdata %d %d %d ===%d ok \n",lDepth,lNumX,lNumY,node->m_data);
	return node->m_data;
}

//删除数据
bool CMapFourTree::DeleteData( long lDepth, long lNumX, long lNumY )
{
	//TRACE("DeleteData %d %d %d\n",lDepth,lNumX,lNumY);
	//检测是否有数据存在
	TreeNode4* node = m_Tree4Root;
	for( int i=0;i<lDepth;i++ )
	{
		if( node == NULL )
			break;
		int tttx = lNumX>>(lDepth-i-1)&0x01;
		int ttty = lNumY>>(lDepth-i-1)&0x01;
		if( lNumX>>(lDepth-i)&0x01 )
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				if( node->m_child11 )
					node = node->m_child11;
				else
					return false;
			}
			else
			{
				if( node->m_child10 )
					node = node->m_child10;
				else
					return false;
			}
		}
		else
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				if( node->m_child01 )
					node = node->m_child01;
				else
					return false;
			}
			else
			{
				if( node->m_child00 )
					node = node->m_child00;
				else
					return false;
			}
		}
	}
	if( node == NULL )
		return false;
	if( node->m_data )
		return false;
	node->DeleteNodeData();
	return true;
}
//清除所有节点
void CMapFourTree::Clear()
{
	if( m_Tree4Root )
	{
		m_Tree4Root->Clear();
		delete m_Tree4Root;
		m_Tree4Root = NULL;
	}
}

//删除所有数据
void CMapFourTree::DeleteAll()
{
	if( m_Tree4Root )
	{
		m_Tree4Root->DeleteAll();
		delete m_Tree4Root;
		m_Tree4Root = NULL;
	}
}
