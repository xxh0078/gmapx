// MapFourTree.h: interface for the CMapFourTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED_)
#define AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�Ĳ����ڵ���
struct TreeNode4
{
	TreeNode4* m_child00;	//��00����ָ��
	TreeNode4* m_child01;	//��01����ָ��
	TreeNode4* m_child10;	//��10����ָ��
	TreeNode4* m_child11;	//��11����ָ��
	void*	   m_data;		//���ݽṹ��
	TreeNode4()
	{
		m_child00 = NULL;	//��00���ڴ�ƫ�Ƶ�ַ
		m_child01 = NULL;	//��01���ڴ�ƫ�Ƶ�ַ
		m_child10 = NULL;	//��10���ڴ�ƫ�Ƶ�ַ
		m_child11 = NULL;	//��11���ڴ�ƫ�Ƶ�ַ
		m_data = NULL;		//���ݵ�ַ
	}
	//����ӽڵ�
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
	//���ýڵ�����
	void SetNodeData( void* data )
	{
		m_data = data;
	}
	//ֻɾ���ڵ�����
	void DeleteNodeData()
	{
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
		}
	}
	//�������
	void Clear()
	{
		if( m_data )
		{
			m_data = NULL;
		}
		//����ӽڵ�����
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
	//ɾ����������
	void DeleteAll()
	{
		//�������
		if( m_data )
		{
			delete m_data;
			m_data = NULL;
		}
		//����ӽڵ�����
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

//��ͼ�Ĳ���
class CMapFourTree  
{
public:
	CMapFourTree();
	virtual ~CMapFourTree();

	//�����Ĳ���
	void Create();
	//�������
	void AddData( long lDepth, long lNumX, long lNumY, void* data );

	//�õ�����
	void* GetData( long lDepth, long lNumX, long lNumY );

	//ɾ���ڵ����ݣ���ɾ���ӽڵ�
	bool DeleteData( long lDepth, long lNumX, long lNumY );

	//������нڵ�
	void Clear();

	//ɾ����������
	void DeleteAll();
public:
	TreeNode4*    m_Tree4Root;
};

#endif // !defined(AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED_)
