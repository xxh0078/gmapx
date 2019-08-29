
#ifndef	__MAP_DEFINE_H__
#define	__MAP_DEFINE_H__
#include "../VOSBase/VOSBase.h"
//��ͼ����ɫ
#define COLORRBG RGB(230,230,230)
//�Զ�����Ϣ
#define WM_DOWNLOAD_MESSAGE		(WM_USER+123) 
#define WM_MAPMOVE_MESSAGE		(WM_USER+125) 
#define WM_MAP_ZOOM_MESSAGE		(WM_USER+126)
#define WM_MAP_ONINIT			(WM_USER+127)
#define WM_MAP_TOOLS_MESSAGE	(WM_USER+128)
#define WM_MAP_POIINFO_MESSAGE	(WM_USER+129)
#define WM_MAP_DCCLICK_POIINFO_MESSAGE	(WM_USER+130)


#define _MAP_TIMER_PROC  0x00002000
#define _MAP_TIMER		  100
#define _MAP_TIMER_PROC1  0x00002001
#define _MAP_TIMER1		  500
#define _MAP_TIMER_PROC2  0x00002002
#define _MAP_TIMER2		  300

//
//ͨ����Ϣ��Ӧ
typedef  void ( *fun_msg )( long, long, long , const char* );
#define MAP_TOOL_MESSAGE	0x00000010				//��ͼ������Ϣ

//��ͼ�ṹ
typedef enum
{
	GMAP_GOOGLE_MAP = 0,			//�ȸ�һ���ͼ
	GMAP_GOOGLE_IMAGE = 1,			//�ȸ�Ӱ���ͼ
	GMAP_GOOGLE_MARK = 2,			//�ȸ�Ӱ��ע��ͼ��
	GMAP_GOOGLE_PHYSICAL  = 3,		//�ȸ���ε���ͼ
	GMAP_GOOGLE_IMAGEMARK  = 4,		//�ȸ���Ӱ��ͼ
	GMAP_BAIDU_MAP = 5,				//�ٶȵ�ͼ����
	GMAP_VM	= 6,					//VIRTUALEARTH
	GMAP_MYMAP = 7,					//���ص�ͼ
	GMAP_CHANGLIAN = 8,				//�����򷽵�ͼ����
	GMAP_MAPABC = 9,				//MapABC��ͼ
	GMAP_MAPBAR = 10,				//MAPBAR��ͼ
	GMAP_MAP365 = 11,				//MAP365��ͼ
	GMAP_TIANDT = 12,				//���ͼ
	GMAP_SUPERMAP = 13,				//��ͼ��ͼ
	GMAP_FILES = 14					//�ļ���ͼ
}en_MapType;

//��ͼ�ṹ
typedef enum
{
	MAP_POI_INFO = 0,			//POI��Ϣ
	MAP_POI_POINT = 1			//һ��POI��
}en_PoiType;

#define	_MAX_MAP_LEVEL_		19
#define	_MIN_MAP_LEVEL_		1

#define _MAX_PIXEL_20_ 134217728//20��һ�������,//�����ܳ�һ��Ϊ��20037508.34��

// POINT �ṹ�嶨��
typedef VOS_EXPORT struct _mPoint
{ 
	long lX;		// X ������
	long lY;		// Y ������
	_mPoint()
	{
		lX =0;
		lY =0;
	}
} MPoint, *LPMPoint; 

// MBOUND �ṹ�嶨��
typedef struct VOS_EXPORT _mBound
{ 
	long left;	//  ��
	long top;	//	��
	long right;	//	��
	long bottom; //	��
	_mBound()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	long width()
	{
		return right - left;
	}
	long height()
	{
		return bottom - top;
	}
	MPoint TopLeft()
	{
		MPoint pt;
		pt.lX = left;
		pt.lY = top;
		return pt;
	}
	MPoint BottomRight()
	{
		MPoint pt;
		pt.lX = right;
		pt.lY = bottom;
		return pt;
	}
} MBound, *LPMBound; 
// POINT �ṹ�嶨��
typedef VOS_EXPORT struct _mapPoint
{ 
	double x;		// X ������
	double y;		// Y ������
	_mapPoint(){
		x = 0;
		y = 0;
	}
} MapPoint, *LPMapPoint; 
//�߶�
struct	MapLineSegment   
{
	MapPoint   pt1;
	MapPoint	pt2;  
};
// POINT �ṹ�嶨��
typedef VOS_EXPORT struct _mapBound
{ 
	double left;		// X ������
	double top;			// X ������
	double right;		// Y ������
	double bottom;		// Y ������
	_mapBound()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	double Width()
	{
		return right - left;
	}
	double Height()
	{
		return bottom - top;
	}
	bool IsPointIn( MapPoint point )
	{
		if ( point.x < left )
			return false;
		if ( point.x >= right )
			return false;
		if ( point.y < bottom )
			return false;
		if ( point.y >= top )
			return false;
		
		return true;
	}
	MapPoint TopLeft()
	{
		MapPoint pt;
		pt.x = left;
		pt.y = top;
		return pt;
	}
	MapPoint BottomRight()
	{
		MapPoint pt;
		pt.x = right;
		pt.y = bottom;
		return pt;
	}
} MapBount, *LPMapBount; 

typedef struct _MapBlockUnit{
	long		lNumX;				//X������
	long		lNumY;				//Y������
	short		sLevel;				//������
    short		sFileID;			//�ļ�ID���ļ���ID����
	long		lFilePos;			//�ļ�λ��
	long		lFileSize;			//�ļ���С
}MapBlockHead;

typedef struct _MapBlockData{
	long		lNumX;				//X������
	long		lNumY;				//Y������
	short		sLevel;				//������
	char*		pData;				//����
	long		lDataLenth;			//��С
}MapBlockData;

#endif		//__MAP_DEFINE_H__