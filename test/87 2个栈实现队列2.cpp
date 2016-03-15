/* 
* 
* function: ������ջʵ�ֶ���2
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

	//�ж���һ�����зǿ�
	if( !QueueA.empty() )
		QueueA.push(t);
	else
		QueueB.push(t);
}

//popʱֱ�ӵ���������T
template<class T> T whStack<T>::pop() {


	std::queue<T> &qa = QueueA.empty()? QueueB:QueueA;
	std::queue<T> &qb = QueueA.empty()? QueueA:QueueB;

	//����β���һ��Ԫ����ס��������Ԫ������һ������
	T tmp;
	while (1) {

		tmp = qa.front();
		qa.pop();

		if( qa.empty() )
			break;

		qb.push(tmp);
	}

	return tmp;
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