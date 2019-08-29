// EasyMapView.cpp : implementation of the CEasyMapView class
//

#include "stdafx.h"
#include "EasyMap.h"

#include "EasyMapDoc.h"
#include "EasyMapView.h"
#include "MapCommand.h"
#include "MapFields.h"
#include "MainFrm.h"
#include "Global.h"

#include "DlgPtSymbolSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView

IMPLEMENT_DYNCREATE(CEasyMapView, CView)

BEGIN_MESSAGE_MAP(CEasyMapView, CView)
	//{{AFX_MSG_MAP(CEasyMapView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MAP_NOTHING, OnMapNothing)
	ON_COMMAND(ID_MAP_ZOOM_IN, OnMapZoomIn)
	ON_COMMAND(ID_MAP_ZOOM_OUT, OnMapZoomOut)
	ON_COMMAND(ID_MAP_ZOOM_ALL, OnMapZoomAll)
	ON_COMMAND(ID_MAP_ZOOM_WINDOW, OnMapZoomWindow)
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_MAP_PTSYMBOL, OnMapPtsymbol)
	ON_WM_CREATE()
	ON_COMMAND(ID_MAP_SRHPT, OnMapSrhpt)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView construction/destruction

CEasyMapView::CEasyMapView()
{
	// TODO: add construction code here
	Initialize();

}

CEasyMapView::~CEasyMapView()
{
}

BOOL CEasyMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.lpszClass = ::AfxRegisterWndClass(0,0,(HBRUSH)::GetStockObject(BLACK_BRUSH),0);  
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView drawing

void CEasyMapView::OnDraw(CDC* pDC)
{
	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapLayer *pLayer;
	CRect rc;
	CBitmap bmp; 
	CDC dcMemory;
	
	BeginWaitCursor(); 
	GetClientRect(rc); 
	dcMemory.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());   
	dcMemory.SelectObject(&bmp); 
	short iCount = pDoc->m_MapLayers.GetCount(); 
	for ( short i = 0 ; i < iCount ; i++ )
	{ 
		pLayer = pDoc->m_MapLayers.GetAt(i);
		pLayer->DrawLayer(&dcMemory , m_DrawParam ); 
		
	} 
	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&dcMemory,0,0,SRCCOPY); 
	dcMemory.DeleteDC(); 
	bmp.DeleteObject(); 
	pDC->SetMapMode(MM_TEXT);          //设置映射模式
	EndWaitCursor(); 

	
    
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView printing

BOOL CEasyMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEasyMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEasyMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView diagnostics

#ifdef _DEBUG
void CEasyMapView::AssertValid() const
{
	CView::AssertValid();
}

void CEasyMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEasyMapDoc* CEasyMapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEasyMapDoc)));
	return (CEasyMapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyMapView message handlers

void CEasyMapView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


	
	CRect rc;
	GetClientRect(&rc); 
	
	if ( m_Operation == CMD_ZOOMIN_WINDOW && rc.PtInRect(point))
    {    
		
		m_StartPt = point;
		m_SecondPt = point;
		m_isDownMouse = 1;
		//保证鼠标移动到窗体外也可以接收到鼠标释放时件
		SetCapture(); 
		Dispatch( point);
		
    } 

    if ( m_Operation == CMD_ZOOMIN && rc.PtInRect(point))
    {
		 //点击放大
		m_StartPt = point;
		m_SecondPt = point;
		ZoomIn();
		

    }  
	if (m_Operation == CMD_ZOOMOUT && rc.PtInRect(point))
    {
		m_StartPt = point;
		m_SecondPt = point;
		m_isDownMouse = 1;
		ZoomOut(); 
			
    } 
	
	if (m_Operation == CMD_ZOOMPAN  && rc.PtInRect(point))
    {
		m_StartPt = point;
		m_SecondPt = point;
		m_isDownMouse = 1;
		//保证鼠标移动到窗体外也可以接收到鼠标释放时件
		SetCapture(); 
		
    }   
	if (m_Operation == CMD_SRHPT  && rc.PtInRect(point))
    {
		PtSelected(point);

    } 
	CView::OnLButtonDown(nFlags, point);
}

void CEasyMapView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_Operation == CMD_ZOOMIN_WINDOW )
    {   
	    if ( m_isDownMouse == 1 ) //一次有效的拖动
        {  
			m_isDownMouse = 2;
			m_SecondPt = point;
			ReleaseCapture();
			Dispatch(point);
			if ( m_StartPt.x != m_SecondPt.x || m_StartPt.y != m_SecondPt.y ) 
				ZoomInWindows();
        }
        m_isDownMouse = 0; 
	
		
    } 
	else if ( m_Operation == CMD_ZOOMOUT )
    {
	    if ( m_isDownMouse == 1 ) //一次有效的拖动
        {  
			m_isDownMouse = 2;
			ReleaseCapture();
			Dispatch(point);
        }
        m_isDownMouse = 0; 
		
	}
	else if ( m_Operation == CMD_ZOOMPAN )
    {
		if ( m_StartPt.x != point.x || m_StartPt.y == point.y )
		{
			m_SecondPt = point;
			Pan();
		}
		m_isDownMouse = 0;
		ReleaseCapture();
	}	
	CView::OnLButtonUp(nFlags, point);
}

void CEasyMapView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
   	double dblX,dblY; 
	CMapPoint pt;
	CPoint    pScreen;
	CString   csStr;
	CRect     RC;
    
	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	dblX = m_DrawParam.m_StartX + point.x*m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - point.y*m_DrawParam.m_Scale;
	pt.SetX(dblX);
	pt.SetY(dblY); 
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	
	if ( m_Operation == CMD_ZOOMIN_WINDOW  )
    {  
	
		::SetCursor(pFrame->m_hcurZInWindow);
		if ( m_isDownMouse == 1 )	   
			Dispatch( point);
		
	    
    }
	else if ( m_Operation == CMD_ZOOMOUT )
    {    
	
		::SetCursor(pFrame->m_hcurZOut);
		
	
	}
	else if ( m_Operation == CMD_ZOOMPAN )
    {
		
		::SetCursor(pFrame->m_hcurPan);
		if ( m_isDownMouse == 1 )
		{
			if ( point.x != m_StartPt.x || point.y != m_StartPt.y )
			{
				m_SecondPt = point;
				Pan();
				m_StartPt = m_SecondPt; 

			}
        }  

    } 
	else if ( m_Operation == CMD_ZOOMIN ) 
    {
		
		::SetCursor(pFrame->m_hcurZIn);
	} else if ( m_Operation == CMD_SRHPT )
    {
		::SetCursor(pFrame->m_hcurFind);
    } 
	else
    {
		::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	}

	if (pFrame->m_bMapTip ) //鼠标动态提示
	{	 
		m_MapTip.InitMapTip(&(pDoc->m_MapLayers)); 
		pScreen = point;
		ClientToScreen(&pScreen);
		m_MapTip.MoveTo( pt,pScreen);
		 
    } 

	
	if (pDoc->m_MapLayers.GetCount() > 0 )
		ShowCoordinate(pt); 
		
	CView::OnMouseMove(nFlags, point);
}

void CEasyMapView::OnMapNothing() 
{
	m_Operation = 0;
	::SetCursor(::LoadCursor(NULL,IDC_NO)); 
	
}

void CEasyMapView::OnMapZoomIn() 
{
	m_Operation =  CMD_ZOOMIN;       

	
}

void CEasyMapView::OnMapZoomOut() 
{
	m_Operation = CMD_ZOOMOUT;
	
}

void CEasyMapView::OnMapZoomAll() 
{
	float fxScale,fyScale;
	double dbTmp;
	CRect rc;
	CMapRectangle mapExtent;

	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//获得当前地图最大矩形范围
	pDoc->m_MapLayers.GetAllExtent(mapExtent);  
	//获得视图客户区矩形范围
	GetClientRect(&rc);
	m_DrawParam.m_ScreenWidth = abs(rc.right - rc.left);
    m_DrawParam.m_ScreenHeigh = abs(rc.bottom  - rc.top); 
    //计算横向比例系数

	fxScale = (float)(fabs(mapExtent.GetRight()-mapExtent.GetLeft())/
		              m_DrawParam.m_ScreenWidth);
	//计算纵向比例系数
	fyScale = (float)(fabs(mapExtent.GetBottom() -mapExtent.GetTop() )/
		              m_DrawParam.m_ScreenHeigh);
	//选择较大的做比例尺
	if ( fxScale > fyScale)
    {  
       m_DrawParam.m_Scale =  fxScale;
	   m_DrawParam.m_StartX = mapExtent.GetLeft();
       dbTmp = fabs(mapExtent.GetBottom() -mapExtent.GetTop());
	   dbTmp =fxScale*m_DrawParam.m_ScreenHeigh - dbTmp;  
       m_DrawParam.m_StartY = mapExtent.GetBottom() -  dbTmp / 2; 
    } 
	else
    {   
	   m_DrawParam.m_Scale =  fyScale;
	   m_DrawParam.m_StartY =  mapExtent.GetBottom(); 
       dbTmp = fabs(mapExtent.GetRight() -mapExtent.GetLeft()); 
	   dbTmp = fyScale*m_DrawParam.m_ScreenWidth - dbTmp;  
       m_DrawParam.m_StartX =  mapExtent.GetLeft() - dbTmp / 2; 
    } 
	pDoc->UpdateAllViews(NULL); 
}

void CEasyMapView::OnMapZoomWindow() 
{
	m_Operation = CMD_ZOOMIN_WINDOW;
	
}

void CEasyMapView::OnMapPan() 
{
	m_Operation = CMD_ZOOMPAN;	
 	
}

void CEasyMapView::Initialize()
{
	m_Operation = CMD_NOTHING;              
	m_isDownMouse = 0;             
	m_StartPt.x = 0 ;
	m_StartPt.y = 0 ;
	m_SecondPt.x = 0;
    m_SecondPt.y = 0; 

}


void CEasyMapView::Dispatch(CPoint curPt)
{
	
	
	int oldDrawMode;
	switch( m_Operation )
    {
		case CMD_ZOOMIN_WINDOW:
			{
				CPen penDrag( PS_DOT , 1 , RGB(0,0,0) );
				CDC *pDC = GetDC();
				CPen* pOldPen = (CPen*)pDC->SelectObject( &penDrag );
				oldDrawMode = pDC->SetROP2(R2_XORPEN); //设置绘制模式
				
			    if ( m_isDownMouse == 1 )
				{
						pDC->MoveTo(m_StartPt);
						pDC->LineTo(m_StartPt.x , m_SecondPt.y);
						pDC->LineTo(m_SecondPt.x , m_SecondPt.y);
                        pDC->LineTo(m_SecondPt.x , m_StartPt.y);
						pDC->LineTo(m_StartPt.x , m_StartPt.y);
						pDC->MoveTo(m_StartPt);
						pDC->LineTo(m_StartPt.x,curPt.y);
						pDC->LineTo(curPt.x,curPt.y);
						pDC->LineTo(curPt.x,m_StartPt.y);
						pDC->LineTo(m_StartPt.x , m_StartPt.y);
						
						
				}
				if ( m_isDownMouse == 2 )
				{
						pDC->MoveTo(m_StartPt);
						pDC->LineTo(m_StartPt.x , m_SecondPt.y);
						pDC->LineTo(m_SecondPt.x , m_SecondPt.y);
                        pDC->LineTo(m_SecondPt.x , m_StartPt.y);
						pDC->LineTo(m_StartPt.x , m_StartPt.y);
								
                } 
				m_SecondPt = curPt;
				pDC->SelectObject( pOldPen ); 
				pDC->SetROP2(oldDrawMode);
				

            }
            break;   
		default:
			break;
	}   

}

BOOL CEasyMapView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	/*CRect rc;
	CBrush br(RGB(0,0,0));
    CBrush *pOldbr = pDC->SelectObject(&br);
	pDC->GetClipBox(&rc);
	pDC->PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY);
	pDC->SelectObject(pOldbr); 
	return TRUE;*/
	return CView::OnEraseBkgnd(pDC); 
}

void CEasyMapView::OnInitialUpdate() 
{
	CRect rc;
	CView::OnInitialUpdate();
	GetClientRect(&rc); 
	m_DrawParam.m_Scale = 1;
	m_DrawParam.m_StartX = 10;
    m_DrawParam.m_StartY = 10;
    m_DrawParam.m_ScreenWidth = abs(rc.right  - rc.left);
	m_DrawParam.m_ScreenHeigh = abs(rc.bottom - rc.top );
	
	m_FixedScale = 2;
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CEasyMapView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	float fxScale,fyScale;
	double dbTmp;
	CRect rc;
	CMapRectangle mapExtent;

	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//获得当前地图最大矩形范围
	pDoc->m_MapLayers.GetAllExtent(mapExtent);  
	//获得视图客户区矩形范围
	GetClientRect(&rc);
	m_DrawParam.m_ScreenWidth = abs(rc.right - rc.left);
    m_DrawParam.m_ScreenHeigh = abs(rc.bottom  - rc.top); 
    //计算横向比例系数

	fxScale = (float)(fabs(mapExtent.GetRight()-mapExtent.GetLeft())/
		              m_DrawParam.m_ScreenWidth);
	//计算纵向比例系数
	fyScale = (float)(fabs(mapExtent.GetBottom() -mapExtent.GetTop() )/
		              m_DrawParam.m_ScreenHeigh);
	//选择较大的做比例尺
	if ( fxScale > fyScale)
    {  
        m_DrawParam.m_Scale =  fxScale;
	    m_DrawParam.m_StartX = mapExtent.GetLeft();
        dbTmp = fabs(mapExtent.GetBottom() -mapExtent.GetTop());
	    dbTmp =fxScale*m_DrawParam.m_ScreenHeigh - dbTmp;  
        m_DrawParam.m_StartY = mapExtent.GetBottom() -  dbTmp / 2; 
    } 
	else
    {   
	   m_DrawParam.m_Scale =  fyScale;
	   m_DrawParam.m_StartY =  mapExtent.GetBottom(); 
       dbTmp = fabs(mapExtent.GetRight() -mapExtent.GetLeft()); 
	   dbTmp = fyScale*m_DrawParam.m_ScreenWidth - dbTmp;  
       m_DrawParam.m_StartX =  mapExtent.GetLeft() - dbTmp / 2; 
    } 
	Invalidate(TRUE); 
}
//显示坐标
void CEasyMapView::ShowCoordinate( CMapPoint& pt)
{

	int iDU,iFEN,iMIAO; 
	double dblX,dblY;
	char szPrompt[100];
	CMapRectangle mapExtent;
	CMainFrame *pframe;

	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//获得当前地图最大矩形范围
    pDoc->m_MapLayers.GetAllExtent(mapExtent); 

	
	//在地图范围内
	if ( mapExtent.IsPointIn(pt) )
    { 		
		pframe =(CMainFrame*)AfxGetMainWnd();
		if ( pframe == NULL )
			return;
		memset(szPrompt , 0 , 100 );
		dblX = pt.GetX(); 
		iDU   = (int)dblX;
	    dblX  = (dblX-iDU)*60;
	    iFEN  = (int)dblX;
	    dblX  = (dblX-iFEN)*60;
	    iMIAO = (int)dblX;
	    sprintf(szPrompt,"东经:%d度%d分%d秒",iDU,iFEN,iMIAO);  
	    pframe->m_wndStatusBar.SetPaneText(1,szPrompt,true);        
	
	    memset(szPrompt , 0 , 100 );
		dblY = pt.GetY(); 
		iDU   = (int)dblY;
	    dblY  = (dblY - iDU)*60;
	    iFEN  = (int)dblY;
	    dblY  = (dblY-iFEN)*60;
	    iMIAO = (int)dblY;
	    sprintf(szPrompt,"北纬:%d度%d分%d秒",iDU,iFEN,iMIAO);
	    pframe->m_wndStatusBar.SetPaneText(2,szPrompt,true);  
    }   
}
void CEasyMapView::ZoomInWindows()
{
	double dblX,dblY,dblXScale,dblYScale;
    CMapPoint ptFirst,ptSecond;

	dblX = m_DrawParam.m_StartX + m_StartPt.x*m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - m_StartPt.y*m_DrawParam.m_Scale;
    ptFirst.SetX(dblX);
    ptFirst.SetY(dblY);
	dblX = m_DrawParam.m_StartX + m_SecondPt.x  *m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - m_SecondPt.y*m_DrawParam.m_Scale;
    ptSecond.SetX(dblX);
    ptSecond.SetY(dblY);
	dblXScale = fabs(ptSecond.GetX() - ptFirst.GetX())/m_DrawParam.m_ScreenWidth;
	dblYScale = fabs(ptSecond.GetY() - ptFirst.GetY())/m_DrawParam.m_ScreenHeigh;
    if ( dblXScale < dblYScale )
		m_DrawParam.m_Scale = (float)dblXScale;
	else
       m_DrawParam.m_Scale = (float)dblYScale;   
 
    m_DrawParam.m_StartX = min( ptFirst.GetX(),ptSecond.GetX());
    m_DrawParam.m_StartY = max( ptFirst.GetY(),ptSecond.GetY());
	Invalidate(TRUE); 
}
void CEasyMapView::ZoomIn()
{
	double dblX,dblY;
	CMapPoint pt,ptCenter;
	

	//移动鼠标点击点到屏幕中心
	dblX = (m_StartPt.x - m_DrawParam.m_ScreenWidth /2)*m_DrawParam.m_Scale; 	
	dblY = (m_StartPt.y - m_DrawParam.m_ScreenHeigh/2) *m_DrawParam.m_Scale;
    m_DrawParam.m_StartX += dblX;
	m_DrawParam.m_StartY -= dblY;
  
	//计算放大窗口屏幕坐标
	m_StartPt.x = m_DrawParam.m_ScreenWidth/2 - m_DrawParam.m_ScreenWidth /(2*m_FixedScale);
    m_StartPt.y = m_DrawParam.m_ScreenHeigh/2 - m_DrawParam.m_ScreenHeigh/(2*m_FixedScale);
   	m_SecondPt.x = m_DrawParam.m_ScreenWidth/2 + m_DrawParam.m_ScreenWidth /(2*m_FixedScale);
    m_SecondPt.y = m_DrawParam.m_ScreenHeigh/2 + m_DrawParam.m_ScreenHeigh/(2*m_FixedScale);
 	ZoomInWindows(); 	
	
}
void CEasyMapView::ZoomOut()
{

	double dblX,dblY,dblXScale,dblYScale;
	CMapPoint pt,ptCenter;
	CMapPoint ptFirst,ptSecond;

	CMapRectangle mapExtent;

	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//获得当前地图最大矩形范围
	pDoc->m_MapLayers.GetAllExtent(mapExtent);
	dblXScale = m_DrawParam.m_Scale + (mapExtent.GetWidth()/m_FixedScale)/m_DrawParam.m_ScreenWidth;
    dblYScale = m_DrawParam.m_Scale + (mapExtent.GetHeigh()/m_FixedScale)/m_DrawParam.m_ScreenHeigh; 
	if ( dblXScale < dblYScale )
    {  
		m_DrawParam.m_StartX -=(dblXScale - m_DrawParam.m_Scale)*m_DrawParam.m_ScreenWidth/2;
        m_DrawParam.m_StartY += (dblXScale - m_DrawParam.m_Scale)*m_DrawParam.m_ScreenHeigh/2;
		m_DrawParam.m_Scale = (float)dblXScale;
	}
	else
    {  
       	m_DrawParam.m_StartX -=(dblYScale - m_DrawParam.m_Scale)*m_DrawParam.m_ScreenWidth/2;
        m_DrawParam.m_StartY += (dblYScale - m_DrawParam.m_Scale)*m_DrawParam.m_ScreenHeigh/2;
		m_DrawParam.m_Scale = (float)dblYScale;
     
	}	

  
    //移动鼠标点击点到屏幕中心  
	dblX = (m_StartPt.x - m_DrawParam.m_ScreenWidth /2)*m_DrawParam.m_Scale; 	
	dblY = (m_StartPt.y - m_DrawParam.m_ScreenHeigh/2) *m_DrawParam.m_Scale;
    m_DrawParam.m_StartX += dblX;
	m_DrawParam.m_StartY -= dblY;
	Invalidate(TRUE);
	

	Invalidate(TRUE);

}
void CEasyMapView::Pan()
{
	double dblX,dblY;
    CMapPoint ptFirst,ptSecond;
	CRect rc;

	dblX = m_DrawParam.m_StartX + m_StartPt.x*m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - m_StartPt.y*m_DrawParam.m_Scale;
    ptFirst.SetX(dblX);
    ptFirst.SetY(dblY);
	dblX = m_DrawParam.m_StartX + m_SecondPt.x  *m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - m_SecondPt.y*m_DrawParam.m_Scale;
    ptSecond.SetX(dblX);
    ptSecond.SetY(dblY);
	m_DrawParam.m_StartX  -= ptSecond.GetX() -  ptFirst.GetX(); 
	m_DrawParam.m_StartY  -= ptSecond.GetY() -  ptFirst.GetY();
	rc.left = (long)min(ptSecond.GetX(),ptFirst.GetX());
	rc.right = (long)max(ptSecond.GetX(),ptFirst.GetX());
    rc.top = (long)min(ptSecond.GetY(),ptFirst.GetY());
	rc.bottom = (long)max(ptSecond.GetY(),ptFirst.GetY());
	Invalidate(FALSE); 
	  

}


void CEasyMapView::OnMapPtsymbol() 
{
	CDlgPtSymbolSet dlgSet;
	char szValue[256];
    char szFile[256];

    GetAppPath(szFile);
	strcat(szFile , "\\System.ini");
	::GetPrivateProfileString("SYMBOL","INDEX","35",szValue,255,szFile);
	dlgSet.uiIndex = (unsigned short)atoi(szValue);
	if ( dlgSet.DoModal() == IDOK )
	{
		sprintf(szValue,"%d",dlgSet.uiIndex);
		::WritePrivateProfileString("SYMBOL","POINTINDEX", szValue , szValue);
    }  
	
}

void CEasyMapView::GetAppPath( char *szPath ) 
{ 
	 // 函数功能：获得应用程序路径
     int i,len;
     char szVal[256];  
    
	 ::GetModuleFileName(NULL,szVal,255);    
     len = strlen(szVal)-1;
     for ( i = len ; i > 0 ; i-- )
        if (szVal[i] == '\\' )
	        break;
     szVal[i] = '\0'; 
     len = strlen(szVal);
     szVal[len] = '\0';
	 strcpy(szPath,szVal);
};

int CEasyMapView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CPoint point(100,100);
	m_MapTip.Create(this->GetParent() ,point); //创建鼠标提示窗口
	m_MapTip.ShowWindow(SW_HIDE);//隐藏鼠标提示窗口	
	
	return 0;
}


BOOL CEasyMapView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//m_MapTip.RelayEvent(pMsg);  
	return CView::PreTranslateMessage(pMsg);
}

void CEasyMapView::OnMapSrhpt() 
{
     m_Operation = CMD_SRHPT;	
}

void CEasyMapView::PtSelected(CPoint& pt)
{

	short i;
	int iIndex;
	double dblX,dblY;
	CMapPoint MapPt;
	CMapLayer *pLayer;
	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC = GetDC(); 
	dblX = m_DrawParam.m_StartX + pt.x*m_DrawParam.m_Scale;  	
	dblY = m_DrawParam.m_StartY - pt.y*m_DrawParam.m_Scale;
	MapPt.SetX(dblX);
	MapPt.SetY(dblY); 
	
	for ( i = 0 ; i < pDoc->m_MapLayers.GetCount() ; i++ )
	{
		pLayer = (CMapLayer*)pDoc->m_MapLayers.GetAt(i);
		iIndex = pLayer->SearchShape(MapPt);
		if ( iIndex > 0 )
        {  
			pLayer->FlashShp(pDC,m_DrawParam,iIndex);
			break;
		} 
    }  
 
}

void CEasyMapView::InitScale()
{

	float fxScale,fyScale;
	double dbTmp;
	CRect rc;
	CMapRectangle mapExtent;

	CEasyMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//获得当前地图最大矩形范围
	pDoc->m_MapLayers.GetAllExtent(mapExtent);  
	//获得视图客户区矩形范围
	GetClientRect(&rc);
	m_DrawParam.m_ScreenWidth = abs(rc.right - rc.left);
    m_DrawParam.m_ScreenHeigh = abs(rc.bottom  - rc.top); 
    //计算横向比例系数

	fxScale = (float)(fabs(mapExtent.GetRight()-mapExtent.GetLeft())/
		              m_DrawParam.m_ScreenWidth);
	//计算纵向比例系数
	fyScale = (float)(fabs(mapExtent.GetBottom() -mapExtent.GetTop() )/
		              m_DrawParam.m_ScreenHeigh);
	//选择较大的做比例尺
	if ( fxScale > fyScale)
    {  
       m_DrawParam.m_Scale =  fxScale;
	   m_DrawParam.m_StartX = mapExtent.GetLeft();
       dbTmp = fabs(mapExtent.GetBottom() -mapExtent.GetTop());
	   dbTmp =fxScale*m_DrawParam.m_ScreenHeigh - dbTmp;  
       m_DrawParam.m_StartY = mapExtent.GetBottom() -  dbTmp / 2; 
    } 
	else
    {   
	   m_DrawParam.m_Scale =  fyScale;
	   m_DrawParam.m_StartY =  mapExtent.GetBottom(); 
       dbTmp = fabs(mapExtent.GetRight() -mapExtent.GetLeft()); 
	   dbTmp = fyScale*m_DrawParam.m_ScreenWidth - dbTmp;  
       m_DrawParam.m_StartX =  mapExtent.GetLeft() - dbTmp / 2; 
    } 


}