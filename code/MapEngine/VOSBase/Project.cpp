// Project.cpp: implementation of the CProject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Project.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "math.h"
#ifndef PI 
	#define PI			3.1415926535897932	// π
	#define PI_MULT_2	6.2831853071795864	// 2倍π
	#define PI_DIVI_2	1.5707963267948966	// π的1/2
#endif	//PI
//////////////////////////////////////////////////////////////////////
// Construction/Destruction	CProject::CPoint2D
//////////////////////////////////////////////////////////////////////
// 坐标点管理类
CProject::CPoint2D::CPoint2D()
{
	x = 0.0;
	y = 0.0;
}

CProject::CPoint2D::CPoint2D( double dx,double dy )
{
	x = dx;
	y = dy;
}

CProject::CPoint2D::CPoint2D( CPoint2D& pt )
{
	x = pt.x;
	y = pt.y;
}

// 重载=运算符
void CProject::CPoint2D::operator=( const CPoint2D& pt )
{
	x = pt.x;
	y = pt.y;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction	CProject
//////////////////////////////////////////////////////////////////////
// 高斯坐标投影类
CProject::CProject()
{
	m_lCenterLong = 117;	//	默认中央经线

	m_a = 6378137.00;
	m_b = 6356752.3;

	m_e1 =  0.081819218048345;
	m_e2 =  0.082094465430911;
}

CProject::~CProject()
{

}

//*************************************
// 函数功能：由地理坐标计算平面高斯坐标
// 输入参数描述：
//	[in]：纬度、经度
//  [inout]：X 、 Y 
// 返回值描述：
// 	无
//*************************************
void CProject::CalXAndY( float fLonWei,float fLatJin,float &fX,float &fY/*,double zong_jin*/)
{
	double dwei = fLonWei;
	double djin = fLatJin;
	double dX  = 0;
	double dY = 0;

	CalXAndY(dwei ,djin,dX,dY/*,double zong_jin*/);
	fX = ( float )dX;
	fY = ( float )dY; 		
}

void CProject::CalXAndY( double dLonWei,double dLatJin,double &X,double &Y/*,double zong_jin*/)
{
	double s_s;								// 赤道到B纬度的经线弧长
	double m_m, n_n;						// 曲率半径，卯酉圈半径
//	double zong_jin = CalZongjing(dLonWei, dLatJin);

	double PP11 = 206264.81;				//ρ″

	double weiPi  = dLonWei * 0.017453293;		// 弧度制的纬度
	double sWeiPi = sin( weiPi );				// sin()
	double cWeiPi = cos( weiPi );				// cos()
	double ee1    = m_e1 * m_e1;

	m_m = m_a*(1-ee1) / (pow( (1-ee1*sWeiPi*sWeiPi), 1.5 )); 
	n_n = m_a / (pow( (1-ee1*sWeiPi*sWeiPi), 0.5 ));
	s_s = m_a*(1-ee1)*( 1.0050517739*weiPi - 0.00506237764*sin(2*weiPi)/2 + 0.0000106245*sin(4*weiPi)/4 - 0.00000002081*sin(6*weiPi)/6 );

//	double ll = (dLatJin-zong_jin)*3600.0;		//
	double ll = ( dLatJin-m_lCenterLong )*3600.0;		//
	double l  = ll*ll*1e-8;					// l'
	double tt = tan(weiPi);					// t
	double nn = m_e2*cos(weiPi);			// η
	double tt2 = tt * tt;
	double nn2 = nn * nn;
	double PP2 = PP11 * PP11;
	double cWeiPi3 = pow(cWeiPi,3);
	double cWeiPi5 = pow(cWeiPi,5);

	double a1 = n_n * sWeiPi*cWeiPi*(1e+8) / (2*PP2);
	double a2 = n_n * sWeiPi*cWeiPi3 * (5-tt2+9*nn2+4*nn2*nn2)*(1e+16) / (24*PP2*PP2);
	double a3 = n_n * sWeiPi*cWeiPi5 * (61-58*tt2+tt2*tt2)*pow(ll,6) / (720*pow(PP2,3));

	Y = s_s+(a1+a2*l)*l;					// 大地X

	a1 = n_n * cWeiPi / PP11;
	a2 = n_n * cWeiPi3 * (1-tt2+nn2)*(1e+8) / (6*PP2*PP11);
	a3 = n_n * cWeiPi5 * (5-18*tt2+tt2*tt2) *pow(ll,5) / (120*pow(PP2,2)*PP11);
	X = (a1 + a2*l)*ll;

	X += 500000;
}
double CProject::CalLength( double x1,double y1,double x2,double y2 )
{
	 CPoint2D pt1(x1,y1);
	 CPoint2D pt2(x2,y2);
	return CalLength(pt1,pt2);
}
double CProject::CalLength(const CPoint2D &pt1,const CPoint2D &pt2)
{	
	double x1,x2,y1,y2;

	CalBestCenterLong( pt1.x,pt2.x );

	CalXAndY(pt1.y,pt1.x,x1,y1);
	CalXAndY(pt2.y,pt2.x,x2,y2);
	
	return fabs( sqrt((x1-x2)*(x1-x2)+((y1-y2)*(y1-y2))) );	
}

//*******************************************************
// 计算两个点之间可用的中央经线(误差最小)
// 输入参数描述:
//		[in] dLong1 : 经度1 
//		[in] dLong2 : 经度2
// 返回值描述:
// 	中央经线
//*******************************************************
void CProject::CalBestCenterLong( double dLong1,double dLong2 )
{
	double dCenterLong = ( dLong2 + dLong1 ) / 2;		
	long lZone = ( long )dCenterLong / 6;
	double dRemaider = dCenterLong - 6 * lZone;

	if( dRemaider > 0.000001 )
		m_lCenterLong = lZone * 6 + 3;
	else
		m_lCenterLong = lZone * 6 - 3;
}
