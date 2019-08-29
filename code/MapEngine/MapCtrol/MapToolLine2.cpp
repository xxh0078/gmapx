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
	m_pMapDisp = NULL;
	m_iState = 0;
	m_lineID = 0x0850;
	m_lTextID = 0x08FF0850;
}

CMapToolLine::~CMapToolLine()
{
	m_pMapDisp = NULL;
}
//初始化资源文件根目录
bool CMapToolLine::Init( CMapDisp* pMapDisp )
{
	m_pMapDisp = pMapDisp;
	return 1;
}
//鼠标消息
bool CMapToolLine::OnLButtonDown( VOSPoint point )
{
	if( m_iState == 1 )
	{
		AddPoint( point );
	}
	else if( m_iState == 2) 
	{
		m_iState = 1;
		AddPoint( point );
	}
	return true;
}
bool CMapToolLine::OnLButtonUp( VOSPoint point)
{
	return false;
}
bool CMapToolLine::OnMouseMove( VOSPoint point)
{
	return false;
}
bool CMapToolLine::OnLButtonDblClk( VOSPoint point )
{
	return false;
}
bool CMapToolLine::OnMouseWheel( short zDelta, VOSPoint point)
{
	return false;
}
void CMapToolLine::OnDraw( HDC hdc )
{

}
//0为无效，1为等待设置起点，2为等待设置终点，3为设置终点结束
int  CMapToolLine::GetState()
{
	return this->m_iState;
}
//创建画线
void CMapToolLine::Create( CMapLayer* pMapLayer )
{
	Clean();
	m_pMapLayer = pMapLayer;
	m_iState = 1;
	m_iCount = 0;
	m_dLength = 0;
	m_pntLast.x = 0;
	m_pntLast.y = 0;
	//m_pMapLayer->DeleteMapLine( m_lineID );
	if( m_pMapLayer->CreatMapLine( m_lineID ) )
	{
		m_pMapLine = m_pMapLayer->GetMapLine( m_lineID );
		m_pMapLine->SetColor(RGB(241,122,54));
		m_pMapLine->SetWidth( 3 );
	}
}
//添加画线点
void CMapToolLine::AddPoint( VOSPoint point )
{
	if( m_pntLast.x == point.x && point.y == m_pntLast.y )
		return ;
	m_pntLast.x = point.x;
	m_pntLast.y = point.y;
	MapPoint* pNew = new MapPoint();
	m_pMapDisp->ScreenToMap(point,*pNew);
	m_pMapLayer->AddMapLinePoint( m_lineID, pNew );
	if( m_iCount > 0 )
	{
		m_dLength += CMapBase::GetLength( pNew->x,pNew->y,m_pMapPoint->x,m_pMapPoint->y);
		char cTemp[30]={0};
		if( m_dLength < 1000 )
		{
			sprintf(cTemp, "%dm",m_dLength);
		}
		else
		{
			double dLen = (double)m_dLength/1000.0;
			sprintf(cTemp, "%.02fkm",dLen );
		}
		//xxh m_pMapLayer->CreateMapText( m_lTextID+m_iCount,pNew->x,pNew->y,cTemp,16,RGB(0,0,255) );
		//xxh m_pMapLayer->SetMapTextFont( m_lTextID+m_iCount,18,0,0,700,1,0,0,0,"微软雅黑" );
	}
	m_pMapPoint = pNew;
	m_iCount++;
}

void CMapToolLine::GetPointsText( string& strlon,string&  strlan )
{
	strlon = m_strlon;
	strlan = m_strlan;
}
//完成画线
void CMapToolLine::End()
{
	//
//	CDialog dlgAbout(IDD_ABOUTBOX_GMAPX);
//	dlgAbout.DoModal();
	m_iState = 2;	
	if( m_pMapLine == NULL )
		return;
	vector<MapPoint*>* arr = m_pMapLine->GetMapPoint();
	MapPoint* pPoint = NULL;
	char cTemp[20];
	bool bFirst = true;
	for (vector<MapPoint*>::iterator it = arr->begin(); it != arr->end(); ++it)
    {
		pPoint = *it;
		if( bFirst ){
			sprintf(cTemp,"%f",pPoint->x);
			m_strlon = cTemp;
			sprintf(cTemp,"%f",pPoint->y);
			m_strlan = cTemp;
			bFirst = false;
		}
		else{
			sprintf(cTemp,",%f",pPoint->x);
			m_strlon += cTemp;
			sprintf(cTemp,",%f",pPoint->y);
			m_strlan += cTemp;
		}
    }
	m_pMapDisp->PostMessageEx( WM_MAP_TOOLS_MESSAGE, 1,m_iCount );
	m_pMapDisp->Invalidate();
}
//清除线信息
void CMapToolLine::Clean()
{
	if( m_pMapLayer )
	{
		vector<MapPoint*>* arr = m_pMapLine->GetMapPoint();
		MapPoint* pPoint = NULL;
		char cTemp[20];
		bool bFirst = true;
		for (vector<MapPoint*>::iterator it = arr->begin(); it != arr->end(); ++it)
		{
			pPoint = *it;
			if( bFirst ){
				sprintf(cTemp,"%f",pPoint->x);
				m_strlon = cTemp;
				sprintf(cTemp,"%f",pPoint->y);
				m_strlan = cTemp;
				bFirst = false;
			}
			else{
				sprintf(cTemp,",%f",pPoint->x);
				m_strlon += cTemp;
				sprintf(cTemp,",%f",pPoint->y);
				m_strlan += cTemp;
			}
		}
		m_pMapLayer->DeleteMapLine( m_lineID );
		for( int i= 0;i< m_iCount;i++)
		{
			m_pMapLayer->DeleteMapText( m_lTextID+i);
		}
		m_iCount = 0;
		m_pMapLayer = NULL;
	}
}
