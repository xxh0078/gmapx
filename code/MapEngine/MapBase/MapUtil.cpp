#include "StdAfx.h"
#include "MapUtil.h"

CMapUtil::CMapUtil(void)
{
}

CMapUtil::~CMapUtil(void)
{
}
inline void stroke_line( agg::renderer_base<agg::pixfmt_bgra32>* renb, int x1, int y1, int x2, int y2, agg::rgba8& color )
{
    double precision = max(abs(x1 - x2), abs(y1 - y2));
    //精度，也就是画多少个点

    for(int i=0; i <= precision; i++)
        renb->copy_pixel( x1 + ( x2 - x1 ) / precision * i, //x
            y1 + ( y2 - y1 ) / precision * i, //y
            color);
}
void CMapUtil::stroke_round( agg::renderer_base<agg::pixfmt_bgra32>* renb, int r, int C_x, int C_y, agg::rgba8& color, float step )
{
    int prev_x = int(r * cos(-0.01)) + C_x,
        prev_y = int(r * sin(-0.01)) + C_y; //保存上一个点

    int x, y; //保存当前的点
    for(double rad = 0; rad < 2 * PI + step; rad+= step) {
        x = int(r * cos(rad)) + C_x;
        y = int(r * sin(rad)) + C_y; //计算弧度为rad时的坐标
        stroke_line( renb, x, y, prev_x, prev_y, color);
        prev_x = x; prev_y = y;
    }
}