/************************************************************
  �ļ���: shpFile.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ���Shp��shx��dbf �ļ���ȡ ʵ�ֶ�shp����Ĺ���
          ���ƹ���
  
  �ʼ���ַ��Visual20@sohu.com
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

/*ϵͳ������*/

#define FILE_READERR    -1 
#define FILE_CODEERR    -2 
#define FILE_VERSIONERR -3

//shp ����
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

	int iFileCode;      //�ļ���ʶ
	int iReserved[5];   //�����ֽ�
	int iFileLength;    //�ļ�����
	int iVersion;       //�汾��
	int iShpType;       //�ļ�����
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
	
	int iRecordNum;      //��¼��
	int iContentLength;  //��¼���ݳ���

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
	
	int ishpType;          //shp ����
	shpPoint Box[2];       //�����η�Χ 
	int iNumParts;         //�ֶ���
	int iNumPoints;        //shp�ܹ�������  

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