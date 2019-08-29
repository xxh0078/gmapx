// MapEdit.h: interface for the CMapEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPEDIT_H__8F00FD2A_8DAE_4524_BFCA_824E6B269DE1__INCLUDED_)
#define AFX_MAPEDIT_H__8F00FD2A_8DAE_4524_BFCA_824E6B269DE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapEdit  
{
public:
	CMapEdit();
	virtual ~CMapEdit();
	void Create( int left,int top, int width,int height,HWND hWndParent );
	void SetPos( int left,int top);
	void MoveWnd( int left,int top, int width,int height );
	void SetText(const TCHAR *pText,  DWORD dwSytle = DT_WORDBREAK|DT_VCENTER|DT_LEFT);
	TCHAR *GetText();
	virtual void DestroyWnd() ;
	void SetVisible(bool visible );
private:
	HWND m_hWnd;
	DWORD	m_dwSytle;
	TCHAR m_szText[MAX_PATH];
	int   m_iLeft;
	int   m_iTop;
	int   m_iWidth;
    int   m_iHeight;
};

#endif // !defined(AFX_MAPEDIT_H__8F00FD2A_8DAE_4524_BFCA_824E6B269DE1__INCLUDED_)
