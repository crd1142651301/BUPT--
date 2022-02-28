#pragma once
#include <process.h>
#include "trade.h"


#define BUF_SIZE 1024						//缓冲区大小
void ErrorHandler(char* message);			//调试
unsigned WINAPI WriteHandler(void* param);	//处理写操作
unsigned WINAPI ReadHandler(void* param);	//处理读进程
const int PORT = 8000;

//事件数组用来控制线程的读写
HANDLE evts[2];
//读取的标准输入的长度，用来接收客户端数据的最大值
int strLen = 0;
