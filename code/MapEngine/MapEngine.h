#pragma once
#include "VOSBase/VOSDefine.h"
#include "MapBase/MapDefine.h"
#include "MapDisp/MapDisp.h"
#include "MapCtrol/MapCtrl.h"
#include "MapOffSet/MapOffSet.h"
#include "mif/MifMan.h"
//xxh class CGmapxCtrl;
//extern fun_msg g_fun_msg;
class VOS_EXPORT CMapEngine
{
public:
	CMapEngine(void);
	~CMapEngine(void);
public:
	//��ʼ��
	void Init( HWND hwnd );
	//������Ϣ�ص�����
	void SetMsgFun( fun_msg msg );
	//���õ�ͼURL·��
	void SetMapUrl(string strMapURL );
	//���ñ��ص�ͼ�ļ�·��
	void SetMapPath( string strMapPath );
	//���ø���ͼ��·��
	void OpenAddMapLayerPath( string strMapFilesPath );
	//�رո��Ӳ�
	void CloseAddMapLayer( );
	//�ͷ�
	void Destroy();
	//����
	void OnDraw( HDC hdc );
	//���õ�ͼλ��
	void SetMapPos( long left, long top, long width, long height, bool bDraw );
	//�����Ϣ
	void OnLButtonDown( VOSPoint point );
	void OnLButtonUp( VOSPoint point);
	void OnMouseMove( VOSPoint point);
	void OnMouseWheel( short zDelta, VOSPoint point );
	void OnLButtonDblClk( VOSPoint point );

	//�Ƿ�����poi����
	bool IsPointIn( VOSPoint point, CMapPoi*& poi );
	//ʧȥ����
	void OnKillFocus();
	//ontimer
	void OnTimer( unsigned int nIDEvent);
	//��С
	void OnMapZoomIn( );
	//�Ŵ�
	void OnMapZoomOut( );

	/*	���ڵ���Ϣ���� */
	void MsgProc( ULONG ulID, ULONG wParam, ULONG lParam );
	//ˢ����Ļ
	void Invalidate();
	//�����Ƿ��ڵ�ͼ��
	bool IsInMap( VOSPoint point );
	//����mif����
	bool LoadMifMidData( string strFileName );
	//���õ�ͼ��ʾ
	long ShowMapTool(long lType, long lValue);
public:
	//���ͼ��,����ͼ��ID,Ҫ��new�������ͷ�
	long CreateMapLeyer();
	//ɾ��ͼ��
	bool DeleteMapLayer( int nID );
	//ɾ��ȫ��ͼ��
	void DeleteAllMapLayer();
	//���POI��
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID );
	//���POI��
	long AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName );
	//��ͼ����ת��Ϊ��Ļ����
	void MapToScreen( double dMapX, double dMapY, long& lScreenX, long& lScreenY );
	//��Ļ����ת��Ϊ��ͼ����
	void ScreenToMap( long lScreenX, long lScreenY, double& dMapX, double& dMapY );
	//�ƶ���ͼ��
	void MoveMap( double dMapX, double dMapY );
	//�ƶ���ͼ
	void MoveMapBound(double x1, double y1, double x2, double y2);
	//�õ���ͼ���ĵ�����
	void GetMapCenter( double& dMapX, double& dMapY );
	//���õ�ͼ���� 
	void SetMapType( en_MapType eMapType = GMAP_GOOGLE_MAP );
	//������Դ������Ǳ��صģ���ֱ�Ӽ��أ�����Ƿ������ģ���Ϊurl��url��http��ͷ
	long CreateMapRes( string strpath );

	//������
	bool CreateMapPoint( long pointID );
	//������
	bool CreateMapPoint( long pointid, double x, double y, string strName, string strText, long icoID );
	//�����Ƿ��ڵ�ͼ�ϵ�ͼ����ϣ�������ͼ���ID
	long GetMapPoint( VOSPoint point );
	//���õ�λ������
	bool SetMapPoint(long pointID, double x, double y);
	//���õ����ƣ�ֱ����ʾ
	bool SetMapPointName(long pointID, string name );
	//���õ���ʾ�ı�,���������ʾ
	bool SetMapPointText(long pointID, string text );
	//���õ��ͼ��
	bool SetMapPointICO(long pointID, long icoid );
	//ɾ����
	bool DeleteMapPoint(long pointID);
	//ɾ��ȫ������Ϣ
	void DeleteAllMapPoint();
	//�����߶���
	bool CreateMapLine( long lineID );
	//Ϊ����ӵ�
	bool AddMapLinePoint( long lineID, double x, double y );
	//����������
	bool SetMapLineName( long lineID, string name );
	//��������ɫ����ɫֵΪBGR()0xFF0000Ϊ��ɫ,0x00FF00Ϊ��ɫ,0x0000FFΪ��ɫ
	bool SetMapLineColor( long lineID, long lineColor );
	//�����߿��
	bool SetMapLineWidth( long lineID, long lineWidth );
	//ɾ����
	bool DeleteLine(long lineID);

	//��������ζ���
	bool CreateMapPolygon(long polygonID );
	//��ӵ�
	bool AddMapPolygonPoint( long polygonID, double x, double y );
	//���ö��������
	long SetMapPolygonName(long pid, const char* name );
	//���ö������ɫ
	long SetMapPolygonColor(long pid, long colorbgr);
	//ɾ������ζ���
	bool DeleteMapPolygon(long polygonID);

	//�õ�/���õ�ͼ��ʾ������
	long GetMapScale();
	void SetMapScale(long scale);
	//�������ĵ�λ�úͱ�����
	void SetMapParam(double x, double y, long scale);
	//�Զ����ٲ��ƶ���ͼ���ڵ�ͼ�ڲ��ģ����ƶ���ͼ��������ͼ��Χ�ģ��ƶ���ͼ
	void AutoMoveMap(double x, double y);
	//���ư�Բ
	void CreateMapAround( long rid, double x, double y, long radius, long alpha );
	//����Բ����
	void SetMapAroundName(long rid, const char* name);
	long SetMapAroundColor(long rid, long colorbgr);
	void DeleteMapAround( long rid );
	//��������
	void CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color);
	void DeleteMapText(long tid);
	//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
	//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
	//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
	bool SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	//ɾ�����ͼ�?
	void RemoveAllLayer();
	//��������Դ,0Ϊ�ȸ裬7Ϊvirtual earth��8Ϊ��ͼ�������ݲ�֧��
	long SetMapRes(long lres );
	//�ж��Ƿ��ڵ�ͼ��ʾ��Χ��
	bool IsMapPointInMapCreen(double x, double y);
	//���õ�ͼ�ɱ༭
	long OpenMapEdit(long type, long id, bool bedit);
	//���õ�ͼ���ߣ���ͼ���� 1Ϊ������ 2Ϊ���ߣ�3Ϊ������Σ�4Ϊ������,5Ϊ��԰
	bool SetMapTools(long MapToolType);
	//�����ͼ�����Լ��������ĵ�ͼ
	void ClearMapTools();
	//���湤��
	void SaveMapTool();
	//�Ƿ���ʾ��ͼ������
	void SetMapToolsBar( bool bShow );
	//ע�����
	long RegisterKey(char* strRegisterKey);

	//�õ���ͼ�ľ�ƫ����ֵ
	bool GetMapOffSet( double& lon, double& lan );
	void SetMapScaleBound(long minscale, long maxscale);
	//���Ƿ��ڵ�ͼ�Ķ���͹�����
	bool IsInMapToolsPolygon( double dLon, double dLan );
	//���������ѯ��ַ
	string GetMapAddress(double dLon, double dLan);
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
	//�����ͼ
	void SaveMap( const char* strPath );

	long SetMarkFile( const char* strFileName  );
public:
	HWND			m_hwnd;
	CMapCtrl		m_MapCtrl;				//��ͼ���ư�ť
	CMapDisp		m_MapDisp;
private:
	
	VOSRect			m_rect;
	HDC				m_memhdc;
	HBITMAP			m_bitmap;
	string			m_strRootPath;
	long			m_lCount;
	BITMAPINFO		bmp_info;
	void*			m_buf;
	agg::rendering_buffer m_rbuf;			//32λλͼ��ÿ���ֽ���Ϊwidth*4��
	CMapOffSet		m_MapOffSet;			//��ͼ��ƫ
	CMifMan			m_MifMan;
	//CMapPoi*		m_pSelMapPoi;			//��ǰ���������Ϣ��
	HBRUSH			m_hbr;
	CVOSImage		m_ImageMark;
};
