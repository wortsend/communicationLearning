/**
 *date:20180807
 *filename:main
 *version:1.0
 *author:molly
 *description:��ϰʹ��socket
 */
#pragma comment(lib,"ws2_32.lib")//��̬���ӿ�
#include<cstdio>
#include<cstdlib>
#include<WinSock2.h>//ͷ�ļ�
void main(void)
{
	WSADATA wsaData;//������ʼ��windows�׽���
	SOCKET ListeningSocket;//����������������׽���
	SOCKET NewConnection;//��Ӧ�������ӵ��׽���
	SOCKADDR_IN ServerAddr;//����˵�ַ
	SOCKADDR_IN ClientAddr;//�ͻ��˵�ַ
	int ClientAddrLen;//�ͻ��˵�ַ�ĳ���
	int Port = 5150;//ָ��һ���˿�
	int Ret;
	char DataBuffer[1024];//���ڽ�������
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed eith error %d\n", Ret);
		return;
	}//����Ƿ�ɹ�

	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)//�����Ч,�����׽���ʧ��
	{
		printf("socket failed with error %d\n", WSAGetLastError());  
		WSACleanup();
		return;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);//�����ֽ�ת��Ϊ�����ֽ� 
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�κ�һ̨�ͻ��˵Ļ�������������
	//��
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//���׽��ְ󶨵���ַ��
	{
		printf("bind failed with error%d\n",WSAGetLastError());
		closesocket(ListeningSocket);//��ʧ���˳�
		WSACleanup();
		return;
	}
	//����
	if (listen(ListeningSocket, 5) == SOCKET_ERROR)//��5���ͻ��˿����Ŷ�,����
	{
		printf("listen failed with error%d\n", WSAGetLastError());
		closesocket(ListeningSocket);//����ʧ���˳�
		WSACleanup();
		return;
	}
	//�ȴ��ͻ������ӷ����
	printf("we are waiting a connection on port %d.\n", Port);
	printf("listen(���ڼ���)...");
	//�пͻ�������
	ClientAddrLen = sizeof(SOCKADDR);//�����ַ�ĳ���
	if ((NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET)//���ܿͻ��˵���������
	{
		printf("accept failed with error%d\n", WSAGetLastError());
		closesocket(ListeningSocket);//����ʧ���˳�
		WSACleanup();
		return;
	}
	//�����Ѿ������˿ͻ��������˵�����
	printf("we successfully got a connection from %s: %d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
	closesocket(ListeningSocket);//�ر��׽���
	printf("we are waiting to receive data\n");
	if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR)//���տͻ��˷��͵����ݵ��ֽ�
	{
		printf("recev failed with error%d\n", WSAGetLastError());
		closesocket(NewConnection);//����ʧ���˳�
		WSACleanup();
		return;
	}
	//��ʾ���ܵ�����
	printf("we successfully received %d bytes.\n", Ret);
	DataBuffer[Ret] = '\0';//�ַ���ĩβ
	printf("%s\n", DataBuffer);
	printf("we are now going to close the client connection.\n");
	closesocket(NewConnection);//�رտͻ����׽���
	WSACleanup();
	system("pause");
}
