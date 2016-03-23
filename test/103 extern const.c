#include <stdio.h>

//extern const int a;
int main()
{
	//freopen("input.txt","r",stdin);
	extern const int a;
	printf("%d\n",a);

	return 0;
}

//const int a = 66;