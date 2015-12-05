#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <limits.h>
using namespace std;

#define MAXN 1000002
#define STEP INT_MAX
char str[MAXN];

enum Op{
	NONE = 0,
	ADD,
	SUB,
	MUL
};

Op isOperator(char c){
	Op op;
	if( c == '+')
		op = ADD;
	else if( c == '-')
		op = SUB;
	else if( c == '*')
		op = MUL;
	else
		op = NONE;
	return op;
}

int main(){
	int m;
	int n;
	char t;
	int res;
	int rrrrrp;
	int ttttt;
	vector<int> vec;
	scanf("%d\n",&n);

	for( int i = 0; i < n; ++i){
		//scanf("%s",cstr);
		gets(str);
		int len = strlen(str);

		if( str[0] != '(' || !isOperator(str[1])){
			cout<<"invalid expression"<<endl;
			continue;
		}

		stack<__int64> _stack;
		for( m = 0; m < len; ++m){

			if (isOperator(str[m]))
			{
				if(_stack.top()!='(')
				{
					cout<<"invalid expression"<<endl;
					goto over;
				}
			}

			if (str[m] == ' ') {
				continue;
			}

			if( str[m] != ')'){
				if (str[m]<='9' && str[m]>='0')
				{
					//当前是数字，但是前一个入栈是"("
					if(_stack.top()=='(') {
						cout<<"invalid expression"<<endl;
						goto over;
					}
						
					if(str[m-1]<='9' && str[m-1]>='0')
					{
						ttttt=_stack.top()-STEP;
						_stack.pop();
						_stack.push(ttttt*10+str[m]-'0'+STEP);
					}
					else
						_stack.push(str[m]-'0'+STEP);
				}
				else
					_stack.push(str[m]);
			}

			if( str[m] == ')'){
				//一定是 ')',开始弹栈
				if (_stack.size() == 1)
				{
					cout<<"invalid expression"<<endl;
					goto over;
				}
				vec.clear();
				while (true)
				{
					t = _stack.top();

					if (isOperator(t))
					{
						_stack.pop();
						_stack.pop();//前一个括号弹出

						if (t == '-')
						{
							if(vec.size()>2 || vec.size()<1)
							{
								cout<<"invalid expression"<<endl;
								goto over;
							}
							if(1==vec.size())
								_stack.push(0-vec.at(0)+STEP);
							else
								_stack.push(vec.at(1)-vec.at(0)+STEP); //推入结果
							break;
						}

						else if( t == '+')
						{
							if(vec.size()<1)
							{
								cout<<"invalid expression"<<endl;
								goto over;
							}

							res=0;
							for (int tmpcount=0;tmpcount<vec.size();++tmpcount)
							{
								res += vec.at(tmpcount);
							}
							_stack.push(res+STEP);
							break;
						}

						else if( t == '*')
						{
							if(vec.size()<1)
							{
								cout<<"invalid expression"<<endl;
								goto over;
							}

							int res=1;
							for (int tmpcount=0;tmpcount<vec.size();++tmpcount)
							{
								res *= vec.at(tmpcount);
							}
							_stack.push(res+STEP);
							break;
						}
					}//操作符

					else if (t!='(')
					{
						t-=STEP;
						//数字
						vec.push_back(t);
						_stack.pop();
					}
				}//while
			}//str[m] == ')'

		}//for 遍历

		rrrrrp=_stack.top()-STEP;
		cout<<rrrrrp<<endl;
		//printf("%s", str.c_str());

over:		
		continue;
	}
	return 0;
}
