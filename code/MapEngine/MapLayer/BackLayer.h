// BackLayer.h: interface for the CBackLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_)
#define AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MapLayer.h"
// POINT �ṹ�嶨��
typedef VOS_EXPORT struct _mapPOI
{ 
	double dx;
	double dy;
	string strICO;
	string strName;
	string strText;
	_mapPOI()
	{
		dx =0;
		dy =0;
	}
} mapPOI, *LPmapPOI; 
// �� �ṹ�嶨��
typedef VOS_EXPORT struct _mapLine
{ 
	vector<MapPoint*> m_arrMapPoint;
	_mapLine()
	{
	}
} mapLine, *LPmapLine; 

class CBackLayer : public CMapLayer
{
public:
	CBackLayer();
	virtual ~CBackLayer();

	//���ص�ͼ����
	void Load( string strFilePath,CMapPoiRes* pRes );
	//����KML��ʽ��ͼ
	bool LoadKML();
	//��ӵ�ͼ��Ϣ��
	bool SaveMapPoint( double x, double y, string strName, string strText, long icoID );

	//��ӵ�ͼ��,
	bool SaveMapLine( string strMapPoints, string strName, long width, long bgrcolor  );
	
	//��ӵ�ͼ�ı���Ϣ
	bool SaveLocMapText( double x, double y, string strText, long fontsize, long bgrcolor );

	//�����ͼ������Ϣ
	bool ClearMapSaveData();

	//�������е�ͼ��
	void SaveAllMapPoint();
	void SaveAllMapLine();
	void SaveAllMapText();
	void SaveAllMapPolygon();
	//�õ���ǰλ�õ���ϢID,0Ϊ�����ݣ�1Ϊ����Ϣ��2Ϊ����Ϣ
	int GetLocID( long& lID, VOSPoint point );
private:
	
	//��ȡ���е�ͼ��
	bool ReadMapPoint();
	bool ReadMapLine();
	bool ReadMapPolygon();
	bool ReadMapText();
	bool ReadMap123();
	bool LoadMap2000();
	//����
	char* ParseMapPoint(char* pBuf, int iLen, int nIndex );
	//����
	char* ParseMapLine(char* pBuf, int iLen, int nIndex );
	char* ParseMapPolygon(char* pBuf, int iLen, int nIndex );
	//����
	char* ParseMapText(char* pBuf, int iLen, int nIndex );
	//����KML��ʽ��ͼ
	bool ParseKML( char* pData, int nlen );
	char* ParasKMLData( char* pData, int nlen );
private:
	string m_strFilePath;
//	vector<mapPOI*> m_arrMapPoi;
//	vector<mapLine*> m_arrMapLine;
	CMapPoiRes*		 m_pMapPoiRes;
	long			 m_lICOID;
	long			 m_lID;
};

#endif // !defined(AFX_BACKLAYER_H__2731AF57_85F4_4F2D_8E12_40DC606A0531__INCLUDED_)
