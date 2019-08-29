/************************************************************
  文件名: MapTip.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 鼠标动态提示数据
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_TIP_H_
#define _MAP_TIP_H_

#include "MapLayer.h"
#include "MapLayers.h"
#include "MapFields.h"
#include "MapField.h"

#define IDT_TIMER_0		WM_USER + 200
#define TimerInterval	1000				// 100 mSec.


class CMapTip:public CToolTipCtrl
{
// Construction
public:
	CMapTip();
	CMapTip(CWnd* pParentWnd,CPoint pt);
  
// Attributes
public:

// Operations
public:
	BOOL Create(CWnd* pParentWnd,CPoint pt);
     // Overrides
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapTipWnd)

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapTip();	
public:
	void InitMapTip(CMapLayers *pWorkSpace);
public:
	void   MoveTo(CMapPoint& MapPt , CPoint& pt );
	CString GetTipText(CMapPoint& pt);
	void SetTipTxtFormat(CString txtFormat,int txtSize);
    void SetTipTxt(int n,CString strDis);
	void SetTipTxt(char* str);
	void ShowMapTip(CString strTip,CPoint pt);
	char *TrimStr(_variant_t str);
	

protected:
	CMapLayers *pLayers;
	CMapLayer  *pLayer;
	CMapFields *pFields;
    CPoint     m_Point;
	CPoint     m_LastPoint;
	CMapPoint  m_MapPoint;
	UINT       m_Timer;
protected:
	//{{AFX_MSG(CMapTip)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnTimer(UINT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif