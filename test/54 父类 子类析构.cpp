#include <iostream>
using namespace std;

class Father
{
public:
	Father() {
		cout<<"���൮����"<<endl;
	}

	virtual ~Father() {
		cout<<"�������"<<endl;
	}

protected:
private:
};

class Kid : public Father
{
public:
	Kid() {
		cout<<"���൮����"<<endl;
	}
	
	~Kid() {
		cout<<"�������"<<endl;
	}

protected:
private:
};

int main() 
{
	Father *f = new Kid();
	delete f; //ֻdelete���࣬���಻�ᱻ����

	cout<<endl;

	Father *f1 = new Kid();
	delete (Kid *)f1;

	return 0; 
}