#include "StdAfx.h"
#include "MapCtrol.h"
#include "MapWnd.h"
CMapCtrol::CMapCtrol(void)
{
	m_bVisible = true;
}

CMapCtrol::~CMapCtrol(void)
{
	
}
//创建控件
void CMapCtrol::Create( int nID,CMapWnd* pParent )
{
	m_bVisible = true;
	this->m_nID = nID;
	m_pParent = pParent;
	m_pParent->AddChild( this );
}
void CMapCtrol::Create( int nID,int nLeft,int nTop,int nRight,int nBottom, CMapWnd* pParent )
{
	this->m_nID = nID;
	m_rect.left = nLeft;
	m_rect.right = nRight;
	m_rect.top = nTop;
	m_rect.bottom = nBottom;
	m_pParent = pParent;
	m_pParent->AddChild( this );
}
//单击属性
bool CMapCtrol::IsPointIn( VOSPoint point )
{
	if( !m_bVisible )
		return false;
	return m_rect.IsPointIn( point );
}
void CMapCtrol::SetVisible( bool bVisible )
{
	this->m_bVisible = bVisible;
}