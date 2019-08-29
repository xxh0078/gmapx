// MapDirRule.h: interface for the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(CMAPTOOLPOLYGON)
#define CMAPTOOLPOLYGON

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
#include "../MapDisp/MapDisp.h"
class CMapToolPolygon
{
public:
	CMapToolPolygon();
	virtual ~CMapToolPolygon();
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapDisp* pMapDisp,CMapLayer* pMapLayer, CVOSImage* pImageDel );

	//����߹���
	void SetActive( bool bActive = true );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//����
	void OnDraw( HDC hdc );

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
	//�����Ƿ��ڶ���ͷ�Χ��
	bool IsInMapToolsPolygon(double dLon, double dLan );
private:
	CMapDisp* m_pMapDisp;
	CMapPolygon* m_pMapPolygon;
	CMapLayer*  m_pMapLayer;
//	CVOSImage*	m_pImageDel;
	VOSRect		m_rectDel;

	//0Ϊ��Ч������գ�1��ʼ���� 2 ������ӵ� 3���߽��� 4 �������Ϣ
	////0δ���� 1��ʼ׼������ 2 �Ѿ�����1���� 3 ���߽���
	int			m_iFlag;
	//��ͼ���ߴ���
	int			m_iCount;//������
	int			m_PolygonlD;

	VOSPoint    m_ptMouse;		//���λ��
	MapPoint	m_mptMouse;
	MapPoint	m_mptLast;
	//-
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
