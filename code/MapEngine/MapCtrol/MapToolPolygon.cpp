// MapToolPolygon.cpp: implementation of the CMapToolPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gmapx.h"
#include "MapToolPolygon.h"
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
CMapToolPolygon::CMapToolPolygon()
{
	m_pMapLayer = NULL;
	m_pMapDisp = NULL;
	m_pMapPolygon = NULL;
	m_iFlag = 0;
	m_PolygonlD = 0x0990;
}

CMapToolPolygon::~CMapToolPolygon()
{
	m_pMapLayer = NULL;
	m_pMapDisp = NULL;
	m_iFlag = 0;
	m_PolygonlD = 0x0850;
//	m_lTextID = 0x08FF0850;
}
//初始化资源文件根目录
bool CMapToolPolygon::Init( CMapDisp* pMapDisp,CMapLayer* pMapLayer, CVOSImage* pImageDel )
{
	m_pMapDisp = pMapDisp;
	m_pMapLayer = pMapLayer;
//	m_pImageDel = pImageDel;
	return 1;
}
//激活画线工具
void CMapToolPolygon::SetActive( bool bActive )
{
	if( bActive )
	{
		Create();
	}
	else
	{
		m_iFlag = 0;
		Clean();
	}
}
//鼠标消息
bool CMapToolPolygon::OnLButtonDown( VOSPoint point )
{
	if( !m_iFlag )
		return false;
	if( 1 == m_iFlag || 2 == m_iFlag )
	{
		AddPoint( point );
	}
	if( m_iFlag == 3 )
	{
		if( this->m_rectDel.IsPointIn( point ) )
		{
			m_iFlag = 0;
			Clean();
			m_pMapDisp->Invalidate();
			//回调函数
			if( g_fun_msg != NULL )
			{
				g_fun_msg( MAP_TOOL_MESSAGE, 3, 0, "" );
			}
			else
			{
				g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 3, 0, "" );
			}
		}	
	}
	return true;
}
bool CMapToolPolygon::OnLButtonUp( VOSPoint point)
{
	if( !m_iFlag )
		return false;
	return true;
}
bool CMapToolPolygon::OnMouseMove( VOSPoint point)
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
bool CMapToolPolygon::OnLButtonDblClk( VOSPoint point )
{
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
bool CMapToolPolygon::OnMouseWheel( short zDelta, VOSPoint point)
{
	if( !m_iFlag )
		return false;
	return true;
}
void CMapToolPolygon::OnDraw( HDC hdc )
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
		
		MapPoint* pNew = new MapPoint();
		m_pMapDisp->ScreenToMap(m_ptMouse,*pNew);
		vector<MapPoint*>* arr = m_pMapPolygon->GetMapPoint();
		double dArea = CMapBase::GetArea( arr,pNew )/1000000.0;
		delete pNew;
		char chTemp[30]={0};
		sprintf( chTemp, "%f平方公里,双击保存",dArea);
		string str = chTemp;
		TextOut( hdc, m_ptMouse.x+6,m_ptMouse.y+6, chTemp, strlen( chTemp ) );
	}
	if( m_iFlag == 3 )
	{
		VOSPoint ptn;
		m_pMapDisp->MapToScreen(m_mptLast,ptn);
		//--绘制删除按钮
		m_rectDel.left = ptn.x + 3;
		m_rectDel.bottom = ptn.y + 3;

		vector<MapPoint*>* arr = m_pMapPolygon->GetMapPoint();
		double dArea = CMapBase::GetArea( arr )/1000000;
		char chTemp[30]={0};
		sprintf( chTemp, "%f平方公里",dArea);
		string str = chTemp;
		TextOut( hdc, ptn.x+3,ptn.y+3, chTemp, strlen( chTemp ) );

//		m_rectDel.top = m_rectDel.bottom - m_pImageDel->GetSize().cy;
//		m_rectDel.right = m_rectDel.left + m_pImageDel->GetSize().cx;
//		m_pImageDel->Draw( hdc, m_rectDel );
		
	}
}
//创建画线
void CMapToolPolygon::Create()
{
	Clean();
	m_iFlag = 1;
	m_rectDel.left = 0;
	m_rectDel.right = 0;
	m_rectDel.top = 0;
	m_rectDel.bottom = 0;
	m_PolygonlD++;
	if( m_pMapLayer->CreatMapPolygon( m_PolygonlD ) )
	{
		m_pMapPolygon = m_pMapLayer->GetMapPolygon( m_PolygonlD );
		m_pMapPolygon->SetColor(RGB(241,122,54));
		m_pMapPolygon->SetWidth( 3 );
	}
}
//添加画线点
void CMapToolPolygon::AddPoint( VOSPoint point )
{
	m_iFlag = 2;
	MapPoint* pNew = new MapPoint();
	m_pMapDisp->ScreenToMap(point,*pNew);
	m_pMapLayer->AddMapPolygonPoint( m_PolygonlD, pNew );
	m_mptLast.x = pNew->x;
	m_mptLast.y = pNew->y;
}

//检测点是否在多变型范围内
bool CMapToolPolygon::IsInMapToolsPolygon(double dLon, double dLan )
{
	if( m_pMapLayer )
	{
		MapPoint mpt;
		mpt.x = dLon;
		mpt.y = dLan;
		vector<MapPoint*>* arr = m_pMapPolygon->GetMapPoint();
		if( arr->size() < 3 || arr->size() > 50 )
			return false;
		return CMapBase::InPolygon( arr, mpt );
	}
	return false;
}
//完成画线
void CMapToolPolygon::End()
{	
	if( m_pMapPolygon == NULL )
		return;
	vector<MapPoint*>* arr = m_pMapPolygon->GetMapPoint();
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
//	m_pMapPolygon->SetName( "线111" );
	m_pMapDisp->Invalidate();
	//回调函数
	if( g_fun_msg != NULL )
	{
		g_fun_msg( MAP_TOOL_MESSAGE, 3, 1, strData.c_str() );
	}
	else
	{
		g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, 3, 1, strData.c_str() );
	}
}
//清除线信息
void CMapToolPolygon::Clean()
{
	m_iFlag = 0;
	if( m_pMapLayer )
	{
		if( m_pMapPolygon )
		{
			m_pMapLayer->DeleteMapPolygon( m_PolygonlD );
			m_pMapPolygon = NULL;
		}
	}
}
//保存
void CMapToolPolygon::Save()
{
	/*
	//创建线对象
	bool CreatMapLine(short lineID );
	bool AddMapLinePoint( short lineID, MapPoint* pPoint );
	bool SetMapLineName( short lineID, string name );
	bool SetMapLineColor( short lineID, long lineColor );
	bool SetMapLineWidth( short lineID, long lineWidth );
	*/
	m_pMapDisp->m_MapLayerMan.m_backLayer.CreatMapPolygon( m_PolygonlD );
	//--
	vector<MapPoint*>* arr = m_pMapPolygon->GetMapPoint();
	m_pMapDisp->m_MapLayerMan.m_backLayer.SetMapPolygonColor( m_PolygonlD,RGB(241,122,54) );
	
	double dArea = CMapBase::GetArea( arr )/1000000;
	char chTemp[30]={0};
	sprintf( chTemp, "%f平方公里",dArea);
	m_pMapDisp->m_MapLayerMan.m_backLayer.SetMapPolygonName( m_PolygonlD, chTemp );

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
		m_pMapDisp->m_MapLayerMan.m_backLayer.AddMapPolygonPoint( m_PolygonlD, pPointNew );
    }
	m_pMapDisp->m_MapLayerMan.m_backLayer.SaveAllMapPolygon();
}