// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MAP_TOOL_AROUND_)
#define _MAP_TOOL_AROUND_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolAround 
{
public:
	CMapToolAround();
	virtual ~CMapToolAround();
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
	void OnDraw( HDC hdc,agg::rendering_buffer* rbuf );

private:
	//��ͼ��ʾ
	CMapDisp*	m_pMapDisp;
	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;
	//
	VOSPoint	m_ptMouse;
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;

	bool		m_bActive;			//�Ƿ񼤻��
	
public:
	//0Ϊ��Ч��1Ϊ�ȴ�������㣬2Ϊ�ȴ������յ㣬3Ϊ�����յ����
	int			m_iState;
	CVOSImage	m_Image;
	
};

#endif // !defined(_MAP_TOOL_AROUND_)
