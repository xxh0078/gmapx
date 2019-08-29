// MapAround.h: interface for the CMapAround class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPAROUND_H__860343B0_07FF_4E79_B3F9_579A494960B7__INCLUDED_)
#define AFX_MAPAROUND_H__860343B0_07FF_4E79_B3F9_579A494960B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class CMapAround  
{
public:
	CMapAround();
	virtual ~CMapAround();
	void Draw(HDC hdc, agg::rendering_buffer* rbuf, CMapDisp* pMapDisp,CMapPoiRes* pMapPoiRes );
	//…Ë÷√œﬂøÌ∂»
	void SetColor( long color );
public:
	long m_rid;
	MapPoint	m_mptPoint;
	long m_radius;
	long alpha;
	VOSRect		m_rc;
	string m_strname;
	long m_color;
};

#endif // !defined(AFX_MAPAROUND_H__860343B0_07FF_4E79_B3F9_579A494960B7__INCLUDED_)
