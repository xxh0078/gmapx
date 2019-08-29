// testmymapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testmymap.h"
#include "testmymapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
bool m_bDown = false;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestmymapDlg dialog

CTestmymapDlg::CTestmymapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestmymapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestmymapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestmymapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestmymapDlg)
	DDX_Control(pDX, IDC_GMAPXCTRL1, m_gmapx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestmymapDlg, CDialog)
	//{{AFX_MSG_MAP(CTestmymapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	ON_COMMAND(ID_MENUITEM32776, OnMenuitem32776)
	ON_COMMAND(ID_MENUITEM32777, OnMenuitem32777)
	ON_COMMAND(ID_MENUITEM32778, OnMenuitem32778)
	ON_COMMAND(ID_MENUITEM32779, OnMenuitem32779)
	ON_COMMAND(ID_MENUITEM32780, OnMenuitem32780)
	ON_COMMAND(ID_MENUITEM32781, OnMenuitem32781)
	ON_COMMAND(ID_MENUITEM32782, OnMenuitem32782)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestmymapDlg message handlers

BOOL CTestmymapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_gmapx.CreateMapPolygon(200);
	m_gmapx.AddMapPolygonPoint( 200,116,39);
	m_gmapx.AddMapPolygonPoint( 200,117,39);
	m_gmapx.AddMapPolygonPoint( 200,117,40);
	m_gmapx.AddMapPolygonPoint( 200,116.5,40);
	//m_gmapx.SetMapPolygonColor( 200,0xFF0000 );
	m_gmapx.SetMapPolygonColor(200,0xFF0000);//RGB(241,122,54)

	m_gmapx.CreateMapPolygon(201);
	m_gmapx.AddMapPolygonPoint( 201,116.5,40);
	m_gmapx.AddMapPolygonPoint( 201,116,40);
	m_gmapx.AddMapPolygonPoint( 201,116,39);
	//m_gmapx.AddMapPolygonPoint( 201,117,40);	
	m_gmapx.SetMapPolygonColor(201,0xFF00);//RGB(241,122,54)
	g_pGMapX = &m_gmapx;
	m_DlgMoveMap.Create(IDD_DLGMOVEMAP); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestmymapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestmymapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestmymapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CTestmymapDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestmymapDlg)
	ON_EVENT(CTestmymapDlg, IDC_GMAPXCTRL1, 1 /* OnMapPointClick */, OnOnMapPointClickGmapxctrl1, VTS_I4)
	ON_EVENT(CTestmymapDlg, IDC_GMAPXCTRL1, 8 /* OnLoadEnd */, OnOnLoadEndGmapxctrl1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTestmymapDlg::OnOnMapPointClickGmapxctrl1(long pid) 
{
	// TODO: Add your control notification handler code here
	
}

void CTestmymapDlg::OnOnLoadEndGmapxctrl1() 
{
	// TODO: Add your control notification handler code here
	m_bDown = true;
	//this->m_gmapx.SetMapLocPath( "D:\\gmapx\\down\\mapabc" );
}

void CTestmymapDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( m_bDown )
	{
		this->m_gmapx.MoveWindow( 0,0,cx,cy );
	}
}

void CTestmymapDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CTestmymapDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	/*	GMAP_GOOGLE_MAP = 0,			//谷歌一般地图
	GMAP_GOOGLE_IMAGE = 1,			//谷歌影像地图
	GMAP_GOOGLE_MARK = 2,			//谷歌影像注记图层
	GMAP_GOOGLE_PHYSICAL  = 3,		//谷歌地形地形图
	GMAP_GOOGLE_IMAGEMARK  = 4,		//谷歌混合影像图
	GMAP_BAIDU_MAP = 5,				//百度地图数据
	GMAP_VM	= 6,					//VIRTUALEARTH
	GMAP_MYMAP = 7,					//下载地图
	GMAP_CHANGLIAN = 8,				//畅联万方地图数据
	GMAP_MAPABC = 9,				//MapABC地图
	GMAP_MAPBAR = 10,				//MAPBAR地图
	GMAP_MAP365 = 11,				//MAP365地图
	GMAP_TIANDT = 12,				//天地图
	GMAP_SUPERMAP = 13,				//超图地图
	GMAP_FILES = 14					//文件地图
	*/
	this->m_gmapx.SetOnlineMap( 0 );
}
//1为方向测距 2为画线，3为画多边形，4为画巨型,5为画园
void CTestmymapDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	m_gmapx.SetMapTools( 2 );
}

void CTestmymapDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	m_gmapx.SetMapTools( 5 );
}

void CTestmymapDlg::OnMenuitem32774() 
{
	// TODO: Add your command handler code here
	m_gmapx.SetMapTools( 3 );
}

void CTestmymapDlg::OnMenuitem32775() 
{
	// TODO: Add your command handler code here
	/*	
	GMAP_GOOGLE_MAP = 0,			//谷歌一般地图
	GMAP_GOOGLE_IMAGE = 1,			//谷歌影像地图
	GMAP_GOOGLE_MARK = 2,			//谷歌影像注记图层
	GMAP_GOOGLE_PHYSICAL  = 3,		//谷歌地形地形图
	GMAP_GOOGLE_IMAGEMARK  = 4,		//谷歌混合影像图
	GMAP_BAIDU_MAP = 5,				//百度地图数据
	GMAP_VM	= 6,					//VIRTUALEARTH
	GMAP_MYMAP = 7,					//下载地图
	GMAP_CHANGLIAN = 8,				//畅联万方地图数据
	GMAP_MAPABC = 9,				//MapABC地图
	GMAP_MAPBAR = 10,				//MAPBAR地图
	GMAP_MAP365 = 11,				//MAP365地图
	GMAP_TIANDT = 12,				//天地图
	GMAP_SUPERMAP = 13,				//超图地图
	GMAP_FILES = 14					//文件地图
	*/
	this->m_gmapx.SetOnlineMap( 9 );
}

void CTestmymapDlg::OnMenuitem32776() 
{
	// TODO: Add your command handler code here
	this->m_gmapx.SetOnlineMap( 3 );
}

void CTestmymapDlg::OnMenuitem32777() 
{
	// TODO: Add your command handler code here
	this->m_gmapx.SetOnlineMap( 1 );
}

void CTestmymapDlg::OnMenuitem32778() 
{
	// TODO: Add your command handler code here
	this->m_gmapx.SetOnlineMap( 4 );
}

void CTestmymapDlg::OnMenuitem32779() 
{
	// TODO: Add your command handler code here
	this->m_gmapx.SetOnlineMap( 6 );
}

void CTestmymapDlg::OnMenuitem32780() 
{
	// TODO: Add your command handler code here
	this->m_gmapx.SetOnlineMap( 6 );
}

void CTestmymapDlg::OnMenuitem32781() 
{
	// TODO: Add your command handler code here
	m_gmapx.SetMapTools( 1 );
}

void CTestmymapDlg::OnMenuitem32782() 
{
	// TODO: Add your command handler code here
	m_DlgMoveMap.ShowWindow(SW_SHOWNORMAL); 
}
