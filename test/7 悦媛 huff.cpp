#include<iostream>
#include <vector>

using namespace std;
const double eps = 1e-6;
vector<int > v;

struct huff
{
	double value;
	huff* left;
	huff* child_l;
	huff* child_r;
	int i;
	bool is_leaf;
	bool visit;
}*q;

huff *p;

void find(huff *p)
{
	v.clear();

	while(p->left != NULL)
	{
		v.push_back(p->i);
		p = p->left; 
	}

	//output
	for (int i=v.size()-1;i>=0;--i)
	{
		cout<<v.at(i);
	}
}

void init(int n)
{
	for (int i=0;i<n;i++)
		p[i].is_leaf = true;

	//初始化不是leaf的
	for (int i=n;i<2*n-1;i++)
		p[i].is_leaf=false;

	//初始化所有child
	for (int i=0;i<2*n-1; ++i)
	{
		p[i].child_l = NULL;
		p[i].child_r = NULL;
		p[i].visit = false;
	}
}

//[lb,rb]范围排序
void my_sort(int lb,int rb)
{
	huff tmp;
	for (int i=lb;i<rb;i++)
	{
		for (int j=i;j<=rb;j++)
		{
			if (p[i].value>p[j].value)
			{
				//交换
				tmp=p[i];
				p[i]=p[j];
				p[j]=tmp;

				//同时他们的孩子的left也要交换
				if(p[i].child_l != NULL)
					p[i].child_l->left = p[i].child_r->left = &p[i];
				if(p[j].child_l != NULL)
					p[j].child_l->left = p[j].child_r->left = &p[j];
			}
		}
	}
}

int main()
{
	//freopen("input.txt","r",stdin);

	int n;
	cin>>n;

	p=new huff[2*n-1];//分配huff数组
	double ori_arr[25];

	init(n);

	for(int i=0;i<n;i++)
	{
		cin>>p[i].value; //输入
		ori_arr[i] = p[i].value;
	}

	int k=0;
	//cout<<"i == "<<i<<endl;
	for(int i=0;i<n-1;i++,k+=2) 
	{
		my_sort(k,n+i-1); //从小到大排序

		p[i+n].value=p[k].value+p[k+1].value;
		p[k].i=0;
		p[k+1].i=1;
		p[k].left=p[k+1].left=&p[i+n];
		p[i+n].child_l=&p[k];
		p[i+n].child_r=&p[k+1];
		//cout<<"old: "<<k<<"->"<<k+1<<"->"<<i+n<<"\n";
	}

	p[n*2-2].left=NULL;
	p[n*2-2].i=1;

// 	for(int j=0;j<2*n-1;j++)
// 		cout<<p[j].i<<endl;

	for(int t=0;t<n;t++)
	{
		for (int h=0;h<2*n-1;++h)
		{
			if( p[h].is_leaf == true && p[h].visit == false && p[h].value == ori_arr[t] )
			{
				q=&p[h]; //q是代表各个叶子节点
				find(q);
				cout<<endl;
				p[h].visit = true;

				break;
			}
		}
	}

	return 0;
}
