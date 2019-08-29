/************************************************************
  文件名: LengendCtrl.h
  
  作者:   钱军洪       Version : 1.0          Date: 2003/12/21
  
  类描述: 图例的管理：分类字段选择分类颜色设置
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#if !defined(AFX_LENGENDCTRL_H__86380FF9_208C_43CA_AE71_C40F0338BE69__INCLUDED_)
#define AFX_LENGENDCTRL_H__86380FF9_208C_43CA_AE71_C40F0338BE69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LengendCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLengendCtrl window

class CLengendCtrl : public CListCtrl
{
// Construction
public:
	CLengendCtrl();

// Attributes
public:
	COLORREF	m_clrHilight;
	COLORREF	m_clrNormalText;
	COLORREF	m_clrHilightText;
	COLORREF	m_clrBkgnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLengendCtrl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLengendCtrl();
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	// Generated message map functions
protected:
	//{{AFX_MSG(CLengendCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LENGENDCTRL_H__86380FF9_208C_43CA_AE71_C40F0338BE69__INCLUDED_)
