#include "StdAfx.h"
#include "VOSImage.h"
//#include "PngImage.h"
#include "VOSUtil.h"
#pragma   comment(lib,"Msimg32.lib")
#pragma comment(lib,"../lib/zlib.lib ")
#pragma comment(lib,"../lib/png.lib")
#pragma comment(lib,"../lib/jpeg.lib")
#pragma comment(lib,"../lib/tiff.lib")
#pragma comment(lib,"../lib/jbig.lib")
#pragma comment(lib,"../lib/jasper.lib")
#pragma comment(lib,"../lib/mng.lib")
#pragma comment(lib,"../lib/libdcr.lib")
#pragma comment(lib,"../lib/cximage.lib")
//../../bin/cximagecrtd.dll
CVOSImage::CVOSImage(void)
{
	//image.Rotate(90,&smallImage);
	m_bLoad = false;
	image = NULL;
}

CVOSImage::~CVOSImage(void)
{
	Release();
}
bool CVOSImage::SetImage(CxImage *image1 )
{
	m_bLoad = false;
	Release();
	image = image1;
	if ( image->IsValid() )
	{
		m_size.cx = image->GetWidth();
		m_size.cy = image->GetHeight();
		m_bLoad = true;
	}
	return m_bLoad;
}
bool CVOSImage::LoadImage( char* buffer, int size )
{
	m_bLoad = false;
//	CVOSUtil::WdieCharToMultiByte( lpPathName, strPath, 256 );
	Release();
	image = new CxImage();
	if ( !image )
	{
		return false;
	}
 	try
 	{
		//CxMemFile memfile((BYTE*)buffer,size);
		if( !image->Decode((BYTE*)buffer,size,0) )
		{
			//memfile.Close();
			delete image;
			image = NULL;
			return false;
		}
		//memfile.Close();
 	}
 	catch ( ... )
 	{
 		
 	}
 /*	catch (CFileException* e)
 	{
 		
 	}
 	catch (CException* e)
 	{
 	}*/
	
	if ( image->IsValid() )
	{
		m_size.cx = image->GetWidth();
		m_size.cy = image->GetHeight();
		m_bLoad = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool CVOSImage::LoadImage( string strFileName )
{
	m_bLoad = false;
	if ( image )
	{
		image->Destroy();
		delete image;
		image = NULL;
	}
	image = new CxImage();
	if ( !image )
	{
		return false;
	}
 	try
 	{
		if( !image->Load( strFileName.c_str() ) )//, CXIMAGE_SUPPORT_JPG
		{
			return false;
		}
 	}
	catch( ... )//std::exception & ex
	{
	}
	/*
 	catch (CMemoryException* e)
 	{
 		
 	}
 	catch (CFileException* e)
 	{
 		
 	}
 	catch (CException* e)
 	{
 	}
	*/
	if ( image->IsValid() )
	{
		m_size.cx = image->GetWidth();
		m_size.cy = image->GetHeight();
		return true;
	}
	else
	{
		return false;
	}
	
//	if ( m_pngImage.load( lpPathName ) )
//	{
//		// get blue, green, red and alpha
//	//	unsigned char* data = png.getBGRA();
//		m_size.cx = m_pngImage.getWidth();
//		m_size.cy = m_pngImage.getHeight();
//		m_bLoad = true;
//		// free memory first
////		if ( m_hBmp != NULL )
////		{
////			::DeleteObject( m_hBmp );
////			m_hBmp = NULL;
////		}
////		if ( m_memdc != NULL )
////		{
////			::DeleteObject( m_memdc );
////			m_memdc = NULL;
////		}
////		HDC hdc = ::GetDC( hwnd );
////		m_hBmp = ::CreateCompatibleBitmap( hdc, width, height );
////		::SetBitmapBits( m_hBmp,width*height*4, data );
////		m_memdc = ::CreateCompatibleDC( hdc );
////		::SelectObject( m_memdc,m_hBmp );
////		m_size.cx = width;
////		m_size.cy = height;
//		// 		CDC* pDC = pWnd->GetDC();
//		// 		bitmap = new CBitmap;
//		// 		bitmap->CreateCompatibleBitmap( pDC, width, heigh );
//		// 		// set pixels
//		// 		bitmap->SetBitmapBits(width*heigh*4, data);
//		// 		memDC = new CDC; 
//		// 		memDC->CreateCompatibleDC( pDC );
//		// 		memDC->SelectObject(bitmap);
//		// 		lHeigh = heigh;
//		// 		lWidth = width;
//		return true;
//	}
//	else
//	{
////		TRACE( " LoadImage:" );
////		TRACE( lpPathName );
////		TRACE( "失败\r\n" );
////		if ( m_hBmp != NULL )
////		{
////			::DeleteObject( m_hBmp );
////			m_hBmp = NULL;
////		}
////		if ( m_memdc != NULL )
////		{
////			::DeleteObject( m_memdc );
////			m_memdc = NULL;
////		}
//		return false;
//	}
}
void CVOSImage::Draw( HDC hdc, long left, long top,long width, long height, RECT& rect )
{
	if ( image->IsValid() )
	{
//		TRACE( "xxh image->IsValid() left=%d,top=%d \r\n", left, top );
		//image->DrawLine( 0,0,100,100,RGB(0,255,0) );
		image->Draw( hdc, left, top , width, height,&rect );
	}
	return;
}
void CVOSImage::Draw( HDC hdc, long left, long top,long width, long height )
{
	if( !image )
		return ;
	if ( image->IsValid() )
	{
//		TRACE( "xxh image->IsValid() left=%d,top=%d \r\n", left, top );
		//image->DrawLine( 0,0,100,100,RGB(0,255,0) );
		//image->Rotate180( image );
		image->Draw( hdc, left, top , width, height );
	}
	return;
//		if (bPrinting) {
//			// get size of printer page (in pixels)
//		int cxPage = pDC->GetDeviceCaps(HORZRES);
//		int cyPage = pDC->GetDeviceCaps(VERTRES);
//		//int dcbpp = pDC->GetDeviceCaps(BITSPIXEL);
//		//int dcnc = pDC->GetDeviceCaps(NUMCOLORS);
//		//int dcp = pDC->GetDeviceCaps(PLANES);
//		// get printer pixels per inch
//		int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
//		int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
//		// Best Fit case: create a rectangle which preserves the aspect ratio
//		int cx=(ima->GetWidth()*cxInch)/ima->GetXDPI();
//		int cy=(ima->GetHeight()*cyInch)/ima->GetYDPI();
//		// print it!
//		/*HDC TmpDC=CreateCompatibleDC(pDC->GetSafeHdc());
//		HBITMAP bm =::CreateCompatibleBitmap(pDC->GetSafeHdc(), cx, cy);
//		HBITMAP oldbm = (HBITMAP)::SelectObject(TmpDC,bm);
//		BitBlt(TmpDC,0,0,cx,cy,0,0,0,WHITENESS);
//		ima->Draw(TmpDC,CRect(0,0,cx,cy));
//		BitBlt(pDC->GetSafeHdc(),100,100,cx,cy,TmpDC,0,0,SRCCOPY);
//		DeleteObject(SelectObject(TmpDC,oldbm));
//		DeleteDC(TmpDC);*/
//		CxImage tmp;
//		tmp.Copy(*ima);
//		RGBQUAD c={255,255,255,0};
//		tmp.SetTransColor(c);
//		tmp.AlphaStrip();
//		tmp.Stretch(pDC->GetSafeHdc(), CRect(100,100,cx,cy));
//		}
//		else if (pDoc->GetStretchMode()) {
//			CRect rect;
//			GetClientRect(&rect);
//			ima->Draw(pDC->GetSafeHdc(), rect);
//		} else {
//			float zoom=pDoc->GetZoomFactor();
//			if (zoom==1)
//				ima->Draw(pDC->GetSafeHdc());
//			else
//				ima->Draw(pDC->GetSafeHdc(),
//						CRect(0,0,(int)(ima->GetWidth()*zoom),(int)(ima->GetHeight()*zoom)));
//		}
//	}
//	return;
//	if ( m_bLoad ) 
//	{
//		BITMAPINFO bmi;        // bitmap header 
//		ZeroMemory(&bmi, sizeof(BITMAPINFO));
//		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//		bmi.bmiHeader.biWidth = width;
//		bmi.bmiHeader.biHeight = height;
//		bmi.bmiHeader.biPlanes = 1;
//		bmi.bmiHeader.biBitCount = 32;         // four 8-bit components 
//		bmi.bmiHeader.biCompression = BI_RGB;
//		bmi.bmiHeader.biSizeImage = width * height * 4;
//	}
//	if( m_memdc )
//	{
//		::BitBlt(hdc,
//			left,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			top,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			width,								// specifies the width (in logical units) of the destination rectangle
//			height,								// specifies the height (in logical units) of the destination rectangle
//			m_memdc,								// specifies the source device context
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			//						width,								// specifies the width (in logical units) of the source rectangle
//			//						height,								// specifies the height (in logical units) of the source rectangle
//			SRCCOPY								// specifies the raster operation to be performed
//			);
//	}
}
void CVOSImage::Draw( HDC hdc, long left, long top )
{
	Draw( hdc, left,top, m_size.cx,m_size.cy );
//	if( m_memdc )
//	{
//		::BitBlt(hdc,
//			left,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			top,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			m_size.cx,								// specifies the width (in logical units) of the destination rectangle
//			m_size.cy,								// specifies the height (in logical units) of the destination rectangle
//			m_memdc,								// specifies the source device context
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			//						width,								// specifies the width (in logical units) of the source rectangle
//			//						height,								// specifies the height (in logical units) of the source rectangle
//			SRCCOPY								// specifies the raster operation to be performed
//			);
//	}
}
void CVOSImage::Draw( HDC hdc, VOSRect rect )
{
	Draw( hdc, rect.left,rect.top,rect.width(),rect.height() );
}
void CVOSImage::AlphaDraw( HDC hdc, long left, long top,long width, long height,long alpha )
{
	if ( image->IsValid() )
	{
//		TRACE( "xxh image->IsValid() left=%d,top=%d \r\n", left, top );
		//image->AlphaSet(alpha);
		image->AlphaSetMax( alpha );
		image->Draw( hdc, left, top , width, height );
	}
}
void CVOSImage::AlphaDraw( HDC hdc, long left, long top )
{
	Draw( hdc, left,top, m_size.cx,m_size.cy );
//	if( m_memdc )
//	{
//		BLENDFUNCTION blend;
//		memset( &blend, 0, sizeof( blend) );
//		blend.BlendOp= AC_SRC_OVER;
//		blend.SourceConstantAlpha= 0; // 透明度 最大255
//		::AlphaBlend(hdc,
//			left,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			top,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			m_size.cx,								// specifies the width (in logical units) of the destination rectangle
//			m_size.cy,								// specifies the height (in logical units) of the destination rectangle
//			m_memdc,								// specifies the source device context
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			m_size.cx,//						width,								// specifies the width (in logical units) of the source rectangle
//			m_size.cy,//						height,								// specifies the height (in logical units) of the source rectangle
//			blend								// specifies the raster operation to be performed
//			);
//	}
}
void CVOSImage::DrawTransparent( HDC hdc, long left, long top )
{
	Draw( hdc, left,top, m_size.cx,m_size.cy );
//	if( m_memdc )
//	{
//		::BitBlt(hdc,
//			left,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			top,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
//			m_size.cx,								// specifies the width (in logical units) of the destination rectangle
//			m_size.cy,								// specifies the height (in logical units) of the destination rectangle
//			m_memdc,								// specifies the source device context
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
//			//						width,								// specifies the width (in logical units) of the source rectangle
//			//						height,								// specifies the height (in logical units) of the source rectangle
//			SRCAND								// specifies the raster operation to be performed
//			);
//	}
}
VOSSize	CVOSImage::GetSize()
{
	return m_size;
}
void CVOSImage::Release()
{
	if ( image )
	{
		image->Destroy();
		delete image;
		image = NULL;
	}
	m_bLoad = false;
}
//
bool CVOSImage::SaveJPEG( const char* strPath )
{
	if ( image )
	{
		image->IncreaseBpp(24);
		image->SetJpegQuality(80);
		image->Save( strPath,CXIMAGE_FORMAT_JPG);
		return true;
	}
	return false;
}
//图片旋转角度
void CVOSImage::Rotate( long lAngle,CVOSImage& imageNew )
{
	CxImage		*image1 = new CxImage();
	image->Rotate(lAngle,image1 );
	imageNew.SetImage( image1 );
}