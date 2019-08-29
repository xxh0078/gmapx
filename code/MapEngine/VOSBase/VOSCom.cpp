#include "StdAfx.h"
#include "VOSCom.h"

CVOSCom::CVOSCom(void)
{
	memset( m_strName,0,6 );
	m_hCom = NULL;
}

CVOSCom::~CVOSCom(void)
{
	this->CloseCom();
}
bool CVOSCom::IsOpen()
{
	if( m_hCom )
		return true;
	else
		return false;
}
/**
  * 打开一个com口  
  *		@param lpszCom		   [in] 要打开的com口序号
  *		@param dwDesiredAccess [in] 设置com口的读写属性,可以为VOS_GENERIC_READ\VOS_GENERIC_WRITE
  *									的组合
  *
  *		@return 成功返回VOS_TRUE,否则返回VOS_FALSE.
  */
HANDLE CVOSCom::OpenCom( const char* lpszCom )
{
	if( lpszCom != NULL )
	{
		if( strlen( lpszCom ) > 5 )
			return NULL;
		else
			strcpy( m_strName, lpszCom );
	}
	if( strlen( m_strName ) < 4 )
		return NULL;
	/** 打开com口 */
	m_hCom = ::CreateFile( m_strName, GENERIC_READ|GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if( m_hCom == INVALID_HANDLE_VALUE )
	{
		m_hCom = NULL;
		return m_hCom;
	}


	// 配置超时信息 	
	::GetCommTimeouts( m_hCom, &m_CommTimeouts );

	// 默认超时信息的设置
	m_CommTimeouts.ReadIntervalTimeout			= MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutMultiplier		= MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutConstant		= 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier	= 0;
	m_CommTimeouts.WriteTotalTimeoutConstant		= 0;
	
	
	// 将新设置的信息写入
	if( !SetCommTimeouts( m_hCom, &m_CommTimeouts ) )
	{
		CloseCom();
		return 0;
	}

	//	配置连接信息
	GetCommState( m_hCom, &m_DCBInfo );
	//m_COM.GetCommState( &DCBInfo );

	m_DCBInfo.DCBlength	= sizeof (DCB);
	m_DCBInfo.BaudRate	= 115200;

	// 为了保险起见，重新设置DCB信息，得到原来的状态可能会出现问题，如果原来设置错误，可能要重起
	// 先初试化，然后再设置用户设定的数据

	// 配置COM口连接信息, 配置不成功则返回
	//if( !m_COM.SetCommState( &DCBInfo ) )
	if( !SetCommState( m_hCom,&m_DCBInfo ) )
	{
		CloseCom();
		return 0;
	}
	
	// 设置端口监视的类型
	SetCommMask( m_hCom,EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING | EV_PERR );

	return m_hCom;
}
HANDLE CVOSCom::ReOpenCom()
{
	CloseCom();
	return OpenCom( m_strName );
}
void CVOSCom::CloseCom()
{
	if( m_hCom )
	{
		::CloseHandle( m_hCom );
		m_hCom = NULL;
	}
}
int CVOSCom::Read(char* pBuf, unsigned long  ulLen )
{
	DWORD dwLen = 0;
	if( !::ReadFile( m_hCom, pBuf, ulLen, &dwLen, 0 ) )
	{
		::CloseHandle( m_hCom );
		m_hCom = NULL;
	}
	return dwLen;
}
int CVOSCom::Write(char* pBuf, unsigned long  ulLen )
{
	DWORD dwLen = 0;
	if( ::WriteFile( m_hCom, pBuf, ulLen, &dwLen, 0 ) )
	{
		return dwLen;
	}
	else
	{
		::CloseHandle( m_hCom );
		m_hCom = NULL;
	}
	return 0;
}