#pragma once
#include "../VOSBase/VOSBase.h"
#include "../MapBase/MapBase.h"
class CMapData;
struct tDownLoadParam
{
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
	int	iState;		//状态，0为等待下载，1为正在下载，2为下载完成,3为下载失败
	int iMapID;		//地图ID
	
	tDownLoadParam()
	{
		iX = 0;			//X
		iY = 0;			//Y
		iZ = 0;			//Y
		iState = 0;		//状态，0为等待下载，1为正在下载，2为下载完成,3为下载失败
		iMapID = 0;		//地图ID
	}
	const tDownLoadParam& operator=( const tDownLoadParam& param )
	{
		iX = param.iX;
		iY = param.iY;
		iZ = param.iZ;
		iState = param.iState;
		iMapID = param.iMapID;
		return * this;
	}
};

class CMapDataDown
{
public:
	CMapDataDown(void);
	~CMapDataDown(void);
	
	//初始化
	void Init( CMapData* pMapData );
	
	//设置类型
	bool SetMapType( en_MapType enMapType );
	
	//释放内存
	void Realse();

	//添加下载项到下载列表列表
	bool AddDownLoadList( int x, int y, int z,int iMapType );

	//从下载列表获取一个下载项，并置该下载项为下载状态
	bool GetNoDownLoadList( tDownLoadParam*& param );

	//得到一个正在下载的列表
	bool GetDownLoadList( tDownLoadParam*& param );

	//清除列表
	bool ClearDownLoadList();
	
	//清除没有开始下载的列表
	bool ClearNoDownLoadList();

	//下载线程
	static unsigned long __stdcall Worker( void* pParameter );
	int RUN();
private:
	//下载
	bool DownLoadMapData( short sLevel, long lNumX, long lNumY,int iMapID,struct MemoryStruct *chunk );
private:
	list<tDownLoadParam*>		m_listDownLoadParam;			//下载列表
	HANDLE						m_hLoadMutex;				// 线程互斥区
	bool		m_bExitProc;
	CMapData*	m_pMapData;
	en_MapType					 m_enMapType;				//地图类型
};
