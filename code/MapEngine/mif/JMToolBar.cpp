#include "stdafx.h"
#include "resource.h"
#include "JMToolBar.h"
#include "MapLayers.h"
#include "MapLayer.h"
#include "MapTableDesc.h"
#include "MainFrm.h"
#include "EasyMapDoc.h"
#include "EasyMapView.h"


BEGIN_MESSAGE_MAP(CJMToolBar, CToolBar)
	//{{AFX_MSG_MAP(CJMToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBOX_LAYER, OnSelchangeLayer)
	ON_CBN_SELCHANGE(IDC_COMBOX_FIELD, OnSelchangeField)
	ON_CBN_SELENDCANCEL(IDC_COMBOX_LAYER, OnSelCancelLayer)
	ON_CBN_SELCHANGE(IDC_COMBOX_FIELD, OnSelCancelField)
END_MESSAGE_MAP()

struct _AFX_CONTROLPOS
{
	int nIndex, nID;
	CRect rectOldPos;
};
CJMToolBar::CJMToolBar()
{


}

CJMToolBar::~CJMToolBar()
{


}
void CJMToolBar::InitBar()
{
	CRect rect;
	CString  string;  
	
	//图层下拉框
	SetButtonInfo( 13, IDC_COMBOX_LAYER, TBBS_SEPARATOR, 150 );
	GetItemRect( 13, &rect );
	rect.bottom += 300;
	if(!m_JMLayer.Create (WS_VISIBLE|WS_CHILD | CBS_DROPDOWNLIST |CBS_OEMCONVERT |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS ,rect, this, IDC_COMBOX_LAYER))
		return;

	m_JMLayer.m_ID = IDC_COMBOX_LAYER;
	m_JMLayer.m_wndParent = this;
	m_JMLayer.SetItemHeight(-1, 18);
 	m_JMLayer.SetDroppedWidth( 260 );
    //CBS_OWNERDRAWVARIABLE

	//字段下拉框
	SetButtonInfo(14, IDC_COMBOX_FIELD, TBBS_SEPARATOR, 80 );
	GetItemRect(14, &rect );
	rect.bottom += 150;
	if(!m_JMField.Create (CBS_DROPDOWNLIST|WS_VISIBLE|CBS_OEMCONVERT |WS_TABSTOP|CBS_AUTOHSCROLL|WS_VSCROLL , rect, this, IDC_COMBOX_FIELD))
		return;
    m_JMField.m_ID  = IDC_COMBOX_FIELD;
	m_JMField.m_wndParent =  this;
	m_JMField.SetItemHeight(-1, 16);
	m_JMField.SetDroppedWidth( 110 );
	GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
}
CSize CJMToolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
}

CSize CJMToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

void CJMToolBar::JM_SetButton(int nIndex, TBBUTTON* pButton)
{

	TBBUTTON button;
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));

	// prepare for old/new button comparsion
	button.bReserved[0] = 0;
	button.bReserved[1] = 0;
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
	pButton->bReserved[0] = 0;
	pButton->bReserved[1] = 0;

	// nothing to do if they are the same
	if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
	{
		// don't redraw everything while setting the button
		DWORD dwStyle = GetStyle();
		ModifyStyle(WS_VISIBLE, 0);
		VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));

		// Force a recalc of the toolbar's layout to work around a comctl bug
		int iTextRows;
		iTextRows = (int)::SendMessage(m_hWnd, TB_GETTEXTROWS, 0, 0);
		::SendMessage(m_hWnd, WM_SETREDRAW, FALSE, 0);
		::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iTextRows+1, 0);
		::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iTextRows, 0);
		::SendMessage(m_hWnd, WM_SETREDRAW, TRUE, 0);

		VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
		ModifyStyle(0, dwStyle & WS_VISIBLE);

		// invalidate appropriate parts
		if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
			((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
		{
			// changing a separator
			Invalidate();
		}
		else
		{
			// invalidate just the button
			CRect rect;
			if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
				InvalidateRect(rect);
		}
	}

}

void CJMToolBar::JM_GetButton(int nIndex, TBBUTTON* pButton) 
{
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
	pButton->fsState ^= TBSTATE_ENABLED;
}
void CJMToolBar::OnSelchangeLayer()
{

    int iCurSel;
	short i,j;
	CString csLayerName,csStr;
	CMapLayer *pLayer;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	
	CEasyMapView *pView = (CEasyMapView*)pFrame->GetActiveView();
	
	if( pView == NULL ) 
		return;
	
	CEasyMapDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
	
	iCurSel = m_JMLayer.GetCurSel();
	if ( iCurSel >= 0 ) 
    {
		m_JMLayer.GetLBText(iCurSel , csLayerName); //获得图层名称
	    for ( i = 0 ; i < pDoc->m_MapLayers.GetCount() ; i++ )
		{
			pLayer = (CMapLayer*)pDoc->m_MapLayers.GetAt(i);
			if ( pLayer == NULL )
				return;
			if ( pLayer->GetLayerName() == csLayerName) 
		    {
				CMapTableDesc tbl(*((pLayer->GetRecordSet())->GetTableDesc()) );
				m_JMField.Clear();
				for ( j = 0 ; j < tbl.GetFieldCount() ; j++ )
				{
					csStr = tbl.GetFieldName(j); 
					m_JMField.AddString(csStr.GetBuffer(csStr.GetLength()));   	
                }
		        m_JMField.SetCurSel(0);
				pFrame->m_MapTipLayer = csLayerName;
		        m_JMField.GetLBText(0,csStr); 
		        pFrame->m_MapTipField = csStr;
				break;
			}	
		}	
		pView->SetFocus();
        m_JMLayer.Invalidate(); 

    }   

}

void CJMToolBar::SizeToolBar(TBBUTTON *pData, int nCount, int nLength, BOOL bVert)
{
		ASSERT(pData != NULL && nCount > 0);

	if (!bVert)
	{
		int nMin, nMax, nTarget, nCurrent, nMid;

		// Wrap ToolBar as specified
		nMax = nLength;
		nTarget = WrapToolBar(pData, nCount, nMax);

		// Wrap ToolBar vertically
		nMin = 0;
		nCurrent = WrapToolBar(pData, nCount, nMin);

		if (nCurrent != nTarget)
		{
			while (nMin < nMax)
			{
				nMid = (nMin + nMax) / 2;
				nCurrent = WrapToolBar(pData, nCount, nMid);

				if (nCurrent == nTarget)
					nMax = nMid;
				else
				{
					if (nMin == nMid)
					{
						WrapToolBar(pData, nCount, nMax);
						break;
					}
					nMin = nMid;
				}
			}
		}
		CSize size = CalcSize(pData, nCount);
		WrapToolBar(pData, nCount, size.cx);
	}
	else
	{
		CSize sizeMax, sizeMin, sizeMid;

		// Wrap ToolBar vertically
		WrapToolBar(pData, nCount, 0);
		sizeMin = CalcSize(pData, nCount);

		// Wrap ToolBar horizontally
		WrapToolBar(pData, nCount, 32767);
		sizeMax = CalcSize(pData, nCount);

		while (sizeMin.cx < sizeMax.cx)
		{
			sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
			WrapToolBar(pData, nCount, sizeMid.cx);
			sizeMid = CalcSize(pData, nCount);

			if (nLength < sizeMid.cy)
			{
				if (sizeMin == sizeMid)
				{
					WrapToolBar(pData, nCount, sizeMax.cx);
					return;
				}
				sizeMin = sizeMid;
			}
			else if (nLength > sizeMid.cy)
			{
				if (sizeMax == sizeMid)
				{
					WrapToolBar(pData, nCount, sizeMin.cx);
					return;
				}
				sizeMax = sizeMid;
			}
			else
				return;
		}
	}

}

CSize CJMToolBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	if (dwMode & LM_HORZDOCK)
		ASSERT(dwMode & LM_HORZ);

	int nCount;
	TBBUTTON* pData = NULL;
	CSize sizeResult(0,0);

	//BLOCK: Load Buttons
	{
	  //IA64: Assume max button count < 2G
		nCount = int(DefWindowProc(TB_BUTTONCOUNT, 0, 0));
		if (nCount != 0)
		{
			int i;
			pData = new TBBUTTON[nCount];
			for (i = 0; i < nCount; i++)
				JM_GetButton(i, &pData[i]);
		}
	}

	if (nCount > 0)
	{
		if (!(m_dwStyle & CBRS_SIZE_FIXED))
		{
			BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

			if (bDynamic && (dwMode & LM_MRUWIDTH))
				SizeToolBar(pData, nCount, m_nMRUWidth);
			else if (bDynamic && (dwMode & LM_HORZDOCK))
				SizeToolBar(pData, nCount, 32767);
			else if (bDynamic && (dwMode & LM_VERTDOCK))
				SizeToolBar(pData, nCount, 0);
			else if (bDynamic && (nLength != -1))
			{
				CRect rect; rect.SetRectEmpty();
				CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeToolBar(pData, nCount, nLen, bVert);
			}
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
				SizeToolBar(pData, nCount, m_nMRUWidth);
			else
				SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
		}

		sizeResult = CalcSize(pData, nCount);

		if (dwMode & LM_COMMIT)
		{
			_AFX_CONTROLPOS* pControl = NULL;
			int nControlCount = 0;
			BOOL bIsDelayed = m_bDelayedButtonLayout;
			m_bDelayedButtonLayout = FALSE;
			int i;

			for (i = 0; i < nCount; i++)
				if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
					nControlCount++;

			if (nControlCount > 0)
			{
				pControl = new _AFX_CONTROLPOS[nControlCount];
				nControlCount = 0;

				for(i = 0; i < nCount; i++)
				{
					if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
					{
						pControl[nControlCount].nIndex = i;
						pControl[nControlCount].nID = pData[i].idCommand;

						CRect rect;
						GetItemRect(i, &rect);
						ClientToScreen(&rect);
						pControl[nControlCount].rectOldPos = rect;

						nControlCount++;
					}
				}
			}

			if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
				m_nMRUWidth = sizeResult.cx;
			for (i = 0; i < nCount; i++)
				JM_SetButton(i, &pData[i]);

			if (nControlCount > 0)
			{
				for (i = 0; i < nControlCount; i++)
				{
					CWnd* pWnd = GetDlgItem(pControl[i].nID);
					if (pWnd != NULL)
					{
						CRect rect;
						pWnd->GetWindowRect(&rect);
						CPoint pt = rect.TopLeft() - pControl[i].rectOldPos.TopLeft();
						GetItemRect(pControl[i].nIndex, &rect);
						pt = rect.TopLeft() + pt;
						pWnd->SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
					}
				}
				delete[] pControl;
			}
			m_bDelayedButtonLayout = bIsDelayed;
		}
		delete[] pData;
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}
	return sizeResult;
}

void CJMToolBar::OnSelCancelLayer()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CEasyMapView *pView = (CEasyMapView*) pFrame->GetActiveView();

	if ( pView != NULL)
	{
		pView->SetFocus();
	}
}
void CJMToolBar::OnSelchangeField()
{

    int iCurSel;
	CString csLayerName,csStr;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CEasyMapView *pView = (CEasyMapView*)pFrame->GetActiveView();
	
	if( pView == NULL ) 
		return;
	
	iCurSel = m_JMField .GetCurSel();
	if ( iCurSel > 0 ) 
    {
		m_JMField.GetLBText(iCurSel , csStr); //获得字段名称
        pFrame->m_MapTipField = csStr;    	    
		pView->SetFocus();
        m_JMLayer.Invalidate(); 

    }   

}

void CJMToolBar::OnSelCancelField()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CEasyMapView *pView = (CEasyMapView*) pFrame->GetActiveView();

	if ( pView != NULL)
	{
		pView->SetFocus();
	}
}
