#ifndef _JM_COOLMENU_H_
#define _JM_COOLMENU_H_

typedef struct strMenuInfo
{

	unsigned int MenuID;
	unsigned short ImageIndex;
	CString  csTitle;

} STRMENUINFO;

class CJMCoolMenu : public CMenu
{

public:
	CJMCoolMenu();
	~CJMCoolMenu();
public:
	void SetImageList(CImageList *pImageList);
	void AddMenuInfo(STRMENUINFO* pInfo); 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
private:
	COLORREF	m_clrHilight;
	COLORREF	m_clrNormalText;
	COLORREF	m_clrHilightText;
	COLORREF	m_clrBkgnd;
private:
	CImageList* m_pImageList;
	CArray<STRMENUINFO*,STRMENUINFO*> m_MenuInfo;


};


#endif //_JM_COOLMENU_H_