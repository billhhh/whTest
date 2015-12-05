#include "ClassC.h"
#include <iostream>

ClassC::ClassC()
{
	std::cout<<"ClassC ¹¹Ôìº¯Êý"<<std::endl;
	std::cout<<this->tmp<<std::endl;
	this->tmp = 105;
	std::cout<<this->tmp<<std::endl;
}

int main()
{
	//ClassA *ap = new ClassC();
	ClassC *cp = new ClassC();
	cp->b = new ClassB();
	cp->b->test(cp);

	return 0;
}
