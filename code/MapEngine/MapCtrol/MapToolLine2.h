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
	bool Init( CMapDisp* pMapDisp );
	//绘制
	void OnDraw( HDC hdc );

	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//0为无效或者清空，1开始画线 2 正在添加点 3画线结束 4 清除线信息
	int  GetState();
	//创建画线
	void Create( CMapLayer* pMapLayer );
	//添加画线点
	void AddPoint( VOSPoint point );

	//结束画线状态，但不清楚线信息
	void End();

	//清除线信息
	void Clean();
	//得到点数据
	void GetPointsText( string& strlon,string&  strlan );
private:
	CMapDisp* m_pMapDisp;
	//0为无效或者清空，1开始画线 2 正在添加点 3画线结束 4 清除线信息
	int			m_iState;
	//地图工具处理
	int			m_iCount;//点数量
	short		m_lineID;
	long		m_lTextID;
	double		m_dLength;
	string		m_strlon;
	string		m_strlan;
	MapPoint*   m_pMapPoint;
	CMapLine*	m_pMapLine;
	CMapLayer*  m_pMapLayer;

	VOSPoint   m_pntLast;		//最后一次添加的点信息
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
