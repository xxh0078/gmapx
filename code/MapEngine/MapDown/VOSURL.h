// VOSURL.h: interface for the CVOSURL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOSURL_H__7E5B2064_06F3_45EA_8D86_F82CD91D7BAF__INCLUDED_)
#define AFX_VOSURL_H__7E5B2064_06F3_45EA_8D86_F82CD91D7BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../include/curl/curl.h"
struct MemoryStruct
{
	char *memory;
	size_t size;
	MemoryStruct()
	{
		memory = NULL;
		size = 0;
	}
};
struct WriteThis {
	char *readptr;
	int sizeleft;
};
int curl_httpget(const char* URLbuf,struct MemoryStruct *chunk,const char* cookiefile);
bool curl_httppost( const char* URLbuf,char* data, int len,struct MemoryStruct *chunk );

#endif // !defined(AFX_VOSURL_H__7E5B2064_06F3_45EA_8D86_F82CD91D7BAF__INCLUDED_)
