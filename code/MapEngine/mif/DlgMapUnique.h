/************************************************************
  文件名: DlgMapSingle.h
  
  作者:   钱军洪       Version : 1.0          Date: 2003/12/21
  
  类描述: 图层分类显示设置  
  邮件地址：Visual20@sohu.com
***********************************************************/
#if !defined(AFX_DLGMAPUNIQUE_H__7AB69BD9_409D_4646_814A_EBB9D1A83D82__INCLUDED_)
#define AFX_DLGMAPUNIQUE_H__7AB69BD9_409D_4646_814A_EBB9D1A83D82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMapUnique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMapUnique dialog
#include "LengendCtrl.h"
#include "MapLayer.h"
#include "MapRender.h"

class CDlgMapUnique : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgMapUnique)

// Construction
public:
	CDlgMapUnique();
	~CDlgMapUnique();

// Dialog Data
	//{{AFX_DATA(CDlgMapUnique)
	enum { IDD = IDD_DLG_MAPUNIQUE };
	CButton	m_BtnSet;
	CComboBox	    m_cmbField;
	CLengendCtrl	m_ListLegend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapUnique)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	CString m_csLayerName;
	CMapRender*  m_pRender;
protected:
	CMapLayer*   m_pLayer; 
	int          m_iCurlSel; 
	
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgMapUnique)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAPUNIQUE_H__7AB69BD9_409D_4646_814A_EBB9D1A83D82__INCLUDED_)
