#include<stdio.h>
#include <iostream>

using namespace std;

// int main()   
// {   
// 	int a[10];
// 
// 	printf("a:\t%p\n", a);
// 	printf("&a:\t%p\n", &a);
// 	printf("a+1:\t%p\n", a+1);
// 	printf("&a+1:\t%p\n", &a+1);
// 
// 	return 0;
// }

int main()
{
	int a[5]={0x11121314,0x21222324,0x31323334,0x41424344,0x51525354};
	int *ptr1=(int *)(&a+1);
	//int *ptr2=(int *)(a+1);
	int *ptr2=(int *)((int)a+1);

	printf("%x\n%x\n",ptr1[-1],*ptr2);
}

// int main()
// {
// 	int a[5]={0x11121314,0x21222324,0x31323334,0x41424344,0x51525354};
// 	printf("%p\n%p\n",a,&a); //��ֵ���
// 
// 	cout<<sizeof(a)<<endl; // a�Ǹ������� int[5]
// 	cout<<sizeof(&a)<<endl; // &a��int(*)[5]
// 
// 	cout<<sizeof(a+1)<<endl; // a+1 ���ָ������ڶ���Ԫ�ص�ָ�룬�������� int *
// 	cout<<sizeof(&a+1)<<endl; // &a+1 ���� int(*)[5]�����ͻ���ָ��
// 
// 	//a+1 ��Ϊ a ָ��int����������ָͨ�룩����1�ƶ�int����С
// 	//&a+1 ��Ϊ &a ָ�� int[5]����1�ƶ� int[5] ����С
// 	printf("%p\n%p\n",a+1,&a+1);
// 
// 	cout<<sizeof(&a[0])<<endl;
// }
