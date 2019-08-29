// bspng.h: interface for the bspng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSPNG_H__DD65F7F1_C8BA_4DD5_A00B_0E925347F86C__INCLUDED_)
#define AFX_BSPNG_H__DD65F7F1_C8BA_4DD5_A00B_0E925347F86C__INCLUDED_

#include "../../include/png/png.h"
class bspng  
{
public:
	bspng();
	virtual ~bspng();
	static int check_if_png( char* filename, FILE** fp );
	static bool GetpngInfo( char* stream, int width, int height, char& byBitsPixel );
	static int loadpng( char* stream, char*& data );
	static int savepng( char* filename, FILE** fp );

};

#endif // !defined(AFX_BSPNG_H__DD65F7F1_C8BA_4DD5_A00B_0E925347F86C__INCLUDED_)
