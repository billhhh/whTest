#include <iostream>
using namespace std;

int main() 
{
	int x=2,y,z;
	x*=(y=z=5); cout<<x<<endl; //���10���൱��x*=y;

	z=3;
	x==(y=z); cout<<x<<endl; //���10�������Ƿ���ȣ�x������ֵ����������warning��==��Ч��

	x=(y==z); cout<<x<<endl; //���1����ȱ��ʽ����ֵ1

	x=(y&z); cout<<x<<endl; //��λ�룬y��z����3��0011������λ�����0011������3��

	x=(y&&z); cout<<x<<endl; //

	return 0; 
}