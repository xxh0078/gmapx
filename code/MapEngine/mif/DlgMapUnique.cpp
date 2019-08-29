// DlgMapUnique.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMapDoc.h"
#include "MainFrm.h"
#include "EasyMapView.h"
#include "MapTableDesc.h" 
#include "MapFields.h"
#include "MapField.h"
#include "easymap.h"
#include "DlgMapUnique.h"
#include "MapRender.h"
//#include "global.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapUnique property page
UINT MapRand(UINT nMax)
{
	int nRand = rand();

	float fMap = (float)(nMax)/RAND_MAX;
	float fRetVal = (float)nRand*fMap + 0.5F;
	
	return (UINT)fRetVal;

};

IMPLEMENT_DYNCREATE(CDlgMapUnique, CPropertyPage)

CDlgMapUnique::CDlgMapUnique() : CPropertyPage(CDlgMapUnique::IDD)
{
	//{{AFX_DATA_INIT(CDlgMapUnique)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_csLayerName = _T("");
	m_pLayer = NULL;
	m_pRender = NULL;
	m_iCurlSel = -1;
}

CDlgMapUnique::~CDlgMapUnique()
{
	if ( m_pRender != NULL )
		delete m_pRender;    
}

void CDlgMapUnique::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapUnique)
	DDX_Control(pDX, IDC_BTNSET, m_BtnSet);
	DDX_Control(pDX, IDC_CMBFIELD, m_cmbField);
	DDX_Control(pDX, IDC_LISTLEGEND, m_ListLegend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMapUnique, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgMapUnique)
	ON_BN_CLICKED(IDC_BTNSET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapUnique message handlers

BOOL CDlgMapUnique::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	int i ;
	LV_COLUMN lvc;
	CString   csFieldName;
	CMapLayer *pLayer;
	
	CMainFrame *pFrame = (CMainFrame *)::AfxGetMainWnd(); 
	ASSERT(pFrame != NULL );
	
	CEasyMapView *pView = (CEasyMapView*)pFrame->GetActiveView();
    ASSERT(pView != NULL );    

	CEasyMapDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
      
	for ( i = 0 ; i < pDoc->m_MapLayers.GetCount() ; i++ )
    { 
		pLayer = (CMapLayer *)pDoc->m_MapLayers.GetAt(i);
		if ( pLayer->GetLayerName() == m_csLayerName )  
			break;   
	}
	if ( i >= pDoc->m_MapLayers.GetCount() )
    {
			pLayer = NULL;
			m_BtnSet.EnableWindow(FALSE);
			m_cmbField.EnableWindow(FALSE);
			m_ListLegend.EnableWindow(FALSE);  
			return TRUE;
	}	
	m_pLayer = pLayer;

	CMapTableDesc *pTableDsc = (pLayer->GetRecordSet())->GetTableDesc( );
	ASSERT(pTableDsc != NULL );

	for ( i = 0 ; i < pTableDsc->GetFieldCount() ; i++ )
	{	
		csFieldName = pTableDsc->GetFieldName(i);
		m_cmbField.AddString((LPCTSTR)csFieldName);  
	}

	ListView_SetExtendedListViewStyle(m_ListLegend.GetSafeHwnd(),LVS_EX_GRIDLINES);
	i = 0;
	lvc.mask= LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.pszText = "分类数值";
    lvc.iSubItem = i;
    lvc.cx =60;
    m_ListLegend.InsertColumn(i,&lvc);
	i = 1;
	lvc.mask= LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	lvc.fmt = LVCFMT_CENTER;
	lvc.pszText = "颜色RGB值";
    lvc.iSubItem = i;
    lvc.cx =130;
    m_ListLegend.InsertColumn(i,&lvc);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMapUnique::OnBtnSet() 
{
	int i,iCurSel,iIndex;
	int iMItem;
	LV_ITEM lvItem;
	CString csText;
	CString csFieldName,csValue;
	CMapFields *pFields;
    CMapField  *pField;
	RENDERINFO render;
	RENDERINFO *pRender;
		
	iCurSel = m_cmbField.GetCurSel();
	if ( iCurSel < 0 )
    {
		::MessageBox(NULL,"请选择分类字段","提示",MB_OK); 

    } 
	if ( iCurSel == m_iCurlSel )
		return;
    m_iCurlSel = iCurSel;

	m_cmbField.GetLBText(iCurSel,csFieldName);  
	iIndex = -1;
    (m_pLayer->GetRecordSet())->MoveFirst();
	pFields = (m_pLayer->GetRecordSet())->GetFields(0);
	
	for ( i = 0 ; i < pFields->GetCout() ; i++ )
	{
		pField = pFields->GetField(i);
		if ( csFieldName == pField->GetName() )
		{
			iIndex = i;
			break;
		}	
    }  
	if ( m_pRender != NULL )
		delete m_pRender;
    m_pRender = new CMapRender;
	m_pRender->SetFieldIndex(iIndex ); 
	m_ListLegend.DeleteAllItems(); 
	ASSERT( m_pRender != NULL );
    
	iMItem = 0;
    while ( !(m_pLayer->GetRecordSet())->GetEOF() && iIndex != -1 )
	{	
		pFields = (m_pLayer->GetRecordSet())->GetFields(0);
		pField = pFields->GetField(iIndex); 
        csValue = pField->GetValueAsString();
		
		if ( m_pRender->GetCount() >= 100 )
		{
			::MessageBox(NULL,"分类个数不能超过100!","提示",MB_OK);
			m_pRender->Clear();
			m_ListLegend.DeleteAllItems();  
			break;
        } 
		render.csValue = csValue;
		render.clr = RGB(MapRand(255),MapRand(255),MapRand(255));
        m_pRender->Add(render);
		(m_pLayer->GetRecordSet())->MoveNext();
	}  
	
	for ( i = 0 ; i <  m_pRender->GetCount() ; i++ )
	{	
		pRender = m_pRender->GetByIndex(i);
		csValue = pRender->csValue; 
		lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
        lvItem.state = 0;      
        lvItem.stateMask = 0;  
        lvItem.iItem = iMItem++;                              //项目索引
	    lvItem.iSubItem =0;	
	    lvItem.pszText = csValue.GetBuffer(csValue.GetLength()); 
        lvItem.cchTextMax =255; 
		m_ListLegend.InsertItem(&lvItem);
		 
	}
	m_pRender->SetRenderType(UNIQUE_RENDER);
	 

}


void CDlgMapUnique::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CMapRender* pRender;
	CRect rc;
   	if ( m_pRender != NULL )
    {   
		pRender = new CMapRender;
		ASSERT(pRender != NULL );
        m_pRender->Clone(pRender);  
	    m_pLayer->SetRender(pRender);
	
		CMainFrame *pFrame = (CMainFrame *)::AfxGetMainWnd(); 
	    ASSERT(pFrame != NULL );
	
	    CEasyMapView *pView = (CEasyMapView*)pFrame->m_wndSplitter.GetPane(0,1);
	    ASSERT(pView != NULL );    
	    pView->GetClientRect(&rc);
	    pView->Invalidate(TRUE); 
	    //pView->UpdateWindow(); 
    } 
	CPropertyPage::OnOK();
}
