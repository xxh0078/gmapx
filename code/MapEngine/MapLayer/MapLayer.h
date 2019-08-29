#pragma once
#include "MapPoi.h"
#include "MapPoint.h"
#include "MapLine.h"
#include "MapAround.h"
#include "MapText.h"
#include "MapPolygon.h"
#define _MAX_MAP_POIT 1024
class VOS_EXPORT CMapLayer
{
public:
	CMapLayer(void);
	~CMapLayer(void);
public:
	//���������
	bool CreatMapPoint( long pointid );
	bool CreatMapPoint( long pointid, double x, double y, string strName, string strText, short icoID );
	void SetMapPointTextColor( long pointID,long color );
	void SetMapPointTextOffset( long pointID,int x, int y);
	bool SetMapPointAngle( long pointID, long lAngle );
	//�����߶���
	bool CreatMapLine(short lineID );
	bool AddMapLinePoint( short lineID, MapPoint* pPoint );
	bool SetMapLineName( short lineID, string name );
	bool SetMapLineColor( short lineID, long lineColor );
	bool SetMapLineWidth( short lineID, long lineWidth );
	bool SetMapLineVisible( long lineID, long lVisible );
	//ɾ��ȫ��
	void RemoveAll();
	//����
	void OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp,CMapPoiRes* pMapPoiRes );
	void OnDrawTip( HDC hdc,CMapDisp* pMapDisp );
	//���
	bool IsPointIn( VOSPoint point,  CMapPoi*& poi );
	bool IsPointInDel( VOSPoint point,  int& type, int& id );
	bool IsPointIn( VOSPoint point );
	//�����Ƿ���ʾ
	void SetVisible( bool bVisible );
	//�����Ƿ���ʾ
	bool GetVisible( );

	//ͼ��ID
	void SetLayerID( long lID );
	//�õ�ͼ��ID
	long GetLayerID( );

	//�õ����ID�ĵ�
	CMapPoi* GetMapPoi( long lid );
	//ɾ��һ����
	bool DeleteMapPoint(long pointID);
	//ɾ��ȫ������Ϣ
	void DeleteAllMapPoint();
	//ɾ��һ����
	bool DeleteMapLine(long lineID);
	//����POI����
	void DrawPoiText( long pointID, CMapDisp* pMapDisp );

	//���ư�Բ
	bool CreateMapAround( long uid, double x, double y, long radius, long alpha );
	long SetMapAroundColor(long rid, long colorbgr);
	bool DeleteMapAround( long uid );
	//��������
	bool CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color = RGB(0,0,0));
	bool DeleteMapText(long tid);
	//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
	//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
	//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);

	//��������ζ���
	bool CreatMapPolygon(short polygonID );
	//��ӵ�
	bool AddMapPolygonPoint( short polygonID, MapPoint* pPoint );
	//ɾ������ζ���
	bool DeleteMapPolygon(short polygonID);
	//
	CMapLine* GetMapLine(short lid);
	CMapPolygon* GetMapPolygon(short pid);

	//���õ�ͼ�ɱ༭
	long OpenMapEdit( long type, long id, bool bedit);
	//���ö��������
	long SetMapPolygonName(long pid, const char* name );
	//���ö������ɫ
	long SetMapPolygonColor(long pid, long colorbgr);
	//����Բ����
	void SetMapAroundName(long rid, const char* name );
protected:
	//CArray<CMapPoi*,CMapPoi*> m_arrPoi;
	list<CMapPoi*> m_arrPoi;
	list<CMapLine*> m_arrLine;
	list<CMapPolygon*> m_arrPolygon;
	list<CMapAround*> m_arrAround;
	list<CMapText*> m_arrMapText;
	HBRUSH		m_brushFont;
	bool		m_bVisible;
	long		m_llayerID;
};
