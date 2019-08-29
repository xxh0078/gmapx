#pragma once

#include "MapButton.h"
class CMapWnd
{
public:
	CMapWnd(void);
	~CMapWnd(void);
	//创建窗口
	virtual void Create( HWND hWnd );
	//绘制
	void OnDraw( HDC hdc );
	//鼠标消息
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//添加控件
	void AddChild( CMapCtrol* pCtrol );

	//得到控件
	CMapCtrol* GetCtrol( int nID );
	
	//刷新屏幕
	void Invalidate();
	//发送消息
	bool PostMessage( int nMessage,long lParam1, long lParam2 );
	//命令
	virtual void OnCommand( int id, int param1,int param2 ); 
protected:
	//设置CtrlButton基准位置 
	void SetBasePos( long left, long top );
protected:
	vector<CMapCtrol*>	m_arrMapCtrol;
	CMapCtrol*			m_pLastCtrol;//当前按钮
	CMapCtrol*			m_pCtrolMouseIn;//鼠标移入的按钮
	HWND				m_hWnd;
	HCURSOR				m_hCursor;		//光标
};
