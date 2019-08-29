#include "StdAfx.h"
#include "SlideButton.h"
#include "MapWnd.h"
CSlideButton::CSlideButton(void)
{
	m_iType = 0;
	m_bSelected = false;
	m_bDraglag = false;
}

CSlideButton::~CSlideButton(void)
{
	m_Image.Release();
	m_Image1.Release();
}
void CSlideButton::Create( int nID,vchar* pRootPath, vchar* pFileName,vchar* pFileName1,vchar* pFileNameSlide, long left, long top,CMapWnd* pParent )
{
	vchar strFileName[256]={0};
	strcat( strFileName, pRootPath );
	strcat( strFileName, pFileNameSlide );////GF..H
	m_ImageSlide.LoadImage(strFileName);
	CMapButton::Create( nID,pRootPath,pFileName,pFileName1,left,top,pParent);
	return;
}
//单击属性
bool CSlideButton::IsPointIn( VOSPoint point )
{
	if( !m_bVisible )
		return false;
	if( m_rect.IsPointIn( point ) )
		return true;
	else
	{
		VOSRect rect;
		rect.left = m_rect.left - 8;
		rect.right = m_rect.right + 8;
		rect.top = m_nPoxY;
		rect.bottom = m_nPoxY + m_ImageSlide.GetSize().cy;
		if( rect.IsPointIn( point ) )
			return true;
		else
			return false;
	}
}
//绘制按钮
void CSlideButton::OnDraw( HDC hdc )
{
	if( !m_bVisible )
		return;
	RECT rect;
	rect.left = m_rect.left;
	rect.top = m_rect.top;
	rect.right = m_rect.right;
	rect.bottom = m_rect.bottom;
	m_Image1.DrawTransparent( hdc,rect.left,rect.top );
//	if( m_nPos > m_nCount )
//		m_nPos = m_nCount;
	rect.bottom = m_nPoxY+2;
	m_Image.Draw( hdc,m_rect.left,m_rect.top, m_rect.width()-16,m_rect.height(),rect );

	m_ImageSlide.Draw( hdc,m_rect.left-8,rect.bottom-(m_ImageSlide.GetSize().cy/2) );
}
//设置被选择
void CSlideButton::SetSlidePos( int nPos,int nCount )
{
	if( nPos > nCount )
		nPos = nCount;
	if( nPos < 0 )
		nPos = 0;
	float nHeight = ( m_rect.height()-10 ) / (float)nCount;
	m_nPoxY = m_rect.top + 3 + nHeight*nPos;
}
//得到位置
int CSlideButton::GetSolidePos( int nCount )
{
	int nPos = 0;
	float nHeight = ( m_rect.height()- 10 )/(float)nCount;
	nPos = ( m_nPoxY - m_rect.top - 3) / nHeight;
	
	if( nPos > nCount )
		nPos = nCount;
	if( nPos < 0 )
		nPos = 0;
	nPos = nCount - nPos;
	return nPos;
}
bool CSlideButton::OnLButtonDown( VOSPoint point )
{
	if( !m_bVisible )
		return false;
	if( m_rect.IsPointIn( point ) )
	{
		VOSRect rect;
		rect.left = m_rect.left - 8;
		rect.right = m_rect.right + 8;
		rect.top = m_nPoxY;
		rect.bottom = m_nPoxY + m_ImageSlide.GetSize().cy;
		if( rect.IsPointIn( point ) )
		{
			
		}
		m_bDraglag = true;
		return true;
	}
	return false;
}
bool CSlideButton::OnLButtonUp( VOSPoint point)
{
	
	if( !m_bVisible )
		return false;
	if( m_bDraglag )
	//if( m_rect.IsPointIn( point ) )
	{
		m_nPoxY = point.y;
		if( point.y < m_rect.top + 3 )
			m_nPoxY = m_rect.top + 3;
		else if( point.y > m_rect.bottom - 3 )
			m_nPoxY = m_rect.bottom - 3;
		else
			m_nPoxY = point.y;
		m_bDraglag = false;
		m_pParent->Invalidate();
		return true;
	}
	return false;
}
//鼠标拖动
bool CSlideButton::OnMouseMove( VOSPoint point)
{
	if( !m_bVisible )
		return false;
	if( m_bDraglag )
	{
		m_nPoxY = point.y;
		if( point.y < m_rect.top + 3 )
			m_nPoxY = m_rect.top + 3;
		else if( point.y > m_rect.bottom - 3 )
			m_nPoxY = m_rect.bottom - 3;
		else
			m_nPoxY = point.y;
		m_pParent->Invalidate();
	}
	return true;
}
//鼠标移入移除操作
void CSlideButton::OnMouseMoveIn()
{
	//this->m_pParent->Invalidate();
}
void CSlideButton::OnMouseMoveOut()
{
	//this->m_pParent->Invalidate();
}