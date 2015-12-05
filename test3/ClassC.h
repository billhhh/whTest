#ifndef _CLASS_C_H_
#define _CLASS_C_H_

#include "ClassA.h"
#include "ClassB.h"

class ClassC: public ClassA
{
public:
	ClassB *b;
	ClassC();

protected:


private:


};


#endif