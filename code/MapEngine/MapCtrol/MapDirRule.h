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
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapDisp* pMapDisp );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//��ʼ����
	void OnStart();
	//��������
	void OnEnd();
	//��������
	void OnStop();
	//�������
	bool SetStartPoint(VOSPoint point);
	//�������
	bool SetEndPoint(VOSPoint point);
	//���õ�ǰ����
	void SetMousePoint( VOSPoint point );
	//����
	void OnDraw( HDC hdc );
	//0Ϊ��Ч��1Ϊ�ȴ�������㣬2Ϊ�ȴ������յ㣬3Ϊ�����յ����
	int  GetState();
private:
	//��ͼ��ʾ
	CMapDisp*	m_pMapDisp;
	MapPoint m_mptStart;
	MapPoint m_mptEnd;
	//
	VOSPoint m_pntMouse;
	long	 m_lMapLength;
	long	 m_lDirection;	//����
public:
	bool	m_bActive;			//����
	//0Ϊ��Ч��1Ϊ�ȴ�������㣬2Ϊ�ȴ������յ㣬3Ϊ�����յ����
	int		m_iState;
	
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
