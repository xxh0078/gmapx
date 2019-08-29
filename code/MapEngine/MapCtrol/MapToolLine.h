// MapDirRule.h: interface for the CMapToolLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CMAPTOOLLINE)
#define CMAPTOOLLINE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolLine
{
public:
	CMapToolLine();
	virtual ~CMapToolLine();
	//初始化资源文件根目录
	bool Init( CMapDisp* pMapDisp, CMapLayer* pMapLayer, CVOSImage* pImageDel );

	//激活画线工具
	void SetActive( bool bActive );
	//绘制
	void OnDraw( HDC hdc );

	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

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
private:
	CMapDisp*	m_pMapDisp;
	CMapLayer*  m_pMapLayer;
	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;
	//地图工具处理
	short		m_lineID;
	MapPoint*   m_pMapPoint;
	CMapLine*	m_pMapLine;

	int			m_iFlag;	//0未画线 1开始准备画线 2 已经画了1个点 3 画线结束

	VOSPoint    m_ptMouse;
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;
	int			m_iCount;		//点数量
	double		m_dLength;		//长度
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
