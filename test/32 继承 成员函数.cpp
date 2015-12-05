/* 
* 
* funtion: ע�⣬���±�ע�͵Ĵ��룬���Ƿ��ʲ�����
* 
* Date:2015-7-29
* 
*    Author: Bill Wang
*/

#include<iostream>
using namespace std;

//����O�зֱ�����������ͬ�������͵ĺ���
class O{
public:
	void F2()
	{
		cout<<"this is O's public function F2"<<endl;
	}
private:
	void F1();
protected:
	void F3();
};

//��P�����̳���O
class P:protected O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//��Q���м̳���O
class Q:public O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//��R˽�м̳���O
class R:private O{
public:
	/*
	void test_F1()
	{
		F1();
	}
	*/
	void test_F2()
	{
		F2();
	}
	void test_F3()
	{
		F3();
	}
};

//�����������ڻ����ⶼһ��
void O::F1()
{
	cout<<"this is O's private function F1"<<endl;
}
void O::F3()
{
	cout<<"this is O's protected function F3"<<endl;
}

//������
int main()
{
	O o;
	P p; //�����̳�
	Q q; //���м̳�
	R r; //˽�м̳�

	cout<<"O:"<<endl;
	//o.F1(); //˽�з���
	o.F2(); //���з���
	//o.F3(); //��������
	cout<<endl;

	//���ּ̳У���Ա�������һ��

	cout<<"P:"<<endl;
//	p.test_F1(); //˽�з������ʲ���
	p.test_F2();
	p.test_F3();
	//p.F1();
	//p.F2();
	//p.F3();
	cout<<endl;

	cout<<"Q:"<<endl;
//	q.test_F1();
	q.test_F2();
	q.test_F3();
	//q.F1();
	q.F2();
	//q.F3();
	cout<<endl;

	cout<<"R:"<<endl;
//	r.test_F1();
	r.test_F2();
	r.test_F3();
	//r.F1();
	//r.F2();
	//r.F3();

	return 0;
}