/*
*
* function: 内存泄露检测工具
*
* Date:2016-04-04
*
*    Author: Bill Wang
*/

#ifndef _DETECT_MEM_LEAK_H_
#define _DETECT_MEM_LEAK_H_

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using namespace std;

#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

//控制台输出
//on_ff 为true 打印内存泄漏, 为false则不打印
//程序进入时调用
void detect_memory_leaks(bool on_off) {

	int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	if (!on_off)
		flags &= ~_CRTDBG_LEAK_CHECK_DF;
	else {
		flags |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	}
	_CrtSetDbgFlag(flags);
}

//输出窗口
//on_ff 为true 打印内存泄漏, 为false则不打印
void detect_memory_leaks2(bool on_off) {

	if (!on_off) {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //程序进入时调用
		//_CrtDumpMemoryLeaks(); //程序退出时调用
	}
}

#endif

void GetMemory(char *p, int num)
{
	p = (char*)malloc(sizeof(char) * num);
}

int main(int argc,char** argv)
{
	detect_memory_leaks(true);
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	char *str = NULL;
	GetMemory(str, 100);
	cout<<"Memory leak test!"<<endl;
	//_CrtDumpMemoryLeaks();
	system("pause");

	return 0;
}
