// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_)
#define AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapData.h"

class CMapDown  
{
public:
	CMapDown();
	virtual ~CMapDown();
	
	//初始化,检测有没有现成的
	bool Init();

	//设置下载参数
	bool SetParam( string strMapName, int lMapType, int Minlevel, int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath, bool bWrite = true );
	
	//启动下载
	void Start( int nThreadNum = 5 );

	//停止下载
	void Stop( );

	//删除下载
	void Delete( );

	//是否正在下载
	bool IsDown(){return !m_bExitProc;};

	//下载线程
	static unsigned long __stdcall DownLoadProc( void* pParameter );

	//执行线程
	int Run();

	//添加
	bool AddMapData( string strPath );
	//添加
	bool CreateDBIndex();

	bool CheckMapData();
private:
	//读取配置文件
	bool ReadConf( string strFileName );
	//生成配置文件
	bool WriteConf( string strFileName );

	//获得载位置，已经下载返回TRUE，没有下载返回FALSE
	bool GetNextPosition( int& x, int& y, int& z );

	
	//得到下载路径
	//bool GetDownLoadURL( string& strURL, int x,int y,int z );
	//下载该文件
	bool DownLoad( const char* strURL, int x, int y, int z );

	//下载第一条数据
	bool DownFirstData();
private:
	//地图类型
	long		m_lMapType;
	//经纬度范围
	MapBount	m_mapBound;
	MBound		m_MBound20;
	MPoint		m_MapCenter20TopLeft;
	MPoint		m_MapCenter20BottomRight;
	//地图根路径
	string		m_strMapPath;
	string		m_strMapName;
	
	HANDLE		m_hDownMutex;				// 线程互斥区
	bool		m_bExitProc;
	bool		m_bFinish;
	//--
	char		m_strRootPath[256];
	
public:
	//下载范围
	CMapData	m_MapData;
};

#endif // !defined(AFX_MAPDOWN_H__76171BEF_2F0A_4FF3_9AEE_9A69AA7C3315__INCLUDED_)
