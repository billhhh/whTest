#include <iostream>
#define INF 0x3f3f3f3f

using namespace std;

int res[10];

int main()
{
	//freopen("input.txt","r",stdin);

	int input;
	cin >> input;

	int left = -90;
	int right = 90;

	int count = 0;
	while (left <= right && count <= 6) {

		count++;
		int middle = (left + right) / 2;

		if (input < middle) {
			res[count] = 0;
			right = middle;
		}
		else if (input > middle) {
			res[count] = 1;
			left = middle;
		}
		else
			break;

	}

	for (int i = 1; i <= 6; ++i) {
		cout << res[i];
	}
	cout << endl;

	return 0;
}