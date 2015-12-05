#include<iostream>
#include<stdlib.h>
#include<time.h>
#define INVALID -1
#define TRUE 1
#define FALSE 0

using namespace std;

struct page //ҳ����ƿ�ṹ
{
	int page_number; //��״̬λ��ҳ���ҳ��,������¼��ҳ�����ڴ��ж�Ӧ��ҳ���
	int hit;  //��ʾҳ���Ƿ����У����Ƿ����ڴ���
	int counter;  //������λ����ʾҳ��ķ��ʴ���
	int time;  //��ʾҳ�汻���ʵ�ʱ��
};

page pageone[32];

struct page_connect //ҳ������
{
	int page_number;//ҳ���ҳ��
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

int arr[320];//arr����������ָ��
int pagetotal[320];  //pagetotal����������ÿ��ָ���Ӧ��ҳ��
int pageoffset[320];  //pageoffset����������ÿ��ָ���Ӧ��ƫ����

int main()
{
	srand(unsigned(time(NULL))); //��ʱ����Ϊ���������
	int k=rand()%320;  //��ȡ�����  0-319
	
	for(int i=0;i<320;i+=4)//����0-319��ָ��
	{
		arr[i]=k;
		arr[i+1]=arr[i]+1;
		arr[i+2]=rand()%arr[i+1];
		arr[i+3]=arr[i+2]+1;
		int a=319-arr[i+3]-1;
		k=rand()%a+arr[i+3]+1;
	}
	
	//10��һ��ҳ��
	for(int i=0;i<320;i++)//��ָ�����б��ҳ��ַ��
	{    
		pagetotal[i]=arr[i]/10;  //�õ�ÿ��ָ���Ӧ��ҳ���
		pageoffset[i]=arr[i]%10;  //ÿ��ָ���ƫ����
	}
	
	for(int i=0;i<320;i++)
		cout<<arr[i]<<" "<<pagetotal[i]<<" "<<pageoffset[i]<<endl;
	cout<<"-----------------END----------------------\n\n";
	
	for(int i=4;i<32;i++)//i��ʾ�ڴ�ռ�ɷŵĵ�ҳ����
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

int initialize(int pagenum)//��ʼ��iҳ��
{
	int i;
	for(i=0;i<32;i++) //��ʼ������32��ҳ��
	{
		pageone[i].page_number=INVALID; //��ֵҳ��ţ�INVALID��ʾҳ����Ч���������ڴ���
		pageone[i].counter=0; //ҳ��ķ��ʴ���Ϊ0
		pageone[i].time=-1;  //����ҳ�����ʱ��
	}

	for(i=0;i<pagenum-1;i++) //�����ڴ���ҳ��pagecon[i]��pagecon[i+1]֮�������,���һ��ҳ�����
	{
		pagecon[i].page_number=i; //����ҳ��pagecon[i]��ҳ���Ϊi
		pagecon[i].next=&pagecon[i+1];//ҳ��iָ��ҳ��i+1
	}

	pagecon[pagenum-1].next=NULL;  //�����һ��ҳ���nextָ��ָ���
	pagecon[pagenum-1].page_number=pagenum-1; //����ҳ�����һ��ҳ���ҳ���Ϊpagenum-1
	free_head=&pagecon[0]; //��ʼ���ڿ���ҳ�������
	return 0;
}

int FIFO(int pagenum)//�Ƚ��ȳ�ҳ���û��㷨���ڴ�����pagenum��ҳ��
{
	int count=0;//count����ҳ��ʧЧ�Ĵ���
	page_connect *p; //ָ��
	initialize(pagenum); //��ʼ��ҳ����ڴ�ҳ��
	busy_head=busy_tail=NULL; //�ڴ�ҳ���ָ�룬��ָ���
	for(int i=0;i<320;i++)
	{	if(pageone[pagetotal[i]].page_number==INVALID)//iָ���Ӧ��ҳ��ʧЧ,��ҳ�治���ڴ���
		{	count++; //ʧЧ������1
	        if(free_head==NULL)//���޿���ҳ��ʱ
			{
				p=busy_head->next;//pָ��ָ��ͷָ�����һ��ҳ�棬���ڼ�¼��һ��ͷ�ڵ�
				pageone[busy_head->hit].page_number=INVALID;//��ͷָ��ָ���ҳ����Ϊ��Ч
				free_head=busy_head;//�ͷ��˵�һ��ҳ�棬������ָ��ָ����
				free_head->next=NULL; //����freeָ����ָ�����޿���ҳ��
				busy_head=p;//busy_headָ��ָ������һ��ҳ��
			}
			p=free_head->next;//��ǰ���ڿ���ҳ�棬��pָ��ָ����һ������ҳ��
			free_head->hit=pagetotal[i];
			pagecon[pagetotal[i]].page_number=free_head->page_number;
			free_head->next=NULL;
			if(busy_tail==NULL)//��ҳ�涼���е�ʱ��
				busy_tail=busy_head=free_head;//������ָ�붼ָ�����ҳ�棬����һ������ҳ��
			else
			{
				busy_tail->next=free_head;
				busy_tail=free_head;
			}
			free_head=p;
	    }
	}
	cout<<"FIFO hit rate="<<1-(double)count/320<<endl;//���������
	return 0;
}

int LRU(int pagenum)//�������ʹ���㷨����Ҫ����ҳ�����ʹ�õ�ʱ�����滻ҳ�档�滻��ʱ����С��
{
	int count=0;//count����ҳ��ʧЧ�Ĵ���
	int min,min_index,present_time;//min������¼��ҳ������С��timeֵ��min_index��¼minҳ����±�
	initialize(pagenum);
	present_time=0;
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//ҳ��ʧЧ����ҳ�治���ڴ���
		{
			count++; //ʧЧ������1
			if(free_head==NULL) //�����ǰû�п���ҳ��
			{
				min=10000; //��������ʱ��Ϊ10000
				for(int j=0;j<32;j++) //��ÿһ��ҳ�棬ѭ����⣬�ҳ�ʱ��ֵ��С��ҳ��
				{
					if(min>pageone[j].time&&pageone[j].page_number!=INVALID)//�ж��ڴ��е�ҳ������ʹ��ʱ��
					{
						min=pageone[j].time;
						min_index=j;//������Сҳ����±�
					}
					free_head=&pagecon[pageone[min_index].page_number];//���ռ�ָ��ָ��ʱ����С���ڴ�ҳ��
					pageone[min_index].page_number=INVALID;//�����±��Ӧ��ҳ�������Ϊ��Ч
					pageone[min_index].time=0;//�Ѹ�ҳ��ʱ������Ϊ0
					free_head->next=NULL; //�ռ�ָ���nextָ���
				}
				pageone[pagetotal[i]].page_number=free_head->page_number;//��iָ���Ӧ��ҳ���ҳ�����Ϊ��Ч
				pageone[pagetotal[i]].time=present_time;
				free_head=free_head->next; //ָ��ռ�ҳ���ָ��ָ����һλ
			}
		}
		else  //�ҵ��ռ�ҳ��
		{
			pageone[pagetotal[i]].time=present_time;//���ø�ҳ���ʱ��Ϊ��ǰʱ��
			present_time++;
		}
	}
	cout<<"LRU hit rate="<<1-(double)count/320<<endl;//���������
	return 0;
}

int OPT(int pagenum)  //�����̭�㷨��OPT��������̭����õ�ҳ��ַ������̭��Զ����Ҫ�õ���ҳ��
{
	int count=0; //����ʧЧ����
	int max,max_page; //��¼��Զ����Ҫ�õ�ҳ��
	int des,dest[32]; //��ÿ��ҳ��δ��Ҫ�õ�ʱ��
	page_connect *p;
	initialize(pagenum);
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//ҳ��ʧЧ
		{
			count++; //ʧЧ������1
			if(free_head==NULL) //�Ҳ�������ҳ��
			{
				for(int j=0;j<32;j++)
				{	if(pageone[j].page_number!=INVALID)//�ж�ҳ���Ƿ����ڴ���
						dest[j]=10000; //���ڴ��У���ҳ��j��Ӧ��dest[j]��ֵ10000
					else
						dest[j]=0; //�����ڴ��У���ֵΪ0
				}
				for(int k=0;k<32;k++)
				{
					if((pageone[k].page_number!=INVALID)&&(dest[k]==10000)) //�������ڴ��е�ҳ�棬��ֵ��ҳ�����
						dest[k]=k;
				}
				max=0;
				for(int j=0;i<32;j++)
				{	
					if(max<dest[j])//�Ƚϣ��ҳ��������ڴ��ҳ������Զ����Ҫ�õ��ģ���ҳ���������ҳ��
					{
						max=dest[j]; //�ҵ���Զ��ҳ��
						max_page=j;  //�ҵ���Զҳ����±�
					}
					free_head=&pagecon[pageone[max_page].page_number]; //������ָ��ָ����Զ����Ҫ�õ�ҳ����
				}
			}
			pageone[pagetotal[i]].page_number=free_head->page_number;//�����ڴ�ҳ��Ÿ�ֵ��Ϊ��ǰҳ��
			free_head=free_head->next; //����ָ��ָ����һҳ
		}
	}
	cout<<"OPT hit rate="<<1-(double)count/320<<endl;//���������
	return 0;
}

int NRU(int pagenum) //���δʹ��ҳ���㷨
{
	int count=0;//����ʧЧ����
	int day,flag,old_day;//day��������ҳ���countλ
	page_connect *p; //ָ��

	initialize(pagenum);//��ʼ��

	day=0;
	for(int i=0;i<320;i++)
	{
		if(pageone[pagetotal[i]].page_number==INVALID)//i���ڵ�ҳ�治���ڴ���
		{
			count++; //ʧЧ������1
			if(free_head==NULL) //�ڴ���ж��п�
			{
				flag=TRUE; //flagλ����Ϊ1
				old_day=day;

				while(flag) 
				{
					if(pageone[day].counter==0 && pageone[day].page_number!=INVALID)//ҳ�����ڴ����ҡ�����λ��Ϊ0
						flag=FALSE; //��Ҫ�滻��ҳ��

					else
					{
						day++; //dayǰ��
						if(day==32)//day����������ҳ�棬��ͷ��ʼ
							day=0;
						if(day==old_day) //���з���λ��0
							for(int j=0;j<32;j++)
								pageone[j].counter=0;
					}
				}
				free_head=&pagecon[pageone[day].page_number];//����headָ��ָ��dayָ���Ӧ���ڴ�ҳ���ҳ��
				pageone[day].page_number=INVALID;//pageone[day]�Ƴ��ڴ�
				free_head->next=NULL;
			}

			//else free_head!=NULL

			pageone[pagetotal[i]].page_number=free_head->page_number;//���п���ҳ�棬�滻���������ҳ��
			free_head->hit=pagetotal[i];//����ָ���hitλ����iָ���Ӧ��ҳ��
			free_head=free_head->next;
		}

		else//ҳ��δʧЧ�����ڴ�ҳ���п����ҵ�
			pageone[pagetotal[i]].counter=1;//����counterֵ����Ϊ1

		if(i%50==0)//iÿ��50���ͽ�ÿ��ҳ���counterֵ��Ϊ0������������
			for(int j=0;j<32;j++)
				pageone[j].counter=0;
	}
	cout<<" , NRU hit rate="<<1-(double)count/320<<endl;
	return 0;
}
