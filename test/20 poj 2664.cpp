#include <iostream>
using namespace std;

int choice[102];  //Freddie's choice

int main()
{
	int k,m,c,r;
	int flag; //����Ƿ�ϸ񣬱�����ڣ���ʹ��ǰ֪�����ϸ�Ҳ��Ҫ���������
	int tempCourse; //����ÿ�α�������γ̺�
	while (scanf("%d",&k)!=EOF)
	{
		if(0 == k)
			break;
		flag=1;
		cin>>m;

		for (int i=0;i<k;++i)
			cin>>choice[i];

		for (int i=0;i<m;++i)
		{
			cin>>c>>r;
			int count=0; //�����������Ȳ�����r
			for (int j=0;j<c;++j)
			{
				cin>>tempCourse;
				if (0 == flag)
					continue;
				
				//����ѧ���Ŀγ�
				for (int it=0;it<k;++it)
				{
					if( choice[it]==tempCourse ){
						++count;
						break;
					}
				}
			}
			if(count<r) //�����Ѿ����ϸ���
				flag=0;
		}
		if(flag == 0)
			cout<<"no"<<endl;

		else
			cout<<"yes"<<endl;
	}

	return 0;
}
