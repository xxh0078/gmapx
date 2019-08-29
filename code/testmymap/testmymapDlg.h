// testmymapDlg.h : header file
//
//{{AFX_INCLUDES()
#include "gmapx.h"
//}}AFX_INCLUDES
#include "DlgMoveMap.h"

#if !defined(AFX_TESTMYMAPDLG_H__C6929780_B430_4383_BFE0_38ED2FEB0442__INCLUDED_)
#define AFX_TESTMYMAPDLG_H__C6929780_B430_4383_BFE0_38ED2FEB0442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestmymapDlg dialog

class CTestmymapDlg : public CDialog
{
// Construction
public:
	CTestmymapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestmymapDlg)
	enum { IDD = IDD_TESTMYMAP_DIALOG };
	CGmapx	m_gmapx;
	CDlgMoveMap m_DlgMoveMap;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestmymapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestmymapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnMapPointClickGmapxctrl1(long pid);
	afx_msg void OnOnLoadEndGmapxctrl1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuitem32771();
	afx_msg void OnMenuitem32772();
	afx_msg void OnMenuitem32773();
	afx_msg void OnMenuitem32774();
	afx_msg void OnMenuitem32775();
	afx_msg void OnMenuitem32776();
	afx_msg void OnMenuitem32777();
	afx_msg void OnMenuitem32778();
	afx_msg void OnMenuitem32779();
	afx_msg void OnMenuitem32780();
	afx_msg void OnMenuitem32781();
	afx_msg void OnMenuitem32782();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMYMAPDLG_H__C6929780_B430_4383_BFE0_38ED2FEB0442__INCLUDED_)
