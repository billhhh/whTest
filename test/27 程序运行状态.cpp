#include<stdio.h>
#include<string>

int overflow(char *buf)
{
	char output[20];
	strcpy(output,buf);
	printf("out char output[20]\n",output);
	printf("press Enter to return\n",output);
	getchar();
	return 0;
}

int main()
{
	char buf[100];
	int j;
	for(j=0;j<100;j++)
	{
		buf[j]='A';
	}
	overflow(buf);
	return 0;
}