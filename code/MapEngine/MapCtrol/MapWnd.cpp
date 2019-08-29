#include "StdAfx.h"
#include "MapWnd.h"
CMapWnd::CMapWnd(void)
{
	m_pCtrolMouseIn = NULL;
	m_pLastCtrol = NULL;
	m_hCursor = LoadCursor(NULL,MAKEINTRESOURCE(32649));
}

CMapWnd::~CMapWnd(void)
{

}
//创建窗口
void CMapWnd::Create( HWND hWnd )
{
	m_hWnd = hWnd;
}
//绘制
void CMapWnd::OnDraw( HDC hdc )
{
	for( int i=0;i<m_arrMapCtrol.size();i++ )
	{
		m_arrMapCtrol[i]->OnDraw( hdc );
	}
}
//鼠标消息
bool CMapWnd::OnLButtonDown( VOSPoint point )
{
	for ( int i=m_arrMapCtrol.size()-1;i>=0 ;i-- )
    {
		if( m_arrMapCtrol[i]->IsPointIn( point ) )
		{
			m_pLastCtrol = m_arrMapCtrol[i];
			return m_arrMapCtrol[i]->OnLButtonDown( point );
		}
    }
	return false;
}
bool CMapWnd::OnLButtonUp( VOSPoint point)
{
	if( m_pLastCtrol != NULL )
	{
		m_pLastCtrol->OnLButtonUp( point );
		//如果鼠标UP事件在控件内，则响应事件
		//if(m_pLastCtrol->IsPointIn( point ) )
		{
			//::PostMessage( m_hWnd, VOS_WM_COMMAND ,m_pLastCtrol->GetID(), 0 );
			PostMessage( VOS_WM_COMMAND,m_pLastCtrol->GetID(),0);
		}
		m_pLastCtrol = NULL;
		return true;
	}
	return false;
}
bool CMapWnd::OnMouseMove( VOSPoint point)
{
	for ( int i=m_arrMapCtrol.size()-1;i>=0 ;i-- )
    {
		if( m_arrMapCtrol[i]->IsPointIn( point ) )
		{
			if( m_pCtrolMouseIn != m_arrMapCtrol[i] )
			{
				if( m_pCtrolMouseIn != NULL )
				{
					m_pCtrolMouseIn->OnMouseMoveOut();
				}
				m_pCtrolMouseIn = m_arrMapCtrol[i];
				m_pCtrolMouseIn->OnMouseMoveIn();
			}
			if( m_arrMapCtrol[i]->OnMouseMove( point ) )
			{
				SetCursor(m_hCursor);
				this->Invalidate();
				return true;
			}
			else
				return false;
		}
    }
	if( m_pCtrolMouseIn != NULL )
	{
		m_pCtrolMouseIn->OnMouseMoveOut();
		m_pCtrolMouseIn = NULL;
	}
	return false;
}
bool CMapWnd::OnLButtonDblClk( VOSPoint point )
{
	for ( int i=m_arrMapCtrol.size()-1;i>=0 ;i-- )
    {
		if( m_arrMapCtrol[i]->IsPointIn( point ) )
		{
			return m_arrMapCtrol[i]->OnLButtonDblClk( point );
		}
    }
	return false;
}
bool CMapWnd::OnMouseWheel( short zDelta, VOSPoint point)
{
	for ( int i=m_arrMapCtrol.size()-1;i>=0 ;i-- )
    {
		if( m_arrMapCtrol[i]->IsPointIn( point ) )
		{
			return m_arrMapCtrol[i]->OnMouseWheel(zDelta, point );
		}
    }
	return false;
}
//添加控件
void CMapWnd::AddChild( CMapCtrol* pCtrol )
{
	m_arrMapCtrol.push_back( pCtrol );
}

//得到控件
CMapCtrol* CMapWnd::GetCtrol( int nID )
{
	CMapCtrol* pCtrol = NULL;
	for( int i=0;i<m_arrMapCtrol.size();i++ )
	{
		if( m_arrMapCtrol[i]->GetID() == nID )
		{
			return m_arrMapCtrol[i];
		}
	}
	return NULL;
}
//刷新屏幕
void CMapWnd::Invalidate()
{
	if( m_hWnd == NULL )
		return;
	::InvalidateRect( m_hWnd, NULL , false );
}
//发送消息
bool CMapWnd::PostMessage( int nMessage,long lParam1, long lParam2 )
{
	if( m_hWnd == NULL )
		return false;
	return ::PostMessage( m_hWnd, nMessage, lParam1,lParam2 );
}
//命令
void CMapWnd::OnCommand( int id, int param1,int param2 )
{

}