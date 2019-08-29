#pragma once
#include "MapBlockUnit.h"
#include "MapDataDown.h"
#include "MapData.h"
class CMapDisp;

class CLoadParam
{
public:
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
};
class CMapDispLayer
{
public:
	CMapDispLayer(void);
	~CMapDispLayer(void);
	//��ʼ�����е����ݿ�
	void Create( CMapDisp* pMapDisp );
	//���ص�ͼ����
	void LoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd, bool bZoom = true );
	//���¼��ص�ͼ����
	void ReLoadMapData( int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd );
	void OnMoveMap( int iDx, int iDy );
	void OnDraw( HDC hdc, int iLevel, MPoint& gptMapCenter,VOSRect& rcWnd );

	//���õ�ͼ����
	void SetMapType( en_MapType eMapType, string strRootPath, string strMapName = "", string strMapURL = "" );
	//���õ�ͼ·��
	void SetMapPath( string strMapPath );
	//�õ���ͼ�ļ�·��
	void GetMapPath( int x,int y,int z,string& strMapPath );
	//������������
	void LoadMapOther();
private:
	//��鵱ǰ�Ļ����б����Ƿ���ڸĻ��Ʋ���
	bool CheckParamInDrawList( CMapBlockUnit* pBlockParam, int iLevel, int iMinX, int iMaxX, int iMinY, int iMaxY );
private:
	CMapData		m_MapData;
	CMapBlockUnit	m_MapBlockUnit[_BLOCK_MAX_NUM];
	int				m_iBlockCount;
	HWND			m_hwnd;
	int				m_iLevel;
	string			m_strRootPath;
	string			m_strMapURL;
	en_MapType	    m_enMapType;
	string			m_strMapPath;
	CMapDisp*		m_pMapDisp;
	MPoint			m_gptMapCenter;				//---
};
