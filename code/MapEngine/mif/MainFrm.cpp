// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "EasyMap.h"

#include "MainFrm.h"
#include "EasyMapDoc.h"
#include "EasyMapView.h"
#include "LayersCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MAP_TIP, OnMapTip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bMapTip = FALSE;
    m_MapTipLayer = _T("");;
	m_MapTipField = _T("");
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*UINT nIndex,nID, nStyle;
	int nImage;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_CHECK | TBSTYLE_TOOLTIPS, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	nIndex = m_wndToolBar.CommandToIndex( ID_MAP_TIP );
	m_wndToolBar.SetButtonInfo( nIndex, ID_MAP_TIP, TBBS_CHECKBOX , 9 ); 
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_MAP_TIP , MF_UNCHECKED );*/
	//创建格式工具栏
    if (! m_JMToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_BORDER_3D|CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0)) ||
		! m_JMToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	 m_JMToolBar.InitBar();
		
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{ 
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
    m_wndStatusBar.SetPaneInfo(0,0,SBPS_NORMAL,200);       //设置状态条
	m_wndStatusBar.SetPaneInfo(1,1,SBPS_NORMAL,200);
    m_wndStatusBar.SetPaneInfo(2,2,SBPS_NORMAL,200);  
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_JMToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
    DockControlBar(&m_JMToolBar); 
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	 
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
     
	 m_hcurZInWindow = (HCURSOR)::LoadImage(cs.hInstance , MAKEINTRESOURCE(IDC_CURZINWINDOW),
		                   IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR ); 
	 m_hcurZIn  = (HCURSOR)::LoadImage(cs.hInstance , MAKEINTRESOURCE(IDC_CURZIN),
	                       IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR ); 
	 m_hcurZOut = (HCURSOR)::LoadImage(cs.hInstance , MAKEINTRESOURCE(IDC_CURZOUT),
		                   IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR ); 
     m_hcurPan =  (HCURSOR)::LoadImage(cs.hInstance , MAKEINTRESOURCE(IDC_CURPAN),
		                   IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR ); 
     m_hcurFind =  (HCURSOR)::LoadImage(cs.hInstance , MAKEINTRESOURCE(IDC_CURFIND),
		                   IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR );  
	 
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::DestroyWindow() 
{
	::DestroyCursor(m_hcurZInWindow);  
	::DestroyCursor(m_hcurZOut);
    ::DestroyCursor(m_hcurPan);

 	return CFrameWnd::DestroyWindow();
}


void CMainFrame::OnMapTip() 
{
   if ( m_bMapTip )
	   m_bMapTip = FALSE;
   else
       m_bMapTip = TRUE;  
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
    if ( !m_wndSplitter.CreateStatic(this,1,2) )
		 return FALSE;
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CLayersCtrlView),CSize(200,200),pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CEasyMapView),CSize(10,10),pContext);	
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
