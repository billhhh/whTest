#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void sing()
	{
		printf("Animal is singing!\n");
	}
};

class Cat : public Animal
{
public:
	void sing()
	{
		printf("Cat is singing!\n");
	}

	void eat()
	{
		printf("Cat is eating!\n");
	}
};

int main(void)
{
	Animal a;
	Cat *cp = (Cat *)&a;
	cp->sing();
	cp->eat();

	//±àÒë´íÎó
// 	Cat c;
// 	Animal a = c;
// 	a.eat();

	return 0;
}