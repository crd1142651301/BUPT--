#include "client.h"

Trade myTrade;

int main(void) {
	SOCKET sock;
	sockaddr_in addr;
	WSADATA wsaData;
	HANDLE hThreads[2];
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR) {
		cout << "��ʼ��ʧ��" << endl;
		return 0;
	}
	cout << "��ʼ���ɹ�" << endl;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << "socket failed." << endl;
		WSACleanup();
		return 0;
	}
	cout << "socket built success!" << endl;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);

	cout << "building connection..." << endl;
	if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		cout << "connect failed" << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	cout << "connection succeed." << endl;

	isSignIn = false;
	myTrade.printInitialInterface();
	//�����߳�����д�Ͷ�
	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, WriteHandler, &sock, 0, NULL);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, ReadHandler, &sock, 0, NULL);

	//�����¼�����Ϊmanual-resetģʽ������д���¼���������ź�״̬�������¼���������ź�״̬
	evts[0] = CreateEvent(NULL, true, true, NULL);
	evts[1] = CreateEvent(NULL, true, false, NULL);

	WaitForMultipleObjects(2, hThreads, true, INFINITE);

	CloseHandle(evts[0]);
	CloseHandle(evts[1]);
	return 0;
}


//����д�߳�
unsigned WINAPI WriteHandler(void* param) {

	char sendbuf[BUF_SIZE];
	SOCKET sock = *((SOCKET*)(param));

	while (true) {
		WaitForSingleObject(evts[0], INFINITE);
		/* ����ѡ�� */
		memset(sendbuf, 0x00, BUF_SIZE);
		//cin.getline(sendbuf, BUF_SIZE);
		
		bool can = myTrade.getSendBuf(sendbuf);

		if (!can) {
			strLen = -1;
			SetEvent(evts[1]);
			break;
		}

		/* ������������������� */
		int x = send(sock, sendbuf, BUF_SIZE, 0);

		if (x <= 0) {
			printf("err = %d\n", WSAGetLastError());
			cout << "����ʧ��" << endl;
			break;
		}

		ResetEvent(evts[0]);
		SetEvent(evts[1]);
	}
	return 0;
}

//���ڶ��߳�
unsigned WINAPI ReadHandler(void* param) {

	char buf[BUF_SIZE];
	SOCKET sock = *((SOCKET*)(param));

	while (true) {
		WaitForSingleObject(evts[1], INFINITE);
		if (strLen == -1)
		{
			SetEvent(evts[0]);
			break;
		}

		/* �������Է������Ļش𣬲����������� */
		int temp = recv(sock, buf, BUF_SIZE, 0);
		/* �������ַ����Ľ����� */
		buf[temp - 1] = '\0';
		myTrade.solveRecvBuf(buf);

		ResetEvent(evts[1]);
		SetEvent(evts[0]);
	}
	return 0;
}
