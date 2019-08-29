// MarkMapPoint.cpp: implementation of the CMarkMapPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MarkMapPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMarkMapPoint::CMarkMapPoint()
{

}

CMarkMapPoint::~CMarkMapPoint()
{

}
//初始化资源文件根目录
bool CMarkMapPoint::Init( CMapDisp* pMapDisp, char* strPath )
{
	char strName[256]={0};
	m_pMapDisp = pMapDisp;

	strcpy( strName, strPath );
	strcat( strName, "mark1.png" );
	m_ImageMark.LoadImage( strName );
	strcpy( strName, strPath );
	strcat( strName, "del.png" );
	m_ImageDel.LoadImage( strName );
	m_bMark = false;
	return false;
}
//绘制
void CMarkMapPoint::OnDraw( HDC hdc )
{
	//MapPoint* pNew = new MapPoint();
	//m_pMapDisp->ScreenToMap(point,*pNew);
	if( !m_bMark )
		return;
	if( m_bStart )
	{
		m_ImageMark.Draw( hdc, m_ptMouse.x - m_ImageMark.GetSize().cx/2, m_ptMouse.y - m_ImageMark.GetSize().cy );
	}
	else
	{
		VOSPoint pt;
		VOSSize sz = m_ImageMark.GetSize();
		m_pMapDisp->MapToScreen( m_mptPoint, pt );
		m_ImageMark.Draw( hdc, pt.x - sz.cx/2, pt.y - sz.cy );

		m_rectDel.left = pt.x + sz.cx/2;
		m_rectDel.bottom = pt.y + sz.cy/2;
		m_rectDel.right = m_rectDel.left + m_ImageDel.GetSize().cx;
		m_rectDel.top = m_rectDel.bottom - m_ImageDel.GetSize().cy;
		m_ImageDel.Draw( hdc, m_rectDel );
	}
}
//标记地图
void CMarkMapPoint::SetMark( bool bMark )
{
	m_bMark = bMark;
	m_bStart = true;
}
//鼠标消息
bool CMarkMapPoint::OnLButtonDown( VOSPoint point )
{
	if( !m_bMark )
		return false;
	return false;
}
bool CMarkMapPoint::OnLButtonUp( VOSPoint point)
{
	if( !m_bMark )
		return false;
	if( m_bStart )
	{
		m_pMapDisp->ScreenToMap(point,m_mptPoint);
		m_bStart = false;
		m_pMapDisp->Invalidate();

		char temp[100]={0};
		sprintf( temp, "%f,%f",m_mptPoint.x,m_mptPoint.y);
		if( g_fun_msg != NULL )
		{
			
			g_fun_msg( MAP_TOOL_MESSAGE, 6, 1, temp );
		}
		else
		{
			g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 6, 1, temp );
		}
	}
	else
	{
		if( m_rectDel.IsPointIn( point ) )
		{
			m_bStart = true;
			m_bMark = false;
			m_pMapDisp->Invalidate();	
			if( g_fun_msg != NULL )
			{
				g_fun_msg( MAP_TOOL_MESSAGE, 6, 0, NULL );
			}
			else
			{
				g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 6, 0, NULL );
			}
		}
	}
	return false;
}
bool CMarkMapPoint::OnMouseMove( VOSPoint point)
{
	if( !m_bMark )
		return false;
	m_ptMouse.x = point.x;
	m_ptMouse.y = point.y;
	if( m_bStart )
	{
		m_pMapDisp->Invalidate();
	}
	return false;
}
bool CMarkMapPoint::OnLButtonDblClk( VOSPoint point )
{
	if( !m_bMark )
		return false;
	return false;
}
bool CMarkMapPoint::OnMouseWheel( short zDelta, VOSPoint point)
{
	if( !m_bMark )
		return false;
	return false;
}
