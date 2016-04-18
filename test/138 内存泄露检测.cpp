#ifndef _DETECT_MEM_LEAK_H_
#define _DETECT_MEM_LEAK_H_

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using namespace std;

#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

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

void GetMemory(char *p, int num)
{
	p = (char*)malloc(sizeof(char) * num);
}

int main(int argc,char** argv)
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	char *str = NULL;
	GetMemory(str, 100);
	cout<<"Memory leak test!"<<endl;
	//_CrtDumpMemoryLeaks();
	detect_memory_leaks(true);
	system("pause");

	return 0;
}

#endif