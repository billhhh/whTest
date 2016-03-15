/* 
* 
* function: ������ջʵ�ֶ���
* 
* Date:2016-03-15
* 
*    Author: Bill Wang
*/

#include <iostream>
#include <queue>

using namespace std;

template <class T>
class whStack
{
public:
	whStack(){}
	~whStack(){}

	void push(T t);
	T pop();

private:
	std::queue<T> QueueA;
	std::queue<T> QueueB;
};

template<class T> void whStack<T>::push(T t) {

	//����һ��������Ϊ��תվ

	//step1����A��������Ԫ������B
	while ( !QueueA.empty() ) {
		T tmp = QueueA.front();
		QueueA.pop();
		QueueB.push(tmp);
	}

	//step2�������½ڵ�
	QueueA.push(t);

	//step3����B���лع�A
	while ( !QueueB.empty() ) {
		T tmp = QueueB.front();
		QueueB.pop();
		QueueA.push(tmp);
	}

}

//popʱֱ�ӵ���������T
template<class T> T whStack<T>::pop() {

	T res = QueueA.front();
	QueueA.pop();
	return res;
}

int main() 
{
	whStack<int > s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;

	return 0; 
}