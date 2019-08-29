// MapLeyerMan.h: interface for the CMapLeyerMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_)
#define AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "../MapDisp/MapDisp.h"
//#include "MapPoiRes.h"
#include "MapLayer.h"
#include "BackLayer.h"
#include "MapPoiInfo.h"
#define _MAX_MAP_LAYER_ 2
class CMapLeyerMan  
{
public:
	CMapLeyerMan();
	virtual ~CMapLeyerMan();

	//��ʼ��
	bool Init( CMapDisp* pMapDisp, string strRootPath );
	void Realse();
	//���ͼ��
	long AddMapLayer( CMapLayer* pMapLayer );

	//ɾ��ͼ��
	bool DeleteMapLayer( int nID );

	//����ͼ���Ƿ���ʾ
	bool SetMapLayerVisible( int nID, bool bVisible );

	//ɾ��ͼ��
	void DeleteMapLayer( CMapLayer* pMapLayer );

	//���Ϳ���
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID );

	//���Ϳ���
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName );

	//ɾ��ȫ��ͼ��
	void ClearAllMapLayer();

	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf );

	//������Դ������Ǳ��صģ���ֱ�Ӽ��أ�����Ƿ������ģ���Ϊurl��url��http��ͷ
	long CreateRes( string strpath );
	//���������
	bool CreatMapPoint(long id );
	bool CreatMapPoint( long pointid, double x, double y, string strName, string strText, long icoID );
	bool SetMapPoint(long pointID, double x, double y);
	bool SetMapPointName(long pointID, string name );
	bool SetMapPointText(long pointID, string text );
	void SetMapPointTextColor( long pointID,long color );
	void SetMapPointTextOffset( long pointID,int x, int y);
	bool SetMapPointAngle( long pointID, long lAngle );

	bool SetMapPointICO(long pointID, long icoid );
	bool DeleteMapPoint(long pointID);
	//ɾ��ȫ������Ϣ
	void DeleteAllMapPoint();
	//�����߶���
	bool CreatMapLine(long lineID );
	bool AddMapLinePoint( long lineID, double x, double y);
	bool AddMapLinePoint( long lineID, MapPoint Point );
	bool SetMapLineName( long lineID, string name );
	bool SetMapLineColor( long lineID, long lineColor );
	bool SetMapLineWidth( long lineID, long lineWidth );
	bool SetMapLineVisible( long lineID, long lVisible );
	bool DeleteLine(long lineID);

	//��������ζ���
	bool CreatMapPolygon(long polygonID );
	//��ӵ�
	bool AddMapPolygonPoint( long polygonID, double x, double y );
	//ɾ������ζ���
	bool DeleteMapPolygon(long polygonID);

	//���ư�Բ
	void CreateMapAround( long uid, double x, double y, long radius, long alpha );
	long SetMapAroundColor(long rid, long colorgbr);
	void DeleteMapAround( long uid );
	//��������
	void CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color);
	void DeleteMapText(long tid);
	//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
	//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
	//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	
	//��Ӧ����ƶ��¼�
//	bool IsPointIn( VOSPoint point );

	//�����������Ƿ����ͼ�㣬������У�����Ƿ��ǣ��Ƿ���poiid�����ǣ�����poidΪ-1
	//bool OnClick( VOSPoint point, CMapPoi*& poi );
	//�����Ƿ���poi����
	bool IsPointIn( VOSPoint point, CMapPoi*& poi );

	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);
	bool OnMouseWheel( short zDelta, VOSPoint pt);
	bool OnLButtonDblClk( VOSPoint point );

	//��ӵ�ͼ��Ϣ��
	bool SaveLocMapPoint( double x, double y, string strName, string strText, long icoID );
	//��ӵ�ͼ��,
	bool SaveLocMapLine( string strMapPoints, string strName, long width, long bgrcolor  );
	//��ӵ�ͼ�ı���Ϣ
	bool SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor );
	//�����ͼ������Ϣ
	bool ClearLocMapData();
	//ɾ��һ����
	bool DeleteLocMapPoint(long pointID);
	//ɾ��һ����
	bool DeleteLocMapLine(long lineID);
	//�õ���ǰλ�õ���ϢID,0Ϊ�����ݣ�1Ϊ����Ϣ��2Ϊ����Ϣ
	int GetLocID( long& lID, VOSPoint point );
	//���õ�ͼ�ɱ༭
	long OpenMapEdit(long type, long id, bool bedit);
	//���ö��������
	long SetMapPolygonName(long pid, const char* name  );
	//���ö������ɫ
	long SetMapPolygonColor(long pid, long colorbgr);
	//����Բ����
	void SetMapAroundName(long rid, const char* name );
public:
	CBackLayer	m_backLayer;
	CMapPoiRes	m_MapPoiRes;
private:
	CMapDisp*	m_pMapDisp;
	vector<CMapLayer*>	m_arrMapLayers;
	CMapPoiInfo	m_MapPoiInfo;
	CMapLayer	m_userLayer;
	long		m_lmaxID;
	HCURSOR		m_hCursor;		//���ι��
	
	CMapPoi*	m_pLastPoi;
	bool		m_bDown;
public:
	CMapLayer	m_ToolsLayer;
	CVOSImage	m_ImageBk;
};

#endif // !defined(AFX_MAPLEYERMAN_H__B1521279_08E2_408D_8ED6_8FD5ED3B06AD__INCLUDED_)
