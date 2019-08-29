#pragma once

#include "VOSFile.h"
class VOS_EXPORT CVOSUtil
{
public:
	CVOSUtil(void);
	~CVOSUtil(void);
	//���ֽ�ת��ΪUNICODE
	static int	MultiByteToWdieChar( char* lpMultiByteStr, wchar* lpWideCharStr, int iWideChar );
	// UNICODEת��Ϊ���ֽ�
	static int	WdieCharToMultiByte( wchar* lpWideCharStr,char* lpMultiByteStr, int iMultiByte );
	// �ѷ�UNICODE��UNICODE�ַ������
	static int	AddMultiByteToWideChar( wchar* lpWideCharStr, char* lpMultiByteStr );
	//�õ���ǰ�����ļ���
	static int  GetModuleFileName( vchar* lpszFilename, int dwSize );
	//
	static int UTF8ToGB2312( char *strUTF8, char* strDes, int nLen );
	/** 
	  *	��ʾ��Ϣ�Ի���
	  *		@param lpszText	   [in] ��ʾ����Ϣ����
	  *		@param lpszCaption [in] ��ʾ����Ϣ����
	  *		@param dwType      [in] ��Ϣ�Ի�������
	  *
	  *		@return	�Ի��򷵻�ֵ
	  *		@notes  hInst��Ŀǰ��Windowsƽ̨��Ч
	  */	
	static int MessageBox( const char* lpszText, char* lpszCaption );
	
	static void EncryptionString( char* str, int len, char* key );
	//д��־
	static void WriteLog( const char* strLog );
};
// �滻�ַ����е�ĳ���ַ�
int	STR_Replace( char* str,char chOld, char chNew );
//
string URLEncode(const string &sIn);

//�ַ����ָ��  
std::vector<std::string> STR_Split(std::string str,std::string pattern);