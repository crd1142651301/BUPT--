#pragma once
#include <process.h>
#include "trade.h"


#define BUF_SIZE 1024						//��������С
void ErrorHandler(char* message);			//����
unsigned WINAPI WriteHandler(void* param);	//����д����
unsigned WINAPI ReadHandler(void* param);	//���������
const int PORT = 8000;

//�¼��������������̵߳Ķ�д
HANDLE evts[2];
//��ȡ�ı�׼����ĳ��ȣ��������տͻ������ݵ����ֵ
int strLen = 0;
