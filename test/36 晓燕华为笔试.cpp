#include <iostream>
#include <string>
using namespace std;

char in[1024];
char out[1024];

void work(char *in,char *out,const int length,int cur,int start,const int m)
{
	if( cur>m )
		return;

	int i;
	for(i=start;i<length;i++)
	{
		out[cur] = in[i];
		out[cur+1] = '\0';

		(m == strlen(out))?
			cout<<out<<"\n":true;

		(i<length-1)?
			work(in, out, length, cur+1, i+1,m):true; //cur = ²ãÊı
	}
}

int main()
{
	int m;
	cin>>in;
	cin>>m;
// 	char *in="abcde";
// 	m=3;

	m>strlen(in)?
		(cout<<"ERROR"<<endl):true;

	work(in, out, strlen(in), 0, 0, m);

	return 0;
}