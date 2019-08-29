/************************************************************
  �ļ���: MapTableDesc.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ���������ݵı�ṹ�Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_TABLEDESC_H_
#define _MAP_TABLEDESC_H_

#define INVALID_VALUE -1

#include "dbfFile.h"
/*typedef struct fieldDesc {
	
	CString csfdName;           //�ֶ�����  
	long    lfdType;            //�ֶ�����   
    short   sfdPression;        //�ֶξ��� 
	short   sfdLength;          //�ֶγ���
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
	CArray<FIELD_ELEMENT*,FIELD_ELEMENT*> m_fieldsDesc; //�洢��ṹ

};
#endif //_MAP_TABLEDESC_H_
