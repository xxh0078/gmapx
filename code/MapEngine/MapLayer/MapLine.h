// MapLine.h: interface for the CMapLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPLINE_H__3A368EAD_697B_48BD_A9DA_34D53CBBE7AC__INCLUDED_)
#define AFX_MAPLINE_H__3A368EAD_697B_48BD_A9DA_34D53CBBE7AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
class CMapDisp;
class CMapLine  
{
public:
	CMapLine();
	virtual ~CMapLine();
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
	//�õ��ڼ�������Ϣ
	bool GetMapPoint( int index, MapPoint& mapPoint );
	//�õ������б�
	vector<MapPoint*>* GetMapPoint(){return &m_arrPoint;};
	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp );
	//����������
	void SetLineName(string strName);
	//
	bool IsPointIn( VOSPoint point );
public:
	long	m_lineid;
	vector<MapPoint*>	m_arrPoint;
	long m_color;
	long m_width;
	string m_strname;
	VOSRect		m_rc;
	bool	m_bVisible;
};

#endif // !defined(AFX_MAPLINE_H__3A368EAD_697B_48BD_A9DA_34D53CBBE7AC__INCLUDED_)
