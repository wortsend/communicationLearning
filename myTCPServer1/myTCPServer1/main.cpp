/**
 *date:20180808
 *filename:main
 *version:1.0
 *author:molly
 *description:TCP的demo，接收client传来的数据并显示
 */
#pragma comment(lib,"ws2_32.lib")//导入动态链接库
#include<iostream>
#include<cstdlib>
#include<WinSock2.h>
int main(void)
{
	WSADATA wsaData;//初始化Windows套接字
	SOCKET ListeningSocket;//服务端用来监听的套接字
	SOCKET NewConnection;//对应新连接的套接字
	SOCKADDR_IN ServerAddr;//服务端地址
	SOCKADDR_IN ClientAddr;//客户端地址
	using namespace std;
	int ClientAddrSize;//客户端地址的长度
	int Port = 7110;//指定一个端口
	int Ret;
	char DataBuffer[1024];//用于接受数据

	//检查创建是否成功
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		cout << "WSAStartup failed with error " << Ret << endl;
		return 0;
	}
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)//创建套接字失败
	{
		cout << "socket failed with error " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//任何一台客户端机器都可以连接
	//绑定
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//把套接字绑定到地址上
	{
		cout << "bind failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//监听
	if (listen(ListeningSocket, 5) == SOCKET_ERROR)
	{
		cout << "listen failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//等待客户端连接
	cout << "we are waiting a connection on port " << Port << endl;
	cout << "listen(正在监听)..." << endl;
	//有客户端连接
	ClientAddrSize = sizeof(SOCKADDR);//客户端地址长度
	if ((NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize)) == INVALID_SOCKET)
	{
		cout << "accept failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//建立了连接
	cout << "we successfully got a connection from " << inet_ntoa(ClientAddr.sin_addr) << ": " << ntohs(ClientAddr.sin_port) << endl;
	closesocket(ListeningSocket);//关闭监听套接字
	cout << "we are waiting to receive data" << endl;
	
	//交互传输
	while (1)
	{
		if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)//接收数据是否成功
		{
			cout << "receive failed with error " << WSAGetLastError() << endl;
			closesocket(NewConnection);
			WSACleanup();
			return 0;
		}
		cout << "we received data as below" << endl;
		cout << DataBuffer << endl;
		cout << "now in receiving state,press 1 to sending state,0 to back..." << endl;
		cin >> DataBuffer;//输入状态指令
		if (strcmp(DataBuffer,"1") == 0)
		{
			cout << "now in sending state...input something" << endl;
			cin >> DataBuffer;
			if (sendto(NewConnection, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ClientAddr, ClientAddrSize) != SOCKET_ERROR)//发送数据
			{
				cout << "we sent a message to client,message is:" << DataBuffer << endl;
			}
		}
		else if (strcmp(DataBuffer, "0") == 0)
		{
			sendto(NewConnection, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ClientAddr, ClientAddrSize);
		}
		Sleep(500);
		/*cout << "input a message: " << endl;
		cin >> DataBuffer;
		if (sendto(NewConnection, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ClientAddr, ClientAddrSize)!= SOCKET_ERROR)
		{
			cout << "send to Client successfully " << endl;
		}*/
	}
	closesocket(NewConnection);
	WSACleanup();
	system("pause");
	return 0;
}
