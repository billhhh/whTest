#include <iostream>
using namespace std;

class Father
{
public:
	Father() {
		cout<<"父类诞生了"<<endl;
	}

	virtual ~Father() {
		cout<<"父类挂了"<<endl;
	}

protected:
private:
};

class Kid : public Father
{
public:
	Kid() {
		cout<<"子类诞生了"<<endl;
	}
	
	~Kid() {
		cout<<"子类挂了"<<endl;
	}

protected:
private:
};

int main() 
{
	Father *f = new Kid();
	delete f; //只delete父类，子类不会被析构

	cout<<endl;

	Father *f1 = new Kid();
	delete (Kid *)f1;

	return 0; 
}