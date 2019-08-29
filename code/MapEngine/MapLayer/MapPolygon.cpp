// MapPolygon.cpp: implementation of the CMapPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapPolygon.h"
#include "../MapDisp/MapDisp.h"
#include "../VOSBase/VOSDefine.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
HBRUSH g_hbr1 = CreateSolidBrush(RGB(230,230,230));
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapPolygon::CMapPolygon()
{
	m_arrPoint.clear();
	m_bVisible = true;
}

CMapPolygon::~CMapPolygon()
{
	Realse();
}
//释放内存
void CMapPolygon::Realse()
{
	MapPoint* pPoint = NULL;
	for (vector<MapPoint*>::iterator it = m_arrPoint.begin(); it != m_arrPoint.end(); ++it)
    {
		pPoint = *it;
        delete pPoint;
    }
	m_arrPoint.clear();
}
//添加一个点
void CMapPolygon::AddPoint( MapPoint* pPoint )
{
	this->m_arrPoint.push_back( pPoint );
}
//得到总的点数量
long CMapPolygon::GetCount()
{
	return this->m_arrPoint.size();
}

//设置线宽度
void CMapPolygon::SetColor( long color )
{
	m_color = color;
}
//设置线名字
void CMapPolygon::SetName(string strName)
{
	m_strname = strName;
}
//设置线的颜色
void CMapPolygon::SetWidth( long width )
{
	this->m_width = width;
}
//绘制
void CMapPolygon::OnDraw( HDC hdc,agg::rendering_buffer* rbuf, CMapDisp* pMapDisp )
{
	if( m_bVisible ){
			//BOOL Polyline( HDC hdc, CONST POINT *lppt, int cPoints)
		//if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
			// 像素格式和renderer_base http://www.cppprog.com C++编程网
			agg::pixfmt_bgra32 pixf(*rbuf); 
			agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 
		//	renb.clear(agg::rgba8(255, 255, 255, 255)); 
			
			// Scanline renderer 
			agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

			// Rasterizer & scanline
			agg::rasterizer_scanline_aa<> ras;
			agg::scanline_p8 sl;
			ras.reset();

			agg::path_storage ps; 
			ps.start_new_path();   
			VOSPoint pt,pt1;
			int count = this->m_arrPoint.size();		
			for ( int i=0;i<count;i++ )
			{
				pMapDisp->MapToScreen( *m_arrPoint.at(i), pt );
				if( i==0 )
				{
					ps.move_to( pt.x,pt.y);
				}
				else
				{
					ps.line_to( pt.x,pt.y);
				}
			}
			//ps.end_poly(); 
			ps.close_polygon();
			
			agg::conv_contour<agg::path_storage> csps(ps);
			//agg::conv_stroke<agg::path_storage, agg::vcgen_markers_term> csps(ps);
			csps.width(this->m_width);
			ras.add_path(csps); 
			//ren.color(agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16)); 
			//agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16));
			agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16,100));
			//显示线的名字
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
				
				//::FillRect( hdc,&m_rc,g_hbr);
				::TextOut(hdc,pt.x,pt.y,m_strname.c_str(),len);
				
			}
			else
			{
				m_rc.left = 0;
				m_rc.top = 0;
				m_rc.right = 0;
				m_rc.bottom = 0;
			}
			/*
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
				
				::FillRect( hdc,&m_rc,g_hbr1);
				::TextOut(hdc,pt.x,pt.y,m_strname.c_str(),len);
			}
			else
			{
				m_rc.left = 0;
				m_rc.top = 0;
				m_rc.right = 0;
				m_rc.bottom = 0;
			}*/
			/*
			agg::pixfmt_bgra32 pixf(*rbuf);
			agg::renderer_base<agg::pixfmt_bgra32> renb(pixf);

			//renb.clear(agg::rgba8(255, 255, 255, 255));

			// Scanline renderer for solid filling.
			agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

			// Rasterizer & scanline
			agg::rasterizer_scanline_aa<> ras;
			agg::scanline_p8 sl;

			// Polygon (triangle)
			VOSPoint pt,pt1;
			int count = this->m_arrPoint.size();		
			for ( int i=0;i<count;i++ )
			{
				pMapDisp->MapToScreen( *m_arrPoint.at(i), pt );
				if( i==0 )
				{
					ras.move_to_d( pt.x,pt.y);
				}
				else
				{
					ras.line_to_d( pt.x,pt.y);
				}
			}
		//	ras.move_to_d(20.7, 34.15);
		//	ras.line_to_d(398.23, 123.43);
		//	ras.line_to_d(165.45, 401.87);

			// Setting the attrribute (color) & Rendering
			ren.color(agg::rgba8(80, 90, 60));
			agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16));
			*/
	}
}
void CMapPolygon::SetVisible(bool bVisible )
{
	m_bVisible = bVisible;
}
bool CMapPolygon::GetVisible()
{
	return m_bVisible;
}

//得到第几个点信息
bool CMapPolygon::GetMapPoint( int index, MapPoint& mapPoint )
{
	if( index >= m_arrPoint.size() )
		return false;
	int i=0;
	MapPoint* pPoint = NULL;
	for (vector<MapPoint*>::iterator it = m_arrPoint.begin(); it != m_arrPoint.end(); ++it)
    {
		pPoint = *it;
		if( i == index )
		{
			mapPoint.x = pPoint->x;
			mapPoint.y = pPoint->y;
			return true;
		}
		i++;
    }
	return false;
}
