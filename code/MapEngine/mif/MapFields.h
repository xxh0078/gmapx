/************************************************************
  文件名: MapFields.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对属性数据的单条记录管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/


#ifndef _MAP_FIELDS_H_
#define _MAP_FIELDS_H_

#include "MapField.h"

class CMapFields {

public:
	CMapFields();
    CMapFields(CMapFields& fields ); 
    ~CMapFields();

//Attribute
public:
	short GetCout();

//operation
public:
	void Add(CMapField* pField);
	void Remove(short sindex);
	void Insert(short sindex, CMapField* pField);
	CMapField *GetField(short sIndex);
	void Clear();

private:
	CArray<CMapField*,CMapField*> m_Fields; //存储字段
};

#endif //_MAP_FIELDS_H_