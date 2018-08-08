/**
 *date:20180808
 *filename:main
 *version:1.0
 *author:molly
 *description:TCP��demo������client���������ݲ���ʾ
 */
#pragma comment(lib,"ws2_32.lib")//���붯̬���ӿ�
#include<iostream>
#include<cstdlib>
#include<WinSock2.h>
int main(void)
{
	WSADATA wsaData;//��ʼ��Windows�׽���
	SOCKET ListeningSocket;//����������������׽���
	SOCKET NewConnection;//��Ӧ�����ӵ��׽���
	SOCKADDR_IN ServerAddr;//����˵�ַ
	SOCKADDR_IN ClientAddr;//�ͻ��˵�ַ
	using namespace std;
	int ClientAddrSize;//�ͻ��˵�ַ�ĳ���
	int Port = 7110;//ָ��һ���˿�
	int Ret;
	char DataBuffer[1024];//���ڽ�������

	//��鴴���Ƿ�ɹ�
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		cout << "WSAStartup failed with error " << Ret << endl;
		return 0;
	}
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)//�����׽���ʧ��
	{
		cout << "socket failed with error " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�κ�һ̨�ͻ��˻�������������
	//��
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//���׽��ְ󶨵���ַ��
	{
		cout << "bind failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//����
	if (listen(ListeningSocket, 5) == SOCKET_ERROR)
	{
		cout << "listen failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//�ȴ��ͻ�������
	cout << "we are waiting a connection on port " << Port << endl;
	cout << "listen(���ڼ���)..." << endl;
	//�пͻ�������
	ClientAddrSize = sizeof(SOCKADDR);//�ͻ��˵�ַ����
	if ((NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize)) == INVALID_SOCKET)
	{
		cout << "accept failed with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 0;
	}
	//����������
	cout << "we successfully got a connection from " << inet_ntoa(ClientAddr.sin_addr) << ": " << ntohs(ClientAddr.sin_port) << endl;
	closesocket(ListeningSocket);//�رռ����׽���
	cout << "we are waiting to receive data" << endl;
	
	//��������
	while (1)
	{
		if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)//���������Ƿ�ɹ�
		{
			cout << "receive failed with error " << WSAGetLastError() << endl;
			closesocket(NewConnection);
			WSACleanup();
			return 0;
		}
		cout << "we received data as below" << endl;
		cout << DataBuffer << endl;
		cout << "now in receiving state,press 1 to sending state,0 to back..." << endl;
		cin >> DataBuffer;//����״ָ̬��
		if (strcmp(DataBuffer,"1") == 0)
		{
			cout << "now in sending state...input something" << endl;
			cin >> DataBuffer;
			if (sendto(NewConnection, DataBuffer, sizeof(DataBuffer), 0, (SOCKADDR*)&ClientAddr, ClientAddrSize) != SOCKET_ERROR)//��������
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
