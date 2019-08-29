/************************************************************
  文件名: MapParts.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对多个点集合对象的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_PARTS_H_
#define _MAP_PARTS_H_

#include "MapPoints.h"

class CMapParts:public CObject {
	
	DECLARE_DYNAMIC(CMapParts)
public:
	CMapParts();
    CMapParts(CMapParts& Parts);
	~CMapParts();

//attribute
public:
	long GetCount();

//operation
public:
	void Add(CMapPoints* pPoints);
	void Set(long lindex, CMapPoints* pPoints);
	void Remove(long lindex);
	void Insert(long lindex, CMapPoints* pPoints);
	CMapPoints* Get(long lindex);
	void Clear();

private:
	CArray<CMapPoints*,CMapPoints*> m_Parts; //存储点集合对象

};

#endif //_MAP_PARTS_H_