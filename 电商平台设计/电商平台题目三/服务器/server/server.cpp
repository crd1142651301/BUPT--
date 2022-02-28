#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <iostream>
#include "trade.h"
using namespace std;
//引入ws2_32.lib库
#pragma comment(lib,"ws2_32.lib")

#define  BUF_SIZE 1024		//缓冲区大小
#define THREAD_SIZE 20		//最多能够创建的线程个数
const int PORT = 8000;		//端口号
//创建线程函数
unsigned WINAPI ClntHandler(void* param);
//存放客户端socket的数组
SOCKET clntSocks[THREAD_SIZE];
//锁
HANDLE mtx;
//总的客户端连接的个数
int clntCnt = 0;
//定义平台
Trade myTrade;

int main(void) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int clntAddrSz;

	//存储创建的线程句柄
	HANDLE hClntThreadHandles[THREAD_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
		cout << "初始化错误" << endl;
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
	//创建互斥，初始状态为signaled，不属于任何线程
	mtx = CreateMutex(NULL, FALSE, NULL);
	while (clntCnt < THREAD_SIZE)
	{
		clntAddrSz = sizeof(clntAddr);
		clntSock = accept(servSock, (sockaddr*)&clntAddr, &clntAddrSz);
		printf("build a conncetion.\n");

		WaitForSingleObject(mtx, INFINITE);
		clntSocks[clntCnt] = clntSock;
		ReleaseMutex(mtx);
		//开启线程
		hClntThreadHandles[clntCnt++] = (HANDLE)_beginthreadex(NULL, 0, ClntHandler, &clntSock, 0, NULL);
	}
	//等待线程结束
	WaitForMultipleObjects(THREAD_SIZE, hClntThreadHandles, true, INFINITE);
	//关闭互斥句柄
	CloseHandle(mtx);
	return 0;
}


//处理客户端socket读写的线程函数
unsigned WINAPI ClntHandler(void* param) {

	int i, strLen;
	char recvbuf[BUF_SIZE];
	char sendbuf[BUF_SIZE];
	SOCKET clntSock = *((SOCKET*)param);
	User* user = nullptr;

	while (true) {

		/* 接收到一个包 */
		memset(recvbuf, 0x00, sizeof(char) * BUF_SIZE);
		strLen = recv(clntSock, recvbuf, BUF_SIZE, 0);
		if (strLen <= 0) {
			break;
		}
		recvbuf[strLen - 1] = '\0';

		//cout << recvbuf << endl;
		memset(sendbuf, 0x00, sizeof(char) * BUF_SIZE);
		//cin.getline(sendbuf, 10);

		/* 更新用户信息 */
		if (user != nullptr) {
			bool success = myTrade.updateMyData(user);
			if (!success) {
				break;
			}
		}

		/* 处理收到的包 */
		myTrade.handleBuf(recvbuf, sendbuf, user);

		/* 向客户端发送响应包 */
		int x = send(clntSock, sendbuf, BUF_SIZE, 0);
		if (x <= 0) {
			cout << "发送失败" << endl;
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
