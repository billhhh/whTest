#include<iostream>
#include<string.h>
using namespace std;

const int MAXN=500;
int map[MAXN][MAXN];

void printMap(int n) {
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) {
			cout<<map[i][j]<<" ";
		}
	}
	cout<<endl;
}

int main() {

	int n;
	cin>>n;

	for(int i=0;i<=n+1;++i) {
		for(int j=0;j<=n+1;++j)
			map[i][j] = MAXN; //ÉèÖÃÉÚ±ø
	}

	//init
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j)
			map[i][j] = 0;
	}

	int cnt = 1;
	int col = 1;
	int row = 1;
	while(cnt<=n*n) {
		//ÉÏºá
		while( 0 == map[row][col] ) {
			map[row][col++]=cnt++;

			if(cnt==n*n+1) {
				printMap(n);
				return 0;
			}
		}
		col--;
		row++;

		//ÓÒÊú
		while( 0 == map[row][col] ) {
			map[row++][col]=cnt++;

			if(cnt==n*n+1) {
				printMap(n);
				return 0;
			}
		}
		row--;
		col--;

		//ÏÂºá
		while( 0 == map[row][col] ) {
			map[row][col--]=cnt++;

			if(cnt==n*n+1) {
				printMap(n);
				return 0;
			}
		}
		col++;
		row--;

		//×óÊú
		while( 0 == map[row][col] ) {
			map[row--][col]=cnt++;

			if(cnt==n*n+1) {
				printMap(n);
				return 0;
			}
		}
		row++;
		col++;
	}

	return 0;
}