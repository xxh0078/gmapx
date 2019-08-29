// MapDataIndex.cpp: implementation of the CMapDataIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapDataIndex.h"
#include "MapFourTree.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define EXTERN_INDEX_DATA_SIZE 1024*1024	//�����ļ���չ�ռ�

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapDataIndex::CMapDataIndex()
{
	m_data = NULL;
	m_length = 0;
	memset( m_strPath,0,256 );
}

CMapDataIndex::~CMapDataIndex()
{
	Realse();
}
//���õ�ͼ�����ļ�·��
bool CMapDataIndex::Init4( const char* strPath )
{
	//�����ļ�·��
	strcpy( m_strPath, strPath );
	strcat( m_strPath, "\\gm.g4i" );
	//���õ�ͼ·��
	if( !m_file.Open( m_strPath, fomReadWrite ) )
	{
		if( !m_file.Open( m_strPath, fomReadWrite|fomCreate ) )
		{
			return false;
		}
	}
	m_length = m_file.GetLength();
	m_data = (char*)malloc( m_length+EXTERN_INDEX_DATA_SIZE );
	m_file.Read( m_data, m_length );
	m_file.Close();
	m_pTree4Root = (tTree4Node*)m_data;
	return true;
}
//���õ�ͼ�����ļ�·��
bool CMapDataIndex::Init( const char* strPath )
{
	//�ͷžɵ�����
	Realse();
	//�����ļ�·��
	strcpy( m_strPath, strPath );
	strcat( m_strPath, "\\gm.gi" );
	//���õ�ͼ·��
	if( m_file.Open( m_strPath, fomReadWrite ) )
	{
		m_length = m_file.GetLength();
		m_data = (char*)malloc( m_length );
		char* pTemp = m_data;
		int iReadLen = 0;
		while(1)
		{
			iReadLen = m_file.Read( pTemp,m_length ); 
			pTemp += iReadLen;
			if( iReadLen >= m_length )
				break;
		}
		//�����ͼ��������
		char ch[64];
		pTemp = m_data;

		while( pTemp - m_data < m_length )
		{
			MapBlockHead* pBlock = (MapBlockHead*)pTemp;
			//memcpy( pBlock, pTemp, sizeof(MapBlockUnit) );
			sprintf( ch,"%d_%d_%d",pBlock->sLevel,pBlock->lNumY,pBlock->lNumX );
			if( pBlock->sLevel > 20 || pBlock->sLevel < 0 )
			{
				pTemp+=sizeof(MapBlockHead);
				continue;
			}
			std::map<int, std::map<int,MapBlockHead*>* >::iterator it;
			std::map<int,MapBlockHead*>::iterator it1;
			std::map<int,MapBlockHead*>* map1;

			//����X����λ��
			it = m_mapMapIndex[ pBlock->sLevel ].find( pBlock->lNumX );
			if( it != m_mapMapIndex[ pBlock->sLevel ].end() )
			{
				map1 = it->second;
			}
			else
			{
				map1 = new std::map<int,MapBlockHead*>;
				m_mapMapIndex[ pBlock->sLevel ].insert( pair<int, std::map<int,MapBlockHead*>*>( pBlock->lNumX, map1 ) );
			}
			//����Y����
			map1->insert( pair<int,MapBlockHead* >( pBlock->lNumY, pBlock ) );
			//m_mapMapIndex
			//this->m_mapMapBlockHead.insert( pair<string,CMapBlockUnit*>(ch,pBlock ) );
			pTemp+=sizeof(MapBlockHead);
		}
		//free( pData );
		m_file.Close();
	}
	else
	{
		//m_data = (char*)malloc( EXTERN_INDEX_DATA_SIZE );
		//memset( m_data,0,24 );
		//m_length = 24;
		if( !m_file.Open( m_strPath, fomReadWrite|fomCreate ) )
		{
			string strLog  = "��";
			strLog += m_strPath;
			strLog += "ʧ��,�п�����IE������İ�ȫ�������⡣��ע��ʹ�øò������Ҫȥ��IE����İ�ȫ����ģʽ���߰�װ�������ϵͳ���̷���";
			CVOSUtil::MessageBox( strLog.c_str(),"������ʾ" );
			return false;
		}
		//m_file.Write( m_data, 24 );
		m_file.Close();
	}
	//���õ�ͼ����
	
	//m_pTree4Root = (tTree4Node*)m_data;
}
//�˳��ͷ�����
void CMapDataIndex::Realse()
{
	std::map<int, std::map<int,MapBlockHead*>* >::iterator it;
	std::map<int,MapBlockHead*>::iterator it1;
	std::map<int,MapBlockHead*>* map1;
	for( int i=0;i<20;i++)
	{
		for (it = m_mapMapIndex[i].begin(); it != m_mapMapIndex[i].end(); it++)
		{
			map1 = it->second;
			map1->clear();
			delete map1;
		}
		m_mapMapIndex[i].clear();
	}
	if( m_data != NULL )
	{
		free( m_data );
		m_data = NULL;
		m_length = 0;
	}
	
	//m_MapFourTree.ClearAll();
}
//��ѯ�����Ƿ����
MapBlockHead* CMapDataIndex::GetMapData( short sLevel, long lNumX, long lNumY )
{
	MapBlockHead* pBlock = NULL;
	std::map<int, std::map<int,MapBlockHead*>* >::iterator it;
	std::map<int,MapBlockHead*>::iterator it1;
	std::map<int,MapBlockHead*>* map1;

	//����X����λ��
	it = m_mapMapIndex[ sLevel ].find( lNumX );
	if( it == m_mapMapIndex[ sLevel ].end() )
	{
		return NULL;
		
	}
	map1 = it->second;
	it1 = map1->find( lNumY );
	if( it1 == map1->end() )
		return NULL;
	pBlock =  it1->second;
	//m_mapMapIndex[ sLevel ].insert( pair<int, std::map<int,MapBlockHead*>*>( lNumX, map1 ) );
	return pBlock;
}
//������ݵ�����
bool CMapDataIndex::AddMapData( short sLevel, long lNumX, long lNumY, short sFileID, long lFilePos, long lFileSize )
{
	//���ļ�
	/*CVOSFile fileIndex; 
	if( !fileIndex.Open( m_strPath, fomReadWrite ) )
		return false;
	//����ڵ�
	tTree4Node* pNode = m_pTree4Root;
	tTree4Node* pNewNode = NULL;
	for( int i=0;i<sLevel;i++)
	{
		if( pNode == NULL )
			return false;
		int tttx = lNumX>>(sLevel-i-1)&0x01;
		int ttty = lNumY>>(sLevel-i-1)&0x01;
		if( lNumX>>(sLevel-i-1)&0x01 )
		{
			if( lNumY>>(sLevel-i-1)&0x01 )
			{
				if( pNode->m_lChild00 )
				{
					pNode = (tTree4Node*)( m_data+pNode->m_lChild00 );
				}
				else
				{
					pNewNode = new TreeNode4( sLevel - i );
					pNode->m_lChild00 = m_data+ m_length;
					break;
				}
			}
			else
			{
				if( pNode->m_child10 )
				{
					pNode = (tTree4Node*)( m_data+pNode->m_lChild00 );
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
			if( lNumY>>(sLevel-i-1)&0x01 )
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
	*/
	MapBlockHead mapBlockUnit;
	mapBlockUnit.lNumX=lNumX;				//X������
	mapBlockUnit.lNumY=lNumY;				//Y������
	mapBlockUnit.sLevel=sLevel;				//������
    mapBlockUnit.sFileID=sFileID;			//�ļ�ID���ļ���ID����
	mapBlockUnit.lFilePos=lFilePos;			//�ļ�λ��
	mapBlockUnit.lFileSize=lFileSize;			//�ļ���С
	CVOSFile fileIndex; 
	if( fileIndex.Open( m_strPath, fomReadWrite ) )
	{
		fileIndex.SeekToEnd();
		fileIndex.Write( &mapBlockUnit,sizeof( MapBlockHead ) );
		fileIndex.Close();
	}
	return true;
}
//ɾ��ĳ������
bool CMapDataIndex::DeleteMapData( short sLevel, long lNumX, long lNumY )
{
	//return m_MapFourTree.DeleteData( sLevel, lNumX, lNumY );
	return false;
}