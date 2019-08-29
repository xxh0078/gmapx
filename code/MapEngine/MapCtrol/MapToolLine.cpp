// MapToolLine.cpp: implementation of the CMapToolLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapToolLine.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapToolLine::CMapToolLine()
{
	m_pMapLayer = NULL;
	m_pMapLine = NULL;
	m_pMapDisp = NULL;
	m_iFlag = 0;
	m_lineID = 0x0850;
}

CMapToolLine::~CMapToolLine()
{
	m_pMapDisp = NULL;
	m_pMapLine = NULL;
	m_iFlag = 0;
}
//初始化资源文件根目录
bool CMapToolLine::Init( CMapDisp* pMapDisp, CMapLayer* pMapLayer, CVOSImage* pImageDel )
{
	m_pMapDisp = pMapDisp;
	m_pMapLayer = pMapLayer;
	m_pImageDel = pImageDel;
	m_iFlag = 0;
	return 1;
}
//激活画线工具
void CMapToolLine::SetActive( bool bActive  )
{
	if( bActive )
	{
		this->Create( );
	}
	else
	{
		this->Clean();
	}
}
//鼠标消息
bool CMapToolLine::OnLButtonDown( VOSPoint point )
{
	TRACE( "OnLButtonDown--- " );
	if( !m_iFlag )
		return false;
	if( 1 == m_iFlag || 2 == m_iFlag )
	{
		AddPoint( point );
	}
	if( this->m_rectDel.IsPointIn( point ) )
	{
		Clean();
		//回调函数
		if( g_fun_msg != NULL )
		{
			g_fun_msg( MAP_TOOL_MESSAGE, 2, 0, "" );
		}
		else
		{
			g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 2, 0, "" );
		}
	}
	return true;
}
bool CMapToolLine::OnLButtonUp( VOSPoint point)
{
	TRACE( "OnLButtonUp---" );
	if( !m_iFlag )
		return false;
	return false;
}
bool CMapToolLine::OnMouseMove( VOSPoint point)
{
	if( !m_iFlag )
		return false;
	if( 1 == m_iFlag || 2 == m_iFlag )
	{
		m_ptMouse.x = point.x;
		m_ptMouse.y = point.y;
		m_pMapDisp->Invalidate();
	}
	return true;
}
bool CMapToolLine::OnLButtonDblClk( VOSPoint point )
{
	
	TRACE( "OnLButtonDblClk---" );
	if( !m_iFlag )
		return false;
	if( 1 == m_iFlag || 2 == m_iFlag )
	{
		Save();
		m_iFlag = 3;
		End();
	}
	return true;
}
bool CMapToolLine::OnMouseWheel( short zDelta, VOSPoint point)
{
	if( !m_iFlag )
		return false;
	return true;
}
void CMapToolLine::OnDraw( HDC hdc )
{
	if( !m_iFlag )
		return;
	if( 1 == m_iFlag || 2 == m_iFlag )
	{
		if( 2 == m_iFlag )
		{
			VOSPoint ptn;
			m_pMapDisp->MapToScreen(m_mptLast,ptn);
			MoveToEx( hdc, ptn.x, ptn.y, NULL );
			LineTo( hdc, m_ptMouse.x, m_ptMouse.y );
		}
		::Ellipse(hdc,m_ptMouse.x-3,m_ptMouse.y-3,m_ptMouse.x+3,m_ptMouse.y+3);
		string str = "双击保存";
		TextOut( hdc, m_ptMouse.x+3,m_ptMouse.y+3, str.c_str(), str.length() );
	}
	if( m_iFlag == 3 )
	{
		VOSPoint ptn;
		m_pMapDisp->MapToScreen(m_mptLast,ptn);
		//--绘制删除按钮
		m_rectDel.left = ptn.x + 3;
		m_rectDel.bottom = ptn.y + 3;
		m_rectDel.top = m_rectDel.bottom - m_pImageDel->GetSize().cy;
		m_rectDel.right = m_rectDel.left + m_pImageDel->GetSize().cx;
		m_pImageDel->Draw( hdc, m_rectDel );
	}
}
//创建画线
void CMapToolLine::Create()
{
	//return ;
	Clean();
	m_iFlag = 1;
	m_rectDel.left = 0;
	m_rectDel.right = 0;
	m_rectDel.top = 0;
	m_rectDel.bottom = 0;
//	char cTemp[100];
	//sprintf( cTemp, "m_pMapLayer=%d\n",m_pMapLayer);
	//CVOSUtil::MessageBox( cTemp,"");
	m_lineID ++;
	if( m_pMapLayer->CreatMapLine( m_lineID ) )
	{
		//sprintf( cTemp, "m_pMapLayer=%d m_lineID=%d\n",m_pMapLayer,m_lineID);
		//CVOSUtil::MessageBox( cTemp,"");
		m_pMapLine = m_pMapLayer->GetMapLine( m_lineID );
		m_pMapLine->SetColor(RGB(255,0,0));
		m_pMapLine->SetWidth( 3 );
	}
}
//添加画线点
void CMapToolLine::AddPoint( VOSPoint point )
{
	//m_mptLast.x = point.x;
	//m_mptLast.y = point.y;
	m_iFlag = 2;
	MapPoint* pNew = new MapPoint();
	m_pMapDisp->ScreenToMap(point,*pNew);
	m_mptLast.x = pNew->x;
	m_mptLast.y = pNew->y;
	m_pMapLayer->AddMapLinePoint( m_lineID, pNew );
	m_pMapPoint = pNew;
}

//完成画线
void CMapToolLine::End()
{
	if( m_pMapLine == NULL )
		return;
	vector<MapPoint*>* arr = m_pMapLine->GetMapPoint();
	MapPoint* pPoint = NULL;
	char cTemp[32];
	bool bFirst = true;
	string strData;
	for (vector<MapPoint*>::iterator it = arr->begin(); it != arr->end(); ++it)
    {
		pPoint = *it;
		if( bFirst ){
			sprintf(cTemp,"%f,%f",pPoint->x,pPoint->y);
			strData = cTemp;
			bFirst = false;
		}
		else{
			sprintf(cTemp,";%f,%f",pPoint->x,pPoint->y);
			strData += cTemp;
		}
    }
	m_pMapLine->SetLineName( "线1" );
	m_pMapDisp->Invalidate();
	//回调函数
	if( g_fun_msg != NULL )
	{
		g_fun_msg( MAP_TOOL_MESSAGE, 2, 1, strData.c_str() );
	}
	else
	{
		g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 2, 1, strData.c_str() );
	}
	
}
//清除线信息
void CMapToolLine::Clean()
{
	m_iFlag = 0;
	if( m_pMapLayer )
	{
		if( m_pMapLine )
		{
			m_pMapLayer->DeleteMapLine( m_lineID );
			m_pMapLine = NULL;
		}
	}
	m_pMapDisp->Invalidate();
}
//保存
void CMapToolLine::Save()
{
	/*
	//创建线对象
	bool CreatMapLine(short lineID );
	bool AddMapLinePoint( short lineID, MapPoint* pPoint );
	bool SetMapLineName( short lineID, string name );
	bool SetMapLineColor( short lineID, long lineColor );
	bool SetMapLineWidth( short lineID, long lineWidth );
	*/
	m_pMapDisp->m_MapLayerMan.m_backLayer.CreatMapLine( m_lineID );
	//--
	vector<MapPoint*>* arr = m_pMapLine->GetMapPoint();
	m_pMapDisp->m_MapLayerMan.m_backLayer.SetMapLineColor( m_lineID,255 );
	m_pMapDisp->m_MapLayerMan.m_backLayer.SetMapLineWidth( m_lineID, 3 );
	MapPoint* pPoint = NULL;
	char cTemp[32];
	bool bFirst = true;
	string strData;
	for (vector<MapPoint*>::iterator it = arr->begin(); it != arr->end(); ++it)
    {
		pPoint = *it;
		MapPoint* pPointNew = new  MapPoint();
		pPointNew->x = pPoint->x;
		pPointNew->y = pPoint->y;
		m_pMapDisp->m_MapLayerMan.m_backLayer.AddMapLinePoint( m_lineID, pPointNew );
    }
	m_pMapDisp->m_MapLayerMan.m_backLayer.SaveAllMapLine();
}
