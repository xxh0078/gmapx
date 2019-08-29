#include "StdAfx.h"
#include "MapButton.h"
#include "MapWnd.h"
CMapButton::CMapButton(void)
{
	m_iType = 0;
	m_bSelected = false;
}

CMapButton::~CMapButton(void)
{
	m_Image.Release();
}
//初始化
void CMapButton::Create( int nID, vchar* pRootPath, vchar* pFileName,  long left, long top,CMapWnd* pParent )
{
	vchar strFileName[256]={0};
	strcat( strFileName, pRootPath );
	strcat( strFileName, pFileName );
	if ( m_Image.LoadImage( strFileName ) )
	{
		m_rect.left = left;
		m_rect.top = top;
		m_rect.right = left+m_Image.GetSize().cx;
		m_rect.bottom = top+m_Image.GetSize().cy;
	}
	m_pParent = pParent;
	m_nID = nID;
	m_pParent->AddChild( this );
}
void CMapButton::Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,  long left, long top,CMapWnd* pParent )
{
	vchar strFileName[256]={0};
	strcat( strFileName, pRootPath );
	strcat( strFileName, pFileName );////GF..H
	if ( m_Image.LoadImage( strFileName ) )
	{
		m_rect.left = left;
		m_rect.top = top;
		m_rect.right = left+m_Image.GetSize().cx;
		m_rect.bottom = top+m_Image.GetSize().cy;
	}
	strcpy( strFileName, pRootPath );
	strcat( strFileName, pFileName1 );
	if ( m_Image1.LoadImage( strFileName ) ) {
		m_iType = 1;
	}
	m_pParent = pParent;
	m_nID = nID;
	m_pParent->AddChild( this );
}
//重新设置位置
void CMapButton::ReSetPos( long left, long top )
{
	m_rect.left = left;
	m_rect.top = top;
	m_rect.right = left+m_Image.GetSize().cx;
	m_rect.bottom = top+m_Image.GetSize().cy;
}
//单击属性
bool CMapButton::IsPointIn( VOSPoint point )
{
	if( !m_bVisible )
		return false;
	return m_rect.IsPointIn( point );
}
//绘制按钮
void CMapButton::OnDraw( HDC hdc )
{
	if( !m_bVisible )
		return;
	if( m_bSelected )
		m_Image1.DrawTransparent( hdc,m_rect.left,m_rect.top );
	else
		m_Image.DrawTransparent( hdc,m_rect.left,m_rect.top );
}
//绘制按钮
void CMapButton::OnDrawSel( HDC hdc )
{
	if( !m_bVisible )
		return;
	m_Image1.DrawTransparent( hdc,m_rect.left,m_rect.top );
}
//绘制半透明按钮
void CMapButton::OnDrawTransparent( HDC hdc )
{
	if( !m_bVisible )
		return;
	m_Image.DrawTransparent( hdc,m_rect.left,m_rect.top );
}
//得到bound
VOSRect* CMapButton::GetBoundsRect()
{
	return &m_rect;
}
//设置被选择
void CMapButton::SetSelected( bool bSelected )
{
	this->m_bSelected = bSelected;
}
//
bool CMapButton::OnLButtonDown( VOSPoint point )
{
	if( !m_bVisible )
		return false;
	if( m_rect.IsPointIn( point ) )
		return true;
	else
		return false;
}
bool CMapButton::OnLButtonUp( VOSPoint point)
{
	if( !m_bVisible )
		return false;
	if( m_rect.IsPointIn( point ) )
		return true;
	else
		return false;
}
//鼠标拖动
bool CMapButton::OnMouseMove( VOSPoint point)
{
	if( !m_bVisible )
		return false;
	if( m_rect.IsPointIn( point ) )
		return true;
	else
		return false;
}
//鼠标移入移除操作
void CMapButton::OnMouseMoveIn()
{
	if( !m_bVisible )
		return;
	SetSelected( true );
	this->m_pParent->Invalidate();
}
void CMapButton::OnMouseMoveOut()
{
	if( !m_bVisible )
		return;
	SetSelected( false );
	this->m_pParent->Invalidate();
}