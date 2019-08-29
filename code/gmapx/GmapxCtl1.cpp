// GmapxCtl.cpp : Implementation of the CGmapxCtrl ActiveX Control class.

#include "stdafx.h"
#include "gmapx.h"
#include "GmapxCtl.h"
#include "GmapxPpg.h"
#include "InputBox.h"
#include "DlgMapSymbol.h"
#include "../MapEngine/MapEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定义地图引擎
//CMapEngine* m_pMapEngine=NULL;
CGmapxCtrl* g_pGmapxCtrl = NULL;
IMPLEMENT_DYNCREATE(CGmapxCtrl, COleControl)

void OnMessage1( long message, long p1, long p2, const char* p3 )
{
	g_pGmapxCtrl->OnEventMessage( message, p1, p2, p3 );
}
void CGmapxCtrl::OnEventMessage( long message, long p1, long p2, const char* p3 )
{
	TRACE("\nm=%d,p1=%d,p2=%d,p3=%s\n",message,p1,p2,p3);
	FireOnMessage( message, p1, p2, p3 );
}
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CGmapxCtrl, COleControl)
	//{{AFX_MSG_MAP(CGmapxCtrl)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_MENUITEM32768, OnMenuitem32768)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM32769, OnMenuitem32769)
	ON_COMMAND(ID_MENUITEM32770, OnMenuitem32770)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CGmapxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CGmapxCtrl)
	DISP_FUNCTION(CGmapxCtrl, "SetMapURL", SetMapURL, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapLocPath", SetMapLocPath, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "MapZoomIn", MapZoomIn, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "MapZoomOut", MapZoomOut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "GetMapScale", GetMapScale, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "SetMapScale", SetMapScale, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "MoveMap", MoveMap, VT_EMPTY, VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "ShowMap", ShowMap, VT_EMPTY, VTS_R8 VTS_R8 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "CreateICO", CreateICO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "CreateMapPoint", CreateMapPoint, VT_BOOL, VTS_I4 VTS_R8 VTS_R8 VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPoint", SetMapPoint, VT_I4, VTS_I4 VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPointName", SetMapPointName, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPointText", SetMapPointText, VT_I4, VTS_I4 VTS_R8 VTS_R8 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPointICO", SetMapPointICO, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "DeleteMapPoint", DeleteMapPoint, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "CreateMapLine", CreateMapLine, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "DeleteLine", DeleteLine, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "AddMapLinePoint", AddMapLinePoint, VT_I4, VTS_I4 VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "SetMapLineName", SetMapLineName, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapLineColor", SetMapLineColor, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SetMapLineWidth", SetMapLineWidth, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "CreateMapAround", CreateMapAround, VT_I4, VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "DeleteMapAround", DeleteMapAround, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "CreateMapText", CreateMapText, VT_I4, VTS_I4 VTS_R8 VTS_R8 VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "DeleteMapText", DeleteMapText, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "Invalidate", Invalidate, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "RemoveAllLayer", RemoveAllLayer, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "SetMapTextFont", SetMapTextFont, VT_I4, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "IsInMapBound", IsInMapBound, VT_BOOL, VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "IsMapPointInMapCreen", IsMapPointInMapCreen, VT_BOOL, VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "CreateMapPolygon", CreateMapPolygon, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "DeletePolygon", DeletePolygon, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "AddMapPolygonPoint", AddMapPolygonPoint, VT_I4, VTS_I4 VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "GetMapCenterX", GetMapCenterX, VT_R8, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "GetMapCenterY", GetMapCenterY, VT_R8, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "MoveMapBound", MoveMapBound, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "SetMapTools", SetMapTools, VT_I4, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "ClearMapTools", ClearMapTools, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "RegisterKey", RegisterKey, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "GetMapBound", GetMapBound, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "GetMapOffSet", GetMapOffSet, VT_BSTR, VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "SetMapLevelBount", SetMapLevelBount, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SetMapScaleBound", SetMapScaleBound, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "OpenAddMapLayer", OpenAddMapLayer, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "CloseAddMapLayer", CloseAddMapLayer, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "DeleteAllMapPoint", DeleteAllMapPoint, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGmapxCtrl, "IsInMapToolsPolygon", IsInMapToolsPolygon, VT_BOOL, VTS_R8 VTS_R8)
	DISP_FUNCTION(CGmapxCtrl, "SaveMapPoint", SaveMapPoint, VT_I4, VTS_R8 VTS_R8 VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SaveMapLine", SaveMapLine, VT_I4, VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "OpenMapEdit", OpenMapEdit, VT_I4, VTS_I4 VTS_I4 VTS_BOOL)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPolygonName", SetMapPolygonName, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapPolygonColor", SetMapPolygonColor, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SetMapAroundName", SetMapAroundName, VT_EMPTY, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGmapxCtrl, "SetMapAroundColor", SetMapAroundColor, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SetOnlineMap", SetOnlineMap, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "SaveMapText", SaveMapText, VT_I4, VTS_R8 VTS_R8 VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION(CGmapxCtrl, "ShowMapTool", ShowMapTool, VT_I2, VTS_I2 VTS_I2)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CGmapxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CGmapxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CGmapxCtrl)
	EVENT_CUSTOM("OnMapPointClick", FireOnMapPointClick, VTS_I4)
	EVENT_CUSTOM("OnDrawLine", FireOnDrawLine, VTS_I4  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnDrawPolygon", FireOnDrawPolygon, VTS_I4  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnDrawLineEnd", FireOnDrawLineEnd, VTS_I4)
	EVENT_CUSTOM("OnDrawPolygonEnd", FireOnDrawPolygonEnd, VTS_I4)
	EVENT_CUSTOM("OnMapToolsLine", FireOnMapToolsLine, VTS_I4  VTS_BSTR  VTS_BSTR)
	EVENT_CUSTOM("OnMapToolsPolygon", FireOnMapToolsPolygon, VTS_I4  VTS_BSTR  VTS_BSTR)
	EVENT_CUSTOM("OnLoadEnd", FireOnLoadEnd, VTS_NONE)
	EVENT_CUSTOM("OnMapTollsRect", FireOnMapTollsRect, VTS_R8  VTS_R8  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnGetMapBound", FireOnGetMapBound, VTS_R8  VTS_R8  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnMouseMap", FireOnMouseMap, VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnMapPointDbClick", FireOnMapPointDbClick, VTS_I4  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnMapToolsDistance", FireOnMapToolsDistance, VTS_R8  VTS_R8  VTS_R8  VTS_R8  VTS_R8  VTS_R8)
	EVENT_CUSTOM("OnMessage", FireOnMessage, VTS_I4  VTS_I4  VTS_I4  VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGmapxCtrl, 1)
	PROPPAGEID(CGmapxPropPage::guid)
END_PROPPAGEIDS(CGmapxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGmapxCtrl, "GMAPX.GmapxCtrl.1",
	0xad6cbf6, 0xe7e0, 0x466f, 0x8a, 0xa3, 0x10, 0xe5, 0x9f, 0x2c, 0xba, 0xc)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CGmapxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGmapx =
		{ 0xe70b546f, 0x7024, 0x4582, { 0x91, 0x2e, 0xad, 0xa3, 0xb9, 0x89, 0xda, 0x6a } };
const IID BASED_CODE IID_DGmapxEvents =
		{ 0xf2fddfb3, 0x5a4b, 0x46b9, { 0xa4, 0xe0, 0x2d, 0x1c, 0x21, 0x7f, 0xff, 0xdd } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGmapxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGmapxCtrl, IDS_GMAPX, _dwGmapxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::CGmapxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGmapxCtrl

BOOL CGmapxCtrl::CGmapxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GMAPX,
			IDB_GMAPX,
			afxRegApartmentThreading,
			_dwGmapxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::CGmapxCtrl - Constructor

CGmapxCtrl::CGmapxCtrl()
{
	InitializeIIDs(&IID_DGmapx, &IID_DGmapxEvents);

	// TODO: Initialize your control's instance data here.
	m_pMapEngine = NULL;
	g_pGmapxCtrl = NULL;
	m_pDlgProperty = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::~CGmapxCtrl - Destructor

CGmapxCtrl::~CGmapxCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if( m_pDlgProperty )
	{
		delete m_pDlgProperty;
		m_pDlgProperty = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::OnDraw - Drawing function

void CGmapxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
//	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
//	pdc->Ellipse(rcBounds);
	if ( m_pMapEngine )
	{
		// device context for painting
		m_pMapEngine->OnDraw( pdc->GetSafeHdc() );
	}
	//::DeleteDC(pdc->GetSafeHdc());
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::DoPropExchange - Persistence support

void CGmapxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::OnResetState - Reset control to default state

void CGmapxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl::AboutBox - Display an "About" box to the user

void CGmapxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_GMAPX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl message handlers

void CGmapxCtrl::SetMapURL(LPCTSTR mapurl) 
{
	// TODO: Add your dispatch handler code here

}

void CGmapxCtrl::SetMapLocPath(LPCTSTR mappath) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->SetMapPath( mappath );
	}
}

void CGmapxCtrl::MapZoomIn() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("MapZoomIn");
		m_pMapEngine->OnMapZoomIn();
	}
}

void CGmapxCtrl::MapZoomOut() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("MapZoomOut");
		m_pMapEngine->OnMapZoomOut();
	}
}

long CGmapxCtrl::GetMapScale() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("GetMapScale");
		return m_pMapEngine->GetMapScale();
	}
	return 0;
	return 0;
}

void CGmapxCtrl::SetMapScale(long scale) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("SetMapScale");
		m_pMapEngine->SetMapScale(scale);
	}
}

void CGmapxCtrl::MoveMap(double longitude, double latitude) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("MoveMap");
		m_pMapEngine->MoveMap(longitude,latitude);
	}
}

void CGmapxCtrl::ShowMap(double longitude, double latitude, long scale) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->SetMapScale( scale );
		m_pMapEngine->MoveMap( longitude,latitude );
	}
}

long CGmapxCtrl::CreateICO(LPCTSTR path) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		m_pMapEngine->WriteLog("CreateICO");
//		m_pMapEngine->WriteLog(path);
		return m_pMapEngine->CreateMapRes( path );
	}
	return 0;
}

BOOL CGmapxCtrl::CreateMapPoint(long pid, double longitude, double lanitude, LPCTSTR name, LPCTSTR text, long icoid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("CreateMapPoint:pid=%d,x=%f,y=%f,name=%s,text=%s,icoid=%d",pid,x,y,name,text,icoid);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->CreateMapPoint(pid,longitude,lanitude,name,text,icoid);
	}
	return false;
}

long CGmapxCtrl::SetMapPoint(long pid, double lonitude, double lanitude) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapPoint:pid=%d,x=%f,y=%f",pid,x,y);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapPoint( pid,lonitude,lanitude );
	}
	return 0;
}

long CGmapxCtrl::SetMapPointName(long pid, LPCTSTR name) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapPointName:pid=%d,%s",pid,name);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapPointName( pid,name);
	}
	return 0;
}

long CGmapxCtrl::SetMapPointText(long pid, double longitude, double lanitude, LPCTSTR text) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapPointText:text=%d,%s",pid,text);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapPointText( pid,text);
	}
	return 0;
}

long CGmapxCtrl::SetMapPointICO(long pid, long icoid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapPointICO:text=%d,%d",pid,icoid);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapPointICO( pid,icoid );
	}
	return 0;
}

long CGmapxCtrl::DeleteMapPoint(long pid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
///		strLog.Format("DeleteMapPoint:pid=%d,%d",pid);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->DeleteMapPoint( pid );
	}
	return 0;
}

long CGmapxCtrl::CreateMapLine(long lid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("CreateMapLine:lid=%d,%d",lid);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->CreateMapLine( lid );
	}
	return 0;
}

long CGmapxCtrl::DeleteLine(long lid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("DeleteLine:lid=%d",lid);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->DeleteLine( lid );
	}
	return 0;
}

long CGmapxCtrl::AddMapLinePoint(long lid, double longitude, double lanitude) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("AddMapLinePoint:lid=%d,%f,%f",lid,x,y);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->AddMapLinePoint( lid,longitude,lanitude);
	}
	return 0;
}

long CGmapxCtrl::SetMapLineName(long lid, LPCTSTR name) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapLineName:lid=%d,%s",lid,name);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapLineName( lid,name );
	}
	return 0;
}

long CGmapxCtrl::SetMapLineColor(long lid, long colorbgr) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapLineColor:lid=%d,%d",lid,bgr);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapLineColor( lid, colorbgr );
	}
	return 0;
}

long CGmapxCtrl::SetMapLineWidth(long lid, long width) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
//		CString strLog;
//		strLog.Format("SetMapLineWidth:lid=%d,%d",lid,width);
//		m_pMapEngine->WriteLog(strLog);
		return m_pMapEngine->SetMapLineWidth( lid, width );
	}
	return 0;
}

long CGmapxCtrl::CreateMapAround(long rid, double longitude, double lanitide, long radius, long alpha) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
//		CString strLog;
//		strLog.Format("CreateMapAround:rid=%d",rid);
//		m_pMapEngine->WriteLog(strLog);
		m_pMapEngine->CreateMapAround( rid,longitude,lanitide,radius,alpha);
	}
	return 0;
}

long CGmapxCtrl::DeleteMapAround(long rid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
//		CString strLog;
//		strLog.Format("DeleteMapAround:rid=%d",rid);
//		m_pMapEngine->WriteLog(strLog);
		m_pMapEngine->DeleteMapAround( rid );
	}
	return 0;
}

long CGmapxCtrl::CreateMapText(long tid, double longitude, double lanitude, LPCTSTR text, long size, long colorbgr) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
//		CString strLog;
//		strLog.Format("CreateMapText:lid=%d",tid);
//		m_pMapEngine->WriteLog(strLog);
		m_pMapEngine->CreateMapText( tid,longitude,lanitude,text,size,colorbgr );
		return TRUE;
	}
	return 0;
}

long CGmapxCtrl::DeleteMapText(long tid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
//		CString strLog;
//		strLog.Format("DeleteMapText:lid=%d",tid);
//		m_pMapEngine->WriteLog(strLog);
		m_pMapEngine->DeleteMapText(tid);
		return TRUE;
	}
	return 0;
}

void CGmapxCtrl::Invalidate() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
		m_pMapEngine->Invalidate();
	}
}

void CGmapxCtrl::RemoveAllLayer() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
		m_pMapEngine->RemoveAllLayer();
	}
}

long CGmapxCtrl::SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
		return m_pMapEngine->SetMapTextFont( tid,size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
	}
	return 0;
}

BOOL CGmapxCtrl::IsInMapBound(double longitude, double lanigude) 
{
	// TODO: Add your dispatch handler code here
	
	return TRUE;
}

BOOL CGmapxCtrl::IsMapPointInMapCreen(double longitude, double lanitude) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine ) {
		return m_pMapEngine->IsMapPointInMapCreen(longitude,lanitude);
	}
	return TRUE;
}

long CGmapxCtrl::CreateMapPolygon(long pid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->CreateMapPolygon( pid );
	}
	return 0;
}

long CGmapxCtrl::DeletePolygon(long pid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->DeleteMapPolygon( pid );
	}
	return 0;
}

long CGmapxCtrl::AddMapPolygonPoint(long pid, double longitude, double lanitude) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->AddMapPolygonPoint( pid,longitude,lanitude );
	}
	return 0;
}

double CGmapxCtrl::GetMapCenterX() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		double x,y;
		m_pMapEngine->GetMapCenter(x,y);
		return x;
	}
	return 0.0;
}

double CGmapxCtrl::GetMapCenterY() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		double x,y;
		m_pMapEngine->GetMapCenter(x,y);
		return y;
	}
	return 0.0;
}

void CGmapxCtrl::MoveMapBound(double long1, double lan1, double long2, double lan2) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		//m_pMapEngine->WriteLog("MoveMap");
		m_pMapEngine->MoveMapBound( long1,lan1,long2,lan2);
	}
}

long CGmapxCtrl::SetMapTools(long type) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->SetMapTools( type );
	}
	return 0;
}

void CGmapxCtrl::ClearMapTools() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->ClearMapTools();
	}
}
/*if ( m_pMapEngine )
	{
		//return m_pMapEngine->RegisterKey( (char*)strRegisterKey );
		//minlan, double maxlan, double minlon, double maxlon
		FireOnGetMapBound( m_pMapEngine->m_MapDisp.m_MapBound.bottom,m_pMapEngine->m_MapDisp.m_MapBound.top,m_pMapEngine->m_MapDisp.m_MapBound.left,m_pMapEngine->m_MapDisp.m_MapBound.right);
	}*/
long CGmapxCtrl::RegisterKey(LPCTSTR userkey) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->RegisterKey( (char*)userkey );
	}
	return 0;
}

BSTR CGmapxCtrl::GetMapBound() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		//return m_pMapEngine->RegisterKey( (char*)strRegisterKey );
		//minlan, double maxlan, double minlon, double maxlon
		FireOnGetMapBound( m_pMapEngine->m_MapDisp.m_MapBound.bottom,m_pMapEngine->m_MapDisp.m_MapBound.top,m_pMapEngine->m_MapDisp.m_MapBound.left,m_pMapEngine->m_MapDisp.m_MapBound.right);
	}
	return strResult.AllocSysString();
}

BSTR CGmapxCtrl::GetMapOffSet(double lon, double lan) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		if( m_pMapEngine->GetMapOffSet( lon,lan ) )
		{
			strResult.Format("%f,%f",lon,lan);
		}
	}
	return strResult.AllocSysString();
}

void CGmapxCtrl::SetMapLevelBount(long minlevel, long maxlevel) 
{
	// TODO: Add your dispatch handler code here

}

void CGmapxCtrl::SetMapScaleBound(long scalemin, long scalemax) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->SetMapScaleBound( scalemin,scalemax);
	}
}

long CGmapxCtrl::OpenAddMapLayer(LPCTSTR path) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->OpenAddMapLayerPath( path );
	}
	return 0;
}

void CGmapxCtrl::CloseAddMapLayer() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->CloseAddMapLayer();
	}
}

void CGmapxCtrl::DeleteAllMapPoint() 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->DeleteAllMapPoint();
	}
}

BOOL CGmapxCtrl::IsInMapToolsPolygon(double lon, double lan) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->IsInMapToolsPolygon(lon,lan);
	} 
	return TRUE;
}

long CGmapxCtrl::SaveMapPoint(double lon, double lan, LPCTSTR name, LPCTSTR text, long icoid) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->SaveLocMapPoint( lon,lan,name,text,icoid );
	} 
	return 0;
}

long CGmapxCtrl::SaveMapLine(LPCTSTR name, LPCTSTR mappoints, long width, long colorbgr) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->SaveLocMapLine( mappoints, name, width, colorbgr );
	} 
	return 0;
}

BOOL CGmapxCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

LRESULT CGmapxCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( m_pMapEngine )
	{
		switch( message )
		{
		case WM_MAP_ONINIT:
			{
				//m_MapDisp.OnMapZoom();
				m_pDlgProperty = new CDlgProperty();
				m_pDlgProperty->Create( IDD_DLGPROPERTY,this );
				//m_pDlgProperty->ShowWindow(SW_SHOW);
				//初始化完成消息
				FireOnLoadEnd();
		//		MoveMapBound(-180,39,180,40);
				break;
			}
			break;
		case WM_MAP_DCCLICK_POIINFO_MESSAGE:
			break;
		case WM_MAP_POIINFO_MESSAGE:
			if ( m_pMapEngine )
			{
				TRACE("WM_MAP_POIINFO_MESSAGE");
				if( !m_bDbClicked )
				{
					TRACE("m_MapPoiInfo show");
//					m_pMapEngine->m_MapDisp.m_MapLayerMan.m_MapPoiInfo.SetVisible( 1 );
//					m_pMapEngine->Invalidate();
				}
			}
			break;
		case WM_MAP_TOOLS_MESSAGE:
			{
				string strParam;
				string strlon,strlan;
				if( wParam == 2 )
				{
//					m_pMapEngine->m_MapCtrl.m_MapToolPolygon.GetPointsText( strlon,strlan );
//					FireOnMapToolsPolygon(  lParam, strlon.c_str(), strlan.c_str() );
				}
				else if( wParam == 3 )
				{
				
				}
				else if( wParam == 6 )
				{
					if( lParam == 1 )
					{

					}
				}
			}
			break;
		}
		
		m_pMapEngine->MsgProc( message,wParam,lParam );
	}
	return COleControl::DefWindowProc(message, wParam, lParam);
}

int CGmapxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pMapEngine = new CMapEngine();
	m_pMapEngine->Init( this->m_hWnd );
	m_pMapEngine->SetMsgFun( OnMessage1 );
	m_pMapEngine->SetMapType( GMAP_MAPABC );
	g_pGmapxCtrl = this;
	m_bDbClicked = false;
//	SetMapUrl( "http://mt1.google.cn/vt/lyrs=m@124&hl=zh-CN&gl=cn&x=%x&y=%y&z=%z&s=G" );
//	SetMapUrl( "http://www.gmapx.com/gmapdata/level%z/%y/%x.png" );
	//http://www.gmapx.com/gmapdata/level%z/%y/%x.png
	//手形状光标
	m_hCursorHand = LoadCursor(NULL,MAKEINTRESOURCE(32649));
	m_hCursorArrow = LoadCursor(NULL,IDC_ARROW);
	//
//	m_pMapEngine->WriteLog("OnCreate");
	return 0;
}

void CGmapxCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	COleControl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->OnKillFocus();
	}
}

void CGmapxCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_pMapEngine )
	{
		m_bDbClicked = false;
		if ( point.x >= 0 && point.x <= m_rcBounds.Width() &&
			point.y >= 0 && point.y <= m_rcBounds.Height() ) 
		{
		//	SetCursor( m_hCursorHand );
			VOSPoint pt( point.x,point.y);
			//m_hCursorHand
		//	m_pMapEngine->OnMouseMove( pt );
			double x,y;
			m_pMapEngine->ScreenToMap(pt.x,pt.y,x,y);
			FireOnMouseMap(x,y);
		}
		else
		{
			SetCursor( m_hCursorArrow );
		}
	}
	COleControl::OnLButtonDown(nFlags, point);
}

void CGmapxCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*if ( m_pMapEngine )
	{
		m_bDown = false;
		SetCursor( m_hCursorArrow );
		VOSPoint pt( point.x,point.y);
		m_pMapEngine->OnLButtonUp( pt );
	}*/
	//:;SetCapture(
	//SetCapture(false);
	//ReleaseCapture();
	COleControl::OnLButtonUp(nFlags, point);
}

void CGmapxCtrl::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnMButtonDblClk(nFlags, point);
}

void CGmapxCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_pMapEngine )
	{
		if ( point.x >= 0 && point.x <= m_rcBounds.Width() &&
			point.y >= 0 && point.y <= m_rcBounds.Height() ) 
		{
		//	SetCursor( m_hCursorHand );
			VOSPoint pt( point.x,point.y);
		//m_hCursorHand
		//	m_pMapEngine->OnMouseMove( pt );
			double x,y;
			m_pMapEngine->ScreenToMap(pt.x,pt.y,x,y);
			TRACE("\nx=%d,y=%d,mapx=%f,mapy=%f\n",pt.x,pt.y,x,y);
			FireOnMouseMap(x,y);
		}
		else
		{
			SetCursor( m_hCursorArrow );
		}
	}
	COleControl::OnMouseMove(nFlags, point);
}

BOOL CGmapxCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	/*if ( m_pMapEngine )
	{
		CPoint pt1( pt );
		ScreenToClient( &pt1 );
		if ( pt1.x >= m_rcBounds.left && pt1.x <= m_rcBounds.right &&
			pt1.y >= m_rcBounds.top && pt1.y <= m_rcBounds.bottom )
		{
			VOSPoint point( pt1.x,pt1.y );
			m_pMapEngine->OnMouseWheel( zDelta, point );
			return true;
		}
	}*/
	return COleControl::OnMouseWheel(nFlags, zDelta, pt);
}

void CGmapxCtrl::OnMove(int x, int y) 
{
	COleControl::OnMove(x, y);
	
	// TODO: Add your message handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->Invalidate();
	}

}

void CGmapxCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if ( this )
	{
		// TODO: Add your message handler code here
		if ( m_pMapEngine )
		{
//			m_pMapEngine->WriteLog("OnSize:%d,%d");
			m_pMapEngine->SetMapPos( 0,0,cx,cy,0 );
		}
	}
}

void CGmapxCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnTimer(nIDEvent);
}

void CGmapxCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnRButtonUp(nFlags, point);
}

BOOL CGmapxCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return COleControl::DestroyWindow();
}

void CGmapxCtrl::OnDestroy() 
{
	COleControl::OnDestroy();
	
	// TODO: Add your message handler code here
	if ( m_pMapEngine ) {
//		CString strLog;
//		strLog.Format("OnDestroy");
//		m_pMapEngine->WriteLog(strLog);
		m_pMapEngine->Destroy();
		delete m_pMapEngine;
		m_pMapEngine = NULL;
	}
//	Sleep(500);
}

void CGmapxCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_pMapEngine )
	{
		VOSPoint pt( point.x,point.y);
		if ( point.x >= 0 && point.x <= m_rcBounds.Width() &&
			point.y >= 0 && point.y <= m_rcBounds.Height() ) 
		{
			//m_pMapEngine->OnLButtonDblClk( pt );
			double x,y;
			m_pMapEngine->ScreenToMap(pt.x,pt.y,x,y);

			CMapPoi* pMapPoi = NULL;
			if( m_pMapEngine->IsPointIn( pt,pMapPoi ))
			{
				m_bDbClicked = true;
				if( pMapPoi )
				{
					this->FireOnMapPointDbClick( pMapPoi->m_sPOIID,pMapPoi->m_Point.x, pMapPoi->m_Point.y );
				}
				TRACE("双击");
				//this->FireOnMapDBClick( x,y);
			}
			else
			{
			
				//this->FireOnMapDBClick( x,y);
			}
		}
	}
	COleControl::OnLButtonDblClk(nFlags, point);
}

long CGmapxCtrl::OpenMapEdit(long type, long id, BOOL bedit) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->OpenMapEdit( type, id, bedit );
	}
	return 0;
}

long CGmapxCtrl::SetMapPolygonName(long pid, LPCTSTR name) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->SetMapPolygonName( pid, name );
	}
	return 0;
}

long CGmapxCtrl::SetMapPolygonColor(long pid, long colorbgr) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		return m_pMapEngine->SetMapPolygonColor( pid, colorbgr );
	}
	return 0;
}

void CGmapxCtrl::SetMapAroundName(long rid, LPCTSTR name) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->SetMapAroundName( rid, name );
	}
}

long CGmapxCtrl::SetMapAroundColor(long rid, long colorbgr) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		m_pMapEngine->SetMapAroundColor( rid, colorbgr );
	}
	return 0;
}

void CGmapxCtrl::SetOnlineMap(long lMapType) 
{
	// TODO: Add your dispatch handler code here
	if ( m_pMapEngine )
	{
		en_MapType eMapType = (en_MapType)lMapType;
		m_pMapEngine->SetMapType( eMapType );
	}
}
bool g_bOnKeyCtrl = false;
void CGmapxCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_SHIFT)
    {
		//AfxMessageBox(_T("Shift"));
	}
	else if (nChar == VK_CONTROL)
	{
		//AfxMessageBox(_T("Ctrl"));
		g_bOnKeyCtrl = true;
	}
	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGmapxCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_CONTROL)
	{
		//AfxMessageBox(_T("Ctrl"));
		g_bOnKeyCtrl = false;
	}
	COleControl::OnKeyUp(nChar, nRepCnt, nFlags);
}
int g_i=0;

void CGmapxCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CRect rect;
	this->GetWindowRect( rect );
	m_lX = point.x-rect.left;
	m_lY = point.y-rect.top;

	CMenu popMenu;
	popMenu.LoadMenu(IDR_RBTN_MENU); //载入菜单
	CMenu *pPopup;
	pPopup=popMenu.GetSubMenu(0); //获得子菜单指针
 
//	pPopup->EnableMenuItem(ID_1,MF_BYCOMMAND|MF_ENABLED); //允许菜单项使用
//	pPopup->EnableMenuItem(ID_2,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED); //不允许菜单项使用
	
	
	//ClientToScreen(&point); //将客户区坐标转换成屏幕坐标
	//m_lX = point.x;
	//m_lY = point.y;
	//TRACE("\n11111x=%d,y=%d\n",m_lX,m_lY);
	
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this); //显示弹出菜单，参数依次为(鼠标在菜单左边|跟踪右键，x，y，this)
	pPopup->Detach();
	popMenu.DestroyMenu();
}

long CGmapxCtrl::SaveMapText(double lon, double lan, LPCTSTR strText, long fontsize, long bgrcolor) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}
void CGmapxCtrl::OnMenuitem32768() 
{
	// TODO: Add your command handler code here
	double dx,dy;
	this->m_pMapEngine->ScreenToMap( this->m_lX,this->m_lY,dx,dy);
	TRACE("\n2222x=%d,y=%d\n",m_lX,m_lY);
	CDlgMapSymbol DlgMapSymbol;
	if( IDOK == DlgMapSymbol.DoModal() )
	{
		this->m_pMapEngine->SaveLocMapPoint(dx,dy,CDlgMapSymbol::m_strInputText.GetBuffer(0),"",CDlgMapSymbol::m_iICOID);
	}
	
}
void CGmapxCtrl::OnMenuitem32769() 
{
	// TODO: Add your command handler code here
	double dx,dy;
	this->m_pMapEngine->ScreenToMap( this->m_lX,this->m_lY,dx,dy);
	TRACE("\n2222x=%d,y=%d\n",m_lX,m_lY);
	CInputBox InputBox;
	if( IDOK == InputBox.DoModal() )
	{
		this->m_pMapEngine->SaveLocMapText(dx,dy,CInputBox::GetInputText().GetBuffer(0),20,0xFF0000);
	}

}

void CGmapxCtrl::OnMenuitem32770() 
{
	// TODO: Add your command handler code here
	double dx,dy;
	this->m_pMapEngine->ScreenToMap( this->m_lX,this->m_lY,dx,dy);
	TRACE("\n2222x=%d,y=%d\n",m_lX,m_lY);
	char chTemp[20];
	sprintf(chTemp,"当前经纬度为：%f,%f",dx,dy);
	AfxMessageBox(chTemp);
}

short CGmapxCtrl::ShowMapTool(short sType, short sValue) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}
