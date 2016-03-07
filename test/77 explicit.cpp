#include <iostream>
using namespace std;

class Book
{
public:
	int num;
	Book(int n) {
		num = n;
	}

	Book() {
	}

protected:
private:
};

class Books
{
public:
	Book b;
	Books(Book tmp) {
		b=tmp;
	}
protected:
private:
};

int main() 
{
	Books books(2);

	return 0; 
}