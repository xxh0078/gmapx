
#ifndef	__VOS_DEFINE_H__
#define	__VOS_DEFINE_H__
// Windows Header Files:
// DLL动态输出宏
#if defined( _VOS_DLL )
#define VOS_EXPORT __declspec(dllexport)
#define VOS_IMPORT __declspec(dllimport)		
#else
#define VOS_EXPORT
#define VOS_IMPORT
#endif // _VOS_DLL

#pragma warning(disable: 4786)
//包含头文件
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//#include <afxwin.h>  
//
#include <list>
#include <vector>
#include<string>
#include <map>
using namespace std;

#ifndef PI
 #define PI 3.141592653589793f
#endif

//agg库
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_p.h"
#include "agg_renderer_scanline.h"
#include "agg_ellipse.h"
#include "agg_pixfmt_gray.h"
#include "agg_pixfmt_rgb.h"
#include "ctrl/agg_slider_ctrl.h"
#include "platform/agg_platform_support.h"

#include <agg_rendering_buffer.h> 
#include <agg_pixfmt_rgba.h>
#include <agg_renderer_base.h> 
#include <agg_rasterizer_scanline_aa.h>
#include <agg_scanline_p.h>
#include <agg_renderer_scanline.h>
#include <agg_rasterizer_scanline_aa.h>
#include <agg_path_storage.h>
#include <agg_conv_stroke.h>
#include <agg_vcgen_markers_term.h>
#include <agg_conv_bspline.h>
#include <agg_ellipse.h>
//
#include <agg_span_image_filter_gray.h>
#include <agg_span_image_filter_rgb.h>
#include <agg_span_image_filter_rgba.h>
#include <agg_span_pattern_gray.h>
#include <agg_span_pattern_rgb.h>
#include <agg_span_pattern_rgba.h>

#include <agg_conv_stroke.h> // conv_stroke
#include <agg_conv_dash.h> // conv_dash
#include <agg_conv_marker.h> // conv_marker
#include <agg_conv_curve.h> // conv_curve
#include <agg_conv_contour.h> // conv_contour
#include <agg_conv_smooth_poly1.h> // conv_smooth_poly1.h
#include <agg_conv_bspline.h> // conv_bspline
#include <agg_conv_transform.h> // conv_transform

// #include <afxtempl.h>
// #include <afxinet.h>
// Win32 消息值定义
#define	VOS_WM_QUIT				WM_DESTROY
#define VOS_WM_DESTROY			WM_DESTROY
#define VOS_IDOK				IDOK
#define VOS_IDCANCEL			IDCANCEL
#define VOS_WM_SETTINGCHANGE	WM_SETTINGCHANGE
#define VOS_WM_TIMER			WM_TIMER
#define VOS_WM_PAINT			WM_PAINT

#define VOS_WM_KEYDOWN			WM_KEYDOWN
#define VOS_WM_KEYUP			WM_KEYUP
#define VOS_WM_MOUSEMOVE		WM_MOUSEMOVE
#define VOS_WM_MOUSEWHEEL		WM_MOUSEWHEEL
#define VOS_WM_LBUTTONDOWN		WM_LBUTTONDOWN
#define VOS_WM_LBUTTONUP		WM_LBUTTONUP
#define VOS_WM_CHAR				WM_CHAR
#define VOS_WM_NCHITTEST		WM_NCHITTEST
#define VOS_WM_COMMAND			WM_COMMAND //(WM_USER+100) 
// 定义Win32平台的 数据类型处理宏
#define VOS_LOWORD(l)		((VOSWord)(l))	// 得到低字
#define VOS_HIWORD(l)       ((VOSWord)(((VOSDWord)(l) >> 16) & 0xFFFF))	// 高字低字
//类型重定义
#ifdef _UNICODE
	typedef	wchar_t		vchar;	// 重定义宽字节类型
#else
	typedef	char		vchar;	// 重定义宽字节类型
#endif
typedef	wchar_t		wchar;	// 重定义宽字节类型
typedef	unsigned long ulong;	// 重定义宽字节类型
typedef	unsigned int  uint;	// 重定义宽字节类型
typedef	unsigned long DWord;

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
// POINT 结构体定义
typedef VOS_EXPORT struct _vosPoint : public POINT
{ 
	_vosPoint()
	{
		x =0;
		y =0;
	}
	_vosPoint( long lx, long ly )
	{
		x = lx;	
		y = ly;
	}
	_vosPoint( DWORD dwPoint )
	{
		x = (short)LOWORD( dwPoint );
		y = (short)HIWORD( dwPoint );
	}
} VOSPoint, *LPVOSPoint; 


// SIZE 结构体定义
typedef struct VOS_EXPORT _vosSize : public SIZE
{ 
	_vosSize()
	{
		cx =0;
		cy =0;
	}
} VOSSize, *LPVOSSize; 

// RECT 结构体定义
typedef struct VOS_EXPORT _vosRect : public RECT
{ 
	_vosRect()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	long Width()
	{
		return right - left;
	}
	long width()
	{
		return right - left;
	}
	long height()
	{
		return bottom - top;
	}
	long Height()
	{
		return bottom - top;
	}
	VOSPoint CenterPoint()
	{
		VOSPoint pt;
		pt.x = left + width() / 2;
		pt.y = top + height() / 2;
		return pt;
	}
	bool IsPointIn( VOSPoint point )
	{
		if ( point.x < left )
			return false;
		if ( point.x >= right )
			return false;
		if ( point.y < top )
			return false;
		if ( point.y >= bottom )
			return false;
		return true;
	}
} VOSRect, *LPVOSRect; 

#endif		//__VOS_DEFINE_H__