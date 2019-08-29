// MapPoiRes.cpp: implementation of the CMapPoiRes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapPoiRes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapPoiRes::CMapPoiRes()
{

}

CMapPoiRes::~CMapPoiRes()
{
	UnInit();
}
//初始化
bool CMapPoiRes::Init( vchar* pRootPath )
{
	m_strRoot = pRootPath;
	CreateDirectory( m_strRoot.c_str(),NULL);
	//string strFileName = this->m_strRoot + "del.png";
	//m_imgDelBtn.LoadImage( strFileName.c_str() );
	m_idImgDelBtn = LoadImg( _T("del.png") );
	m_idImgRect = LoadImg( _T("maprect.png") );
	m_idImgAround = LoadImg( _T("maparound.png") );
	LoadImg( _T("3.png") );
	LoadImg( _T("4.png") );
	LoadImg( _T("5.png") );
	LoadImg( _T("6.png") );
	LoadImg( _T("7.png") );
	LoadImg( _T("8.png") );
	/*
	LoadImg( pRootPath, _T("r0000.png") );
	LoadImg( pRootPath, _T("r0225.png") );
	LoadImg( pRootPath, _T("r0450.png") );
	LoadImg( pRootPath, _T("r0675.png") );
	LoadImg( pRootPath, _T("r0900.png") );
	LoadImg( pRootPath, _T("r1125.png") );
	LoadImg( pRootPath, _T("r1350.png") );
	LoadImg( pRootPath, _T("r1575.png") );
	LoadImg( pRootPath, _T("r1800.png") );
	LoadImg( pRootPath, _T("r2025.png") );
	LoadImg( pRootPath, _T("r2250.png") );
	LoadImg( pRootPath, _T("r2475.png") );
	LoadImg( pRootPath, _T("r2700.png") );
	LoadImg( pRootPath, _T("r2925.png") );
	LoadImg( pRootPath, _T("r3150.png") );
	LoadImg( pRootPath, _T("r3375.png") );
	LoadImg( pRootPath, _T("qr.png") );
	LoadImg( pRootPath, _T("rno.png") );
	LoadImg( pRootPath, _T("sr.png") );
	LoadImg( pRootPath, _T("demy.png") );
	*/
	return true;
}
//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
long CMapPoiRes::CreateRes( string strpath )
{
	int iret = -1;
	int pos = strpath.find("http",0,4);
	if ( pos == -1 ) {
		return LoadImg( strpath );
	}
	char strFileName[40] = {0};
	CMD5::GetMD5( (BYTE*)strpath.c_str(), strpath.length() , (BYTE*)strFileName );
	iret = LoadImg(strFileName);
	if ( iret >= 0 ) {
		return iret;
	}
	if( this->DownLoadRes( strpath, strFileName ) )
	{
		return LoadImg( strFileName );
	}
	return -1;
}
//创建资源
long CMapPoiRes::CreateFileRes( string strpath )
{
	return LoadImgFile( strpath );
}
//下载资源
bool CMapPoiRes::DownLoadRes( string strurl, string strname )
{
	//内存
	MemoryStruct chunk;
	int errcode= curl_httpget(strurl.c_str(),&chunk,NULL);
	if(!errcode)
	{
		if ( strstr( chunk.memory,"html" ) ){
			if(chunk.memory)
				free(chunk.memory);
			if(errcode)
			{
				return false;
			}
		}
		string strFileName = this->m_strRoot + strname;
		CVOSFile fileWrite; 
		if( fileWrite.Open( strFileName.c_str(),fomCreate | fomReadWrite))//"wb+"|fomReadWrite
		{
			fileWrite.Write( chunk.memory, chunk.size );
			fileWrite.Close();
			//AfxMessageBox("下载完毕");
			return true;
		}
		else
		{
			//AfxMessageBox("本地文件"+strWriteName+"打开出错."); 
			return false;
		}
	}
	if(chunk.memory)
		free(chunk.memory);
	return true;
}
//释放
void CMapPoiRes::UnInit()
{
	for ( int i=0;i<m_arrMapRes.size();i++ )
    {
		m_arrMapRes[i]->pImage->Release();
		delete m_arrMapRes[i]->pImage;
		delete m_arrMapRes[i];
    }
	m_arrMapRes.clear();
}
//得到资源ID
long CMapPoiRes::GetResID( string strFileName )
{
	MapRes* pMapRes = NULL;
	for ( int i=0;i<m_arrMapRes.size();i++ )
    {
		if( m_arrMapRes[i]->strName == strFileName )
		{
			return i;
		}
    }
	return 3;
}
//得到文件名
string CMapPoiRes::GetResName( long sID )
{
	if( sID >= m_arrMapRes.size() )
		return "";
	return m_arrMapRes[sID]->strName;
	return 0;
}
//绘制
void CMapPoiRes::DrawCenter( HDC hdc, long uid, VOSPoint pt )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return;
	}
	VOSSize sz = m_arrMapRes[uid]->pImage->GetSize();
	m_arrMapRes[uid]->pImage->AlphaDraw( hdc, pt.x-sz.cx/2, pt.y-sz.cy/2 );
}
void CMapPoiRes::DrawCenter( HDC hdc, long uid, VOSPoint ptCenter, long lAngle )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return;
	}
	CVOSImage imgNew;
	m_arrMapRes[uid]->pImage->Rotate( lAngle, imgNew );
	VOSSize sz = imgNew.GetSize();
	imgNew.AlphaDraw( hdc, ptCenter.x-sz.cx/2, ptCenter.y-sz.cy/2 );
}
//绘制
void CMapPoiRes::DrawPoiText( HDC hdc, long uid, VOSPoint pt,string strText )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return;
	}
	VOSSize sz = m_arrMapRes[uid]->pImage->GetSize();
	m_arrMapRes[uid]->pImage->AlphaDraw( hdc, pt.x-sz.cx/2, pt.y-sz.cy );
//	HPEN pen = CreatePen(PS_SOLID,1,RGB(0,0,0));
//	::SelectObject( hdc, pen );
	VOSRect rc;
	rc.top =  pt.y-sz.cy;
	rc.left = pt.x-sz.cx/2;
	rc.bottom =rc.top+sz.cy/2;
	rc.right = rc.left+sz.cx;
	int len = strText.length();
	SetTextColor( hdc,   RGB( 0, 0, 0 )   ); 
	::DrawText( hdc, strText.c_str(),len ,&rc,DT_LEFT);
}
//绘制
void CMapPoiRes::Draw( HDC hdc, long uid, VOSRect rc )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return;
	}
	m_arrMapRes.at( uid )->pImage->Draw( hdc, rc );
	//m_Image[uid].Draw( hdc, rc );
}
//绘制
void CMapPoiRes::DrawAroundAlpha( HDC hdc, VOSPoint ptCenter, long radius, long alpha )
{
	VOSRect rc;
	rc.left =   ptCenter.x - radius;
	rc.right =  ptCenter.x + radius;
	rc.top =    ptCenter.y - radius;
	rc.bottom = ptCenter.y + radius;
	m_arrMapRes.at( m_idImgAround )->pImage->AlphaDraw(hdc,ptCenter.x - radius,ptCenter.y - radius,2*radius,2*radius,alpha);

}
void CMapPoiRes::DrawAutoSize( HDC hdc, long uid, long left, long top )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return;
	}
	m_arrMapRes.at( uid )->pImage->Draw( hdc, left, top );
}
//加载
long CMapPoiRes::LoadImg( string strname )
{
	string strFileName = this->m_strRoot + strname;
	MapRes* res = new MapRes();
	res->pImage = new CVOSImage();
	if( res->pImage->LoadImage( strFileName.c_str() ) )
	{
		res->strName = strname;
		m_arrMapRes.push_back( res );
		return m_arrMapRes.size()-1;
	}
	delete res->pImage;
	delete res;
	return -1;
}
//加载全路径
long CMapPoiRes::LoadImgFile( string strname )
{
	string strFileName = strname;
	MapRes* res = new MapRes();
	res->pImage = new CVOSImage();
	if( res->pImage->LoadImage( strFileName.c_str() ) )
	{
		res->strName = strname;
		m_arrMapRes.push_back( res );
		return m_arrMapRes.size()-1;
	}
	delete res->pImage;
	delete res;
	return -1;
}
bool CMapPoiRes::GetSize( long uid, VOSSize& sz )
{
	if ( uid >= m_arrMapRes.size() || uid < 0 )
	{
		return false;
	}
	sz = m_arrMapRes.at( uid )->pImage->GetSize();
	return true;
}

//绘制
void CMapPoiRes::DrawDelBtn( HDC hdc, long left, long top )
{
	//m_imgDelBtn.Draw( hdc, left, top );
	this->DrawAutoSize( hdc,this->m_idImgDelBtn, left, top );
}