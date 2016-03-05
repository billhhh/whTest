#include <iostream>
#include <string>
using namespace std;

class Student
{
	string Name; //Ä¬ÈÏÎªprivate
	mutable int times_of_getname;
public:
	Student(char *name)
		:Name(name),times_of_getname(0) {

	}

	string get_name() const{
		times_of_getname++;
		return Name;
	}

	void PrintTimes() const {
		cout<<times_of_getname<<endl;
	}
};

int main() 
{
	const Student s("BillÍõ");
	cout<<s.get_name()<<endl;
	cout<<s.get_name()<<endl;
	s.PrintTimes();

	return 0; 
}