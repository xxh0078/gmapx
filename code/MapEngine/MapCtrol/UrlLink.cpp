// UrlLink.cpp: implementation of the CUrlLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UrlLink.h"
#include <vfw.h>
//#include <windows.h>
#include <shellapi.h>
#include <iostream>
#pragma comment(lib,"vfw32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUrlLink::CUrlLink()
{
	m_sFontSize = 20;
	m_lColor = RGB( 19, 110, 194 );
}

CUrlLink::~CUrlLink()
{

}
void CUrlLink::SetText( string strText )
{
	this->m_strText = strText;
}
void CUrlLink::SetUrl( string strUrl )
{
	if( strUrl.find("http://") == -1 )
	{
		m_strUrl = "http://";
		m_strUrl += strUrl;	
	}
	else
	{
		this->m_strUrl = strUrl;
	}
}
void CUrlLink::OpenURL()
{
	if( m_strUrl.find("gmapx") != m_strUrl.npos )
	{
		//ShellExecute(NULL,"open","http://www.amazon.cn/?tag=gshop365-23",NULL,NULL,SW_SHOWNORMAL);
		//http://click.union.360buy.com/JdClick/?unionId=22295&t=1&to=http://www.360buy.com/
		ShellExecute(NULL,"open",m_strUrl.c_str(),NULL,NULL,SW_SHOWNORMAL);	
	}
}
void CUrlLink::setPos(short sLeft, short sTop)
{
	m_rect.top = sTop;
	m_rect.left = sLeft;
	int iLen = m_strText.length();
//	TEXTMETRIC tm;
//	GetTextMetrics(hdc,&tm);
	m_rect.right = m_rect.left + iLen*m_sFontSize;
	m_rect.bottom = m_rect.top + m_sFontSize;
}
void CUrlLink::OnDraw( HDC hdc )
{
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor( hdc,   m_lColor   ); 
	HFONT font = CreateFont(                 
		m_sFontSize,//pFont-> xFont-> GetCxFont(),                                       //   nHeight 
		0,                                   //   nWidth 
		0,                                                   //   nEscapement 
		0,                                                   //   nOrientation 
		FW_NORMAL,                                       //   nWeight 
		false,                                           //   bItalic 
		false,                                           //   bUnderline 
		0,                                                   //   cStrikeOut 
		ANSI_CHARSET,                             //   nCharSet 
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision 
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision 
		DEFAULT_QUALITY,                       //   nQuality 
		DEFAULT_PITCH,//   |   FF_SWISS,     //   nPitchAndFamily 
		"system"// "Arial "// "system "         
	);			
	SelectObject( hdc, font );
	TextOut(hdc,m_rect.left,m_rect.top,m_strText.c_str(),m_strText.length());
	//::DrawText( hdc, sVer.c_str(),iLen ,&m_rcTestVersion,DT_LEFT);
	DeleteObject(font);
}
bool CUrlLink::IsPointIn( VOSPoint point )
{
	return m_rect.IsPointIn( point );
}
void CUrlLink::SetColor( long bgr )
{
	m_lColor = bgr;
}