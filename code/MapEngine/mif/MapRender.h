/************************************************************
  �ļ���: MapRender.h
  
  ����:   Ǯ����       Version : 1.0          Date: 2002/12/21
  
  ������: ��ͼ������Ĺ���
  
  �ʼ���ַ��Visual20@sohu.com
***********************************************************/


#ifndef _MAP_RENDER_H_
#define _MAP_RENDER_H_
#include <afxtempl.h>

#define MAX_CLASSNUM     //��������

typedef enum 
{
	SIMPLE_RENDER,
    UNIQUE_RENDER

} RENDERTYPE;

typedef struct simpleRender
{
	COLORREF FillColor;
    COLORREF OutlineColor;
	int      iIndex;

}SIMPLERENDER;

typedef struct renderInfo
{
	CString   csValue;
	COLORREF  clr;

}RENDERINFO;

class CMapRender 
{
public:
   CMapRender();
   ~CMapRender();
public:
   void  Add(RENDERINFO& rInfo );
   void  RemoveByValue(CString& csValue);
   void  RemoveByIndex(int iIndex );
   int   GetCount();
   RENDERINFO* GetByValue(CString& csValue);
   RENDERINFO* GetByIndex(int iIndex);
   void Clear();
   void SetRenderType(int m_Type) { m_RenderType = m_Type; };
   int  GetRenderType() { return m_RenderType; };
   void SetSimpleRender( SIMPLERENDER& simpleRender );
   void GetSimpleRender( SIMPLERENDER& simpleRender );
   void SetFieldIndex(int iIndex);
   int  GetFieldIndex();
   void Clone(CMapRender *pRender);
private:  
   SIMPLERENDER  m_SimpleRender; 
   int m_RenderType;
   int m_FieldIndex;
private:
	CArray<RENDERINFO*,RENDERINFO*> m_Render;

};
#endif //_MAP_RENDER_H_