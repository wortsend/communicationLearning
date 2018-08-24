/**
 *date:20180816
 *filename:RadarDataReceiver
 *version:1.0
 *author:molly
 *description:接收雷达发送的数据
 */
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>
#include<iostream>
#include <fstream>//写入文件
#define LoadSize 302//每一包的大小
#define PortNum  5150      //端口号
#define BfSize 1208 //缓存器大小
#define PackSize 9   //包个数
#define RadarNum 6// 雷达个数
#define PackNum 30   //每包中数据的个数
using namespace std;


//用于测试
//INT32 test_data[] = { 0,1,1793,1007205,0,78,105,255,128,32,1,130,1793,1007232,1,78,153,255,128,32,1,112,1793,1007258,2,78,185,254,128,32,1,118,1793,1007284,3,78,218,2,128,32,1,118,1793,1007310,4,79,18,2,128,32,1,102,1793,1007336,5,79,66,9,128,32,3,97,1793,1007362,6,79,162,12,128,32,3,92,1793,1007390,7,79,185,240,128,32,3,82,1793,1007417,8,79,242,7,128,32,3,77,1793,1007443,9,80,18,5,128,32,3,78,1793,1007470,10,80,18,17,128,32,3,82,1793,1007496,11,79,242,32,128,32,3,85,1793,1007522,12,80,65,176,128,32,3,112,1793,1007548,13,80,137,171,128,32,3,114,1793,1007574,14,79,82,153,128,32,4,206,1793,1007600,15,83,57,237,128,32,3,91,1793,1007626,16,78,90,0,128,32,1,117,1793,1007653,17,78,121,255,128,32,1,127,1793,1007679,18,79,9,252,128,32,1,105,1793,1007705,19,79,186,9,128,32,4,99,1793,1007732,20,80,113,241,128,32,4,74,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1536,1014183,17,4,1,71,16,0,0,0,240,21 };









struct TEST_DATA
{
	INT32 test_buffer[LoadSize] = {0};

};
struct PACK_DATA
{
	INT32 pack_data[PackSize][LoadSize] = {0};
	int flag = 0;
};
struct CONVERT_DATA
{
	double TargetDPS = 0.0;
	int RadarID = 0;
	int FrameCount = 0;
	int TargetID = 0;
	double TargetDistLong = 0.0;
	double TargetDistLat = 0.0;
	double TargetVrel = 0.0;
	double TargetRCS = 0.0;
	double Time = 0.0;
	double ESC_VehicleSpeed = 0.0;
};
struct RETURNINFO//保存转换后的一帧数据
{
	CONVERT_DATA cd[PackNum*PackSize];
	int total_num;
};

void Print_Test_Data(TEST_DATA *td)//打印结构体
{
	if (td == NULL)
	{
		cout << "error:结构体为空!" << endl;
		return;
	}
	for (int i = 0; i < LoadSize; i++)
	{
		cout << td->test_buffer[i] << endl;
	}
	return;
}
int Print_Test_Data_Length(TEST_DATA *td)//打印结构体长度
{
	if (td == NULL)
	{
		cout << "error:结构体为空!" << endl;
		return 0;
	}

	return sizeof(td);
}
void Save_Test_Data(TEST_DATA*td)//保存td结构体到文件中
{
	if (td == NULL)
	{
		cout << "error:结构体为空!" << endl;
		return;
	}
	//写入文件
	ofstream fout;     //创建一个data.txt的文件，用于存储数据
	fout.open("E:\\socketLearning\\RadarDataDemo\\data.txt", ios::app);//打开文件，输出的数据追加到文件末尾
	for (int i = 0; i < LoadSize; i++)
	{
		fout << td->test_buffer[i] << " ";  //将变量的值写入文件
	}
	fout << endl << endl;
	fout.close();                  //关闭文件
	return;
}
void Save_Convert_Pack(RETURNINFO &info)//保存每个雷达的一帧数据，测试没问题
{
	if (&info == NULL)
	{
		cout << "error:结构体为空!" << endl;
		return;
	}
	//写入文件
	ofstream fout;     //创建一个convert_data.txt的文件，用于存储数据
	fout.open("E:\\socketLearning\\RadarDataDemo\\convert_data.txt", ios::app);//打开文件，输出的数据追加到文件末尾
	fout << "TargetDPS  RadarID	 FrameCount  TargetID  TargetDistLong   TargetDistLat      TargetVrel  TargetRCS  Time  ESC_VehicleSpeed" << endl;
	for (int i = 0; i < info.total_num; i++)
	{
		fout << info.cd[i].TargetDPS << "              ";  //将变量的值写入文件
		fout << info.cd[i].RadarID << "            ";  //将变量的值写入文件
		fout << info.cd[i].FrameCount << "          ";  //将变量的值写入文件
		fout << info.cd[i].TargetID << "              ";  //将变量的值写入文件
		fout << info.cd[i].TargetDistLong << "           ";  //将变量的值写入文件
		fout << info.cd[i].TargetDistLat << "           ";  //将变量的值写入文件
		fout << info.cd[i].TargetVrel << "             ";  //将变量的值写入文件
		fout << info.cd[i].TargetRCS << "          ";  //将变量的值写入文件
		fout << info.cd[i].Time << "         ";  //将变量的值写入文件
		fout << info.cd[i].ESC_VehicleSpeed << "        ";  //将变量的值写入文件
		fout << endl << endl;
	}

	fout.close();     //关闭文件
	return;
}
void Save_Pack_Data(PACK_DATA *pd,int PackID)//保存包结构体到文件中
{
	if (pd == NULL)
	{
		cout << "error:pd结构体为空!" << endl;
		return;
	}
	//写入文件
	ofstream fout;     //创建一个data.txt的文件，用于存储数据
	fout.open("E:\\socketLearning\\RadarDataDemo\\data.txt", ios::app);//打开文件，输出的数据追加到文件末尾
		for (int j = 0; j < LoadSize; j++)
		{
			fout << pd->pack_data[PackID-1][j] << " ";  //将变量的值写入文件
		}
	fout << endl;

	fout.close();                  //关闭文件
	return;
}
void Pack_Fill(int RadarID, int PackID, PACK_DATA pd[], TEST_DATA *td)
{
	if (td == NULL)
	{
		cout << "error:td结构体为空!" << endl;
		return;
	}
	if (pd == NULL)
	{
		cout << "error:pd结构体为空!" << endl;
		return;
	}
	memcpy(&pd[RadarID].pack_data[PackID-1], td, sizeof(TEST_DATA));
	return;
}
int bit_convert(int bitlong, char strin[])//把二进制值转换为十进制
{
	char str[14] = "\0";
	for (int i = 0; i < bitlong; i++)
	{
		str[i] = strin[i];
	}
	int bin = 0;
	int bit = 0;
	for (int j = 0; j < bitlong; j++)
	{
		bit = str[bitlong - 1 - j] - '0';
		bin = bit * (int)pow(2, j) + bin;
	}
	return bin;
}
char* dec2bin(int val)//十进制转二进制保留高位0
{
	char str[9] = "\0";
	for (int i = 7; i >= 0; i--)
	{
		if (val & (1 << i))
			//cout << "1";
			str[7 - i] = '1';
		else
			//cout << "0";
			str[7 - i] = '0';
	}
	//cout << str << endl;
	return str;
}
void Convert_Data(PACK_DATA *pd, RETURNINFO* info, int RadarID)//用于转换数据,测试没问题
{
	static int frame_count[6] = { 0 };//初始化帧
	for (int j = 0; j < PackSize; j++)
	{
		for (int i = 0; i < PackNum; i++)
		{
			int index = j*PackNum + i;//数据在cd中的索引
			if (index < info->total_num)
			{
				cout << "索引:" << index << endl;

				char tp_str[50];
				char tp_str1[18];
				char tp_str2[9];
				itoa((int)pd->pack_data[j][2 + i * 10], tp_str, 16);
				info->cd[index].TargetRCS = *tp_str;//转换TargetRCS
				info->cd[index].RadarID = RadarID;
				info->cd[index].FrameCount = frame_count[RadarID];//帧信息
				info->cd[index].TargetID = (int)pd->pack_data[j][2 + i * 10 + 2];

				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 3]));//TargetDistLong的高位
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 4]));//TargetDistLong的低位
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetDistLong = (double)bit_convert(13, tp_str1)*0.2 - 500;
				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 4]));//TargetDistLat的高位
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 5]));//TargetDistLat的低位
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetDistLat = (double)bit_convert(10, tp_str1)*0.2 - 102.3;
				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 6]));//TargetTargetVrel的高位
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 7]));//TargetTargetVrel的低位
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetVrel = (double)bit_convert(10, tp_str1)*0.25 - 128;
				info->cd[index].TargetRCS = (double)pd->pack_data[j][2 + i * 10 + 9] * 0.5 - 64;
				info->cd[index].Time = (double)pd->pack_data[j][2 + i * 10 + 1] * 10 / 1000000.0;//时间转换成秒
				info->cd[index].ESC_VehicleSpeed = (double)pd->pack_data[j][288];//车速信息
				info->cd[index].TargetDPS = (double)pd->pack_data[j][289];//DPS信息
				//测试用-------------------------------------------
				//cout << info->cd[index].TargetRCS << "   " << info->cd[index].TargetVrel << "   " << info->cd[index].RadarID << "   " << info->cd[index].FrameCount << "   ";
				//cout << info->cd[index].TargetID << "   " << info->cd[index].TargetDistLong << "   " << info->cd[index].TargetDistLat << "   " << info->cd[index].TargetVrel << "   " << info->cd[index].TargetRCS << "   " << info->cd[index].Time << "   " << info->cd[index].ESC_VehicleSpeed << "   " << info->cd[index].TargetDPS << endl;
			}
			else
				break;
		}
	}
	frame_count[RadarID]++;//记录是雷达的第几帧数据
	cout << "已发送雷达" << RadarID << "号的第" << frame_count[RadarID] << "帧数据,包个数: " << info->total_num << endl;
	return ;
}
void UDP_receiver()//定义套接字
{
	WSADATA wsaData;
	SOCKET ReceivingSocket;
	SOCKADDR_IN ReceiverAddr;//接收端地址
	SOCKADDR_IN SenderAddr;//发送端地址
	int SenderAddrSize;
	int Port = PortNum;//端口地址
	int Ret;
	char buffer[BfSize] = {0};
	int countwhile = 0;
	SenderAddrSize = sizeof(SenderAddr);
	PACK_DATA pd[RadarNum];
	TEST_DATA td;
	RETURNINFO rinfo;
	int total_num = 0;
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("Error:WSAStartup failed with error %d\n", Ret);
		return;
	}
	else
	{
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			printf("Error:not winsock2.2\n");
			WSACleanup();
			return;
		}
	}
	if ((ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Error:socket failed eith error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	//创建完毕
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	ReceiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//如何客户端都可以向客户端发送数据
	if (bind(ReceivingSocket, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Error:bind failed eith error %d\n", WSAGetLastError());
		closesocket(ReceivingSocket);
		WSACleanup();
		return;
	}
	//绑定完毕
	while (1)//接收部分
	{
		cout << "waiting for message from others..." << endl;

		if ((Ret = recvfrom(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize)) == SOCKET_ERROR)
		{
			printf("Error:receive failed eith error %d\n", WSAGetLastError());
			closesocket(ReceivingSocket);
			WSACleanup();
			return;
		}
		//显示数据
		else
		{
			TEST_DATA td;
			RETURNINFO rinfo;
			int total_num = 0;
			memcpy(&td, buffer, sizeof(buffer));
			
			////printf("received datagram from %s -- %d\n", buffer);
			////Print_Test_Data(&td);//打印结构体
			////Save_Test_Data(&td);//将结构体保存到文件中
			////int length_Struct = Print_Test_Data_Length(&td);//打印结构体长度
			////cout << "length：" << length_Struct << endl;
			int RadarID = (int)td.test_buffer[0];//获取雷达ID
			int PackID = (int)td.test_buffer[1];//获取包ID

			Pack_Fill(RadarID, PackID, pd, &td);//把接收到的数据传入包中
			if (PackID == 9)
			{
				total_num = (int)td.test_buffer[301];
				rinfo.total_num = total_num;
				Convert_Data(&pd[RadarID], &rinfo, RadarID);//如果到了第9包，就解析该帧
				Save_Convert_Pack(rinfo);//保存每个雷达的一帧数据到文件中
				//cout << rinfo.total_num;//获取包ID << endl;
			}
			//Save_Pack_Data(&pd[RadarID],PackID);//保存传入的数据
		}
		//Sleep(100);
	}

	closesocket(ReceivingSocket);
	WSACleanup();
	return;
}

int main()
{

	UDP_receiver();
	//////////////////////////////////////////////////////////////测试用
	//PACK_DATA pd[RadarNum];
	//for (int i = 0; i < 9; i++)
	//{
	//	for (int j = 0; j < 302; j++)
	//	{
	//		pd[0].pack_data[i][j] = test_data[i * 302 + j];
	//	}
	//}

	//int RadarID = 0;
	//int PackID = 9;
	//RETURNINFO info;
	//info.total_num = pd[0].pack_data[8][301];
	//cout << info.total_num << endl;
	//Convert_Data(&pd[0],&info, RadarID);//如果到了第9包，就发送该帧
	////Save_Convert_Pack(info);//保存每个雷达的一帧数据
	////cout << (int)pd[0].pack_data[0][5] <<endl;
	////cout<< (double)((double)pd[RadarID].pack_data[0][289])<<endl;
	////cout<<(int)pd[RadarID].pack_data[0][2 + 0 * 10 + 2];

	//cout << info.total_num << endl;
	/////////////////////////////////////////////////////////////////
	system("pause");
	return 0;
}