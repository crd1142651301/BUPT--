#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <iostream>
#include "trade.h"
using namespace std;
//����ws2_32.lib��
#pragma comment(lib,"ws2_32.lib")

#define  BUF_SIZE 1024		//��������С
#define THREAD_SIZE 20		//����ܹ��������̸߳���
const int PORT = 8000;		//�˿ں�
//�����̺߳���
unsigned WINAPI ClntHandler(void* param);
//��ſͻ���socket������
SOCKET clntSocks[THREAD_SIZE];
//��
HANDLE mtx;
//�ܵĿͻ������ӵĸ���
int clntCnt = 0;
//����ƽ̨
Trade myTrade;

int main(void) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int clntAddrSz;

	//�洢�������߳̾��
	HANDLE hClntThreadHandles[THREAD_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
		cout << "��ʼ������" << endl;
		return 0;
	}
	
	servSock = socket(AF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET) {
		cout << "socket build failed" << endl;
		WSACleanup();
		return 0;
	}
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	if (bind(servSock, (const sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		cout << "bind failed" << endl;
		closesocket(servSock);
		WSACleanup();
		return 0;
	}
	cout << "bind succeed" << endl;

	listen(servSock, 5);
	//�������⣬��ʼ״̬Ϊsignaled���������κ��߳�
	mtx = CreateMutex(NULL, FALSE, NULL);
	while (clntCnt < THREAD_SIZE)
	{
		clntAddrSz = sizeof(clntAddr);
		clntSock = accept(servSock, (sockaddr*)&clntAddr, &clntAddrSz);
		printf("build a conncetion.\n");

		WaitForSingleObject(mtx, INFINITE);
		clntSocks[clntCnt] = clntSock;
		ReleaseMutex(mtx);
		//�����߳�
		hClntThreadHandles[clntCnt++] = (HANDLE)_beginthreadex(NULL, 0, ClntHandler, &clntSock, 0, NULL);
	}
	//�ȴ��߳̽���
	WaitForMultipleObjects(THREAD_SIZE, hClntThreadHandles, true, INFINITE);
	//�رջ�����
	CloseHandle(mtx);
	return 0;
}


//����ͻ���socket��д���̺߳���
unsigned WINAPI ClntHandler(void* param) {

	int i, strLen;
	char recvbuf[BUF_SIZE];
	char sendbuf[BUF_SIZE];
	SOCKET clntSock = *((SOCKET*)param);
	User* user = nullptr;

	while (true) {

		/* ���յ�һ���� */
		memset(recvbuf, 0x00, sizeof(char) * BUF_SIZE);
		strLen = recv(clntSock, recvbuf, BUF_SIZE, 0);
		if (strLen <= 0) {
			break;
		}
		recvbuf[strLen - 1] = '\0';

		//cout << recvbuf << endl;
		memset(sendbuf, 0x00, sizeof(char) * BUF_SIZE);
		//cin.getline(sendbuf, 10);

		/* �����û���Ϣ */
		if (user != nullptr) {
			bool success = myTrade.updateMyData(user);
			if (!success) {
				break;
			}
		}

		/* �����յ��İ� */
		myTrade.handleBuf(recvbuf, sendbuf, user);

		/* ��ͻ��˷�����Ӧ�� */
		int x = send(clntSock, sendbuf, BUF_SIZE, 0);
		if (x <= 0) {
			cout << "����ʧ��" << endl;
		}
	}
	WaitForSingleObject(mtx, INFINITE);
	for (i = 0; i < clntCnt; i++)
	{
		if (clntSocks[i] == clntSock)
		{
			while (i++ < clntCnt - 1)
				clntSocks[i] = clntSocks[i + 1];
			break;
		}

	}

	if (user != nullptr) {
		delete user;
		user = nullptr;
	}
	clntCnt--;
	ReleaseMutex(mtx);
	closesocket(clntSock);
	return 0;
}
