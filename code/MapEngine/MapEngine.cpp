#include "StdAfx.h"
#include "MapEngine.h"
#include "VOSBase/VOSBase.h"
#include "MapLayer/MapLeyerMan.h"

double x1=116;
double y11=39;
int g_iTimes = 0;

//fun_msg g_fun_msg=NULL;
//unsigned char* g_Memery = NULL;//全局内存，仅供地图图片加载临时使用
CMapEngine::CMapEngine(void)
{
	m_memhdc = NULL;
	m_bitmap = NULL;
	m_hbr = CreateSolidBrush(RGB(230,230,230));
	g_fun_msg = NULL;
}

CMapEngine::~CMapEngine(void)
{
	Destroy();
	g_fun_msg = NULL;
}
//void CMapEngine::WriteLog(CString strLog)
//{
//	CMapBase::WriteLog(strLog.GetBuffer(0));
//}
char g_Text[4096];
void CMapEngine::Init( HWND hwnd )
{
	g_fun_msg = NULL;
	char strRootPath[512]={0};
	m_hwnd = hwnd;
//	m_pGmapxCtrl = pGmapxCtrl;
	//得到用户根目录
//	::SHGetSpecialFolderPath(NULL,strRootPath,CSIDL_APPDATA,FALSE);
	//得到程序当前目录//GetModuleHandle 
	GetModuleFileName( AfxGetInstanceHandle(), strRootPath, 256 ); 
	//::GetModuleFileName( NULL, strRootPath, 256 );
	char* pEnd = strrchr( strRootPath,_T('\\'));
	if( pEnd == NULL )
		return;
	pEnd[1]=0;
//	GetWindowsDirectory(strRootPath,255);
	m_strRootPath = strRootPath;
	CMapBase::SetMapRootPath( strRootPath );
	//m_strRootPath+="\\gmap";
	//CreateDirectory( m_strRootPath.c_str(),NULL);
	//m_strRootPath+="\\";
	HDC dc = ::GetDC(hwnd);
	//创建DC
	if ( m_memhdc )
	{
		//delete m_memDC;
		::DeleteDC( m_memhdc );
		m_memhdc = NULL;
	}
	m_memhdc = ::CreateCompatibleDC( dc );
	::SetBkColor( m_memhdc,RGB(255,255,255) );
	//初始化aggbuff
	m_MapOffSet.Init( m_strRootPath );
//	m_memDC.CreateCompatibleDC(pDC);
	//m_memDC.SetBkColor( RGB(100,100,100));
	//UI资源初始化
	//m_uiResMan.Init( m_strRootPath, hwnd );
	//地图初始化
	m_MapDisp.Init( hwnd, m_memhdc, m_strRootPath, GMAP_GOOGLE_MAP);//GMAP_GOOGLE_MAP
	// 窗口初始化
	//m_MapZoomCtrl.Init( &m_MapDisp, m_strRootPath, hwnd, 30,75 );
	
	m_MapCtrl.Create( hwnd );
	m_MapCtrl.Init( this,(char*)m_strRootPath.c_str(),hwnd, 0,0 );
	
	//m_MapWnd.Init( hwnd,& m_MapDisp,&m_uiResMan );
//	::SetTimer( m_hwnd, _MAP_TIMER_PROC, _MAP_TIMER, NULL );
	//初始化完成
	PostMessage( m_hwnd,WM_MAP_ONINIT, 0,0);
//	::SetTimer( m_hwnd, _MAP_TIMER_PROC1, _MAP_TIMER1, NULL );
	//E:\work\gmap\trunk\gmap\bin\gugemap\level16\7a669bbb4ea378e00b8c35257bec394d
/*	string str1 = GetMapAddress( 115,38 );
*/
//	m_MifMan.Init( &m_MapDisp.m_MapLayerMan );
//	string strtemp  = m_strRootPath;
//	strtemp += "map\\楚雄分局自辖站点分布图";//中国地图_景点//中国地图_国界线//中国地图_省界面//中国地图_省会点//中国地图_铁路线
//	LoadMifMidData( strtemp );
//	strtemp  = m_strRootPath;
//	strtemp += "mif\\中国地图_省界面";//中国地图_景点//中国地图_国界线//中国地图_省界面//中国地图_省会点//中国地图_铁路线
//	LoadMifMidData( strtemp );
	//SetMapToolsBar( 1 );
	MapPoint mp1111;
	
	mp1111.x = 19.66;
	mp1111.y = -19.3;
	MPoint lonLat20 ;
	CMapBase::LonLat2MapPoint20( mp1111, lonLat20 );

	////103.762050,25.58994
	SetMapParam( 116,39,4 );

	//GetMapAddress(1,1);
}
//设置地图位置
void CMapEngine::SetMapPos( long left, long top, long width, long height, bool bDraw )
{
	if ( width <= 0 && height <= 0 )
	{
		return;
	}
	m_MapDisp.OnSize( width, height );

	m_rect.left = left;
	m_rect.top = top;
	m_rect.right = left+width;
	m_rect.bottom = top+height;
	// 创建bitmap
	if ( m_bitmap )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	HDC hdc = GetDC( m_hwnd );
	// 首先让系统生成一个32位的bmp缓存
	bmp_info.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmp_info.bmiHeader.biWidth = width;
	bmp_info.bmiHeader.biHeight = height;
	bmp_info.bmiHeader.biPlanes = 1;
	bmp_info.bmiHeader.biBitCount = 32;
	bmp_info.bmiHeader.biCompression = BI_RGB;
	bmp_info.bmiHeader.biSizeImage = 0;
	bmp_info.bmiHeader.biXPelsPerMeter = 0;
	bmp_info.bmiHeader.biYPelsPerMeter = 0;
	bmp_info.bmiHeader.biClrUsed = 0;
	bmp_info.bmiHeader.biClrImportant = 0;
	/*
	bMapInfo->bmiHeader.biBitCount = bInfo.bmBitsPixel;
    bMapInfo->bmiHeader.biClrImportant = 0;
    bMapInfo->bmiHeader.biCompression = 0;
    bMapInfo->bmiHeader.biHeight = bInfo.bmHeight;
    bMapInfo->bmiHeader.biPlanes = bInfo.bmPlanes;
    bMapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
    bMapInfo->bmiHeader.biSizeImage = bInfo.bmHeight*bInfo.bmWidthBytes;
    bMapInfo->bmiHeader.biWidth = bInfo.bmWidth;
    bMapInfo->bmiHeader.biXPelsPerMeter = 0;
    bMapInfo->bmiHeader.biYPelsPerMeter = 0;
	*/
	m_bitmap = ::CreateDIBSection( hdc, &bmp_info, DIB_RGB_COLORS, &m_buf, 0, 0 );
	//::CreateCompatibleBitmap( hdc, width,height );
	if ( m_memhdc )
	{
		::SelectObject( m_memhdc,m_bitmap );
	}
	//====================AGG Start====================================== // 以下是AGG代码  
	// BMP是上下倒置的，为了和GDI习惯相同，最后一个参数是负值。
	m_rbuf.attach((unsigned char*)m_buf, width, height, -width*4);

	m_MapCtrl.SetMapRect( m_rect );
}

//设置消息回调函数
void CMapEngine::SetMsgFun( fun_msg msg )
{
	g_fun_msg = msg;
	ShowMapTool(1,0);
}
//设置地图URL路径
void CMapEngine::SetMapUrl(string strMapURL )
{
	SetMapType( GMAP_MYMAP );
	CMapBase::SetMapUrl( strMapURL );
}
//设置本地地图文件路径
void CMapEngine::SetMapPath( string strMapPath )
{
	m_MapDisp.SetMapPath( strMapPath ); 
}
//设置附件图层路径
void CMapEngine::OpenAddMapLayerPath( string strMapFilesPath )
{
	m_MapDisp.OpenAddMapLayerPath( strMapFilesPath );
}
//关闭附加层
void CMapEngine::CloseAddMapLayer( )
{
	m_MapDisp.CloseAddMapLayer();
}
//UnInit释放内存
void CMapEngine::Destroy()
{
	//地图显示释放
	this->m_MapDisp.realse();
	if ( m_bitmap )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	//创建DC
	if ( m_memhdc )
	{
		//delete m_memDC;
		::DeleteDC( m_memhdc );
		m_memhdc = NULL;
	}
	KillTimer( m_hwnd,_MAP_TIMER_PROC);
}
//设置地图显示
long CMapEngine::ShowMapTool(long lType, long lValue)
{
	if( lType == 1 )
		this->m_MapCtrl.SetMapToolsBar( lValue );

	return 1;
}
//设置地图类型 
void CMapEngine::SetMapType( en_MapType eMapType )
{
	//eMapType = GMAP_GOOGLE_IMAGEMARK;
	m_MapDisp.SetMapType( m_strRootPath, eMapType );
}
void CMapEngine::OnDraw( HDC hdc )
{
	g_iTimes++;
	VOSPoint point = m_rect.CenterPoint();
	m_MapDisp.DrawMap( m_memhdc );
//	SaveMap("c://22.jpg" );
	m_MapCtrl.OnDraw(m_memhdc,&m_rbuf);
	/*
	// 像素格式和renderer_base http://www.cppprog.com C++编程网
	agg::pixfmt_bgra32 pixf(m_rbuf); 
	agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 
	renb.clear(agg::rgba8(255, 255, 255, 255)); 
	
	// Scanline renderer 
	agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

	// Rasterizer & scanline
	agg::rasterizer_scanline_aa<> ras;
	agg::scanline_p8 sl;

	// 多义线（三角形） 
	ras.move_to_d(20.7, 34.15); 
	ras.line_to_d(398.23, 123.43);
	ras.line_to_d(165.45, 401.87); 

	// 设置颜色后渲染 
	ren.color(agg::rgba8(80, 90, 60)); 
	agg::render_scanlines(ras, sl, ren); 
	//=================AGG End=========================================*/


	m_ImageMark.Draw( m_memhdc, 0, 0 );

	HPEN hPen,hOldPen; 
	hPen=::CreatePen(PS_SOLID,1,RGB(0,0,0));
	hOldPen=(HPEN)SelectObject(m_memhdc,hPen); 
	
//	MoveToEx(m_memhdc,m_rect.Width()/2,m_rect.Height()/2-20,NULL);
//	LineTo(m_memhdc,m_rect.Width()/2,m_rect.Height()/2+20);
//	MoveToEx(m_memhdc,m_rect.Width()/2-20,m_rect.Height()/2,NULL);
//	LineTo(m_memhdc,m_rect.Width()/2+20,m_rect.Height()/2);
	BitBlt(hdc,m_rect.left,m_rect.top,m_rect.width(),m_rect.height(),m_memhdc,0,0,SRCCOPY);
	SelectObject(m_memhdc,hOldPen); 
	DeleteObject(hPen);

	//
	//SaveMap("c://22.jpg" );
	//char chTemp[100];
	//sprintf(chTemp,"%d次",g_iTimes);
	//::DrawText( hdc, chTemp,strlen(chTemp) ,&m_rect,DT_LEFT | DT_TOP);
//	m_MapWnd.OnDraw( hdc );
}
//鼠标消息
void CMapEngine::OnLButtonDown( VOSPoint point )
{
	TRACE("\nOnLButtonDown");
	SetCapture( m_hwnd );
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
	if ( m_MapCtrl.OnLButtonDown( point ) )
	{
		//return;
	}
	m_MapDisp.OnLButtonDown( point );
}
void CMapEngine::OnLButtonUp( VOSPoint point)
{
	TRACE("OnLButtonUp");
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
	if ( m_MapCtrl.OnLButtonUp( point ) )
	{
		ReleaseCapture( );
		//return;
	}
	//ReleaseCapture();
	ReleaseCapture( );
	m_MapDisp.OnLButtonUp( point );
//	if ( m_MapDisp.m_MapLayerMan.OnClick( point, m_pSelMapPoi ) ) {
//		return;
//	}
}
void CMapEngine::OnKillFocus()
{
	m_MapDisp.OnKillFocus();
}
//检测点是否在地图上
bool CMapEngine::IsInMap( VOSPoint point )
{
	return this->m_rect.IsPointIn( point );
}
void CMapEngine::OnMouseMove( VOSPoint point)
{
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
//	TRACE( "xxh OnMouseMove point.x=%d,point.y=%d \r\n", point.x, point.y );
	if ( m_MapCtrl.OnMouseMove( point ) )
	{
		//return;
	}
	m_MapDisp.OnMouseMove( point );
	//m_MapLayerMan.OnMouseMove( point );
	this->GetMapCenter(x1,y11);
}
void CMapEngine::OnMouseWheel( short zDelta, VOSPoint point)
{
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
	m_MapDisp.OnMouseWheel( zDelta, point );
	m_MapCtrl.OnMouseWheel( zDelta, point );
}
void CMapEngine::OnLButtonDblClk( VOSPoint point )
{
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
	if ( m_MapCtrl.OnLButtonDblClk( point ) )
	{
		return ;
	}
	//m_MapDisp.OnLButtonDblClk( point );;
}
bool CMapEngine::IsPointIn( VOSPoint point, CMapPoi*& poi )
{
	poi = NULL;
	point.x = point.x - m_rect.left;
	point.y = point.y - m_rect.top;
	if ( m_MapCtrl.OnLButtonDblClk( point ) )
	{
		return false;
	}
	if( m_MapDisp.m_MapLayerMan.IsPointIn( point, poi ) )
	{
		return true;
	}
	return false;
}
void CMapEngine::OnTimer( unsigned int nIDEvent)
{
	if ( nIDEvent == _MAP_TIMER_PROC )
	{
		m_MapDisp.OnTimer( nIDEvent );
	}
	if ( nIDEvent == _MAP_TIMER_PROC1 )
	{
		//m_MapDisp.OnTimer( nIDEvent );
		x1-=0.01;
		y11-=0.01;
		this->MoveMap(x1,y11);
		this->Invalidate();
	}
	if ( nIDEvent == _MAP_TIMER_PROC2 )
	{
		m_MapDisp.PostMessageEx( WM_MAP_POIINFO_MESSAGE, 0,0 );
		KillTimer( m_MapDisp.m_hwnd, _MAP_TIMER_PROC2);
	}
	
}
void CMapEngine::OnMapZoomIn( )
{
	m_MapDisp.OnMapZoomIn();
}
void CMapEngine::OnMapZoomOut( )
{
	m_MapDisp.OnMapZoomOut();
}
//移动地图到
void CMapEngine::MoveMap( double dMapX, double dMapY )
{
	MapPoint mpt;
	mpt.x = dMapX;
	mpt.y = dMapY;
	m_MapDisp.MoveMap( mpt );
	Invalidate();
}
//移动地图
void CMapEngine::MoveMapBound(double x1, double y1, double x2, double y2)
{
	m_MapDisp.MoveMapBound(x1,y1,x2,y2);
}
/*	窗口的消息处理 */
void CMapEngine::MsgProc( ULONG ulID, ULONG wParam, ULONG lParam )
{
	switch( ulID )
	{
	case WM_MOUSEMOVE:
		{
			//#define VOS_LOWORD(l)		((VOSWord)(l))	// 得到低字
			//#define VOS_HIWORD(l)       ((VOSWord)(((VOSDWord)(l) >> 16) & 0xFFFF))	// 高字低字
			VOSPoint pt;
			pt.x = (short)LOWORD( lParam );
			pt.y = (short)HIWORD( lParam );
			this->OnMouseMove( pt );
			break;
		}
	case WM_LBUTTONDOWN:
		{
			VOSPoint pt;
			pt.x = (short)LOWORD( lParam );
			pt.y = (short)HIWORD( lParam );
			this->OnLButtonDown( pt );
			break;
		}
	case WM_LBUTTONUP:
		{
			VOSPoint pt;
			pt.x = (short)LOWORD( lParam );
			pt.y = (short)HIWORD( lParam );
			this->OnLButtonUp( pt );
			break;
		}
	case WM_MOUSEWHEEL:
		{
			//fwKeys   =   LOWORD(wParam);   /*   key   flags   */     
			short zDelta   =   (short) HIWORD(wParam);     
			/*   wheel   rotation   */   
			//xPos   =   (short)   LOWORD(lParam);     
			/*   horizontal   position   of   pointer   */   
			//yPos   =   (short)   HIWORD(lParam);     
			/*   vertical   position   of   pointer   */     
			POINT pt;
		//	VOSPoint pt;
			pt.x = (short)LOWORD( lParam );
			pt.y = (short)HIWORD( lParam );
		//	CPoint pt1( pt );
			ScreenToClient( this->m_hwnd, &pt );
			
			VOSPoint point(pt.x,pt.y);
			if( this->m_rect.IsPointIn( point ) )
			{
				this->OnMouseWheel( zDelta, point );
			}
			break;
		}
	case WM_LBUTTONDBLCLK:
		{
			VOSPoint pt;
			pt.x = (short)LOWORD( lParam );
			pt.y = (short)HIWORD( lParam );
			this->OnLButtonDblClk( pt );
			break;
		}
	case WM_TIMER:
		{
			this->OnTimer( wParam );
			break;
		}
	case WM_KILLFOCUS:
		{
			this->OnKillFocus();
			break;
		}
		case WM_DOWNLOAD_MESSAGE:
		{
			m_MapDisp.OnDownload((tDownLoadParam*)lParam);
			break;
		}
	case WM_MAPMOVE_MESSAGE:
		{
			VOSPoint point;
			((DWORD)lParam);
			m_MapDisp.OnMapMove( point );
			break;
		}
	case WM_MAP_ZOOM_MESSAGE:
		{
			m_MapDisp.OnMapZoom();
			break;
		}
	/*case VOS_WM_LBUTTONDOWN:
		{
			m_MapDisp.OnMapZoom();
			break;
		}*/
	case WM_MAP_ONINIT:
		{
			//m_MapDisp.OnMapZoom();
			//this->SetMapPath("E:\\work\\gmap\\trunk\\gmap\\bin\\瓦片数据\\卫星地图\\level%z\\%y\\%x.png");
			//初始化完成消息
			break;
		}
	case VOS_WM_COMMAND:
		m_MapCtrl.OnCommand( wParam,lParam,0);
		break;
	default:
		;
	}
}
//地图坐标转换为屏幕坐标
void CMapEngine::MapToScreen( double dMapX, double dMapY, long& lScreenX, long& lScreenY )
{
	MapPoint mpt;
	mpt.x = dMapX;
	mpt.y = dMapY;
	VOSPoint pt;
	m_MapDisp.MapToScreen( mpt, pt );
	lScreenX = pt.x + m_rect.left;
	lScreenY = pt.y + m_rect.top;
}
void CMapEngine::ScreenToMap( long lScreenX, long lScreenY, double& dMapX, double& dMapY )
{
	VOSPoint pt;
	pt.x = lScreenX - m_rect.left;
	pt.y = lScreenY - m_rect.top;
	MapPoint mpt;
	m_MapDisp.ScreenToMap( pt, mpt );
	dMapX = mpt.x;
	dMapY = mpt.y;
}
//地图坐标转换为屏幕坐标
// void CMapEngine::MapToScreen( MapPoint mpt, VOSPoint& pt )
// {
// 	m_MapDisp.MapToScreen( mpt, pt );
// }
// //屏幕坐标转换为地图坐标
// void CMapEngine::ScreenToMap( VOSPoint pt, MapPoint& mpt )
// {
// 	m_MapDisp.ScreenToMap( pt, mpt );
// }
	//得到地图中心点坐标
void CMapEngine::GetMapCenter( double& dMapX, double& dMapY )
{
	MapPoint mpt;
	m_MapDisp.GetMapCenter( mpt );
	dMapX = mpt.x;
	dMapY = mpt.y;
}
//添加图层
long CMapEngine::CreateMapLeyer()
{
	CMapLayer* pMapLayer = new CMapLayer();
	return m_MapDisp.m_MapLayerMan.AddMapLayer( pMapLayer );
}
//删除图层
bool CMapEngine::DeleteMapLayer( int nID )
{
	return m_MapDisp.m_MapLayerMan.DeleteMapLayer( nID );
}
//删除图层
// void CMapEngine::DeleteMapLayers( CMapLayer* pMapLayer )
// {
// 	DeleteMapLayers( pMapLayer );
// }
//删除全部图层
void CMapEngine::DeleteAllMapLayer()
{
	m_MapDisp.m_MapLayerMan.ClearAllMapLayer();
}
//添加POI点
long CMapEngine::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID )
{
	return m_MapDisp.m_MapLayerMan.AddMapLayerPoint( nLayerID, lMapX, lMapY, strName, icoID );
}
//添加POI点
long CMapEngine::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName )
{
	return m_MapDisp.m_MapLayerMan.AddMapLayerPoint( nLayerID, lMapX, lMapY, strName, strFileName );
}
//刷新屏幕
void CMapEngine::Invalidate()
{
//	TRACE( "Invalidate \r\n " );
	RECT rc;
	rc =m_rect;
	if( m_hwnd == NULL )
		return;
	::InvalidateRect( m_hwnd,&rc , false );
	return;
}
//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
long CMapEngine::CreateMapRes( string strpath )
{
	return m_MapDisp.m_MapLayerMan.CreateRes( strpath );
}
//加载mif数据
bool CMapEngine::LoadMifMidData( string strFileName )
{
	if (!m_MifMan.loaddata(  strFileName.c_str()) )
		return false;
	return true;
}
bool CMapEngine::CreateMapPoint( long pointid )
{
	return m_MapDisp.m_MapLayerMan.CreatMapPoint( pointid );
}
bool CMapEngine::CreateMapPoint( long pointid, double x, double y, string strName, string strText, long icoID )
{
	Invalidate();
	return m_MapDisp.m_MapLayerMan.CreatMapPoint( pointid,x,y,strName,strText,icoID );
}
bool CMapEngine::SetMapPoint(long pointID, double x, double y)
{
	return m_MapDisp.m_MapLayerMan.SetMapPoint(pointID,x,y);
}
bool CMapEngine::SetMapPointName(long pointID, string name)
{
	return m_MapDisp.m_MapLayerMan.SetMapPointName( pointID, name );
}
bool CMapEngine::SetMapPointText(long pointID, string text)
{
	return m_MapDisp.m_MapLayerMan.SetMapPointText( pointID,text);
}
bool CMapEngine::SetMapPointICO(long pointID, long icoid )
{
	return m_MapDisp.m_MapLayerMan.SetMapPointICO( pointID, icoid );
}
bool CMapEngine::DeleteMapPoint(long pointID)
{
	Invalidate();
	return m_MapDisp.m_MapLayerMan.DeleteMapPoint( pointID );
}
void CMapEngine::DeleteAllMapPoint()
{
	m_MapDisp.m_MapLayerMan.DeleteAllMapPoint();
	Invalidate();
}
bool CMapEngine::CreateMapLine( long lineID )
{
	Invalidate();
	return m_MapDisp.m_MapLayerMan.CreatMapLine( lineID );
}
bool CMapEngine::AddMapLinePoint( long lineID, double x, double y )
{
	return m_MapDisp.m_MapLayerMan.AddMapLinePoint( lineID, x, y );
}
bool CMapEngine::SetMapLineName( long lineID, string name )
{
	return m_MapDisp.m_MapLayerMan.SetMapLineName( lineID, name );
}
bool CMapEngine::SetMapLineColor( long lineID, long lineColor )
{
	return m_MapDisp.m_MapLayerMan.SetMapLineColor( lineID, lineColor );
}
bool CMapEngine::SetMapLineWidth( long lineID, long lineWidth )
{
	return m_MapDisp.m_MapLayerMan.SetMapLineWidth( lineID, lineWidth );
}
bool CMapEngine::DeleteLine(long lineID)
{
	return m_MapDisp.m_MapLayerMan.DeleteLine( lineID );
}
//创建多边形对象
bool CMapEngine::CreateMapPolygon(long polygonID )
{
	Invalidate();
	return m_MapDisp.m_MapLayerMan.CreatMapPolygon( polygonID );
}
//添加点
bool CMapEngine::AddMapPolygonPoint( long polygonID, double x, double y )
{
		return m_MapDisp.m_MapLayerMan.AddMapPolygonPoint( polygonID, x, y );
}
//删除多边形对象
bool CMapEngine::DeleteMapPolygon(long polygonID)
{
	return m_MapDisp.m_MapLayerMan.DeleteMapPolygon( polygonID );
}
long CMapEngine::GetMapScale()
{
	return m_MapDisp.GetMapLevel();
}
void CMapEngine::SetMapScale(long scale)
{
	m_MapDisp.SetMapLevel( scale );
	m_MapCtrl.OnMapZoom();
	Invalidate();
}
void CMapEngine::SetMapParam(double x, double y, long scale)
{
	m_MapDisp.SetMapLevel( scale );
	MoveMap( x, y );
	Invalidate();
}
void CMapEngine::AutoMoveMap(double x, double y)
{
	MapPoint mpt;
	mpt.x = x;
	mpt.y = y;
	if( !this->m_MapDisp.IsMapPointInMapCreen( mpt ) )
	{
		MoveMap( x, y );
	}
	Invalidate();
}
//绘制半圆
void CMapEngine::CreateMapAround( long rid, double x, double y, long radius, long alpha )
{
	Invalidate();
	m_MapDisp.m_MapLayerMan.CreateMapAround( rid,x,y,radius,alpha);
}
void CMapEngine::DeleteMapAround( long rid )
{
	Invalidate();
	m_MapDisp.m_MapLayerMan.DeleteMapAround(rid);
}
//绘制文字
void CMapEngine::CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color)
{
	Invalidate();
	m_MapDisp.m_MapLayerMan.CreateMapText(tid,x,y,text,size,color);	
}
void CMapEngine::DeleteMapText(long tid)
{
	Invalidate();
	m_MapDisp.m_MapLayerMan.DeleteMapText(tid);
}
//设置字体参数，size，字号（16）；width 字体宽度(默认0), escapement 字体显示的角度(0),orientation 字体的角度(0)
//weight 字体的磅数(默认400，黑体为700), Italic(默认0,1为斜体)，underline(0,1为下划线),strikeOut(0,1为删除线)
//fontname 字体名称(默认"宋体"，可以为"微软雅黑"，)
bool CMapEngine::SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	Invalidate();
//	m_MapDisp.m_MapLayerMan.CreateMapText(tid,x,y,text,size,color);	
	return m_MapDisp.m_MapLayerMan.SetMapTextFont( tid,size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
}
//删除所有图层
void CMapEngine::RemoveAllLayer()
{
	m_MapDisp.m_MapLayerMan.Realse();
}
//设置数据源,0为谷歌，8为virtual earth，9为超图，其他暂不支持
long CMapEngine::SetMapRes(long lres )
{
	this->m_MapDisp.SetMapType( m_strRootPath, (en_MapType)lres );
	return 0;
}
//判断是否在地图显示范围内
bool CMapEngine::IsMapPointInMapCreen(double x, double y)
{
	MapPoint mapPoint;
	mapPoint.x = x;
	mapPoint.y = y;
	return m_MapDisp.IsMapPointInMapCreen(mapPoint);
}
//注册程序
long CMapEngine::RegisterKey(char* strRegisterKey)
{
	return m_MapDisp.RegisterKey( strRegisterKey );
}
//设置地图工具，地图工具 1为方向测距 2为
bool CMapEngine::SetMapTools(long MapToolType)
{
	this->m_MapCtrl.SetMapTools( MapToolType );
	return 1;
}
//清楚地图工具以及所操作的地图
void CMapEngine::ClearMapTools()
{
	this->m_MapCtrl.ClearMapTools();
}
//是否显示地图工具栏
void CMapEngine::SetMapToolsBar( bool bShow )
{
	m_MapCtrl.SetMapToolsBar( bShow );
}
//得到地图的纠偏数据值
bool CMapEngine::GetMapOffSet( double& lon, double& lan )
{
	return m_MapOffSet.GetMapOffSetFromLoc(lon,lan);
}
void CMapEngine::SetMapScaleBound(long minscale, long maxscale)
{
	this->m_MapCtrl.SetMapScaleBound( minscale,maxscale	);
	this->m_MapDisp.SetMapScaleBound( minscale,maxscale );
}
//点是否在地图的多变型工具内
bool CMapEngine::IsInMapToolsPolygon( double dLon, double dLan )
{
	return m_MapCtrl.m_MapToolPolygon.IsInMapToolsPolygon( dLon, dLan );
	return 1;
}
//根据坐标查询地址
string CMapEngine::GetMapAddress(double dLon, double dLan)
{
	string str;
	char strUrl[512] = {0};
	//sprintf( strUrl,"http://ditu.google.cn/maps/geo?output=csv&key=abcdef&q=%f,%f",dLan,dLon );
	sprintf( strUrl,"http://api.map.baidu.com/geocoder/v2/?&address=东城区东城愉景时代广场51号&output=json&ak=97E16405fb782b4eb078fa97066c0710&city=东莞市");
	//内存
	MemoryStruct chunk;
	int errcode= curl_httpget(strUrl,&chunk,NULL);
	if(!errcode)
	{	
		char chTemp[1024];
		CVOSUtil::UTF8ToGB2312( chunk.memory,chTemp,1024 );
		str = chTemp;
	}
	if(chunk.memory)
		free(chunk.memory);
	return str;
}
//添加地图信息点
bool CMapEngine::SaveLocMapPoint( double x, double y, string strName, string strText, long icoID )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapPoint( x, y ,strName, strText, icoID ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//添加地图线,
bool CMapEngine::SaveLocMapLine( string strMapPoints, string strName, long width, long bgrcolor  )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapLine( strMapPoints, strName, width, bgrcolor ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//添加地图文本信息
bool CMapEngine::SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapText( x, y, strText, fontsize, bgrcolor ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//清除地图保存信息
bool CMapEngine::ClearLocMapData()
{
	return m_MapDisp.m_MapLayerMan.ClearLocMapData();
}
//删除一个点
bool CMapEngine::DeleteLocMapPoint(long pointID)
{
	return m_MapDisp.m_MapLayerMan.DeleteLocMapPoint( pointID );
}
//删除一个线
bool CMapEngine::DeleteLocMapLine(long lineID)
{
	return m_MapDisp.m_MapLayerMan.DeleteLocMapLine( lineID );
}
//得到当前位置的信息ID,0为无数据，1为点信息，2为线信息
int CMapEngine::GetLocID( long& lID, VOSPoint point )
{
	return m_MapDisp.m_MapLayerMan.GetLocID( lID, point );
}
//保存地图
void CMapEngine::SaveMap( const char* strPath )
{
	//保存成jpeg
	/*
	int len = bmp_info.bmiHeader.biWidth*bmp_info.bmiHeader.biHeight*4+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	char* pData = new char[len];
	BITMAPFILEHEADER* pFHead = (BITMAPFILEHEADER*)pData;
	pFHead->bfType = 0x4D42;
    pFHead->bfReserved1 = 0;
    pFHead->bfReserved2 = 0;
    pFHead->bfSize = sizeof(BITMAPFILEHEADER); 
    pFHead->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);//+bmp_info.bmiHeader.biSizeImage
	memcpy( pData+sizeof(BITMAPFILEHEADER),&bmp_info,sizeof( BITMAPINFOHEADER ) );
	//memcpy( pData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER), (char*)m_buf, bmp_info.bmiHeader.biHeight * bmp_info.bmiHeader.biWidth * 4);
	::GetDIBits( m_memhdc,m_bitmap,0,bmp_info.bmiHeader.biHeight,pData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER),&bmp_info,DIB_RGB_COLORS );
	//m_bitmap = ::CreateDIBSection( hdc, &bmp_info, DIB_RGB_COLORS, &m_buf, 0, 0 );
	CVOSImage image;
	image.LoadImage( pData,len );
	image.SaveJPEG( strPath );
	delete[] pData;
	*/

	//保存成jpeg
	CxImage* NewImg = new CxImage();
	NewImg->CreateFromHBITMAP( m_bitmap );
	if (NewImg->GetTransIndex() != 24)
    {
        NewImg->IncreaseBpp(24);
    }
	NewImg->IncreaseBpp(24);
	NewImg->SetJpegQuality(80);
	NewImg->Save( strPath,CXIMAGE_FORMAT_JPG);
	//保存成png
    /*NewImg->SetTransIndex(0);
	RGBQUAD rgbTrans = {255, 255, 255, 0};
	NewImg->SetTransColor( rgbTrans );
	NewImg->Save( strPath,CXIMAGE_FORMAT_PNG );
	*/
	delete NewImg;
}
//设置地图可编辑
long CMapEngine::OpenMapEdit(long type, long id, bool bedit)
{
	return m_MapDisp.m_MapLayerMan.OpenMapEdit( type, id, bedit);
}
//设置多边形名字
long CMapEngine::SetMapPolygonName(long pid, const char* name )
{
	return m_MapDisp.m_MapLayerMan.SetMapPolygonName( pid, name );
}
//设置多边形颜色
long CMapEngine::SetMapPolygonColor(long pid, long colorbgr)
{
	return m_MapDisp.m_MapLayerMan.SetMapPolygonColor( pid, colorbgr );
}
//设置圆名字
void CMapEngine::SetMapAroundName(long rid, const char* name )
{
	m_MapDisp.m_MapLayerMan.SetMapAroundName( rid, name );
}
long CMapEngine::SetMapAroundColor(long rid, long colorbgr)
{
	return m_MapDisp.m_MapLayerMan.SetMapAroundColor( rid, colorbgr );
}
//保存工具
void CMapEngine::SaveMapTool()
{
	;
}
long CMapEngine::SetMarkFile( const char* strFileName  )
{
	return this->m_ImageMark.LoadImage( strFileName );
	return 1;
}