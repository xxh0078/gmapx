// MarkMapPoint.h: interface for the CMarkMapPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKMAPPOINT_H__D7AC02DD_CF1E_4A49_B8C0_E85D54D38373__INCLUDED_)
#define AFX_MARKMAPPOINT_H__D7AC02DD_CF1E_4A49_B8C0_E85D54D38373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMarkMapPoint  
{
public:
	CMarkMapPoint();
	virtual ~CMarkMapPoint();
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapDisp* pMapDisp, char* strPath );
	//����
	void OnDraw( HDC hdc );
	
	//��ǵ�ͼ
	void SetMark( bool bMark = true );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//
private:
	//��ͼ��ʾ
	CMapDisp*	m_pMapDisp;
	VOSPoint    m_ptMouse;
	MapPoint	m_mptPoint;
	CVOSImage	m_ImageMark;
	CVOSImage	m_ImageDel;
	VOSRect		m_rectDel;
	bool        m_bMark;		//���
	bool		m_bStart;
};

#endif // !defined(AFX_MARKMAPPOINT_H__D7AC02DD_CF1E_4A49_B8C0_E85D54D38373__INCLUDED_)
