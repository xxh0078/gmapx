#pragma once
#include "../VOSBase/VOSBase.h"
#include "MapCtrol.h"
class CMapButton : public CMapCtrol
{
public:
	CMapButton(void);
	~CMapButton(void);
	//初始化
	void Create( int nID,vchar* pRootPath, vchar* pFileName,  long left, long top,CMapWnd* pParent );
	void Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,  long left, long top,CMapWnd* pParent );
	//重新设置位置
	void ReSetPos( long left, long top );
	//单击属性
	virtual bool IsPointIn( VOSPoint point );
	//绘制按钮
	virtual void OnDraw( HDC hdc );
	void OnDrawSel( HDC hdc );
	//绘制半透明按钮
	void OnDrawTransparent( HDC hdc );
	//得到bound
	VOSRect* GetBoundsRect();
	//设置被选择
	void SetSelected( bool bSelected );
	//
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	//鼠标拖动
	bool OnMouseMove( VOSPoint point);
	//鼠标移入移除操作
	virtual void OnMouseMoveIn();
	virtual void OnMouseMoveOut();
protected:
	int			m_iType;
	CVOSImage	m_Image;
	CVOSImage	m_Image1;
	bool		m_bSelected;
};
