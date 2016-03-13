#include <iostream>
using namespace std;

const long M=999999999;

void Merge(int A[],long Left,long Middle,long Right)
{
	long n1=Middle-Left+1;
	long n2=Right-Middle;

	int *L = new int[n1+2]; //预留空间
	int *R = new int[n2+2];

	long i,k;
	//
	for(i=1;i<=n1;i++)
		L[i]=A[Left+i-1];
	for(i=1;i<=n2;i++)
		R[i]=A[Middle+i];

	L[n1+1]=M; //哨兵
	R[n2+1]=M;

	i=1;
	long j=1;
	for(k=Left;k<=Right;k++)
	{
		if(L[i]<=R[j])
			A[k]=L[i++];

		else
			A[k]=R[j++];
	}

	delete L,R;
}

void Merge_sort(int A[],long Left,long Right)
{
	long Middle;
	if(Left<Right)
	{
		Middle=(Left+Right)/2; 
		Merge_sort(A,Left,Middle);  // 二分分解左部分
		Merge_sort(A,Middle+1,Right); // 二分分解有部分
		Merge(A,Left,Middle,Right); //合并两部分
	}
}

int main() 
{
	int array[10] = {4,5,7,1,22,33,8,10,23,199};

	Merge_sort(array,0,9);

	return 0; 
}