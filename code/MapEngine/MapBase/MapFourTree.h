// MapFourTree.h: interface for the CMapFourTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED11_)
#define AFX_MAPFOURTREE_H__D454C0B3_04B1_459D_826F_82F789C63888__INCLUDED11_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapDefine.h"
//�Ĳ����ڵ���
//�Ĳ�������
struct tTree4Node
{
	long  m_lChild00;	//��00��ƫ�Ƶ�ַ
	long  m_lChild01;	//��01��ƫ�Ƶ�ַ
	long  m_lChild10;	//��10��ƫ�Ƶ�ַ
	long  m_lChild11;	//��11��ƫ�Ƶ�ַ
	long  m_lFileID;	//�ļ�ID
	long  m_lFilePos;	//�ļ�λ��
	long  m_lFileSize;	//�ļ���С
	//���캯��
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

	//���ýڵ����ݵ�ַ�ͳ���
	void SetNodeData( long lFID, long  lFPos, long lFSize )
	{
		m_lFileID = lFID;
		m_lFilePos = lFPos;
		m_lFileSize = lFSize;
	}
	//�����ӽڵ�00
	tTree4Node* CreateNode00( int iPos,char* pData )
	{
		m_lChild00 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}
	//�����ӽڵ�01
	tTree4Node* CreateNode01( int iPos,char* pData )
	{
		m_lChild01 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}//�����ӽڵ�00
	tTree4Node* CreateNode10( int iPos,char* pData )
	{
		m_lChild10 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}//�����ӽڵ�00
	tTree4Node* CreateNode11( int iPos,char* pData )
	{
		m_lChild11 = iPos;
		tTree4Node* pNode = (tTree4Node*)pData;
		pNode->Create();
		return pNode;
	}
};

//��ͼ�Ĳ���
class CMapFourTree  
{
public:
	CMapFourTree();
	virtual ~CMapFourTree();

	//�����Ĳ���
	bool Create( int iCount );
	
	//���ļ�
	bool OpenTreeFile( string strFileName );
	//�������
	tTree4Node* SetData( long lDepth, long lNumX, long lNumY, long lFID, long  lFPos, long lFSize );

	//�õ�����
	tTree4Node* GetData( long lDepth, long lNumX, long lNumY );

	//ɾ���ڵ����ݣ���ɾ���ӽڵ�
	bool DeleteData( long lDepth, long lNumX, long lNumY );

	//���ȫ�����ݺ��ӽڵ�
	void ClearAll();
	
	//����ڵ�����
	unsigned long GetDataCount();
	//�������ݴ�С
	long GetLength();
	//������
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
