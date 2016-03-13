#include <iostream>
using namespace std;

void Merge(long Left,long Middle,long Right)
{
	long n1=Middle-Left+1;
	long n2=Right-Middle;

	long i,k;
	for(i=1;i<=n1;i++)
		L[i]=A[Left+i-1];
	for(i=1;i<=n2;i++)
		R[i]=A[Middle+i];

	L[n1+1]=M;
	R[n2+1]=M;

	i=1;
	long j=1;
	for(k=Left;k<=Right;k++)
	{
		if(L[i]<=R[j])
			A[k]=L[i++];

		else
		{
			A[k]=R[j++];
			cunt+=n1-i+1;                 //cunt为全局变量
		}
	}
}

void Merge_sort(int A[],long Left,long Right)
{
	long Middle;
	if(Left<Right)
	{
		Middle=(Left+Right)/2; 
		Merge_sort(A,Left,Middle);  // 二分分解左部分
		Merge_sort(A,Middle+1,Right); // 二分分解有部分
		Merge(Left,Middle,Right); //合并两部分
	}
}

int main() 
{

	return 0; 
}