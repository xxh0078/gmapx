// VosTime.h: interface for the CVosTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOSTIME_H__6587E56C_D27B_4D26_A42F_8DE8346031B9__INCLUDED_)
#define AFX_VOSTIME_H__6587E56C_D27B_4D26_A42F_8DE8346031B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVOSTime  
{
public:
	CVOSTime();
	virtual ~CVOSTime();
	/** 得到当前机器的当前时间 */
	static CVOSTime GetCurrentTime();
};

#endif // !defined(AFX_VOSTIME_H__6587E56C_D27B_4D26_A42F_8DE8346031B9__INCLUDED_)
