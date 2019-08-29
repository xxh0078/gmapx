#include "StdAfx.h"
#include "VOSUtil.h"
//#include <windows.h>
CVOSUtil::CVOSUtil(void)
{
}

CVOSUtil::~CVOSUtil(void)
{
}
//多字节转换为UNICODE
int	CVOSUtil::MultiByteToWdieChar( char* lpMultiByteStr, wchar* lpWideCharStr, int iWideChar )
{
	int i = ::MultiByteToWideChar( CP_ACP, 0, lpMultiByteStr, strlen( lpMultiByteStr),
		lpWideCharStr, iWideChar );

	lpWideCharStr[i] = '\0';
	return i;
}
// UNICODE转换为多字节
int	CVOSUtil::WdieCharToMultiByte( wchar* lpWideCharStr,char* lpMultiByteStr, int iMultiByte )
{
	int i = ::WideCharToMultiByte( CP_ACP, 0, lpWideCharStr, wcslen( lpWideCharStr )
		, lpMultiByteStr, iMultiByte, 0, 0 );	
	lpMultiByteStr[i] = '\0';
	return i;
}
//
int CVOSUtil::UTF8ToGB2312( char *strUTF8, char* strDes, int nLen )
{
	WCHAR *strSrc = NULL;
	TCHAR *szRes = NULL; 
	int i = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);  
	strSrc = new WCHAR[i+1];
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, strSrc, i);  // Unicode转换成GB2312 
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);   
	szRes = new TCHAR[i+1]; 
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL); 
	strcpy( strDes, szRes );
	if (strSrc != NULL)  
	{
		delete []strSrc; 
		strSrc = NULL;
	}

	if (szRes != NULL)
	{
		delete []szRes;
		szRes = NULL;  
	}
	return 1;
}
// 把非UNICODE和UNICODE字符串相加
int	CVOSUtil::AddMultiByteToWideChar( wchar* lpWideCharStr, char* lpMultiByteStr )
{
	int iLen = 0;
	iLen = wcslen( lpWideCharStr );
	iLen += CVOSUtil::MultiByteToWdieChar( lpMultiByteStr,&lpWideCharStr[iLen],MAX_PATH - iLen );
	lpWideCharStr[iLen] = '\0';
	

	return iLen;
}	
//得到当前程序文件名
int CVOSUtil::GetModuleFileName( vchar* lpszFilename, int dwSize )
{
	return ::GetModuleFileName( NULL, lpszFilename, dwSize );
}

/** 
  *	显示消息对话框
  *		@param lpszText	   [in] 显示的消息内容
  *		@param lpszCaption [in] 显示的消息标题
  *		@param dwType      [in] 消息对话框类型
  *
  *		@return	对话框返回值
  *		@notes  hInst对目前的Windows平台有效
  */	
int CVOSUtil::MessageBox( const char* lpszText, char* lpszCaption )
{
	return ::MessageBox( NULL,lpszText,lpszCaption,MB_OK );
}
void CVOSUtil::EncryptionString( char* str,int len, char* key )
{
	const char* pSeed = key;
	int nSeedLength = strlen(pSeed);
	for(int n = 0; n < len / nSeedLength; n++)
	{
		char* pPos = str + n * nSeedLength;
		for(int nIndex = 0; nIndex < nSeedLength; nIndex++)
		{
			pPos[nIndex] ^= pSeed[nIndex];
		}
	}
}
#define	_vcsinc(f)		(char*)( (( char * )f)++ )	// 自动增长1
// 替换字符串中的某个字符
int	STR_Replace( char* str,char chOld, char chNew )
{
	char* psz		= str;
	int nCount = 0;
	while( *psz )
	{
		if( *psz == chOld )
		{
			// 替换为目标字符
			*psz = chNew;
			nCount++;
		}
		psz = _vcsinc( psz );
	}
	return nCount;
}
inline BYTE toHex(const BYTE &x)
{
    return x > 9 ? x -10 + 'A': x + '0';
}
inline BYTE fromHex(const BYTE &x)
    {
        return isdigit(x) ? x-'0' : x-'A'+10;
    }
string URLEncode(const string &sIn)
{
    string sOut;
    for( size_t ix = 0; ix < sIn.size(); ix++ )
    {      
        BYTE buf[4];
        memset( buf, 0, 4 );
        if( isalnum( (BYTE)sIn[ix] ) )
        {      
            buf[0] = sIn[ix];
        }
        //else if ( isspace( (BYTE)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
        //{
        //    buf[0] = '+';
        //}
        else
        {
            buf[0] = '%';
            buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
            buf[2] = toHex( (BYTE)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }
    return sOut;
};
//写日志
void CVOSUtil::WriteLog( const char* strLog )
{
	;
}
//字符串分割函数  
std::vector<std::string> STR_Split(std::string str,std::string pattern)  
{  
    std::string::size_type pos;  
    std::vector<std::string> result;  
    str+=pattern;//扩展字符串以方便操作  
    int size=str.size();  
  
    for(int i=0; i<size; i++)  
    {  
        pos=str.find(pattern,i);  
        if(pos<size)  
        {  
            std::string s=str.substr(i,pos-i);  
            result.push_back(s);  
            i=pos+pattern.size()-1;  
        }  
    }  
    return result;  
}  