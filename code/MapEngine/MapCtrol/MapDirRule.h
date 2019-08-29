// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
#define AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapDirRule  
{
public:
	CMapDirRule();
	virtual ~CMapDirRule();
	//初始化资源文件根目录
	bool Init( CMapDisp* pMapDisp );
	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//开始设置
	void OnStart();
	//结束设置
	void OnEnd();
	//结束设置
	void OnStop();
	//设置起点
	bool SetStartPoint(VOSPoint point);
	//设置起点
	bool SetEndPoint(VOSPoint point);
	//设置当前鼠标点
	void SetMousePoint( VOSPoint point );
	//绘制
	void OnDraw( HDC hdc );
	//0为无效，1为等待设置起点，2为等待设置终点，3为设置终点结束
	int  GetState();
private:
	//地图显示
	CMapDisp*	m_pMapDisp;
	MapPoint m_mptStart;
	MapPoint m_mptEnd;
	//
	VOSPoint m_pntMouse;
	long	 m_lMapLength;
	long	 m_lDirection;	//方向
public:
	bool	m_bActive;			//激活
	//0为无效，1为等待设置起点，2为等待设置终点，3为设置终点结束
	int		m_iState;
	
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
