// MapDirRule.cpp: implementation of the CMapToolAround class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapToolAround.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapToolAround::CMapToolAround()
{
	m_iState = 0;
	m_bActive = false;
}

CMapToolAround::~CMapToolAround()
{
	m_bActive = false;
}
//初始化资源文件根目录
bool CMapToolAround::Init( CMapDisp* pMapDisp,string strFileName, CVOSImage* pImageDel )
{
	m_bActive = false;
	m_pMapDisp = pMapDisp;
	m_pImageDel = pImageDel;
	if ( m_Image.LoadImage( strFileName ) )
	{
		return true;
	}
	return false;
}
//鼠标消息
bool CMapToolAround::OnLButtonDown( VOSPoint point )
{
	if( !m_bActive )
		return false;
	if( m_iState == 1 )
	{
		SetStartPoint( point );
	}
	if( m_iState == 3 )
	{
		if( this->m_rectDel.IsPointIn( point ) )
		{
			OnStop();
			this->m_pMapDisp->Invalidate();
			if( g_fun_msg != NULL )
			{
				g_fun_msg( MAP_TOOL_MESSAGE, 5, 0, "" );
			}
			else
			{
				g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 5, 0, "" );
			}
		}
	}
	return true;
}
bool CMapToolAround::OnLButtonUp( VOSPoint point)
{
	if( !m_bActive )
		return false;
	if( m_iState == 2 )
	{
		SetEndPoint( point );
	}
	return true;
}
bool CMapToolAround::OnMouseMove( VOSPoint point)
{
	if( !m_bActive )
		return false;
	if( m_iState == 2 )
	{
		SetMousePoint( point );
	}
	return true;
}
bool CMapToolAround::OnLButtonDblClk( VOSPoint point )
{
	if( !m_bActive )
		return false;
	return true;
}
bool CMapToolAround::OnMouseWheel( short zDelta, VOSPoint point)
{
	if( !m_bActive )
		return false;
	return true;
}
//开始设置
void CMapToolAround::OnStart()
{
	m_bActive = true;
	m_iState = 1;
}
//结束设置
void CMapToolAround::OnStop()
{
	m_bActive = false;
	m_iState = 0;
}
//设置起点;
bool CMapToolAround::SetStartPoint(VOSPoint point)
{
	m_pMapDisp->ScreenToMap(point,m_mptLast);
	m_iState = 2;
	return 1;
}
//设置终点
bool CMapToolAround::SetEndPoint(VOSPoint point)
{
	this->m_ptMouse.x = point.x;
	this->m_ptMouse.y = point.y;
	m_iState = 3;
	
	m_pMapDisp->ScreenToMap(m_ptMouse,m_mptMouse);

	CProject mapProject;
	long lMapLength = mapProject.CalLength(m_mptLast.x,m_mptLast.y,m_mptMouse.x,m_mptMouse.y);
	char cTemp[128];
	sprintf( cTemp, "%f,%f,%d", m_mptLast.x, m_mptLast.y, lMapLength );

	if( g_fun_msg != NULL )
	{
		g_fun_msg( MAP_TOOL_MESSAGE, 5, 1, cTemp );
	}
	else
	{
		g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 5, 1, cTemp );
	}
	this->m_pMapDisp->Invalidate();
	return 1;
}
//设置当前鼠标点
void CMapToolAround::SetMousePoint( VOSPoint point )
{
	m_ptMouse.x = point.x;
	m_ptMouse.y = point.y;
	this->m_pMapDisp->Invalidate();
}
//inline void stroke_line(int x1, int y1, int x2, int y2, agg::rgba8& color);
void CMapToolAround::OnDraw( HDC hdc, agg::rendering_buffer* rbuf )
{
	if( !m_bActive )
		return;
	VOSPoint ptStart;
	m_pMapDisp->MapToScreen(m_mptLast,ptStart);
	if( m_iState == 2 || m_iState == 3 )
	{		
		int ndx = abs( ptStart.x-m_ptMouse.x );
		int ndy = abs( ptStart.y-m_ptMouse.y );
		double nLen = sqrt( (double)(ndx*ndx + ndy*ndy) );
		m_Image.AlphaDraw(hdc,ptStart.x - nLen,ptStart.y - nLen, nLen*2,
			nLen*2,100 );
	}
	if( m_iState == 3 )
	{
		//--绘制删除按钮
		m_rectDel.left = ptStart.x + 3;
		m_rectDel.bottom = ptStart.y + 3;
		m_rectDel.top = m_rectDel.bottom - m_pImageDel->GetSize().cy;
		m_rectDel.right = m_rectDel.left + m_pImageDel->GetSize().cx;
		m_pImageDel->Draw( hdc, m_rectDel );
	}
	/*
	else if( m_iState == 3 )
	{
		HBRUSH hBr, hOldBr; 
		HPEN hPen,hOldPen; 
		hPen=::CreatePen(PS_SOLID,2,RGB(241,122,54));
		hOldPen=(HPEN)SelectObject(hdc,hPen); 
		hBr = (HBRUSH) GetStockObject (RGB(241,122,54));
		hOldBr = (HBRUSH) SelectObject (hdc, hBr);

		VOSPoint point1,point2;
		m_pMapDisp->MapToScreen(m_mptStart,point1);
		m_pMapDisp->MapToScreen(m_mptEnd,point2);
		//::Rectangle( hdc, point2.x-3,point2.y-3,point1.x+3,point1.y+3 );
		//m_Image.AlphaDraw(hdc,point1.x,point1.y,abs(point2.x-point1.x),abs(point2.y-point1.y),100 );
		m_Image.AlphaDraw(hdc,min( point1.x,point2.x),min(point1.y,point2.y),abs(point2.x-point1.x),abs(point2.y-point1.y),100 );
		SelectObject (hdc, hOldBr);
		SelectObject (hdc, hOldPen);
	}*/
}