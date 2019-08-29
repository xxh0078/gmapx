#pragma once
#include "../VOSBase/VOSBase.h"
#include "../MapBase/MapBase.h"
class CMapData;
struct tDownLoadParam
{
	int iX;			//X
	int iY;			//Y
	int iZ;			//Y
	int	iState;		//״̬��0Ϊ�ȴ����أ�1Ϊ�������أ�2Ϊ�������,3Ϊ����ʧ��
	int iMapID;		//��ͼID
	
	tDownLoadParam()
	{
		iX = 0;			//X
		iY = 0;			//Y
		iZ = 0;			//Y
		iState = 0;		//״̬��0Ϊ�ȴ����أ�1Ϊ�������أ�2Ϊ�������,3Ϊ����ʧ��
		iMapID = 0;		//��ͼID
	}
	const tDownLoadParam& operator=( const tDownLoadParam& param )
	{
		iX = param.iX;
		iY = param.iY;
		iZ = param.iZ;
		iState = param.iState;
		iMapID = param.iMapID;
		return * this;
	}
};

class CMapDataDown
{
public:
	CMapDataDown(void);
	~CMapDataDown(void);
	
	//��ʼ��
	void Init( CMapData* pMapData );
	
	//��������
	bool SetMapType( en_MapType enMapType );
	
	//�ͷ��ڴ�
	void Realse();

	//�������������б��б�
	bool AddDownLoadList( int x, int y, int z,int iMapType );

	//�������б��ȡһ����������ø�������Ϊ����״̬
	bool GetNoDownLoadList( tDownLoadParam*& param );

	//�õ�һ���������ص��б�
	bool GetDownLoadList( tDownLoadParam*& param );

	//����б�
	bool ClearDownLoadList();
	
	//���û�п�ʼ���ص��б�
	bool ClearNoDownLoadList();

	//�����߳�
	static unsigned long __stdcall Worker( void* pParameter );
	int RUN();
private:
	//����
	bool DownLoadMapData( short sLevel, long lNumX, long lNumY,int iMapID,struct MemoryStruct *chunk );
private:
	list<tDownLoadParam*>		m_listDownLoadParam;			//�����б�
	HANDLE						m_hLoadMutex;				// �̻߳�����
	bool		m_bExitProc;
	CMapData*	m_pMapData;
	en_MapType					 m_enMapType;				//��ͼ����
};
