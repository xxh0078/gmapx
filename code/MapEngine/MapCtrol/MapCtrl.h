#pragma once
#include "MapWnd.h"
#include "MapButton.h"
#include "SlideButton.h"
#include "UrlLink.h"
#include "../MapDisp/MapDisp.h"
//#include "../MapEngine.h"
#include "MapDirRule.h"
#include "MapSymbolEdit.h"
#include "MapToolLine.h"
#include "MapToolPolygon.h"
#include "MapToolRect.h"
#include "MapToolAround.h"
#include "MarkMapPoint.h"
class CMapEngine;
class CMapCtrl : public CMapWnd
{
public:
	CMapCtrl(void);
	~CMapCtrl(void);
	//��ʼ����Դ�ļ���Ŀ¼
	bool Init( CMapEngine* pMapEngine, vchar* pRootPath, HWND hwnd , long left, long top );
	//����rc
	void SetMapRect( VOSRect& rcWnd );
	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* rbuf  );
	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnLButtonDblClk( VOSPoint point );
	bool OnMouseWheel( short zDelta, VOSPoint point);
	//
	void CheckAndSetMapLevel( VOSPoint point );
	void OnMoveOut();

	//���õ�ͼ���ߣ���ͼ���� 1Ϊ������ 2Ϊ���ߣ�3Ϊ������Σ�4Ϊ������,5Ϊ��԰,6Ϊ��ǵ�
	bool SetMapTools(long MapToolType);
	//�����ͼ�����Լ��������ĵ�ͼ
	void ClearMapTools();
	//�Ƿ���ʾ
	void SetMapToolsBar( bool bShow );
	//���ñ�����
	void SetMapScaleBound(long minscale, long maxscale);

	//����
	void OnCommand( int id, int param1,int param2 );

	//��ͼ���Ź���
	void OnMapZoom( ); 
	//���湤��
	void SaveMap();
	//
	void SetVisible( bool bVisible );
	void SetVisible1( bool bVisible );
private:
	//����CtrlButton��׼λ�� 
	void SetBasePos( long left, long top );
private:
	CMapEngine* m_pMapEngine;
	//��ͼ��ʾ
	CMapDisp*	m_pMapDisp;
	//�ؼ�
	CMapButton	m_btnLeft;
	CMapButton	m_btnRight;
	CMapButton	m_btnUp;
	CMapButton	m_btnDown;
	//CMapButton	m_btnCenter;
	CMapButton	m_btnZoomIn;
	CMapButton	m_btnZoomOut;
	CSlideButton	m_btnZoomBk;
//	CMapButton	m_btnZoomMove;
	//��๤��
	CMapButton	m_btnRule;
//	CMapButton	m_btnMapRect;
//	CMapButton	m_btnLine;
//	CMapButton	m_btnPolygon;
//	CMapButton	m_btnSymbol;
	CMapButton	m_btnClean;
//	CMapButton	m_btnMapSat;

#ifdef GMAP_VIEW_QQ
	CUrlLink	m_urlDemo;
#endif
#ifdef GMAP_VIEW_URL
	CUrlLink	m_urlCopyRight;
//	CMapButton	m_btnCopyRight;
#endif
	//�϶�
	long		m_left;
	long		m_top;
	long		m_interval;		//λ�ü��
	VOSRect*	m_pRectBk;		//������������
	long		m_level;		//������
	long		m_maxLevel;		//��������
	long		m_minLevel;		//��С������
	bool		m_flagMove;
	//
	
	//
	VOSRect		m_rcWnd;
//	CArray<CMapButton*,CMapButton*> m_ArrMapCtrl;
	CMapLayer*  m_pMapLayer;
//	long		m_lLayerID;
	long		m_lLineIDRule;	//����߱��
	//���߱�־,0���޹���״̬��1�������๤��,2�����ߣ�2�������
	int				m_iFlagTools;
	CMapDirRule		m_mapDirRule;
	VOSPoint		m_pntMouse;

//	bool			m_bMapSat;		//�Ƿ������ǵ�ͼ
public:
	CMapToolLine	m_MapToolLine;
	CMapToolPolygon m_MapToolPolygon;
	CMapToolRect	m_MapToolRect;
	CMapToolAround	m_MapToolAround;
	CMapButton*		m_pButtonCurr;
	//CVOSImage		m_ImageMark;
	CMarkMapPoint	m_MarkMapPoint;
	CVOSImage		m_ImageDel;

	bool			m_bVisible;
	bool			m_bVisible1;
};