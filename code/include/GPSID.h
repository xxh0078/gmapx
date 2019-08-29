#ifndef RITU_GPSID_H
#define RITU_GPSID_H

extern "C"
{
	//将经纬度转换成全局GPSID
	//输入：经纬度
	//输出：GPSIDg 的字符串形式，定长20个字符,以 \0 结束
	int GPSID_RawToGlobal(double x, double y, char GPSIDg[21]);

	//将全局GPSID转换成经纬度
	//输入：GPSIDg 的字符串形式，定长20个字符,最好以 \0 结束
	//输出：经纬度的字符串形式
	int GPSID_GlobalToRaw(char GPSIDg[21], char lon[10], char lat[10]);

	//取得当前库的版本号
	//返回的2字节整数，如0x0100,代表版本号是1.0,如0x0201,代表版本号是2.1，类推
	unsigned short GPSID_Version();
};


#endif