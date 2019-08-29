// MapText.h: interface for the CMapText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_)
#define AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "MapPoiRes.h"
#include <string>
using namespace std;
class CMapDisp;
class CMapText  
{
public:
	CMapText();
	virtual ~CMapText();
	void Draw( HDC hdc, CMapDisp* pMapDisp );
	//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
	//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
	//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
	bool SetMapTextFont(long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname);
	long		tid;
	MapPoint	m_Point;
	string		text;
	long		color;//gbr
	long		m_size;
	long		m_width;
	long		m_escapement;
	long		m_orientation;
	long		m_weight;
	long		m_Italic;
	long		m_underline;
	long		m_strikeOut;
	LPCTSTR		m_fontname;

};

#endif // !defined(AFX_MAPTEXT_H__E29B9202_65E3_437A_8A12_FB16DF7250B2__INCLUDED_)
