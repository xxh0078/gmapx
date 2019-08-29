#include "StdAfx.h"
#include "MapEngine.h"
#include "VOSBase/VOSBase.h"
#include "MapLayer/MapLeyerMan.h"

double x1=116;
double y11=39;
int g_iTimes = 0;

//fun_msg g_fun_msg=NULL;
//unsigned char* g_Memery = NULL;//ȫ���ڴ棬������ͼͼƬ������ʱʹ��
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
	//�õ��û���Ŀ¼
//	::SHGetSpecialFolderPath(NULL,strRootPath,CSIDL_APPDATA,FALSE);
	//�õ�����ǰĿ¼//GetModuleHandle 
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
	//����DC
	if ( m_memhdc )
	{
		//delete m_memDC;
		::DeleteDC( m_memhdc );
		m_memhdc = NULL;
	}
	m_memhdc = ::CreateCompatibleDC( dc );
	::SetBkColor( m_memhdc,RGB(255,255,255) );
	//��ʼ��aggbuff
	m_MapOffSet.Init( m_strRootPath );
//	m_memDC.CreateCompatibleDC(pDC);
	//m_memDC.SetBkColor( RGB(100,100,100));
	//UI��Դ��ʼ��
	//m_uiResMan.Init( m_strRootPath, hwnd );
	//��ͼ��ʼ��
	m_MapDisp.Init( hwnd, m_memhdc, m_strRootPath, GMAP_GOOGLE_MAP);//GMAP_GOOGLE_MAP
	// ���ڳ�ʼ��
	//m_MapZoomCtrl.Init( &m_MapDisp, m_strRootPath, hwnd, 30,75 );
	
	m_MapCtrl.Create( hwnd );
	m_MapCtrl.Init( this,(char*)m_strRootPath.c_str(),hwnd, 0,0 );
	
	//m_MapWnd.Init( hwnd,& m_MapDisp,&m_uiResMan );
//	::SetTimer( m_hwnd, _MAP_TIMER_PROC, _MAP_TIMER, NULL );
	//��ʼ�����
	PostMessage( m_hwnd,WM_MAP_ONINIT, 0,0);
//	::SetTimer( m_hwnd, _MAP_TIMER_PROC1, _MAP_TIMER1, NULL );
	//E:\work\gmap\trunk\gmap\bin\gugemap\level16\7a669bbb4ea378e00b8c35257bec394d
/*	string str1 = GetMapAddress( 115,38 );
*/
//	m_MifMan.Init( &m_MapDisp.m_MapLayerMan );
//	string strtemp  = m_strRootPath;
//	strtemp += "map\\���۷־���Ͻվ��ֲ�ͼ";//�й���ͼ_����//�й���ͼ_������//�й���ͼ_ʡ����//�й���ͼ_ʡ���//�й���ͼ_��·��
//	LoadMifMidData( strtemp );
//	strtemp  = m_strRootPath;
//	strtemp += "mif\\�й���ͼ_ʡ����";//�й���ͼ_����//�й���ͼ_������//�й���ͼ_ʡ����//�й���ͼ_ʡ���//�й���ͼ_��·��
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
//���õ�ͼλ��
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
	// ����bitmap
	if ( m_bitmap )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	HDC hdc = GetDC( m_hwnd );
	// ������ϵͳ����һ��32λ��bmp����
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
	//====================AGG Start====================================== // ������AGG����  
	// BMP�����µ��õģ�Ϊ�˺�GDIϰ����ͬ�����һ�������Ǹ�ֵ��
	m_rbuf.attach((unsigned char*)m_buf, width, height, -width*4);

	m_MapCtrl.SetMapRect( m_rect );
}

//������Ϣ�ص�����
void CMapEngine::SetMsgFun( fun_msg msg )
{
	g_fun_msg = msg;
	ShowMapTool(1,0);
}
//���õ�ͼURL·��
void CMapEngine::SetMapUrl(string strMapURL )
{
	SetMapType( GMAP_MYMAP );
	CMapBase::SetMapUrl( strMapURL );
}
//���ñ��ص�ͼ�ļ�·��
void CMapEngine::SetMapPath( string strMapPath )
{
	m_MapDisp.SetMapPath( strMapPath ); 
}
//���ø���ͼ��·��
void CMapEngine::OpenAddMapLayerPath( string strMapFilesPath )
{
	m_MapDisp.OpenAddMapLayerPath( strMapFilesPath );
}
//�رո��Ӳ�
void CMapEngine::CloseAddMapLayer( )
{
	m_MapDisp.CloseAddMapLayer();
}
//UnInit�ͷ��ڴ�
void CMapEngine::Destroy()
{
	//��ͼ��ʾ�ͷ�
	this->m_MapDisp.realse();
	if ( m_bitmap )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
	//����DC
	if ( m_memhdc )
	{
		//delete m_memDC;
		::DeleteDC( m_memhdc );
		m_memhdc = NULL;
	}
	KillTimer( m_hwnd,_MAP_TIMER_PROC);
}
//���õ�ͼ��ʾ
long CMapEngine::ShowMapTool(long lType, long lValue)
{
	if( lType == 1 )
		this->m_MapCtrl.SetMapToolsBar( lValue );

	return 1;
}
//���õ�ͼ���� 
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
	// ���ظ�ʽ��renderer_base http://www.cppprog.com C++�����
	agg::pixfmt_bgra32 pixf(m_rbuf); 
	agg::renderer_base<agg::pixfmt_bgra32> renb(pixf); 
	renb.clear(agg::rgba8(255, 255, 255, 255)); 
	
	// Scanline renderer 
	agg::renderer_scanline_aa_solid<agg::renderer_base<agg::pixfmt_bgra32> > ren(renb);

	// Rasterizer & scanline
	agg::rasterizer_scanline_aa<> ras;
	agg::scanline_p8 sl;

	// �����ߣ������Σ� 
	ras.move_to_d(20.7, 34.15); 
	ras.line_to_d(398.23, 123.43);
	ras.line_to_d(165.45, 401.87); 

	// ������ɫ����Ⱦ 
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
	//sprintf(chTemp,"%d��",g_iTimes);
	//::DrawText( hdc, chTemp,strlen(chTemp) ,&m_rect,DT_LEFT | DT_TOP);
//	m_MapWnd.OnDraw( hdc );
}
//�����Ϣ
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
//�����Ƿ��ڵ�ͼ��
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
//�ƶ���ͼ��
void CMapEngine::MoveMap( double dMapX, double dMapY )
{
	MapPoint mpt;
	mpt.x = dMapX;
	mpt.y = dMapY;
	m_MapDisp.MoveMap( mpt );
	Invalidate();
}
//�ƶ���ͼ
void CMapEngine::MoveMapBound(double x1, double y1, double x2, double y2)
{
	m_MapDisp.MoveMapBound(x1,y1,x2,y2);
}
/*	���ڵ���Ϣ���� */
void CMapEngine::MsgProc( ULONG ulID, ULONG wParam, ULONG lParam )
{
	switch( ulID )
	{
	case WM_MOUSEMOVE:
		{
			//#define VOS_LOWORD(l)		((VOSWord)(l))	// �õ�����
			//#define VOS_HIWORD(l)       ((VOSWord)(((VOSDWord)(l) >> 16) & 0xFFFF))	// ���ֵ���
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
			//this->SetMapPath("E:\\work\\gmap\\trunk\\gmap\\bin\\��Ƭ����\\���ǵ�ͼ\\level%z\\%y\\%x.png");
			//��ʼ�������Ϣ
			break;
		}
	case VOS_WM_COMMAND:
		m_MapCtrl.OnCommand( wParam,lParam,0);
		break;
	default:
		;
	}
}
//��ͼ����ת��Ϊ��Ļ����
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
//��ͼ����ת��Ϊ��Ļ����
// void CMapEngine::MapToScreen( MapPoint mpt, VOSPoint& pt )
// {
// 	m_MapDisp.MapToScreen( mpt, pt );
// }
// //��Ļ����ת��Ϊ��ͼ����
// void CMapEngine::ScreenToMap( VOSPoint pt, MapPoint& mpt )
// {
// 	m_MapDisp.ScreenToMap( pt, mpt );
// }
	//�õ���ͼ���ĵ�����
void CMapEngine::GetMapCenter( double& dMapX, double& dMapY )
{
	MapPoint mpt;
	m_MapDisp.GetMapCenter( mpt );
	dMapX = mpt.x;
	dMapY = mpt.y;
}
//���ͼ��
long CMapEngine::CreateMapLeyer()
{
	CMapLayer* pMapLayer = new CMapLayer();
	return m_MapDisp.m_MapLayerMan.AddMapLayer( pMapLayer );
}
//ɾ��ͼ��
bool CMapEngine::DeleteMapLayer( int nID )
{
	return m_MapDisp.m_MapLayerMan.DeleteMapLayer( nID );
}
//ɾ��ͼ��
// void CMapEngine::DeleteMapLayers( CMapLayer* pMapLayer )
// {
// 	DeleteMapLayers( pMapLayer );
// }
//ɾ��ȫ��ͼ��
void CMapEngine::DeleteAllMapLayer()
{
	m_MapDisp.m_MapLayerMan.ClearAllMapLayer();
}
//���POI��
long CMapEngine::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, long icoID )
{
	return m_MapDisp.m_MapLayerMan.AddMapLayerPoint( nLayerID, lMapX, lMapY, strName, icoID );
}
//���POI��
long CMapEngine::AddMapLayerPoint( int nLayerID, double lMapX, double lMapY, string strName, string strFileName )
{
	return m_MapDisp.m_MapLayerMan.AddMapLayerPoint( nLayerID, lMapX, lMapY, strName, strFileName );
}
//ˢ����Ļ
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
//������Դ������Ǳ��صģ���ֱ�Ӽ��أ�����Ƿ������ģ���Ϊurl��url��http��ͷ
long CMapEngine::CreateMapRes( string strpath )
{
	return m_MapDisp.m_MapLayerMan.CreateRes( strpath );
}
//����mif����
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
//��������ζ���
bool CMapEngine::CreateMapPolygon(long polygonID )
{
	Invalidate();
	return m_MapDisp.m_MapLayerMan.CreatMapPolygon( polygonID );
}
//��ӵ�
bool CMapEngine::AddMapPolygonPoint( long polygonID, double x, double y )
{
		return m_MapDisp.m_MapLayerMan.AddMapPolygonPoint( polygonID, x, y );
}
//ɾ������ζ���
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
//���ư�Բ
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
//��������
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
//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
bool CMapEngine::SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	Invalidate();
//	m_MapDisp.m_MapLayerMan.CreateMapText(tid,x,y,text,size,color);	
	return m_MapDisp.m_MapLayerMan.SetMapTextFont( tid,size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
}
//ɾ������ͼ��
void CMapEngine::RemoveAllLayer()
{
	m_MapDisp.m_MapLayerMan.Realse();
}
//��������Դ,0Ϊ�ȸ裬8Ϊvirtual earth��9Ϊ��ͼ�������ݲ�֧��
long CMapEngine::SetMapRes(long lres )
{
	this->m_MapDisp.SetMapType( m_strRootPath, (en_MapType)lres );
	return 0;
}
//�ж��Ƿ��ڵ�ͼ��ʾ��Χ��
bool CMapEngine::IsMapPointInMapCreen(double x, double y)
{
	MapPoint mapPoint;
	mapPoint.x = x;
	mapPoint.y = y;
	return m_MapDisp.IsMapPointInMapCreen(mapPoint);
}
//ע�����
long CMapEngine::RegisterKey(char* strRegisterKey)
{
	return m_MapDisp.RegisterKey( strRegisterKey );
}
//���õ�ͼ���ߣ���ͼ���� 1Ϊ������ 2Ϊ
bool CMapEngine::SetMapTools(long MapToolType)
{
	this->m_MapCtrl.SetMapTools( MapToolType );
	return 1;
}
//�����ͼ�����Լ��������ĵ�ͼ
void CMapEngine::ClearMapTools()
{
	this->m_MapCtrl.ClearMapTools();
}
//�Ƿ���ʾ��ͼ������
void CMapEngine::SetMapToolsBar( bool bShow )
{
	m_MapCtrl.SetMapToolsBar( bShow );
}
//�õ���ͼ�ľ�ƫ����ֵ
bool CMapEngine::GetMapOffSet( double& lon, double& lan )
{
	return m_MapOffSet.GetMapOffSetFromLoc(lon,lan);
}
void CMapEngine::SetMapScaleBound(long minscale, long maxscale)
{
	this->m_MapCtrl.SetMapScaleBound( minscale,maxscale	);
	this->m_MapDisp.SetMapScaleBound( minscale,maxscale );
}
//���Ƿ��ڵ�ͼ�Ķ���͹�����
bool CMapEngine::IsInMapToolsPolygon( double dLon, double dLan )
{
	return m_MapCtrl.m_MapToolPolygon.IsInMapToolsPolygon( dLon, dLan );
	return 1;
}
//���������ѯ��ַ
string CMapEngine::GetMapAddress(double dLon, double dLan)
{
	string str;
	char strUrl[512] = {0};
	//sprintf( strUrl,"http://ditu.google.cn/maps/geo?output=csv&key=abcdef&q=%f,%f",dLan,dLon );
	sprintf( strUrl,"http://api.map.baidu.com/geocoder/v2/?&address=�����������侰ʱ���㳡51��&output=json&ak=97E16405fb782b4eb078fa97066c0710&city=��ݸ��");
	//�ڴ�
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
//��ӵ�ͼ��Ϣ��
bool CMapEngine::SaveLocMapPoint( double x, double y, string strName, string strText, long icoID )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapPoint( x, y ,strName, strText, icoID ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//��ӵ�ͼ��,
bool CMapEngine::SaveLocMapLine( string strMapPoints, string strName, long width, long bgrcolor  )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapLine( strMapPoints, strName, width, bgrcolor ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//��ӵ�ͼ�ı���Ϣ
bool CMapEngine::SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor )
{
	if( m_MapDisp.m_MapLayerMan.SaveLocMapText( x, y, strText, fontsize, bgrcolor ) )
	{
		this->Invalidate();
		return true;
	}
	return false;
}
//�����ͼ������Ϣ
bool CMapEngine::ClearLocMapData()
{
	return m_MapDisp.m_MapLayerMan.ClearLocMapData();
}
//ɾ��һ����
bool CMapEngine::DeleteLocMapPoint(long pointID)
{
	return m_MapDisp.m_MapLayerMan.DeleteLocMapPoint( pointID );
}
//ɾ��һ����
bool CMapEngine::DeleteLocMapLine(long lineID)
{
	return m_MapDisp.m_MapLayerMan.DeleteLocMapLine( lineID );
}
//�õ���ǰλ�õ���ϢID,0Ϊ�����ݣ�1Ϊ����Ϣ��2Ϊ����Ϣ
int CMapEngine::GetLocID( long& lID, VOSPoint point )
{
	return m_MapDisp.m_MapLayerMan.GetLocID( lID, point );
}
//�����ͼ
void CMapEngine::SaveMap( const char* strPath )
{
	//�����jpeg
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

	//�����jpeg
	CxImage* NewImg = new CxImage();
	NewImg->CreateFromHBITMAP( m_bitmap );
	if (NewImg->GetTransIndex() != 24)
    {
        NewImg->IncreaseBpp(24);
    }
	NewImg->IncreaseBpp(24);
	NewImg->SetJpegQuality(80);
	NewImg->Save( strPath,CXIMAGE_FORMAT_JPG);
	//�����png
    /*NewImg->SetTransIndex(0);
	RGBQUAD rgbTrans = {255, 255, 255, 0};
	NewImg->SetTransColor( rgbTrans );
	NewImg->Save( strPath,CXIMAGE_FORMAT_PNG );
	*/
	delete NewImg;
}
//���õ�ͼ�ɱ༭
long CMapEngine::OpenMapEdit(long type, long id, bool bedit)
{
	return m_MapDisp.m_MapLayerMan.OpenMapEdit( type, id, bedit);
}
//���ö��������
long CMapEngine::SetMapPolygonName(long pid, const char* name )
{
	return m_MapDisp.m_MapLayerMan.SetMapPolygonName( pid, name );
}
//���ö������ɫ
long CMapEngine::SetMapPolygonColor(long pid, long colorbgr)
{
	return m_MapDisp.m_MapLayerMan.SetMapPolygonColor( pid, colorbgr );
}
//����Բ����
void CMapEngine::SetMapAroundName(long rid, const char* name )
{
	m_MapDisp.m_MapLayerMan.SetMapAroundName( rid, name );
}
long CMapEngine::SetMapAroundColor(long rid, long colorbgr)
{
	return m_MapDisp.m_MapLayerMan.SetMapAroundColor( rid, colorbgr );
}
//���湤��
void CMapEngine::SaveMapTool()
{
	;
}
long CMapEngine::SetMarkFile( const char* strFileName  )
{
	return this->m_ImageMark.LoadImage( strFileName );
	return 1;
}