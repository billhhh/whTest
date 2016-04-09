#include <iostream>
#include <map>

using namespace std;

//======================================================

map<int ,int > BuyList;
map<int ,int > SaleList;

int main()
{
	//freopen("input.txt","r",stdin);

	int n; //委托数
	int s; //最抢手清单数

	cin>>n>>s;
	for(int i=0;i<n;++i) {
		
		char BorS;
		int price; //价格
		int stockNum; //数量
		
		cin>>BorS>>price>>stockNum;
		if(BorS == 'B') {
			if(BuyList.count(price) == 0)
				BuyList[price] = stockNum;
			else
				BuyList[price] += stockNum;
		}

		else {
			if(SaleList.count(price) == 0)
				SaleList[price] = stockNum;
			else
				SaleList[price] += stockNum;
		}
	}

	int cnt = 0;
	for(auto index = SaleList.end();; ) {
		if(cnt == s || index == SaleList.begin())
			break;
		--index;
		cout<<"S "<<index->first<<" "<<index->second<<endl;
		++cnt;
		if(cnt == s || index == SaleList.begin())
			break;
	}

	cnt = 0;
	for(auto index = BuyList.end();; ) {
		if(cnt == s || index == BuyList.begin())
			break;
		--index;
		cout<<"B "<<index->first<<" "<<index->second<<endl;
		++cnt;
		if(cnt == s || index == BuyList.begin())
			break;
	}

	return 0;
}