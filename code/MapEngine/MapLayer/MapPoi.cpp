// MapPoi.cpp: implementation of the CMapPoi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapPoi.h"
#include "../MapDisp/MapDisp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapPoi::CMapPoi()
{
	m_strPoiName = "";
	m_iTextOffsetX = 15;
	m_iTextOffsetY = - 10;
	m_lTextColor = RGB(0,0,255);
	m_bDrawPoiName = false;
	m_rcDelBtn.left = 0;
	m_rcDelBtn.bottom = 0;
	m_rcDelBtn.top = 0;
	m_rcDelBtn.right = 0;
	m_bEdit = false;
	m_lAngle = 0;
}
void CMapPoi::SetMapTextColor( long color )
{
	m_lTextColor = color;
}
void CMapPoi::SetMapTextOffset(int x, int y)
{
	m_iTextOffsetX = x;
	m_iTextOffsetY = y;
}
CMapPoi::~CMapPoi()
{
	m_bDrawPoiName = false;
}
// 	//设置POI类型
// 	void SetPoiType( en_PoiType ePoiType );
//设置资源ID
void CMapPoi::SetResID( short sResID )
{
	m_sResID = sResID;
}
//设置POIID
void CMapPoi::SetPOIID( short sPOIID )
{
	m_sPOIID = sPOIID;
}
//设置POIName
void CMapPoi::SetPoiName( string strName )
{
	m_strPoiName = strName;
}
//设置POI文本说明
void CMapPoi::SetPoiText( string strText )
{
	m_strText = strText;
}
//设置POIPoint
void CMapPoi::SetMapPoint( double dMapX, double dMapY )
{
	m_Point.x = dMapX;
	m_Point.y = dMapY;
}
//设置POIName
void CMapPoi::SetMapPoint( MapPoint* Point )
{
	SetMapPoint( Point->x, Point->y );
}
void CMapPoi::SetMapAngle( long lAngle)
{
	m_lAngle = lAngle;
}
void CMapPoi::OnDraw(HDC hdc, CMapDisp* pMapDisp,CMapPoiRes* pMapPoiRes)
{
	if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
	{
		VOSPoint pt;
		pMapDisp->MapToScreen( m_Point, pt );
		//
		//
		VOSSize sz ;
		pMapPoiRes->GetSize( m_sResID, sz );
		//TRACE("\n33333mapx=%f,mapy=%f,x=%d,y=%d\n",m_Point.x,m_Point.y,pt.x,pt.y);
		m_rc.left = pt.x-(sz.cx/2);
		m_rc.right = pt.x + (sz.cx/2);
		m_rc.top =	pt.y-(sz.cy/2);
		m_rc.bottom = pt.y+(sz.cy/2);
		//TRACE("\n444444m_rcx.left=%d,m_rc.right=%d,m_rc.top=%d,m_rc.bottom=%d\n",m_rc.left,m_rc.right,m_rc.top,m_rc.bottom);
		//pMapPoiRes->Draw( hdc, m_sResID, m_rc );
		if( m_lAngle == 0 )
			pMapPoiRes->DrawCenter( hdc, m_sResID, pt );
		else
			pMapPoiRes->DrawCenter( hdc, m_sResID, pt, m_lAngle );
		if( m_bEdit )
		{
			DrawDelBtn( hdc, pMapPoiRes ); 
		}
	}
}
void CMapPoi::SetPoiNameVisible( bool bVisible )
{
	m_bDrawPoiName = bVisible;
}
//绘制POIName
void CMapPoi::DrawPoiName( HDC hdc,CMapDisp* pMapDisp )
{
	if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
	{
		//	if (  m_rc.IsPointIn( point ) )
	//	{
	//	if( m_bDrawPoiName )
		{
			int iLen = m_strPoiName.length();// strlen( m_strPoiName);

			if ( iLen == 0 ) {
				return ;
			}
			
			SetBkMode(hdc,TRANSPARENT);
			VOSPoint pt = m_rc.CenterPoint();

			VOSRect rc;
			rc.top =  pt.y + m_iTextOffsetY;
			//rc.top =  m_rc.top + m_iTextOffsetY;
			rc.bottom =rc.top+16;

			rc.left = pt.x + m_iTextOffsetX;
			//rc.left = m_rc.right + m_iTextOffsetX;
			rc.right = rc.left+10*iLen;

			//rc.bottom =rc.top+20;
		// 		MoveToEx( hdc,rc.left,rc.top,NULL );
		// 		LineTo( hdc, rc.left,rc.bottom );
		// 		LineTo( hdc, rc.right,rc.bottom );
		// 		LineTo( hdc, rc.right,rc.top );
		// 		LineTo( hdc, rc.left,rc.top );
		//	HPEN pen = CreatePen(PS_SOLID,1,RGB(255,255,0));
		//	::SelectObject( hdc, pen );
			HFONT font =   CreateFont(                 
			18,//pFont-> xFont-> GetCxFont(),                                       //   nHeight 
			0,                                   //   nWidth 
			0,                                                   //   nEscapement 
			0,                                                   //   nOrientation 
			FW_BOLD,//FW_BOLD,//FW_NORMAL,                                       //   nWeight 
			0,                                           //   bItalic 
			0,                                           //   bUnderline	下划线
			0,                                                   //   cStrikeOut 删除线
			GB2312_CHARSET,//ANSI_CHARSET,                             //   nCharSet 
			OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
			CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
			DEFAULT_QUALITY,                       //   nQuality 
			DEFAULT_PITCH|FF_ROMAN,//   |   FF_SWISS,     //   nPitchAndFamily 
			"宋体"// "Arial"// "system"         
			);
			HFONT oldfont = (HFONT)::SelectObject(hdc,font );

			SetTextColor( hdc,   255   ); 
			::DrawText( hdc, m_strPoiName.c_str(),iLen ,&rc,DT_LEFT);
			SelectObject(hdc,oldfont);
			DeleteObject( font );
			//}
		}
	}
}
//绘制POITEXT
void CMapPoi::DrawPoiText( HDC hdc, CMapPoiRes* pMapPoiRes )
{
	int iLen = this->m_strText.length();
	if ( iLen == 0 )
	{
		return ;
	}

	SetBkMode(hdc,TRANSPARENT);
	SetTextColor( hdc,   RGB( 255, 0, 0 )   ); 

	//设置
	long lCenterX = m_rc.CenterPoint().x;
	long lCenterY = m_rc.CenterPoint().y;
	
	
	//绘制巨型
	pMapPoiRes->DrawPoiText( hdc,0,m_rc.CenterPoint(), m_strText );
}
//绘制删除按钮
void CMapPoi::DrawDelBtn( HDC hdc , CMapPoiRes* pMapPoiRes )
{
	if( !m_bEdit )
		return;
	VOSSize sz;
	pMapPoiRes->GetSize( pMapPoiRes->m_idImgDelBtn, sz );
	m_rcDelBtn.left = this->m_rc.right;
	m_rcDelBtn.bottom = m_rc.bottom;
	m_rcDelBtn.top = m_rcDelBtn.bottom-sz.cy;
	m_rcDelBtn.right = m_rcDelBtn.left + sz.cx;
	pMapPoiRes->Draw( hdc, pMapPoiRes->m_idImgDelBtn, m_rcDelBtn );
}
//单击属性
bool CMapPoi::IsPointIn( VOSPoint point )
{
	if (  m_rc.IsPointIn( point ) )
	{
		return TRUE;
	}
	return false;
}
bool CMapPoi::IsPointInDel( VOSPoint point )
{
	if( !m_bEdit )
		return false;
	if (  m_rcDelBtn.IsPointIn( point ) )
	{
		return true;
	}
	return false;
}
//设置POI数据编辑状态
void CMapPoi::OpenEdit( bool bEdit )
{
	this->m_bEdit = bEdit;
}
