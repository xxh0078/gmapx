// MapLine.cpp: implementation of the CMapLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapLine.h"
#include "../MapDisp/MapDisp.h"
#include "agg_basics.h" 
#include "agg_rendering_buffer.h" 
#include "agg_rasterizer_scanline_aa.h" 
#include "agg_scanline_u.h" 
#include "agg_renderer_scanline.h" 
#include "agg_pixfmt_rgb.h" 
#include "platform/agg_platform_support.h" 
#include "agg_ellipse.h" 
#include "agg_conv_contour.h" 
#include "agg_conv_stroke.h" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HBRUSH g_hbr = CreateSolidBrush(RGB(230,230,230));
CMapLine::CMapLine()
{
	m_arrPoint.clear();
	m_bVisible = true;
}

CMapLine::~CMapLine()
{
	Realse();
}
//�ͷ��ڴ�
void CMapLine::Realse()
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
//���һ����
void CMapLine::AddPoint( MapPoint* pPoint )
{
	this->m_arrPoint.push_back( pPoint );
}
//�õ��ܵĵ�����
long CMapLine::GetCount()
{
	return this->m_arrPoint.size();
}

//�����߿��
void CMapLine::SetColor( long color )
{
	m_color = color;
}
//�����ߵ���ɫ
void CMapLine::SetWidth( long width )
{
	this->m_width = width;
}
// ����ü����ε��ı߹�ϵ��
enum EDirection
{
	dtLEFT		= 0x01,	// ���
	dtRIGHT		= 0x02,	// �ұ�
	dtBOTTOM	= 0x04,	// �±�
	dtTOP		= 0x08,	// �ϱ�
};
/**
  *	 �ߵĲü�
  * 	@param rect	  [in]		�ü�����
  *		@param x	  [in]		���жϵ��x����
  *		@param y	  [in]		���жϵ��y����
  *		@param code	  [in/out]	�����λ����
  *
  *		@return	��
  *		@note	�ڲ�����
  */
void Encode( VOSRect rect, int x, int y, int* code )
{
	int ncode = 0;
	if( x < rect.left )
		ncode = ncode|dtLEFT;
	else if( x > rect.right )
		ncode = ncode|dtRIGHT;
	if( y < rect.top )
		ncode = ncode|dtTOP;
	else if( y > rect.bottom )
		ncode = ncode|dtBOTTOM;
	*code = ncode;
}

void EncodeEx( VOSRect rect, float x, float y, int* code )
{
	int ncode = 0;
	if( x < rect.left )
		ncode = ncode|dtLEFT;
	else if( x > rect.right )
		ncode = ncode|dtRIGHT;
	if( y < rect.top )
		ncode = ncode|dtTOP;
	else if( y > rect.bottom )
		ncode = ncode|dtBOTTOM;
	*code = ncode;
}

/**
  *	�ߵĲü�
  *
  *		@param rect		[in/out]  �ü�����
  *		@param ptStart	[in]	  �ߵ����
  *		@param ptEnd	[in]	  �ߵ��յ�
  *		@param ptFirst	[in/out]  �ü����ߵ����
  *		@param ptSecond	[in/out]  �ü����ߵ��յ�
  * 
  *		@return	�ɹ�����true�����򷵻�false
  *		@note	��
  */
bool RDIClipLine( VOSRect rect, VOSPoint ptStart, VOSPoint ptEnd, VOSPoint* ptFirst, VOSPoint* ptSecond )
{
	if( ::abs( ptEnd.y - ptStart.y ) < 0x7FF )
	{
		int code1, code2, code;
		int nX1, nY1;
		int nX2, nY2;
		int nX = 0, nY = 0;
		int k;		// ֱ��б��
		int nCount = 0;
		
		// �ü����߶θ���ֵ
		nX1 = ptStart.x;
		nY1 = ptStart.y;
		nX2 = ptEnd.x;
		nY2 = ptEnd.y;
		
		k = (0x80000000 & ( ptStart.y - ptEnd.y )) | ( ( ptStart.y - ptEnd.y ) << 20 );		// ����1024��
		if( ( ptStart.x - ptEnd.x ) == 0 )
			k = 0xEFFFFFFF;
		else
			k /= ( ptStart.x - ptEnd.x );
		
		// ȷ���߶ε�������
		Encode( rect, ptStart.x, ptStart.y, &code1 );
		Encode( rect, ptEnd.x, ptEnd.y, &code2 );
		while( code1 != 0 || code2 != 0 )
		{
			nCount++;
			if( (code1 & code2) != 0 || nCount > 4 )	// �߶��ڲü�������
				return 0;
			
			code = code1;
			if( code1 == 0 )
				code = code2;
			if( (dtLEFT & code) != 0 )
			{
				nX = rect.left;

				nY = nY2 + (( 0x80000000 & ((rect.left - nX2) * k)) | ((rect.left - nX2) * k) >> 20 );
			}
			else if( (dtRIGHT & code) != 0 )
			{
				nX = rect.right;

				nY = nY2 + (( 0x80000000 & ((rect.right - nX2) * k)) | ((rect.right - nX2) * k) >> 20 );
			}
			else if( (dtBOTTOM & code) != 0 )
			{
				nY = rect.bottom;

				if( k == 0 )
					nX = nX2 + ( ( (int)( 0x80000000 & (rect.bottom - nY2)) | ( (rect.bottom - nY2) << 20 ) ) / (k+1) );
				else if( ptStart.x == ptEnd.x )
					nX = nX2;
				else
					nX = nX2 + ( ( (int)( 0x80000000 & (rect.bottom - nY2)) | ( (rect.bottom - nY2) << 20 )) / k );
			}
			else if( (dtTOP & code) != 0 )
			{
				nY = rect.top;

				if( k == 0 )
					nX = nX2 + ( ( (int)( 0x80000000 & (rect.top - nY2)) | ( (rect.top - nY2) << 20 ) ) / (k+1) );
				else if( ptStart.x == ptEnd.x )
					nX = nX2;
				else
					nX = nX2 + ( ( (int)( 0x80000000 & (rect.top - nY2)) | ( (rect.top - nY2) << 20 ) ) / k );
			}
			
			if( code == code1 )
			{
				nX1 = nX;
				nY1 = nY;
				Encode( rect, nX, nY, &code1 );
			}
			else
			{
				nX2 = nX;
				nY2 = nY;
				Encode( rect, nX, nY, &code2 );
			}
		}
		ptFirst->x = nX1;
		ptFirst->y = nY1;
		ptSecond->x = nX2;
		ptSecond->y = nY2;
	}
	else
	{
		int code1, code2, code;
		float nX1, nY1;
		float nX2, nY2;
		float nX = 0, nY = 0;
		float k;		// ֱ��б��
		int nCount = 0;
		
		// �ü����߶θ���ֵ
		nX1 = (float)ptStart.x;
		nY1 = (float)ptStart.y;
		nX2 = (float)ptEnd.x;
		nY2 = (float)ptEnd.y;
		
		if( ptStart.x - ptEnd.x == 0 )
			k = ( ptStart.y - ptEnd.y )/0.000001f;
		else
			k = (float)(( ptStart.y - ptEnd.y )/( ptStart.x - ptEnd.x ));
		
		// ȷ���߶ε�������
		EncodeEx( rect, (float)ptStart.x, (float)ptStart.y, &code1 );
		EncodeEx( rect, (float)ptEnd.x, (float)ptEnd.y, &code2 );
		while( code1 != 0 || code2 != 0 )
		{
			nCount++;
			if( (code1 & code2) != 0 || nCount > 4 )	// �߶��ڲü�������
				return 0;
			
			code = code1;
			if( code1 == 0 )
				code = code2;
			if( (dtLEFT & code) != 0 )
			{
				nX = (float)rect.left;

				nY = nY2 + (rect.left - nX2) * k;
			}
			else if( (dtRIGHT & code) != 0 )
			{
				nX = (float)rect.right;

				nY = nY2 + (rect.right - nX2) * k;
			}
			else if( (dtBOTTOM & code) != 0 )
			{
				nY = (float)rect.bottom;

				if( k == 0 )
					nX = nX2 + (rect.bottom - nY2)/0.000001f;
				else if( ptStart.x == ptEnd.x )
					nX = nX2;
				else
					nX = nX2 + (rect.bottom - nY2)/k;
			}
			else if( (dtTOP & code) != 0 )
			{
				nY = (float)rect.top;

				if( k == 0 )
					nX = nX2 + (rect.top - nY2)/0.000001f;
				else if( ptStart.x == ptEnd.x )
					nX = nX2;
				else
					nX = nX2 + (rect.top - nY2)/k;
			}
			
			if( code == code1 )
			{
				nX1 = nX;
				nY1 = nY;
				EncodeEx( rect, nX, nY, &code1 );
			}
			else
			{
				nX2 = nX;
				nY2 = nY;
				EncodeEx( rect, nX, nY, &code2 );
			}
		}
		ptFirst->x = (long)nX1;
		ptFirst->y = (long)nY1;
		ptSecond->x = (long)nX2;
		ptSecond->y = (long)nY2;
	}
	return 1;
}

//����
void CMapLine::OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp )
{
	if( m_bVisible ){
			//BOOL Polyline( HDC hdc, CONST POINT *lppt, int cPoints)
		//if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
			// ���ظ�ʽ��renderer_base http://www.cppprog.com C++�����
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
			// �����ߣ������Σ� 
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
			// ������ɫ����Ⱦ 
			ren.color(agg::rgba8(80, 90, 60)); 
			agg::render_scanlines(ras, sl, ren); 
			*/
			agg::path_storage ps;   

			ps.start_new_path();   
			VOSPoint pt,pt1;
		//		int iTimes = 0;	//�������
		//		bool bFirst = true;
			bool bFirst = true;
			int count = this->m_arrPoint.size();		
			for ( int i = 0;i<count;i++ )
			{
				pMapDisp->MapToScreen( *m_arrPoint.at(i), pt );
				if( i == 0 )
				{
					//ps.move_to( pt.x,pt.y);
					//bFirst = false;
				}
				else
				{
					//if( pt
					if ( pMapDisp->m_rcWnd.IsPointIn( pt1 ) && pMapDisp->m_rcWnd.IsPointIn( pt ) ) 
					{
						ps.move_to( pt1.x,pt1.y);
						ps.line_to( pt.x,pt.y);
					}
					else
					{
						VOSPoint pt2,pt3;
						if( RDIClipLine( pMapDisp->m_rcWnd,pt1,pt,&pt2,&pt3))
						{
							ps.move_to( pt2.x,pt2.y);
							ps.line_to( pt3.x,pt3.y);
						}
					}
					//if( pMapDisp->m_rcWnd.IsPointIn( pt ) ) 
					//	ps.line_to( pt.x,pt.y);
					//ps.move_to( pt.x,pt.y);
				}
				pt1.x = pt.x;
				pt1.y = pt.y;
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
			//agg::ellipse(100,100,50,50);
			//RGB()
			//agg::rgba()agg::rgba(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16)
			agg::render_scanlines_aa_solid(ras,sl,renb,agg::rgba8(m_color&0xFF,(m_color>>8)&0xFF,m_color>>16));   

			//agg::ellipse(pt.x,pt.y,50,50);
			//::Ellipse(
			
			//��ʾ�ߵ�����
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
void CMapLine::SetVisible(bool bVisible )
{
	m_bVisible = bVisible;
}
bool CMapLine::GetVisible()
{
	return m_bVisible;
}
//����������
void CMapLine::SetLineName(string strName)
{
	m_strname = strName;
}
//�õ��ڼ�������Ϣ
bool CMapLine::GetMapPoint( int index, MapPoint& mapPoint )
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
bool CMapLine::IsPointIn( VOSPoint point )
{
	return m_rc.IsPointIn( point );
}