#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>  

using namespace std;

map<string,int> mapCount;

//������������
bool notCopy(pair<string,int> key_value){
	return key_value.second==1;
}

int main(){
	mapCount.insert(make_pair("000",0));
	mapCount.insert(make_pair("001",1));
	mapCount.insert(make_pair("002",2));
	mapCount.insert(make_pair("003",1));
	//mapCount["009"] = 6;

	map<string,int> mapCountTemp;//��ʱmap����
	//֮����Ҫ��inserter()��������Ϊͨ������insert()��Ա����������Ԫ�أ������û�ָ������λ��
	remove_copy_if(mapCount.begin(),mapCount.end(),inserter(mapCountTemp,mapCountTemp.begin()),notCopy);

	mapCount.swap(mapCountTemp);//ʵ�����������Ľ���

	cout<<mapCount.size()<<endl;     //���2
	cout<<mapCountTemp.size()<<endl; //���4

	//��֤
	//��ȷ���:
	//000 0
	//002 2
	for(map<string,int>::iterator it=mapCount.begin();it!=mapCount.end();++it){
		cout<<it->first<<" "<<it->second<<endl;
	}

	getchar();
}