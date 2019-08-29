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
	bool Init( CMapDisp* pMapDisp );
	//����
	void OnDraw( HDC hdc );

	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);

	//0Ϊ��Ч������գ�1��ʼ���� 2 ������ӵ� 3���߽��� 4 �������Ϣ
	int  GetState();
	//��������
	void Create( CMapLayer* pMapLayer );
	//��ӻ��ߵ�
	void AddPoint( VOSPoint point );

	//��������״̬�������������Ϣ
	void End();

	//�������Ϣ
	void Clean();
	//�õ�������
	void GetPointsText( string& strlon,string&  strlan );
private:
	CMapDisp* m_pMapDisp;
	//0Ϊ��Ч������գ�1��ʼ���� 2 ������ӵ� 3���߽��� 4 �������Ϣ
	int			m_iState;
	//��ͼ���ߴ���
	int			m_iCount;//������
	short		m_lineID;
	long		m_lTextID;
	double		m_dLength;
	string		m_strlon;
	string		m_strlan;
	MapPoint*   m_pMapPoint;
	CMapLine*	m_pMapLine;
	CMapLayer*  m_pMapLayer;

	VOSPoint   m_pntLast;		//���һ����ӵĵ���Ϣ
};

#endif // !defined(AFX_MAPDIRRULE_H__9168D138_0A2F_4902_AEE0_18795CD4E5FC__INCLUDED_)
