#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int res[12][12];
int digitCnt[6] ={0}; //该位可行计数
int miniCnt[6] = {0}; //该位比之小的
int equalCnt[6] = {0}; //是否和所比数当位有相等

int manyDigit(int a) {

	int cnt = 1;
	while ( a/=10 ) {
		++cnt;
	}

	return cnt;
}

//get特定位数
int getDigit(int a, int n) {

	int p = pow(10,n-1);
	return (a/p)%10;
}

void work(int &resCnt,int deep,int n) {

	if(deep == n) { //递归结束条件
		return;
	}

	if ( equalCnt[deep] ) { //如果可相等
		
		work(resCnt,deep+1,n);
		int tmpCnt = miniCnt[deep];
		for (int i=deep+1;i<n;++i)
			tmpCnt*=digitCnt[i];

		resCnt += tmpCnt;
	}else {

		int tmpCnt = miniCnt[deep];
		for (int i=deep+1;i<n;++i)
			tmpCnt*=digitCnt[i];

		resCnt += tmpCnt;
	}
}

int main() 
{
	freopen("input.txt","r",stdin);

	int LED[10][8]={
		 0,1,1,1,0,1,1,1 //0
		,0,0,0,1,0,0,1,0 //1
		,0,1,0,1,1,1,0,1 //2
		,0,1,0,1,1,0,1,1 //3
		,0,0,1,1,1,0,1,0 //4
		,0,1,1,0,1,0,1,1 //5
		,0,1,1,0,1,1,1,1 //6
		,0,1,0,1,0,0,1,0 //7
		,0,1,1,1,1,1,1,1 //8
		,0,1,1,1,1,0,1,1 //9
	};

	int T;
	cin>>T;

start:
	while (T--) {

		//init
		for (int i=0;i<12;++i) {
			for (int j=0;j<12;++j) {
				res[i][j] = 1;
			}
		}

		memset(digitCnt,0,sizeof(digitCnt));
		memset(miniCnt,0,sizeof(miniCnt));
		memset(equalCnt,0,sizeof(equalCnt));

		int K;
		cin>>K;
		int N;
		cin>>N;

		getchar();
		for (int i=0;i<K;++i) {

			while (1){
				char tmp;
				tmp = getchar();

				if(tmp == ' ')
					continue;

				if(tmp=='\n')
					break;

				for (int j=0;j<=9;++j) { //0-9个数字

					if( 0 == LED[j][tmp-48] )
						//与某个数字j不吻合
						res[i][j] = 0; //此位不能为j
				}
			}
		}

		//输入完毕，得出res可以为的数字
		//判断N是几位数
		int highdigit = manyDigit(N);

		//前导0
		for (int i=0;i<K-highdigit;++i) {
			if( res[i][0] != 1 ) {
				//错误
				cout<<"0"<<endl;
				goto start;
			}
		}

		//N最高位，是否比之小的
		int tmpDigit = getDigit(N,highdigit);
		int tmpFlag = 0;
		for (int i=0;i<=tmpDigit;++i) {
			if( res[K-highdigit][i] == 1 ) {
				tmpFlag = 1;
				break;
			}
		}
		if (tmpFlag == 0) {
			//错误
			cout<<"0"<<endl;
			goto start;
		}

		for (int i=K-highdigit;i<K;++i) {

			for(int j=0;j<=9;++j) {
				if(res[i][j] == 1) {
					digitCnt[i]++;
					if( j<getDigit(N,K-i) )
						miniCnt[i]++;

					else if(j == getDigit(N,K-i))
						equalCnt[i]++;
				}
			}
		}

		//计算个数
		int resCnt = 0;
		int deep = K-highdigit;
		work(resCnt,deep,K);

		cout<<resCnt<<endl;
		//system("pause");
	}//while(T--)

	return 0; 
}