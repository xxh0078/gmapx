#pragma once
#ifndef	_VOS_IMAGE_
#define	_VOS_IMAGE_

#include "VOSDefine.h"
//#include "PngImage.h"
#include "../../include/cximage600_full/CxImage/ximage.h"
class CVOSImage;
class VOS_EXPORT CVOSImage
{
public:
	CVOSImage(void);
	~CVOSImage(void);
	bool SetImage(CxImage *image );
	bool LoadImage( string strFileName );
	bool LoadImage( char* buffer, int size );
	void Draw( HDC hdc, long left, long top );
	void Draw( HDC hdc, long left, long top,long width, long height );
	void Draw( HDC hdc, long left, long top,long width, long height, RECT& rect );
	void Draw( HDC hdc, VOSRect rect );
	void AlphaDraw( HDC hdc, long left, long top );
	void AlphaDraw( HDC hdc, long left, long top,long width, long height,long alpha );
	
	void DrawTransparent( HDC hdc, long left, long top );
	VOSSize	GetSize();
	void Release();
	//保存jpg文件
	bool SaveJPEG( const char* strPath );
	//图片旋转角度
	void Rotate( long lAngle,CVOSImage& imageNew );
public:
//	BITMAPINFO	m_bmpinfo;
	bool		m_bLoad;
//	PngImage	m_pngImage;
	CxImage		*image;				//main image
//	HBITMAP		m_hBmp;
//	HDC			m_memdc;
	VOSSize		m_size;
};
#endif // _VOS_IMAGE_