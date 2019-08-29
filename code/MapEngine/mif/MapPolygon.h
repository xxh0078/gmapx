/************************************************************
  �ļ���: MapPolygon.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: �Զ���ζ���Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_POLYGON_H_
#define _MAP_POLYGON_H_

#include "MapParts.h"

class CMapPolygon:public CObject {

	DECLARE_DYNAMIC(CMapPolygon)
public:	
	CMapPolygon();
	CMapPolygon(CMapPolygon& mappolygon );
	~CMapPolygon();

//Attributes
public:
   long GetCount();
   CMapRectangle GetExtent();
   void SetExtent(CMapRectangle& exent);
   CMapParts* GetParts(long lIndex);
   double GetArea();

//operation
public:
	void Add(CMapParts* pParts);
	void Set(long lIndex , CMapParts* pParts);
	void SetIndex(unsigned int uiIndex ) { m_uiIndex = uiIndex ; }; 
	unsigned int GetIndex() { return m_uiIndex; }; 
	void Remove(long lIndex);
	void Insert(long lndex , CMapParts* pParts);
    void Clear();
	BOOL IsPointIn(CMapPoint& pt );
protected:
	BOOL isIntersect(CMapPoint& p1 , CMapPoint& p2 , CMapPoint& p3 , CMapPoint& p4 );
private:
	unsigned int m_uiIndex;  //����ֵ
	CMapRectangle m_Extent;
	CArray<CMapParts*,CMapParts*> m_Polygon; //�洢�㼯�϶���

};

#endif //_MAP_POLYGON_H_