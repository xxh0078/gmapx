#include "StdAfx.h"
#include "VOSFile.h"
#include "VOSUtil.h"
//包含头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
CVOSFile::CVOSFile(void)
{
	m_hFile = NULL;
}

CVOSFile::~CVOSFile(void)
{
}
bool CVOSFile::Open( const vchar* strFileName, int dwOpenFlags )
{
	DWORD dwAccess = 0;
	SECURITY_ATTRIBUTES sa;
	DWORD dwCreateFlag;
//	HANDLE hFile = NULL;
//	char  pbuffer[512] = {0};
//	VOS_WdieCharToMultiByte( pusFileName,pbuffer,512 );


//	VOS_wcsreplace( pusFileName, '\\', '/' );
	switch (dwOpenFlags & 0x07)
	{
	case fomOnlyRead:
		dwAccess = GENERIC_READ;
		break;
	case fomOnlyWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case fomReadWrite:
		dwAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	case fomShareReadWrite:
		dwAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	default:
		//ASSERT(FALSE);  // invalid share mode
		;
	}
	// map share mode
	DWORD dwShareMode = 0;
	switch ( dwOpenFlags & 0x0f00 )    // map compatibility mode to exclusive
	{
	case fomShareOnlyRead:
		dwShareMode = FILE_SHARE_READ;
		break;
	case fomShareOnlyWrite:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case fomShareReadWrite:
		dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
		break;
	default:
		//ASSERT(FALSE);  // invalid share mode?
		dwShareMode	= 0;
	}

	// Note: typeText and typeBinary are used in derived classes only.

	// map modeNoInherit flag
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = ( dwOpenFlags & fomNoInherit ) == 0;

	// map creation flags
	if (dwOpenFlags & fomCreate )
	{
		if ( dwOpenFlags & fomCreateNoTruncate )
			dwCreateFlag = OPEN_ALWAYS;
		else
			dwCreateFlag = CREATE_ALWAYS;
	}
	else
		dwCreateFlag = OPEN_EXISTING;
	
	// 若需要写文件则修改文件属性
//	if( ( ( dwOpenFlags & fomOnlyWrite ) ||  ( dwOpenFlags & fomReadWrite) ) )
//	{
//		SetAttributesFileNotReadOnly( pusFileName );
//	}

	m_hFile = ::CreateFile( strFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
	
//	VOSPrint( pbuffer );
//	VOSPrint( " open file handle = %d \n",hFile );
	/** 判断句柄是否有效 */
	if (m_hFile == INVALID_HANDLE_VALUE)
	{	
		int error = ::GetLastError();
#if defined( DEBUG ) || defined( _DEBUG ) 
//	    VOSChar buf[VOS_MAX_PATH];					
//	    VOSUtil_WideCharToMultiByte( pusFileName, VOS_wcslen( pusFileName ), buf, VOS_MAX_PATH, 0 );
//		VOSUtil_MessageBox( buf, "File Error" );
//		ASSERT( 0 );
#endif //
		return FALSE;
	}
	
	return m_hFile;
	
}

int CVOSFile::Write( void * pBuffer, int dwCount)
{
	DWORD nWritten;
	if ( dwCount == 0 )
		return 0;     // avoid Win32 "null-write" option

#if defined( DEBUG ) || defined( _DEBUG ) 
	if( pBuffer == NULL || NULL == m_hFile )
	{
		//VOSUtil_MessageBox( "CVOSFile::Write fault!,Please Check!", "fatal error" );
		//VOS_ASSERT( 0 );
	}
#endif //
//	VOS_ASSERT( pBuffer != NULL );
//	VOS_ASSERT( NULL != hFile );

	/** VOS_ASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE)); */

	// Modified by shaoyongqiang 2009-2-4 当pBuffer指针不为NULL但是内容为空时，可能nWritten为空，这样就可能提示拔卡
	// ，因为写成功失败的判断依据从nWritten修改为根据::WriteFile判断。修改代码分析如此，还需要测试验证。
	// ::WriteFile( (HANDLE)m_hHandle, pBuffer, dwCount, &nWritten, NULL );
	// if( nWritten == 0 )
	if( !::WriteFile( (HANDLE)m_hFile, pBuffer, dwCount, &nWritten, NULL ) )
	{
		// Modified by shaoyongqiang 2009-2-4 end
		unsigned long ul = ::GetLastError( );
	//	CVOSUtil::MessageBox( strText,strCaption );
	//	::MessageBox( NULL , L"写文件失败，存储卡被拔出,软件将退出!" , L"System error" , MB_OKCANCEL );
	//	VOS_ASSERT( 0 );
		exit( 0 );
	}
	// Win32s will not return an error all the time (usually DISK_FULL)
	return nWritten;
}
int CVOSFile::Read( void * pBuffer, int dwCount)
{
	DWORD dwRead = 0;
	if ( dwCount == 0 )
		return 0;   // avoid Win32 "null-read"

#if defined( DEBUG ) || defined( _DEBUG ) 
	if( pBuffer == NULL || NULL == m_hFile )
	{
	//	VOSUtil_MessageBox( "CVOSFile::Read fault!,Please Check!","fatal error" );
		//ASSERT( 0 );
	}
#endif //
//	ASSERT(pBuffer != NULL);
//	ASSERT( NULL != m_hFile );
	if( ::ReadFile( m_hFile, pBuffer, dwCount, &dwRead, NULL ) )
	{
		// DWOED dwErr = ::GetLastError();
		return (int)dwRead;
	}
	else
	{
		return -1;
	}
	/** CFileException::ThrowOsError((LONG)::GetLastError()); */
	return dwRead;
}
void CVOSFile::Flush()
{
	if ( m_hFile == NULL )
		return;

	::FlushFileBuffers( m_hFile);
}
ulong CVOSFile::GetLength()
{
	DWORD dwLen, dwCur;
	// 得到文件当前位置
	dwCur = Seek( 0L, fspCurrent);
	// Seek操作失败，直接返回-1.
	if( -1 == dwCur )
		return -1;

	// 得到文件尾指针
	dwLen = SeekToEnd( );
	if( -1 == dwLen )
		return -1;

	Seek( dwCur, fspBegin );
	return dwLen;
}

void CVOSFile::SetLength( ulong len )
{
}
/**
  *	移动文件指针到指定的位置
  *		@param lOffset [in] 移动位置的偏移量
  *		@param posFrom [in] 移动位置的相对基准
  *
  *		@return 新的文件指针位置,函数失败返回-1.
  */
ulong CVOSFile::Seek( long lOffset, VOSFileSeekPosition posFrom )
{
	DWORD dwNew = 0;										// 文件指针位置
	//VOS_ASSERT( NULL != hFile );
	dwNew = ::SetFilePointer((HANDLE)m_hFile, lOffset, NULL, (DWORD)posFrom);
	return dwNew;
}

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
bool CVOSFile::SeekEx( long llOffset,long* pNewPointer, VOSFileSeekPosition posFrom )
{
	DWORD dwNew = 0;										// 文件指针位置的低32位
	long lHigh = (long)(llOffset >> 32);				// 文件指针位置的高32位
	//VOS_ASSERT( NULL != hFile );
	dwNew = ::SetFilePointer((HANDLE)m_hFile, (long)llOffset, &lHigh, (DWORD)posFrom);

	// 判断文件指针移动是否成功
	if ( dwNew  == (DWORD)-1 )
	{
		if( NO_ERROR != ::GetLastError() )
		return FALSE;
	}
	*pNewPointer = ( (long)lHigh << 32 ) + (long)dwNew;
	return TRUE;
}

/** 移动文件指针到文件首部 */
void CVOSFile::SeekToBegin( )
{
	::SetFilePointer( m_hFile, 0, NULL, FILE_BEGIN );
}

/**
  *	移动文件指针到文件尾部
  *		@return 返回移动后的文件指针位置,函数失败返回-1.
  */	
ulong CVOSFile::SeekToEnd( )
{
	DWORD dwNew = 0;
	dwNew = ::SetFilePointer( m_hFile, 0, NULL, FILE_END );
	return dwNew;
}
void CVOSFile::Close()
{
	if( NULL != m_hFile )
	{
	//	VOSPrint( " close file handle = %d \n",hFile );
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}
}	
bool CVOSFile::Rename( const vchar* strOldName, const vchar* strNewName )
{
	if( ::MoveFile( strOldName, strNewName ) )
		return true;
	else
		return false;
}

bool CVOSFile::Remove( const vchar* strFileName )
{
	if( ::DeleteFile( strFileName ) )
		return true;
	else
		return false;
}
bool CVOSFile::CreateDirectory( const vchar* strFileName )
{
	return ::CreateDirectory( strFileName,NULL );
}
bool CVOSFile::IsExit( const char* strFileName )
{
	FILE* f = fopen( strFileName,"r");
	if ( f ) {
		fclose(f);
		return true;
	}
	return false;
}