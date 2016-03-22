#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cassert>
#include <time.h>
#include <queue>
#include <map>
#include <stack>
#include <bitset>
#include <string>
#include <sstream>
#include <list>
#define INF 0x3f3f3f3f

using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}

//======================================================

#define MAXN 250002

int a[MAXN];

int Partition(int *arr, int i,int j) {

	arr[0] = arr[i]; //arr[0] is a temp space

	while(i<j) {

		while(i<j && arr[j] >= arr[0]) --j;

		if( i < j) { //move the smaller element to the front
			arr[i] = arr[j];
			++i;
		}

		while(i<j && arr[i] < arr[0]) ++i;

		if( i < j) { //move the bigger element to the tail
			arr[j] = arr[i];
			--j;
		}
	}

	arr[i] = arr[0];
	return i;
}

void quickSort(int *arr, int left,int right) {

	int i;
	if(left<right) {
		i = Partition(arr,left,right); //divide the arr into 2 parts
		quickSort(arr,left,i-1);
		quickSort(arr,i+1,right);
	}
}

int main()
{
	//freopen("input.txt","r",stdin);

	int N;
	cin>>N;

	for (int i = 1; i <= N; ++i) {
		scanf("%d",&a[i]);
	}

	quickSort(a,1,N);

	if(N%2) //odd
		printf("%d.0\n", a[(N+1)/2]);
	else {
		double sum = (double)a[N/2] + (double)a[N/2+1];
		printf("%.1lf\n", sum / 2);
	}

	return 0;
}