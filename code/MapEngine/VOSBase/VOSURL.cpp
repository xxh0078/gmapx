#include "StdAfx.h"
#include "VOSURL.h"
#pragma comment(lib,"../lib/libcurl_imp.lib")
#include "../../include/curl/curl.h"
#pragma comment(lib,"wininet.lib")
#include<wininet.h>
void *myrealloc(void *ptr, size_t size)
{ /* There might be a realloc() out there that doesn't like reallocing  NULL pointers, so we take care of it here */
	if(ptr)
	  return realloc(ptr, size);
	else
	  return malloc(size);
}

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;
	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
	  memcpy(&(mem->memory[mem->size]), ptr, realsize);
	  mem->size += realsize;
	  mem->memory[mem->size] = 0;
	}
	return realsize;
}
size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct WriteThis *pooh = (struct WriteThis *)userp;
	
	if(size*nmemb < 1)
		return 0;
	
	if(pooh->sizeleft) {
		*(char *)ptr = pooh->readptr[0]; /* copy one single byte */
		pooh->readptr++;                 /* advance pointer */
		pooh->sizeleft--;                /* less data left */
		return 1;                        /* we return 1 byte at a time! */
	}
	
	return -1;                         /* no more data left to deliver */
}
int curl_httpget(const char* URLbuf,struct MemoryStruct *chunk,const char* cookiefile)
{
	CURL *curl_handle;
	int errcode=0; 
	chunk->memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk->size = 0; /* no data at this point */
	curl_global_init(CURL_GLOBAL_ALL);
	/* init the curl session */
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, URLbuf);
	curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE,cookiefile);
	/* send all data to this function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk); 
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR,cookiefile); 
	/* get it! */
	errcode=curl_easy_perform(curl_handle); 
	  /* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);
	return errcode; 
}
bool curl_httppost( const char* URLbuf,char* data, int len,struct MemoryStruct *chunk )
{
  CURL *curl;
  CURLcode res;
  chunk->memory=NULL; /* we expect realloc(NULL, size) to work */
  chunk->size = 0; /* no data at this point */
  struct WriteThis pooh;

  pooh.readptr = data;
  pooh.sizeleft = len;

  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. */
/**
    curl_easy_setopt(curl, CURLOPT_URL,
                     "http://receivingsite.com.pooh/index.cgi");
**/
	  curl_easy_setopt(curl, CURLOPT_URL,URLbuf);
	  /* Now specify we want to POST data */
	  curl_easy_setopt(curl, CURLOPT_POST, TRUE);
	  
	  /* we want to use our own read function */
	  curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	  /* pointer to pass to our read function */
	  curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);

	  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk); 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	  /* get verbose debug output please */
	  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	  
	  /*
      If you use POST to a HTTP 1.1 server, you can send data without knowing
      the size before starting the POST if you use chunked encoding. You
      enable this by adding a header like "Transfer-Encoding: chunked" with
      CURLOPT_HTTPHEADER. With HTTP 1.0 or without chunked transfer, you must
      specify the size in the request.
	  */
#ifdef USE_CHUNKED
	  {
		  curl_slist *chunk = NULL;
		  
		  chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
		  res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		  /* use curl_slist_free_all() after the *perform() call to free this
		  list again */
	  }
#else
	  /* Set the expected POST size. If you want to POST large amounts of data,
	  consider CURLOPT_POSTFIELDSIZE_LARGE */
	  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);
#endif
	  
#ifdef DISABLE_EXPECT
	  /*
      Using POST with HTTP 1.1 implies the use of a "Expect: 100-continue"
      header.  You can disable this header with CURLOPT_HTTPHEADER as usual.
      NOTE: if you want chunked transfer too, you need to combine these two
      since you can only set one list of headers with CURLOPT_HTTPHEADER. */
	  
	  /* A less good option would be to enforce HTTP 1.0, but that might also
	  have other implications. */
	  {
		  curl_slist *chunk = NULL;
		  
		  chunk = curl_slist_append(chunk, "Expect:");
		  res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		  /* use curl_slist_free_all() after the *perform() call to free this
		  list again */
	  }
#endif
	  
	  /* Perform the request, res will get the return code */
	  res = curl_easy_perform(curl);
	  
	  /* always cleanup */
	  curl_easy_cleanup(curl);
  }
  return 0;
}
CVOSURL::CVOSURL(void)
{
}

CVOSURL::~CVOSURL(void)
{
}

int InterNet_httpget(char* strURL,struct MemoryStruct *chunk )
{
	HINTERNET internet=InternetOpen("HTTP Downloader 1", INTERNET_OPEN_TYPE_PRECONFIG, 
        NULL, NULL, NULL);
    if(!internet)
	{
        throw "InternetOpen error!";
		return 1 ;
	}
    //打开一个http url地址
    HINTERNET file_handle = InternetOpenUrl(internet, strURL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if(!file_handle)
	{
        //throw "InternetOpenUrl error! - Maybe you should add Http:// or Ftp://";
		return 2 ;
	}
	chunk->size = 0;
	char* ptemp = chunk->memory;
	int b=false;
	unsigned long ilen = 0 ;
	while(1)
	{
		if ( chunk->size >1024*1023 )
		{
			break;
		}
		b = InternetReadFile( file_handle, ptemp, 1024, &ilen);
		if(!b )
		{
			//throw "InternetReadFile error!";
			int iiii = ::GetLastError();
			break;
		}
		if( ilen <= 0 )
		{
			break;
		}
		ptemp += ilen;
		chunk->size += ilen;
	}
	//关闭连接
	InternetCloseHandle(internet);
	return 0;
}