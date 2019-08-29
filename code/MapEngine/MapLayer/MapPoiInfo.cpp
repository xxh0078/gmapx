// MapPoiInfo.cpp: implementation of the CMapPoiInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapPoiInfo.h"
#include "../MapDisp/MapDisp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapPoiInfo::CMapPoiInfo()
{
//	m_bDraw = false;
//	m_bFirstSHow = false;
	m_pPOI = NULL;
}

CMapPoiInfo::~CMapPoiInfo()
{

}
//初始化
void CMapPoiInfo::Init( CMapDisp* pMapDisp, const char* strPath )
{
	m_pPOI = NULL;
	m_pMapDisp = pMapDisp;
	string strFileName = strPath;
	strFileName += "poiinfo.png";
	this->m_image.LoadImage( strFileName.c_str() );	
}
//绘制
void CMapPoiInfo::Draw( HDC hdc, CMapDisp* pMapDisp )
{
	if( m_pPOI == NULL )
		return;
	if( m_pPOI->m_strText.empty() )
		return ;
	m_rect.left = m_pPOI->m_rc.CenterPoint().x-140;
	m_rect.bottom = m_pPOI->m_rc.top;
	VOSSize sz = m_image.GetSize();
	m_rect.right = m_rect.left + sz.cx;
	m_rect.top = m_rect.bottom - sz.cy;
	//--
	this->m_rcClose.left = m_rect.right - 19;
	this->m_rcClose.right = m_rect.right - 7;
	this->m_rcClose.top = m_rect.top + 5 ;
	this->m_rcClose.bottom = m_rect.top + 18;
	//
	m_rcText.left = m_rect.left;
	m_rcText.right = m_rect.right;
	m_rcText.top = m_rect.top;
	m_rcText.bottom = m_rect.top+119;
	//绘制巨型
	m_image.Draw( hdc, m_rect );
	//绘制字体
/*	m_size = 8;
	m_width = 0;
	m_escapement = 0;
	m_orientation = 0;
	m_weight = FW_NORMAL;//FW_NORMAL:400  FW_BOLD:700
	m_Italic = 0;
	m_underline = 0;
	m_strikeOut = 0;
	m_fontname = "宋体";*/
	HFONT font =   CreateFont(                 
		12,//pFont-> xFont-> GetCxFont(),                                       //   nHeight 
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
	int iLen = m_pPOI->m_strText.length();
	if ( iLen <= 0 )
	{
		return ;
	}
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor( hdc,   RGB( 255, 0, 0 )   ); 
	SetTextColor( hdc,   RGB( 0, 0, 0 )   ); 
	RECT rect;
	rect.left = m_rect.left+13;
	rect.right = m_rect.right-3;
	rect.top = m_rect.top+11;
	rect.bottom = m_rect.bottom-3;
//	SetTextCharacterExtra( hdc, 2 );
	string str = m_pPOI->m_strText;
    string tmp;
	string sep = "\n";
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
			::DrawText( hdc, tmp.c_str(),tmp.length() ,&rect,DT_LEFT);
			rect.top += 18;
        }
    }
	//::DrawText( hdc, m_strText.c_str(),iLen ,&rect,DT_LEFT);
	SelectObject(hdc,oldfont);
	DeleteObject( font );
}
//设置POI信息
void CMapPoiInfo::SetPoiInfo( CMapPoi* pPOI )
{
	m_pPOI = pPOI;
	this->m_pMapDisp->Invalidate();
	//SetPoiInfo(  poiid, strText, mpt, bDraw );
}
//设置信息
/*void CMapPoiInfo::SetPoiInfo( short poiid, string strText, MapPoint mpt, bool bDraw )
{
	this->m_bDraw = bDraw;
	this->m_Point = mpt;
	this->m_strText = strText;
	this->m_poiid = poiid;
	//计算是否超出范围
	m_bFirstSHow = true;

	VOSPoint pt;
	m_pMapDisp->MapToScreen( m_Point, pt );
	m_rect.left = pt.x -140;
	m_rect.bottom = pt.y;
	VOSSize sz;
	m_pMapPoiRes->GetSize( 0, sz );
	m_rect.right = m_rect.left + sz.cx;
	m_rect.top = m_rect.bottom - sz.cy;

	int ndx = 0;
	int ndy = 0;
	if( m_rect.left < m_pMapDisp->m_rcWnd.left )
	{
		ndx = m_pMapDisp->m_rcWnd.left - m_rect.left+5;
	}
	if( m_rect.top < m_pMapDisp->m_rcWnd.top )
	{
		ndy = m_pMapDisp->m_rcWnd.top-m_rect.top+5;
	}
	if( m_rect.right > m_pMapDisp->m_rcWnd.right )
	{
		ndx = m_pMapDisp->m_rcWnd.right - m_rect.right-5;
	}
	if(ndx != 0 || ndy != 0 )
	{
		m_pMapDisp->OnMapMove( ndx, ndy );
	}
}	
//设置信息
void CMapPoiInfo::SetPoiInfo( short poiid, string strText, MapPoint mpt )
{
	this->m_Point = mpt;
	this->m_strText = strText;
	this->m_poiid = poiid;
}
*/
//单击属性
bool CMapPoiInfo::IsPointIn( VOSPoint point )
{
	if ( m_pPOI == NULL ) {
		return false;
	}
	if ( !this->m_rcText.IsPointIn(point) ) {
		return false;
	}
	if ( this->m_rcClose.IsPointIn(point) ) {
		Close();
		return true;
	}
	return false;
}
//鼠标消息
bool CMapPoiInfo::OnLButtonDown( VOSPoint point )
{
	if ( m_pPOI == NULL ) {
		return false;
	}
	if ( !this->m_rcText.IsPointIn(point) ) {
		return true;
	}
	return false;
}
bool CMapPoiInfo::OnLButtonUp( VOSPoint point)
{
	if ( m_pPOI == NULL ) {
		return false;
	}
	if ( this->m_rcClose.IsPointIn(point) ) {
		Close();
		return true;
	}
	return false;
}
bool CMapPoiInfo::OnMouseMove( VOSPoint point)
{
	if ( m_pPOI == NULL ) {
		return false;
	}
	return false;
}
//关闭
void CMapPoiInfo::Close()
{
	m_pPOI = NULL;
	this->m_pMapDisp->Invalidate();
}