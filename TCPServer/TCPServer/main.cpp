/**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:练习使用socket
 */
#pragma comment(lib,"ws2_32.lib")//动态链接库
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>//头文件
void main(void)
{
	WSADATA wsaData;//用来初始化windows套接字
	SOCKET ListeningSocket;//服务端用来监听的套接字
	SOCKET NewConnection;//对应的新连接的套接字
	SOCKADDR_IN ServerAddr;//服务端地址
	SOCKADDR_IN ClientAddr;//客户端地址
	int ClientAddrLen;//客户端地址的长度
	int Port = 5150;//指定一个端口
	int Ret;
	char DataBuffer[1024];//用于接收数据
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed eith error %d\n", Ret);
		return;
	}//检测是否成功

	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)//如果无效,创建套接字失败
	{
		printf("socket failed with error %d\n", WSAGetLastError());  
		WSACleanup();
		return;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);//本机字节转换为网络字节 
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//任何一台客户端的机器都可以连接
	//绑定
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//把套接字绑定到地址上
	{
		printf("bind failed with error%d\n",WSAGetLastError());
		closesocket(ListeningSocket);//绑定失败退出
		WSACleanup();
		return;
	}
	//监听
	if (listen(ListeningSocket, 5) == SOCKET_ERROR)//有5个客户端可以排队,连接
	{
		printf("listen failed with error%d\n", WSAGetLastError());
		closesocket(ListeningSocket);//监听失败退出
		WSACleanup();
		return;
	}
	//等待客户端连接服务端
	printf("we are waiting a connection on port %d.\n", Port);
	printf("listen(正在监听)...");
	//有客户端连接
	ClientAddrLen = sizeof(SOCKADDR);//计算地址的长度
	if ((NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)//接受客户端的连接请求
	{
		printf("accept failed with error%d\n", WSAGetLastError());
		closesocket(ListeningSocket);//接收失败退出
		WSACleanup();
		return;
	}
	//以上已经建立了客户端与服务端的连接
	printf("we successfully got a connection from %s: %d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
	closesocket(ListeningSocket);//关闭套接字
	printf("we are waiting to receive data\n");
	if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)//接收客户端发送的数据的字节
	{
		printf("recev failed with error%d\n", WSAGetLastError());
		closesocket(NewConnection);//接收失败退出
		WSACleanup();
		return;
	}
	//显示接受的数据
	printf("we successfully received %d bytes.\n", Ret);
	DataBuffer[Ret] = '\0';//字符串末尾
	printf("%s\n", DataBuffer);
	printf("we are now going to close the client connection.\n");
	closesocket(NewConnection);//关闭客户端套接字
	WSACleanup();
	system("pause");
}
