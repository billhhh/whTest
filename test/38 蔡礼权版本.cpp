#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
using namespace std;

enum Op{
	NONE = 0,
	ADD,
	SUB,
	MUL,
	LEF,
	RIG,
	BLK
};

string char2str(char c){
	char tmp[30] = {0};
	sprintf_s(tmp, sizeof(tmp), "%c", c);
	return tmp;
}

Op isOperator(string c){
	Op op;
	if( c == "+")
		op = ADD;
	else if( c == "-")
		op = SUB;
	else if( c == "*")
		op = MUL;
	else if( c == "(")
		op = LEF;
	else if( c == ")")
		op = RIG;
	else if( c == " ")
		op = BLK;
	else
		op = NONE;
	return op;
}

int main(){
	int n;
	string str;
	getline(cin, str);
	n = atoi(str.c_str());
	char cstr[256];
	for( int i = 0; i < n; ++i){
		getline(cin, str);
		int len = str.length();
		if( str[0] != '('){
			cout<<"invalid expression"<<endl;
			continue;
		}

		stack<string> _stack;
		bool invalid = false;

		for( int m = 0; m < len; ++m){
			char c = str[m];
			string strTemp = char2str(c);
			if (c == ' '){
				continue;
			}
			if( isOperator(strTemp) == NONE){
				while( isOperator(char2str(str[m+1])) == NONE){
					strTemp += str[++m];
				}
			}

			if( c != ')'){
				_stack.push(strTemp);
			}else if( str[m] == ')'){
				bool isDone = false;
				vector<int> vec;
				while( 1){
					if( _stack.empty()){
						invalid = true;
						break;
					}
					string t = _stack.top();
					_stack.pop();
					Op op = isOperator(t);
					if( op == NONE){
						int num = atoi(t.c_str());
						vec.push_back(num);
					}else if( op == ADD){
						int sum = 0;
						if( vec.size() == 0){
							invalid = true;
							break;
						}
						for(int n = 0; n < vec.size(); ++n)
							sum += vec[n];
						char tmp[20];
						itoa(sum, tmp, 10);
						if( _stack.top() == "("){
							_stack.pop();
							isDone = true;
						}
						_stack.push(tmp);
					}else if( op == SUB){
						int _sub;
						if( vec.size() > 2){
							invalid = true;
							break;
						}else if( vec.size() == 1)
							_sub = vec[0]*-1;
						else
							_sub = vec[1]-vec[0];
						char tmp[20];
						itoa(_sub, tmp, 10);

						if( _stack.top() == "("){
							_stack.pop();
							isDone = true;
						}
						_stack.push(tmp);
					}else if( op == MUL){
						int _mul = 1;
						if( vec.size() <= 1){
							invalid = true;
							break;
						}
						for(int n = 0; n < vec.size(); ++n)
							_mul *= vec[n];
						char tmp[20];
						itoa(_mul, tmp, 10);
						if( _stack.top() == "("){
							_stack.pop();
							isDone = true;
						}
						_stack.push(tmp);
					}else if( op == LEF){
						break;
					}else if( op == RIG){
						invalid = true;
						break;
					}
					if( isDone)
						break;
				}

			}
			if( invalid)
				break;

		}
		if( _stack.size() != 1 || invalid)
			cout<<"invalid expression"<<endl;
		else
			cout<<atoi(_stack.top().c_str())<<endl;
		//printf("%s", str.c_str());
	}
	return 0;
}