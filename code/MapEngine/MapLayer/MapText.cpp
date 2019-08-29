// MapText.cpp: implementation of the CMapText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapText.h"
#include "../MapDisp/MapDisp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapText::CMapText()
{
	tid = -1;
	color = 0;
	m_size = 8;
	m_width = 0;
	m_escapement = 0;
	m_orientation = 0;
	m_weight = FW_NORMAL;//FW_NORMAL:400  FW_BOLD:700
	m_Italic = 0;
	m_underline = 0;
	m_strikeOut = 0;
	m_fontname = "宋体";
}

CMapText::~CMapText()
{

}
//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
bool CMapText::SetMapTextFont(long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	m_size = size;
	m_weight = weight;
	m_width = width;
	m_escapement = escapement;
	m_orientation = orientation;
	m_Italic = Italic;
	m_strikeOut =strikeOut;
	m_underline = underline;
	m_fontname = fontname;
	return true;
}
void CMapText::Draw( HDC hdc, CMapDisp* pMapDisp )
{
	if ( tid >= 0 )
	{
		if( pMapDisp->IsMapPointInMapCreen( m_Point ) )
		{
			VOSPoint pt;
			pMapDisp->MapToScreen( m_Point, pt );
			HFONT font =   CreateFont(                 
                m_size,//pFont-> xFont-> GetCxFont(),                                       //   nHeight 
                m_width,                                   //   nWidth 
                m_escapement,                                                   //   nEscapement 
                m_orientation,                                                   //   nOrientation 
                m_weight,//FW_BOLD,//FW_NORMAL,                                       //   nWeight 
                m_Italic,                                           //   bItalic 
                m_underline,                                           //   bUnderline	下划线
                m_strikeOut,                                                   //   cStrikeOut 删除线
                ANSI_CHARSET,                             //   nCharSet 
                OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
                CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
                DEFAULT_QUALITY,                       //   nQuality 
                DEFAULT_PITCH,//   |   FF_SWISS,     //   nPitchAndFamily 
                m_fontname// "Arial"// "system"         
			);
			HFONT oldfont = (HFONT)::SelectObject(hdc,font );
			int len = text.length();
			::SetTextColor( hdc, color );
			SetBkMode(hdc,TRANSPARENT);
			/*
			MoveToEx(hdc,pt.x,pt.y,NULL);
			LineTo( hdc,pt.x-15,pt.y-15);
			MoveToEx(hdc,pt.x,pt.y,NULL);
			LineTo( hdc,pt.x-15,pt.y);
			MoveToEx(hdc,pt.x,pt.y,NULL);
			LineTo( hdc,pt.x,pt.y-15);
			*/
			TEXTMETRIC tm;
			if( GetTextMetrics( hdc, &tm ) )
			{
				pt.x -= (tm.tmAveCharWidth*len)/2;
				pt.y -= tm.tmHeight/2;
			}
			::TextOut(hdc,pt.x,pt.y,text.c_str(),len);
			SelectObject(hdc,oldfont);
			DeleteObject( font );
		}	
	}
}