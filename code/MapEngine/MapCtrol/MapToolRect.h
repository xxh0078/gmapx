// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MAP_TOOL_RECT_)
#define _MAP_TOOL_RECT_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolRect  
{
public:
	CMapToolRect();
	virtual ~CMapToolRect();
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapDisp* pMapDisp,string strFilename, CVOSImage* pImageDel );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//��ʼ����
	void OnStart();
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
private:
	//��ͼ��ʾ
	CMapDisp*	m_pMapDisp;
	//--
	VOSPoint	m_ptMouse;
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;
	//VOSPoint m_pntMouse;
	//--
	bool		m_bActive;			//�Ƿ񼤻��
	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;
public:
	//0Ϊ��Ч��1Ϊ�ȴ�������㣬2Ϊ�ȴ������յ㣬3Ϊ�����յ����
	int			m_iState;
	CVOSImage	m_Image;
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
