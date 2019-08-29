// Project.h: interface for the CProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_)
#define AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************
//						北京瑞图万方科技有限公司
//						
//						B/S GPS车辆监控后台系统工具包
//   
//
//	类名: CProject
//	设计: 李慧恩	    	 完成时间: 2005-04-08
//  实现: 李慧恩			 完成时间: 2005-04-08
//  实现评语:
//	
//	检验和测试: 		完成时间:
//	测试评语:
//  功能描述:投影变换（高斯计算）
//		采用6度分带方式
//  参考文档:
//  
//*******************************************************************

class CProject  
{
public:
	// 坐标点管理类
	class CPoint2D
	{
	public:
		double x;
		double y;

		// 构造函数和成员函数
	public:
		CPoint2D();
		CPoint2D( double dx,double dy );
		CPoint2D( CPoint2D& pt );

		// 重载=运算符
		void operator=( const CPoint2D& pt );
	};

public:
	CProject();
	virtual ~CProject();

public:
	//*************************************
	// 函数功能:由地理坐标计算平面高斯坐标
	// 输入参数描述:
	//	[in]:dLonWei:纬度；dLatJin:经度
	//  [inout]:X、Y :平面坐标 
	// 返回值描述:
	// 	无
	//*************************************
	void CalXAndY(double dLonWei,double dLatJin,double &X,double &Y/*,double zong_jin*/);

	//*************************************
	// 函数功能:由地理坐标计算平面高斯坐标
	// 输入参数描述:
	//	[in]:fLonWei 纬度、fLatJin 经度
	//  [inout]:X 、 Y 
	// 返回值描述:
	// 	无
	//*************************************
	void CalXAndY(float fLonWei,float fLatJin,float &fX,float &fY/*,double zong_jin*/);

	//*************************************
	// 函数功能:由地理坐标计算平面高斯坐标上的距离
	// 输入参数描述:
	//	[in]:两个坐标点
	// 返回值描述:
	// 	距离
	//*************************************
	double CalLength(const CPoint2D &pt1,const CPoint2D &pt2);
	
	double CalLength( double x1,double y1,double x2,double y2);
protected:
	//*******************************************************
	// 计算两个点之间可用的中央经线(误差最小)
	// 输入参数描述:
	//		[in] dLong1 : 经度1 
	//		[in] dLong2 : 经度2
	// 返回值描述:
	// 	中央经线
	//*******************************************************
	void CalBestCenterLong( double dLong1,double dLong2 );

protected:
	long m_lCenterLong;	// 中央经线	
	//公式计算常量
	double 	m_a ;	//地球长半径
	double	m_b ;	//地球短半径
	
	double	m_e1 ;	//地球第一扁心率
	double  m_e2 ;	//地球第二扁心率
};

#endif // !defined(AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_)
