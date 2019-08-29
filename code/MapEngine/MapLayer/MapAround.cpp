// MapAround.cpp: implementation of the CMapAround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapAround.h"
#include "../MapDisp/MapDisp.h"
#include "../MapBase/MapUtil.h"
#include <agg_ellipse.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
HBRUSH g_hbr2 = CreateSolidBrush(RGB(230,230,230));
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapAround::CMapAround()
{
	m_rid = -1;
	m_strname = "";
}

CMapAround::~CMapAround()
{

}
//agg::pixfmt_bgra32 pixf(*m_rbuf); 
//agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 
//agg::renderer_base<agg::pixfmt_rgb24> ren_bas;
void CMapAround::Draw(HDC hdc, agg::rendering_buffer* rbuf,CMapDisp* pMapDisp,CMapPoiRes* pMapPoiRes )
{
	if ( m_rid >= 0 ) {
		if( pMapDisp->IsMapPointInMapCreen( m_mptPoint ) )
		{
			VOSPoint pt,pt1;
			pMapDisp->MapToScreen( m_mptPoint, pt );
			pt1.x = pt.x+100;
			pt1.y = pt.y;
			MapPoint mpt1;
			pMapDisp->ScreenToMap( pt1, mpt1 );
			CProject mapProject;
			long lMapLength = mapProject.CalLength(m_mptPoint.x,m_mptPoint.y,mpt1.x,mpt1.y);
			//--
			long radius = (m_radius * 100 )/ lMapLength  ;

		//	pMapPoiRes->DrawAroundAlpha( hdc, pt, radius, alpha );

			agg::pixfmt_bgra32 pixf(*rbuf); 
			agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 		
			// Scanline renderer 
			agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

			// Rasterizer & scanline
			agg::rasterizer_scanline_aa<> ras;
			agg::scanline_p8 sl;
			ras.reset();

			agg::ellipse er( pt.x, pt.y, radius, radius, alpha );
			ras.add_path(er);
			agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16,alpha));

			
			/*VOSPoint ptStart;
			m_pMapDisp->MapToScreen(m_mptLast,ptStart);
			if( m_iState == 2 || m_iState == 3 )
			{		
				int ndx = abs( ptStart.x-m_ptMouse.x );
				int ndy = abs( ptStart.y-m_ptMouse.y );
				double nLen = sqrt( (double)(ndx*ndx + ndy*ndy) );
				m_Image.AlphaDraw(hdc,ptStart.x - nLen,ptStart.y - nLen, nLen*2,
					nLen*2,100 );
			}*/
			int len = m_strname.length();
			if( len > 0 && pMapDisp->m_rcWnd.IsPointIn( pt ) )
			{
				//::SetTextColor( hdc, color );
				SetBkMode(hdc,TRANSPARENT);
				int r =3;
				::Ellipse( hdc,pt.x-r,pt.y-r,pt.x+r,pt.y+r);
				TEXTMETRIC tm;
				if( GetTextMetrics( hdc, &tm ) )
				{
					//pt.x -= (tm.tmAveCharWidth*len)/2;
					pt.y -= tm.tmHeight;
				}
				m_rc.left = pt.x;
				m_rc.top = pt.y;
				m_rc.right = m_rc.left + len*tm.tmAveCharWidth;
				m_rc.bottom = m_rc.top + tm.tmHeight;
				
				::FillRect( hdc,&m_rc,g_hbr2);
				::TextOut(hdc,pt.x,pt.y,m_strname.c_str(),len);
			}
			else
			{
				m_rc.left = 0;
				m_rc.top = 0;
				m_rc.right = 0;
				m_rc.bottom = 0;
			}
		}	
	}
}
//…Ë÷√œﬂøÌ∂»
void CMapAround::SetColor( long color )
{
	m_color = color;
}