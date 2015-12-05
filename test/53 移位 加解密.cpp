#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//加密 返回加密后id
int encryptBranchId(int if_id,int branch_id) {

	//把一个32位 unsigned 整数分成：
	///高16位做moduleId，低15位做branchId，符号位保留（不允许为负）
	int ui_branch_id = if_id<<15;
	ui_branch_id += branch_id;

	return ui_branch_id;
}

//解密
void decryptBranchId(int ui_branch_id,int &if_id,int &branch_id) {

	//高16位先分出来
	if_id = ui_branch_id >> 15;
	branch_id = ui_branch_id & 0x7FFF; //抹去高位
}

void showInBinary(int number) {

	char string[100];

	itoa(number, string, 2); 
	printf("integer = %3d string = %s\n", number, string);
}

int main() 
{
	int i = encryptBranchId(5798,15646);

	int t1,t2;
	decryptBranchId(i,t1,t2);

	return 0; 
}