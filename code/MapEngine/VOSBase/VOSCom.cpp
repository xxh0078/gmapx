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
  * ��һ��com��  
  *		@param lpszCom		   [in] Ҫ�򿪵�com�����
  *		@param dwDesiredAccess [in] ����com�ڵĶ�д����,����ΪVOS_GENERIC_READ\VOS_GENERIC_WRITE
  *									�����
  *
  *		@return �ɹ�����VOS_TRUE,���򷵻�VOS_FALSE.
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
	/** ��com�� */
	m_hCom = ::CreateFile( m_strName, GENERIC_READ|GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if( m_hCom == INVALID_HANDLE_VALUE )
	{
		m_hCom = NULL;
		return m_hCom;
	}


	// ���ó�ʱ��Ϣ 	
	::GetCommTimeouts( m_hCom, &m_CommTimeouts );

	// Ĭ�ϳ�ʱ��Ϣ������
	m_CommTimeouts.ReadIntervalTimeout			= MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutMultiplier		= MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutConstant		= 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier	= 0;
	m_CommTimeouts.WriteTotalTimeoutConstant		= 0;
	
	
	// �������õ���Ϣд��
	if( !SetCommTimeouts( m_hCom, &m_CommTimeouts ) )
	{
		CloseCom();
		return 0;
	}

	//	����������Ϣ
	GetCommState( m_hCom, &m_DCBInfo );
	//m_COM.GetCommState( &DCBInfo );

	m_DCBInfo.DCBlength	= sizeof (DCB);
	m_DCBInfo.BaudRate	= 115200;

	// Ϊ�˱����������������DCB��Ϣ���õ�ԭ����״̬���ܻ�������⣬���ԭ�����ô��󣬿���Ҫ����
	// �ȳ��Ի���Ȼ���������û��趨������

	// ����COM��������Ϣ, ���ò��ɹ��򷵻�
	//if( !m_COM.SetCommState( &DCBInfo ) )
	if( !SetCommState( m_hCom,&m_DCBInfo ) )
	{
		CloseCom();
		return 0;
	}
	
	// ���ö˿ڼ��ӵ�����
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