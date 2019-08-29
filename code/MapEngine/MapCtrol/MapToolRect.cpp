// MapDirRule.cpp: implementation of the CMapToolRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapToolRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapToolRect::CMapToolRect()
{
	m_bActive = false;
	m_iState = 0;
}

CMapToolRect::~CMapToolRect()
{
	m_bActive = false;
}
//初始化资源文件根目录
bool CMapToolRect::Init( CMapDisp* pMapDisp,string strFileName, CVOSImage* pImageDel )
{
	m_pMapDisp = pMapDisp;
	m_pImageDel = pImageDel;
	if ( m_Image.LoadImage( strFileName ) )
	{
		return true;
	}
	m_bActive = false;
	return false;
}
//鼠标消息
bool CMapToolRect::OnLButtonDown( VOSPoint point )
{
	if( !m_bActive )
		return false;
	if( m_iState == 1 )
		SetStartPoint( point );
	if( m_iState == 3 )
	{
		if( this->m_rectDel.IsPointIn( point ) )
		{
			OnStop();
			this->m_pMapDisp->Invalidate();
			if( g_fun_msg != NULL )
			{
				g_fun_msg( MAP_TOOL_MESSAGE, 4, 0, "" );
			}
			else
			{
				g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 4, 0, "" );
			}
		}
	}
	return true;
}
bool CMapToolRect::OnLButtonUp( VOSPoint point)
{
	if( !m_bActive )
		return false;
	if( m_iState == 2 )
		SetEndPoint( point );
	return true;
}
bool CMapToolRect::OnMouseMove( VOSPoint point)
{
	if( !m_bActive )
		return false;
	if( m_iState == 2 )
		SetMousePoint( point );
	return true;
}
bool CMapToolRect::OnLButtonDblClk( VOSPoint point )
{
	if( !m_bActive )
		return false;
	return true;
}
bool CMapToolRect::OnMouseWheel( short zDelta, VOSPoint point)
{
	if( !m_bActive )
		return false;
	return true;
}
//开始设置
void CMapToolRect::OnStart()
{
	m_bActive = true;
	m_iState = 1;
	m_rectDel.left = 0;
	m_rectDel.right = 0;
	m_rectDel.top = 0;
	m_rectDel.bottom = 0;
}
//结束设置
void CMapToolRect::OnStop()
{
	m_bActive = false;
	m_iState = 0;
}
//设置起点;
bool CMapToolRect::SetStartPoint(VOSPoint point)
{
	m_pMapDisp->ScreenToMap(point,m_mptLast);
	m_pMapDisp->ScreenToMap(point,m_mptMouse);
	m_iState = 2;
	return 1;
}
//设置终点
bool CMapToolRect::SetEndPoint(VOSPoint point)
{
	//m_pMapDisp->ScreenToMap(point,m_mptEnd);
	m_pMapDisp->ScreenToMap(point,m_mptMouse);
	m_iState = 3;
	this->m_pMapDisp->Invalidate();
	char cTemp[128];
	sprintf( cTemp, "%f,%f;%f,%f", m_mptLast.x, m_mptLast.y, m_mptMouse.x, m_mptMouse.y );
	if( g_fun_msg != NULL )
	{	
		g_fun_msg( MAP_TOOL_MESSAGE, 4, 1, cTemp );
	}
	else
	{
		g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 4, 1, cTemp );
	}
	return true;
}
//设置当前鼠标点
void CMapToolRect::SetMousePoint( VOSPoint point )
{
	if( m_iState == 2 )
	{
		m_ptMouse.x = point.x;
		m_ptMouse.y = point.y;
		this->m_pMapDisp->Invalidate();
	}	
}
void CMapToolRect::OnDraw( HDC hdc )
{
	if( m_iState == 2 )
	{
		VOSPoint ptStart;
		m_pMapDisp->MapToScreen(m_mptLast,ptStart);
		//m_pMapDisp->MapToScreen(m_mptMouse,ptEnd);
		m_Image.AlphaDraw(hdc,min( ptStart.x,m_ptMouse.x),min(ptStart.y,m_ptMouse.y),abs(m_ptMouse.x-ptStart.x),abs(m_ptMouse.y-ptStart.y),100 );
		//::Rectangle( hdc, point.x,point.y,m_pntMouse.x,m_pntMouse.y );		
	}
	
	else if( m_iState == 3 )
	{
		VOSPoint ptStart,ptEnd;
		m_pMapDisp->MapToScreen(m_mptLast,ptStart);
		m_pMapDisp->MapToScreen(m_mptMouse,ptEnd);
		m_Image.AlphaDraw(hdc,min( ptStart.x,ptEnd.x),min(ptStart.y,ptEnd.y),abs(ptEnd.x-ptStart.x),abs(ptEnd.y-ptStart.y),100 );

		//--绘制删除按钮
		m_rectDel.left = ptEnd.x + 3;
		m_rectDel.bottom = ptEnd.y + 3;
		m_rectDel.top = m_rectDel.bottom - m_pImageDel->GetSize().cy;
		m_rectDel.right = m_rectDel.left + m_pImageDel->GetSize().cx;
		m_pImageDel->Draw( hdc, m_rectDel );
	}
}