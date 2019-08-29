/************************************************************
  文件名: MapLine.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对多义线对象的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/


#ifndef _MAP_LINE_H_
#define _MAP_LINE_H_

#include "MapParts.h"

class CMapLine:public CObject 
{
    
	DECLARE_DYNAMIC(CMapLine)
public:	
	CMapLine();
	CMapLine(CMapLine& mapline );
	~CMapLine();

//Attributes
public:
   long GetCount();
   CMapRectangle GetExtent();
   void SetExtent(CMapRectangle& exent);
   CMapParts* GetParts(long lIndex);
   double GetLength();
   double Distance(CMapPoint& pt );
   double ptToSegment(CMapPoint& pt,CMapPoint& ptStart,CMapPoint& ptEnd);

//operation
public:
	void Add(CMapParts* pParts);
	void Set(long lIndex , CMapParts* pParts);
	void SetIndex(unsigned int uiIndex ) { m_uiIndex = uiIndex ; }; 
	unsigned int GetIndex() { return m_uiIndex; }; 
	void Remove(long lIndex);
	void Insert(long lndex , CMapParts* pParts);
    void Clear();

private:
	unsigned int m_uiIndex;  //索引值
	CString m_csID;
	CMapRectangle m_Extent;
	CArray<CMapParts*,CMapParts*> m_Line; //存储点集合对象

};

#endif //_MAP_LINE_H_