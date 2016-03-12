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
// 	printf("%p\n%p\n",a,&a); //数值相等
// 
// 	cout<<sizeof(a)<<endl; // a是复合类型 int[5]
// 	cout<<sizeof(&a)<<endl; // &a是int(*)[5]
// 
// 	cout<<sizeof(a+1)<<endl; // a+1 变成指向数组第二个元素的指针，其类型是 int *
// 	cout<<sizeof(&a+1)<<endl; // &a+1 还是 int(*)[5]，类型还是指针
// 
// 	//a+1 因为 a 指向int（但不是普通指针），加1移动int个大小
// 	//&a+1 因为 &a 指向 int[5]，加1移动 int[5] 个大小
// 	printf("%p\n%p\n",a+1,&a+1);
// 
// 	cout<<sizeof(&a[0])<<endl;
// }
