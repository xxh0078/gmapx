#pragma once

class CVOSCom
{
public:
	CVOSCom(void);
public:
	~CVOSCom(void);
	HANDLE ReOpenCom();
	HANDLE OpenCom( const char* lpszCom );
	void CloseCom();
	int Read(char* pBuf, unsigned long  ulLen );
	int Write(char* pBuf, unsigned long  ulLen );
	bool IsOpen();
private:
	HANDLE m_hCom;
	DCB		m_DCBInfo;
	COMMTIMEOUTS m_CommTimeouts;
	char   m_strName[6];
};
