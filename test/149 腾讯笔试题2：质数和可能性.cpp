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

bool isPrime(int num) {
	
	for (int i = 2; i < num; ++i) {
		if (num%i == 0)
			return false;
	}
	return true;
}

int m[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449,
457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523,
541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677,
683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761,
769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853,
857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
941, 947, 953, 967, 971, 977, 983, 991, 997 };

bool isInMatrix(int num) {

	for (int i = 0; i < 168; ++i) {
		if (num == m[i])
			return true;
	}
	return false;
}

int main()
{
	/*freopen("primeOutput.txt","w",stdout);

	int count = 0;
	for (int i = 2; i <= 1000; ++i) {
		if (isPrime(i)) {
			cout << i << ",";
			count++;
		}
					
	}
	cout << endl << count << endl;;*/

	int input;
	cin >> input;

	int cnt = 0;
	for (int i = 0; m[i] <= input/2+1; ++i) {
		if (isInMatrix(input - m[i])) {
			cnt++;
			//cout << m[i] << "," << input - m[i] << endl;
		}
			
	}

	cout << cnt << endl;

	return 0;
}