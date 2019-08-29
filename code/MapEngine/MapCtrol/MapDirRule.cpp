// MapDirRule.cpp: implementation of the CMapDirRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapDirRule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//extern CGMapxCtrl* g_pGmapxCtrl;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapDirRule::CMapDirRule()
{
	m_bActive = false;
	m_iState = 0;
}

CMapDirRule::~CMapDirRule()
{
	m_bActive = false;
}
//初始化资源文件根目录
bool CMapDirRule::Init( CMapDisp* pMapDisp )
{
	m_pMapDisp = pMapDisp;
	return 1;
}
//鼠标消息
bool CMapDirRule::OnLButtonDown( VOSPoint point )
{
	if( m_iState == 1 )
	{
		SetStartPoint( point );
	}
	else if( m_iState == 2 )
	{
		SetEndPoint( point );
	}
	else if( m_iState ==  3 )
	{
		SetStartPoint( point );
	}
	return false;
}
bool CMapDirRule::OnLButtonUp( VOSPoint point)
{
	return false;
}
bool CMapDirRule::OnMouseMove( VOSPoint point)
{
	return false;
}
bool CMapDirRule::OnLButtonDblClk( VOSPoint point )
{
	return false;
}
bool CMapDirRule::OnMouseWheel( short zDelta, VOSPoint point)
{
	return false;
}
//开始设置
void CMapDirRule::OnStart()
{
	m_bActive = true;
	m_iState = 1;
}
//结束设置
void CMapDirRule::OnEnd()
{
}
//结束设置
void CMapDirRule::OnStop()
{
	m_iState = 0;
}
//设置起点;
bool CMapDirRule::SetStartPoint(VOSPoint point)
{
	m_pMapDisp->ScreenToMap(point,m_mptStart);
	m_iState = 2;
	return 1;
}
//设置终点
bool CMapDirRule::SetEndPoint(VOSPoint point)
{
	m_pMapDisp->ScreenToMap(point,m_mptEnd);
	CProject mapProject;
	m_lMapLength = mapProject.CalLength(m_mptStart.x,m_mptStart.y,m_mptEnd.x,m_mptEnd.y);
	m_lDirection = CMapBase::AzimuthAngle(m_mptStart.x,m_mptStart.y,m_mptEnd.x,m_mptEnd.y);
//xxh	g_pGmapxCtrl->FireOnMapToolsDistance( m_mptStart.x,m_mptStart.y,m_mptEnd.x,m_mptEnd.y,m_lMapLength,m_lDirection);
	m_iState = 3;
	return 1;
}
//设置当前鼠标点
void CMapDirRule::SetMousePoint( VOSPoint point )
{
	m_pntMouse.x = point.x;
	m_pntMouse.y = point.y;
	this->m_pMapDisp->Invalidate();
}
void CMapDirRule::OnDraw( HDC hdc )
{
	//SetTextColor(hdc,RGB(241,122,54));
	if ( m_iState == 1 ) 
	{
		SetBkMode(hdc,TRANSPARENT);
		string strText = "请单击地图选择起点！";
		::TextOut( hdc, m_pntMouse.x,m_pntMouse.y,strText.c_str(),strText.length());
		//::DrawText( hdc, strText.c_str(),strText.length() ,&m_rcWnd,DT_CENTER);
		//MoveToEx(hdc,   100+20,   100,   NULL); 
		//AngleArc(hdc,   100,   100,   20,   0,   360);
	}
	else if( m_iState == 2 )
	{
		HBRUSH hBr, hOldBr; 
		HPEN hPen,hOldPen; 
		hPen=::CreatePen(PS_SOLID,2,RGB(241,122,54));
		hOldPen=(HPEN)SelectObject(hdc,hPen); 
		hBr = (HBRUSH) GetStockObject (RGB(241,122,54));
		hOldBr = (HBRUSH) SelectObject (hdc, hBr);
		
		VOSPoint point;
		m_pMapDisp->MapToScreen(m_mptStart,point);
		::Ellipse(hdc,point.x-3,point.y-3,point.x+3,point.y+3);
		
		MoveToEx( hdc,point.x,point.y,NULL);
		LineTo( hdc,m_pntMouse.x,m_pntMouse.y);


		int radius = ::sqrt( ::pow((double)(point.x - m_pntMouse.x),2)+::pow((double)(point.y- m_pntMouse.y),2));
		MoveToEx(hdc,   point.x+radius,   point.y,   NULL); 
		//AngleArc(hdc,   point.x,   point.y,   radius,   0,   360);
		
		MapPoint mapPoint;

		m_pMapDisp->ScreenToMap(m_pntMouse,mapPoint);
		CProject mapProject;
		long lMapLength = mapProject.CalLength(m_mptStart.x,m_mptStart.y,mapPoint.x,mapPoint.y);
		//long ljiaodu = atan
//		long A1 = arcsin ( sin (90 - mapPoint.y) * sin (mapPoint.x - m_mptStart.x) / sin (b) ) .
		long A1 = CMapBase::AzimuthAngle(m_mptStart.x,m_mptStart.y,mapPoint.x,mapPoint.y);
		char cTemp[128]={0};
		if( lMapLength < 1000 )
		{
			sprintf(cTemp, "距离:%dm，方位角：%d度",lMapLength,A1);
		}
		else
		{
			double dLen = (double)lMapLength/1000.0;
			sprintf(cTemp, "距离:%.02fkm，方位角：%d度",dLen,A1);
		}
		SetBkMode(hdc,TRANSPARENT);
		string strText = "请单击地图设置选择点！";
		//::Ellipse(hdc,point.x - m_pntMouse.x,m_pntMouse.y- m_pntMouse.y,point.x + m_pntMouse.x,m_pntMouse.y + m_pntMouse.y);
		::TextOut( hdc, m_pntMouse.x,m_pntMouse.y,strText.c_str(),strText.length());
		::TextOut( hdc, m_pntMouse.x+20,m_pntMouse.y-20,cTemp,strlen(cTemp));

		::SelectObject(hdc,hOldPen); 
		::DeleteObject(hPen);
		::SelectObject (hdc, hOldBr);
		::DeleteObject(hBr);
	}
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
		
		MoveToEx( hdc,point1.x,point1.y,NULL);
		LineTo( hdc,point2.x,point2.y);

		int radius = ::sqrt( ::pow((double)(point1.x - point2.x),2)+::pow((double)(point1.y- point2.y),2));
		MoveToEx(hdc,   point1.x+radius,   point1.y,   NULL); 
		//AngleArc(hdc,   point1.x,   point1.y,   radius,   0,   360);

		::Ellipse(hdc,point1.x-3,point1.y-3,point1.x+3,point1.y+3);
		::Ellipse(hdc,point2.x-3,point2.y-3,point2.x+3,point2.y+3);

		//CProject mapProject;
		//long lMapLength = mapProject.CalLength(m_mptStart.x,m_mptStart.y,m_mptEnd.x,m_mptEnd.y);
		//long ljiaodu = atan
		//long A1 = CMapBase::AzimuthAngle(m_mptStart.x,m_mptStart.y,m_mptEnd.x,m_mptEnd.y);
		char cTemp[128]={0};
		if( m_lMapLength < 1000 )
		{
			sprintf(cTemp, "距离:%dm，方位角：%d度",m_lMapLength,m_lDirection);
		}
		else
		{
			double dLen = (double)m_lMapLength/1000.0;
			sprintf(cTemp, "距离:%.02fkm，方位角：%d度",dLen,m_lDirection);
		}
		::TextOut( hdc, point2.x+20,point2.y-20,cTemp,strlen(cTemp));

		SelectObject (hdc, hOldBr);
		SelectObject (hdc, hOldPen);
		::DeleteObject(hPen);
		::DeleteObject(hBr);
	}
}
//0为无效，1为等待设置起点，2为等待设置终点，3为设置终点结束
int  CMapDirRule::GetState()
{
	return this->m_iState;
}