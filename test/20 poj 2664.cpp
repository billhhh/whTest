#include <iostream>
using namespace std;

int choice[102];  //Freddie's choice

int main()
{
	int k,m,c,r;
	int flag; //标记是否合格，必须存在，即使提前知道不合格，也需要把输入完毕
	int tempCourse; //保存每次必修输入课程号
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
			int count=0; //计数看看最后等不等于r
			for (int j=0;j<c;++j)
			{
				cin>>tempCourse;
				if (0 == flag)
					continue;
				
				//遍历学过的课程
				for (int it=0;it<k;++it)
				{
					if( choice[it]==tempCourse ){
						++count;
						break;
					}
				}
			}
			if(count<r) //代表已经不合格了
				flag=0;
		}
		if(flag == 0)
			cout<<"no"<<endl;

		else
			cout<<"yes"<<endl;
	}

	return 0;
}
