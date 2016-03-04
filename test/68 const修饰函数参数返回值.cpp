#include <iostream>
using namespace std;

void disp1(const int &ri){
	cout<<ri<<endl;
}

void disp2(const int i){
	cout<<i<<endl;
}

const int disp3(const int& ri){
	cout<<ri<<endl;
	return ri;
}

int& disp4(int& ri){
	cout<<ri<<endl;
	return ri;
}

const int& disp5(int& ri){
	cout<<ri<<endl;
	return ri;
}


int main(int argc,char* argv[])
{
	int n=5;
	disp1(n);
	disp2(n);
	disp3(n);
	disp4(n)=6;
	disp5(n);//disp5(n)=6;ÊÇ´íÎóµÄ
}