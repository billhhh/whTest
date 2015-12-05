#include <iostream>
#include <string>
#define MAXN 1002
using namespace std;

char in1[MAXN];
char in2[MAXN];

int main()
{
	scanf("%s",in1);
	scanf("%s",in2);

	int count=0;
	for (int i=0;i<strlen(in1);++i)
	{
		if( (in1[i]>='0' && in1[i]<='9') || (in1[i]>='a' && in1[i]<='z') || (in1[i]>='A' && in1[i]<='Z') )
		{
			if (in2[i]=='1')
				count++;
		}

		else
		{
			if (in2[i]=='0')
				count++;
		}
	}

	printf("%.2lf%%\n",count*100.0/strlen(in1));
	
	return 0;
}
