/************************************************************
  文件名: MapRectangle.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 对矩形对象的管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_RECTANGLE_H_
#define _MAP_RECTANGLE_H_

#include <math.h>
//#include "MapPoint.h"


class CMapRectangle {

public:
	CMapRectangle();
	CMapRectangle(CMapRectangle& MapRectangle );
	~CMapRectangle();
//attribute
public:
	void   SetLeft(double dbLeft) { m_dbLeft = dbLeft;};
	void   SetRight(double dbRight) { m_dbRight = dbRight;};
	void   SetTop(double dbTop ) { m_dbTop = dbTop;};  
	void   SetBottom(double dbBottom) { m_dbBottom = dbBottom; }; 
	double GetLeft()   { return m_dbLeft; };
	double GetRight()  { return m_dbRight; }
	double GetTop()    { return m_dbTop; };
	double GetBottom() { return m_dbBottom; };
	double GetWidth()  { return fabs(m_dbRight-m_dbLeft);};
	double GetHeigh()  { return fabs(m_dbBottom-m_dbTop);};
//operations
public:
//	BOOL IsPointIn(CMapPoint& Point);
//	BOOL IsInsercet(CMapRectangle& rc);
private:
	double m_dbLeft;
	double m_dbRight;
	double m_dbTop;
	double m_dbBottom;
};
#endif //_MAP_RECTANGLE_H_
