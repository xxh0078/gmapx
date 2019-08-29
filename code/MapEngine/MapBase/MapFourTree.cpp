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
	m_iPos = 0;
	m_iCount = 0;
}

CMapFourTree::~CMapFourTree()
{
	ClearAll();
}

//�����Ĳ���
bool CMapFourTree::Create( int iCount )
{
	m_lDataSize = iCount*sizeof(tTree4Node);
	m_pData = (char*)malloc(m_lDataSize);
	if( m_pData == NULL )
		return false;
	m_Tree4Root = (tTree4Node*)m_pData;
	m_iPos = sizeof( tTree4Node );
	m_Tree4Root->Create();
	m_iCount=1;
	
	return true;
}
//������ݣ����ؽڵ�ķѵ��ڴ��ֽ���
tTree4Node* CMapFourTree::SetData( long lDepth, long lNumX, long lNumY, long lFID, long  lFPos, long lFSize )
{
	TRACE("SetData %d %d %d %d %d %d \n", lDepth,lNumX,lNumY, lFID, lFPos, lFSize );
	//���������Ƿ����
	if( m_Tree4Root == NULL )
	{
		m_Tree4Root = (tTree4Node*)m_pData;
		m_iPos = sizeof( tTree4Node );
		m_Tree4Root->Create();
	}
	if( lDepth==0 )
	{
		m_Tree4Root->SetNodeData( lFID, lFPos, lFSize );
		return m_Tree4Root;
	}
	//���¼��
	tTree4Node* pNode = m_Tree4Root;
	for( int i=1;i<=lDepth;i++ )
	{
		if( pNode == NULL )
			return NULL;
		int tttx = lNumX>>(lDepth-i)&0x01;
		int ttty = lNumY>>(lDepth-i)&0x01;
		if( lNumX>>(lDepth-i)&0x01 )
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				//��������ӽڵ㣬�򷵻��ӽڵ�ָ��
				if( pNode->m_lChild11 )
				{
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild11 );
				}
				else
				{
					//�������򴴽�
					pNode = pNode->CreateNode11( m_iPos, m_pData+m_iPos );
					m_iPos += sizeof( tTree4Node );
				}
			}
			else
			{
				//��������ӽڵ㣬�򷵻��ӽڵ�ָ��
				if( pNode->m_lChild10 )
				{
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild10 );
				}
				else
				{
					//�������򴴽�
					pNode = pNode->CreateNode10( m_iPos, m_pData+m_iPos );
					m_iPos += sizeof( tTree4Node );
				}
			}
		}
		else
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				//��������ӽڵ㣬�򷵻��ӽڵ�ָ��
				if( pNode->m_lChild01 )
				{
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild01 );
				}
				else
				{
					//�������򴴽�
					pNode = pNode->CreateNode01( m_iPos, m_pData+m_iPos );
					m_iPos += sizeof( tTree4Node );
				}
			}
			else
			{
				//��������ӽڵ㣬�򷵻��ӽڵ�ָ��
				if( pNode->m_lChild00 )
				{
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild00 );
				}
				else
				{
					//�������򴴽�
					pNode = pNode->CreateNode00( m_iPos, m_pData+m_iPos );
					m_iPos += sizeof( tTree4Node );
				}
			}
		}
	}
	pNode->SetNodeData( lFID, lFPos, lFSize );
	m_iCount++;
	return pNode;
}

//�õ�����
tTree4Node* CMapFourTree::GetData( long lDepth, long lNumX, long lNumY )
{
	TRACE("GetData %d %d %d\n", lDepth,lNumX,lNumY );
	/*
	tTree4Node* pNode1 = (tTree4Node*)m_pData;
	for( int j=0;j<m_iPos/sizeof(tTree4Node);j++ )
	{
		TRACE("pNode%d 00=%d 01=%d 10=%d 11=%d == %d,%d,%d\n",j,pNode1->m_lChild00,
			pNode1->m_lChild01,pNode1->m_lChild10,pNode1->m_lChild11,pNode1->m_lFileID,pNode1->m_lFilePos,pNode1->m_lFileSize);
		pNode1++;
	}
	TRACE("ok\n");
	*/
	//����Ƿ������ݴ���
	if( lDepth == 0 )
		return m_Tree4Root;
	//
	tTree4Node* pNode = m_Tree4Root;
	for( int i=1;i<=lDepth;i++ )
	{
		if( pNode == NULL )
			return NULL;
		int tttx = lNumX>>(lDepth-i)&0x01;
		int ttty = lNumY>>(lDepth-i)&0x01;
		if( lNumX>>(lDepth-i)&0x01 )
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				if( pNode->m_lChild11 )
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild11 );
				else
					return NULL;
			}
			else
			{
				if( pNode->m_lChild10 )
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild10 );
				else
					return NULL;
			}
		}
		else
		{
			if( lNumY>>(lDepth-i)&0x01 )
			{
				if( pNode->m_lChild01 )
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild01 );
				else
					return NULL;
			}
			else
			{
				if( pNode->m_lChild00 )
					pNode = (tTree4Node*)( m_pData + pNode->m_lChild00 );
				else
					return NULL;
			}
		}
	}
	/*
	pNode1 = (tTree4Node*)m_pData;	
	for( j=0;j<m_iPos/sizeof(tTree4Node);j++ )
	{
		TRACE("pNode%d 00=%d 01=%d 10=%d 11=%d == %d,%d,%d\n",j,pNode1->m_lChild00,
			pNode1->m_lChild01,pNode1->m_lChild10,pNode1->m_lChild11,pNode1->m_lFileID,pNode1->m_lFilePos,pNode1->m_lFileSize);
		pNode1++;
	}
	TRACE("ok\n");
	*/
	if( pNode == NULL )
		return NULL;
	TRACE("GetData %d %d %d %d %d %d \n", lDepth,lNumX,lNumY, pNode->m_lFileID, pNode->m_lFilePos, pNode->m_lFileSize );
	return pNode;
}

/*
//ɾ������
bool CMapFourTree::DeleteData( long lDepth, long lNumX, long lNumY )
{
	//TRACE("DeleteData %d %d %d\n",lDepth,lNumX,lNumY);
	return true;
}
//���ȫ������
void CMapFourTree::ClearAll()
{
	if( m_Tree4Root )
	{
		//m_Tree4Root->ClearAll();
		//delete m_Tree4Root;
		m_Tree4Root = NULL;
		m_lDepth = 0;
	}
}
//����ڵ�����
unsigned long CMapFourTree::GetDataCount()
{
	return 1;//m_Tree4Root->GetDataCount();
}
*/
//���ȫ������
void CMapFourTree::ClearAll()
{
	if( m_Tree4Root )
	{
		//m_Tree4Root->ClearAll();
		delete m_pData;
		m_pData = NULL;
		m_Tree4Root = NULL;
		m_lDepth = 0;
	}
}
//�������ݴ�С
long CMapFourTree::GetLength()
{
	return m_iPos;
}
//���ļ�
bool CMapFourTree::OpenTreeFile( string strFileName )
{
	CVOSFile fileIndex4;
	if( !fileIndex4.Open( strFileName.c_str(), fomReadWrite ) )
	{
		CVOSUtil::MessageBox( "�������ļ�ʧ��!","��ʾ" );
		return false;
	}
	m_lDataSize = fileIndex4.GetLength();
	m_pData = (char*)malloc( m_lDataSize );
	if( m_pData == NULL )
		return false;
	char* pTemp = m_pData;
	m_iPos = 0;
	while( 1 )
	{
		m_iPos += fileIndex4.Read( pTemp, m_lDataSize );
		if( m_iPos >= m_lDataSize )
			break;
	}
	fileIndex4.Close();
	m_Tree4Root = (tTree4Node*)m_pData;
	return true;
}
//������
bool CMapFourTree::SaveTree( string strFileName )
{
	TRACE("m_iPos=%d\n", m_iPos);
	tTree4Node* pNodeNew = GetData( 15, 23028, 10420 );
	tTree4Node* pNodeNew1 = GetData( 15, 23028, 10520 );
	/*
	tTree4Node* pNode1 = (tTree4Node*)m_pData;
	for( int j=0;j<m_iPos/sizeof(tTree4Node);j++ )
	{
		TRACE("pNode1 00=%d 01=%d 10=%d 11=%d == %d,%d,%d\n",pNode1->m_lChild00,
			pNode1->m_lChild01,pNode1->m_lChild10,pNode1->m_lChild11,pNode1->m_lFileID,pNode1->m_lFilePos,pNode1->m_lFileSize);
		pNode1++;
	}
	TRACE("ok\n");
	*/
	CVOSFile fileIndex4;
	if( !fileIndex4.Open( strFileName.c_str(), fomReadWrite|fomCreate ) )
	{
		CVOSUtil::MessageBox( "�����ļ�ʧ�ܣ���ر���ؽ��̻��������Ժ����ԣ�","��ʾ" );
		return false;
	}
	char* pTemp = m_pData;
	int iLen = 0;
	while( 1 )
	{
		iLen += fileIndex4.Write( pTemp, m_iPos-iLen );
		if( iLen >= m_iPos )
			break;
	}
	fileIndex4.Close();
	CVOSUtil::MessageBox( "���������������!","��ʾ" );
	return true;
}