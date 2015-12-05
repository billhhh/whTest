#include "ClassA.h"
#include <iostream>

ClassA::ClassA()
{
	std::cout<<"ClassA ¹¹Ôìº¯Êý"<<std::endl;
	std::cout<<this->tmp<<std::endl;
	this->tmp = 55;
	std::cout<<this->tmp<<std::endl;
}
