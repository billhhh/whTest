#include "ClassB.h"
#include <iostream>

void ClassB::test(ClassA *a)
{
	printf("%d\n",a->tmp);
}

// int main()
// {
// 	ClassA *a = new ClassA();
// 	a->b = new ClassB();
// 	a->b->test(*a);
// 
// 	delete a->b;
// 	delete a;
// 	//delete a->b;
// 
// 	return 0;
// }
