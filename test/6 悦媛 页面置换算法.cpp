#include<iostream>
#include<stdlib.h>
#include<time.h>
#define INVALID -1
#define TRUE 1
#define FALSE 0

using namespace std;

struct page //页面控制块结构
{
	int page_number; //【状态位】页面的页号,用来记录该页面在内存中对应的页面号
	int hit;  //表示页面是否命中，即是否在内存中
	int counter;  //【访问位】表示页面的访问次数
	int time;  //表示页面被访问的时间
};

page pageone[32];

struct page_connect //页面链表
{
	int page_number;//页面的页号
	int hit;
	page_connect* next;
};

page_connect pagecon[32];
page_connect *free_head,*busy_head,*busy_tail;

int initialize(int);
int FIFO(int i);
int LRU(int i);
int OPT(int i);
int NRU(int i);

int arr[320];//arr数组用来存指令
int pagetotal[320];  //pagetotal数组用来存每条指令对应的页面
int pageoffset[320];  //pageoffset数组用来存每条指令对应的偏移量

int main()
{
	srand(unsigned(time(NULL))); //以时间作为随机数种子
	int k=rand()%320;  //获取随机数  0-319
	
	for(int i=0;i<320;i+=4)//产生0-319条指令
	{
		arr[i]=k;
		arr[i+1]=arr[i]+1;
		arr[i+2]=rand()%arr[i+1];
		arr[i+3]=arr[i+2]+1;
		int a=319-arr[i+3]-1;
		k=rand()%a+arr[i+3]+1;
	}
	
	//10个一个页面
	for(int i=0;i<320;i++)//将指令序列变成页地址流
	{    
		pagetotal[i]=arr[i]/10;  //得到每条指令对应的页面号
		pageoffset[i]=arr[i]%10;  //每条指令的偏移量
	}
	
	for(int i=0;i<320;i++)
		cout<<arr[i]<<" "<<pagetotal[i]<<" "<<pageoffset[i]<<endl;
	cout<<"-----------------END----------------------\n\n";
	
	for(int i=4;i<32;i++)//i表示内存空间可放的的页面数
	{
		cout<<"page frame="<<i;
		FIFO(i);
// 		LRU(i);
// 		OPT(i);
// 		NRU(i);
	}
	
	/*for(int i=0;i<320;i++)
		int k=pagenum[i];
		for(int j=0;j<n;j++)
		   if(pageone[j].page_number==k&&pageone[j].hit==1)
			   count++;
		   else if(pageone[j].hit==0)
			 {  pageone[j].hit=1;
		pageone[j].page_number=k;}
		return 0;*/
}

int initialize(int pagenum)//初始化i页面
{
	int i;
	for(i=0;i<32;i++) //初始化所有32个页面
	{
		pageone[i].page_number=INVALID; //赋值页面号，INVALID表示页面无效，即不在内存中
		pageone[i].counter=0; //页面的访问次数为0
		pageone[i].time=-1;  //设置页面访问时间
	}

	for(i=0;i<pagenum-1;i++) //创建内存中页面pagecon[i]和pagecon[i+1]之间的连接,组成一个页面队列
	{
		pagecon[i].page_number=i; //设置页面pagecon[i]的页面号为i
		pagecon[i].next=&pagecon[i+1];//页面i指向页面i+1
	}

	pagecon[pagenum-1].next=NULL;  //将最后一个页面的next指针指向空
	pagecon[pagenum-1].page_number=pagenum-1; //设置页面最后一个页面的页面号为pagenum-1
	free_head=&pagecon[0]; //开始都在空闲页面队列中
	return 0;
}

int FIFO(int pagenum)//先进先出页面置换算法，内存中有pagenum个页面
{
	int count=0;//count计算页面失效的次数
	page_connect *p; //指针
	initialize(pagenum); //初始化页面和内存页面
	busy_head=busy_tail=NULL; //内存页面的指针，都指向空
	for(int i=0;i<320;i++)
	{	if(pageone[pagetotal[i]].page_number==INVALID)//i指令对应的页面失效,即页面不在内存中
		{	count++; //失效次数加1
	        if(free_head==NULL)//当无空闲页面时
			{
				p=busy_head->next;//p指针指向头指针的下一个页面，用于记录下一个头节点
				pageone[busy_head->hit].page_number=INVALID;//将头指针指向的页面置为无效
				free_head=busy_head;//释放了第一个页面，将空闲指针指向它
				free_head->next=NULL; //除了free指针所指，再无空闲页面
				busy_head=p;//busy_head指针指向其下一个页面
			}
			p=free_head->next;//当前存在空闲页面，将p指针指向下一个空闲页面
			free_head->hit=pagetotal[i];
			pagecon[pagetotal[i]].page_number=free_head->page_number;
			free_head->next=NULL;
			if(busy_tail==NULL)//当页面都空闲的时候
				busy_tail=busy_head=free_head;//将三个指针都指向空闲页面，即第一个空闲页面
			else
			{
				busy_tail->next=free_head;
				busy_tail=free_head;
			}
			free_head=p;
	    }
	}
	cout<<"FIFO hit rate="<<1-(double)count/320<<endl;//输出命中率
	return 0;
}

int LRU(int pagenum)//最近最少使用算法。主要根据页面最近使用的时间来替换页面。替换掉时间最小的
{
	int count=0;//count计算页面失效的次数
	int min,min_index,present_time;//min用来记录内页面中最小的time值，min_index记录min页面的下标
	initialize(pagenum);
	present_time=0;
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//页面失效，即页面不在内存中
		{
			count++; //失效次数加1
			if(free_head==NULL) //如果当前没有空闲页面
			{
				min=10000; //设置最大的时间为10000
				for(int j=0;j<32;j++) //对每一个页面，循环检测，找出时间值最小的页面
				{
					if(min>pageone[j].time&&pageone[j].page_number!=INVALID)//判断内存中的页面的最近使用时间
					{
						min=pageone[j].time;
						min_index=j;//保留最小页面的下标
					}
					free_head=&pagecon[pageone[min_index].page_number];//将空间指针指向时间最小的内存页面
					pageone[min_index].page_number=INVALID;//将该下标对应的页面号设置为无效
					pageone[min_index].time=0;//把该页面时间设置为0
					free_head->next=NULL; //空间指针的next指向空
				}
				pageone[pagetotal[i]].page_number=free_head->page_number;//将i指令对应的页面的页面号置为有效
				pageone[pagetotal[i]].time=present_time;
				free_head=free_head->next; //指向空间页面的指针指向下一位
			}
		}
		else  //找到空间页面
		{
			pageone[pagetotal[i]].time=present_time;//设置改页面的时间为当前时间
			present_time++;
		}
	}
	cout<<"LRU hit rate="<<1-(double)count/320<<endl;//输出命中率
	return 0;
}

int OPT(int pagenum)  //最佳淘汰算法（OPT），先淘汰最不常用的页地址，即淘汰最远将来要用到的页面
{
	int count=0; //计算失效次数
	int max,max_page; //记录最远将来要用的页面
	int des,dest[32]; //存每个页面未来要用的时间
	page_connect *p;
	initialize(pagenum);
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//页面失效
		{
			count++; //失效次数加1
			if(free_head==NULL) //找不到空闲页面
			{
				for(int j=0;j<32;j++)
				{	if(pageone[j].page_number!=INVALID)//判断页面是否在内存中
						dest[j]=10000; //在内存中，给页面j对应的dest[j]赋值10000
					else
						dest[j]=0; //不在内存中，赋值为0
				}
				for(int k=0;k<32;k++)
				{
					if((pageone[k].page_number!=INVALID)&&(dest[k]==10000)) //对于在内存中的页面，赋值上页面序号
						dest[k]=k;
				}
				max=0;
				for(int j=0;i<32;j++)
				{	
					if(max<dest[j])//比较，找出所有在内存的页面中最远将来要用到的，即页面序号最大的页面
					{
						max=dest[j]; //找到最远的页面
						max_page=j;  //找到最远页面的下标
					}
					free_head=&pagecon[pageone[max_page].page_number]; //将空闲指针指向最远将来要用的页面上
				}
			}
			pageone[pagetotal[i]].page_number=free_head->page_number;//将该内存页面号赋值给为当前页面
			free_head=free_head->next; //空闲指针指向下一页
		}
	}
	cout<<"OPT hit rate="<<1-(double)count/320<<endl;//输出命中率
	return 0;
}

int NRU(int pagenum) //最近未使用页面算法
{
	int count=0;//计算失效次数
	int day,flag,old_day;//day用来跟踪页面的count位
	page_connect *p; //指针

	initialize(pagenum);//初始化

	day=0;
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//i所在的页面不在内存中
		{
			count++; //失效次数加1
			if(free_head==NULL) //内存空闲队列空
			{
				flag=TRUE; //flag位设置为1
				old_day=day;

				while(flag) 
				{
					if(pageone[day].counter==0 && pageone[day].page_number!=INVALID)//页面在内存中且【访问位】为0
						flag=FALSE; //将要替换该页面

					else
					{
						day++; //day前移
						if(day==32)//day遍历完所有页面，从头开始
							day=0;
						if(day==old_day) //所有访问位置0
							for(int j=0;j<32;j++)
								pageone[j].counter=0;
					}
				}
				free_head=&pagecon[pageone[day].page_number];//空闲head指针指向day指令对应的内存页面的页面
				pageone[day].page_number=INVALID;//pageone[day]移出内存
				free_head->next=NULL;
			}

			//else free_head!=NULL

			pageone[pagetotal[i]].page_number=free_head->page_number;//当有空闲页面，替换掉这个空闲页面
			free_head->hit=pagetotal[i];//空闲指针的hit位保存i指令对应的页面
			free_head=free_head->next;
		}

		else//页面未失效，在内存页面中可以找到
			pageone[pagetotal[i]].counter=1;//将其counter值设置为1

		if(i%50==0)//i每过50，就将每个页面的counter值置为0，周期性清零
			for(int j=0;j<32;j++)
				pageone[j].counter=0;
	}
	cout<<" , NRU hit rate="<<1-(double)count/320<<endl;
	return 0;
}
