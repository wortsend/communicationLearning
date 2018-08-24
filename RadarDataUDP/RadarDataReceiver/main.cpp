/**
 *date:20180816
 *filename:RadarDataReceiver
 *version:1.0
 *author:molly
 *description:�����״﷢�͵�����
 */
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>
#include<iostream>
#include <fstream>//д���ļ�
#define LoadSize 302//ÿһ���Ĵ�С
#define PortNum  5150      //�˿ں�
#define BfSize 1208 //��������С
#define PackSize 9   //������
#define RadarNum 6// �״����
#define PackNum 30   //ÿ�������ݵĸ���
using namespace std;


//���ڲ���
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
struct RETURNINFO//����ת�����һ֡����
{
	CONVERT_DATA cd[PackNum*PackSize];
	int total_num;
};

void Print_Test_Data(TEST_DATA *td)//��ӡ�ṹ��
{
	if (td == NULL)
	{
		cout << "error:�ṹ��Ϊ��!" << endl;
		return;
	}
	for (int i = 0; i < LoadSize; i++)
	{
		cout << td->test_buffer[i] << endl;
	}
	return;
}
int Print_Test_Data_Length(TEST_DATA *td)//��ӡ�ṹ�峤��
{
	if (td == NULL)
	{
		cout << "error:�ṹ��Ϊ��!" << endl;
		return 0;
	}

	return sizeof(td);
}
void Save_Test_Data(TEST_DATA*td)//����td�ṹ�嵽�ļ���
{
	if (td == NULL)
	{
		cout << "error:�ṹ��Ϊ��!" << endl;
		return;
	}
	//д���ļ�
	ofstream fout;     //����һ��data.txt���ļ������ڴ洢����
	fout.open("E:\\socketLearning\\RadarDataDemo\\data.txt", ios::app);//���ļ������������׷�ӵ��ļ�ĩβ
	for (int i = 0; i < LoadSize; i++)
	{
		fout << td->test_buffer[i] << " ";  //��������ֵд���ļ�
	}
	fout << endl << endl;
	fout.close();                  //�ر��ļ�
	return;
}
void Save_Convert_Pack(RETURNINFO &info)//����ÿ���״��һ֡���ݣ�����û����
{
	if (&info == NULL)
	{
		cout << "error:�ṹ��Ϊ��!" << endl;
		return;
	}
	//д���ļ�
	ofstream fout;     //����һ��convert_data.txt���ļ������ڴ洢����
	fout.open("E:\\socketLearning\\RadarDataDemo\\convert_data.txt", ios::app);//���ļ������������׷�ӵ��ļ�ĩβ
	fout << "TargetDPS  RadarID	 FrameCount  TargetID  TargetDistLong   TargetDistLat      TargetVrel  TargetRCS  Time  ESC_VehicleSpeed" << endl;
	for (int i = 0; i < info.total_num; i++)
	{
		fout << info.cd[i].TargetDPS << "              ";  //��������ֵд���ļ�
		fout << info.cd[i].RadarID << "            ";  //��������ֵд���ļ�
		fout << info.cd[i].FrameCount << "          ";  //��������ֵд���ļ�
		fout << info.cd[i].TargetID << "              ";  //��������ֵд���ļ�
		fout << info.cd[i].TargetDistLong << "           ";  //��������ֵд���ļ�
		fout << info.cd[i].TargetDistLat << "           ";  //��������ֵд���ļ�
		fout << info.cd[i].TargetVrel << "             ";  //��������ֵд���ļ�
		fout << info.cd[i].TargetRCS << "          ";  //��������ֵд���ļ�
		fout << info.cd[i].Time << "         ";  //��������ֵд���ļ�
		fout << info.cd[i].ESC_VehicleSpeed << "        ";  //��������ֵд���ļ�
		fout << endl << endl;
	}

	fout.close();     //�ر��ļ�
	return;
}
void Save_Pack_Data(PACK_DATA *pd,int PackID)//������ṹ�嵽�ļ���
{
	if (pd == NULL)
	{
		cout << "error:pd�ṹ��Ϊ��!" << endl;
		return;
	}
	//д���ļ�
	ofstream fout;     //����һ��data.txt���ļ������ڴ洢����
	fout.open("E:\\socketLearning\\RadarDataDemo\\data.txt", ios::app);//���ļ������������׷�ӵ��ļ�ĩβ
		for (int j = 0; j < LoadSize; j++)
		{
			fout << pd->pack_data[PackID-1][j] << " ";  //��������ֵд���ļ�
		}
	fout << endl;

	fout.close();                  //�ر��ļ�
	return;
}
void Pack_Fill(int RadarID, int PackID, PACK_DATA pd[], TEST_DATA *td)
{
	if (td == NULL)
	{
		cout << "error:td�ṹ��Ϊ��!" << endl;
		return;
	}
	if (pd == NULL)
	{
		cout << "error:pd�ṹ��Ϊ��!" << endl;
		return;
	}
	memcpy(&pd[RadarID].pack_data[PackID-1], td, sizeof(TEST_DATA));
	return;
}
int bit_convert(int bitlong, char strin[])//�Ѷ�����ֵת��Ϊʮ����
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
char* dec2bin(int val)//ʮ����ת�����Ʊ�����λ0
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
void Convert_Data(PACK_DATA *pd, RETURNINFO* info, int RadarID)//����ת������,����û����
{
	static int frame_count[6] = { 0 };//��ʼ��֡
	for (int j = 0; j < PackSize; j++)
	{
		for (int i = 0; i < PackNum; i++)
		{
			int index = j*PackNum + i;//������cd�е�����
			if (index < info->total_num)
			{
				cout << "����:" << index << endl;

				char tp_str[50];
				char tp_str1[18];
				char tp_str2[9];
				itoa((int)pd->pack_data[j][2 + i * 10], tp_str, 16);
				info->cd[index].TargetRCS = *tp_str;//ת��TargetRCS
				info->cd[index].RadarID = RadarID;
				info->cd[index].FrameCount = frame_count[RadarID];//֡��Ϣ
				info->cd[index].TargetID = (int)pd->pack_data[j][2 + i * 10 + 2];

				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 3]));//TargetDistLong�ĸ�λ
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 4]));//TargetDistLong�ĵ�λ
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetDistLong = (double)bit_convert(13, tp_str1)*0.2 - 500;
				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 4]));//TargetDistLat�ĸ�λ
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 5]));//TargetDistLat�ĵ�λ
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetDistLat = (double)bit_convert(10, tp_str1)*0.2 - 102.3;
				strcpy(tp_str1, dec2bin((int)pd->pack_data[j][2 + i * 10 + 6]));//TargetTargetVrel�ĸ�λ
				strcpy(tp_str2, dec2bin((int)pd->pack_data[j][2 + i * 10 + 7]));//TargetTargetVrel�ĵ�λ
				strcat(tp_str1, tp_str2);
				info->cd[index].TargetVrel = (double)bit_convert(10, tp_str1)*0.25 - 128;
				info->cd[index].TargetRCS = (double)pd->pack_data[j][2 + i * 10 + 9] * 0.5 - 64;
				info->cd[index].Time = (double)pd->pack_data[j][2 + i * 10 + 1] * 10 / 1000000.0;//ʱ��ת������
				info->cd[index].ESC_VehicleSpeed = (double)pd->pack_data[j][288];//������Ϣ
				info->cd[index].TargetDPS = (double)pd->pack_data[j][289];//DPS��Ϣ
				//������-------------------------------------------
				//cout << info->cd[index].TargetRCS << "   " << info->cd[index].TargetVrel << "   " << info->cd[index].RadarID << "   " << info->cd[index].FrameCount << "   ";
				//cout << info->cd[index].TargetID << "   " << info->cd[index].TargetDistLong << "   " << info->cd[index].TargetDistLat << "   " << info->cd[index].TargetVrel << "   " << info->cd[index].TargetRCS << "   " << info->cd[index].Time << "   " << info->cd[index].ESC_VehicleSpeed << "   " << info->cd[index].TargetDPS << endl;
			}
			else
				break;
		}
	}
	frame_count[RadarID]++;//��¼���״�ĵڼ�֡����
	cout << "�ѷ����״�" << RadarID << "�ŵĵ�" << frame_count[RadarID] << "֡����,������: " << info->total_num << endl;
	return ;
}
void UDP_receiver()//�����׽���
{
	WSADATA wsaData;
	SOCKET ReceivingSocket;
	SOCKADDR_IN ReceiverAddr;//���ն˵�ַ
	SOCKADDR_IN SenderAddr;//���Ͷ˵�ַ
	int SenderAddrSize;
	int Port = PortNum;//�˿ڵ�ַ
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
	//�������
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	ReceiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//��οͻ��˶�������ͻ��˷�������
	if (bind(ReceivingSocket, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Error:bind failed eith error %d\n", WSAGetLastError());
		closesocket(ReceivingSocket);
		WSACleanup();
		return;
	}
	//�����
	while (1)//���ղ���
	{
		cout << "waiting for message from others..." << endl;

		if ((Ret = recvfrom(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize)) == SOCKET_ERROR)
		{
			printf("Error:receive failed eith error %d\n", WSAGetLastError());
			closesocket(ReceivingSocket);
			WSACleanup();
			return;
		}
		//��ʾ����
		else
		{
			TEST_DATA td;
			RETURNINFO rinfo;
			int total_num = 0;
			memcpy(&td, buffer, sizeof(buffer));
			
			////printf("received datagram from %s -- %d\n", buffer);
			////Print_Test_Data(&td);//��ӡ�ṹ��
			////Save_Test_Data(&td);//���ṹ�屣�浽�ļ���
			////int length_Struct = Print_Test_Data_Length(&td);//��ӡ�ṹ�峤��
			////cout << "length��" << length_Struct << endl;
			int RadarID = (int)td.test_buffer[0];//��ȡ�״�ID
			int PackID = (int)td.test_buffer[1];//��ȡ��ID

			Pack_Fill(RadarID, PackID, pd, &td);//�ѽ��յ������ݴ������
			if (PackID == 9)
			{
				total_num = (int)td.test_buffer[301];
				rinfo.total_num = total_num;
				Convert_Data(&pd[RadarID], &rinfo, RadarID);//������˵�9�����ͽ�����֡
				Save_Convert_Pack(rinfo);//����ÿ���״��һ֡���ݵ��ļ���
				//cout << rinfo.total_num;//��ȡ��ID << endl;
			}
			//Save_Pack_Data(&pd[RadarID],PackID);//���洫�������
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
	//////////////////////////////////////////////////////////////������
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
	//Convert_Data(&pd[0],&info, RadarID);//������˵�9�����ͷ��͸�֡
	////Save_Convert_Pack(info);//����ÿ���״��һ֡����
	////cout << (int)pd[0].pack_data[0][5] <<endl;
	////cout<< (double)((double)pd[RadarID].pack_data[0][289])<<endl;
	////cout<<(int)pd[RadarID].pack_data[0][2 + 0 * 10 + 2];

	//cout << info.total_num << endl;
	/////////////////////////////////////////////////////////////////
	system("pause");
	return 0;
}