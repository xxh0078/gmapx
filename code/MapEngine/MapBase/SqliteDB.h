#pragma once
#include"../VOSBase/VOSDefine.h"
#include "../VOSBase/sqlite3.h"
#include "MapDefine.h"
#pragma comment( lib,"../MapEngine/VOSBase/sqlite3.lib" )
typedef  int (*callback)(void*,int,char**,char**);
class CSqliteDB
{
public:
	CSqliteDB(void);
	~CSqliteDB(void);
	//�����ݿ�ͱ�
	bool CreateDB( string strDBName,string strTableName );
	//���������ݿ�ͱ�
	bool OpenDB( string strDBName,string strTableName );
	//ɾ�����ݿ�
	bool RemoveDB();
	//bool OpenDB();
	void CloseDB();

	int BeginTansaction();
	int EndTansaction();
	//��������
	int CreateIndex();
	//��������
	int DeleteIndex();
	//д������
	int Write( MapBlockHead* pMapBlockHead );
	
	//д������
	int WriteEnd( MapBlockHead* pMapBlockHead );
	//��ѯ����
	int QueryData( int sLevel, int iNumX, int iNumY, callback sqlcallback );
	//��ѯ����
	int QueryData( callback sqlcallback );
private:
	sqlite3 *	m_db;
	//string		m_strDBName;
	string		m_strTableName;
};
