#include <stdio.h>

//extern const int a;
int main()
{
	extern int a;
	printf("%d\n",a);

	return 0;
}

//const int a = 66;