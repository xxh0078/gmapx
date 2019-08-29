#pragma once
#include "../VOSBase/VOSBase.h"
class CMapDisp;
//#include <windows.h>
class CDownLoadParam
{
public:
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
	int	iState;		//״̬��0Ϊ�ȴ����أ�1Ϊ�������أ�2Ϊ�������
	int iMapID;		//��ͼID
};

class CMapDataDown
{
public:
	CMapDataDown(void);
	~CMapDataDown(void);
	//��ʼ��
	void Init( CMapDisp* pMapDisp );
	//�ͷ�
	void realse();

	//�������������б��б�
	bool AddDownLoadList( int x, int y, int z,int iMapType );

	//�������б��ȡһ����������ø�������Ϊ����״̬
	bool GetNoDownLoadList( CDownLoadParam*& param );

	//�õ�һ���������ص��б�
	bool GetDownLoadList( CDownLoadParam*& param );

	//ɾ��һ��������
	bool RemoveDownLoadList( int x, int y, int z );

	//����б�
	bool ClearDownLoadList();
	
	//���û�п�ʼ���ص��б�
	bool ClearNoDownLoadList();

	//���������غ���ļ���
	bool RenameDownLoadFile( CDownLoadParam* pParam );

	//
	bool bLoacked();

	//�����߳�
	static unsigned long __stdcall DownLoadProc( void* pParameter );

private:
	//��ȡ�ȸ賣���ͼ
	bool DownLoadMap( CDownLoadParam* pParam, struct MemoryStruct *chunk );
	
public:
	//�����б�
	list<CDownLoadParam*>	m_arrDownLoadParam;		//�����б�
//	CDownLoadParam	m_DownLoadParam[100];			//�ȴ������б�
//	int				m_iDownLoadCount;				//�ȴ������б�����
	//
	HANDLE			m_hDownLoadMutex;				// �̻߳�����
//	CRITICAL_SECTION	m_cs;						// �ٽ���
public:
	CMapDisp*       m_pMapDisp;						// ��ͼ��ʾ��
};
