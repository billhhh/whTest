#include <iostream>
using namespace std;

void fun5(int *&);  //��������������ʱ��������д������

int main()
{
	int a,*p=&a;
	cout<<"��main������p�ĵ�ַ�ǣ�"<<&p<<"p�д�ŵĵ�ַ�ǣ���a�ĵ�ַ����"<<p<<endl;
	fun5(p);

	return 0;
}

void fun5(int *& rp) //�������壬����ʵ�ֹ��̣���Ҫд��������ָ�������
{
	cout<<"��fun5������rp�ĵ�ַ�ǣ�"<<&rp<<"rp�д�ŵĵ�ַ�ǣ�"<<rp<<endl;
	return;
}
