/************************************************************
  文件名: shpFile.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 完成Shp、shx、dbf 文件读取 实现对shp对象的管理及
          绘制工作
  
  邮件地址：Visual20@sohu.com
***********************************************************/


#ifndef _SHPFILE_H_
#define _SHPFILE_H_

#include "../MapLayer/MapLeyerMan.h"

#include "Global.h"
#include "MapRectangle.h"
//#include "MapLine.h"
//#include "MapPolygon.h"
//#include "MapRender.h"
#include "MapRecordSet.h"

#define FILE_VERSION 1000
#define MAX_BUFFER_SIZE 32768 /*32K*/

/*系统错误常量*/

#define FILE_READERR    -1 
#define FILE_CODEERR    -2 
#define FILE_VERSIONERR -3

//shp 类型
#define NULLSHP       0
#define POINT         1
#define POLYLINE      3
#define POLYGON       5
#define MULTIPOINT    8
#define POINTZ        11
#define POLYLINEZ     13
#define POLYGONZ      15
#define MULTIPOINTZ   18
#define POINTM        21
#define POLYLINEM     23
#define POLYGONM      25
#define MULTIPOINTM   28
#define MULTIPATCH    31 

#pragma pack(4) 


typedef struct  {

	int iFileCode;      //文件标识
	int iReserved[5];   //保留字节
	int iFileLength;    //文件长度
	int iVersion;       //版本号
	int iShpType;       //文件类型
	double dbXMin;
	double dbYMin;
	double dbXMax;
	double dbYMax;
	double dbZMin;
	double dbZMax;
	double dbMMin;
	double dbMMax;

} SHPHEADER;

typedef struct shpRecordHeader {
	
	int iRecordNum;      //记录数
	int iContentLength;  //记录内容长度

} SHPRECORDHEADER;

typedef struct shpPoint
{
	double dbX;
	double dbY;

} SHPPOINT;

typedef struct shpPtContent {
	
	int iShpType;
	double dbX;
	double dbY;

} SHPPTCONTENT;


typedef struct shxRecord {
	
	int iOffset;
	int iContentLength;

} SHXRECORD;

typedef struct shpInfo {
	
	int ishpType;          //shp 类型
	shpPoint Box[2];       //最大矩形范围 
	int iNumParts;         //分段数
	int iNumPoints;        //shp总共顶点数  

} SHPINFO;

class CMapLayer;

class CShpFile 
{
public:
    CShpFile();
	virtual ~CShpFile();

public:
	BOOL ReadShp(CString& csFileName);
	CMapRectangle GetExtent();
	void SetExtent(CMapRectangle& extent );
	int GetShpType( ) {return m_shpType;};
	void SetShpType(int& iShpType);
	int SearchShape(CMapPoint& pt );
//	void DrawShp(CDC*pDC ,  CMapRender* m_pRender , DrawParam& draw );
//	void FlashShp(CDC*pDC , DrawParam& draw , int iIndex);
protected:
	BOOL ReadRecord();
	BOOL GetRecordHeader(SHPRECORDHEADER& varHeader );
	BOOL GetShpInfo(SHPINFO& varInfo);
	int  ReadPoint(char* pszBuffer,int& iLength,BOOL& bEof); 
	int  SetRecordPos( int iRecord );
	BOOL ReadDBF(CString& csFileName);
private:
//	void DrawPoint(CDC*pDC ,  CMapRender* m_pRender , DrawParam& draw );
//	void DrawPointElement(CDC*pDC,CMapPoint *pPoint,DrawParam& draw );
//  void DrawPLine(CDC*pDC ,  CMapRender* m_pRender , DrawParam& draw );
//	void DrawPLineElement(CDC*pDC,CMapLine *pPline , DrawParam& draw );
///	void DrawPolygon(CDC*pDC ,  CMapRender* m_pRender , DrawParam& draw );
//	void DrawPolygonElement(CDC*pDC , CMapPolygon* pPolygon , DrawParam& draw );
private:
	BOOL bShpOpen,bShxOpen;
	BOOL m_bBigEndian; 
	CFile fShp,fShx;
	CMapRectangle m_Extent;
	CMapRecordSet *pRecordSet;
private:
	int m_shpFileLength;
	int m_shxFileLength;
	int m_iRecordCount;
	int m_shpType;
	CMapRectangle m_CurMapExtent;
	CObList m_ObList;
	vector<CMapPoint> m_arrShpPoint;
	CMapLeyerMan* m_pMapLeyerMan;
private:
	friend class CMapLayer;
	

};
#endif //_SHPFILE_H_