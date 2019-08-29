#ifndef _JW2_STD_H_
#define _JW2_STD_H_

/************************************************************************/
/* 对外接口定义                                                         */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

//	初始化资源
__declspec(dllexport) bool jw2_initialize();

//	卸载资源
__declspec(dllexport) void jw2_uninitialize();

/**
  *  对坐标进行加密
  *
  *		@param pinx		[in]	 一串x经度坐标，在坐标传入该函数之前需要*1000000
  *		@param piny		[in]	 一串y维度坐标，在坐标传入该函数之前需要*1000000
  *		@param pinx		[out]	 加密后的一串x经度坐标,比如 实际经度 = pinx[0]/1000000
  *		@param piny		[out]	 加密后的一串y维度坐标,比如 实际经度 = piny[0]/1000000
  *		@param ncount	[in]	 传入坐标点的个数
  *
  *		@return 成功返回加密点的个数
  *				失败 -1,表示坐标超过了中国的范围
  *				失败 -2,表示没有插入狗	
  *	
  *		@mark	调用此函数之前必须调用 jw2_initialize()
  *	
  */
__declspec(dllexport) int jw2_transcoord( int* pinx, int* piny, int* poutx, int*pouty, int ncount );

#ifdef __cplusplus
}
#endif 



#endif  // _JW2_STD_H_
