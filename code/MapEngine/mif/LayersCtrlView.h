#if !defined(AFX_LAYERSCTRLVIEW_H__3B707BC6_0CD6_48D1_98F7_13AF548C14C3__INCLUDED_)
#define AFX_LAYERSCTRLVIEW_H__3B707BC6_0CD6_48D1_98F7_13AF548C14C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayersCtrlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayersCtrlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "JMCOOLMENU.h"
#include "JMTreeCtrl.h"

class CLayersCtrlView : public CFormView
{
protected:
	CLayersCtrlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLayersCtrlView)

// Form Data
public:
	//{{AFX_DATA(CLayersCtrlView)
	enum { IDD = IDD_DLG_LAYERCTRL };
	CTabCtrl	m_Tab;
	CStatic	m_Static2;
	CStatic	m_Static1;
	CJMTreeCtrl	m_LayerCtrlTree;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayersCtrlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_Imagelist[2];
	//CJMCoolMenu m_Menu;

protected:
	virtual ~CLayersCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLayersCtrlView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERSCTRLVIEW_H__3B707BC6_0CD6_48D1_98F7_13AF548C14C3__INCLUDED_)
