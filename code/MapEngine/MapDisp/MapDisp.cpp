#include "StdAfx.h"
#include "MapDisp.h"

#ifdef _GMAPX_CTROL_
#include "../../gmapx/GmapxCtl.h"
extern CGmapxCtrl* g_pGmapxCtrl;//CGMapxCtrl* g_pGmapxCtrl;
#endif
//+		lonLat20	{lX=134217728 lY=134217729 }	_mPoint
//+		lonLat20	{lX=148877286 lY=148888989 }	_mPoint
#ifdef jincheng
long llon1 = 134217728;
long llon2 = 148877286;
long llan1 = 134217729;
long llan2 = 148888989;
#endif
CMapDisp::CMapDisp(void)
{
	m_iLevel = 4;
	m_MapCenter20.lX = 0;
	m_MapCenter20.lY = 0;
	m_bitmap = NULL;
	m_memDC = NULL;
	m_bitmapStretch = NULL;
	m_memDCStretch = NULL;
	m_brushBg = NULL;
	m_penBg = NULL;
	m_iSpeedX =0;
	m_iSpeedY = 0;
	m_bFlagMoveMap = false;
	m_bFlagMoveLayerPoint = false;
	m_bMapAutoMove = false;

	m_pMapDispLayerMark = NULL;
	m_maxLevel = 20;		//最大比例尺
	m_minLevel = 1;		//最小比例尺
}	

CMapDisp::~CMapDisp(void)
{
	realse();
}
void CMapDisp::realse()
{
	//退出前保存用户信息
//	m_UserInfo.SetMapCenter( m_MapCenter20.lX,m_MapCenter20.lY,this->m_iLevel );
//	m_UserInfo.SaveUserInfo();
	//释放
	m_hwnd = NULL;
//	m_MapDataDown.realse();
	this->m_MapLayerMan.Realse();
	if ( m_bitmap != NULL )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	if ( m_bitmapStretch != NULL )
	{
		::DeleteObject( m_bitmapStretch );
		m_bitmapStretch = NULL;
	}
	if ( m_memDC != NULL )
	{
		::DeleteDC( m_memDC );
		m_memDC = NULL;
	}
	if ( m_memDCStretch != NULL )
	{
		::DeleteDC( m_memDCStretch );
		m_memDCStretch =NULL;
	}
	if ( m_penBg ) {
		DeleteObject( m_penBg );
		m_penBg = NULL;
	}
	if ( m_brushBg ) {
		DeleteObject( m_brushBg );
		m_penBg = NULL;
	}
	if( m_pMapDispLayerMark )
	{
		delete m_pMapDispLayerMark;
		m_pMapDispLayerMark = NULL;
	}
	
}
//设置地图类型 
void CMapDisp::SetMapType( string strRoot, en_MapType eMapType, string strMapName, string strMapURL )
{
	//CMapBase::SetMapType( eMapType, strRoot );
//	m_MapDispLayer.SetMapType( 
//	m_MapDataDown.ClearNoDownLoadList();
	m_enMapType = eMapType;
	SetMapBound();
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
		
	if( m_pMapDispLayerMark )
	{
		delete m_pMapDispLayerMark;
		m_pMapDispLayerMark = NULL;
	}
	if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		m_MapDispLayer.SetMapType( GMAP_GOOGLE_IMAGE, strRoot, strMapName, strMapURL );
		m_pMapDispLayerMark = new CMapDispLayer();
		m_pMapDispLayerMark->Create(this);
		m_pMapDispLayerMark->SetMapType( GMAP_GOOGLE_MARK,strRoot );
		m_pMapDispLayerMark->ReLoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
	else
		m_MapDispLayer.SetMapType( eMapType, strRoot, strMapName, strMapURL );

	m_MapDispLayer.ReLoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	Invalidate();
}
//设置本地地图路径
void CMapDisp::SetMapPath( string strMapPath )
{
//	m_MapDataDown.ClearNoDownLoadList();
	m_enMapType = GMAP_FILES;
	SetMapBound();
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	if( m_pMapDispLayerMark )
	{
		delete m_pMapDispLayerMark;
		m_pMapDispLayerMark = NULL;
	}
	m_MapDispLayer.SetMapPath( strMapPath );
//	m_MapDispLayer.setma
	m_MapDispLayer.ReLoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	Invalidate();
	
}
//设置附件图层路径
void CMapDisp::OpenAddMapLayerPath( string strMapFilesPath )
{
	if( m_pMapDispLayerMark )
	{
		delete m_pMapDispLayerMark;
		m_pMapDispLayerMark = NULL;
	}
	//if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		SetMapBound();
#ifdef _GMAPX_CTROL_
	//	g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
		MPoint gptMapCenter;
		CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
		m_pMapDispLayerMark = new CMapDispLayer();
		m_pMapDispLayerMark->Create(this);
		m_pMapDispLayerMark->SetMapPath( strMapFilesPath );
		m_pMapDispLayerMark->ReLoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
}
//关闭附加层
void CMapDisp::CloseAddMapLayer( )
{
	if( m_pMapDispLayerMark )
	{
		delete m_pMapDispLayerMark;
		m_pMapDispLayerMark = NULL;
	}
}
void CMapDisp::Init( HWND hwnd, HDC dcEngine, string strRootPath, en_MapType eMapType )
{
//	m_pWnd = pWnd;
	m_hwnd = hwnd;
	//设置地图类型与地图路径
	//CMapBase::SetMapType( eMapType, strRootPath );
	//m_MapDataDown.Init( this );
	m_hCursor = LoadCursor(NULL,MAKEINTRESOURCE(32649));

	MPoint gptMapCenter;
	gptMapCenter.lX = (414*8);
	gptMapCenter.lY = (194*8);
	m_iLevel = 4;
	CMapBase::GetMapPoint20( m_iLevel, gptMapCenter, m_MapCenter20 );
	
	//CDC* pDC = this->m_pWnd->GetDC();
	HDC dc = ::GetDC(hwnd);
	//创建DC
	if ( m_memDC )
	{
		//delete m_memDC;
		::DeleteObject( m_memDC );
		m_memDC = NULL;
	}
	m_memDC = ::CreateCompatibleDC( dc );
// 	m_memDC= new CDC; 
// 	m_memDC->CreateCompatibleDC(pDC);
// 	m_memDC->SetBkColor( RGB(100,100,100));
	 
	//创建缩放DC
	if ( m_memDCStretch )
	{
		::DeleteObject( m_memDCStretch );
		m_memDCStretch = NULL;
	}
	m_memDCStretch = ::CreateCompatibleDC( dc );
// 	m_penCursor.CreatePen( PS_SOLID,1,RGB(255,0,0));
	//CreatePen(PS_SOLID,1,RGB(rand()%256,rand()%256,rand()%256))
 	m_penBg = CreatePen( PS_SOLID,1, COLORRBG );
	m_brushBg = CreateSolidBrush( COLORRBG );
// 	m_brushBg.CreateSolidBrush( COLORRBG );
	//初始化所有数据块
	m_MapDispLayer.Create( this );
	//GMAP_GOOGLE_IMAGE
	m_MapDispLayer.SetMapType( GMAP_MAPABC, strRootPath  );
	m_MapLayerMan.Init( this, strRootPath);
	m_dcEngine = dcEngine;

//	this->m_bCanUsed = m_UserInfo.CanUseded();
	m_hbr = CreateSolidBrush(RGB(230,230,230));
}
//	void MapToScreen();
//	void ScreenToMap( CPoint pt, CGmPoint &gmpt);

//地图移动,参数偏移量
void CMapDisp::OnMoveMap( int iDx, int iDy )
{
	if( iDx == 0 && iDy == 0 )
		return;
	//HDC hdc = GetDC( m_hwnd );
	m_pntStart.x += iDx;
	m_pntStart.y += iDy;
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	//--------晋城
	MPoint mMapLT20,mMapRB20, mMapLT,mMapRB;
	mMapLT.lX = gptMapCenter.lX - this->m_rcWnd.width()/2;
	mMapLT.lY = gptMapCenter.lY - this->m_rcWnd.height()/2;

	mMapRB.lX = gptMapCenter.lX + this->m_rcWnd.width()/2;
	mMapRB.lY = gptMapCenter.lY + this->m_rcWnd.height()/2;
	CMapBase::GetMapPoint20( m_iLevel, mMapLT, mMapLT20 );
	CMapBase::GetMapPoint20( m_iLevel, mMapRB, mMapRB20 );
	//CMapBase::GetMapPoint( m_iLevel, mMapLT20, mMapLT );
	//CMapBase::GetMapPoint( m_iLevel, mMapRB20, mMapRB );
#ifdef jincheng
	if( iDx > 0 && mMapLT20.lX < llon1 )
		iDx = 0;
	if( iDx < 0 && mMapRB20.lX > llon2 )
		iDx = 0;
	if( iDy > 0 && mMapLT20.lY < llan1 )
		iDy = 0;
	if( iDy < 0 && mMapRB20.lY > llan2 )
		iDy = 0;
	--//晋城
#endif
	//if( m_MapCenter20.lX < 

	gptMapCenter.lX -= iDx;
	gptMapCenter.lY -= iDy;
	CMapBase::GetMapPoint20( m_iLevel, gptMapCenter, m_MapCenter20 );
	if ( !CheckAndSetMapCenter() )
	{
		m_iSpeedX = 0;
		m_iSpeedY = 0;
		return;
	}
	m_iSpeedX = iDx;
	m_iSpeedY = iDy;
//	TRACE( "point dx=%d,dy=%d \r\n", iDx, iDy );
	this->m_MapDispLayer.OnMoveMap(iDx,iDy);
	if( m_pMapDispLayerMark )
	{
		m_pMapDispLayerMark->OnMoveMap( iDx,iDy );
	}
	//CPen* pen = m_memDC->SelectObject( &m_penBg );
	//m_memDC->Rectangle(m_rcWnd);
	//m_memDC->SelectObject( pen );
	//this->m_pWnd->Invalidate(0);
	//Invalidate();
}
void CMapDisp::OnMapMove( int iDx, int iDy )
{
	//30 98 130 49 
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	gptMapCenter.lX -= iDx;
	gptMapCenter.lY -= iDy;
	CMapBase::GetMapPoint20( m_iLevel, gptMapCenter, m_MapCenter20 );
	SetMapBound();
#ifdef _GMAPX_CTROL_
	//	g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
//	MPoint gptMapCenter;
//	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	if( m_pMapDispLayerMark )
		m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	Invalidate();
}
//刷新屏幕
void CMapDisp::Invalidate()
{
//	TRACE( "Invalidate \r\n " );
// 	RECT rc;
// 	rc.left =200;
// 	rc.top =100;
// 	rc.right = m_rcWnd.width()+200;
// 	rc.bottom = m_rcWnd.height()+100;
	if( m_hwnd == NULL )
		return;
	::InvalidateRect( m_hwnd,NULL , false );
	//PostMessage( m_hwnd, WM_PAINT,0,0 );
	return;
}
//地图放大
void CMapDisp::MapZoomIn( VOSPoint pt )
{
//	HDC hdc = ::GetDC( m_hwnd );
	if ( m_iLevel+1 > m_maxLevel )
	{
		return;
	}
	//TRACE("MapZoomIn");
	m_ZoomParam.bOnZoom = true;
	::SetTimer( m_hwnd, _MAP_TIMER_PROC, _MAP_TIMER, NULL );
	if( m_ZoomParam.iZoomLevel <= this->m_minLevel )
	{ 
		DrawMap2StretchDC();
		m_ZoomParam.iZoomLevel = _ZOOM_MAX_COUNT;
	}
	else
	{
		return;
	}
	VOSPoint ptOffset,ptOffset20;
	ptOffset.x = pt.x - m_rcWnd.CenterPoint().x;
	ptOffset.y = pt.y - m_rcWnd.CenterPoint().y;
// 	ptOffset.x = ptOffset.x / 2;
// 	ptOffset.y = ptOffset.y / 2;
	CMapBase::OffsetMapPoint20( m_iLevel, ptOffset, ptOffset20 );
	m_MapCenter20.lX += ptOffset20.x/2;
	m_MapCenter20.lY += ptOffset20.y/2;
//	MPoint ptOffset20;
//	CMapBase::GetMapPoint20( m_iLevel, ptOffset, ptOffset20 );
//	m_gptMapCenter.lX = m_gptMapCenter.lX*2 + pt1.x;
//	m_gptMapCenter.lY = m_gptMapCenter.lY*2 + pt1.y;
	this->m_iLevel++;

//	MPoint gptMapCenter;
//	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
//	m_MapDataDown.ClearNoDownLoadList();
	//m_download.ClearDownLoadList();
	m_ZoomParam.point.x = pt.x;
	m_ZoomParam.point.y = pt.y;
	OnMapZoom();
//	LoadMapData();
}
void CMapDisp::MapZoomIn()
{
	MapZoomIn( m_rcWnd.CenterPoint() );
}
//地图缩小
void CMapDisp::MapZoomOut()
{
	MapZoomOut( m_rcWnd.CenterPoint() );
}
void CMapDisp::MapZoomOut( VOSPoint pt )
{
	if ( this->m_iLevel-1 < m_minLevel )
	{
		return;
	}
	m_ZoomParam.bOnZoom = true;
	::SetTimer( m_hwnd, _MAP_TIMER_PROC, _MAP_TIMER, NULL );
	if( m_ZoomParam.iZoomLevel <= m_minLevel )
	{ 
		DrawMap2StretchDC();
		m_ZoomParam.iZoomLevel = -_ZOOM_MAX_COUNT;
	}
	else
	{
		return;
	}
	VOSPoint ptOffset,ptOffset20 ;
	ptOffset.x = pt.x - m_rcWnd.CenterPoint().x;
	ptOffset.y = pt.y - m_rcWnd.CenterPoint().y;
// 	ptOffset.x = ptOffset.x*2;
// 	ptOffset.y = ptOffset.y*2  ;
	CMapBase::OffsetMapPoint20( m_iLevel, ptOffset, ptOffset20 );
	m_MapCenter20.lX -= ptOffset20.x;
	m_MapCenter20.lY -= ptOffset20.y;
	//m_MapCenter20
// 	m_gptMapCenter.lX = m_gptMapCenter.lX/2 - pt1.x/2 ;
// 	m_gptMapCenter.lY = m_gptMapCenter.lY/2 - pt1.y/2 ;
	this->m_iLevel--;
//	m_MapDataDown.ClearNoDownLoadList();
	m_ZoomParam.point.x = pt.x;
	m_ZoomParam.point.y = pt.y;
	OnMapZoom();
	//LoadMapData();
}
//绘制地图
void CMapDisp::DrawMap( HDC hdc )
{
	if( m_ZoomParam.bOnZoom )
	{
		::BitBlt( hdc,0,0,m_rcWnd.width(),m_rcWnd.height(),m_memDC,0,0,SRCCOPY);
	}
	else
	{
		RECT  src;
		src.left = 0;
		src.top = 0;
		src.right = m_rcWnd.width();
		src.bottom = m_rcWnd.height();
		::FillRect( m_memDC,&src,m_hbr);
//		TRACE( " CMapDisp::DrawMap \r\n" );
		MPoint gptMapCenter;
		CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
		m_MapDispLayer.OnDraw( m_memDC, m_iLevel, gptMapCenter, m_rcWnd );
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->OnDraw(  m_memDC,m_iLevel, gptMapCenter, m_rcWnd );
		
		m_MapLayerMan.OnDraw( m_memDC ,&m_rbuf );
// 		src.left = x111;
// 		src.top = 300;
// 		src.right = m_rcWnd.width();
// 		src.bottom = m_rcWnd.height();
/*		::FillRect( m_memDC,&src,hbr);*/
	/*	char ch[10]={0};
		sprintf(ch,"绘图count：%d,down=%d",this->m_iBlockCount,this->m_MapDataDown.m_iDownLoadCount);
		TextOut(m_memDC,120,0,ch,strlen(ch));*/
		::BitBlt( hdc,0,0,m_rcWnd.width()+100,m_rcWnd.height()+20,m_memDC,0,0,SRCCOPY);
// 		MoveToEx(hdc,m_rcWnd.Width()-10,m_rcWnd.Height()-10,NULL);
// 		LineTo(hdc,m_rcWnd.Width(),m_rcWnd.Height() );

		MapBount* mbu = this->GetMapBound();
	}
	/*if( !m_UserInfo.CanUseded() )
	{
		//HBRUSH hbr = CreateSolidBrush(RGB(230,230,230));
		SetBkMode(hdc,TRANSPARENT);
		::SetTextColor( hdc,   RGB( 255, 110, 194 )   ); 
		//SetTextColor( m_memDC,   RGB( 255, 0, 0 )   ); 
		RECT  src;
		src.left = 85;
		src.top = 50;
		src.right = m_rcWnd.width()-85;
		src.bottom = m_rcWnd.Height()-50;
		//HBRUSH brush = CreateSolidBrush( RGB(255,255,255) );
		//HBRUSH oldbrush = (HBRUSH)::SelectObject(hdc,brush );
		//::FillRect( hdc,&src,brush);
		string strText = "您的软件没有注册，请注册后使用。\n客服EMAIL:gge@globaleye.co";//QQ:214010522";//EMAIL:gge@globaleye.co"//
		::DrawText( hdc, strText.c_str(),strText.length() ,&src,DT_LEFT | DT_WORDBREAK );
		//SelectObject(hdc,oldbrush );
		//TextOut(hdc,m_rcWnd.left+100,m_rcWnd.top+100,strText.c_str(),strText.length());
		//::BitBlt( hdc,0,0,m_rcWnd.width(),m_rcWnd.height(),m_memDC,0,0,SRCCOPY);
		return;
	}*/
}
//绘制地图
void CMapDisp::DrawMap2StretchDC()
{
	//HBRUSH hbr = CreateSolidBrush(RGB(230,230,230));
	RECT  src;
	src.left = 0;
	src.top = 0;
	src.right = m_rcWnd.width();
	src.bottom = m_rcWnd.height();
	::FillRect( m_memDCStretch,&src,m_hbr);
//	TRACE( " CMapDisp::DrawMap \r\n" );
// 	BitBlt
// 		(
// 		m_memDCStretch,
// 		0,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
// 		0,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
// 		m_rcWnd.width(),								// specifies the width (in logical units) of the destination rectangle
// 		m_rcWnd.height(),								// specifies the height (in logical units) of the destination rectangle
// 		m_memDC,								// specifies the source device context
// 		0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
// 		0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
// 		//						width,								// specifies the width (in logical units) of the source rectangle
// 		//						height,								// specifies the height (in logical units) of the source rectangle
// 		SRCCOPY								// specifies the raster operation to be performed
// 			);
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.OnDraw( m_memDCStretch,m_iLevel, gptMapCenter, m_rcWnd );
	
	if( m_pMapDispLayerMark )
		m_pMapDispLayerMark->OnDraw(  m_memDCStretch,m_iLevel, gptMapCenter, m_rcWnd );
}
//窗口大小改变事件
void CMapDisp::OnSize( int cx, int cy )
{
	if ( cx <= 0 && cy <= 0 )
	{
		return;
	}
	m_rcWnd.left = 0;
	m_rcWnd.top = 0;
	m_rcWnd.right = cx;
	m_rcWnd.bottom = cy;
	// 创建bitmap
	if (m_bitmap)
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	if ( m_bitmapStretch )
	{
		::DeleteObject( m_bitmapStretch );
		m_bitmapStretch = NULL;
	}
	//创建bitmap
	HDC hdc = GetDC(m_hwnd);
	// 首先让系统生成一个32位的bmp缓存
	bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmp_info.bmiHeader.biWidth = cx;
	bmp_info.bmiHeader.biHeight = cy;
	bmp_info.bmiHeader.biPlanes = 1;
	bmp_info.bmiHeader.biBitCount = 32;
	bmp_info.bmiHeader.biCompression = BI_RGB;
	bmp_info.bmiHeader.biSizeImage = 0;
	bmp_info.bmiHeader.biXPelsPerMeter = 0;
	bmp_info.bmiHeader.biYPelsPerMeter = 0;
	bmp_info.bmiHeader.biClrUsed = 0;
	bmp_info.bmiHeader.biClrImportant = 0;
	void* buf = 0;
	m_bitmap = ::CreateDIBSection( hdc, &bmp_info, DIB_RGB_COLORS, &buf, 0, 0 );
	//::CreateCompatibleBitmap( hdc, width,height );
	if ( m_memDC )
	{
		::SelectObject( m_memDC,m_bitmap );
	}
	//====================AGG Start====================================== // 以下是AGG代码  
	// BMP是上下倒置的，为了和GDI习惯相同，最后一个参数是负值。
	m_rbuf.attach((unsigned char*)buf, cx, cy, -cx*4);

	//m_bitmap = ::CreateCompatibleBitmap( hdc, cx, cy );
	//SelectObject( m_memDC, m_bitmap );
	
	m_bitmapStretch = ::CreateCompatibleBitmap( hdc, cx, cy );
	::SelectObject( m_memDCStretch, m_bitmapStretch );

	//RGB(230,230,230)
	//清空下载列表，
//	m_download.ClearDownLoadList();
//	m_MapDataDown.ClearNoDownLoadList();
	//加载地图数据
	SetMapBound();
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	if( m_pMapDispLayerMark )
		m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	Invalidate();
//	m_memDC->SelectObject(&m_brushBg);
//	m_memDC->SelectObject( &m_penBg );
}
//鼠标消息
void CMapDisp::OnLButtonDown( VOSPoint point )
{
	m_MapLayerMan.OnLButtonDown( point );

	m_pntStart.x = point.x;
	m_pntStart.y = point.y;
	m_pntSpeed.x = point.x;
	m_pntSpeed.y = point.y;
	m_ulSpeedTickCount = ::GetTickCount();
	m_bFlagMoveMap = true;
	SetCursor(m_hCursor);
}
void CMapDisp::OnLButtonUp( VOSPoint point)
{
	m_MapLayerMan.OnLButtonUp( point );
//	m_MapDataDown.ClearNoDownLoadList();
	m_bFlagMoveMap = false;
	m_pntSpeed.x = point.x - m_pntSpeed.x;
	m_pntSpeed.y = point.y - m_pntSpeed.y;
	m_ulSpeedTickCount = ::GetTickCount()-m_ulSpeedTickCount;

	if ( m_ulSpeedTickCount!= 0 )
	{
		m_iSpeedX = m_pntSpeed.x*30/m_ulSpeedTickCount;
		m_iSpeedY = m_pntSpeed.y*30/m_ulSpeedTickCount;
	}
	else
	{
		m_iSpeedX = 0;
		m_iSpeedY = 0;
	}
	if( m_iSpeedX > 1000 || m_iSpeedX < -1000 || m_iSpeedY >1000 || m_iSpeedY <-1000)
	{
		int io=00l;
	}
	SetMapBound();
#ifdef _GMAPX_CTROL_
	//	g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	if( m_pMapDispLayerMark )
		m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	Invalidate();
}
void CMapDisp::OnMouseMove( VOSPoint point)
{
	if( m_bFlagMoveMap )
	{
	//	HDC hdc = ::GetDC( m_hwnd );
		int iDx = point.x - m_pntStart.x;
		int iDy = point.y - m_pntStart.y;
		OnMoveMap( iDx, iDy );
		Invalidate();
	}
 	else
 	{
		if( m_MapLayerMan.OnMouseMove( point ) )
			return;
 	}
}
void CMapDisp::OnKillFocus()
{
	m_bFlagMoveMap = false;
}
BOOL CMapDisp::OnMouseWheel( short zDelta, VOSPoint pt)
{
	if ( m_ZoomParam.bOnZoom )
	{
		return false;
	}
	if ( zDelta > 0 )
	{
		if ( m_iLevel < this->m_maxLevel )
		{
			MapZoomIn( pt );
			//MapZoomIn();
		}
	}
	else
	{
		if ( this->m_iLevel > this->m_minLevel )
		{
			MapZoomOut( pt );
			//MapZoomOut();
		}
	}
	return 1;
}
void CMapDisp::OnLButtonDblClk( VOSPoint point )
{
	//MapZoomIn( point );
}

//void OnDownload( tDownLoadParam* param );
void CMapDisp::OnDownload( tDownLoadParam* param )
{
//	m_MapDataDown.RenameDownLoadFile( param );
	SetMapBound();
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	if( m_pMapDispLayerMark )
		m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
//	m_MapDispLayer.LoadMapData();
	Invalidate();

}
void CMapDisp::OnMapMove( VOSPoint point )
{
	if( m_bFlagMoveMap )
		return;
	int l111= ::GetTickCount() - m_lMapMoveTickCount;
	m_lMapMoveTickCount = ::GetTickCount();
	if( point.x != 0 && point.y != 0 )
	{
		OnMoveMap( point.x,point.y );
		long point1 = MAKELONG(point.x*3/4,point.y*3/4);
		if( m_hwnd != NULL )
		{
			PostMessage( m_hwnd,WM_MAPMOVE_MESSAGE, 0,(unsigned int)point1);
		}
	}
}

//地图坐标转换为屏幕坐标
void CMapDisp::MapToScreen( MapPoint mpt, VOSPoint& pt )
{
	MPoint mlevel,mcenter ;
	CMapBase::GetMapPoint( m_iLevel, mpt, mlevel );
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20,mcenter);
	pt.x = m_rcWnd.Width()/2 + ( mlevel.lX - mcenter.lX );
	pt.y = m_rcWnd.Height()/2 + ( mlevel.lY - mcenter.lY );
// 	MapPoint mercator;
// 	float itemp =(2<<(m_iLevel-1))*256;
// 	itemp = itemp/2;
// 	if( itemp!= 0  )
// 	{
// 		mercator = lonLat2Mercator( mpt, itemp );
// 		pt.x = m_rcWnd.Width()/2 + mercator.x + itemp - m_gptMapCenter.lX;
// 		pt.y = m_rcWnd.Height()/2 + itemp - mercator.y - m_gptMapCenter.lY;
// 	}
}
//屏幕坐标转换为地图坐标
void CMapDisp::ScreenToMap( VOSPoint pt, MapPoint& mpt )
{
	VOSPoint point;
	point.x = pt.x-m_rcWnd.Width()/2;
	point.y = pt.y-m_rcWnd.Height()/2;
	MPoint mxy,mxy20;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, mxy );
	mxy.lX += point.x;
	mxy.lY += point.y;
	CMapBase::GetMapPoint20( m_iLevel,mxy, mxy20 );
	CMapBase::MapPoint2LonLat( mxy20, mpt );
// 	MapPoint mercator;
// 	float itemp =(2<<(m_iLevel-1))*256;
// 	int i1111 = itemp;
// 	itemp = itemp/2;
// 	if( itemp!= 0  )
// 	{
// 		mercator.x = m_gptMapCenter.lX + pt.x - m_rcWnd.Width()/2 - itemp;
// 		mercator.y = itemp - ( m_gptMapCenter.lY + pt.y-m_rcWnd.Height()/2 ) ;
// 		mpt = Mercator2lonLat( mercator, itemp );
// 	}
}
void CMapDisp::OnMapZoomIn( )
{
	VOSPoint pt;
	pt.x = m_rcWnd.width()/2;
	pt.y = m_rcWnd.height()/2;
	if ( m_iLevel < this->m_maxLevel )
	{
		MapZoomIn( pt );
	}
	/*if ( m_iLevel+1 <= 20 )
	{
		MapZoomIn( pt );
	}*/
}
void CMapDisp::OnMapZoomOut( )
{
	VOSPoint pt;
	pt.x = m_rcWnd.width()/2;
	pt.y = m_rcWnd.height()/2;
	if ( this->m_iLevel > this->m_minLevel )
	{
		MapZoomOut( pt );
	}
	/*if ( this->m_iLevel-1 >= 2 )
	{
		MapZoomOut( pt );
	}*/
}
void CMapDisp::OnMapZoom()
{
//	TRACE("OnMapZoom m_ZoomParam.iZoomLevel = %d\r\n",m_ZoomParam.iZoomLevel);
	int iZoomLevel = 0;
	//HBRUSH hbr = CreateSolidBrush(RGB(230,230,230));
// 	RECT  src;
// 	src.left = 0;
// 	src.top = 0;
// 	src.right = m_rcWnd.width();
// 	src.bottom = m_rcWnd.height();
// 	::FillRect( m_memDC,&src,hbr);
	if( m_ZoomParam.iZoomLevel > 0 )
	{
		m_ZoomParam.iZoomLevel--;
		iZoomLevel = m_ZoomParam.iZoomLevel;
		//m_penBg = CreatePen( PS_SOLID,1, COLORRBG );
		//m_brushBg = CreateSolidBrush( COLORRBG );
		/*
		HPEN pen = SelectObject( m_memDC, m_penBg );
		HBRUSH brush = SelectObject(m_memDC,m_brushBg );
		Rectangle( m_memDC, m_rcWnd );
		Rectangle( m_memDC,m_rcWnd);
		SelectObject( m_memDC, pen );
		SelectObject( m_memDC, brush );*/
		

		int idx = m_rcWnd.width()/2*(_ZOOM_MAX_COUNT - iZoomLevel ) / _ZOOM_MAX_COUNT*m_ZoomParam.point.x/m_rcWnd.Width();
		int idy = m_rcWnd.height()/2*(_ZOOM_MAX_COUNT - iZoomLevel ) / _ZOOM_MAX_COUNT*m_ZoomParam.point.y/m_rcWnd.Height();
		
		int iWidth = m_rcWnd.Width()- m_rcWnd.Width()*(_ZOOM_MAX_COUNT-iZoomLevel)/_ZOOM_MAX_COUNT/2;
		int ihight = m_rcWnd.Height()- m_rcWnd.Height()*(_ZOOM_MAX_COUNT-iZoomLevel)/_ZOOM_MAX_COUNT/2;

		StretchBlt
			(
			m_memDC,
			0,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
			0,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
			m_rcWnd.Width(),								// specifies the width (in logical units) of the destination rectangle
			m_rcWnd.Height(),								// specifies the height (in logical units) of the destination rectangle
			m_memDCStretch,								// specifies the source device context
			idx,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			idy,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			iWidth,								// specifies the width (in logical units) of the source rectangle
			ihight,								// specifies the height (in logical units) of the source rectangle
			SRCCOPY								// specifies the raster operation to be performed
			);
		Invalidate();
	}
	else if( m_ZoomParam.iZoomLevel < 0 )
	{
		m_ZoomParam.iZoomLevel++;
		iZoomLevel = -m_ZoomParam.iZoomLevel;
		int idx = m_rcWnd.Width()/4*(_ZOOM_MAX_COUNT - iZoomLevel ) / _ZOOM_MAX_COUNT*m_ZoomParam.point.x/m_rcWnd.Width();
		int idy = m_rcWnd.Height()/4*(_ZOOM_MAX_COUNT - iZoomLevel ) / _ZOOM_MAX_COUNT*m_ZoomParam.point.y/m_rcWnd.Height();
		
		int iWidth = m_rcWnd.Width()- m_rcWnd.Width()*(_ZOOM_MAX_COUNT-iZoomLevel)/_ZOOM_MAX_COUNT/4;
		int ihight = m_rcWnd.Height()- m_rcWnd.Height()*(_ZOOM_MAX_COUNT-iZoomLevel)/_ZOOM_MAX_COUNT/4;

	/*	CBrush* pBrush = m_memDC->SelectObject(&m_brushBg);
		CPen* pen = m_memDC->SelectObject( &m_penBg );
		m_memDC->Rectangle(m_rcWnd);
		m_memDC->SelectObject(pBrush);
		m_memDC->SelectObject( pen );*/
		//	m_memDC->SetStretchBltMode( STRETCH_HALFTONE );
		//HBRUSH hbr = CreateSolidBrush(RGB(230,230,230));
		RECT  src;
		src.left = 0;
		src.top = 0;
		src.right = m_rcWnd.width();
		src.bottom = m_rcWnd.height();
		::FillRect( m_memDC,&src,m_hbr);

		StretchBlt
			(
			m_memDC,
			idx,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
			idy,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
			iWidth,				// specifies the width (in logical units) of the destination rectangle
			ihight,			// specifies the height (in logical units) of the destination rectangle
			m_memDCStretch,																	// specifies the source device context
			0,																				// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			0,																				// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			m_rcWnd.Width(),																// specifies the width (in logical units) of the source rectangle
			m_rcWnd.Height(),																// specifies the height (in logical units) of the source rectangle
			SRCCOPY																			// specifies the raster operation to be performed
			);
		Invalidate();
	}
	else
	{
	//	LoadMapData();
		//m_memDC->Rectangle(m_rcWnd);
//		TRACE("zoom[-----------------------------------]");
		m_ZoomParam.bOnZoom = false;
		KillTimer( m_hwnd,_MAP_TIMER_PROC);
		SetMapBound();
#ifdef _GMAPX_CTROL_
//		g_pGmapxCtrl->FireOnMapZoom( m_iLevel );
//		g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
		MPoint gptMapCenter;
		CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
		m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
		Invalidate();
		return;
	}
	/*
	CDC* pDC = m_pWnd->GetDC();
	pDC->BitBlt(0,0,m_rcWnd.Width(),m_rcWnd.Height(),m_memDC,0,0,SRCCOPY);
	float idxCursor = 10*iZoomLevel/_ZOOM_MAX_COUNT;
	DrawCursor( pDC,m_ZoomParam.point, idxCursor);*/
//	g_pAppMan->m_GmWnd.OnDraw( pDC );
	//Sleep(10);
//	OnMapZoom();	
	
	
}

void CMapDisp::OnTimer( unsigned int nIDEvent)
{
	if ( m_bMapAutoMove )
	{
//		TRACE("m_bMapAutoMove\r\n");
		OnMoveMap( m_iSpeedX,m_iSpeedY );
		Invalidate();
		m_iSpeedX = m_iSpeedX*3/4;
		m_iSpeedY = m_iSpeedY*3/4;
		if ( m_iSpeedX == 0 && m_iSpeedY == 0 )
		{
			m_bMapAutoMove = false;
			SetMapBound();
			MPoint gptMapCenter;
			CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
			m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
			if( m_pMapDispLayerMark )
					m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
			Invalidate();
		}
	}
	if ( m_ZoomParam.bOnZoom )
	{
		OnMapZoom();
	}
	return;
	switch( nIDEvent )
	{
	case _MAP_MOVE_TIMER_PROC:
		{
			if( m_bFlagMoveMap )
			{
				KillTimer( m_hwnd, _MAP_MOVE_TIMER_PROC );
				break;
			}
//			TRACE( "OnTimer m_iSpeedX=%d,m_iSpeedY=%d \r\n", m_iSpeedX, m_iSpeedY );
			OnMoveMap( m_iSpeedX,m_iSpeedY );
			m_iSpeedX = m_iSpeedX*3/4;
			m_iSpeedY = m_iSpeedY*3/4;
			if( m_iSpeedX == 0 && m_iSpeedY == 0 )
			{
				KillTimer( m_hwnd,_MAP_MOVE_TIMER_PROC );
			}
		}
		break;
	case _MAP_ZOOM_TIMER_PROC:
		{
			if( m_ZoomParam.iZoomLevel == 0 )
			{
				KillTimer( m_hwnd, _MAP_ZOOM_TIMER_PROC );
				break;
			}
			else
			{
				OnMapZoom();
			}
		}
	default:
		;
	}
}
//检查当前的绘制列表中是否存在改绘制参数
/*bool CMapDisp::CheckParamInDrawList( CMapBlockUnit* pBlockParam, int m_iLevel, int iMinX, int iMaxX, int iMinY, int iMaxY )
{
	if( pBlockParam->lLevel == m_iLevel 
		&&pBlockParam->lNumX >= iMinX && pBlockParam->lNumX <= iMaxX
		&&pBlockParam->lNumY >= iMinY && pBlockParam->lNumY <= iMaxY && pBlockParam->bDraw )
	{
		return true;
	}
	else
		return false;
}*/

//绘制光标
//void DrawCursor(CDC* pDC, CPoint pt, float fZoom );
//检查地图是否出界，出界的给改到正确位置
bool CMapDisp::CheckAndSetMapCenter()
{
	return true;
	bool bret = true;
	if ( m_iLevel > 20 && m_iLevel < 0 )
	{
		return false;
	}
	if( m_MapCenter20.lX < 0 )
	{
		m_MapCenter20.lX = 0;
		bret = false;
	}
	if ( m_MapCenter20.lX > (2<<(20-1))*256 )
	{
		m_MapCenter20.lX = (2<<(20-1))*256;
		bret = false;
	}
	if ( m_MapCenter20.lY < 0 )
	{
		m_MapCenter20.lY = 0;
		bret = false;
	}
	if ( m_MapCenter20.lY > (2<<(20-1))*256 )
	{
		m_MapCenter20.lY = (2<<(20-1))*256;
		bret = false;
	}
	return bret;
}
//获得地图中心点坐标
MPoint* CMapDisp::GetMapCenter()
{
	return &m_MapCenter20;
}
void CMapDisp::SetMapLevel( long level )
{
	int iOffSet = level - m_iLevel;
	if ( iOffSet == 0 )
	{
		return;
	}
// 	else if ( iOffSet > 0 )
// 	{
// 		m_gptMapCenter.lX = m_gptMapCenter.lX << iOffSet;
// 		m_gptMapCenter.lY = m_gptMapCenter.lY << iOffSet;
// 	}
// 	else
// 	{
// 		m_gptMapCenter.lX = m_gptMapCenter.lX >> abs( iOffSet );
// 		m_gptMapCenter.lY = m_gptMapCenter.lY >> abs( iOffSet );
// 	}
	m_iLevel = level;
	SetMapBound();
#ifdef _GMAPX_CTROL_
//		g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	//if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
//	m_MapDispLayer.LoadMapData();
	Invalidate();
}
long CMapDisp::GetMapLevel()
{
	return m_iLevel;
}
//设置地图默认位置
void CMapDisp::SetMapDefault()
{
	MPoint gptMapCenter;
	gptMapCenter.lX = (414*8);
	gptMapCenter.lY = (194*8);
	m_iLevel = 4;
	CMapBase::GetMapPoint20( m_iLevel, gptMapCenter, m_MapCenter20 );
	SetMapBound();
#ifdef _GMAPX_CTROL_
//		g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
//	MPoint gptMapCenter;
//	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
//	if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
	Invalidate();
}
//设置MapBound
void CMapDisp::SetMapBound( MapPoint ptlt, MapPoint ptrb )
{
	m_MapBound.left = ptlt.x;
	m_MapBound.top = ptlt.y;
	m_MapBound.right = ptrb.x;
	m_MapBound.bottom = ptrb.y;
}
//设置MapBound
void CMapDisp::SetMapBound()
{
	VOSPoint pt( 0,0 ) ;
	MapPoint mpt;
	ScreenToMap( pt, mpt );
	m_MapBound.left = mpt.x;
	m_MapBound.top = mpt.y;
	pt.x = m_rcWnd.Width();
	pt.y = m_rcWnd.Height();
	ScreenToMap( pt, mpt );
	m_MapBound.right = mpt.x;
	m_MapBound.bottom = mpt.y;
}
//得到MapBound
MapBount*	CMapDisp::GetMapBound()
{
	return &m_MapBound;
}
//检查坐标是否在屏幕内
bool CMapDisp::IsMapPointInMapCreen( MapPoint pt )
{
	return m_MapBound.IsPointIn( pt );
}

//得到地图中线点坐标
void CMapDisp::GetMapCenter( MapPoint& mpt )
{
	VOSPoint pt( m_rcWnd.Width()/2,m_rcWnd.Height()/2 );
	ScreenToMap( pt, mpt );
}
//移动地图到指定的点
void CMapDisp::MoveMap( MapPoint mpt )
{
	CMapBase::LonLat2MapPoint20( mpt, m_MapCenter20 );
	SetMapBound();
#ifdef _GMAPX_CTROL_
	//	g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	//if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
	Invalidate();
}

//移动地图到指定的点
void CMapDisp::MoveMap( MapPoint mpt,long level )
{
	m_iLevel = level;
	MoveMap( mpt );
}
//移动地图到一个区域范围
void CMapDisp::MoveMapBound( double x1, double y1, double x2, double y2 )
{
	MapPoint mpt1,mpt2,mptcenter;
	MPoint mp1,mp2;
	mpt1.x = x1;
	mpt1.y = y1;
	mpt2.x = x2;
	mpt2.y = y2;
	mptcenter.x = (x1+x2)/2.0;
	mptcenter.y = (y1+y2)/2.0;
	CMapBase::LonLat2MapPoint20( mptcenter, m_MapCenter20 );
	CMapBase::LonLat2MapPoint20( mpt1, mp1 );
	CMapBase::LonLat2MapPoint20( mpt2, mp2 );
	//----
	long loffset = 0;
	if( abs(mp1.lX - mp2.lX ) / m_rcWnd.width() > abs(mp1.lY - mp2.lY ) / m_rcWnd.height() )
	{
		loffset = abs(mp1.lX - mp2.lX ) / m_rcWnd.width();
	}
	else
	{
		loffset = abs(mp1.lY - mp2.lY ) / m_rcWnd.height();
	}
	m_iLevel = 20;
	for( int i = 0; i < 20;i++)
	{
		loffset = loffset>>1;
		if( loffset < 1 )
		{
			m_iLevel = 20-i-1;
			break;
		}
	}
	SetMapBound();
#ifdef _GMAPX_CTROL_
	//g_pGmapxCtrl->FireOnMapOnSize( m_MapBound.left, m_MapBound.right,m_MapBound.bottom, m_MapBound.top,m_iLevel );
#endif
	MPoint gptMapCenter;
	CMapBase::GetMapPoint( m_iLevel, m_MapCenter20, gptMapCenter );
	m_MapDispLayer.LoadMapData( m_iLevel, gptMapCenter, m_rcWnd  );
	//if( m_enMapType == GMAP_GOOGLE_IMAGEMARK )
	{
		if( m_pMapDispLayerMark )
			m_pMapDispLayerMark->LoadMapData( m_iLevel, gptMapCenter, m_rcWnd );
	}
	Invalidate();
}
CMapDispLayer* CMapDisp::GetMapDispLayer( int iMapID )
{
	if( GMAP_GOOGLE_MARK == iMapID )
	{
		if( m_pMapDispLayerMark != NULL )
			return m_pMapDispLayerMark;
	}
	return &m_MapDispLayer;
}
//发送消息
void CMapDisp::PostMessageEx( unsigned long message,unsigned long param1, unsigned long param2 )
{
	::PostMessage( this->m_hwnd,message,param1,param2);
}
//注册程序
long CMapDisp::RegisterKey(char* strRegisterKey)
{
	return 1;
}
//设置比例尺
void CMapDisp::SetMapScaleBound(long minscale, long maxscale)
{
	this->m_maxLevel = maxscale;
	this->m_minLevel = minscale;
}