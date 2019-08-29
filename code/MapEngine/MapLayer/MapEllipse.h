// MapAround.h: interface for the CMapAround class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_Map_Ellipse_)
#define _Map_Ellipse_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class CMapEllipse
{
public:
	CMapEllipse();
	virtual ~CMapEllipse();
	void Draw(HDC hdc, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes);
	long uid;
	MapPoint	m_Point;
	long radius;
	long alpha;
};

#endif // !defined(_Map_Ellipse_)
