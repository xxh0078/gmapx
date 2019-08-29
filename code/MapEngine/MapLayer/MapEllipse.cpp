// MapAround.cpp: implementation of the CMapAround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapEllipse.h"
#include "../MapDisp/MapDisp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapEllipse::CMapEllipse()
{
	uid = -1;
}

CMapEllipse::~CMapEllipse()
{

}
void CMapEllipse::Draw(HDC hdc, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes)
{
	if ( uid >= 0 ) {
		if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
		{
			VOSPoint pt;
			pMapDisp->MapToScreen( m_Point, pt );
			pMapPoiRes->DrawAroundAlpha( hdc,1, pt,radius,alpha );
		}	
	}
}
