#pragma once
#include "../VOSBase/VOSDefine.h"
#include "MapDefine.h"

#define _BLOCK_SIZE 512

#define _LEVEL3_X	90
#define _LEVEL3_Y	40

#define _LEVEL4_X	45
#define _LEVEL4_Y	20

#define _BLOCK_MAX_NUM	1024

#define _MAP_MOVE_TIMER_PROC  0x00002000
#define _MAP_MOVE_TIMER		  50

#define _MAP_ZOOM_TIMER_PROC  0x00002001
#define _MAP_ZOOM_TIMER		  50

#define _ZOOM_MAX_COUNT	5


extern fun_msg			g_fun_msg;

//#define _MAP_MOVE_TIMER		  200
/*
*	��������
*/
struct tagZoomParam
{
	int		iZoomLevel;
	bool	bOnZoom;
	POINT	point;
	tagZoomParam()
	{
		iZoomLevel = 0;
		bOnZoom = false;
	}
	~tagZoomParam()
	{
		bOnZoom = false;
		iZoomLevel = 0;
	}
};

#include <math.h>
#define M_PI 3.1415926
//α��γ��תī����
MapPoint lonLat2Mercator(MapPoint lonLat,long temp );
//αī����ת��γ��
MapPoint Mercator2lonLat( MapPoint  mercator,long temp);

//α��γ��תī����
MapPoint lonLat2Mercator20(MapPoint lonLat );
//αī����ת��γ��
MapPoint Mercator2lonLat20( MapPoint  mercator );

//�����ļ���
bool EncryptionFileName( int t, int x, int y, int z , vchar*strFileEncryName,int iLen );


class CMapBase
{
public:
	CMapBase(void);
	~CMapBase(void);
	//��ʼ����̬��Դ
	static void Init( string strRootPath );
	//���õ�ͼ����
	static void SetMapType( en_MapType eMapType );
	//���õ�ͼ��Ŀ¼
	static void SetMapRootPath( string strRootPath );
	//�õ������Ŀ¼
	static void GetMapRootPath( string& strMapRootPath );
	//�õ���ͼ���͸�Ŀ¼
	static void GetMapTypePath( int iMapType, string& strMapTypePath );
	//��õ�ͼ�ļ�����·��
	static void GetMapDataEncryptionPath( int x, int y, int z, int iMapType, string& strRootPath );
	//��õ�ͼ�ļ�·��
	//static void GetMapDataPath( int x, int y, int z, string& strRootPath, int iLen );
	//��õ�ͼURL·��
	//static void GetMapUrl( int x, int y, int z, vchar* pUrl,int iLen );
	//���ݴ���ʱʹ�ñ�����ַ
	static void GetMapUrlBk( int x, int y, int z, char* strUrl, int iLen );
	//��ùȸ��ͼ��ǩ��
	static void GetMapUrlMark( int x, int y, int z, char* strUrl, int iLen );
	//�õ���������
	static void GetMapPoint( int nLevel, MPoint lonLat20, MPoint& lonLat );
	//�õ�20����������
	static void GetMapPoint20( int nLevel, MPoint lonLat, MPoint& lonLat20 );

	//�õ���������
	static void GetMapPoint( int nLevel, MapPoint lonLat,  MPoint& lonLatout );
	//�õ�20����������
	static void LonLat2MapPoint20( MapPoint lonLat, MPoint& lonLat20 );
	//�õ���γ������
	static void MapPoint2LonLat( MPoint lonLat20, MapPoint& lonLat );
	//ƫ��20����������
	static void OffsetMapPoint20( int nLevel, VOSPoint offest, VOSPoint& offest20 );
	//д��־
	static bool  WriteLog(string strLog);
	//���õ�ͼURL·��
	static void SetMapUrl(string strMapURL );
	//����2��֮��ľ���
	static double  GetLength(double x1, double y1, double x2, double y2);
	static double  GetArea( double* pdX, double* pdY, int iSize );
	static double AzimuthAngle(double x1,double y1,double x2,double y2);
	//��õ�ͼ�ļ�·��
//	void CMapBase::GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType )
	static void GetMapDataPath( int x, int y, int z, string& strMapFilePath, int iMapType );
	//��õ�ͼURL·��
	static void GetMapUrl( int x, int y, int z,int iMapType, char* strUrl, int iLen  );
	//�����ַ���
	static void EncryptionString(char* str);

	//���������ŷ�Χ
	static bool GetMapBlockBound( MBound& MapBound20,int nLevel, int& nMinX, int& nMaxX,int& nMinY, int& nMaxY );
	//������Ƿ��ڶ�����ڲ�
	static bool InPolygon( vector<MapPoint*>* arr, MapPoint mpt );
	static bool InPolygon( MapPoint mpt, MapPoint* polygon, int nCount );
	static double  GetArea(  vector<MapPoint*>* arr );
	static double  GetArea(  vector<MapPoint*>* arr, MapPoint* pMpt );
};
