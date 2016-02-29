#include <iostream>
#include <map>
#include "63.h"

using namespace std;

int main() 
{
	map<int , int > m;
	m[1] = 100;
	m[2] = 200;
	m[3] = 300;

	eraseMap(m);

	return 0; 
}