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
#define INF 0x3f3f3f3f

#define PRINT(x) cout<<x<<endl;

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

int find_tri(int* A, int num, int cnt) {

	for (int i = 0; i < cnt; i++)
		if (A[i] == num)
			return 1;

	return 0;
}

int main()
{
	//freopen("input.txt","r",stdin);

	int k=10;
	int arr[10] = {1,-2,3,-1,2,-3,4,5,-5,6};

	int neg_cnt = 0;
	int pos_cnt = 0;
	int arr_negtive[10];
	int arr_positive[10];
	for (int i = 0; i < k; i++) {
		if (arr[i] < 0)
			arr_negtive[neg_cnt++] = arr[i];
		else
			arr_positive[pos_cnt++] = arr[i];
	}

	// for triplets
	int tri_count = 0;
	int res;
	for (int i = 0; i < pos_cnt; i++)
		for (int j = 0; j < neg_cnt; j++) {
			int sum = arr_positive[i] + arr_negtive[j];
			if (sum < 0)
				res = find_tri(arr_positive, -sum, pos_cnt);
			else
				res = find_tri(arr_negtive, -sum, neg_cnt);

			if (res == 1 && -sum != arr_positive[i] && -sum != arr_negtive[j]) {
				tri_count++;
				cout << arr_positive[i] << " " << arr_negtive[j] << " " << -sum << endl;
			}
		}

	cout << tri_count << endl;
	return 0;
}