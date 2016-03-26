#include <stdio.h>

typedef struct test
{
	int a;
	int b;
	test() {printf("struct construct\n");};

}myTest;

int main()
{
	myTest t;
	t.a = 1;
	t.b = 2;

	return 0;
}