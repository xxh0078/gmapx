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
//�ļ����ֶ�Ӧ��Image
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
	//��ʼ��
	bool Init( vchar* pRootPath );
	//�ͷ�
	void UnInit();
	//�õ���ԴID
	long GetResID( string strFileName );
	//�õ��ļ���
	string GetResName( long sID );
	//����
	void DrawCenter( HDC hdc, long uid, VOSPoint ptCenter );
	void DrawCenter( HDC hdc, long uid, VOSPoint ptCenter, long lAngle );
	//void DrawAlphaDraw( HDC hdc, long uid, VOSPoint ptCenter, long alpha );
	//����
	void DrawPoiText( HDC hdc, long uid, VOSPoint ptCenter,string strText );
	//����
	void Draw( HDC hdc, long uid, VOSRect rc );
	//����
	void DrawAutoSize( HDC hdc, long uid, long left, long top );
	//�õ���С
	bool GetSize( long uid, VOSSize& sz );
	//������Դ������Ǳ��صģ���ֱ�Ӽ��أ�����Ƿ������ģ���Ϊurl��url��http��ͷ
	long CreateRes( string strpath );
	//������Դ
	long CreateFileRes( string strpath );
	//����
	void DrawDelBtn( HDC hdc, long left, long top );
	//����
	void DrawAroundAlpha( HDC hdc, VOSPoint ptCenter, long radius, long alpha );
	//����
	void DrawRectAlpha( HDC hdc, VOSPoint ptCenter, long radius, long alpha );
private:
	//����ResID
	long LoadImg( string strfilename );
	//����ȫ·��
	long LoadImgFile( string strname );
	//������Դ
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
