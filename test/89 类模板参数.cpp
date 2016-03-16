#include <iostream>
using namespace std;

template<class T> class A{
public:
	T g(T a,T b);
	A();
};

template<class T> A<T>::A(){}

template<class T> T A<T>::g(T a,T b){
	return a+b;
}

int main() 
{
	A<double> a;
	cout<<a.g(6.5,3)<<endl;

	return 0; 
}