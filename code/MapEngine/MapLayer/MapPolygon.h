// MapPolygon.h: interface for the CMapPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOLYGON_H__2B31638E_C3A9_46D2_ACDA_96DEB88EBDF3__INCLUDED_)
#define AFX_MAPPOLYGON_H__2B31638E_C3A9_46D2_ACDA_96DEB88EBDF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
class CMapDisp;
class CMapPolygon  
{
public:
	CMapPolygon();
	virtual ~CMapPolygon();
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
	//����������
	void SetName(string strName);
	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* rbuf, CMapDisp* pMapDisp );
public:
	long	m_polygonID;
	vector<MapPoint*>	m_arrPoint;
	long m_color;
	long m_width;
	string m_strname;
	VOSRect		m_rc;
	bool	m_bVisible;
};

#endif // !defined(AFX_MAPPOLYGON_H__2B31638E_C3A9_46D2_ACDA_96DEB88EBDF3__INCLUDED_)
