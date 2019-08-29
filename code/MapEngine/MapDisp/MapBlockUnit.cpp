#include "StdAfx.h"
#include "MapBlockUnit.h"
#include "../VOSBase/VOSBase.h"
CMapBlockUnit::CMapBlockUnit(void)
{
	m_hBmp = NULL;
	m_memdc = NULL;
	m_VOSImage = NULL;
//	m_MarkImage = NULL;
//	bLoad = false;
	bDraw = false;
//	bDown = false;
}

CMapBlockUnit::~CMapBlockUnit(void)
{
	if( m_hBmp != NULL )
	{
		DeleteObject( m_hBmp );
		m_hBmp = NULL;
	}
	if( m_memdc != NULL )
	{
		DeleteDC( m_memdc );
		m_memdc = NULL;
	}
	if( m_VOSImage )
	{
		m_VOSImage->Release();
		delete m_VOSImage;
		m_VOSImage = NULL;
	}
	bDraw = false;
}
//初始化所有的数据块
/*void CMapBlockUnit::Init( HWND hwnd )
{
	if ( m_hBmp == NULL || m_memdc == NULL )
	{
		//::DeleteObject( m_hBmp );
		//m_hBmp = NULL;
		HDC hdc = ::GetDC( hwnd );
		m_hBmp = ::CreateCompatibleBitmap( hdc, 256, 256 );
		m_memdc = ::CreateCompatibleDC( hdc );
		::SelectObject( m_memdc,m_hBmp );
	}
}*/
///
void CMapBlockUnit::Draw( HDC hdc, short sStartX, short sStartY )
{
//	if( this->bLoad )
	{
		if( m_VOSImage && hdc )
		{
			m_VOSImage->Draw( hdc,sStartX,sStartY);
			//::MoveToEx(hdc,sStartX,sStartY,NULL );
			//::LineTo( hdc,sStartX+100,sStartY+100);
		}
		else
		{//AlphaBlend  使用alphe通道半透明贴图
		/*
		if ( m_hBmp == NULL || m_memdc == NULL )
		{
			m_hBmp = ::CreateCompatibleBitmap( hdc, 256, 256 );
			m_memdc = ::CreateCompatibleDC( hdc );
			::SelectObject( m_memdc,m_hBmp );
		}
		if( m_hBmp )
		::SetBitmapBits( m_hBmp,lWidth*lHeight*4, data );
			int alpha = 255 ;
			BLENDFUNCTION bf;   
			bf.BlendOp = AC_SRC_OVER;   
			bf.BlendFlags = 0;   
			bf.SourceConstantAlpha = alpha;   
			bf.AlphaFormat = AC_SRC_ALPHA;   
			AlphaBlend( hdc,lStartX,lStartY,lWidth,lHeight,m_memdc,0,0,lWidth,lHeight,bf );*/
/*
		
		BitBlt
			(
			hdc,
			lStartX,			// specifies the x-coordinate (in logical units) of the upper-left corner of the destination rectangle
			lStartY,			// specifies the y-coordinate (in logical units) of the upper-left corner of the destination rectangle
			lWidth,								// specifies the width (in logical units) of the destination rectangle
			lHeight,								// specifies the height (in logical units) of the destination rectangle
			m_memdc,								// specifies the source device context
			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			0,									// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
			//						width,								// specifies the width (in logical units) of the source rectangle
			//						height,								// specifies the height (in logical units) of the source rectangle
			SRCCOPY								// specifies the raster operation to be performed
			);*/
		return ;
		}
	}
}
//加载png数据
bool CMapBlockUnit::LoadPng( string strPath )//, HWND hwnd
{
	if( m_VOSImage )
	{
		m_VOSImage->Release();
		delete m_VOSImage;
		m_VOSImage = NULL;
	}
	bDraw = false;
	PngImage png;
 	try
     {
		 FILE *file=fopen( strPath.c_str(),"r");
		if ( !file )
		{
			return bDraw;
		}
		fclose( file );
        if ( png.load( strPath.c_str() ) )
		{
//			TRACE( "LoadPng ok " );
//			TRACE( "\r\n" );
			// get size
			lWidth  = png.getWidth();
			lHeight = png.getHeight();
			if ( lWidth != 256 || lHeight != 256 ) {
				DeleteFile( strPath.c_str() );
				return false;
			}
			// get blue, green, red and alpha
			if( data )
			{
				delete[] data;
				data = NULL;
			}
			data = png.getBGRA();
			//free memory first			
			bDraw = true;
			return true;
		}
		else
		{
			DeleteFile( strPath.c_str() );
			//CFile::Remove( Path );
			return false;
		}
     }
	catch( ... )
	// catch(CException* e)
 	{
		 DeleteFile( strPath.c_str() );
 		throw;
 		return false;
 	}  
	return bDraw;
}
bool CMapBlockUnit::LoadImg( char* pData, int len )
{
	if( m_VOSImage )
	{
		m_VOSImage->Release();
		delete m_VOSImage;
		m_VOSImage = NULL;
	}
	m_VOSImage = new CVOSImage(); 
	if( !m_VOSImage->LoadImage( pData, len ) )
	{
		return false;
	}
//	this->bLoad = true;
	return true;
}
//加载jpg数据
bool CMapBlockUnit::LoadImg( string strPath )
{
	if( m_VOSImage )
	{
		m_VOSImage->Release();
		delete m_VOSImage;
		m_VOSImage = NULL;
	}
	m_VOSImage = new CVOSImage(); 
	if( !m_VOSImage->LoadImage( strPath.c_str() ) )
	{
		return false;
	}
	bDraw = true;
	return true;
}
