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
	//绘制
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp );
	//设置线名字
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
