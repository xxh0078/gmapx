// MapRule.h: interface for the CMapRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPRULE_H__2701B14A_5449_4E50_9EFE_7760AA295CD5__INCLUDED_)
#define AFX_MAPRULE_H__2701B14A_5449_4E50_9EFE_7760AA295CD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
class CMapDisp;
class CMapRule  
{
public:
	CMapRule();
	virtual ~CMapRule();
	//�ͷ��ڴ�
	void Realse();

	//���һ����
	void AddPoint( MapPoint* pPoint );
	//�õ��ܵĵ�����
	long GetCount();

	//�����߿��
	void SetColor( long color );
	//�����ߵ���ɫ
	void SetWidth( long width );
	//�����Ƿ���ʾ
	void SetVisible(bool visible );
	bool GetVisible();
	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp );
public:
	long	m_lineid;
	vector<MapPoint*>	m_arrPoint;
	long m_color;
	long m_width;
	string m_strname;
	bool	m_bVisible;
};

#endif // !defined(AFX_MAPRULE_H__2701B14A_5449_4E50_9EFE_7760AA295CD5__INCLUDED_)
