#define TRUE 1 
#define FALSE 0 
#define INVALID -1 
#define NULL  0 
#include<stdlib.h>
#include<stdio.h>
#define  total_instruction 320    
#define  total_vp  32             
#define  clear_period  50  

typedef struct   
{ 
	int pn;     int pfn;     int counter;  int time;   
}pl_type; 

pl_type pl[total_vp];                    
typedef struct pfc_struct             
{                           
	int pn; int pfn; 
	struct pfc_struct *next; 
}pfc_type;

pfc_type pfc[total_vp], *freepf_head, *busypf_head, *busypf_tail; 
int diseffect,  a[total_instruction];
int page[total_instruction],  offset[total_instruction];
int  initialize(int); int  FIFO(int); int  LRU(int); int  LFU(int); int  NUR(int);  
int  OPT(int); 

int main( ) 
{ 
	int s,i,j; 
	srand(10*getpid());                  
	s=(float)319*rand( )/32767/32767/2+1;  
	for(i=0;i<total_instruction;i+=4)        
	{ 
		if(s<0||s>319) 
		{ 
			printf("When i==%d,Error,s==%d\n",i,s); 
			exit(0); 
		}  
		a[i]=s; a[i+1]=a[i]+1;                              
		a[i+2]=(float)a[i]*rand( )/32767/32767/2; 
		a[i+3]=a[i+2]+1;  
		s=(float)(318-a[i+2])*rand( )/32767/32767/2+a[i+2]+2; 
		if((a[i+2]>318)||(s>319)) 
			printf("a[%d+2],a number which is :%d and s==%d",i,a[i+2],s);  
	} 
	for (i=0;i<total_instruction;i++) /*将指令序列变换成页地址流*/ 
	{ 
		page[i]=a[i]/10;  offset[i]=a[i]%10; 
	} 
	for(i=4;i<=32;i++)   /*用户内存工作区从4个页面到32个页面*/ 
	{ 
		printf("---%2d page frames---",i); 
		FIFO(i);  LRU(i);   LFU(i);   NUR(i);   OPT(i); 
	} 
	return 0; 
} 

int initialize(int total_pf)              
{ 
	int i; diseffect=0; 
	for(i=0;i<total_vp;i++) 
	{
		pl[i].pfn=INVALID;       /*置页面控制结构中的页号，页面为空*/ 
		pl[i].counter=0;         /*页面控制结构中的访问次数为0*/ 
		pl[i].time=-1;           /*访问的时间*/ 
	} 
	for(i=0;i<total_pf-1;i++)  /*建立pfc[i-1]和pfc[i]之间的链接*/ 
	{   
		pfc[i].next=&pfc[i+1];  pfc[i].pfn=i; 
	}    
	pfc[total_pf-1].next=NULL; 
	pfc[total_pf-1].pfn=total_pf-1; 
	freepf_head=&pfc[0];         /*空页面队列的头指针为pfc[0]*/ 
	return 0;
} 

int FIFO(int total_pf)              /*先进先出算法total_pf:用户进程的内存页面数*/ 
{ 
	int i,j; pfc_type *p;          /*中间变量*/ 
	initialize(total_pf);         /*初始化相关页面控制用数据结构*/ 
	busypf_head=busypf_tail=NULL; /*忙页面队列头，队列尾链接*/ 
	for(i=0;i<total_instruction;i++) 
	{ 
		if(pl[page[i]].pfn==INVALID)   /*页面失效*/ 
		{ 
			diseffect+=1;   if(freepf_head==NULL)      
			{ 
				p=busypf_head->next;        
				pl[busypf_head->pn].pfn=INVALID; 
				freepf_head=busypf_head;  /*释放忙页面队列的第一个页面*/ 
				freepf_head->next=NULL;  /*表明还是缺页*/ 
				busypf_head=p; 
			} 
			p=freepf_head->next;         
			freepf_head->pn=page[i]; 
			pl[page[i]].pfn=freepf_head->pfn; 
			freepf_head->next=NULL; /*使busy的尾为null*/ 
			if(busypf_tail==NULL) 
			{ busypf_tail=busypf_head=freepf_head;  } 
			else 
			{ 
				busypf_tail->next=freepf_head; 
				busypf_tail=freepf_head; 
			} 
			freepf_head=p; 
		} 
	} 
	printf("FIFO:%6.4f",1-(float)diseffect/320); return 0; 
}

int LRU (int total_pf)       /*最近最久未使用算法least recently used*/ 
{ 
	int min,minj,i,j,present_time; /*minj为最小值下标*/ 
	initialize(total_pf);  present_time=0; 
	for(i=0;i<total_instruction;i++) 
	{ 
		if(pl[page[i]].pfn==INVALID)             /*页面失效*/ 
		{ 
			diseffect++; if(freepf_head==NULL)              /*无空闲页面*/ 
			{ 
				min=32767;            /*设置最大值*/ 
				for(j=0;j<total_vp;j++)            /*找出time的最小值*/ 
				{  
					if(min>pl[j].time&&pl[j].pfn!=INVALID) 
					{min=pl[j].time; minj=j; } 
				} 
				freepf_head=&pfc[pl[minj].pfn];   //腾出一个单元 
				pl[minj].pfn=INVALID;  pl[minj].time=0; 
				freepf_head->next=NULL; 
			} 
			pl[page[i]].pfn=freepf_head->pfn;   //有空闲页面,改为有效 
			pl[page[i]].time=present_time; 
			freepf_head=freepf_head->next;      //减少一个free 页面 
		} 
		else 
		{ 
			pl[page[i]].time=present_time;  present_time++; 
		} 
	}
	printf("LRU:%6.4f",1-(float)diseffect/320); return 0; 
} 

int NUR(int  total_pf )                  /*最近未使用算法Not Used recently count表示*/ 
{  
	int i,j,dp,cont_flag,old_dp;pfc_type *t; 
	initialize(total_pf); dp=0; 
	for(i=0;i<total_instruction;i++) 
	{  
		if (pl[page[i]].pfn==INVALID)         /*页面失效*/ 
		{ 
			diseffect++;  if(freepf_head==NULL)               /*无空闲页面*/ 
			{  
				cont_flag=TRUE;  old_dp=dp; 
				while(cont_flag) 
				{
					if(pl[dp].counter==0&&pl[dp].pfn!=INVALID) cont_flag=FALSE; 
					else 
					{ 
						dp++; if(dp==total_vp) dp=0; 
						if(dp==old_dp) 
							for(j=0;j<total_vp;j++) 
								pl[j].counter=0; } 
				} 
				freepf_head=&pfc[pl[dp].pfn]; 
				pl[dp].pfn=INVALID; 
				freepf_head->next=NULL; 
			} 
			pl[page[i]].pfn=freepf_head->pfn;
			freepf_head->pn=page[i]; 
			freepf_head=freepf_head->next; 
		} 
		else 
			pl[page[i]].counter=1; 
		if(i%clear_period==0) 
			for(j=0;j<total_vp;j++) 
				pl[j].counter=0; 
	} 
	printf("NUR:%6.4f",1-(float)diseffect/320); 
	return 0;
}  

int OPT(int total_pf)       /*最佳置换算法*/ 
{ 
	int i,j, max,maxpage,d,dist[total_vp]; 
	pfc_type *t;  initialize(total_pf); 
	for(i=0;i<total_instruction;i++) 
	{  
		if(pl[page[i]].pfn==INVALID)      /*页面失效*/ 
		{  diseffect++; 
		if(freepf_head==NULL)         /*无空闲页面*/ 
		{ 
			for(j=0;j<total_vp;j++) 
			{ 
				if(pl[j].pfn!=INVALID) dist[j]=32767; 
				else  dist[j]=0;    
			} 
			for(j=0;j<total_vp;j++)         
			{ 
				if((pl[j].pfn!=INVALID)&&(dist[j]==32767)) 
				{ dist[j]=j;} 
			} 
			max=0; 
			for(j=0;j<total_vp;j++) 
				if(max<dist[j]) 
				{ max=dist[j]; maxpage=j; } 
				freepf_head=&pfc[pl[maxpage].pfn]; 
				freepf_head->next=NULL; 
				pl[maxpage].pfn=INVALID; 
		} 
		pl[page[i]].pfn=freepf_head->pfn; freepf_head=freepf_head->next; 
		}
	} 
	printf("OPT:%6.4f\n",1-(float)diseffect/320); 
	return 0; 
} 

int  LFU(int total_pf)         
{ 
	int i,j,min,minpage;  pfc_type *t;  initialize(total_pf); 
	for(i=0;i<total_instruction;i++) 
	{  
		if(pl[page[i]].pfn==INVALID)      /*页面失效*/ 
		{ diseffect++; 
		if(freepf_head==NULL)          /*无空闲页面*/ 
		{  
			min=32767;      
			for(j=0;j<total_vp;j++) 
			{ 
				if(min>pl[j].counter&&pl[j].pfn!=INVALID) 
				{  min=pl[j].counter; minpage=j; } 
			} 
			freepf_head=&pfc[pl[minpage].pfn]; 
			pl[minpage].pfn=INVALID;   pl[minpage].counter=0; 
			freepf_head->next=NULL; 
		} 
		pl[page[i]].pfn=freepf_head->pfn;   //有空闲页面,改为有效 
		pl[page[i]].counter++; 
		freepf_head=freepf_head->next;      //减少一个free 页面 
		} 
		else 
		{ pl[page[i]].counter; pl[page[i]].counter=pl[page[i]].counter+1; } 
	}  printf("LFU:%6.4f",1-(float)diseffect/320); return 0;
}