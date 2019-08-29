// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_)
#define AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapData.h"

class CMapDown  
{
public:
	CMapDown();
	virtual ~CMapDown();
	
	//��ʼ��,�����û���ֳɵ�
	bool Init();

	//�������ز���
	bool SetParam( string strMapName, int lMapType, int Minlevel, int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath, bool bWrite = true );
	
	//��������
	void Start( int nThreadNum = 5 );

	//ֹͣ����
	void Stop( );

	//ɾ������
	void Delete( );

	//�Ƿ���������
	bool IsDown(){return !m_bExitProc;};

	//�����߳�
	static unsigned long __stdcall DownLoadProc( void* pParameter );

	//ִ���߳�
	int Run();

	//���
	bool AddMapData( string strPath );
	//���
	bool CreateDBIndex();

	bool CheckMapData();
private:
	//��ȡ�����ļ�
	bool ReadConf( string strFileName );
	//���������ļ�
	bool WriteConf( string strFileName );

	//�����λ�ã��Ѿ����ط���TRUE��û�����ط���FALSE
	bool GetNextPosition( int& x, int& y, int& z );

	
	//�õ�����·��
	//bool GetDownLoadURL( string& strURL, int x,int y,int z );
	//���ظ��ļ�
	bool DownLoad( const char* strURL, int x, int y, int z );

	//���ص�һ������
	bool DownFirstData();
private:
	//��ͼ����
	long		m_lMapType;
	//��γ�ȷ�Χ
	MapBount	m_mapBound;
	MBound		m_MBound20;
	MPoint		m_MapCenter20TopLeft;
	MPoint		m_MapCenter20BottomRight;
	//��ͼ��·��
	string		m_strMapPath;
	string		m_strMapName;
	
	HANDLE		m_hDownMutex;				// �̻߳�����
	bool		m_bExitProc;
	bool		m_bFinish;
	//--
	char		m_strRootPath[256];
	
public:
	//���ط�Χ
	CMapData	m_MapData;
};

#endif // !defined(AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_)
