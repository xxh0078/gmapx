// MapPoiRes.h: interface for the CMapPoiRes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPOIRES_H__A5395871_AA9F_498F_8101_F015BA3BE420__INCLUDED_)
#define AFX_MAPPOIRES_H__A5395871_AA9F_498F_8101_F015BA3BE420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "../MapDisp/MapDisp.h"
#include"../MapBase/MapDefine.h"
//文件名字对应的Image
typedef VOS_EXPORT struct _MapRes
{ 
	CVOSImage*  pImage;
	string		strName;
} MapRes, *LPMapRes; 

class CMapPoiRes  
{
public:
	CMapPoiRes();
	virtual ~CMapPoiRes();
	//初始化
	bool Init( vchar* pRootPath );
	//释放
	void UnInit();
	//得到资源ID
	long GetResID( string strFileName );
	//得到文件名
	string GetResName( long sID );
	//绘制
	void DrawCenter( HDC hdc, long uid, VOSPoint ptCenter );
	void DrawCenter( HDC hdc, long uid, VOSPoint ptCenter, long lAngle );
	//void DrawAlphaDraw( HDC hdc, long uid, VOSPoint ptCenter, long alpha );
	//绘制
	void DrawPoiText( HDC hdc, long uid, VOSPoint ptCenter,string strText );
	//绘制
	void Draw( HDC hdc, long uid, VOSRect rc );
	//绘制
	void DrawAutoSize( HDC hdc, long uid, long left, long top );
	//得到大小
	bool GetSize( long uid, VOSSize& sz );
	//创建资源，如果是本地的，则直接加载，如果是服务器的，则为url，url以http开头
	long CreateRes( string strpath );
	//创建资源
	long CreateFileRes( string strpath );
	//绘制
	void DrawDelBtn( HDC hdc, long left, long top );
	//绘制
	void DrawAroundAlpha( HDC hdc, VOSPoint ptCenter, long radius, long alpha );
	//绘制
	void DrawRectAlpha( HDC hdc, VOSPoint ptCenter, long radius, long alpha );
private:
	//返回ResID
	long LoadImg( string strfilename );
	//加载全路劲
	long LoadImgFile( string strname );
	//下载资源
	bool DownLoadRes( string strurl, string strname );
public:
	long			m_idImgRect;
	long			m_idImgAround;
	long			m_idImgDelBtn;
private:
	vector<MapRes*> m_arrMapRes;
	string			m_strRoot;
};

#endif // !defined(AFX_MAPPOIRES_H__A5395871_AA9F_498F_8101_F015BA3BE420__INCLUDED_)
