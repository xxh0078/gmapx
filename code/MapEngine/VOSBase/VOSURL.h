#pragma once
#include "VOSDefine.h"
#include "../../include/curl/curl.h"
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
int InterNet_httpget(char* strURL,struct MemoryStruct *chunk );
class VOS_EXPORT CVOSURL
{
public:
	CVOSURL(void);
	~CVOSURL(void);
};
