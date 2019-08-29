#include "StdAfx.h"
#include "SqliteDB.h"
CSqliteDB::CSqliteDB(void)
{
	m_db = NULL;
//	vector<CEndPoint*>	m_vEndPoint;
}

CSqliteDB::~CSqliteDB(void)
{
	CloseDB();
}
//打开数据库和表
bool CSqliteDB::CreateDB( string strDBName,string strTableName )
{
	m_strTableName = strTableName;
	char strSql[512];
    int rc;
	rc = sqlite3_open( strDBName.c_str(), &m_db); 
    if( rc )
	{ 
		this->CloseDB();
        return false;
    }
	//删除表和索引
    rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	sprintf( strSql,"DROP INDEX gmapindex1 ");
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
	sprintf( strSql,"DROP TABLE %s",m_strTableName.c_str() );
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 
	//创建数据表
	sprintf( strSql,"CREATE TABLE IF NOT EXISTS %s(maplevel int,mapx int,mapy int, fileid int, filepos int, filesize int )",m_strTableName.c_str() );
    rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 

	if (rc != SQLITE_OK)
    {
        this->CloseDB();
        return false;
    }
	return true;
}
bool CSqliteDB::OpenDB( string strDBName,string strTableName )
{
	m_strTableName = strTableName;
	char strSql[512];
    int rc;
	rc = sqlite3_open( strDBName.c_str(), &m_db); 
    if( rc )
	{ 
		this->CloseDB();
        return false;
    }
	//----
	sprintf( strSql,"CREATE TABLE IF NOT EXISTS %s(maplevel int,mapx int,mapy int, fileid int, filepos int, filesize int )",m_strTableName.c_str() );
    rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 

	if (rc != SQLITE_OK)
    {
        this->CloseDB();
        return false;
    }
	return true;
}
//删除数据库
bool CSqliteDB::RemoveDB()
{
	char strSql[512];
    int rc;
	//----
	sprintf( strSql,"DROP TABLE %s",m_strTableName.c_str() );
    rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 

	if (rc != SQLITE_OK)
    {
        this->CloseDB();
        return false;
    }
	return true;
}
//创建索引
int CSqliteDB::CreateIndex()
{
	if( !m_db )
	{
		return 0;
	}
	char strSql[512];
    int rc;
	sprintf( strSql,"CREATE INDEX gmapindex1 ON %s(maplevel, mapx, mapy);",m_strTableName.c_str() );
    rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 

	if (rc != SQLITE_OK)
    {
        this->CloseDB();
        return 0;
    }
	return rc;
}
//创建索引
int CSqliteDB::DeleteIndex()
{
	if( !m_db )
	{
		return 0;
	}
	char strSql[512];
	sprintf( strSql,"DROP INDEX gmapindex1 ");
    int rc;
	rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL); 
	rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 
	return rc;
}
void CSqliteDB::CloseDB()
{
	if( m_db )
	{
		sqlite3_close(m_db);
		m_db = NULL;
	}
}
int CSqliteDB::BeginTansaction()
{
	return sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
}
int CSqliteDB::EndTansaction()
{
	return sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 
}

int CSqliteDB::Write( MapBlockHead* pMapBlockHead )
{
	//char cFormatStr[25] = {0};   
	//sprintf(cFormatStr,"%04d-%02d-%02d %02d:%02d:%02d",pEndPoint->m_tmRecv.GetYear(),pEndPoint->m_tmRecv.GetMonth(),pEndPoint->m_tmRecv.GetDay(),pEndPoint->m_tmRecv.GetHour(),pEndPoint->m_tmRecv.GetMinute(),pEndPoint->m_tmRecv.GetSecond());  
	char strSql[512]={0};
	sprintf( strSql,"INSERT INTO %s(maplevel,mapx,mapy,fileid,filepos,filesize ) VALUES(%d,%d,%d,%d,%d,%d)",m_strTableName.c_str(),
		pMapBlockHead->sLevel,pMapBlockHead->lNumX,pMapBlockHead->lNumY,pMapBlockHead->sFileID,pMapBlockHead->lFilePos,pMapBlockHead->lFileSize );
	return sqlite3_exec(m_db, strSql, NULL, NULL, NULL);
}
//写入数据
int CSqliteDB::WriteEnd( MapBlockHead* pMapBlockHead )
{
	sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	char strSql[512]={0};
	sprintf( strSql,"INSERT INTO %s(maplevel,mapx,mapy,fileid,filepos,filesize ) VALUES(%d,%d,%d,%d,%d,%d)",m_strTableName.c_str(),
		pMapBlockHead->sLevel,pMapBlockHead->lNumX,pMapBlockHead->lNumY,pMapBlockHead->sFileID,pMapBlockHead->lFilePos,pMapBlockHead->lFileSize );
	sqlite3_exec(m_db, strSql, NULL, NULL, NULL);
	sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 
	return 1;
}
//批量写入
/*int CSqliteDB::Write( list<MapBlockData*> listMapBlock )
{
	
	char strSql[512]={0};
	int rc = sqlite3_exec(m_db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	sprintf( strSql,"INSERT INTO %s(maplevel,mapx,mapy,fileid,filepos,filesize ) VALUES(%d,%d,%d,%d,%d,%d)",m_strTableName.c_str(),
		pMapBlockHead->sLevel,pMapBlockHead->lNumX,pMapBlockHead->lNumY,pMapBlockHead->sFileID,pMapBlockHead->lFilePos,pMapBlockHead->lFileSize );
	rc = sqlite3_exec(m_db, strSql, NULL, NULL, NULL);
    rc = sqlite3_exec(m_db, "COMMIT TRANSACTION;", NULL, NULL, NULL); 
	return rc;
	return 1;
}*/
int CSqliteDB::QueryData( int sLevel, int iNumX, int iNumY, callback sqlcallback )
{
	char strSql[512]={0};
	sprintf( strSql,"select * from %s where maplevel = %d and mapx=%d and mapy=%d",
		m_strTableName.c_str(),sLevel,iNumX, iNumY );
	int rc = sqlite3_exec(m_db, strSql, sqlcallback, 0,NULL );
	return rc;
}
//查询数据
int CSqliteDB::QueryData( callback sqlcallback )
{
	char strSql[512]={0};
	sprintf( strSql,"select * from %s",m_strTableName.c_str() );
	int rc = sqlite3_exec(m_db, strSql, sqlcallback, 0,NULL );
	return rc;
}