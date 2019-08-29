#ifndef _JW2_STD_H_
#define _JW2_STD_H_

/************************************************************************/
/* ����ӿڶ���                                                         */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

//	��ʼ����Դ
__declspec(dllexport) bool jw2_initialize();

//	ж����Դ
__declspec(dllexport) void jw2_uninitialize();

/**
  *  ��������м���
  *
  *		@param pinx		[in]	 һ��x�������꣬�����괫��ú���֮ǰ��Ҫ*1000000
  *		@param piny		[in]	 һ��yά�����꣬�����괫��ú���֮ǰ��Ҫ*1000000
  *		@param pinx		[out]	 ���ܺ��һ��x��������,���� ʵ�ʾ��� = pinx[0]/1000000
  *		@param piny		[out]	 ���ܺ��һ��yά������,���� ʵ�ʾ��� = piny[0]/1000000
  *		@param ncount	[in]	 ���������ĸ���
  *
  *		@return �ɹ����ؼ��ܵ�ĸ���
  *				ʧ�� -1,��ʾ���곬�����й��ķ�Χ
  *				ʧ�� -2,��ʾû�в��빷	
  *	
  *		@mark	���ô˺���֮ǰ������� jw2_initialize()
  *	
  */
__declspec(dllexport) int jw2_transcoord( int* pinx, int* piny, int* poutx, int*pouty, int ncount );

#ifdef __cplusplus
}
#endif 



#endif  // _JW2_STD_H_
