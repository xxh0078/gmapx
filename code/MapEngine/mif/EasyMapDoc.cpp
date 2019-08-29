// EasyMapDoc.cpp : implementation of the CEasyMapDoc class
//

#include "stdafx.h"
#include "EasyMap.h"
#include "Mainfrm.h"
#include "EasyMapDoc.h"
#include "EasyMapView.h"
#include "LayersCtrlView.h"
#include "DlgMapLegend.h"
#include "DlgMapSingle.h"
#include "DlgMapUnique.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyMapDoc

IMPLEMENT_DYNCREATE(CEasyMapDoc, CDocument)

BEGIN_MESSAGE_MAP(CEasyMapDoc, CDocument)
	//{{AFX_MSG_MAP(CEasyMapDoc)
	ON_COMMAND(ID_FILE_SHPADD, OnFileShpadd)
	ON_COMMAND(ID_ADD_LAYER, OnAddLayer)
	ON_COMMAND(ID_ATTRIBUTE_LAYER, OnAttributeLayer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyMapDoc construction/destruction

CEasyMapDoc::CEasyMapDoc()
{
	// TODO: add one-time construction code here

}

CEasyMapDoc::~CEasyMapDoc()
{
}

BOOL CEasyMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEasyMapDoc serialization

void CEasyMapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEasyMapDoc diagnostics

#ifdef _DEBUG
void CEasyMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEasyMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyMapDoc commands

void CEasyMapDoc::OnFileShpadd() 
{   
	int     iImage;
	CString csFileName;
	CMainFrame *pFrame;
	CLayersCtrlView *pLayerView;
	CEasyMapView    *pMapView;
	HTREEITEM hParent;
	CString csFilter = " shp Files (*.shp)|*.shp||";

	CFileDialog fDlg(TRUE,0,0,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,(LPCTSTR)csFilter
	                 ,NULL);
	pFrame = (CMainFrame*)AfxGetMainWnd(); 
	if( fDlg.DoModal() != IDCANCEL  ) 
	{
		csFileName = fDlg.GetPathName();  
		CMapLayer* pLayer = new CMapLayer;
        pLayer->SetLayerName(csFileName); 
		if ( pLayer->LoadData(csFileName) > 0 )
		{
			
			m_MapLayers.Add(pLayer);
			m_MapLayers.GetAllExtent(m_AllExtent); 
			//csFileName.TrimRight("\");
			pFrame->m_JMToolBar.m_JMLayer.AddString( csFileName);
			pLayerView = (CLayersCtrlView *)pFrame->m_wndSplitter.GetPane(0,0);  
            if ( pLayerView != NULL )
			{
			    switch ( pLayer->GetShpType() )
				{
					case POINT:
						iImage = 1;
						break;
                    case POLYLINE:
						iImage = 2;
						break;
                    case POLYGON:
						iImage = 3;
						break;
                    default:
						iImage = 3;
						break;
                }
				hParent =  pLayerView->m_LayerCtrlTree.GetNextItem(NULL,TVGN_CHILD); 
				pLayerView->m_LayerCtrlTree.InsertItem(csFileName,iImage,iImage,hParent,TVI_LAST); 
				pLayerView->m_LayerCtrlTree.Expand(hParent,TVE_EXPAND);    

			}	
			if ( m_MapLayers.GetCount() == 1 ) 
            { 
				pMapView = (CEasyMapView*)pFrame->m_wndSplitter.GetPane(0,1);
				pMapView->InitScale();
            }
			UpdateAllViews(NULL);  
        }
		else 
        {
			::MessageBox(NULL,"加载文件失败!","提示",MB_OK);
		    delete pLayer;
		}	
	
	}
	
}



void CEasyMapDoc::OnAddLayer() 
{
	// TODO: Add your command handler code here
	int a =10;
}

void CEasyMapDoc::OnAttributeLayer() 
{
	CString csLayerName;
	HTREEITEM hItem;
	CLayersCtrlView *pLayerView;
	CMainFrame* pFrame = (CMainFrame*)::AfxGetMainWnd(); 
	pLayerView = (CLayersCtrlView *)pFrame->m_wndSplitter.GetPane(0,0);  
	
	hItem = pLayerView->m_LayerCtrlTree.GetSelectedItem();
	if ( hItem !=  NULL )
    {  
		 
		CDlgMapLegend dlgMapLegend("图例设置",pFrame,0);
		CDlgMapSingle dlgMapSingle;
		dlgMapSingle.m_csLayerName = pLayerView->m_LayerCtrlTree.GetItemText(hItem);
		CDlgMapUnique dlgMapUnique;
		dlgMapUnique.m_csLayerName = pLayerView->m_LayerCtrlTree.GetItemText(hItem);
 
		dlgMapLegend.AddPage(&dlgMapSingle);
		dlgMapLegend.AddPage(&dlgMapUnique);
		dlgMapLegend.DoModal();
	}	

	
}
