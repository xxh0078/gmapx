// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_)
#define AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
class CMapDown  
{
public:
	CMapDown();
	virtual ~CMapDown();
	//��ʼ����ʱ�ļ�,dirΪ����Ŀ¼
	void Init( CWnd* pWnd, float x1,float x2, float y1,float y2,long level, string strIndex );
	//��������
	void Start( );
	//ֹͣ����
	void Stop( );
	//������ʾ����
	void Draw( HDC hdc, int left,int top );
private:
	//��ȡ�ȸ賣���ͼ
	bool GetMap(  int x, int y, int z  );
	//��õ�ǰbound
	void GetLevelBound( int z );
	//����������·��
	void CreateLevelDir(int iLevel );
	//���������߳�
	static unsigned long __stdcall DownLoadProc( void* pParameter );
	//����ϴ�����λ��
	bool GetDownPosition( int& x, int& y, int& z );
	//�������λ��
	bool GetNextDownPosition( int& x, int& y, int& z );
	//��������λ��
	void SaveDownPosition( int x, int y, int z );
private:
	//��ǰ�ļ�����
	int m_ix;
	int m_iy;
	int m_iz;
	//ת����ķ�Χ
	int m_iMinX ;
	int m_iMaxX ;
	int m_iMinY ;
	int m_iMaxY ;

	bool m_bExitProc;
	bool m_bFirst;
	CWnd* m_pWnd;
	//��γ�ȷ�Χ
	MapBount m_mapBound;
	char	m_strRootPath[255];
	CString m_strView;
	CString m_strIndex;
};

#endif // !defined(AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_)
