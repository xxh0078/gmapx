// MapOffSet.h: interface for the CMapOffSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPOFFSET_H__A008B0D7_F0D6_493B_AE5E_084554569BD6__INCLUDED_)
#define AFX_MAPOFFSET_H__A008B0D7_F0D6_493B_AE5E_084554569BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../VOSBase/VOSBase.h"
struct MapOffSet
{
	long lxy;
	long loffsetx;
	long loffsety;
};

class CMapOffSet  
{
public:
	CMapOffSet();
	virtual ~CMapOffSet();
	bool Init( string strRootPath );
	bool GetMapOffSet( double& lon, double& lan );
	bool GetMapOffSetFromLoc( double& lon, double& lan );
	bool GetMapOffSetOnLine( double& lon, double& lan );
private:
	map<int, MapOffSet>m_mapMapOffSet;		//µØÍ¼¾ÀÆ«±í
	FILE*	m_file;
	int		m_iFileLen;
	int		m_iRowCount;
	int		m_iVariousCount;
};

#endif // !defined(AFX_MAPOFFSET_H__A008B0D7_F0D6_493B_AE5E_084554569BD6__INCLUDED_)
