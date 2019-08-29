#pragma once
#include "../VOSBase/VOSBase.h"
#include "MapButton.h"
class CSlideButton: public CMapButton
{
public:
	CSlideButton(void);
	~CSlideButton(void);
	void Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,vchar* pFileNameSlide, long left, long top,CMapWnd* pParent );
	//绘制按钮
	virtual void OnDraw( HDC hdc );

	//单击属性
	virtual bool IsPointIn( VOSPoint point );
	//设置被选择
	void SetSlidePos( int nPos,int nCount );

	//得到位置
	int GetSolidePos( int nCount );
	//
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	//鼠标拖动
	bool OnMouseMove( VOSPoint point);
	//鼠标移入移除操作
	virtual void OnMouseMoveIn();
	virtual void OnMouseMoveOut();
private:
	//int		m_nPos;//0-20;
	//int		m_nCount;
	CVOSImage	m_ImageSlide;
	bool	 m_bDraglag;
	int		m_nPoxY;		//滑动条坐标
};
