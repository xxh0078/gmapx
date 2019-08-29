#include "stdafx.h"
#include "MapRectangle.h"


CMapRectangle::CMapRectangle()
{
	m_dbLeft = 0.0;
	m_dbRight = 0.0;
	m_dbTop = 0.0;
	m_dbBottom = 0.0;   


}


CMapRectangle::CMapRectangle(CMapRectangle& MapRectangle )
{

	m_dbLeft = MapRectangle.m_dbLeft;
	m_dbRight = MapRectangle.m_dbRight;
	m_dbTop = MapRectangle.m_dbTop;
	m_dbBottom = MapRectangle.m_dbBottom;   


}

CMapRectangle::~CMapRectangle()
{


}
