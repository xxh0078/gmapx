// DlgPtSymbolSet.cpp : implementation file
//

#include "stdafx.h"
#include "EasyMap.h"
#include "DlgPtSymbolSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPtSymbolSet dialog


CDlgPtSymbolSet::CDlgPtSymbolSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtSymbolSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPtSymbolSet)
	csFontName = _T("");
	uiIndex = 35;
	iPrevIndex = -1;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPtSymbolSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtSymbolSet)
	DDX_Control(pDX, IDC_COMBOFONT, m_Font);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtSymbolSet, CDialog)
	//{{AFX_MSG_MAP(CDlgPtSymbolSet)
	ON_WM_PAINT()
	ON_CBN_SELENDOK(IDC_COMBOFONT, OnSelendokCombofont)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtSymbolSet message handlers

void CDlgPtSymbolSet::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CFont fnt;
	CFont *pOldFnt;
	CString csText;
	CRect *pRC;
  
	fnt.CreateFont(20,0,0,0,FW_EXTRABOLD,0,0,0,SYMBOL_CHARSET,OUT_TT_PRECIS,
		                   CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,csFontName);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	pOldFnt = dc.SelectObject(&fnt);

	for ( int  i = 0 ; i < m_Bound.GetSize() ; i++)
	{
		pRC = m_Bound.GetAt(i);
		csText = i + 35;
        dc.TextOut(pRC->left ,pRC->top,csText ); 
		if ( i == (uiIndex - 35))
		{	
			dc.Draw3dRect(pRC, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));	
		}
    } 
	if ( iPrevIndex != - 1 && iPrevIndex != uiIndex)
    { 
		pRC = m_Bound.GetAt(iPrevIndex - 35);
		dc.Draw3dRect(pRC,::GetSysColor(COLOR_BTNHILIGHT),::GetSysColor(COLOR_BTNSHADOW) );
    }  
	
	dc.SelectObject(pOldFnt); 
}

int CALLBACK CDlgPtSymbolSet::EnumFontFamProc(LPENUMLOGFONT lplf,LPNEWTEXTMETRIC lpNtm,DWORD dwFontType,long lParam)
{
	CDlgPtSymbolSet *pDlg = (CDlgPtSymbolSet*)lParam;
	
	if( ( dwFontType == TRUETYPE_FONTTYPE) && 
		pDlg->m_Font.FindStringExact( -1, lplf->elfLogFont.lfFaceName ) == CB_ERR )
	{
		pDlg->m_Font.AddString(lplf->elfLogFont.lfFaceName);
    }  
	return 1;

}

BOOL CDlgPtSymbolSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int x,y;
	char szTip[128];
	LOGFONT lf;
	CRect *pRC;
	
	if ( !m_ToolTip.Create(this) ) 
	 return FALSE;

	lf.lfCharSet = SYMBOL_CHARSET;
	strcpy(lf.lfFaceName , "");

	HDC hDC  = ::CreateDC( "DISPLAY", NULL, NULL, NULL );
	if( hDC ){
		::EnumFonts( hDC, NULL, (FONTENUMPROC)EnumFontFamProc, (LPARAM)this );//Enumerate
		::DeleteDC( hDC);
	}
	if ( m_Font.GetCount() > 0 )
	{
		m_Font.SetCurSel(0);
		m_Font.GetLBText(0,csFontName);
    } 

	x= 20,
	y=50;
	for ( int i = 35; i < 189 ; i++ )
    {
		pRC = new CRect;
		pRC->left = x;
        pRC->right = x + 25;
		pRC->top = y;
        pRC->bottom = y + 30; 
		m_Bound.Add(pRC);  
		if ( x < 345 )
			x += 25;
        else
		{
			x = 20;
			y+=30;
		} 
		sprintf(szTip,"Ë÷Òý:%d",i);
		m_ToolTip.AddTool(this ,szTip, pRC,i);
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtSymbolSet::OnSelendokCombofont() 
{
	int iCur;

	iCur = m_Font.GetCurSel(); 
	m_Font.GetLBText(iCur,csFontName); 
	Invalidate(TRUE); 
	
}



BOOL CDlgPtSymbolSet::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
    CRect *pRC;
	for ( i = m_Bound.GetSize() - 1 ; i>= 0 ; i--)
	{
		pRC = m_Bound.GetAt(i);
		delete pRC;
    } 
	m_Bound.RemoveAll(); 
	return CDialog::DestroyWindow();
}

void CDlgPtSymbolSet::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRect RC;
	CRect *pOldRC,*pRC;

	for ( int i = 0 ; i < m_Bound.GetSize(); i++)
    {
		pRC = m_Bound.GetAt(i);
		if ( pRC->PtInRect(point) && i != (iPrevIndex-35) ) 
			
		{
		        
			if ( i == (uiIndex -35) )
			{
				if ( iPrevIndex != -1 )
				{
				    pOldRC =  m_Bound.GetAt(iPrevIndex -35);
					iPrevIndex = -1;
					InvalidateRect(pOldRC,TRUE);
					
				}
				break;
              
			}
			else
            {
				if ( iPrevIndex == -1 )
				{
				   InvalidateRect(pRC,TRUE);
                   iPrevIndex = i + 35;
                }
				else
				{
					pOldRC =  m_Bound.GetAt(iPrevIndex -35);
					RC.left  = min(pRC->left,pOldRC->left);
					RC.right = max(pRC->right,pOldRC->right);
					RC.top   = min(pRC->top,pOldRC->top);
					RC.bottom = max(pRC->bottom,pOldRC->bottom);  
					iPrevIndex = i + 35;
					InvalidateRect(&RC,TRUE); 
			
				}	
				break;
			}
		}  
	
    } 
	
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CDlgPtSymbolSet::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPtSymbolSet::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CRect RC;
	CRect *pOldRC,*pRC;
 
	for ( int i = 0 ; i < m_Bound.GetSize(); i++)
    {
		pRC = m_Bound.GetAt(i);
		if ( pRC->PtInRect(point) ) 
		{  	
            if ( uiIndex == i + 35 )
				break;
			
			pOldRC =  m_Bound.GetAt(uiIndex -35);
			RC.left  = min(pRC->left,pOldRC->left);
			RC.right = max(pRC->right,pOldRC->right);
			RC.top   = min(pRC->top,pOldRC->top);
			RC.bottom = max(pRC->bottom,pOldRC->bottom);  
			uiIndex = i + 35;
			iPrevIndex = -1;
			InvalidateRect(&RC,TRUE); 
			break;
		}
	}	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPtSymbolSet::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
