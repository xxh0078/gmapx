/************************************************************
  �ļ���: MapLayers.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ��ͼͼ�����ݼ��Ϲ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/

#ifndef _MAP_LAYERS_H_
#define _MAP_LAYERS_H_

#include "MapLayer.h"

class CMapLayers {


public:
	CMapLayers();
	~CMapLayers();

// Attributes
public:
	short GetCount();
	void SetCount(short);
	void GetAllExtent(CMapRectangle& rc);

// Operations
public:
	CMapLayer* GetAt(short sIndex);
	BOOL Add(CMapLayer* pMapLayer);
	void Remove(short sIndex);
	void Clear();
	void MoveTo(short fromIndex, short toIndex);
	void MoveToTop(short sIndex);
	void MoveToBottom(short sIndex);


private:
	CArray<CMapLayer*,CMapLayer*> m_Layers; //�洢ͼ�㼯�϶���


};

#endif //_MAP_LAYERS_H_