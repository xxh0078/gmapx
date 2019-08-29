// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MAP_TOOL_AROUND_)
#define _MAP_TOOL_AROUND_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolAround 
{
public:
	CMapToolAround();
	virtual ~CMapToolAround();
	//初始化资源文件根目录
	bool Init( CMapDisp* pMapDisp,string strFilename, CVOSImage* pImageDel );
	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//开始设置
	void OnStart();
	//结束设置
	void OnStop();
	//设置起点
	bool SetStartPoint(VOSPoint point);
	//设置起点
	bool SetEndPoint(VOSPoint point);
	//设置当前鼠标点
	void SetMousePoint( VOSPoint point );
	//绘制
	void OnDraw( HDC hdc,agg::rendering_buffer* rbuf );

private:
	//地图显示
	CMapDisp*	m_pMapDisp;
	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;
	//
	VOSPoint	m_ptMouse;
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;

	bool		m_bActive;			//是否激活工具
	
public:
	//0为无效，1为等待设置起点，2为等待设置终点，3为设置终点结束
	int			m_iState;
	CVOSImage	m_Image;
	
};

#endif // !defined(_MAP_TOOL_AROUND_)
