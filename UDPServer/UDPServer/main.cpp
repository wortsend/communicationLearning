/**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:��ϰʹ��UDP����
 */
#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>

void main()
{
	WSADATA wsaData;
	SOCKET ReceivingSocket;
	SOCKADDR_IN ReceiverAddr;//���ն˵�ַ
	SOCKADDR_IN SenderAddr;//���Ͷ˵�ַ
	int SenderAddrSize;
	int Port = 5150;//�˿ڵ�ַ
	int Ret;
	SenderAddrSize = sizeof(SenderAddr);
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("Error:WSAStartup failed eith error %d\n", Ret);
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

	while (1)
	{
		char buffer[1024] = "\0";
		printf("waiting for message from others...\n");
		if((Ret = recvfrom(ReceivingSocket,buffer,sizeof(buffer),0,(SOCKADDR*)&SenderAddr,&SenderAddrSize))==SOCKET_ERROR)
		{
			printf("Error:receive failed eith error %d\n", WSAGetLastError());
			closesocket(ReceivingSocket);
			WSACleanup();
			return;
         }
		//���յ������ݷ��ͻ�ȥ
		else
		{
			printf("received datagram from %s -- %s\n", inet_ntoa(SenderAddr.sin_addr), buffer);
			sendto(ReceivingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&SenderAddr, SenderAddrSize);

		}
		Sleep(500);
	}
	closesocket(ReceivingSocket);
	WSACleanup();
	printf("hello\n");
	system("pause");
}