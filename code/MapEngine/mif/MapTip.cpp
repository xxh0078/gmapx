#include "stdafx.h"
#include "MapTip.h"
#include "MainFrm.h"


BEGIN_MESSAGE_MAP(CMapTip,CToolTipCtrl)
	//{{AFX_MSG_MAP(CMapTip)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapTipWnd message handlers

CMapTip::CMapTip() 
{
	pLayers = NULL;
	pFields = NULL;
	m_Timer = 0;

}

CMapTip::~CMapTip()
{


}

BOOL CMapTip::Create(CWnd* pParentWnd,CPoint pt) 
{ 

	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              ::LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH),0);
	if (!CWnd::CreateEx(WS_EX_TOOLWINDOW, szClassName, "Hello", WS_VISIBLE|WS_POPUPWINDOW|WS_BORDER, 
                        pt.x, pt.y, 100, 100, // size updated soon
                        pParentWnd->GetSafeHwnd(), 0, NULL))
		return FALSE;
	//WS_POPUP
	return TRUE;

	
	
}

void CMapTip::InitMapTip(CMapLayers *pWorkSpace)
{

	pLayers = pWorkSpace;

}
void  CMapTip::MoveTo(CMapPoint& MapPt , CPoint& pt )
{
	int iCount;
	double dblX,dblY;
	CRect RC;
	if ( pLayers == NULL)
		return ;
	
	iCount = pLayers->GetCount();
	if ( iCount == 0 )
		return;
	m_Point = pt; 
	dblX = MapPt.GetX();
	dblY = MapPt.GetY();
	m_MapPoint.SetX(dblX);    
    m_MapPoint.SetY(dblY);  
	if ( m_Timer == 0 )
    {  
	
		m_LastPoint = m_Point;
		m_Timer = SetTimer (IDT_TIMER_0, TimerInterval, NULL);
	}
	else
	{   
		if (IsWindowVisible() ) 
        {
	 		ShowWindow(SW_HIDE);
			
		}
    }  
}
CString CMapTip::GetTipText(CMapPoint& pt)
{
	int iIndex;
	short i,iCount;
	CString csStr;
	CMapField *pField;
	CMainFrame *pFrame;
		
	if ( pLayers == NULL)
		return "";
	pFrame = (CMainFrame*)AfxGetMainWnd(); 
    if ( pFrame == NULL )
		return "";

	iCount = pLayers->GetCount();
	if ( iCount == 0 )
		return "";
	for ( i = 0 ; i < iCount ; i++)
	{	
		pLayer = pLayers->GetAt(i);
		if ( pLayer == NULL )
			return "";
		if (pFrame->m_MapTipLayer == pLayer->GetLayerName() )
             break;
	}
	if ( i >= iCount )
         return "";

	iIndex = pLayer->SearchShape(pt);
	if ( iIndex > 0 )
    {
		(pLayer->GetRecordSet())->Move(iIndex,BookmarkFirst); 
		pFields = (pLayer->GetRecordSet())->GetFields(0);
        for ( i = 0 ; i < pFields->GetCout(); i++ )
		{ 
		    pField = pFields->GetField(i); 
			if ( pField == NULL )
				return "";
            if ( pFrame->m_MapTipField == pField->GetName())
			{	
		          csStr = pField->GetValueAsString();						
			      break;			
            } 
		}        
	} 	
    return csStr; 
	    
}

void CMapTip::SetTipTxtFormat(CString txtFormat,int txtSize)
{

	int txtHight;
	CDC*   pDC;
	CFont  fontText;

	pDC = GetDC();
	
	switch ( txtSize ) {
	     case 10:
		     txtHight = 12;
			 break;
	     
		 case 11:
			 txtHight = 14;
		     break;
	     
		 case 12:
			 txtHight = 16;
			 break;
	     
		 case 13:
		     txtHight = 18;
			 break;
	     
		 case 14:
			 txtHight=20;
			 break;
	     
		 case 15:  
		     txtHight=22;
			 break;
	     
		 case 16:
			txtHight = 24;
			break;
	     
		 case 18:
			txtHight = 28;
			break;

	     default:
		     txtHight=12;
		
		}
	

	fontText.CreateFont(-txtHight, 0, 0, 0, 400, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, txtFormat);

	CFont *pOldFont=pDC->SelectObject(&fontText);

}

void CMapTip::SetTipTxt(int maxlen,CString strDis)
{
	CDC* pDC;

    pDC = GetDC();
	TEXTMETRIC tm;
	int k = 0;
	int n = 0;
	int nPos = 0;
	int j = 0;
	CString str[7];
	char s[256];
	
	strcpy(s,strDis);
	int len=strDis.GetLength();
	if ( len <= 15 ) 
	{
		pDC->TextOut(1,1,strDis);
	}
	else 
	{
	    for ( int i= 0 ; i < 7 ; i++) 
		{
             j=k+maxlen;
             while ( (s[j]!=',') && (s[j]!='\0') ) 
			 {
                  j--;
             }
             s[j]=' ';
             for ( n = k ; n <= j ; n++ ) 
			 {
             	str[i] += s[n];

             }
             k = j + 1;
        }
		pDC->GetTextMetrics(&tm);
		nPos=tm.tmHeight+tm.tmExternalLeading;
		
		for (int t = 0 ; t < 7 ; t++) 
		{
		   pDC->TextOut(1,nPos*t+1,str[t]);
		}
			
	}

}


void CMapTip::SetTipTxt(char* str)
{

	CDC*  pDC;
	pDC = GetDC();
	CString strDis = (CString)str;
	int len = strDis.GetLength();

	if ( len <= 20 )
		pDC->TextOut(1,1,strDis);
	else 
	{
	
		CString strTmp1,strTmp2;
		strTmp1 = strDis.Left(20);
		strTmp2 = strDis.Mid(20,strDis.GetLength()-19);
		pDC->TextOut(1,0,strTmp1);
		pDC->TextOut(1,25,strTmp2);
	}
}

void CMapTip::ShowMapTip(CString strTip, CPoint pt)   
{
	CDC* pDC; 
	CRect RC;
	TEXTMETRIC tm;
	CSize sizeText;
	CString mTip[7];
	int iPos1, iPos2, iStrLen, iSubLen, iMaxSubLen;
	int wndHeight, wndWidth;
	int i, n;
	int iPosition;

	pDC = GetDC();
	pDC->GetTextMetrics(&tm);
	sizeText = pDC->GetTextExtent(strTip.Mid(0,2));
	iStrLen = strTip.GetLength();
	
	// split the string
	iMaxSubLen = 0;
	iPos1 = -1;
	iPos2 = 0;
	i = 0;
	while ( iPos1!=-1 || iPos2!=-1 )
	{
		iPos2 = strTip.Find(",",iPos1+1);
		if ( iPos2==-1 )
			if ( iPos1==-1)
				iSubLen = iStrLen;
			else
				iSubLen = iStrLen-iPos1;
		else
			iSubLen = iPos2-iPos1-1;
		mTip[i] = strTip.Mid(iPos1+1,iSubLen);
		if ( iMaxSubLen<iSubLen )
			iMaxSubLen = iSubLen;
		iPos1 = iPos2;
		i++;
	}
	n = i;
		
    ShowWindow( SW_SHOWNORMAL );
	wndHeight = (int)sizeText.cy * n + 8;
	wndWidth=(int)sizeText.cx * iMaxSubLen / 2 + 8;
	MoveWindow(pt.x+12,pt.y+12,wndWidth,wndHeight,TRUE);
   	
    
     
	// set color of the tip window
	CBrush myBrush(RGB(240,245,230));
	CBrush *oldBrush;
	CRect rect;
	oldBrush = pDC->SelectObject(&myBrush);
	GetClientRect(&rect);
	pDC->Rectangle(rect);
	pDC->SetBkColor(RGB(240,245,230));
	pDC->SelectObject(oldBrush);
	// output
	iPosition = tm.tmHeight+tm.tmExternalLeading;
	for ( i=0;i<n;i++ )
	{
		pDC->TextOut(1,iPosition*i+1,mTip[i]);
	}
	
	// move, resize and show the tip window
	
}

char *  CMapTip::TrimStr(_variant_t str) {

	static CString retStr;
	
	retStr = (char *)_bstr_t(str);
	retStr.TrimLeft (_T(' '));
	retStr.TrimRight (_T(' '));
	return retStr.GetBuffer (1024);
}

void CMapTip::OnTimer (UINT TimerVal)
{
	CString csStr;
	CRect RC;

	if ( m_Point == m_LastPoint )
    {
		KillTimer(m_Timer);
		m_Timer = 0;
		if (IsWindowVisible() )
        {    
			ShowWindow(SW_HIDE);
					
		}  
		csStr = GetTipText(m_MapPoint);
		if ( csStr != "" )
        {  
			//ShowWindow(SW_HIDE);
			ShowMapTip(csStr,m_Point);
		
		}
		/*else
		{	
			ShowWindow(SW_HIDE);  //隐藏鼠标提示窗口
	
		}*/
		
    }
	else
    {
		  m_LastPoint = m_Point; 	
    } 
	CWnd::OnTimer(TimerVal);
}