/**
*date:20180808
*filename:mian
*version:1.0
*author:molly
*description:TCP的demo，输入数据传入Server并显示
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")//Windows套接字的动态链接库
#include <WinSock2.h>
#include<cstdio>
#include<cstdlib>

int main(int argc, char ** argv)
{
	WSADATA wsaData;
	SOCKET SendingSocket;
	SOCKADDR_IN ServerAddr;//服务器端的套接字地址
	int ServerAddrSize = sizeof(ServerAddr);
	int Ret;
	int Port = 7110;
	char DataBuffer[1024];//存储传输数据
						  /*if (argc <= 1)
						  {
						  printf("USAGE: TCPClient <Server IP address>.\n");
						  system("pause");
						  return 0;
						  }*/
						  //加载和初始化
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)//加载失败
	{
		printf("WSAStartup failed with eror %d\n", Ret);
		return 0;
	}
	//创建新的套接字
	if ((SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	//客户端连接服务器端
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);//本机字节转换为网络字节
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);//本机IP地址
	printf("we are trying to connect to %s: %d...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
	//连接
	if (connect(SendingSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		printf("connect failed with error %d\n", WSAGetLastError());
		closesocket(SendingSocket);
		WSACleanup();
		return 0;
	}
	//连接成功
	printf("our connection succeeded.\n");
	while (1)
	{
		printf("input something: \n");
		scanf("%s", DataBuffer);
		if (strcmp(DataBuffer, "bye") == 0)
		{
			break;
		}

		if (sendto(SendingSocket, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ServerAddr, ServerAddrSize) != SOCKET_ERROR)//发送数据
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