/**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:UDP接收
 */
#pragma comment(lib,"ws2_32.lib")
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h> 
void main(int argc, char ** argv)
{
	WSADATA wsaData;
	SOCKET SendingSocket;
	SOCKADDR_IN ReceiverAddr;
	int ReceiverAddrsize = sizeof(ReceiverAddr);
	int Port = 5150;
	/*if (argc <= 1)
	{
		printf("USAGE:UDPSender< receiver IP address>\n");
		system("pause");
		return;
	}*/
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//接收端地址
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(Port);
	ReceiverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	while (1)
	{
		char buffer[1024] = "\0";
		printf("input message: \n");
		scanf("%s", buffer);
		if (strcmp(buffer, "bye") == 0)
			break;
		if (sendto(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr, sizeof(ReceiverAddr)) != SOCKET_ERROR)
		{
			if (recvfrom(SendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&ReceiverAddr,&ReceiverAddrsize) != SOCKET_ERROR)
			{
				printf("received from server: %s\n",buffer);
			}

		}
	}
	closesocket(SendingSocket);
	WSACleanup();

	system("pause");
}