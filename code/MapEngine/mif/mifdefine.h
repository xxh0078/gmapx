
#ifndef	__MIF_DEFINE_H__
#define	__MIF_DEFINE_H__
#include "../VOSBase/VOSBase.h"
// POINT 结构体定义
typedef VOS_EXPORT struct _mifPoint
{ 
	double dx;
	double dy;
	string strText;
	short  sIco;
	_mifPoint()
	{
		dx =0;
		dy =0;
		sIco = 0;
	}
} mifPoint, *LPmifPoint; 

#endif		//__MAP_DEFINE_H__