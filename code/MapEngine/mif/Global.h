#ifndef _MAP_GLOBAL_H_
#define _MAP_GLOBAL_H_

#define infinity 1e20           //����Ϊ�����
#define EP 1e-10                //��������С   

typedef unsigned char uchar;
typedef unsigned int  uint;

typedef struct DrawParam {
	
	double m_StartX;       //��ǰ����ԭ�������
	double m_StartY;       //��ǰ����ԭ�������� 
	int m_ScreenWidth;  //��ǰ��Ļ���
	int m_ScreenHeigh;  //��ǰ��Ļ�߶�
	double m_Top;
	double m_left;
	float m_Scale;      //��ǰ��ͼ������     


} DRAWPARAM;

/************************************************************************/
/*                              SwapWord()                              */
/*                                                                      */
/*      Swap a 2, 4 or 8 byte word.                                     */
/************************************************************************/

 static void	SwapWord( int length, void * wordP )

{
    int		i;
    uchar	temp;

    for( i=0; i < length/2; i++ )
    {
	temp = ((uchar *) wordP)[i];
	((uchar *)wordP)[i] = ((uchar *) wordP)[length-i-1];
	((uchar *) wordP)[length-i-1] = temp;
    }
}

#endif //_MAP_GLOBAL_H_