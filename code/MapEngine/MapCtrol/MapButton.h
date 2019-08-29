#pragma once
#include "../VOSBase/VOSBase.h"
#include "MapCtrol.h"
class CMapButton : public CMapCtrol
{
public:
	CMapButton(void);
	~CMapButton(void);
	//��ʼ��
	void Create( int nID,vchar* pRootPath, vchar* pFileName,  long left, long top,CMapWnd* pParent );
	void Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,  long left, long top,CMapWnd* pParent );
	//��������λ��
	void ReSetPos( long left, long top );
	//��������
	virtual bool IsPointIn( VOSPoint point );
	//���ư�ť
	virtual void OnDraw( HDC hdc );
	void OnDrawSel( HDC hdc );
	//���ư�͸����ť
	void OnDrawTransparent( HDC hdc );
	//�õ�bound
	VOSRect* GetBoundsRect();
	//���ñ�ѡ��
	void SetSelected( bool bSelected );
	//
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	//����϶�
	bool OnMouseMove( VOSPoint point);
	//��������Ƴ�����
	virtual void OnMouseMoveIn();
	virtual void OnMouseMoveOut();
protected:
	int			m_iType;
	CVOSImage	m_Image;
	CVOSImage	m_Image1;
	bool		m_bSelected;
};
