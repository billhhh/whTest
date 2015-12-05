#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <pthread.h>
#include <cstring>
#include <Windows.h>

#define CLK_TCK CLOCKS_PER_SEC
#define M 2

#define MAX 10

using namespace std;

pthread_t thread[2];
pthread_mutex_t mut;

int number=0,i;

int omp_get_num_threads();
double start_time,end_time,start_time_0,end_time_0;                        //M是度，

typedef struct btree_node
{
    int k[2*M-1];                    //关键字向量    都是从0开始
    struct btree_node *p[2*M];       //子树指针向量    指针比关键字多1
    int num;              //节点中关键字个数
    bool is_leaf;          //判断是否是叶子
} btree_node;     //没有指向双亲结点的，记录指针向量


typedef struct find_node
{
    int num;
    int tag;
    btree_node *pt;    //指向找到的结点
    //int position;    //结点地址
}find_node;



btree_node *btree_node_new();      //声明

btree_node *btree_create();

int btree_split_child(btree_node *parent, int pos, btree_node *child);

void btree_insert_nonfull(btree_node *node, int target);

btree_node* btree_insert(btree_node *root, int target);

void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);

btree_node *btree_delete(btree_node *root, int target);

void btree_delete_nonone(btree_node *root, int target);

int btree_search_predecessor(btree_node *root);

int btree_search_successor(btree_node *root);

void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);

void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);

void btree_inorder_print(btree_node *root);

void btree_level_display(btree_node *root);


//创建b树
btree_node *btree_node_new()
{
	int i;
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(node==NULL)
	{
        return NULL;
    }

    for(i=0;i<2*M-1;i++)              //初始化key
	{
        node->k[i] = 0;
    }

    for(i=0;i<2*M;i++)            //初始化pointer
	{
        node->p[i] = NULL;
    }

    node->num = 0;
    node->is_leaf = true;                         //默认为叶子
}


btree_node *btree_create()                      //??????
{
    btree_node *node = btree_node_new();
    if(node==NULL)
	{
        return NULL;
    }

    return node;
}


//插入结点

//分裂          pos是指向孩子的该放的指针顺序
int btree_split_child(btree_node *parent, int pos, btree_node *child)     // 当child满时，将其进行分裂，child = parent->p[pos]
{
	int i;
    btree_node *new_child = btree_node_new();
    if(new_child==NULL)
	{
        return -1;
    }

	//new_child是分裂后新的 child
    new_child->is_leaf = child->is_leaf;             // 新节点的is_leaf与child相同
    new_child->num = M - 1;                          //新的孩子，是一半，新老各M-1

    for(i=0;i<M-1;i++)                          // 将child后半部分的key拷贝给新节点
	{
        new_child->k[i] = child->k[M+i];
    }

    if((new_child->is_leaf)==false)                   // 如果child不是叶子，还需要把指针拷过去，指针比节点多1
    {
        for(i=0;i<M;i++)
		{
            new_child->p[i]=child->p[M+i];
        }
    }

    child->num = M - 1;                             //原来的child

    for(i=parent->num;i>pos;i--)
	{
        parent->p[i+1] = parent->p[i];                    //空出指针位置
    }
    parent->p[pos+1] = new_child;

	//下面是对parent
    for(i=parent->num- 1; i>= pos; i--)        // child的中间节点需要插入parent的pos处，更新parent的key和pointer
    {
		parent->k[i+1] = parent->k[i];
    }
    parent->k[pos] = child->k[M-1];                     //空出k的位置

    parent->num += 1;
}


//target 是要插入的值
void btree_insert_nonfull(btree_node *node, int target)
{
    if(1==node->is_leaf)                         //是叶子           不用判断是否需要分裂，因为已经优化过了    都能直接插入
	{
        int pos = node->num;
        while(pos >=1 && target < node->k[pos-1])     //从后往前
		{
            node->k[pos] = node->k[pos-1];
            pos--;                                       //pos的值也在改变，找到该放的值
        }

        node->k[pos] = target;
        node->num += 1;

    }
	else                                              //不是叶子
	{
        int pos = node->num;
        while(pos>0 && target < node->k[pos-1])
		{
            pos--;
        }

        if(node->p[pos]->num==2*M-1)              //满了
		{
			btree_split_child(node, pos, node->p[pos]);    //从上往下调
			if(target > node->k[pos])                      //  下一个子节点
			{
				pos++;
			}
		}

        btree_insert_nonfull(node->p[pos], target);                   //   只能在叶子的时候才插入
    }
}

//总的插入    root是要插入的结构体
btree_node* btree_insert(btree_node *root, int target)
{
    if(root==NULL)
	{
        return NULL;
    }

    if(root->num==2*M-1)                 //根节点已经满了    必须新创建一个结构体   没满的话，结构体够放（数组够）
	{
		btree_node *node = btree_node_new();           //关键字已经初始化为0
		if(node==NULL)
		{
			return root;
		}

        node->is_leaf = 0;
        node->p[0] = root;
        btree_split_child(node, 0, root);         //满了先进行分裂   优化
        btree_insert_nonfull(node, target);        //调用上面的
        return node;
    }
	else
	{
        btree_insert_nonfull(root, target);
        return root;
    }
}

//搜索

find_node *find_node_new()
{
    find_node *fnode=(find_node *)malloc(sizeof(find_node));
    if(fnode==NULL)
    return NULL;
    fnode->num=0;
    fnode->pt=NULL;
    //fnode->position=0;
    fnode->tag=0;
}


find_node *find_node_create()
{
    find_node *fnode=find_node_create();
    if(fnode==NULL)
    {
       return NULL;
    }
    return fnode;
}




int btree_search(btree_node *root,int target, find_node *fnode)
{
	int i,j;
   // find_node *fnode=find_node_new();      不需要创建新的结点
	if(root==NULL)
    {
     //  if(!fnode->num)
    //   printf("%d没有搜索结果\n",target);
       return  fnode->num;     //怎样返回上一个函数？？？？？？？？？？？？？？？
    }
    j=0;
	for(i=0;i<root->num;i++)
	{
		if(target==root->k[i])  //找到了
		{
            fnode->num=fnode->num+1;    //个数
            fnode->pt=root;
            fnode->tag=i;
            //return fnode;
          //  printf("搜索成功,第%d个%d所在位置为节点%X的第%d个\n,", fnode->num, target, fnode->pt, fnode->tag);
            /*
            //继续搜索
		    for(j=i+1;j<root->num;j++)
		    {
		        if(target==root->k[j])
		        {
                fnode->num=fnode->num+1;
                fnode->pt=root;
                fnode->tag=j;
                //return fnode;
                printf("搜索成功,第%d个%d所在位置为节点%X的第%d个\n,", fnode->num, target, fnode->pt, fnode->tag);
                }
			}*/
			btree_search(root->p[i],target,fnode);
			/*
			else if(j<root->num)
			{
			//printf("搜索完毕\n");
			return ;
			}*/
        }
		else if(target<root->k[i])     //去左节点
		{
		    if(fnode->num!=0)
            break;
            btree_search(root->p[i],target,fnode);
        }
	   //大于的话继续比 i++
	}
    btree_search(root->p[i],target,fnode);
}

void btree_search_num(btree_node *root,int target, find_node *fnode)
{
	int i;
   	if(root==NULL)
    {
       if(!fnode->num)
       {
           printf("%d没有搜索结果\n",target);
       }
     //printf("return\n");
       return  ;     //怎样返回上一个函数？？？？？？？？？？？？？？？
    }
    for(i=0;i<root->num;i++)
    {
        if(target==root->k[i])  //找到了
        {
            fnode->num=fnode->num+1;    //个数
            fnode->pt=root;
            fnode->tag=i;
          //  printf("查找成功，%d所在位置为节点%X的第%d个,查找时间为%fms\n,", target, fnode->pt, fnode->tag);
            btree_search_num(root->p[i],target,fnode);
        }
        if(target<root->k[i]) //去左节点
        {
             if(fnode->num!=0)
             break;
             btree_search_num(root->p[i],target,fnode);
        }
    }
     btree_search_num(root->p[i],target,fnode);       //全都左右左右就行了
}


//删除
//合并y、z，k[pos]下降为y的中间节点，2（3）
void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
	y->num = 2 * M - 1;                               // 将z中节点拷贝到y的后半部分
	for(int i = M; i < 2 * M - 1; i++)
	{
		y->k[i] = z->k[i-M];
	}
	y->k[M-1] = root->k[pos];

	if(false == z->is_leaf)                          // 如果z非叶子，需要拷贝pointer
	{
		for(int i = M; i < 2 * M; i++) {
			y->p[i] = z->p[i-M];
		}
	}

	for(int j = pos + 1; j < root->num; j++)          // k[pos]下降到y中，更新原来k[pos]所在的key和pointer
	{
		root->k[j-1] = root->k[j];
		root->p[j] = root->p[j+1];
	}

	root->num -= 1;
	free(z);
}


btree_node *btree_delete(btree_node *root, int target)     // 特殊处理，当根只有两个子女，切两个子女的关键字个数都为M-1时，合并根与两个子女
                                                            // 这是唯一能降低树高的情形
{
	if(1 == root->num)
	{
		btree_node *y = root->p[0];
		btree_node *z = root->p[1];
		if(NULL != y && NULL != z &&
				M - 1 == y->num && M - 1 == z->num)
		{
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;
		}
		else
		{
			btree_delete_nonone(root, target);
			return root;
		}
	}
	else
	{
		btree_delete_nonone(root, target);
		return root;
	}
}

void btree_delete_nonone(btree_node *root, int target)
{
	if(true == root->is_leaf)
	{
		int i = 0;
		while(i < root->num && target > root->k[i]) i++;
		if(target == root->k[i])
		{
			for(int j = i + 1; j < 2 * M - 1; j++)
			{
				root->k[j-1] = root->k[j];
			}
			root->num -= 1;
		}
		else
		{
			printf("target not found\n");
		}
	}
	else
	{
		int i = 0;
		btree_node *y = NULL, *z = NULL;
		while(i < root->num && target > root->k[i]) i++;
		if(i < root->num && target == root->k[i])
		{
			y = root->p[i];
			z = root->p[i+1];
			if(y->num > M - 1)
			{
				int pre = btree_search_predecessor(y);
				root->k[i] = pre;
				btree_delete_nonone(y, pre);
			}
			else
				if(z->num > M - 1)
				{
					int next = btree_search_successor(z);
					root->k[i] = next;
					btree_delete_nonone(z, next);
				}
			else
			{
				btree_merge_child(root, i, y, z);
				btree_delete(y, target);
			}
		}
		else
		{
			y = root->p[i];
			if(i < root->num) {
				z = root->p[i+1];
			}
			btree_node *p = NULL;
			if(i > 0) {
				p = root->p[i-1];
			}

			if(y->num == M - 1) {
				if(i > 0 && p->num > M - 1) {
					btree_shift_to_right_child(root, i-1, p, y);
				} else if(i < root->num && z->num > M - 1) {
					btree_shift_to_left_child(root, i, y, z);
				} else if(i > 0) {
					btree_merge_child(root, i-1, p, y); // note
					y = p;
				} else {
					btree_merge_child(root, i, y, z);
				}
				btree_delete_nonone(y, target);
			} else {
				btree_delete_nonone(y, target);
			}
		}

	}
}

//寻找rightmost，以root为根的最大关键字    一直y = y->p[y->num];知道找到叶子，叶子的才是最接近的，最大的
int btree_search_predecessor(btree_node *root)
{
	btree_node *y = root;
	while(false == y->is_leaf) {
		y = y->p[y->num];
	}
	return y->k[y->num-1];
}

// 寻找leftmost，以root为根的最小关键字
int btree_search_successor(btree_node *root)
{
	btree_node *z = root;
	while(false == z->is_leaf) {
		z = z->p[0];
	}
	return z->k[0];
}

 // z向y借节点，将root->k[pos]下降至z，将y的最大关键字上升至root的pos处 3（1）
void btree_shift_to_right_child(btree_node *root, int pos,
		btree_node *y, btree_node *z)
{
	z->num += 1;
	for(int i = z->num -1; i > 0; i--) {
		z->k[i] = z->k[i-1];
	}
	z->k[0]= root->k[pos];
	root->k[pos] = y->k[y->num-1];

	if(false == z->is_leaf) {
		for(int i = z->num; i > 0; i--) {
			z->p[i] = z->p[i-1];
		}
		z->p[0] = y->p[y->num];
	}

	y->num -= 1;
}

// y向借节点，将root->k[pos]下降至y，将z的最小关键字上升至root的pos处
void btree_shift_to_left_child(btree_node *root, int pos,
		btree_node *y, btree_node *z)
{
	y->num += 1;
	y->k[y->num-1] = root->k[pos];
	root->k[pos] = z->k[0];

	for(int j = 1; j < z->num; j++) {
		z->k[j-1] = z->k[j];
	}

	if(false == z->is_leaf) {
		y->p[y->num] = z->p[0];
		for(int j = 1; j <= z->num; j++) {
			z->p[j-1] = z->p[j];
		}
	}

	z->num -= 1;
}



void btree_inorder_print(btree_node *root)
{
    if(NULL != root) {
        btree_inorder_print(root->p[0]);
        for(int i = 0; i < root->num; i++) {
            printf("%d ", root->k[i]);
            btree_inorder_print(root->p[i+1]);
        }
    }
}

//btree xianshi
void btree_level_display(btree_node *root)
{
	int i;
	// 只能显示1000个结点
    btree_node *queue[500000] = {NULL};
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while(front < rear) {
        btree_node *node = queue[front++];

        printf("[");
        for( i = 0; i < node->num; i++) {
            printf("%d ", node->k[i]);                  //输出关键字
        }
        printf("]");

        for( i = 0; i <= node->num; i++) {
            if(NULL != node->p[i]) {
                queue[rear++] = node->p[i];                //转到子节点
            }
        }
    }
	printf("\n");
}


    btree_node *root = btree_create();
    find_node *fnode=find_node_new();
    int find_num[] = {10,23,100};

void *thread1(void*)
{
    printf("thread1 : I'm thread 1\n");
    for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d搜索个数为%d\n\n",find_num[i],fnode->num);
        printf("查找时间为%fms\n,", (end_time-start_time)/CLK_TCK*1000);

       pthread_mutex_lock(&mut);
                number++;
        pthread_mutex_unlock(&mut);
        Sleep(2);
    }
  /*  for(i = 0;i < MAX;i++)
    {
        printf("thread1 : number = %d\n",number);
        pthread_mutex_lock(&mut);
                number++;
        pthread_mutex_unlock(&mut);
        sleep(2);
    }*/
    printf("thread1 :main?\n");
    pthread_exit(NULL);

	return NULL;
}

void *thread2(void*)
{
    printf("thread2 : I'm thread 2\n");

        for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d搜索个数为%d\n\n",find_num[i],fnode->num);
        printf("查找时间为%fms\n,", (end_time-start_time)/CLK_TCK*1000);

       pthread_mutex_lock(&mut);
                number++;
        pthread_mutex_unlock(&mut);
        Sleep(3);
    }
  /*  for(i = 0;i < MAX;i++)
    {

        printf("thread2 : number = %d\n",number);
        pthread_mutex_lock(&mut);
                number++;
        pthread_mutex_unlock(&mut);
        sleep(3);
    }*/
    printf("thread2 :main?\n");
    pthread_exit(NULL);

	return NULL;
}

void thread_create(void)
{
    int temp;
    memset(&thread,0,sizeof(thread));

    if((temp = pthread_create(&thread[0],NULL,&thread1,NULL)) != 0)
         printf("thread1_create fail!\n");
    else
         printf("thread1_create success!\n");
    if((temp = pthread_create(&thread[1],NULL,&thread2,NULL)) != 0)
         printf("thread2_create fail!\n");
    else
         printf("thread2_create success!\n");
}


void thread_wait(void)
{
//    wait for the end of thread

    //if(thread[0] != 0)
    {
        pthread_join(thread[0],NULL);
        printf("thread1 already end\n ");
    }

    //if(thread[1] !=0)
    {
        pthread_join(thread[1],NULL);
        printf("thread2 already end\n ");
    }
}

int main()
{
	int i,j,x,num,all_num;
    //int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
    int arr[1024];

   // btree_node *root = btree_create();
    //find_node *fnode=find_node_new();

    FILE *fp;

    //打开文件
    if((fp=fopen("num2.txt", "r")) == NULL)
    {
        printf("cannot open this file\n");
        exit(0);
    }

    all_num = 0;
    num = 0;
    while( !feof(fp))
    {
        for( i = 0; i < 1024; i++)
        {
            if(!feof(fp))
            {
                fscanf(fp, "%d ", &arr[i]);
            //    printf("%d ", arr[i]);    //输出数据
                num = i + 1;
            }
        }
      //  printf("\n*************************%d\n", num);     //共有几个数据

     //   printf("***************************创建b树\n");
        for( i = 0; i < num ; i++)
        {
            root = btree_insert(root, arr[i]);
            //btree_level_display(root);
        }
        //btree_level_display(root);
        all_num = all_num + num;
    }
    printf("\n%d\n", all_num);     //总共有几个数据
    fclose(fp);


 /*   printf("\n删除测试\n");
	//int todel[] = {15, 18, 23, 30, 31, 52, 50};     //要删除的数    删除有问题～～重复的只能删除一个
	int todel[] = {52,1612,1432};
	for( i = 0; i < sizeof(todel) / sizeof(int); i++)
	{
		find_node *fnode=find_node_new();
        btree_search_num(root, todel[i],fnode);
        printf("查找到%d个%d\n,",fnode->num,todel[i]);
    	printf("删除%d之后\n", todel[i]);
     	for(j=0;j<fnode->num;j++)
		{
		   root = btree_delete(root, todel[i]);
		   printf("delete\n");
        }
	//	btree_level_display(root);
	}
	//btree_level_display(root);

*/

    //搜索

    printf("\n搜索\n");
  //  int find_num[] = {15, 18, 23, 30};
  //  int find_num[] = {52,640,2682,2892,2871};
    //int find_num[] = {10,23,100};
    printf("串行搜索 \n");
	start_time_0=clock();
	 for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d搜索个数为%d\n\n",find_num[i],fnode->num);
        printf("查找时间为%fms\n,", (end_time-start_time)/CLK_TCK*1000);
    }
    end_time_0=clock();
    printf("总搜索时间为%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);

    printf("\n并行搜索 \n");
	start_time_0=clock();
   // #pragma omp parallel for

	/* for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d搜索个数为%d\n\n",find_num[i],fnode->num);
        printf("查找时间为%fms\n,", (end_time-start_time)/CLK_TCK*1000);
    }*/
  //  end_time_0=clock();
//    int t= omp_get_num_threads();
   // printf("xianchengshuwei:%d\n",t);

   // printf("kaishishijian:%fms\n",start_time_0);
   // printf("jieshushijian:%fms\n",end_time_0);
   // printf("总搜索时间为%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);

    pthread_mutex_init(&mut,NULL);
    printf("I'm the main,I'm building thread\n");
    thread_create();
    printf("I'm the main,I'm waiting for thread to finish mission\n");
    thread_wait();
        end_time_0=clock();
        printf("总搜索时间为%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);
    return 0;

}
