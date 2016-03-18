/* 
* 
* function: 源代码编译
* 
* Date:2016-03-18
* 
*    Author: Bill Wang
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#define MAXN 1002

using namespace std;

typedef struct myStruct
{
	string name;
	int dependCnt;
	int visited;

	myStruct() {
		visited = 0;
	}
}cppFile;

cppFile cppfile[MAXN];
map<int, vector<int>>  fileDependMap; //文件依赖关系映射表

int main() 
{
	int t;
	cin>>t;

	while (t--) {

		int n;
		cin>>n;

		//init
		fileDependMap.clear();
		for (int i=0;i<n;++i) {
			cppfile[i].dependCnt=0;
			cppfile[i].visited = 0;
		}

		//输入数据
		for (int i=0;i<n;++i) {
			cin>>cppfile[i].name;
			cin>>cppfile[i].dependCnt;

			for (int j=0;j<cppfile[i].dependCnt;++j) {
				int tmpDepend;
				cin>>tmpDepend;

				if(fileDependMap.count(tmpDepend)>0) {
					vector<int > tmpV = fileDependMap[tmpDepend];
					tmpV.push_back(i);
				}else {
					vector<int > tmpV;
					tmpV.push_back(i);
					fileDependMap[tmpDepend] = tmpV;
				}
			}
		}

		//字典序排序
		for (int i=0;i<n-1;++i) {
			for(int j=i+1;j<n;++j) {
				if( cppfile[i].name > cppfile[j].name ) {
					cppFile tmp = cppfile[i];
					cppfile[i] = cppfile[j];
					cppfile[j] = tmp;
				}
			}
		}

		while (1) {
			int flag = 0; //判断有没有改变
			int errorFlag = 0;
			for (int i=0;i<n;++i) {

				if(cppfile[i].dependCnt == 1)
					errorFlag = 1;

				if( cppfile[i].visited == 0 && cppfile[i].dependCnt == 0 ) {
					//如果为0，以该文件为基础的文件都减1
					for (int j=0;j<fileDependMap[i].size();++j) {
						cppfile[fileDependMap[i][j]].dependCnt--;
					}
					cppfile[i].visited = 1;
					flag = 1;
					cout<<cppfile[i].name<<endl;
				}
			}

			if(flag == 0 && errorFlag == 1) {
				cout<<"ERROR"<<endl<<endl;
				break;
			}

			else if(flag == 0 && errorFlag == 0) { //已经没有可改变的
				cout<<endl;
				break;
			}
		}

	}

	return 0; 
}