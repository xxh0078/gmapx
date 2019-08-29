// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_)
#define AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
class CMapDown  
{
public:
	CMapDown();
	virtual ~CMapDown();
	//初始化临时文件,dir为下载目录
	void Init( CWnd* pWnd, float x1,float x2, float y1,float y2,long level, string strIndex );
	//启动下载
	void Start( );
	//停止下载
	void Stop( );
	//绘制显示参数
	void Draw( HDC hdc, int left,int top );
private:
	//获取谷歌常规地图
	bool GetMap(  int x, int y, int z  );
	//获得当前bound
	void GetLevelBound( int z );
	//创建比例尺路径
	void CreateLevelDir(int iLevel );
	//下载数据线程
	static unsigned long __stdcall DownLoadProc( void* pParameter );
	//获得上次下载位置
	bool GetDownPosition( int& x, int& y, int& z );
	//获得下载位置
	bool GetNextDownPosition( int& x, int& y, int& z );
	//保存下载位置
	void SaveDownPosition( int x, int y, int z );
private:
	//当前文件索引
	int m_ix;
	int m_iy;
	int m_iz;
	//转换后的范围
	int m_iMinX ;
	int m_iMaxX ;
	int m_iMinY ;
	int m_iMaxY ;

	bool m_bExitProc;
	bool m_bFirst;
	CWnd* m_pWnd;
	//经纬度范围
	MapBount m_mapBound;
	char	m_strRootPath[255];
	CString m_strView;
	CString m_strIndex;
};

#endif // !defined(AFX_MAPDOWN_H__AE67D5BF_E721_44F2_B12A_28E744252244__INCLUDED_)
