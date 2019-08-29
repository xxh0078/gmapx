#include "StdAfx.h"
#include "VOSUtil.h"
//#include <windows.h>
CVOSUtil::CVOSUtil(void)
{
}

CVOSUtil::~CVOSUtil(void)
{
}
//���ֽ�ת��ΪUNICODE
int	CVOSUtil::MultiByteToWdieChar( char* lpMultiByteStr, wchar* lpWideCharStr, int iWideChar )
{
	int i = ::MultiByteToWideChar( CP_ACP, 0, lpMultiByteStr, strlen( lpMultiByteStr),
		lpWideCharStr, iWideChar );

	lpWideCharStr[i] = '\0';
	return i;
}
// UNICODEת��Ϊ���ֽ�
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
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, strSrc, i);  // Unicodeת����GB2312 
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
// �ѷ�UNICODE��UNICODE�ַ������
int	CVOSUtil::AddMultiByteToWideChar( wchar* lpWideCharStr, char* lpMultiByteStr )
{
	int iLen = 0;
	iLen = wcslen( lpWideCharStr );
	iLen += CVOSUtil::MultiByteToWdieChar( lpMultiByteStr,&lpWideCharStr[iLen],MAX_PATH - iLen );
	lpWideCharStr[iLen] = '\0';
	

	return iLen;
}	
//�õ���ǰ�����ļ���
int CVOSUtil::GetModuleFileName( vchar* lpszFilename, int dwSize )
{
	return ::GetModuleFileName( NULL, lpszFilename, dwSize );
}

/** 
  *	��ʾ��Ϣ�Ի���
  *		@param lpszText	   [in] ��ʾ����Ϣ����
  *		@param lpszCaption [in] ��ʾ����Ϣ����
  *		@param dwType      [in] ��Ϣ�Ի�������
  *
  *		@return	�Ի��򷵻�ֵ
  *		@notes  hInst��Ŀǰ��Windowsƽ̨��Ч
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
#define	_vcsinc(f)		(char*)( (( char * )f)++ )	// �Զ�����1
// �滻�ַ����е�ĳ���ַ�
int	STR_Replace( char* str,char chOld, char chNew )
{
	char* psz		= str;
	int nCount = 0;
	while( *psz )
	{
		if( *psz == chOld )
		{
			// �滻ΪĿ���ַ�
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
        //else if ( isspace( (BYTE)sIn[ix] ) ) //ò�ưѿո�����%20����+������
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
//д��־
void CVOSUtil::WriteLog( const char* strLog )
{
	;
}
//�ַ����ָ��  
std::vector<std::string> STR_Split(std::string str,std::string pattern)  
{  
    std::string::size_type pos;  
    std::vector<std::string> result;  
    str+=pattern;//��չ�ַ����Է������  
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