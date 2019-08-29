#pragma once
#include "../MapBase/MapBase.h"

class CMapBlockUnit
{
public:
	CMapBlockUnit(void);
	~CMapBlockUnit(void);
	//��ʼ�����е����ݿ�
	//void Init( HWND hwnd );
	//����
	void Draw( HDC hdc,short sStart, short sStartY );
	//����png����
	bool LoadPng( string strPath );
	//����jpg����,-1Ϊ��һ�����ݼ���ʧ�ܣ�-2Ϊ�ڶ������ݼ���ʧ�ܣ�>0Ϊ�ɹ�
	bool LoadImg( string strPath );
	bool LoadImg( char* pData, int len );
public:
//	MapBlockUnit m_mapBlock;		//��ͼ�����
//	long		lStartX;			//X�������λ��
//	long		lStartY;			//Y�������λ��
	bool		bDraw;				//����Ƿ���Ҫ����
	long		lLevel;				//������
	long		lNumX;				//X������
	long		lNumY;				//Y������
	//bool		bLoad;				//�Ƿ����
	//bool		bDown;				//�Ƿ�����
private:
	long		lWidth;
	long		lHeight;
	unsigned char* data;			//ͼƬ����
	HBITMAP		m_hBmp;
	HDC			m_memdc;
	CVOSImage*  m_VOSImage;
};
