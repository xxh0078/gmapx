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
	//�����ӽڵ����ݡ�
	int CreateNode( int iDepth, int lNumX, int lNumY, long lFID, long  lFPos, long lFSize, int lStart )
	{
		return 1;
	}
	//���ýڵ����ݵ�ַ�ͳ���
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

	//���õ�ͼ�����ļ�·��
	bool Init( const char* strPath );
	//���õ�ͼ�����ļ�·��
	bool Init4( const char* strPath );
	//�˳��ͷ�����
	void Realse();
	//��ѯ�����Ƿ����
	MapBlockHead* GetMapData( short sLevel, long lNumX, long lNumY );

	//������ݵ�����short sLevel, long lNumX, long lNumY,int iMapID, char* pData, int len
	bool AddMapData( short sLevel, long lNumX, long lNumY, short sFileID, long lFilePos, long lFileSize );
	//ɾ��ĳ������
	bool DeleteMapData( short sLevel, long lNumX, long lNumY );
private:
	char		m_strPath[256];
	char*		m_data;
	long		m_length;
	CVOSFile	m_file; 
	std::map<int, std::map<int,MapBlockHead*>* > m_mapMapIndex[20];		//��ͼ�༶�б�
	tTree4Node*	m_pTree4Root;
};

#endif // !defined(AFX_MAPDATAINDEX_H__833A2630_C43E_4917_ADA9_9DF3F2BF21D6__INCLUDED_)
