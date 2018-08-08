
 /**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:socket客户端
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")//Windows套接字的动态链接库
#include <WinSock2.h>
#include<cstdio>
#include<cstdlib>

int main(int argc, char ** argv)
{
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN ServerAddr;//服务器端的套接字地址
	int Ret;
	int Port = 5150;
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
	if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	//客户端连接服务器端
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port =  htons(Port);//本机字节转换为网络字节
	ServerAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);//本机IP地址
	printf("we are trying to connect to %s: %d...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
	//连接
	if (connect(s, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		printf("connect failed with error %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 0;
	}
	//连接成功
	printf("our connection succeeded.\n");
	printf("we will now try to send a hello message.\n");
	if ((Ret = send(s, "hello", 5, 0)) == SOCKET_ERROR)
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 0;
	}
	//发送成功
	printf("we successfully sent %d bytes.\n", Ret);
	printf("we are cloing connection.\n ");
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}