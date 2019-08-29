// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MAP_DOWN_TASK_)
#define _MAP_DOWN_TASK_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../MapBase/MapBase.h"
#include "../VOSBase/VOSFile.h"
#include "../VOSBase/VOSURL.h"
#include "../VOSBase/MD5.h"
#include "../MapActive/MapActive.h"
#include "MapData.h"
class CMapDownParam
{
public:
	long lMapType;
	long Minlevel;
	long Maxlevel;
	long lLevel[20];
	float x1;
	float x2;
	float y1;
	float y2;
	char strMapPath[256];
	char strMapName[64];
	bool bFinish;
	void GetString( string& str )
	{
		char chTemp[512]={0};
		sprintf( chTemp, "%s_%d_%d_%f_%f_%f_%f_%s",strMapName,Minlevel,Maxlevel,x1,x2,y1,y2,strMapPath );
		str = chTemp;
	}
};
class CLevelParam
{
public:
	long	m_lMinX ;
	long	m_lMaxX ;
	long	m_lMinY ;
	long	m_lMaxY ;
	double  m_dCount;	//当前比例尺下需要下载的地图数据总数
	double	m_dPos;		//当前比例尺下已经下载的地图数量
	long	m_lx;		//当前比例尺下已经下载的X位置
	long	m_ly;		//当前比例尺下已经下载的Y位置
};

class CMapDownTask  
{
public:
	CMapDownTask();
	virtual ~CMapDownTask();

	//添加一个下载任务
	bool CreateTask( int lMapType, int Minlevel, int Maxlevel, float x1,float x2, float y1,float y2,string strMapPath,string strMapName );

	//删除任务
	bool DeleteTask( );
	
	//得到任务信息
	bool GetTask( int& lMapType, int& Minlevel, int& Maxlevel, float& x1,float& x2, float& y1,float& y2,string& strMapPath,string& strMapName );
	bool GetTaskParam( int nID, CMapDownParam& param );
	//启动下载
	void Start( int nThreadNum = 5 );

	//停止下载
	void Stop( );
	//暂停
	void Pause();

	//得到下载路径
	bool GetDownLoadPath( string& strURL, int &x,int &y,int &z );

	//得到地图数据路径
	void GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType  );
	//得到正在下载的位置
	void GetDownPos(int &x,int &y,int &z);
	//得到下载任务参数
	void GetMapDownParam(CMapDownParam& param);
	//下载线程
	static unsigned long __stdcall DownLoadProc( void* pParameter );

	//得到下载的地图路径
	void GetMapPath( string& strMapPath );

	//计算要下载的总的文件数量
	double GetDownLoadMaxCount();
	double GetDownLoadCount();
	//绘制显示内容
	void SetViewDC( HDC hdc );

	//检查数据
	bool CheckData();
private:

	//下载
	void DownLoad();
	
	//写日志
	void WriteLog(const char* pLog );
	//获取谷歌常规地图
	bool GetMap(  int x, int y, int z, int iMapType  );

	//获得当前bound
	void GetLevelBound( int z );

	//创建比例尺路径
	void CreateLevelDir(int iLevel );

	//检查已经下载的地图数据信息
	bool CheckedMapData( char* strPath );

	//获得上次下载位置
	//bool GetDownPosition( int& x, int& y, int& z );

	//获得下载位置
	bool GetNextDownPosition( int& x, int& y, int& z );

	//保存下载位置
	//void SaveDownPosition( int x, int y, int z );

	//下载文件
	bool DownLoad( string& strURL, int x, int y, int z );
	//是否停止下载
	bool IsStop();
	//绘制下载位置
	void DrawDownPos();
private:
	//当前文件索引
	int m_ix;
	int m_iy;
	int m_iz;

	//地图类型
	//en_MapType	    m_enMapType;
	//转换后的范围
	int m_iMinX ;
	int m_iMaxX ;
	int m_iMinY ;
	int m_iMaxY ;

	//比例尺范围
	int m_iMinLevel;
	int m_iMaxLevel;
	//经纬度范围
	MapBount m_mapBound;
	MBound	 m_MBound20;
	MPoint	 m_MapCenter20TopLeft;
	MPoint	 m_MapCenter20BottomRight;
	//地图根路径
	string	m_strMapPath;
	string	m_strMapTaskPath;
	string	m_strMapName;
	//写日志
	char     m_pLog[256];
	CVOSFile m_fileLog;
	bool     m_bLog;
	//地图类型
	long     m_lMapType;
	//线程互斥区
	HANDLE	m_hDownLoadMutex;				// 线程互斥区
	bool	m_bExitProc;
	int		m_nState;						//状态
	CLevelParam m_LevelParam[20];			//每一层需要的下载数量和参数
	double		m_dMaxCount;				//总的下载数量
	double		m_dCount;					//总的下载数量
	CMapData	m_MapData;
public:
	bool		m_bFinish;					//下载是否完成
};

#endif // !defined(_MAP_DOWN_TASK_)
