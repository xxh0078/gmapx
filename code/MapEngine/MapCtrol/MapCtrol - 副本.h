#pragma once
#include "../VOSBase/VOSBase.h"
class CMapWnd;
class CMapCtrol
{
public:
	CMapCtrol(void);
	~CMapCtrol(void);
	//�����ؼ�
	void Create( int nID,CMapWnd* pParent );
	void Create( int nID,int nLeft,int nTop,int nRight,int nBottom, CMapWnd* pParent );
	//��������
	virtual bool IsPointIn( VOSPoint point );
	//���ư�ť
	virtual void OnDraw( HDC hdc ){};
	//�����Ϣ
	virtual bool OnLButtonDown( VOSPoint point ){return false;};
	virtual bool OnLButtonUp( VOSPoint point){return false;};
	virtual bool OnMouseMove( VOSPoint point){return false;};
	virtual bool OnLButtonDblClk( VOSPoint point ){return false;};
	virtual bool OnMouseWheel( short zDelta, VOSPoint pt){return false;};

	virtual void OnMouseMoveIn( ){ };
	virtual void OnMouseMoveOut( ){ };

	//����ID
	void SetID( int nID ){ m_nID = nID;};
	int GetID(){return m_nID;};
protected:
	VOSRect		m_rect;
	long		m_nID;
	CMapWnd*	m_pParent;
};
