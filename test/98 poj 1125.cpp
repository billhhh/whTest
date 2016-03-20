#include <stdio.h>
#include <iostream>
#define MAXN 102
#define INF 0x3f3f3f3f

using namespace std;

int map[MAXN][MAXN];

void Floyd(int sbNum) {

	//i to j
	for (int k=0;k<sbNum;++k) {

		for (int i=0;i<sbNum;++i) {
			for (int j = 0; j < sbNum; j++) {

				map[i][j] = (map[i][k]+map[k][j]) < map[i][j] ?
					map[i][k]+map[k][j]:
					map[i][j];
			}
		}
	}

}

int main() 
{
	//freopen("input.txt","r",stdin);

	while (1) {

		int sbNum;
		cin>>sbNum;
		
		if( !sbNum )
			break;

		//init
		for (int i=0;i<sbNum;++i) {
			for (int j = 0; j < sbNum; j++) {
				map[i][j] = INF;
			}
		}

		for (int i=0;i<sbNum;++i) {

			int n;
			cin>>n;
			for (int j = 0; j < n; j++) { //具体到哪个人

				int otherContact;
				cin>>otherContact;
				cin>>map[i][otherContact-1];
			}
		}
		//输入完毕

		Floyd(sbNum);

		int who = -1, time =INF;

		for (int i=0;i<sbNum;++i) {

			int tmpMax = -1;
			for (int j = 0; j < sbNum; j++) { //到其他人最大的作为最快速度

				if( i == j )
					continue;

				tmpMax = tmpMax>map[i][j]? tmpMax:map[i][j];
			}

			if( time > tmpMax ) {
				time = tmpMax;
				who = i+1;
			}
		}

		if( INF == time )
			cout<<"disjoint"<<endl;
		else
			cout<<who<<" "<<time<<endl;
	}

	return 0; 
}