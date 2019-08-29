#include "StdAfx.h"
#include "MapLayer.h"

CMapLayer::CMapLayer(void)
{
	m_brushFont = CreateSolidBrush(RGB(0,0,0));
	m_bVisible = TRUE;
}

CMapLayer::~CMapLayer(void)
{
	DeleteObject( m_brushFont );
	RemoveAll();
}
/*bool CMapLayer::OnLButtonDown( VOSPoint point )
{
	return false;
}
bool CMapLayer::OnLButtonUp( VOSPoint point)
{
	return false;
}
bool CMapLayer::OnMouseMove( VOSPoint point)
{
	return false;
}*/
//���������
bool CMapLayer::CreatMapPoint( long pointid )
{
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		if ( pointid == poi->m_sPOIID ) {
			return false;
		}
    }
	CMapPoi* pNewPoi = new CMapPoi();
	pNewPoi->m_sPOIID = pointid;
	m_arrPoi.push_back(pNewPoi);
	return true;
}
bool CMapLayer::CreatMapPoint( long pointid, double x, double y, string strName, string strText, short icoID )
{
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		if ( pointid == poi->m_sPOIID ) {
			return false;
		}
    }
	CMapPoi* pNewPoi = new CMapPoi();
	pNewPoi->m_sPOIID = pointid;
	pNewPoi->m_Point.x = x;
	pNewPoi->m_Point.y = y;
	pNewPoi->m_strPoiName = strName;
	pNewPoi->m_strText = strText;
	pNewPoi->m_sResID = icoID;
	//pNewPoi->OpenEdit( 1 );
	m_arrPoi.push_back(pNewPoi);
	return true;
}
bool CMapLayer::SetMapPointAngle( long pointID, long lAngle )
{
	CMapPoi* poi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->m_sPOIID == pointID ) 
		{
			poi->SetMapAngle( lAngle );
			return true;
		}
    }
	return false;
}
//�����߶���
bool CMapLayer::CreatMapLine(short lineID )
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			return false;
		}
    }

	CMapLine* pNewLine = new CMapLine();
	pNewLine->m_lineid = lineID;
	pNewLine->SetColor( 0x000000 );
	pNewLine->SetWidth( 1 );
	m_arrLine.push_back(pNewLine);

	int count = this->m_arrLine.size();
	return true;
}
bool CMapLayer::AddMapLinePoint( short lineID, MapPoint* pPoint)
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			line->AddPoint( pPoint );
			return true;
		}
    }
	return false;
}
bool CMapLayer::SetMapLineName( short lineID, string name )
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			//line->m_strname = name;
			line->SetLineName( name );
			return true;
		}
    }
	return false;
}
bool CMapLayer::SetMapLineColor( short lineID, long lineColor )
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			line->m_color = lineColor;
			return true;
		}
    }
	return false;
}
bool CMapLayer::SetMapLineWidth( short lineID, long lineWidth )
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			line->m_width = lineWidth;
			return true;
		}
    }
	return false;
}
bool CMapLayer::SetMapLineVisible( long lineID, long lVisible )
{
	for (list<CMapLine*>::iterator it = m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        CMapLine* line = *it;
		if ( line->m_lineid == lineID  ) {
			line->m_bVisible = lVisible;
			return true;
		}
    }
	return false;
}
void CMapLayer::RemoveAll()
{
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		delete poi;
    }
	m_arrPoi.clear();
	//��
	for (list<CMapLine*>::iterator it1 = m_arrLine.begin(); it1 != m_arrLine.end(); ++it1)
    {
        CMapLine* line = *it1;
		line->Realse();
		delete line;
    }
	m_arrLine.clear();
	//��
	for (list<CMapPolygon*>::iterator it4 = m_arrPolygon.begin(); it4 != m_arrPolygon.end(); ++it4)
    {
        CMapPolygon* line = *it4;
		line->Realse();
		delete line;
    }
	m_arrPolygon.clear();
	//����
	for (list<CMapText*>::iterator it2 = m_arrMapText.begin(); it2 != m_arrMapText.end(); ++it2)
    {
        CMapText* text = *it2;
		delete text;
    }
	m_arrMapText.clear();
	//Բ
	for (list<CMapAround*>::iterator it3 = m_arrAround.begin(); it3 != m_arrAround.end(); ++it3)
    {
        CMapAround* around = *it3;
		delete around;
    }
	m_arrAround.clear();
}
void CMapLayer::OnDraw( HDC hdc,agg::rendering_buffer* m_rbuf, CMapDisp* pMapDisp, CMapPoiRes* pMapPoiRes )
{
	HBRUSH oldbrush = (HBRUSH)::SelectObject( hdc, m_brushFont );	
	//����
	for (list<CMapLine*>::iterator itline = m_arrLine.begin(); itline != m_arrLine.end(); ++itline)
    {
        CMapLine* line = *itline;
		line->OnDraw( hdc,m_rbuf, pMapDisp );
    }
	//����
	for (list<CMapPolygon*>::iterator itPolygon = m_arrPolygon.begin(); itPolygon != m_arrPolygon.end(); ++itPolygon)
    {
        CMapPolygon* Polygon = *itPolygon;
		Polygon->OnDraw( hdc,m_rbuf, pMapDisp );
    }
	//����
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		poi->OnDraw( hdc, pMapDisp, pMapPoiRes );
    }
	//��Բ
	for (list<CMapAround*>::iterator itaround = m_arrAround.begin(); itaround != m_arrAround.end(); ++itaround)
    {
        CMapAround* around = *itaround;
		around->Draw(hdc,m_rbuf,pMapDisp,pMapPoiRes);
    }
	//�����ϵ�����
	for ( list<CMapPoi*>::iterator it1 = m_arrPoi.begin(); it1 != m_arrPoi.end(); ++it1)
    {
        CMapPoi* poi = *it1;
		poi->DrawPoiName( hdc, pMapDisp );
    }
	//������
	for (list<CMapText*>::iterator ittext = m_arrMapText.begin(); ittext != m_arrMapText.end(); ++ittext)
    {
        CMapText* text = *ittext;
		text->Draw(hdc,pMapDisp);
    }
	::SelectObject( hdc, oldbrush );
}
void CMapLayer::OnDrawTip( HDC hdc,CMapDisp* pMapDisp )
{
	//�����ϵ�����
	//����
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		poi->DrawPoiName( hdc,pMapDisp );
    }
}
//��Ӧ����ƶ��¼�
bool CMapLayer::IsPointIn( VOSPoint point,  CMapPoi*& poi )
{
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->IsPointIn( point ) )
		{
			return true;
		}
    }
	return FALSE;
}
bool CMapLayer::IsPointInDel( VOSPoint point, int& type, int& id )
{
	CMapPoi* poi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->IsPointInDel( point ) )
		{
			type = 6;
			id = poi->m_sPOIID;
			return true;
		}
    }
	return false;
}
bool CMapLayer::IsPointIn( VOSPoint point )
{
	CMapPoi* pPoi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        pPoi = *it;
		if ( pPoi->IsPointIn( point ) )
		{
			return true;
		}
    }
	return false;
}
//�����Ƿ���ʾ
void CMapLayer::SetVisible( bool bVisible )
{
	m_bVisible = bVisible;
}
//�����Ƿ���ʾ
bool CMapLayer::GetVisible( )
{
	return m_bVisible;
}
//ͼ��ID
void CMapLayer::SetLayerID( long lID )
{
	m_llayerID = lID;
}
//�õ�ͼ��ID
long CMapLayer::GetLayerID( )
{
	return m_llayerID;
}
//�õ����ID�ĵ�
CMapPoi* CMapLayer::GetMapPoi( long lid )
{
	CMapPoi* poi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->m_sPOIID == lid ) {
			return poi;
		}
    }
	return NULL;
}
//ɾ��һ����
bool CMapLayer::DeleteMapPoint(long pointID)
{
	CMapPoi* poi = NULL;
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        poi = *it;
		if ( poi->m_sPOIID == pointID ) 
		{
			delete poi;
			m_arrPoi.erase(it);
			return true;
		}
    }
	return NULL;
}
//ɾ��ȫ������Ϣ
void CMapLayer::DeleteAllMapPoint()
{
	for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
    {
        CMapPoi* poi = *it;
		delete poi;
    }
	m_arrPoi.clear();
}
//ɾ��һ����
bool CMapLayer::DeleteMapLine(long lineID)
{
	CMapLine* line = NULL;
	int count = this->m_arrLine.size();
	for (list<CMapLine*>::iterator it = this->m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        line = *it;
		if ( line->m_lineid == lineID ) 
		{
			delete line;
			m_arrLine.erase(it);
			return true;
		}
    }
	return NULL;
}
void CMapLayer::DrawPoiText( long pointID, CMapDisp* pMapDisp )
{

}
//���ư�Բ
bool CMapLayer::CreateMapAround( long uid, double x, double y, long radius, long alpha )
{
	CMapAround* pAround = NULL;
	for (list<CMapAround*>::iterator it = m_arrAround.begin(); it != m_arrAround.end(); ++it)
    {
        pAround = *it;
		if ( pAround->m_rid == uid ) {
			return false;
		}
    }
	pAround = new CMapAround();
	pAround->m_rid = uid;
	pAround->m_mptPoint.x = x;
	pAround->m_mptPoint.y = y;
	pAround->alpha = alpha;
	pAround->m_radius = radius;
	pAround->SetColor( 0x00FFFF );
	m_arrAround.push_back( pAround );
	return TRUE;
}
bool CMapLayer::DeleteMapAround( long uid )
{
	CMapAround* pAround = NULL;
	for (list<CMapAround*>::iterator it = this->m_arrAround.begin(); it != m_arrAround.end(); ++it)
    {
        pAround = *it;
		if ( pAround->m_rid == uid ) 
		{
			delete pAround;
			m_arrAround.erase(it);
			return true;
		}
    }
	return false;
}
//��������
bool CMapLayer::CreateMapText(long tid, double x, double y, LPCTSTR text, long size, long color)
{
	CMapText* pText = NULL;
	for (list<CMapText*>::iterator it = m_arrMapText.begin(); it != m_arrMapText.end(); ++it)
    {
        pText = *it;
		if ( pText->tid == tid ) {
			return false;
		}
    }
	pText = new CMapText();
	pText->tid = tid;
	pText->m_Point.x = x;
	pText->m_Point.y = y;
	pText->text = text;
	pText->m_size = size;
	pText->color = color;
	pText->SetMapTextFont( size,0,0,700,1,0,0,0,"΢���ź�" );
	m_arrMapText.push_back( pText );
	return true;
}
bool CMapLayer::DeleteMapText(long tid)
{
	CMapText* pText = NULL;
	for (list<CMapText*>::iterator it = this->m_arrMapText.begin(); it != m_arrMapText.end(); ++it)
    {
        pText = *it;
		if ( pText->tid == tid ) 
		{
			delete pText;
			m_arrMapText.erase(it);
			return true;
		}
    }
	return false;
}
//�������������size���ֺţ�16����width ������(Ĭ��0), escapement ������ʾ�ĽǶ�(0),orientation ����ĽǶ�(0)
//weight ����İ���(Ĭ��400������Ϊ700), Italic(Ĭ��0,1Ϊб��)��underline(0,1Ϊ�»���),strikeOut(0,1Ϊɾ����)
//fontname ��������(Ĭ��"����"������Ϊ"΢���ź�"��)
bool CMapLayer::SetMapTextFont(long tid,long size, long width, long escapement, long orientation, long weight, long Italic, long underline, long strikeOut, LPCTSTR fontname)
{
	CMapText* pText = NULL;
	for (list<CMapText*>::iterator it = this->m_arrMapText.begin(); it != m_arrMapText.end(); ++it)
    {
        pText = *it;
		if ( pText->tid == tid ) 
		{
			pText->SetMapTextFont( size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
			return true;
		}
    }
	return false;

//return m_mainLayer.SetMapTextFont( size,width,escapement,orientation,weight,Italic,underline,strikeOut,fontname );
}//��������ζ���
bool CMapLayer::CreatMapPolygon(short polygonID )
{
	for (list<CMapPolygon*>::iterator it = m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        CMapPolygon* line = *it;
		if ( line->m_polygonID == polygonID  ) {
			return false;
		}
    }
	CMapPolygon* pNewLine = new CMapPolygon();
	pNewLine->m_polygonID = polygonID;
	pNewLine->SetColor( 0x000000 );
	pNewLine->SetWidth( 1 );
	m_arrPolygon.push_back(pNewLine);

	int count = this->m_arrPolygon.size();
	return true;
}
//��ӵ�
bool CMapLayer::AddMapPolygonPoint( short polygonID, MapPoint* pPoint )
{
	for (list<CMapPolygon*>::iterator it = m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        CMapPolygon* line = *it;
		if ( line->m_polygonID == polygonID  ) {
			line->AddPoint( pPoint );
			return true;
		}
    }
	return false;
}
//ɾ������ζ���
bool CMapLayer::DeleteMapPolygon(short polygonID)
{

	CMapPolygon* line = NULL;
	int count = this->m_arrPolygon.size();
	for (list<CMapPolygon*>::iterator it = this->m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        line = *it;
		if ( line->m_polygonID == polygonID ) 
		{
			delete line;
			m_arrPolygon.erase(it);
			return true;
		}
    }
	return NULL;
}
CMapLine* CMapLayer::GetMapLine(short lid)
{
	CMapLine* line = NULL;
	int count = this->m_arrLine.size();
	for (list<CMapLine*>::iterator it = this->m_arrLine.begin(); it != m_arrLine.end(); ++it)
    {
        line = *it;
		if ( line->m_lineid == lid ) 
		{
			return line;
		}
    }
	return NULL;
}
CMapPolygon* CMapLayer::GetMapPolygon(short pid)
{
	CMapPolygon* line = NULL;
	int count = this->m_arrPolygon.size();
	for (list<CMapPolygon*>::iterator it = this->m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        line = *it;
		if ( line->m_polygonID == pid ) 
		{
			return line;
		}
    }
	return NULL;
}
//���õ�ͼ�ɱ༭
long CMapLayer::OpenMapEdit(long type, long id, bool bedit)
{
	if( type == 6 )
	{
		CMapPoi* pPoi = NULL;
		for (list<CMapPoi*>::iterator it = m_arrPoi.begin(); it != m_arrPoi.end(); ++it)
		{
			pPoi = *it;
			if ( pPoi->m_sPOIID == id ) 
			{
				pPoi->OpenEdit( bedit );
				return 1;
			}
		}
	}
	return 0;
}
//���ö��������
long CMapLayer::SetMapPolygonName(long pid, const char* name )
{
	for (list<CMapPolygon*>::iterator it = m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        CMapPolygon* pPolygon = *it;
		if ( pPolygon->m_polygonID == pid  ) {
			pPolygon->SetName( name );
			return 1;
		}
    }
	return 0;
}
//���ö������ɫ
long CMapLayer::SetMapPolygonColor(long pid, long colorbgr)
{
	for (list<CMapPolygon*>::iterator it = m_arrPolygon.begin(); it != m_arrPolygon.end(); ++it)
    {
        CMapPolygon* pPolygon = *it;
		if ( pPolygon->m_polygonID == pid  ) {
			pPolygon->SetColor( colorbgr );
			return 1;
		}
    }
	return 0;
}
//����Բ����
void CMapLayer::SetMapAroundName(long rid, const char* name )
{
	//Բ
	for (list<CMapAround*>::iterator it3 = m_arrAround.begin(); it3 != m_arrAround.end(); ++it3)
    {
        CMapAround* around = *it3;
		if ( around->m_rid == rid  ) {
			around->m_strname = name ;
			return ;
		}
    }
	return ;
}
long CMapLayer::SetMapAroundColor(long rid, long colorbgr)
{
	//Բ
	for (list<CMapAround*>::iterator it3 = m_arrAround.begin(); it3 != m_arrAround.end(); ++it3)
    {
        CMapAround* around = *it3;
		if ( around->m_rid == rid  ) {
			around->m_color = colorbgr ;
			return rid;
		}
    }
	return 0;
}