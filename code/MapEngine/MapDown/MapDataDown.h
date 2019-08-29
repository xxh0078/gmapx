#pragma once
#include "../VOSBase/VOSBase.h"
class CMapDisp;
//#include <windows.h>
class CDownLoadParam
{
public:
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
	int	iState;		//状态，0为等待下载，1为正在下载，2为下载完成
	int iMapID;		//地图ID
};

class CMapDataDown
{
public:
	CMapDataDown(void);
	~CMapDataDown(void);
	//初始化
	void Init( CMapDisp* pMapDisp );
	//释放
	void realse();

	//添加下载项到下载列表列表
	bool AddDownLoadList( int x, int y, int z,int iMapType );

	//从下载列表获取一个下载项，并置该下载项为下载状态
	bool GetNoDownLoadList( CDownLoadParam*& param );

	//得到一个正在下载的列表
	bool GetDownLoadList( CDownLoadParam*& param );

	//删除一个下载项
	bool RemoveDownLoadList( int x, int y, int z );

	//清除列表
	bool ClearDownLoadList();
	
	//清除没有开始下载的列表
	bool ClearNoDownLoadList();

	//重命名下载后的文件名
	bool RenameDownLoadFile( CDownLoadParam* pParam );

	//
	bool bLoacked();

	//下载线程
	static unsigned long __stdcall DownLoadProc( void* pParameter );

private:
	//获取谷歌常规地图
	bool DownLoadMap( CDownLoadParam* pParam, struct MemoryStruct *chunk );
	
public:
	//下载列表
	list<CDownLoadParam*>	m_arrDownLoadParam;		//下载列表
//	CDownLoadParam	m_DownLoadParam[100];			//等待下载列表
//	int				m_iDownLoadCount;				//等待下载列表数量
	//
	HANDLE			m_hDownLoadMutex;				// 线程互斥区
//	CRITICAL_SECTION	m_cs;						// 临界区
public:
	CMapDisp*       m_pMapDisp;						// 地图显示类
};
