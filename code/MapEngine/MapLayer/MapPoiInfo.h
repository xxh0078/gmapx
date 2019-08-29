// MapPoiInfo.h: interface for the CMapPoiInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_)
#define AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include "MapPoi.h"
class CMapDisp;
class CMapPoiInfo  
{
public:
	CMapPoiInfo();
	virtual ~CMapPoiInfo();
	//��ʼ��
	void Init( CMapDisp* pMapDisp, const char* strPath );
	//����
	void Draw( HDC hdc, CMapDisp* pMapDisp );

	//���õ�ͼPOI��Ϣ
	void SetPoiInfo( CMapPoi* pPOI );
	
	//��������
	bool IsPointIn( VOSPoint point );

	//�����Ϣ
	bool OnLButtonDown( VOSPoint point );
	bool OnLButtonUp( VOSPoint point);
	bool OnMouseMove( VOSPoint point);

	//�ر�
	void Close();
public:
	CMapPoi*	m_pPOI;
	CVOSImage	m_image;
	CMapDisp*	m_pMapDisp;
	VOSRect		m_rect;			//��Ϣ��ʾ����λ��
	VOSRect		m_rcClose;		//�رհ�ťλ��
	VOSRect		m_rcText;		//�ı���ʾ����
	/*
	string		m_strText;		//����ƶ���ʾ
	MapPoint	m_Point;		//
	bool		m_bDraw;		//	
	short		m_poiid;
	CMapPoiRes*	m_pMapPoiRes;
	bool		m_bFirstSHow;
	*/
};

#endif // !defined(AFX_MAPPOIINFO_H__11DCD504_CD9C_4B31_A453_628638699EAA__INCLUDED_)
