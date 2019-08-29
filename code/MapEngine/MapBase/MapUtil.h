#pragma once

#include "MapDefine.h"
class CMapUtil
{
public:
	CMapUtil(void);
	~CMapUtil(void);
	static void stroke_round( agg::renderer_base<agg::pixfmt_bgra32>* renb, int r, int C_x, int C_y, agg::rgba8& color, float step = 0.01);
};
