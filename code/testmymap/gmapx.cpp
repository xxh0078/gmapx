// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "gmapx.h"

/////////////////////////////////////////////////////////////////////////////
// CGmapx

IMPLEMENT_DYNCREATE(CGmapx, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CGmapx properties

/////////////////////////////////////////////////////////////////////////////
// CGmapx operations

void CGmapx::SetMapURL(LPCTSTR mapurl)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 mapurl);
}

void CGmapx::SetMapLocPath(LPCTSTR mappath)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 mappath);
}

void CGmapx::MapZoomIn()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CGmapx::MapZoomOut()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CGmapx::GetMapScale()
{
	long result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CGmapx::SetMapScale(long scale)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 scale);
}

void CGmapx::MoveMap(double longitude, double latitude)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 longitude, latitude);
}

void CGmapx::ShowMap(double longitude, double latitude, long scale)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 longitude, latitude, scale);
}

long CGmapx::CreateICO(LPCTSTR path)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		path);
	return result;
}

BOOL CGmapx::CreateMapPoint(long pid, double longitude, double lanitude, LPCTSTR name, LPCTSTR text, long icoid)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8 VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pid, longitude, lanitude, name, text, icoid);
	return result;
}

long CGmapx::SetMapPoint(long pid, double lonitude, double lanitude)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, lonitude, lanitude);
	return result;
}

long CGmapx::SetMapPointName(long pid, LPCTSTR name)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, name);
	return result;
}

long CGmapx::SetMapPointText(long pid, double longitude, double lanitude, LPCTSTR text)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8 VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, longitude, lanitude, text);
	return result;
}

long CGmapx::SetMapPointICO(long pid, long icoid)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, icoid);
	return result;
}

long CGmapx::DeleteMapPoint(long pid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid);
	return result;
}

long CGmapx::CreateMapLine(long lid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid);
	return result;
}

long CGmapx::DeleteLine(long lid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid);
	return result;
}

long CGmapx::AddMapLinePoint(long lid, double longitude, double lanitude)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid, longitude, lanitude);
	return result;
}

long CGmapx::SetMapLineName(long lid, LPCTSTR name)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid, name);
	return result;
}

long CGmapx::SetMapLineColor(long lid, long colorbgr)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid, colorbgr);
	return result;
}

long CGmapx::SetMapLineWidth(long lid, long width)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lid, width);
	return result;
}

long CGmapx::CreateMapAround(long rid, double longitude, double lanitide, long radius, long alpha)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		rid, longitude, lanitide, radius, alpha);
	return result;
}

long CGmapx::DeleteMapAround(long rid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		rid);
	return result;
}

long CGmapx::CreateMapText(long tid, double longitude, double lanitude, LPCTSTR text, long size, long colorbgr)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8 VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		tid, longitude, lanitude, text, size, colorbgr);
	return result;
}

long CGmapx::DeleteMapText(long tid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		tid);
	return result;
}

void CGmapx::Invalidate()
{
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CGmapx::RemoveAllLayer()
{
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CGmapx::SetMapTextFont(long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		size, width, escapement, orientation, weight, Italic, underline, strikeOut, fontname);
	return result;
}

BOOL CGmapx::IsInMapBound(double longitude, double lanigude)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		longitude, lanigude);
	return result;
}

BOOL CGmapx::IsMapPointInMapCreen(double longitude, double lanitude)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		longitude, lanitude);
	return result;
}

long CGmapx::CreateMapPolygon(long pid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid);
	return result;
}

long CGmapx::DeletePolygon(long pid)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid);
	return result;
}

long CGmapx::AddMapPolygonPoint(long pid, double longitude, double lanitude)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, longitude, lanitude);
	return result;
}

double CGmapx::GetMapCenterX()
{
	double result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CGmapx::GetMapCenterY()
{
	double result;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

void CGmapx::MoveMapBound(double long1, double lan1, double long2, double lan2)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 long1, lan1, long2, lan2);
}

long CGmapx::SetMapTools(long type)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		type);
	return result;
}

void CGmapx::ClearMapTools()
{
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CGmapx::RegisterKey(LPCTSTR userkey)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		userkey);
	return result;
}

CString CGmapx::GetMapBound()
{
	CString result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CGmapx::GetMapOffSet(double lon, double lan)
{
	CString result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		lon, lan);
	return result;
}

void CGmapx::SetMapLevelBount(long minlevel, long maxlevel)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 minlevel, maxlevel);
}

void CGmapx::SetMapScaleBound(long scalemin, long scalemax)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 scalemin, scalemax);
}

long CGmapx::OpenAddMapLayer(LPCTSTR path)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		path);
	return result;
}

void CGmapx::CloseAddMapLayer()
{
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CGmapx::DeleteAllMapPoint()
{
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CGmapx::IsInMapToolsPolygon(double lon, double lan)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		lon, lan);
	return result;
}

long CGmapx::SaveMapPoint(double lon, double lan, LPCTSTR name, LPCTSTR text, long icoid)
{
	long result;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lon, lan, name, text, icoid);
	return result;
}

long CGmapx::SaveMapLine(LPCTSTR name, LPCTSTR mappoints, long width, long colorbgr)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		name, mappoints, width, colorbgr);
	return result;
}

long CGmapx::OpenMapEdit(long type, long id, BOOL bedit)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		type, id, bedit);
	return result;
}

long CGmapx::SetMapPolygonName(long pid, LPCTSTR name)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, name);
	return result;
}

long CGmapx::SetMapPolygonColor(long pid, long colorbgr)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pid, colorbgr);
	return result;
}

void CGmapx::SetMapAroundName(long rid, LPCTSTR name)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 rid, name);
}

long CGmapx::SetMapAroundColor(long rid, long colorbgr)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		rid, colorbgr);
	return result;
}

void CGmapx::SetOnlineMap(long lMapType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lMapType);
}

void CGmapx::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}