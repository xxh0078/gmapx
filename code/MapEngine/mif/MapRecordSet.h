/************************************************************
  �ļ���: MapRecordSet.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ��Shp������������ݼ�¼��(DBF����)�Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_RECORDSET_H_
#define _MAP_RECORDSET_H_

#include "dbfFile.h"
#include "MapTableDesc.h"


#define MAX_CACH_SIZE 100   //��󻺴��¼��


class CMapFields;

//��¼���ƶ���λ��
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
	CArray<CMapFields*,CMapFields*> m_Fields; //��¼��������
	CMapTableDesc  m_TableDesc;
	int m_CacheSize;
	unsigned long iCursorPos;                //�α굱ǰλ��
	BOOL bBOF,bEOF;

private:
	 DBF_HEADER m_Header;          //�洢DBF�ļ�ͷ
	 BOOL  m_bDbfOpen;             //���ݿ��ļ��Ƿ��  
     CFile fDbf;  
};

//extern static void	SwapWord( int length, void * wordP );
#endif //_MAP_RECORDSET_H_
