// JMTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMap.h"
#include "JMTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJMTreeCtrl

CJMTreeCtrl::CJMTreeCtrl()
{
	m_bIsDrag = FALSE;
	m_pDragImage = NULL;
}

CJMTreeCtrl::~CJMTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CJMTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CJMTreeCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMTreeCtrl message handlers

void CJMTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
	
	HTREEITEM hItem = GetSelectedItem();
	if (GetParentItem(hItem) == NULL) 
		return ;
}

void CJMTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CJMTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HTREEITEM htiNew,hSibling; 
	if (m_bIsDrag)
	{
		m_bIsDrag = FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		if(m_pDragImage != NULL) 
		{ 
			delete m_pDragImage; 
			m_pDragImage = NULL; 
		} 
		SelectDropTarget(NULL);
		if ( m_hitemDrag == m_hitemDrop)
			return;
		else
        {
			if ( m_hitemDrop != NULL )
            {
				if ( point.y > m_DragPos.y)
				{	
				    //向下拖动
					htiNew = CopyItem(m_hitemDrag,GetRootItem(),m_hitemDrop);
				   	
					
                }
				else
                {
					hSibling = GetPrevSiblingItem(m_hitemDrop);
					//if (GetParentItem(m_hitemDrop) != GetChildItem(GetRootItem())) 
                    if ( hSibling != NULL )
					{
						//hSibling = GetPrevVisibleItem(m_hitemDrop); 
						htiNew = CopyItem(m_hitemDrag,GetRootItem(),hSibling);
 					
					}
					else
                    {
						 htiNew = CopyItem(m_hitemDrag,GetRootItem(),TVI_FIRST);
 				
                    }  
				} 
				DeleteItem( m_hitemDrag );
				SelectItem( htiNew );
			}    


		}
	}
	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CJMTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HTREEITEM hItem;
    UINT flags;

	if ( m_bIsDrag )
    {
		//正在拖动
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);
		
		if ((hItem = HitTest(point, &flags)) != NULL)
		{
			CImageList::DragShowNolock(FALSE);
		
			SelectDropTarget(hItem); 
			m_hitemDrop = hItem;
        }
		if ( m_hitemDrag == m_hitemDrop) //拖动结点和放置节点是一个位置
			return;
		CImageList::DragShowNolock(TRUE);

	}
	else
    {
		::SetCursor(m_arr);	
    }   
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CJMTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	POINT pt;
	*pResult = 0;
	HTREEITEM hRoot;

	
	// 根节点不允许拖动
	hRoot = GetRootItem(); 
	if (hRoot == pNMTreeView->itemNew.hItem) 
		return ; 
	m_hitemDrag = pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;
	m_bIsDrag = TRUE; 
	pt = pNMTreeView->ptDrag;
	m_DragPos = pt;
	//转换为屏幕坐标
	ClientToScreen( &pt );
	m_pDragImage = CreateDragImage(m_hitemDrag);
	
	if ( m_pDragImage == NULL )
		return;
     m_pDragImage->BeginDrag(0,CPoint(8,8)); 
	 m_pDragImage->DragEnter(NULL, pt);
	 ::SetCursor(m_hand);
	SetCapture();
}

HTREEITEM CJMTreeCtrl::CopyItem(HTREEITEM hItem , HTREEITEM hParent , HTREEITEM hAfter)
{

	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
	CString sText;

	//得到源条目的信息
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText = sText.LockBuffer ();

	//将条目插入到合适的位置
	tvstruct.hParent = hParent;
	tvstruct.hInsertAfter = hAfter;
	tvstruct.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	//限制拷贝条目数据和条目状态
	SetItemData( hNewItem,GetItemData(hItem) );
	SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);
	return hNewItem;
}

void CJMTreeCtrl::SetDefaultCursor()
{

	 CString cstrWndDir;
     
	 GetWindowsDirectory(cstrWndDir.GetBuffer(MAX_PATH), MAX_PATH);
     cstrWndDir.ReleaseBuffer();

     cstrWndDir += _T("\\winhlp32.exe");
     
	 HMODULE hModule = LoadLibrary(cstrWndDir);
     if (hModule) 
	 {
            HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
            if (hHandCursor)
			{
                m_hand = CopyCursor(hHandCursor);
			}
			      
     }
     FreeLibrary(hModule);

	 m_arr	= ::LoadCursor(NULL, IDC_ARROW);
	 m_no	= ::LoadCursor(NULL, IDC_NO) ;



}
/*HTREEITEM CJMTreeCtrl::CopyBranch(HTREEITEM hItem , HTREEITEM hParent , HTREEITEM hAfter)
{



}*/
