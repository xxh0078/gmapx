#pragma once
#include "MapDataDown.h"
#include "../MapLayer/MapLeyerMan.h"
#include "MapDispLayer.h"
#include "../MapBase/MapUtil.h"
#define _EXTERND_WIDTH_HEIGHT_ 
class CMapDisp
{
public:
	CMapDisp(void);
	~CMapDisp(void);
public:
	//��ʼ��
	void Init( HWND hwnd, HDC dcEngine, string strRootPath, en_MapType eMapType = GMAP_GOOGLE_MAP );
	//���õ�ͼ���� 
	void SetMapType( string strRoot, en_MapType eMapType, string strMapName = "", string strMapURL = "" );
	//���ñ��ص�ͼ·��
	void SetMapPath( string strMapPath );
	//���ø���ͼ��·��
	void OpenAddMapLayerPath( string strMapFilesPath );
	//�رո��Ӳ�
	void CloseAddMapLayer( );
	//��ͼ�ƶ�,����ƫ����
	void OnMoveMap( int iDx, int iDy );
	//��ͼ�Ŵ�
	void MapZoomIn( VOSPoint pt );
	void MapZoomIn();
	//��ͼ��С
	void MapZoomOut();
	//��ͼ��С
	void MapZoomOut( VOSPoint pt );

	//���Ƶ�ͼ
	void DrawMap( HDC hdc );
	//���Ƶ�ͼ
	void DrawMap2StretchDC();
	//���ڴ�С�ı��¼�
	void OnSize( int cx, int cy );
	//�����Ϣ
	void OnLButtonDown( VOSPoint point );
	void OnLButtonUp( VOSPoint point);
	void OnMouseMove( VOSPoint point);
	BOOL OnMouseWheel( short zDelta, VOSPoint pt);
	void OnLButtonDblClk( VOSPoint point );
	//�����ص�ʱ��
	void OnDownload( tDownLoadParam* param );
	void OnMapMove( VOSPoint point );
	void OnMapMove( int iDx, int iDy );
	//void OnMapZoomIn( int iZoomLevel,CPoint pt );
	//	void OnMapZoomOut( int iZoomLevel,CPoint pt );

	void OnMapZoomIn( );
	void OnMapZoomOut( );
	void OnMapZoom();
	void OnKillFocus();
	//
	void OnTimer( unsigned int nIDEvent);
	//ˢ����Ļ
	void Invalidate();
	//
	void realse();
public:
	//�ƶ���ͼ��ָ���ĵ�
	void MoveMap( MapPoint mpt );

	//�ƶ���ͼ��ָ���ĵ�
	void MoveMap( MapPoint mpt,long level );

	//���õ�ͼ������
	void SetMapLevel( long level);

	//�ƶ���ͼ��һ������Χ
	void MoveMapBound( double x1, double y1, double x2, double y2 );
	//�õ���ͼ������
	long GetMapLevel();

	//���õ�ͼĬ��λ��
	void SetMapDefault();

	//�õ���ͼ���ߵ�����
	void GetMapCenter( MapPoint& mpt );
	
	//��ͼ����ת��Ϊ��Ļ����
	void MapToScreen( MapPoint mpt, VOSPoint& pt );

	//��Ļ����ת��Ϊ��ͼ����
	void ScreenToMap( VOSPoint pt, MapPoint& mpt );

	//�õ�MapBound
	MapBount*	GetMapBound();

	//��������Ƿ�����Ļ��
	bool IsMapPointInMapCreen( MapPoint pt );
	//��ȡ��ʾͼ��
	CMapDispLayer* GetMapDispLayer( int iMapID );

	//������Ϣ
	void PostMessageEx( unsigned long message,unsigned long param1, unsigned long param2 );

	//ע�����
	long RegisterKey(char* strRegisterKey);
	//���ñ�����
	void SetMapScaleBound(long minscale, long maxscale);
private:

	//����MapBound
	void SetMapBound();

	//����MapBound
	void SetMapBound( MapPoint ptlt, MapPoint ptrb );

	//���ƹ��
	//void DrawCursor(CDC* pDC, CPoint pt, float fZoom );

	//����ͼ�Ƿ���磬����ĸ��ĵ���ȷλ��
	bool CheckAndSetMapCenter();

	//��õ�ͼ���ĵ�����
	MPoint* GetMapCenter();
	
private:
	bool			m_bFlagMoveMap;
	bool			m_bMapAutoMove;
	bool			m_bFlagMoveLayerPoint;
	tagZoomParam	m_ZoomParam;
	VOSPoint		m_pntStart;
	VOSPoint		m_pntSpeed;
	int				m_iSpeedX;
	int				m_iSpeedY;

	long			m_ulSpeedTickCount;	
	long			m_lMapMoveTickCount;
	//CBitmap*		m_bitmap;
	HBITMAP			m_bitmap;
	HDC				m_memDC;
	//CDC*			m_memDC;

	//	CBitmap*		m_bitmapStretch;
	HBITMAP			m_bitmapStretch;
	HDC				m_memDCStretch;
	//	CDC*			m_memDCStretch;
	//MPoint			m_gptMapCenter;
	MPoint			m_MapCenter20;
	
	//	CDownLoad		m_download;
	//CWnd*			m_pWnd;
	HPEN			m_penBg;
	HBRUSH			m_brushBg;
	HDC				m_dcEngine;

//	bool			m_bCanUsed;//ʹ������
	HBRUSH			m_hbr;

	BITMAPINFO		bmp_info;
	agg::rendering_buffer m_rbuf; // 32λλͼ��ÿ���ֽ���Ϊwidth*4��
public:
	CMapLeyerMan	m_MapLayerMan;			// ��ͼͼ�������
	CMapDispLayer	m_MapDispLayer;			// ��ͼ��ʾͼ�����
	CMapDispLayer*	m_pMapDispLayerMark;	// ����ͼ��,�ȸ�Ӱ��ͼ��ʱ��Ŵ���
	VOSRect			m_rcWnd;
	int				m_iLevel;
	HWND			m_hwnd;
	en_MapType	    m_enMapType;
	MapBount		m_MapBound;
	long			m_maxLevel;		//��������
	long			m_minLevel;		//��С������
	HCURSOR			m_hCursor;		//���ι��
	//CMapActive		m_MapActive;
};
