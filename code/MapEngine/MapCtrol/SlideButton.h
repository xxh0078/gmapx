#pragma once
#include "../VOSBase/VOSBase.h"
#include "MapButton.h"
class CSlideButton: public CMapButton
{
public:
	CSlideButton(void);
	~CSlideButton(void);
	void Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,vchar* pFileNameSlide, long left, long top,CMapWnd* pParent );
	//���ư�ť
	virtual void OnDraw( HDC hdc );

	//��������
	virtual bool IsPointIn( VOSPoint point );
	//���ñ�ѡ��
	void SetSlidePos( int nPos,int nCount );

	//�õ�λ��
	int GetSolidePos( int nCount );
	//
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	//����϶�
	bool OnMouseMove( VOSPoint point);
	//��������Ƴ�����
	virtual void OnMouseMoveIn();
	virtual void OnMouseMoveOut();
private:
	//int		m_nPos;//0-20;
	//int		m_nCount;
	CVOSImage	m_ImageSlide;
	bool	 m_bDraglag;
	int		m_nPoxY;		//����������
};
