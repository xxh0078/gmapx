// MapEdit.cpp: implementation of the CMapEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapEdit::CMapEdit()
{
	m_hWnd = NULL;
}

CMapEdit::~CMapEdit()
{

}
void CMapEdit::Create( int left,int top, int width,int height,HWND hWndParent )
{
	m_iLeft = left;
	m_iTop = top;
	m_iWidth= width;
	m_iHeight = height;
	m_hWnd=CreateWindow("edit",NULL,
	WS_CHILD|WS_VISIBLE|WS_BORDER,
	left,top,width,height,hWndParent,NULL,NULL,NULL);
}
void CMapEdit::SetPos( int left,int top)
{
	m_iLeft = left;
	m_iTop = top;
	::MoveWindow( m_hWnd, m_iLeft, m_iTop, m_iWidth, m_iHeight ,TRUE);
}
void CMapEdit::MoveWnd( int left,int top, int width,int height  )
{
	m_iLeft = left;
	m_iTop = top;
	m_iWidth= width;
	m_iHeight = height;
	::MoveWindow( m_hWnd, m_iLeft, m_iTop, width, height ,TRUE);
}
void CMapEdit::SetText(const TCHAR *pText,  DWORD dwSytle )
{
	m_dwSytle =  dwSytle;
	
	memset(m_szText, 0, MAX_PATH * sizeof(TCHAR)) ;
	strcpy(m_szText, pText);
	if(m_hWnd != NULL)    
	{
		SetWindowText(m_hWnd,pText);
		DWORD dOldSytle = GetWindowLong( m_hWnd, GWL_STYLE );
		dOldSytle |= dwSytle;
		SetWindowLong( m_hWnd, GWL_STYLE, dOldSytle );
		int nLength = strlen(m_szText)  ;
		SendMessage(m_hWnd, EM_SETSEL, nLength, nLength) ;
	}

}
TCHAR *CMapEdit::GetText()
{
	return m_szText;
}
void CMapEdit::DestroyWnd()
{
	
}
void CMapEdit::SetVisible(bool visible )
{
	if(visible )
		::ShowWindow( m_hWnd,SW_SHOW);
	else
		::ShowWindow( m_hWnd,SW_HIDE);
}