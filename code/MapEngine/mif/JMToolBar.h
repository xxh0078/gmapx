#ifndef _JM_TOOLBAR_H_
#define _JM_TOOLBAR_H_

#include "JMComboBox.h"

class CJMToolBar : public CToolBar
{

public:
	CJMToolBar();
	virtual ~CJMToolBar();

public:
	CJMComboBox m_JMLayer;
    CJMComboBox m_JMField;
public:
	void InitBar();
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

protected:
	void JM_SetButton(int nIndex, TBBUTTON* pButton);
	void JM_GetButton(int nIndex, TBBUTTON* pButton);
	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
	CSize CalcLayout(DWORD nMode, int nLength = -1);
		// Generated message map functions
protected:
	//{{AFX_MSG(CJMToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnSelchangeLayer();
	afx_msg void OnSelCancelLayer();
	afx_msg void OnSelchangeField();
	afx_msg void OnSelCancelField();
	DECLARE_MESSAGE_MAP()

};
#endif //_JM_TOOLBAR_H_