/************************************************************
  文件名: MapLayer.h
  
  作者:   钱军洪       Version : 1.0          Date: 2002/12/21
  
  类描述: 地图图层数据管理
  
  邮件地址：Visual20@sohu.com
***********************************************************/

#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_

#include "MapRectangle.h"
#include "shpFile.h"
#include "MaprecordSet.h"
#include "MapRender.h"
  


class CMapLayer {

public:
	CMapLayer();
	~CMapLayer();

//Attribute
public:
    CMapRectangle GetExtent();
	BOOL ReadShp(CString& csFileName);
	long GetShpType();
	BOOL GetVisible();
	BOOL LoadData(CString& csFileName);
	void SetVisible(bool bVisible);
	void SetLayerName(CString& csLayerName );
	CString GetLayerName();
    int SearchShape(CMapPoint& pt );
	void SetRender(CMapRender* pRender ); 
	void DrawLayer(CDC*pDC , DrawParam& draw);
	void FlashShp(CDC*pDC , DrawParam& draw , int iIndex);
	CMapRecordSet* GetRecordSet() { return m_shpFile.pRecordSet;};
    CMapRender* GetRender() { return m_pRender; } ;
protected:
	void SetExtent(CMapRectangle& extent );
	void SetShpType(int lShpType );

public:
	
	//CMapRecordSet *pRecordSet;
private:  
	BOOL m_bVisible;
	BOOL m_Valid;
	CMapRectangle m_Extent;
	CShpFile m_shpFile;
	CString m_csLayerName;
	CMapRender* m_pRender;

	
};	

#endif //_MAP_LAYER_H_ 