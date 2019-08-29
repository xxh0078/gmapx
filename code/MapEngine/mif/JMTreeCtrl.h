/************************************************************
  �ļ���: JMTreeCtrl.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2003/12/21
  
  ������:   ͼ���������ͼ�����ӡ�ɾ�����Ϸš��Ƿ���ʾ
            ��Ӧ����Ҽ������˵�

  �ʼ���ַ��Visual20@sohu.com
***********************************************************/
#if !defined(AFX_JMTREECTRL_H__3F0C34E8_6684_4255_AD9F_771352A4146B__INCLUDED_)
#define AFX_JMTREECTRL_H__3F0C34E8_6684_4255_AD9F_771352A4146B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JMTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJMTreeCtrl window

class CJMTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CJMTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	HCURSOR m_hand;
	HCURSOR m_arr;
	HCURSOR m_no;
	bool	m_IsCursorArrow;
	CPoint  m_DragPos;
public:
	virtual ~CJMTreeCtrl();
protected:
	HTREEITEM CopyItem(HTREEITEM hItem , HTREEITEM hParent , HTREEITEM hAfter);
	void SetDefaultCursor();
private:
	BOOL        m_bIsDrag  ;       //�Ƿ����϶� 
	HTREEITEM	m_hitemDrag;       //���϶��Ľڵ�
    HTREEITEM   m_hitemDrop;       //��ǰѡ�нڵ�  
	CImageList*	m_pDragImage;      //�϶�ͼ���б�

	// Generated message map functions
protected:
	//{{AFX_MSG(CJMTreeCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMTREECTRL_H__3F0C34E8_6684_4255_AD9F_771352A4146B__INCLUDED_)
