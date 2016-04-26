#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>  

using namespace std;

map<string,int> mapCount;

//不拷贝的条件
bool notCopy(pair<string,int> key_value){
	return key_value.second==1;
}

int main(){
	mapCount.insert(make_pair("000",0));
	mapCount.insert(make_pair("001",1));
	mapCount.insert(make_pair("002",2));
	mapCount.insert(make_pair("003",1));
	//mapCount["009"] = 6;

	map<string,int> mapCountTemp;//临时map容器
	//之所以要用inserter()函数是因为通过调用insert()成员函数来插入元素，并由用户指定插入位置
	remove_copy_if(mapCount.begin(),mapCount.end(),inserter(mapCountTemp,mapCountTemp.begin()),notCopy);

	mapCount.swap(mapCountTemp);//实现两个容器的交换

	cout<<mapCount.size()<<endl;     //输出2
	cout<<mapCountTemp.size()<<endl; //输出4

	//验证
	//正确输出:
	//000 0
	//002 2
	for(map<string,int>::iterator it=mapCount.begin();it!=mapCount.end();++it){
		cout<<it->first<<" "<<it->second<<endl;
	}

	getchar();
}