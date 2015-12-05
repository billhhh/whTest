#include <iostream>
#include "3 TemplateStringToNum.h"

using namespace std;

double find_weight_num(int position,string content){

	int start_pos = content.find("(",position);
	int end_pos = content.find(")",position);
	int lenth = end_pos - start_pos+1;

	string numStr = content.substr(start_pos+1,lenth);
	return stringToNum<double> (numStr);
}

int main()
{
	string str("Cost(275.3),Weight(4999.15),Cust(17) 36 38 40 39 26 27 30 14 25 3 2 20 6 7 32 35\n34");
	//cout<<"original str == "<<str<<endl;

	int position = 0;
	position=str.find("Weight",position);
	double return_double = find_weight_num(position,str);

	cout<<return_double<<endl;

	return 0;
}