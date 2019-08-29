#if !defined(AFX_GMAPXCTL_H__FBF69BDD_0D18_431A_815E_2A448946A768__INCLUDED_)
#define AFX_GMAPXCTL_H__FBF69BDD_0D18_431A_815E_2A448946A768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GmapxCtl.h : Declaration of the CGmapxCtrl ActiveX Control class.
#include "../MapEngine/MapEngine.h"
#include "DlgProperty.h"
/////////////////////////////////////////////////////////////////////////////
// CGmapxCtrl : See GmapxCtl.cpp for implementation.

class CGmapxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGmapxCtrl)

// Constructor
public:
	CGmapxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGmapxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CGmapxCtrl();

	DECLARE_OLECREATE_EX(CGmapxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGmapxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGmapxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGmapxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CGmapxCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMenuitem32768();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuitem32769();
	afx_msg void OnMenuitem32770();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CGmapxCtrl)
	afx_msg void SetMapURL(LPCTSTR mapurl);
	afx_msg void SetMapLocPath(LPCTSTR mappath);
	afx_msg void MapZoomIn();
	afx_msg void MapZoomOut();
	afx_msg long GetMapScale();
	afx_msg void SetMapScale(long scale);
	afx_msg void MoveMap(double longitude, double latitude);
	afx_msg void ShowMap(double longitude, double latitude, long scale);
	afx_msg long CreateICO(LPCTSTR path);
	afx_msg BOOL CreateMapPoint(long pid, double longitude, double lanitude, LPCTSTR name, LPCTSTR text, long icoid);
	afx_msg long SetMapPoint(long pid, double lonitude, double lanitude);
	afx_msg long SetMapPointName(long pid, LPCTSTR name);
	afx_msg long SetMapPointText(long pid, double longitude, double lanitude, LPCTSTR text);
	afx_msg long SetMapPointICO(long pid, long icoid);
	afx_msg long DeleteMapPoint(long pid);
	afx_msg long CreateMapLine(long lid);
	afx_msg long DeleteLine(long lid);
	afx_msg long AddMapLinePoint(long lid, double longitude, double lanitude);
	afx_msg long SetMapLineName(long lid, LPCTSTR name);
	afx_msg long SetMapLineColor(long lid, long colorbgr);
	afx_msg long SetMapLineWidth(long lid, long width);
	afx_msg long CreateMapAround(long rid, double longitude, double lanitide, long radius, long alpha);
	afx_msg long DeleteMapAround(long rid);
	afx_msg long CreateMapText(long tid, double longitude, double lanitude, LPCTSTR text, long size, long colorbgr);
	afx_msg long DeleteMapText(long tid);
	afx_msg void Invalidate();
	afx_msg void RemoveAllLayer();
	afx_msg long SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	afx_msg BOOL IsInMapBound(double longitude, double lanigude);
	afx_msg BOOL IsMapPointInMapCreen(double longitude, double lanitude);
	afx_msg long CreateMapPolygon(long pid);
	afx_msg long DeletePolygon(long pid);
	afx_msg long AddMapPolygonPoint(long pid, double longitude, double lanitude);
	afx_msg double GetMapCenterX();
	afx_msg double GetMapCenterY();
	afx_msg void MoveMapBound(double long1, double lan1, double long2, double lan2);
	afx_msg long SetMapTools(long type);
	afx_msg void ClearMapTools();
	afx_msg long RegisterKey(LPCTSTR userkey);
	afx_msg BSTR GetMapBound();
	afx_msg BSTR GetMapOffSet(double lon, double lan);
	afx_msg void SetMapLevelBount(long minlevel, long maxlevel);
	afx_msg void SetMapScaleBound(long scalemin, long scalemax);
	afx_msg long OpenAddMapLayer(LPCTSTR path);
	afx_msg void CloseAddMapLayer();
	afx_msg void DeleteAllMapPoint();
	afx_msg BOOL IsInMapToolsPolygon(double lon, double lan);
	afx_msg long SaveMapPoint(double lon, double lan, LPCTSTR name, LPCTSTR text, long icoid);
	afx_msg long SaveMapLine(LPCTSTR name, LPCTSTR mappoints, long width, long colorbgr);
	afx_msg long OpenMapEdit(long type, long id, BOOL bedit);
	afx_msg long SetMapPolygonName(long pid, LPCTSTR name);
	afx_msg long SetMapPolygonColor(long pid, long colorbgr);
	afx_msg void SetMapAroundName(long rid, LPCTSTR name);
	afx_msg long SetMapAroundColor(long rid, long colorgbr);
	afx_msg void SetOnlineMap(long lMapType);
	afx_msg long SaveMapText(double lon, double lan, LPCTSTR strText, long fontsize, long bgrcolor);
	afx_msg short ShowMapTool(short sType, short sValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CGmapxCtrl)
	void FireOnMapPointClick(long pid)
		{FireEvent(eventidOnMapPointClick,EVENT_PARAM(VTS_I4), pid);}
	void FireOnDrawLine(long count, double lon, double lan)
		{FireEvent(eventidOnDrawLine,EVENT_PARAM(VTS_I4  VTS_R8  VTS_R8), count, lon, lan);}
	void FireOnDrawPolygon(long count, double lon, double lan)
		{FireEvent(eventidOnDrawPolygon,EVENT_PARAM(VTS_I4  VTS_R8  VTS_R8), count, lon, lan);}
	void FireOnDrawLineEnd(long count)
		{FireEvent(eventidOnDrawLineEnd,EVENT_PARAM(VTS_I4), count);}
	void FireOnDrawPolygonEnd(long count)
		{FireEvent(eventidOnDrawPolygonEnd,EVENT_PARAM(VTS_I4), count);}
	void FireOnMapToolsLine(long count, LPCTSTR lons, LPCTSTR lans)
		{FireEvent(eventidOnMapToolsLine,EVENT_PARAM(VTS_I4  VTS_BSTR  VTS_BSTR), count, lons, lans);}
	void FireOnMapToolsPolygon(long count, LPCTSTR lons, LPCTSTR lans)
		{FireEvent(eventidOnMapToolsPolygon,EVENT_PARAM(VTS_I4  VTS_BSTR  VTS_BSTR), count, lons, lans);}
	void FireOnLoadEnd()
		{FireEvent(eventidOnLoadEnd,EVENT_PARAM(VTS_NONE));}
	void FireOnMapTollsRect(double mleft, double mtop, double mright, double mbottom)
		{FireEvent(eventidOnMapTollsRect,EVENT_PARAM(VTS_R8  VTS_R8  VTS_R8  VTS_R8), mleft, mtop, mright, mbottom);}
	void FireOnGetMapBound(double lanmin, double lanmax, double lonmin, double lonmax)
		{FireEvent(eventidOnGetMapBound,EVENT_PARAM(VTS_R8  VTS_R8  VTS_R8  VTS_R8), lanmin, lanmax, lonmin, lonmax);}
	void FireOnMouseMap(double lon, double lan)
		{FireEvent(eventidOnMouseMap,EVENT_PARAM(VTS_R8  VTS_R8), lon, lan);}
	void FireOnMapPointDbClick(long pid, double lon, double lan)
		{FireEvent(eventidOnMapPointDbClick,EVENT_PARAM(VTS_I4  VTS_R8  VTS_R8), pid, lon, lan);}
	void FireOnMapToolsDistance(double lon1, double lan1, double lon2, double lan2, double distance, double direction)
		{FireEvent(eventidOnMapToolsDistance,EVENT_PARAM(VTS_R8  VTS_R8  VTS_R8  VTS_R8  VTS_R8  VTS_R8), lon1, lan1, lon2, lan2, distance, direction);}
	void FireOnMessage(long message, long param1, long param2, LPCTSTR param3)
		{FireEvent(eventidOnMessage,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4  VTS_BSTR), message, param1, param2, param3);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CGmapxCtrl)
	dispidSetMapURL = 1L,
	dispidSetMapLocPath = 2L,
	dispidMapZoomIn = 3L,
	dispidMapZoomOut = 4L,
	dispidGetMapScale = 5L,
	dispidSetMapScale = 6L,
	dispidMoveMap = 7L,
	dispidShowMap = 8L,
	dispidCreateICO = 9L,
	dispidCreateMapPoint = 10L,
	dispidSetMapPoint = 11L,
	dispidSetMapPointName = 12L,
	dispidSetMapPointText = 13L,
	dispidSetMapPointICO = 14L,
	dispidDeleteMapPoint = 15L,
	dispidCreateMapLine = 16L,
	dispidDeleteLine = 17L,
	dispidAddMapLinePoint = 18L,
	dispidSetMapLineName = 19L,
	dispidSetMapLineColor = 20L,
	dispidSetMapLineWidth = 21L,
	dispidCreateMapAround = 22L,
	dispidDeleteMapAround = 23L,
	dispidCreateMapText = 24L,
	dispidDeleteMapText = 25L,
	dispidInvalidate = 26L,
	dispidRemoveAllLayer = 27L,
	dispidSetMapTextFont = 28L,
	dispidIsInMapBound = 29L,
	dispidIsMapPointInMapCreen = 30L,
	dispidCreateMapPolygon = 31L,
	dispidDeletePolygon = 32L,
	dispidAddMapPolygonPoint = 33L,
	dispidGetMapCenterX = 34L,
	dispidGetMapCenterY = 35L,
	dispidMoveMapBound = 36L,
	dispidSetMapTools = 37L,
	dispidClearMapTools = 38L,
	dispidRegisterKey = 39L,
	dispidGetMapBound = 40L,
	dispidGetMapOffSet = 41L,
	dispidSetMapLevelBount = 42L,
	dispidSetMapScaleBound = 43L,
	dispidOpenAddMapLayer = 44L,
	dispidCloseAddMapLayer = 45L,
	dispidDeleteAllMapPoint = 46L,
	dispidIsInMapToolsPolygon = 47L,
	dispidSaveMapPoint = 48L,
	dispidSaveMapLine = 49L,
	dispidOpenMapEdit = 50L,
	dispidSetMapPolygonName = 51L,
	dispidSetMapPolygonColor = 52L,
	dispidSetMapAroundName = 53L,
	dispidSetMapAroundColor = 54L,
	dispidSetOnlineMap = 55L,
	dispidSaveMapText = 56L,
	dispidShowMapTool = 57L,
	eventidOnMapPointClick = 1L,
	eventidOnDrawLine = 2L,
	eventidOnDrawPolygon = 3L,
	eventidOnDrawLineEnd = 4L,
	eventidOnDrawPolygonEnd = 5L,
	eventidOnMapToolsLine = 6L,
	eventidOnMapToolsPolygon = 7L,
	eventidOnLoadEnd = 8L,
	eventidOnMapTollsRect = 9L,
	eventidOnGetMapBound = 10L,
	eventidOnMouseMap = 11L,
	eventidOnMapPointDbClick = 12L,
	eventidOnMapToolsDistance = 13L,
	eventidOnMessage = 14L,
	//}}AFX_DISP_ID
	};
public:
	void OnEventMessage( long message, long p1, long p2, const char* p3 );
private:
	HCURSOR		m_hCursorHand;//手型光标
	HCURSOR		m_hCursorArrow;//手型光标
	bool		m_bDbClicked;	//是否双击
	
	long		m_lID;
	int			m_iRet;

	long		m_lX;			//当前坐标X
	long		m_lY;			//当前坐标Y
	CDlgProperty*  m_pDlgProperty;
public:
	//定义地图引擎
	CMapEngine* m_pMapEngine;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMAPXCTL_H__FBF69BDD_0D18_431A_815E_2A448946A768__INCLUDED)
