/************************************************************
  �ļ���: MapPoint.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: �Ե��������Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_POINT_H_
#define _MAP_POINT_H_


class CMapPoint:public CObject {

    DECLARE_DYNAMIC(CMapPoint)
public:
	CMapPoint();
    CMapPoint(CMapPoint& pt);  
	virtual ~CMapPoint();
public:
	void   SetX(double& dbX ) { m_dbX = dbX;};
	void   SetY(double& dbY ) { m_dbY = dbY;};
	void   SetIndex(unsigned int uiIndex ) { m_uiIndex = uiIndex ; };
	unsigned int GetIndex() { return m_uiIndex; }; 
	void   SetStatus(bool& bStatus) { m_bStatus = bStatus;};
	double GetX() { return m_dbX;};
	double GetY() { return m_dbY;};
	double Distance(CMapPoint& pt );
  	bool   GetStatus() { return m_bStatus;};
	bool   IsEqual(CMapPoint& pt );
	bool   IsPointInLine(CMapPoint& p1 , CMapPoint& p2 );
    
private:
	bool   m_bStatus;    //0---��ѡ��״̬, 1---ѡ��״̬
        
	unsigned int m_uiIndex;  //����ֵ
	double m_dbX;
	double m_dbY;
	CString m_csID;
};

#endif //_MAP_POINT_H_
