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
	//打开数据库和表
	bool CreateDB( string strDBName,string strTableName );
	//打开现有数据库和表
	bool OpenDB( string strDBName,string strTableName );
	//删除数据库
	bool RemoveDB();
	//bool OpenDB();
	void CloseDB();

	int BeginTansaction();
	int EndTansaction();
	//创建索引
	int CreateIndex();
	//创建索引
	int DeleteIndex();
	//写入数据
	int Write( MapBlockHead* pMapBlockHead );
	
	//写入数据
	int WriteEnd( MapBlockHead* pMapBlockHead );
	//查询数据
	int QueryData( int sLevel, int iNumX, int iNumY, callback sqlcallback );
	//查询数据
	int QueryData( callback sqlcallback );
private:
	sqlite3 *	m_db;
	//string		m_strDBName;
	string		m_strTableName;
};
