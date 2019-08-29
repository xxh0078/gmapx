/************************************************************
  文件名: MapTableDesc.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对属性数据的表结构的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_TABLEDESC_H_
#define _MAP_TABLEDESC_H_

#define INVALID_VALUE -1

#include "dbfFile.h"
/*typedef struct fieldDesc {
	
	CString csfdName;           //字段名称  
	long    lfdType;            //字段类型   
    short   sfdPression;        //字段精度 
	short   sfdLength;          //字段长度
	short   sfdScale;

} FIELDDESC*/;

class CMapTableDesc {

public:
	CMapTableDesc();
    CMapTableDesc(CMapTableDesc& tblDesc);
	~CMapTableDesc();

public:
	short GetFieldCount();
	void SetFieldCount(short);
	
// Operations
public:
	CString GetFieldName(short index);
	void SetFieldName(short index, LPCTSTR lpszNewValue);
	long GetFieldType(short index);
	void SetFieldType(short index, long nNewValue);
	short GetFieldPrecision(short index);
	void SetFieldPrecision(short index, short nNewValue);
	short GetFieldLength(short index);
	void SetFieldLength(short index, short nNewValue);
	short GetFieldScale(short index);
	void SetFieldScale(short index, short nNewValue);
    FIELD_ELEMENT *GetDesc(short sIndex);
	void Add(FIELD_ELEMENT* pField);
	void Remove(short sindex);
	void Insert(short sindex, FIELD_ELEMENT* pField);
	void Clear();

private:
	CArray<FIELD_ELEMENT*,FIELD_ELEMENT*> m_fieldsDesc; //存储表结构

};
#endif //_MAP_TABLEDESC_H_
