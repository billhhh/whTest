#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//���� ���ؼ��ܺ�id
int encryptBranchId(int if_id,int branch_id) {

	//��һ��32λ unsigned �����ֳɣ�
	///��16λ��moduleId����15λ��branchId������λ������������Ϊ����
	int ui_branch_id = if_id<<15;
	ui_branch_id += branch_id;

	return ui_branch_id;
}

//����
void decryptBranchId(int ui_branch_id,int &if_id,int &branch_id) {

	//��16λ�ȷֳ���
	if_id = ui_branch_id >> 15;
	branch_id = ui_branch_id & 0x7FFF; //Ĩȥ��λ
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