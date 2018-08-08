/**
*date:20180808
*filename:mian
*version:1.0
*author:molly
*description:TCP��demo���������ݴ���Server����ʾ
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")//Windows�׽��ֵĶ�̬���ӿ�
#include <WinSock2.h>
#include<cstdio>
#include<cstdlib>

int main(int argc, char ** argv)
{
	WSADATA wsaData;
	SOCKET SendingSocket;
	SOCKADDR_IN ServerAddr;//�������˵��׽��ֵ�ַ
	int ServerAddrSize = sizeof(ServerAddr);
	int Ret;
	int Port = 7110;
	char DataBuffer[1024];//�洢��������
						  /*if (argc <= 1)
						  {
						  printf("USAGE: TCPClient <Server IP address>.\n");
						  system("pause");
						  return 0;
						  }*/
						  //���غͳ�ʼ��
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)//����ʧ��
	{
		printf("WSAStartup failed with eror %d\n", Ret);
		return 0;
	}
	//�����µ��׽���
	if ((SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	//�ͻ������ӷ�������
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);//�����ֽ�ת��Ϊ�����ֽ�
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);//����IP��ַ
	printf("we are trying to connect to %s: %d...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
	//����
	if (connect(SendingSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		printf("connect failed with error %d\n", WSAGetLastError());
		closesocket(SendingSocket);
		WSACleanup();
		return 0;
	}
	//���ӳɹ�
	printf("our connection succeeded.\n");
	while (1)
	{
		printf("input something: \n");
		scanf("%s", DataBuffer);
		if (strcmp(DataBuffer, "bye") == 0)
		{
			break;
		}

		if (sendto(SendingSocket, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ServerAddr, ServerAddrSize) != SOCKET_ERROR)//��������
		{
			printf("we sent a message to server,message is:%s\n", DataBuffer);
		}
		if (recv(SendingSocket, DataBuffer, sizeof(DataBuffer), 0) != SOCKET_ERROR)
		{
			if (strcmp(DataBuffer, "0") == 0)
			{
				continue;
			}
			else
			printf("we received a message from server:%s\n", DataBuffer);
		}
		
		/*if (recvfrom(SendingSocket, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ServerAddr, &ServerAddrSize) != SOCKET_ERROR)
		{
			printf("received from server: %s\n", DataBuffer);
		}*/

	}
	closesocket(SendingSocket);
	WSACleanup();
	system("pause");
	return 0;
}