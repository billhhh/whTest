#include <iostream>
using namespace std;

const long M=999999999;

void Merge(int A[],long Left,long Middle,long Right,int length)
{
	long n1=Middle-Left+1;
	long n2=Right-Middle;

	int *L = new int[n1+2]; //Ԥ���ռ�
	int *R = new int[n2+2];

	L[n1+1]=M; //�ڱ�
	R[n2+1]=M;

	long i;
	int oddCnt = 0;
	if (Right == length -1 ){

		//���һ�����������ż��
		for(i=1;i<=n1;i++){
			L[i]=A[Left+i-1];
			if( L[i]%2 == 0 )
				oddCnt++;
		}
		for(i=1;i<=n2;i++) {
			R[i]=A[Middle+i];
			if( L[i]%2 == 0 )
				oddCnt++;
		}

		i=1;
		long j=1;
		long oddPos = 0,evenPos = oddCnt;
		for(long k=Left;k<=Right; )
		{
			//���ĳһ���ȵִ��ڱ�����һ��һ����С�ڵ�
			if(L[i]<=R[j]) {
					A[k]=L[i++];
			}

			else
				A[k]=R[j++];
		}
	}else {

		//�ֳ���������
		for(i=1;i<=n1;i++)
			L[i]=A[Left+i-1];
		for(i=1;i<=n2;i++)
			R[i]=A[Middle+i];

		i=1;
		long j=1;
		for(long k=Left;k<=Right;k++)
		{
			//���ĳһ���ȵִ��ڱ�����һ��һ����С�ڵ�
			if(L[i]<=R[j]) {

				if(L[i]<=R[j])
					A[k]=L[i++];
			}

			else
				A[k]=R[j++];
		}
	}

	delete L,R;
}

void Merge_sort(int A[],long Left,long Right,int length)
{
	long Middle;
	if(Left<Right)
	{
		Middle=(Left+Right)/2; 
		Merge_sort(A,Left,Middle,length);  // ���ַֽ��󲿷�
		Merge_sort(A,Middle+1,Right,length); // ���ַֽ��в���
		Merge(A,Left,Middle,Right,length); //�ϲ�������
	}
}

void sort(int *array,int length) {

	Merge_sort(array,0,length-1,length);
}

int main() 
{
	int array[10] = {4,5,7,1,22,33,8,10,23,199};

	int length = 10;
	sort(array,length);

	for(int i=0;i<10;++i) {
		cout<<array[i]<<" ";
	}

	return 0; 
}