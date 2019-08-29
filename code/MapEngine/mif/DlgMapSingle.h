/************************************************************
  文件名: DlgMapSingle.h
  
  作者:   钱军洪       Version : 1.0          Date: 2003/12/21
  
  类描述: 图层简单符号显示设置
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#if !defined(AFX_DLGMAPSINGLE_H__B12D3D3A_9701_4CDD_8D2A_93F487642AB8__INCLUDED_)
#define AFX_DLGMAPSINGLE_H__B12D3D3A_9701_4CDD_8D2A_93F487642AB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapSingle.h : header file
//
#include "MapLayer.h"
#include "MapRender.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgMapSingle dialog

class CDlgMapSingle : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgMapSingle)

// Construction
public:
	CDlgMapSingle();
	~CDlgMapSingle();

// Dialog Data
	//{{AFX_DATA(CDlgMapSingle)
	enum { IDD = IDD_DLG_MAPSINGLE };
	CComboBox	m_cmbStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapSingle)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF       m_FillColor;
	COLORREF       m_OutlineColor;
	int            m_FillStyle; 
	CString        m_csLayerName;
protected:
	int            m_Hot;
	CRect          m_RCFill;
	CRect          m_RCOutLine; 
	CToolTipCtrl   m_ToolTip;
	CMapLayer*     m_pLayer;
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgMapSingle)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPSINGLE_H__B12D3D3A_9701_4CDD_8D2A_93F487642AB8__INCLUDED_)
