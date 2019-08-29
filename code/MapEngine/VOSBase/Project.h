// Project.h: interface for the CProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_)
#define AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************
//						������ͼ�򷽿Ƽ����޹�˾
//						
//						B/S GPS������غ�̨ϵͳ���߰�
//   
//
//	����: CProject
//	���: ��۶�	    	 ���ʱ��: 2005-04-08
//  ʵ��: ��۶�			 ���ʱ��: 2005-04-08
//  ʵ������:
//	
//	����Ͳ���: 		���ʱ��:
//	��������:
//  ��������:ͶӰ�任����˹���㣩
//		����6�ȷִ���ʽ
//  �ο��ĵ�:
//  
//*******************************************************************

class CProject  
{
public:
	// ����������
	class CPoint2D
	{
	public:
		double x;
		double y;

		// ���캯���ͳ�Ա����
	public:
		CPoint2D();
		CPoint2D( double dx,double dy );
		CPoint2D( CPoint2D& pt );

		// ����=�����
		void operator=( const CPoint2D& pt );
	};

public:
	CProject();
	virtual ~CProject();

public:
	//*************************************
	// ��������:�ɵ����������ƽ���˹����
	// �����������:
	//	[in]:dLonWei:γ�ȣ�dLatJin:����
	//  [inout]:X��Y :ƽ������ 
	// ����ֵ����:
	// 	��
	//*************************************
	void CalXAndY(double dLonWei,double dLatJin,double &X,double &Y/*,double zong_jin*/);

	//*************************************
	// ��������:�ɵ����������ƽ���˹����
	// �����������:
	//	[in]:fLonWei γ�ȡ�fLatJin ����
	//  [inout]:X �� Y 
	// ����ֵ����:
	// 	��
	//*************************************
	void CalXAndY(float fLonWei,float fLatJin,float &fX,float &fY/*,double zong_jin*/);

	//*************************************
	// ��������:�ɵ����������ƽ���˹�����ϵľ���
	// �����������:
	//	[in]:���������
	// ����ֵ����:
	// 	����
	//*************************************
	double CalLength(const CPoint2D &pt1,const CPoint2D &pt2);
	
	double CalLength( double x1,double y1,double x2,double y2);
protected:
	//*******************************************************
	// ����������֮����õ����뾭��(�����С)
	// �����������:
	//		[in] dLong1 : ����1 
	//		[in] dLong2 : ����2
	// ����ֵ����:
	// 	���뾭��
	//*******************************************************
	void CalBestCenterLong( double dLong1,double dLong2 );

protected:
	long m_lCenterLong;	// ���뾭��	
	//��ʽ���㳣��
	double 	m_a ;	//���򳤰뾶
	double	m_b ;	//����̰뾶
	
	double	m_e1 ;	//�����һ������
	double  m_e2 ;	//����ڶ�������
};

#endif // !defined(AFX_PROJECT_H__1F1029DC_A010_4761_A27E_80B992B72FA6__INCLUDED_)
