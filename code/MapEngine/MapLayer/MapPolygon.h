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
	//释放内存
	void Realse();

	//添加一个点
	void AddPoint( MapPoint* pPoint );
	//得到总的点数量
	long GetCount();

	//设置线宽度
	void SetColor( long color );
	//设置线的颜色
	void SetWidth( long width );
	//设置是否显示
	void SetVisible(bool visible );
	bool GetVisible();
	//得到第几个点信息
	bool GetMapPoint( int index, MapPoint& mapPoint );
	//得到数据列表
	vector<MapPoint*>* GetMapPoint(){return &m_arrPoint;};
	//设置线名字
	void SetName(string strName);
	//绘制
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
