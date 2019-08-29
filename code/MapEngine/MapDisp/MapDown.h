// MapDown.h: interface for the CMapDown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDOWN_H__4EDF3007_4868_4542_9E47_2399BF05053F__INCLUDED_)
#define AFX_MAPDOWN_H__4EDF3007_4868_4542_9E47_2399BF05053F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapDown  
{
public:
	CMapDown();
	virtual ~CMapDown();

	//执行线程
	int RUN();
	//下载线程
	static unsigned long __stdcall ThreadProc( void* pParameter );
private:

};

#endif // !defined(AFX_MAPDOWN_H__4EDF3007_4868_4542_9E47_2399BF05053F__INCLUDED_)
