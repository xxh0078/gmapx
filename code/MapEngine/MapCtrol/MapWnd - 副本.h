#pragma once

#include "MapButton.h"
class CMapWnd
{
public:
	CMapWnd(void);
	~CMapWnd(void);
	//��������
	void Create( HWND hWnd );
	//����
	void OnDraw( HDC hdc );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//void OnMoveOut();

	//��ӿؼ�
	void AddChild( CMapCtrol* pCtrol );

	//�õ��ؼ�
	CMapCtrol* GetCtrol( int nID );
	
	//ˢ����Ļ
	void Invalidate();
	//������Ϣ
	bool PostMessage( int nMessage,long lParam1, long lParam2 );
	//����
	virtual void OnCommand( int id, int param1,int param2 ); 
private:
	//����CtrlButton��׼λ�� 
	void SetBasePos( long left, long top );
private:
	vector<CMapCtrol*>	m_arrMapCtrol;
	CMapCtrol*			m_pLastCtrol;//��ǰ��ť
	CMapCtrol*			m_pCtrolMouseIn;//�������İ�ť
	HWND				m_hWnd;
};
