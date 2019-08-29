// MapDirRule.h: interface for the CMapToolLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CMAPTOOLLINE)
#define CMAPTOOLLINE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolLine
{
public:
	CMapToolLine();
	virtual ~CMapToolLine();
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapDisp* pMapDisp, CMapLayer* pMapLayer, CVOSImage* pImageDel );

	//����߹���
	void SetActive( bool bActive );
	//����
	void OnDraw( HDC hdc );

	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//��������
	void Create();
	//��ӻ��ߵ�
	void AddPoint( VOSPoint point );

	//��������״̬�������������Ϣ
	void End();

	//�������Ϣ
	void Clean();
	//����
	void Save();
private:
	CMapDisp*	m_pMapDisp;
	CMapLayer*  m_pMapLayer;
	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;
	//��ͼ���ߴ���
	short		m_lineID;
	MapPoint*   m_pMapPoint;
	CMapLine*	m_pMapLine;

	int			m_iFlag;	//0δ���� 1��ʼ׼������ 2 �Ѿ�����1���� 3 ���߽���

	VOSPoint    m_ptMouse;
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;
	int			m_iCount;		//������
	double		m_dLength;		//����
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
