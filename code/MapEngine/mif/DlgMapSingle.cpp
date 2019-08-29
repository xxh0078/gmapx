// DlgMapSingle.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMap.h"
#include "EasyMapDoc.h"
#include "MainFrm.h"
#include "EasyMapView.h"
#include "DlgMapSingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSingle property page


IMPLEMENT_DYNCREATE(CDlgMapSingle, CPropertyPage)

CDlgMapSingle::CDlgMapSingle() : CPropertyPage(CDlgMapSingle::IDD)
{
	//{{AFX_DATA_INIT(CDlgMapSingle)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_RCFill.left = 120;
    m_RCFill.right = m_RCFill.left + 105;
	m_RCFill.top   = 30;
    m_RCFill.bottom = m_RCFill.top + 20; 
	
	m_RCOutLine = m_RCFill;
    m_RCOutLine.top = 60;
    m_RCOutLine.bottom = m_RCOutLine.top + 20; 

    m_FillColor = RGB(255,239,156);
	m_OutlineColor = RGB(0,0,0);
	m_FillStyle = 0; 

	m_Hot = 0;
	m_csLayerName = _T("");
	m_pLayer = NULL;
}

CDlgMapSingle::~CDlgMapSingle()
{
}

void CDlgMapSingle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapSingle)
	DDX_Control(pDX, IDC_CMBSTYLE, m_cmbStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMapSingle, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgMapSingle)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSingle message handlers

BOOL CDlgMapSingle::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	int i ;
	CString   csFieldName;
	CMapLayer *pLayer;
	
	CMainFrame *pFrame = (CMainFrame *)::AfxGetMainWnd(); 
	ASSERT(pFrame != NULL );
	
	CEasyMapView *pView = (CEasyMapView*)pFrame->GetActiveView();
    ASSERT(pView != NULL );    

	CEasyMapDoc* pDoc = pView->GetDocument();
	ASSERT_VALID(pDoc);
      

	
	
	if ( !m_ToolTip.Create(this) ) 
	 return FALSE;
	
    m_ToolTip.AddTool(this,"RGB",&m_RCFill , 1 );
	m_ToolTip.AddTool(this,"RGB",&m_RCOutLine , 1 );

	m_cmbStyle.AddString("Solid Fill");
	m_cmbStyle.SetItemData(0,0); 
	m_cmbStyle.AddString("BDIAGONAL Fill");
	m_cmbStyle.SetItemData(1,HS_BDIAGONAL); 
	m_cmbStyle.AddString("CROSS Fill");
	m_cmbStyle.SetItemData(2,HS_CROSS); 
   	m_cmbStyle.AddString("DIAGCROSS Fill");
	m_cmbStyle.SetItemData(3,HS_DIAGCROSS);
	m_cmbStyle.AddString("FDIAGONAL Fill");
	m_cmbStyle.SetItemData(4,HS_FDIAGONAL);
	m_cmbStyle.AddString("HORIZONTAL Fill");
	m_cmbStyle.SetItemData(5,HS_HORIZONTAL);
	m_cmbStyle.AddString("VERTICAL Fill");
	m_cmbStyle.SetItemData(6,HS_VERTICAL);
  
	
	for ( i = 0 ; i < pDoc->m_MapLayers.GetCount() ; i++ )
    { 
		pLayer = (CMapLayer *)pDoc->m_MapLayers.GetAt(i);
		if ( pLayer->GetLayerName() == m_csLayerName )  
			break;   
	}
	if ( i >= pDoc->m_MapLayers.GetCount() )
    {
		m_pLayer = NULL;	
		return TRUE;
	}	
	m_pLayer = pLayer;
	
	 CMapRender* pRender = pLayer->GetRender();
	if ( pRender != NULL )
	{
		if ( pRender->GetRenderType() == SIMPLE_RENDER )
		{
			SIMPLERENDER simple;
			pRender->GetSimpleRender(simple); 
            m_FillColor = simple.FillColor;   
		    m_OutlineColor = simple.OutlineColor;
			for ( i = 0 ; i < m_cmbStyle.GetCount() ; i++ )
			{	
				if ( m_cmbStyle.GetItemData(i) == (DWORD)simple.iIndex )
				{
					m_FillStyle = i;
					break;
                } 
			}
		    if (  m_FillStyle >= m_cmbStyle.GetCount() || m_FillStyle < 0 )
			{
				m_FillStyle = 0;
				m_cmbStyle.SetCurSel(0); 

			}
			else
			{
				m_cmbStyle.SetCurSel(m_FillStyle);

			}
		}  
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgMapSingle::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg); 
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CDlgMapSingle::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brFill(m_FillColor);
    CBrush brOutLine(m_OutlineColor);
    
	dc.FillRect(m_RCFill,&brFill);
	dc.FillRect(m_RCOutLine,&brOutLine);
	dc.Draw3dRect(&m_RCFill,::GetSysColor(COLOR_BTNHILIGHT),::GetSysColor(COLOR_BTNSHADOW) );
	dc.Draw3dRect(&m_RCOutLine,::GetSysColor(COLOR_BTNHILIGHT),::GetSysColor(COLOR_BTNSHADOW) );
	 
	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CDlgMapSingle::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_RCFill.PtInRect(point) )
	{	
		m_Hot = 1;
         
	} 
	else if (m_RCOutLine.PtInRect(point) )
    {
		m_Hot = 2;
		 
    }    
	else
        m_Hot = 0;  
	CPropertyPage::OnMouseMove(nFlags, point);
}

void CDlgMapSingle::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_RCFill.PtInRect(point) )
	{	
		CColorDialog dlgColor(m_FillColor,CC_FULLOPEN|CC_RGBINIT,GetParent());
			
		if ( dlgColor.DoModal() == IDOK )
        {
		   m_FillColor = dlgColor.GetColor(); 
		   InvalidateRect(&m_RCFill,TRUE); 
		}            
	} 
	else if ( m_RCOutLine.PtInRect(point) )
    {
		CColorDialog dlgColor(m_OutlineColor,CC_FULLOPEN|CC_RGBINIT,this);
		if ( dlgColor.DoModal() == IDOK )
        {
		   m_OutlineColor = dlgColor.GetColor(); 
		   InvalidateRect(&m_RCOutLine,TRUE); 
		}            

    }  
	CPropertyPage::OnLButtonDblClk(nFlags, point);
}

void CDlgMapSingle::OnOK() 
{
	CMapRender *pRender;
	SIMPLERENDER simple;
	
	pRender = new CMapRender;
	ASSERT( pRender != NULL );
	pRender->SetRenderType(SIMPLE_RENDER); 
    
	simple.FillColor = m_FillColor;
	simple.OutlineColor = m_OutlineColor;
	simple.iIndex = m_cmbStyle.GetItemData( m_cmbStyle.GetCurSel());  
    pRender->SetSimpleRender(simple);    
    m_pLayer->SetRender(pRender);  

	CMainFrame *pFrame = (CMainFrame *)::AfxGetMainWnd(); 
	ASSERT(pFrame != NULL );
	
	CEasyMapView *pView = (CEasyMapView*)pFrame->GetActiveView();
    ASSERT(pView != NULL );    
	
	pView->Invalidate(TRUE); 
	CPropertyPage::OnOK();
}
