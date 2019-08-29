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
	//绘制
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
