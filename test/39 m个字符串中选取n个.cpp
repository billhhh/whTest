#include <iostream>
#include <string>

using namespace std;

//������⣨��M����ͬ�ַ�����ȡN���ַ���������ϣ�
void combine(char *source,char *result,int n){

	//ƽ�����
	if (1==n){
		while (*source)
		{
			printf("%s%c\n",result,*source++);
		}
	}
	
	else{
		int i,j;
		for (i=0;source[i]!='\0';i++); //��ǰ�ַ�������
		for (j=0;result[j]!='\0';j++);
		for (;i>=n;i--)
		{
			result[j]=*source++;
			result[j+1]='\0';
			combine(source,result,n-1);
		}
	}
}

int main(int argc, char* argv[])
{
	int const n=4;
	char *source="abcdef",result[n+1]={'\0'};
	if (n>0 && strlen(source)>0 && n<=strlen(source))
	{
		combine(source,result,n);
	}
	//getchar();
	return 0;
}

