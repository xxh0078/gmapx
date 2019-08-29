// MapPoi.h: interface for the CMapPoi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_)
#define AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MapPoiRes.h"
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class VOS_EXPORT CMapPoi
{
public:
	CMapPoi();
	virtual ~CMapPoi();

	//������ԴID
	void SetResID( short sResID );

	//����POIID
	void SetPOIID( short sPOIID );

	//����POIName
	void SetPoiName( string strName );

	//����POI�ı�˵��
	void SetPoiText( string strText );

	//����POIPoint
	void SetMapPoint( double dMapX, double dMapY );

	//����POIPoint
	void SetMapPoint( MapPoint* Point );
	
	void SetMapAngle( long lAngle);
	//����
	void OnDraw( HDC hdc, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes );

	//����POIName
	void DrawPoiName( HDC hdc, CMapDisp* pMapDisp );

	//��������
	void SetPoiNameVisible( bool bVisible = false );

	//����POIName
	void DrawPoiText( HDC hdc , CMapPoiRes* pMapPoiRes );

	//����ɾ����ť
	void DrawDelBtn( HDC hdc , CMapPoiRes* pMapPoiRes );

	//��������
	bool IsPointIn( VOSPoint point );
	bool IsPointInDel( VOSPoint point );
	//����long color
	void SetMapTextColor( long color );
	void SetMapTextOffset( int x, int y );

	//���õ�ͼ�ɱ༭
	void OpenEdit( bool bEdit );
public:
	en_PoiType	m_ePoiType;
	MapPoint	m_Point;
	short		m_sResID;
	long		m_sPOIID;
	string		m_strPoiName;
	string		m_strText;
	VOSRect		m_rc;
	VOSRect		m_rcDelBtn;
	int			m_iTextOffsetX;
	int			m_iTextOffsetY;
	long		m_lTextColor;
	bool		m_bDrawPoiName;
	bool		m_bEdit;
	long		m_lAngle;
};

#endif // !defined(AFX_MAPPOI_H__93DA55CC_303F_4DED_9E5D_8E6F09927810__INCLUDED_)
