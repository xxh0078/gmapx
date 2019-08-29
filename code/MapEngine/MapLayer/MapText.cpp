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
	m_fontname = "����";
}

CMapText::~CMapText()
{

}
//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
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
                m_underline,                                           //   bUnderline	�»���
                m_strikeOut,                                                   //   cStrikeOut ɾ����
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