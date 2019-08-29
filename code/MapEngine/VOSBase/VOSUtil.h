#pragma once

#include "VOSFile.h"
class VOS_EXPORT CVOSUtil
{
public:
	CVOSUtil(void);
	~CVOSUtil(void);
	//多字节转换为UNICODE
	static int	MultiByteToWdieChar( char* lpMultiByteStr, wchar* lpWideCharStr, int iWideChar );
	// UNICODE转换为多字节
	static int	WdieCharToMultiByte( wchar* lpWideCharStr,char* lpMultiByteStr, int iMultiByte );
	// 把非UNICODE和UNICODE字符串相加
	static int	AddMultiByteToWideChar( wchar* lpWideCharStr, char* lpMultiByteStr );
	//得到当前程序文件名
	static int  GetModuleFileName( vchar* lpszFilename, int dwSize );
	//
	static int UTF8ToGB2312( char *strUTF8, char* strDes, int nLen );
	/** 
	  *	显示消息对话框
	  *		@param lpszText	   [in] 显示的消息内容
	  *		@param lpszCaption [in] 显示的消息标题
	  *		@param dwType      [in] 消息对话框类型
	  *
	  *		@return	对话框返回值
	  *		@notes  hInst对目前的Windows平台有效
	  */	
	static int MessageBox( const char* lpszText, char* lpszCaption );
	
	static void EncryptionString( char* str, int len, char* key );
	//写日志
	static void WriteLog( const char* strLog );
};
// 替换字符串中的某个字符
int	STR_Replace( char* str,char chOld, char chNew );
//
string URLEncode(const string &sIn);

//字符串分割函数  
std::vector<std::string> STR_Split(std::string str,std::string pattern);