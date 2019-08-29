// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C3072623_1B58_401F_888B_C93CABEB2ED3__INCLUDED_)
#define AFX_MAINFRM_H__C3072623_1B58_401F_888B_C93CABEB2ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapLayers.h"
#include "JMToolBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public: //cursor resource
    HCURSOR m_hcurZInWindow;
	HCURSOR m_hcurZOut;
    HCURSOR m_hcurPan; 
    HCURSOR m_hcurZIn;
    HCURSOR m_hcurFind;

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	BOOL m_bMapTip;
    CString m_MapTipLayer;
	CString m_MapTipField;
	CJMToolBar  m_JMToolBar;
public:
	CStatusBar  m_wndStatusBar;
	CSplitterWnd m_wndSplitter;
protected:  // control bar embedded members
	//CToolBar    m_wndToolBar;
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMapTip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C3072623_1B58_401F_888B_C93CABEB2ED3__INCLUDED_)
