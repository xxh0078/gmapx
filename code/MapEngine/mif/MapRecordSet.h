/************************************************************
  文件名: MapRecordSet.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对Shp对象的属性数据记录集(DBF数据)的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_RECORDSET_H_
#define _MAP_RECORDSET_H_

#include "dbfFile.h"
#include "MapTableDesc.h"


#define MAX_CACH_SIZE 100   //最大缓存记录数


class CMapFields;

//记录集移动的位置
typedef enum {
	BookmarkCurrent,
	BookmarkFirst,
	BookmarkLast

} RECORDSTART;
class CMapRecordSet {

public:
    CMapRecordSet();
	~CMapRecordSet();

//ATTRIBUTE
public:
	long GetRecordCount();
	CMapFields* GetFields(long sIndex);
	CMapTableDesc* GetTableDesc();
	BOOL GetBOF();
	BOOL GetEOF();
	int  GetCacheSize();
    BOOL SetCacheSize(int& CacheSize);   
//opeeration
public:
	BOOL openDBF(CString& csFileName);
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void MovePrev();
	BOOL Move(int iNumRecords , RECORDSTART Start );
private:
	void Clear();
	void ReadRecord(unsigned long lRecordID);
private:
	CArray<CMapFields*,CMapFields*> m_Fields; //记录集缓冲区
	CMapTableDesc  m_TableDesc;
	int m_CacheSize;
	unsigned long iCursorPos;                //游标当前位置
	BOOL bBOF,bEOF;

private:
	 DBF_HEADER m_Header;          //存储DBF文件头
	 BOOL  m_bDbfOpen;             //数据库文件是否打开  
     CFile fDbf;  
};

//extern static void	SwapWord( int length, void * wordP );
#endif //_MAP_RECORDSET_H_
