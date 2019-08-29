// EasyMapDoc.h : interface of the CEasyMapDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EASYMAPDOC_H__4703CDC8_74CC_4938_98F2_F3D2E54278DD__INCLUDED_)
#define AFX_EASYMAPDOC_H__4703CDC8_74CC_4938_98F2_F3D2E54278DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapLayers.h"

class CEasyMapDoc : public CDocument
{
protected: // create from serialization only
	CEasyMapDoc();
	DECLARE_DYNCREATE(CEasyMapDoc)

// Attributes
public:
	CMapLayers m_MapLayers;
	CMapRectangle m_AllExtent;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyMapDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEasyMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEasyMapDoc)
	afx_msg void OnFileShpadd();
	afx_msg void OnAddLayer();
	afx_msg void OnAttributeLayer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYMAPDOC_H__4703CDC8_74CC_4938_98F2_F3D2E54278DD__INCLUDED_)
