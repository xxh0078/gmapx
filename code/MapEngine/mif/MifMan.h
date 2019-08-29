// MifMan.h: interface for the CMifMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIFMAN_H__254BEBAA_2732_4A0C_BD73_5757EDCD5A35__INCLUDED_)
#define AFX_MIFMAN_H__254BEBAA_2732_4A0C_BD73_5757EDCD5A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mifdefine.h"
#include "../MapLayer/MapLeyerMan.h"
class CMifMan  
{
public:
	CMifMan();
	virtual ~CMifMan();
	bool Init( CMapLeyerMan* pMapLeyerMan );
	bool loaddata( string strfile );
	bool loadmif(string strfile );
	bool loadmid(string strfile );
	bool LoadShp(string strfile );
private:
	bool ParaseRegion( char* pData, int nlen );
	bool ParasePoint( char* pData, int nlen );
	bool Parase( char* pData, int nlen );
public:
	vector<mifPoint> m_arrMidPoint;
	string	strVer;
	string strCharset;
	string strDelimiter;
	int iL;
	int iPl;
	int iR;

	int m_iID;
	CMapLeyerMan* m_pMapLeyerMan;
};

#endif // !defined(AFX_MIFMAN_H__254BEBAA_2732_4A0C_BD73_5757EDCD5A35__INCLUDED_)
