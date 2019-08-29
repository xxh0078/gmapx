#pragma once
#include "MapBlockUnit.h"
#include "MapDataDown.h"
#include "MapData.h"
class CMapDisp;

class CLoadParam
{
public:
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
};
class CMapDispLayer
{
public:
	CMapDispLayer(void);
	~CMapDispLayer(void);
	//初始化所有的数据块
	void Create( CMapDisp* pMapDisp );
	//加载地图数据
	void LoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd, bool bZoom = true );
	//重新加载地图数据
	void ReLoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd );
	void OnMoveMap( int iDx, int iDy );
	void OnDraw( HDC hdc, int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd );

	//设置地图类型
	void SetMapType( en_MapType eMapType, string strRootPath, string strMapName = "", string strMapURL = "" );
	//设置地图路径
	void SetMapPath( string strMapPath );
	//得到地图文件路径
	void GetMapPath( int x,int y,int z,string& strMapPath );
	//加载其他数据
	void LoadMapOther();
private:
	//检查当前的绘制列表中是否存在改绘制参数
	bool CheckParamInDrawList( CMapBlockUnit* pBlockParam, int iLevel, int iMinX, int iMaxX, int iMinY, int iMaxY );
private:
	CMapData		m_MapData;
	CMapBlockUnit	m_MapBlockUnit[_BLOCK_MAX_NUM];
	int				m_iBlockCount;
	HWND			m_hwnd;
	int				m_iLevel;
	string			m_strRootPath;
	string			m_strMapURL;
	en_MapType	    m_enMapType;
	string			m_strMapPath;
	CMapDisp*		m_pMapDisp;
	MPoint			m_gptMapCenter;				//---
};
