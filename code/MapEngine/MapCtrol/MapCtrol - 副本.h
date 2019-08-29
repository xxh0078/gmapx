#pragma once
#include "../VOSBase/VOSBase.h"
class CMapWnd;
class CMapCtrol
{
public:
	CMapCtrol(void);
	~CMapCtrol(void);
	//创建控件
	void Create( int nID,CMapWnd* pParent );
	void Create( int nID,int nLeft,int nTop,int nRight,int nBottom, CMapWnd* pParent );
	//单击属性
	virtual bool IsPointIn( VOSPoint point );
	//绘制按钮
	virtual void OnDraw( HDC hdc ){};
	//鼠标消息
	virtual bool OnLButtonDown( VOSPoint point ){return false;};
	virtual bool OnLButtonUp( VOSPoint point){return false;};
	virtual bool OnMouseMove( VOSPoint point){return false;};
	virtual bool OnLButtonDblClk( VOSPoint point ){return false;};
	virtual bool OnMouseWheel( short zDelta, VOSPoint pt){return false;};

	virtual void OnMouseMoveIn( ){ };
	virtual void OnMouseMoveOut( ){ };

	//设置ID
	void SetID( int nID ){ m_nID = nID;};
	int GetID(){return m_nID;};
protected:
	VOSRect		m_rect;
	long		m_nID;
	CMapWnd*	m_pParent;
};
