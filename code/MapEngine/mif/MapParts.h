/************************************************************
  �ļ���: MapParts.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: �Զ���㼯�϶���Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
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
	CArray<CMapPoints*,CMapPoints*> m_Parts; //�洢�㼯�϶���

};

#endif //_MAP_PARTS_H_