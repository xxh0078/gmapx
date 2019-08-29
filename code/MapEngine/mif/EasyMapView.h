// EasyMapView.h : interface of the CEasyMapView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EASYMAPVIEW_H__77FB13C9_A193_43C9_8CE6_F47C88CED14A__INCLUDED_)
#define AFX_EASYMAPVIEW_H__77FB13C9_A193_43C9_8CE6_F47C88CED14A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Global.h"
#include "MapTip.h"

class CEasyMapView : public CView
{
protected: // create from serialization only
	CEasyMapView();
	DECLARE_DYNCREATE(CEasyMapView)

// Attributes
public:
	CEasyMapDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyMapView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEasyMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
    void InitScale();      
protected:
	int   m_Operation;             //设置当前操作状态
	int   m_isDownMouse;          //鼠标是否按下过  
	CPoint m_StartPt;             //记录鼠标操作起始点 
	CPoint m_SecondPt;            //记录鼠标操作第二点
private:
	
	DRAWPARAM m_DrawParam;
	CMapTip m_MapTip;
	int     m_FixedScale;
private:
	void ShowCoordinate(CMapPoint& pt);
	void ZoomInWindows();
	void ZoomIn();
	void ZoomOut();
	void Pan();
	void PtSelected(CPoint& pt);
protected:
    void Initialize();
	void Dispatch(CPoint pt);  
	void GetAppPath( char *szPath );
	// Generated message map functions
protected:
	//{{AFX_MSG(CEasyMapView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMapNothing();
	afx_msg void OnMapZoomIn();
	afx_msg void OnMapZoomOut();
	afx_msg void OnMapZoomAll();
	afx_msg void OnMapZoomWindow();
	afx_msg void OnMapPan();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMapPtsymbol();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMapSrhpt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EasyMapView.cpp
inline CEasyMapDoc* CEasyMapView::GetDocument()
   { return (CEasyMapDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYMAPVIEW_H__77FB13C9_A193_43C9_8CE6_F47C88CED14A__INCLUDED_)
