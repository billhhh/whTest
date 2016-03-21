#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int res[12][12];
int digitCnt[6] ={0}; //��λ���м���
int miniCnt[6] = {0}; //��λ��֮С��
int equalCnt[6] = {0}; //�Ƿ����������λ�����

int manyDigit(int a) {

	int cnt = 1;
	while ( a/=10 ) {
		++cnt;
	}

	return cnt;
}

//get�ض�λ��
int getDigit(int a, int n) {

	int p = pow(10,n-1);
	return (a/p)%10;
}

void work(int &resCnt,int deep,int n) {

	if(deep == n) { //�ݹ��������
		return;
	}

	if ( equalCnt[deep] ) { //��������
		
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

				for (int j=0;j<=9;++j) { //0-9������

					if( 0 == LED[j][tmp-48] )
						//��ĳ������j���Ǻ�
						res[i][j] = 0; //��λ����Ϊj
				}
			}
		}

		//������ϣ��ó�res����Ϊ������
		//�ж�N�Ǽ�λ��
		int highdigit = manyDigit(N);

		//ǰ��0
		for (int i=0;i<K-highdigit;++i) {
			if( res[i][0] != 1 ) {
				//����
				cout<<"0"<<endl;
				goto start;
			}
		}

		//N���λ���Ƿ��֮С��
		int tmpDigit = getDigit(N,highdigit);
		int tmpFlag = 0;
		for (int i=0;i<=tmpDigit;++i) {
			if( res[K-highdigit][i] == 1 ) {
				tmpFlag = 1;
				break;
			}
		}
		if (tmpFlag == 0) {
			//����
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

		//�������
		int resCnt = 0;
		int deep = K-highdigit;
		work(resCnt,deep,K);

		cout<<resCnt<<endl;
		//system("pause");
	}//while(T--)

	return 0; 
}