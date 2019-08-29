#pragma once
#include "../MapBase/MapBase.h"

class CMapBlockUnit
{
public:
	CMapBlockUnit(void);
	~CMapBlockUnit(void);
	//初始化所有的数据块
	//void Init( HWND hwnd );
	//绘制
	void Draw( HDC hdc,short sStart, short sStartY );
	//加载png数据
	bool LoadPng( string strPath );
	//加载jpg数据,-1为第一个数据加载失败，-2为第二层数据加载失败，>0为成功
	bool LoadImg( string strPath );
	bool LoadImg( char* pData, int len );
public:
//	MapBlockUnit m_mapBlock;		//地图块参数
//	long		lStartX;			//X方向起点位置
//	long		lStartY;			//Y方向起点位置
	bool		bDraw;				//这次是否需要绘制
	long		lLevel;				//比例尺
	long		lNumX;				//X方向编号
	long		lNumY;				//Y方向编号
	//bool		bLoad;				//是否加载
	//bool		bDown;				//是否下载
private:
	long		lWidth;
	long		lHeight;
	unsigned char* data;			//图片数据
	HBITMAP		m_hBmp;
	HDC			m_memdc;
	CVOSImage*  m_VOSImage;
};
