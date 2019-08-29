#pragma once

#include "VOSDefine.h"

enum VOSFileOpenMode
{
	fomOnlyRead				= 0x0001,	// 只读
	fomOnlyWrite			= 0x0002,	// 只写
	fomReadWrite			= 0x0004,	// 读写
	fomShareOnlyRead		= 0x0100,	// 共享只读操作
	fomShareOnlyWrite		= 0x0200,	// 共享只写操作
	fomShareReadWrite		= 0x0400,	// 共享读写操作
	fomNoInherit			= 0x0080,	
	fomCreate				= 0x1000,	// 创建，如果文件存在，文件长度被清零。
	fomCreateNoTruncate		= 0x2000,	// 创建，如果文件存在，文件不被清空。
	fomTypeText				= 0x4000, // typeText and typeBinary are used in
	fomTypeBinary			= 0x8000, // derived classes only
};
enum VOSFileSeekPosition
{
	fspBegin	= 0x00,		// 首位置
	fspCurrent	= 0x01,		// 当前位置
	fspEnd		= 0x02,		// 尾位置
};
class VOS_EXPORT CVOSFile
{
public:
	CVOSFile(void);
	~CVOSFile(void);
//	bool Open( const vchar* strFileName,char* type );
	bool Open( const vchar* strFileName, int etype );
	int Write( void * buffer, int ilen);
	int Read( void * buffer, int ilen);
	
	/**
	  *	移动文件指针到指定的位置
	  *		@param lOffset [in] 移动位置的偏移量
	  *		@param posFrom [in] 移动位置的相对基准
	  *
	  *		@return 新的文件指针位置,函数失败返回-1.
	  */
	ulong Seek( long lOffset, VOSFileSeekPosition posFrom );

	/**
	  *	移动文件指针到指定的位置(扩展数据类型,支持64位)
	  *
	  *		@param llOffset    [in] 移动位置的偏移量
	  *		@param pNewPointer [in/out] 移动后的新的文件指针位置
	  *		@param posFrom	   [in] 移动位置的相对基准
	  *
	  *		@return 成功返回VOS_TRUE,否则返回VOS_FALSE.
	  *		@note	函数执行成功后，pNewPointer存放的是新的文件指针位置.
	  */
	bool SeekEx( long llOffset,long* pNewPointer, VOSFileSeekPosition posFrom );

	/** 移动文件指针到文件首部 */
	void SeekToBegin( );

	/**
	  *	移动文件指针到文件尾部
	  *		@return 返回移动后的文件指针位置,函数失败返回-1.
	  */	
	ulong SeekToEnd( );

	void Flush();
	void Close();
	ulong GetLength();
	void SetLength( ulong len );
	static bool Rename( const vchar* strOldName, const vchar* strNewName );
	static bool Remove( const vchar* strFileName );
	static bool CreateDirectory( const vchar* strFileName );
	static bool IsExit( const vchar* strFileName );
private:
//	bool Open( const vchar* strFileName,char* type );
	//FILE * fp;
	HANDLE m_hFile;
};
