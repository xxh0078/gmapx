// MapRule.cpp: implementation of the CMapRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapRule.h"
#include "../MapDisp/MapDisp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapRule::CMapRule()
{
	m_arrPoint.clear();
	m_bVisible = true;
}

CMapRule::~CMapRule()
{
	Realse();
}
//释放内存
void CMapRule::Realse()
{
	MapPoint* pPoint = NULL;
	for (vector<MapPoint*>::iterator it = m_arrPoint.begin(); it != m_arrPoint.end(); ++it)
    {
		pPoint = *it;
        delete pPoint;
		//m_arrMapLayers.erase( it );
    }
	m_arrPoint.clear();
}
//添加一个点
void CMapRule::AddPoint( MapPoint* pPoint )
{
	this->m_arrPoint.push_back( pPoint );
}
//得到总的点数量
long CMapRule::GetCount()
{
	return this->m_arrPoint.size();
}

//设置线宽度
void CMapRule::SetColor( long color )
{
	m_color = color;
}
//设置线的颜色
void CMapRule::SetWidth( long width )
{
	this->m_width = width;
}
//绘制
void CMapRule::OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp )
{
	if( m_bVisible ){
			//BOOL Polyline( HDC hdc, CONST POINT *lppt, int cPoints)
		//if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
			// 像素格式和renderer_base http://www.cppprog.com C++编程网
			agg::pixfmt_bgra32 pixf(*m_rbuf); 
			agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 
		//	renb.clear(agg::rgba8(255, 255, 255, 255)); 
			
			// Scanline renderer 
			agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

			// Rasterizer & scanline
			agg::rasterizer_scanline_aa<> ras;
			agg::scanline_p8 sl;
			ras.reset();
		/*
			// 多义线（三角形） 
			ras.move_to_d(20.7, 34.15); 
			ras.line_to_d(398.23, 123.43);
			ras.line_to_d(165.45, 401.87); 
		 pixfmt pixf(rbuf_window());
    
			rb.clear(agg::rgba(1, 1, 1));

			scanline_type sl;
			agg::rasterizer_scanline_aa<> ras;

			agg::simple_polygon_vertex_source path(m_poly.polygon(), 
												   m_poly.num_points(), 
												   false, 
												   m_close.status());

			typedef agg::conv_bspline<agg::simple_polygon_vertex_source> conv_bspline_type;
			conv_bspline_type bspline(path);
			bspline.interpolation_step(1.0 / m_num_points.value());

			typedef agg::conv_stroke<conv_bspline_type> conv_stroke_type;
			conv_stroke_type stroke(bspline);

			stroke.width(2.0);

			ras.add_path(stroke);
			// 设置颜色后渲染 
			ren.color(agg::rgba8(80, 90, 60)); 
			agg::render_scanlines(ras, sl, ren); 
			*/
			agg::path_storage ps;   

			ps.start_new_path();   
			VOSPoint pt,pt1;
		//		int iTimes = 0;	//出界次数
		//		bool bFirst = true;
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
		//
		//			if ( pMapDisp->m_rcWnd.IsPointIn(pt)  ) 
		//			{
		//				if( bFirst )
		//				{
		//					ps.move_to( pt.x,pt.y);
		//					bFirst = false;
		//				}
		//				else
		//				{
		//					ps.line_to( pt.x,pt.y);
		//				}
		//				
		//			}
		//			else
		//			{
		//				if ( i == 0 )
		//				{
		//					if( bFirst )
		//					{
		//						ps.move_to( pt.x,pt.y);
		//						bFirst = false;
		//					}
		//					else
		//					{
		//						ps.line_to( pt.x,pt.y);
		//					}
		//				}
		//				else
		//				{
		//					if( bFirst )
		//					{
		//						ps.move_to( pt.x,pt.y);
		//						bFirst = false;
		//					}
		//					else
		//					{
		//						ps.line_to( pt.x,pt.y);
		//					}
		//				}
		//				i++;
		//			}
		//			pt1.x = pt.x;
		//			pt1.y = pt.y;	
		//	ps.end_poly(); 
			agg::conv_stroke<agg::path_storage, agg::vcgen_markers_term> csps(ps);
			csps.width(this->m_width);
			ras.add_path(csps); 
		//	ras.auto_close(1);
		//	agg::ellipse(100,100,50,50);
			//RGB()
			//agg::rgba()agg::rgba(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16)
			agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16));   

			/*path_storage
		HPEN hpen = CreatePen(PS_SOLID, this->m_width, this->m_color ); 
		HPEN holdpen = (HPEN)SelectObject( hdc, hpen );

		int count = this->m_arrPoint.size();
		POINT* pt = new POINT[count];
		POINT* pttemp = pt;
		for ( int i=0;i<count;i++ ) {
			pMapDisp->MapToScreen( *m_arrPoint.at(i), *(VOSPoint*)pttemp );
			if ( i == 0 ) {
				MoveToEx( hdc, pt->x,pt->y,NULL);
			}
			else
			{
				LineTo( hdc, pttemp->x,pttemp->y);
			}
			pttemp++;
		}
		//Polyline( hdc, pt,count );
		SelectObject( hdc, holdpen );
		DeleteObject( hpen );
		delete[] pt;*/
	}
}
void CMapRule::SetVisible(bool bVisible )
{
	m_bVisible = bVisible;
}
bool CMapRule::GetVisible()
{
	return m_bVisible;
}