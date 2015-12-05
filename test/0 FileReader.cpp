#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	ifstream myfile ("D:\\TESTCASE\\∏Ò Ω2.txt");
	string buf;
	string outStr;

	if(!myfile){
		cout << "Unable to open myfile";
		exit(1); // terminate with error
	}

	while (myfile)
	{
		if( getline( myfile, buf ) ){  
			outStr.append(buf);
			outStr.append("\n");
		}
	}

	cout<<outStr<<endl;

	return 0;
}
