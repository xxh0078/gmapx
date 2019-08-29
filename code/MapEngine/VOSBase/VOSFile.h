#pragma once

#include "VOSDefine.h"

enum VOSFileOpenMode
{
	fomOnlyRead				= 0x0001,	// ֻ��
	fomOnlyWrite			= 0x0002,	// ֻд
	fomReadWrite			= 0x0004,	// ��д
	fomShareOnlyRead		= 0x0100,	// ����ֻ������
	fomShareOnlyWrite		= 0x0200,	// ����ֻд����
	fomShareReadWrite		= 0x0400,	// �����д����
	fomNoInherit			= 0x0080,	
	fomCreate				= 0x1000,	// ����������ļ����ڣ��ļ����ȱ����㡣
	fomCreateNoTruncate		= 0x2000,	// ����������ļ����ڣ��ļ�������ա�
	fomTypeText				= 0x4000, // typeText and typeBinary are used in
	fomTypeBinary			= 0x8000, // derived classes only
};
enum VOSFileSeekPosition
{
	fspBegin	= 0x00,		// ��λ��
	fspCurrent	= 0x01,		// ��ǰλ��
	fspEnd		= 0x02,		// βλ��
};
class VOS_EXPORT CVOSFile
{
public:
	CVOSFile(void);
	~CVOSFile(void);
//	bool Open( const vchar* strFileName,char* type );
	bool Open( const vchar* strFileName, int etype );
	int Write( void * buffer, int ilen);
	int Read( void * buffer, int ilen);
	
	/**
	  *	�ƶ��ļ�ָ�뵽ָ����λ��
	  *		@param lOffset [in] �ƶ�λ�õ�ƫ����
	  *		@param posFrom [in] �ƶ�λ�õ���Ի�׼
	  *
	  *		@return �µ��ļ�ָ��λ��,����ʧ�ܷ���-1.
	  */
	ulong Seek( long lOffset, VOSFileSeekPosition posFrom );

	/**
	  *	�ƶ��ļ�ָ�뵽ָ����λ��(��չ��������,֧��64λ)
	  *
	  *		@param llOffset    [in] �ƶ�λ�õ�ƫ����
	  *		@param pNewPointer [in/out] �ƶ�����µ��ļ�ָ��λ��
	  *		@param posFrom	   [in] �ƶ�λ�õ���Ի�׼
	  *
	  *		@return �ɹ�����VOS_TRUE,���򷵻�VOS_FALSE.
	  *		@note	����ִ�гɹ���pNewPointer��ŵ����µ��ļ�ָ��λ��.
	  */
	bool SeekEx( long llOffset,long* pNewPointer, VOSFileSeekPosition posFrom );

	/** �ƶ��ļ�ָ�뵽�ļ��ײ� */
	void SeekToBegin( );

	/**
	  *	�ƶ��ļ�ָ�뵽�ļ�β��
	  *		@return �����ƶ�����ļ�ָ��λ��,����ʧ�ܷ���-1.
	  */	
	ulong SeekToEnd( );

	void Flush();
	void Close();
	ulong GetLength();
	void SetLength( ulong len );
	static bool Rename( const vchar* strOldName, const vchar* strNewName );
	static bool Remove( const vchar* strFileName );
	static bool CreateDirectory( const vchar* strFileName );
	static bool IsExit( const vchar* strFileName );
private:
//	bool Open( const vchar* strFileName,char* type );
	//FILE * fp;
	HANDLE m_hFile;
};
