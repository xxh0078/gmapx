// MapAround.cpp: implementation of the CMapAround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapPie.h"
#include "../MapDisp/MapDisp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapPie::CMapPie()
{
	uid = -1;
}

CMapPie::~CMapPie()
{

}
void CMapPie::Draw(HDC hdc, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes)
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
