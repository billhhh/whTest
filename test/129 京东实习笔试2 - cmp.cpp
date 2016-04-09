#include <iostream>
#include<stdlib.h>

using namespace std;

//======================================================

#define MAXN 1002

struct Buy
{
	int Pri;
	int Num;
};

struct Sale
{
	int Pri;
	int Num;
};

Buy BuyList[MAXN];
Sale SaleList[MAXN];


int bcmp ( const void *a , const void *b ) { return (*(Buy *)a).Pri > (*(Buy *)b).Pri ? -1 : 1; }
int scmp ( const void *a , const void *b ) { return (*(Sale *)a).Pri > (*(Sale *)b).Pri ? -1 : 1; }

int main()
{
	freopen("input.txt","r",stdin);

	int n; //委托数
	int s; //最抢手清单数

	cin>>n>>s;
	int sCnt = 0;
	int bCnt = 0;
	for(int i=0;i<n;++i) {

		char BorS;
		int price; //价格
		int stockNum; //数量

		cin>>BorS>>price>>stockNum;

		int j;
		if(BorS == 'B') {
			for (j=0;j<bCnt;++j) {
				if(BuyList[j].Pri == price) {
					BuyList[j].Num += stockNum;
					break;
				}
			}

			if(j == bCnt) {
				BuyList[bCnt].Pri = price;
				BuyList[bCnt].Num = stockNum;
				++bCnt;
			}
		}

		else {
			for (j=0;j<sCnt;++j) {
				if(SaleList[j].Pri == price) {
					SaleList[j].Num += stockNum;
					break;
				}
			}

			if(j == sCnt) {
				SaleList[sCnt].Pri = price;
				SaleList[sCnt].Num = stockNum;
				++sCnt;
			}
		}
	}

	//排序
	qsort(BuyList,bCnt,sizeof(BuyList[0]),bcmp);
	qsort(SaleList,sCnt,sizeof(SaleList[0]),scmp);

	for(int k = sCnt-s;k<s && k<sCnt; ++k) {
		cout<<"S "<<SaleList[k].Pri<<" "<<SaleList[k].Num<<endl;
	}

	for(int k = 0;k<s && k<bCnt; ++k) {
		cout<<"B "<<BuyList[k].Pri<<" "<<BuyList[k].Num<<endl;
	}

	return 0;
}