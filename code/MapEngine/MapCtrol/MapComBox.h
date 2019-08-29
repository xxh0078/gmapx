// MapComBox.h: interface for the CMapComBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPCOMBOX_H__66C395A6_FBEA_4E16_8FC6_A05B6B2B0381__INCLUDED_)
#define AFX_MAPCOMBOX_H__66C395A6_FBEA_4E16_8FC6_A05B6B2B0381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapComBox  
{
public:
	CMapComBox();
	virtual ~CMapComBox();
	void Create( int left,int top, int width,int height,HWND hWndParent );
	void SetPos( int left,int top);
	void SetVisible(bool visible );
private:
	HWND	m_hWnd;
	DWORD	m_dwSytle;
	TCHAR	m_szText[MAX_PATH];
	int		m_iLeft;
	int		m_iTop;
	int		m_iWidth;
    int		m_iHeight;
};

#endif // !defined(AFX_MAPCOMBOX_H__66C395A6_FBEA_4E16_8FC6_A05B6B2B0381__INCLUDED_)
