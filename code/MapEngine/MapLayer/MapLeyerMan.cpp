// MapLeyerMan.cpp: implementation of the CMapLeyerMan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapLeyerMan.h"
#include "../MapDisp/MapDisp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapLeyerMan::CMapLeyerMan()
{
	m_lmaxID = 0;
	m_pLastPoi = NULL;
}

CMapLeyerMan::~CMapLeyerMan()
{
	ClearAllMapLayer();
	this->m_MapPoiRes.UnInit();
	m_pLastPoi = NULL;
}
//初始化
bool CMapLeyerMan::Init( CMapDisp* pMapDisp, string strRootPath )
{
	m_pMapDisp = pMapDisp;
	string strResPath = strRootPath;
	strResPath += _T("res\\");
	if( !m_MapPoiRes.Init( (char*)strResPath.c_str() ) )
		return false;
	m_hCursor = LoadCursor(NULL,MAKEINTRESOURCE(32649));
	this->m_MapPoiInfo.Init( pMapDisp,strResPath.c_str() );

	string strMapPath = strRootPath;
	strMapPath += _T("map\\");
	m_backLayer.Load( strMapPath,&m_MapPoiRes );

	string strbk = strRootPath;
	strbk += "bk.bmp";
	m_ImageBk.LoadImage( strbk );
	return true;
}
//添加图层
long CMapLeyerMan::AddMapLayer( CMapLayer* pMapLayer )
{
	m_lmaxID++;
	pMapLayer->SetLayerID( m_lmaxID );
	m_arrMapLayers.push_back( pMapLayer );//m_arrMapLayers.Add( pMapLayer );
	return m_lmaxID;
}
//删除图层
bool CMapLeyerMan::DeleteMapLayer( int nID )
{
	CMapLayer* pMapLayer = NULL;
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
		pMapLayer = *it;
        if( pMapLayer->GetLayerID() == nID )
		{
			delete pMapLayer;
			m_arrMapLayers.erase( it );
			return TRUE;
		}
    }
	return FALSE;
}
//设置图层是否显示
bool CMapLeyerMan::SetMapLayerVisible( int nID, bool bVisible )
{
	CMapLayer* pMapLayer = NULL;
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
		pMapLayer = *it;
        if( pMapLayer->GetLayerID() == nID )
		{
			pMapLayer->SetVisible( bVisible );
			return TRUE;
		}
    }
	return FALSE;
}
//删除图层
void CMapLeyerMan::DeleteMapLayer( CMapLayer* pMapLayer )
{
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
        if( pMapLayer == *it )
		{
			delete pMapLayer;
			m_arrMapLayers.erase( it );
		}
    }
}
long CMapLeyerMan::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName )
{
	short sResID = m_MapPoiRes.GetResID( strFileName );
	return AddMapLayerPoint( nLayerID, lMapX, lMapY, strName,sResID );
}
//添加涂层点
int nid = 0;
long CMapLeyerMan::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID )
{
	CMapLayer* pMapLayer = NULL;
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
		pMapLayer = *it;
        if( pMapLayer->GetLayerID() == nLayerID )
		{
			pMapLayer->CreatMapPoint( nid++,lMapX,lMapY,strName,strName,icoID );
			/*CMapPoi* pNewPoi = new CMapPoi();
			pNewPoi->SetMapPoint( lMapX, lMapY );
			pNewPoi->SetPoiName( strName );
			pNewPoi->SetResID( icoID );
// 			pNewPoi->m_Point.x = lMapX;6
// 			pNewPoi->m_Point.y = lMapY;
// 			pNewPoi->m_strPoiName = strName;
// 			pNewPoi->m_uid = icoID;
			pMapLayer->AddMapPoi( pNewPoi );*/
			return nid;
		}
    }
	return FALSE;
}
//删除全部图层
void CMapLeyerMan::ClearAllMapLayer()
{
	Realse();
}
void CMapLeyerMan::Realse()
{
	m_backLayer.RemoveAll();
	m_userLayer.RemoveAll();
	m_ToolsLayer.RemoveAll();
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
        CMapLayer* layer = *it;
		if ( layer ) {
			layer->RemoveAll();
			delete layer;
		}	
    }
	m_arrMapLayers.clear();
}
//绘制
void CMapLeyerMan::OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf )
{
	m_ImageBk.Draw( hdc,0,0);
	m_backLayer.OnDraw(hdc,m_rbuf,m_pMapDisp, &m_MapPoiRes);
	for (vector<CMapLayer*>::iterator it = m_arrMapLayers.begin(); it != m_arrMapLayers.end(); ++it)
    {
        CMapLayer* layer = *it;
		if ( layer->GetVisible() )
		{
			layer->OnDraw( hdc,m_rbuf,m_pMapDisp, &m_MapPoiRes );
		}
    }
	this->m_userLayer.OnDraw( hdc,m_rbuf,m_pMapDisp, &m_MapPoiRes );
	m_ToolsLayer.OnDraw( hdc,m_rbuf,m_pMapDisp, &m_MapPoiRes );
	m_MapPoiInfo.Draw( hdc, m_pMapDisp );

//	this->m_MapAround.Draw(hdc,m_pMapDisp, &m_MapPoiRes );
//	this->m_MapText.Draw(hdc,m_pMapDisp);
// 	for( int i=0;i<m_arrMapLayers.GetSize();i++ )
// 	{
// 		m_arrMapLayers.GetAt(i)->OnDraw( hdc,m_pMapDisp, &m_MapPoiRes );
// 	}
}
//点击处理,返回点中的POI对象ID，不是返回-1
//点击处理，检测是否击中图层，如果击中，检测是否是，是返回poiid，不是，返回poid为-1
/*bool CMapLeyerMan::OnClick( VOSPoint point, CMapPoi*& poi )
{
	if ( m_MapPoiInfo.IsPointIn( point ) ) {
		poi = NULL;
		return true;
	}
	//用户图层
	if ( this->m_userLayer.IsPointIn(point, poi) ) {
		if( poi->m_strText.length() > 0 )
		{
			m_MapPoiInfo.SetPoiInfo( poi,true);
			//m_MapPoiInfo.SetPoiInfo( poi->m_sPOIID, poi->m_strText,poi->m_Point,true);
			//::SetTimer( m_pMapDisp->m_hwnd, _MAP_TIMER_PROC2, _MAP_TIMER2, NULL );
			//m_pMapDisp->PostMessageEx( WM_MAP_POIINFO_MESSAGE, 0,0 );
			return true;
		}
		return true;
	}
	//背景图层
	if ( this->m_backLayer.IsPointIn(point, poi) ) {
		if( poi->m_strText.length() > 0 )
		{
			m_MapPoiInfo.SetPoiInfo( poi,true);
			//m_MapPoiInfo.SetPoiInfo( poi->m_sPOIID, poi->m_strText,poi->m_Point,true);
			//::SetTimer( m_pMapDisp->m_hwnd, _MAP_TIMER_PROC2, _MAP_TIMER2, NULL );
			return true;
		}
		return true;
	}
	return false;
}*/
bool CMapLeyerMan::IsPointIn( VOSPoint point, CMapPoi*& poi )
{
	if ( m_MapPoiInfo.IsPointIn( point ) )
	{
		poi = NULL;
		return true;
	}
	if ( this->m_userLayer.IsPointIn(point, poi) ) 
	{
		return true;
	}
	if ( this->m_ToolsLayer.IsPointIn(point, poi) ) 
	{
		return true;
	}
	return false;
}
//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
long CMapLeyerMan::CreateRes( string strpath )
{
	return this->m_MapPoiRes.CreateFileRes( strpath );
}
bool CMapLeyerMan::CreatMapPoint( long id )
{
	return this->m_userLayer.CreatMapPoint( id );
}
bool CMapLeyerMan::CreatMapPoint( long pointid, double x, double y, string strName, string strText, long icoID )
{
	//m_backLayer.SaveMapPoint( pointid,x,y,strName,strText,icoID );
	return this->m_userLayer.CreatMapPoint( pointid,x,y,strName,strText,icoID );
}
bool CMapLeyerMan::SetMapPointAngle( long pointID, long lAngle )
{
	CMapPoi* pNewPoi = this->m_userLayer.GetMapPoi( pointID );
	if ( pNewPoi != NULL ) {
		pNewPoi->SetMapAngle( lAngle );
	}
	return false;
}
bool CMapLeyerMan::SetMapPoint(long pointID, double x, double y)
{
	CMapPoi* pNewPoi = this->m_userLayer.GetMapPoi( pointID );
	if ( pNewPoi != NULL ) {
		pNewPoi->SetMapPoint(x,y);
		/*m_MapPoiInfo.SetPoiInfo( pNewPoi );
		if( m_MapPoiInfo.m_poiid == pNewPoi->m_sPOIID )
		{
			m_MapPoiInfo.SetPoiInfo( pNewPoi->m_sPOIID,pNewPoi->m_strText,pNewPoi->m_Point);
		}*/
		return true;
	}
	return false;
}
bool CMapLeyerMan::SetMapPointName(long pointID, string name)
{
	CMapPoi* pNewPoi = this->m_userLayer.GetMapPoi( pointID );
	if ( pNewPoi != NULL ) {
		pNewPoi->SetPoiName(name);
		return true;
	}
	return false;
}
bool CMapLeyerMan::SetMapPointText(long pointID, string text)
{
	CMapPoi* pNewPoi = this->m_userLayer.GetMapPoi( pointID );
	if ( pNewPoi != NULL ) {
		pNewPoi->SetPoiText(text);
/*		if( m_MapPoiInfo.m_poiid == pNewPoi->m_sPOIID )
		{
			m_MapPoiInfo.SetPoiInfo( pNewPoi->m_sPOIID,pNewPoi->m_strText,pNewPoi->m_Point);
		}
*/		return true;
	}
	return false;
}
bool CMapLeyerMan::SetMapPointICO(long pointID, long icoid )
{
	CMapPoi* pNewPoi = this->m_userLayer.GetMapPoi( pointID );
	if ( pNewPoi != NULL ) {
		pNewPoi->SetResID( icoid );
		return true;
	}
	return false;
}
bool CMapLeyerMan::DeleteMapPoint(long pointID)
{
	return m_userLayer.DeleteMapPoint( pointID );
	return false;
}
//删除全部点信息
void CMapLeyerMan::DeleteAllMapPoint()
{
	m_MapPoiInfo.Close();
	m_userLayer.DeleteAllMapPoint();
}
bool CMapLeyerMan::CreatMapLine( long lineID )
{
	return m_userLayer.CreatMapLine( lineID );
}
bool CMapLeyerMan::AddMapLinePoint( long lineID, double x, double y)
{
	MapPoint* pNew = new MapPoint(); 
	pNew->x =x;
	pNew->y = y;
	return m_userLayer.AddMapLinePoint( lineID, pNew );
}
bool CMapLeyerMan::AddMapLinePoint( long lineID, MapPoint Point )
{
	MapPoint* pNew = new MapPoint(); 
	pNew->x = Point.x;
	pNew->y = Point.y;
	return m_userLayer.AddMapLinePoint( lineID, pNew );
}
bool CMapLeyerMan::SetMapLineName( long lineID, string name )
{
	return m_userLayer.SetMapLineName( lineID, name );
}
bool CMapLeyerMan::SetMapLineColor( long lineID, long lineColor )
{
	return m_userLayer.SetMapLineColor( lineID, lineColor );
}
bool CMapLeyerMan::SetMapLineWidth( long lineID, long lineWidth )
{
	return m_userLayer.SetMapLineWidth( lineID, lineWidth );
}
bool CMapLeyerMan::SetMapLineVisible( long lineID, long lVisible )
{
	return m_userLayer.SetMapLineVisible( lineID, lVisible );
}
bool CMapLeyerMan::DeleteLine(long lineID)
{
	return m_userLayer.DeleteMapLine( lineID );
	return false;
}
//创建多边形对象
bool CMapLeyerMan::CreatMapPolygon(long polygonID )
{
	return m_userLayer.CreatMapPolygon( polygonID );
}
//添加点
bool CMapLeyerMan::AddMapPolygonPoint( long polygonID, double x, double y)
{
	MapPoint* pNew = new MapPoint(); 
	pNew->x = x;
	pNew->y = y;
	return m_userLayer.AddMapPolygonPoint( polygonID, pNew );
}
//删除多边形对象
bool CMapLeyerMan::DeleteMapPolygon(long polygonID)
{
	return m_userLayer.DeleteMapPolygon( polygonID );
	return false;
}
//绘制半圆
void CMapLeyerMan::CreateMapAround( long uid, double x, double y, long radius, long alpha )
{
	m_userLayer.CreateMapAround( uid,x,y,radius,alpha);
}
void CMapLeyerMan::DeleteMapAround( long uid )
{
	m_userLayer.DeleteMapAround(uid);
}
//绘制文字
void CMapLeyerMan::CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color)
{
	m_userLayer.CreateMapText( tid,x,y,text,size,color);
}
void CMapLeyerMan::DeleteMapText(long tid)
{
	m_userLayer.DeleteMapText(tid);
}
//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
bool CMapLeyerMan::SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	return m_userLayer.SetMapTextFont( tid,size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
}
//鼠标消息
bool CMapLeyerMan::OnLButtonDown( VOSPoint point )
{
	int type;
	int id;
	//POI弹出信息
	if( this->m_MapPoiInfo.OnLButtonDown( point ) )
		return false;
	//地图信息点
	CMapPoi* poi=NULL;
	//用户图层
	if ( this->m_userLayer.IsPointIn(point, poi) ) {
		return false;
	}
	//背景图层
	if ( this->m_backLayer.IsPointIn(point, poi) ) {
		return false;
	}
	//删除按钮
	if ( this->m_userLayer.IsPointInDel( point, type, id ) )
	{
		return false;
	}
	return false;
}
bool CMapLeyerMan::OnLButtonUp( VOSPoint point)
{
	//地图POI弹出信息
	if( this->m_MapPoiInfo.OnLButtonUp( point ) )
		return false;
	//地图信息点
	CMapPoi* poi=NULL;
	//用户图层
	if ( this->m_userLayer.IsPointIn(point, poi) ) {
		if( poi->m_strText.length() > 0 )
		{
			m_MapPoiInfo.SetPoiInfo( poi );
			return false;
		}
		return false;
	}
	//背景图层
	if ( this->m_backLayer.IsPointIn(point, poi) ) {
		if( poi->m_strText.length() > 0 )
		{
			m_MapPoiInfo.SetPoiInfo( poi );
			return false;
		}
		return false;
	}
	//删除按钮
	int type;
	int id;
	if ( this->m_userLayer.IsPointInDel( point, type, id ) )
	{
		if( type == 6 )
		{
			m_userLayer.DeleteMapPoint( id );
		}
		//回调函数
		if( g_fun_msg != NULL )
		{
			char temp[20];
			sprintf( temp,"%d", id );
			g_fun_msg( MAP_TOOL_MESSAGE, type, 0, temp );
		}
		else
		{
			char temp[20];
			sprintf( temp,"%d", id );
			g_pGmapxCtrl->OnEventMessage( MAP_TOOL_MESSAGE, type, 0, temp );
		}
		return false;
	}
	return false;
}
bool CMapLeyerMan::OnMouseMove( VOSPoint point)
{
	CMapPoi* poi=NULL;
	if( m_userLayer.IsPointIn( point,poi ) )
	{
		if( m_pLastPoi )
		{
			m_pLastPoi->SetPoiNameVisible( false );
			m_pLastPoi = NULL;
		}
		poi->SetPoiNameVisible( true );
		m_pLastPoi = poi;
		SetCursor(m_hCursor);
		m_pMapDisp->Invalidate();
		return false;
	}
	else
	{
		if( m_pLastPoi )
		{
			m_pLastPoi->SetPoiNameVisible( false );
			m_pLastPoi = NULL;
			m_pMapDisp->Invalidate();
		}
	}
	return false;
}
bool CMapLeyerMan::OnMouseWheel( short zDelta, VOSPoint pt)
{
	return false;
}
bool CMapLeyerMan::OnLButtonDblClk( VOSPoint point )
{
	return false;
}
//添加地图信息点
bool CMapLeyerMan::SaveLocMapPoint( double x, double y, string strName, string strText, long icoID )
{
	return m_backLayer.SaveMapPoint( x, y ,strName, strText, icoID );
}
//添加文本信息
bool CMapLeyerMan::SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor )
{
	return m_backLayer.SaveLocMapText( x,y,strText,fontsize,bgrcolor);
}
//添加地图线,
bool CMapLeyerMan::SaveLocMapLine( string strMapPoints, string strName, long width, long bgrcolor  )
{
	return m_backLayer.SaveMapLine( strMapPoints, strName, width, bgrcolor );
}
//清除地图保存信息
bool CMapLeyerMan::ClearLocMapData()
{
	return m_backLayer.ClearMapSaveData();
	return true;
}
//删除一个点
bool CMapLeyerMan::DeleteLocMapPoint(long pointID)
{
	m_backLayer.DeleteMapPoint( pointID );
	m_backLayer.SaveAllMapPoint();
	return true;
}
//删除一个线
bool CMapLeyerMan::DeleteLocMapLine(long lineID)
{
	m_backLayer.DeleteMapLine( lineID );
	m_backLayer.SaveAllMapLine();
	return true;
}
//得到当前位置的信息ID,0为无数据，1为点信息，2为线信息
int CMapLeyerMan::GetLocID( long& lID, VOSPoint point )
{
	return m_backLayer.GetLocID( lID, point );
}
//设置地图可编辑
long CMapLeyerMan::OpenMapEdit(long type, long id, bool bedit)
{
	return m_userLayer.OpenMapEdit( type, id, bedit );
}
//设置多边形名字
long CMapLeyerMan::SetMapPolygonName(long pid, const char* name )
{
	return m_userLayer.SetMapPolygonName( pid, name );
}
//设置多边形颜色
long CMapLeyerMan::SetMapPolygonColor(long pid, long colorbgr)
{
	return m_userLayer.SetMapPolygonColor( pid, colorbgr );
}
//设置圆名字
void CMapLeyerMan::SetMapAroundName(long rid, const char* name )
{
	m_userLayer.SetMapAroundName( rid, name );
}
long CMapLeyerMan::SetMapAroundColor(long rid, long colorbgr)
{
	return m_userLayer.SetMapAroundColor( rid, colorbgr );
}