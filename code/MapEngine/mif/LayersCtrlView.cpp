// LayersCtrlView.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMap.h"
#include "LayersCtrlView.h"
#include "JMCoolMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayersCtrlView

IMPLEMENT_DYNCREATE(CLayersCtrlView, CFormView)

CLayersCtrlView::CLayersCtrlView()
	: CFormView(CLayersCtrlView::IDD)
{
	//{{AFX_DATA_INIT(CLayersCtrlView)
	//}}AFX_DATA_INIT

}

CLayersCtrlView::~CLayersCtrlView()
{
	 
}

void CLayersCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayersCtrlView)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_LAYERTREE, m_LayerCtrlTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayersCtrlView, CFormView)
	//{{AFX_MSG_MAP(CLayersCtrlView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayersCtrlView diagnostics

#ifdef _DEBUG
void CLayersCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLayersCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLayersCtrlView message handlers

void CLayersCtrlView::OnDraw(CDC* pDC) 
{
	
	CRect rect,rcTree,rc;
    GetClientRect(&rect);

	
	//¸Ä±ä¿Ø¼þ´°Ìå´óÐ¡
	rcTree.left  = rect.left+3;
    rcTree.right = rect.right - 6;
	rcTree.top   = rect.top+20;
    rcTree.bottom = rect.bottom - 40; 
	m_LayerCtrlTree.MoveWindow(&rcTree,TRUE);
	
	rc.left = rect.left+5 ;
    rc.right = rect.right - 10  ;
    rc.top = rect.top+6;
	rc.bottom = rc.top + 5;
	m_Static1.MoveWindow(&rc);
	rc.left = rect.left+5 ;
    rc.right = rect.right - 10  ;
    rc.top = rect.top+11;
	rc.bottom = rc.top + 5;
	m_Static2.MoveWindow(&rc);
	rc.left = rect.left+5 ;
    rc.right = rect.left + 90  ;
    rc.top = rect.bottom - 40;
	rc.bottom = rc.top + 25;
	m_Tab.MoveWindow(&rc,TRUE);
	
}


void CLayersCtrlView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	TC_ITEM tci;
	HICON hIcon;
    HICON hIconLayer[4]; 
    unsigned int IconID[4]={IDI_LAYER,IDI_POINT,IDI_LINE,IDI_POLYGON};
	
	CWinApp *pApp=AfxGetApp();
	m_Imagelist[0].Create(16,16,true,1,1);
	m_Imagelist[1].Create(16,16,true,3,3);
	hIcon = pApp->LoadIcon(IDI_SPACE);
    m_Imagelist[0].Add(hIcon);  
	m_Tab.SetImageList(&m_Imagelist[0]);
	CString csStr = "Í¼²ã¿Õ¼ä";

	tci.mask    = TCIF_TEXT | TCIF_IMAGE ;
	tci.pszText = (LPSTR)(LPCTSTR)csStr;
	tci.cchTextMax = csStr.GetLength(); 
	tci.iImage = 0;
	m_Tab.InsertItem(0, &tci);

	for( int i = 0 ; i < 4 ; i++)   	
	{
       hIconLayer[i]=pApp->LoadIcon(IconID[i]);  
       m_Imagelist[1].Add(hIconLayer[i]);
	}	   
	m_LayerCtrlTree.SetImageList(&m_Imagelist[1],TVSIL_NORMAL); 
	m_LayerCtrlTree.InsertItem("Í¼²ã¹ÜÀí",0,0,TVI_ROOT,TVI_SORT);
    
    
   
	
	// TODO: Add your specialized code here and/or call the base class
	
}

BOOL CLayersCtrlView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	int idCtrl;
	CRect RC;
	CPoint point;
	CString csText;

	idCtrl  = (int)wParam;
	if ( idCtrl == IDC_LAYERTREE )
    {
		//´¦ÀíÊ÷¿Ø¼þÊó±êÓÒ¼üµ¯³ö²Ëµ¥
		NMHDR* pHdr = (NMHDR*)lParam;
		if ( pHdr->code == NM_RCLICK )
        {
			HTREEITEM hItem;
			hItem = m_LayerCtrlTree.GetSelectedItem(); 
			if ( hItem != NULL && hItem != m_LayerCtrlTree.GetRootItem())
			{
			
			    
				
				CJMCoolMenu menu;
				CWnd* pWndPopupOwner = this;

				HICON hIcon;
	            CString csText;
	            STRMENUINFO *pInfo;
	            unsigned int IconID[3]={IDI_ADD,IDI_DELETE,IDI_ATTRIBUTE};
                CWinApp *pApp=AfxGetApp();
                CImageList* pImageList = new CImageList;
                pImageList->Create(16,16,true,3,3);
	            for ( int i = 0 ; i < 3 ; i++)   	
				{
                   hIcon = pApp->LoadIcon(IconID[i]);  
                   pImageList->Add(hIcon);
				}
				menu.CreatePopupMenu(); 
				menu.SetImageList(pImageList); 

				pInfo = new STRMENUINFO;
				pInfo->csTitle = "Ìí¼ÓÍ¼²ã";
				pInfo->ImageIndex =0;
				pInfo->MenuID = ID_ADD_LAYER;
				csText = "Ìí¼ÓÍ¼²ã";
				menu.InsertMenu(MF_BYPOSITION,MF_STRING|MF_ENABLED|MF_OWNERDRAW , ID_ADD_LAYER,(LPCTSTR)csText);    
				menu.AddMenuInfo(pInfo); 
				
				pInfo = new STRMENUINFO;
				pInfo->csTitle = "É¾³ýÍ¼²ã";
				pInfo->ImageIndex =1;
				pInfo->MenuID =  ID_DEL_LAYER;
				csText = "É¾³ýÍ¼²ã";
				menu.InsertMenu(MF_BYPOSITION,MF_STRING|MF_ENABLED|MF_OWNERDRAW , ID_DEL_LAYER,(LPCTSTR)csText);
				menu.AddMenuInfo(pInfo);

				pInfo = new STRMENUINFO;
				pInfo->csTitle = "Í¼²ãÊôÐÔ";
				pInfo->ImageIndex = 2;
				pInfo->MenuID =  ID_ATTRIBUTE_LAYER;
				csText = "Í¼²ãÊôÐÔ";
			    menu.InsertMenu(MF_BYPOSITION,MF_STRING|MF_ENABLED|MF_OWNERDRAW , ID_ATTRIBUTE_LAYER,(LPCTSTR)csText);
				menu.AddMenuInfo(pInfo);

				/*if(m_Menu.GetSafeHmenu() == NULL)   
					m_Menu.LoadMenu(IDR_MENUPOP); 

				CMenu* pPopup =  m_Menu.GetSubMenu(0);
		        ASSERT(pPopup != NULL);*/
			   
		        while (pWndPopupOwner->GetStyle() & WS_CHILD)
					pWndPopupOwner = pWndPopupOwner->GetParent();
			    m_LayerCtrlTree.GetItemRect(hItem,&RC,TRUE);
				m_LayerCtrlTree.ClientToScreen(&RC);
				point = RC.TopLeft();
				point.Offset(5, 5);
               
			    menu.TrackPopupMenu(TPM_LEFTALIGN
							| TPM_RIGHTBUTTON, point.x, 
							point.y,pWndPopupOwner);
				/*pPopup->TrackPopupMenu(TPM_LEFTALIGN
							| TPM_RIGHTBUTTON, point.x, 
							point.y, pWndPopupOwner);*/
               
            }  
				
            
				 
        } 

		
    } 
	return CFormView::OnNotify(wParam, lParam, pResult);
}

BOOL CLayersCtrlView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	
	return CFormView::PreCreateWindow(cs);
}
