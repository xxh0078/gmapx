// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CMAPTOOLPOLYGON)
#define CMAPTOOLPOLYGON

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolPolygon
{
public:
	CMapToolPolygon();
	virtual ~CMapToolPolygon();
	//初始化资源文件根目录
	bool Init( CMapDisp* pMapDisp,CMapLayer* pMapLayer, CVOSImage* pImageDel );

	//激活画线工具
	void SetActive( bool bActive = true );
	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//绘制
	void OnDraw( HDC hdc );

	//创建画线
	void Create();
	//添加画线点
	void AddPoint( VOSPoint point );

	//结束画线状态，但不清楚线信息
	void End();

	//清除线信息
	void Clean();
	//保存
	void Save();
	//检测点是否在多变型范围内
	bool IsInMapToolsPolygon(double dLon, double dLan );
private:
	CMapDisp* m_pMapDisp;
	CMapPolygon* m_pMapPolygon;
	CMapLayer*  m_pMapLayer;
//	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;

	//0为无效或者清空，1开始画线 2 正在添加点 3画线结束 4 清除线信息
	////0未画线 1开始准备画线 2 已经画了1个点 3 画线结束
	int			m_iFlag;
	//地图工具处理
	int			m_iCount;//点数量
	int			m_PolygonlD;

	VOSPoint    m_ptMouse;		//鼠标位置
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;
	//-
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
