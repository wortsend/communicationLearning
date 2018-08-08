/**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:练习使用UDP发送
 */
#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>

void main()
{
	WSADATA wsaData;
	SOCKET ReceivingSocket;
	SOCKADDR_IN ReceiverAddr;//接收端地址
	SOCKADDR_IN SenderAddr;//发送端地址
	int SenderAddrSize;
	int Port = 5150;//端口地址
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
		//把收到的数据发送回去
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