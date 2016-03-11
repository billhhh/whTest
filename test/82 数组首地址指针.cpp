#include <iostream>
using namespace std;

void ShowValue(int *i) {
	cout<<i<<endl;
}

int main(int argc,char *argv[])
{
// 	int b[5]={111,666,3,4,5};
// 
// 	int *pos = (int *)&b;
// 	cout<<*pos<<endl;
// 	(*pos)++;
// 	cout<<*pos<<endl;
	//ShowValue((int *)&b);


	int a = 6;
	int *p = &a;
	
	cout<<&a<<endl;
 	int *pp = (int *)&p;
	cout<<p<<endl;
 	(*pp) += 4;
 	cout<<p<<endl;

	return 0; 
}
