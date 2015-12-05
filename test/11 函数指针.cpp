#include <stdio.h>
#include <stdlib.h>

//int* (*a[5])(int,char*);

typedef int (*f)(int,char*);
f funp;

int foo(int n, char *s)
{
	return 10086;
}

int main(int argc, char *argv[])
{
	funp = foo;

	printf("%x\n",funp);
	printf("%d\n",(*funp)(6,"test"));

	return 0;
}
