/************************************************************
  文件名: DlgPtSymbolSet.h
  
  作者:   钱军洪       Version : 1.0          Date: 2003/12/21
  
  类描述: 显示TRUE TYPE 字体符号
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#if !defined(AFX_DLGPTSYMBOLSET_H__C26B68BC_E98A_4837_8EEA_5F1F4A0C95A2__INCLUDED_)
#define AFX_DLGPTSYMBOLSET_H__C26B68BC_E98A_4837_8EEA_5F1F4A0C95A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtSymbolSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtSymbolSet dialog

class CDlgPtSymbolSet : public CDialog
{
// Construction
public:
	CDlgPtSymbolSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtSymbolSet)
	enum { IDD = IDD_DLG_PTSYMBOL };
	CComboBox	m_Font;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtSymbolSet)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CString csFontName;
	unsigned short uiIndex;
    int iPrevIndex;  
public:
 static	int CALLBACK EnumFontFamProc(LPENUMLOGFONT lplf,LPNEWTEXTMETRIC lpNtm,DWORD dwFontType,long lParam);
protected:
  CToolTipCtrl   m_ToolTip;
  CArray<CRect*,CRect*> m_Bound; 
  
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtSymbolSet)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCombofont();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTSYMBOLSET_H__C26B68BC_E98A_4837_8EEA_5F1F4A0C95A2__INCLUDED_)
