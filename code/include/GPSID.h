#ifndef RITU_GPSID_H
#define RITU_GPSID_H

extern "C"
{
	//����γ��ת����ȫ��GPSID
	//���룺��γ��
	//�����GPSIDg ���ַ�����ʽ������20���ַ�,�� \0 ����
	int GPSID_RawToGlobal(double x, double y, char GPSIDg[21]);

	//��ȫ��GPSIDת���ɾ�γ��
	//���룺GPSIDg ���ַ�����ʽ������20���ַ�,����� \0 ����
	//�������γ�ȵ��ַ�����ʽ
	int GPSID_GlobalToRaw(char GPSIDg[21], char lon[10], char lat[10]);

	//ȡ�õ�ǰ��İ汾��
	//���ص�2�ֽ���������0x0100,����汾����1.0,��0x0201,����汾����2.1������
	unsigned short GPSID_Version();
};


#endif