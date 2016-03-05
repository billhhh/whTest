#include <iostream>
using namespace std;

int main() 
{
	int x=2,y,z;
	x*=(y=z=5); cout<<x<<endl; //输出10，相当于x*=y;

	z=3;
	x==(y=z); cout<<x<<endl; //输出10，不论是否相等，x不被赋值（编译器会warning，==无效）

	x=(y==z); cout<<x<<endl; //输出1，相等表达式返回值1

	x=(y&z); cout<<x<<endl; //按位与，y和z都是3（0011），按位与后是0011（还是3）

	x=(y&&z); cout<<x<<endl; //

	return 0; 
}