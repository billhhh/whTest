#include <iostream>
using namespace std;

class Test
{
public:
	int a[2][2];
	void set(int *tmpGragh) {
		for (int i=0;i<2; ++i){

			for (int j=0;j<2; ++j) {

				a[i][j]=tmpGragh[i*2+j];
			}
		}
	}
		
protected:


private:


};

int main() 
{
	int aa[2][2]={{1,2},{3,4}};
	Test t;
	t.set(&aa[0][0]);

	cout<<t.a[1][0]<<endl;
	
	return 0;
}