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
double start_time,end_time,start_time_0,end_time_0;                        //M�Ƕȣ�

typedef struct btree_node
{
    int k[2*M-1];                    //�ؼ�������    ���Ǵ�0��ʼ
    struct btree_node *p[2*M];       //����ָ������    ָ��ȹؼ��ֶ�1
    int num;              //�ڵ��йؼ��ָ���
    bool is_leaf;          //�ж��Ƿ���Ҷ��
} btree_node;     //û��ָ��˫�׽��ģ���¼ָ������


typedef struct find_node
{
    int num;
    int tag;
    btree_node *pt;    //ָ���ҵ��Ľ��
    //int position;    //����ַ
}find_node;



btree_node *btree_node_new();      //����

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


//����b��
btree_node *btree_node_new()
{
	int i;
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(node==NULL)
	{
        return NULL;
    }

    for(i=0;i<2*M-1;i++)              //��ʼ��key
	{
        node->k[i] = 0;
    }

    for(i=0;i<2*M;i++)            //��ʼ��pointer
	{
        node->p[i] = NULL;
    }

    node->num = 0;
    node->is_leaf = true;                         //Ĭ��ΪҶ��
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


//������

//����          pos��ָ���ӵĸ÷ŵ�ָ��˳��
int btree_split_child(btree_node *parent, int pos, btree_node *child)     // ��child��ʱ��������з��ѣ�child = parent->p[pos]
{
	int i;
    btree_node *new_child = btree_node_new();
    if(new_child==NULL)
	{
        return -1;
    }

	//new_child�Ƿ��Ѻ��µ� child
    new_child->is_leaf = child->is_leaf;             // �½ڵ��is_leaf��child��ͬ
    new_child->num = M - 1;                          //�µĺ��ӣ���һ�룬���ϸ�M-1

    for(i=0;i<M-1;i++)                          // ��child��벿�ֵ�key�������½ڵ�
	{
        new_child->k[i] = child->k[M+i];
    }

    if((new_child->is_leaf)==false)                   // ���child����Ҷ�ӣ�����Ҫ��ָ�뿽��ȥ��ָ��Ƚڵ��1
    {
        for(i=0;i<M;i++)
		{
            new_child->p[i]=child->p[M+i];
        }
    }

    child->num = M - 1;                             //ԭ����child

    for(i=parent->num;i>pos;i--)
	{
        parent->p[i+1] = parent->p[i];                    //�ճ�ָ��λ��
    }
    parent->p[pos+1] = new_child;

	//�����Ƕ�parent
    for(i=parent->num- 1; i>= pos; i--)        // child���м�ڵ���Ҫ����parent��pos��������parent��key��pointer
    {
		parent->k[i+1] = parent->k[i];
    }
    parent->k[pos] = child->k[M-1];                     //�ճ�k��λ��

    parent->num += 1;
}


//target ��Ҫ�����ֵ
void btree_insert_nonfull(btree_node *node, int target)
{
    if(1==node->is_leaf)                         //��Ҷ��           �����ж��Ƿ���Ҫ���ѣ���Ϊ�Ѿ��Ż�����    ����ֱ�Ӳ���
	{
        int pos = node->num;
        while(pos >=1 && target < node->k[pos-1])     //�Ӻ���ǰ
		{
            node->k[pos] = node->k[pos-1];
            pos--;                                       //pos��ֵҲ�ڸı䣬�ҵ��÷ŵ�ֵ
        }

        node->k[pos] = target;
        node->num += 1;

    }
	else                                              //����Ҷ��
	{
        int pos = node->num;
        while(pos>0 && target < node->k[pos-1])
		{
            pos--;
        }

        if(node->p[pos]->num==2*M-1)              //����
		{
			btree_split_child(node, pos, node->p[pos]);    //�������µ�
			if(target > node->k[pos])                      //  ��һ���ӽڵ�
			{
				pos++;
			}
		}

        btree_insert_nonfull(node->p[pos], target);                   //   ֻ����Ҷ�ӵ�ʱ��Ų���
    }
}

//�ܵĲ���    root��Ҫ����Ľṹ��
btree_node* btree_insert(btree_node *root, int target)
{
    if(root==NULL)
	{
        return NULL;
    }

    if(root->num==2*M-1)                 //���ڵ��Ѿ�����    �����´���һ���ṹ��   û���Ļ����ṹ�幻�ţ����鹻��
	{
		btree_node *node = btree_node_new();           //�ؼ����Ѿ���ʼ��Ϊ0
		if(node==NULL)
		{
			return root;
		}

        node->is_leaf = 0;
        node->p[0] = root;
        btree_split_child(node, 0, root);         //�����Ƚ��з���   �Ż�
        btree_insert_nonfull(node, target);        //���������
        return node;
    }
	else
	{
        btree_insert_nonfull(root, target);
        return root;
    }
}

//����

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
   // find_node *fnode=find_node_new();      ����Ҫ�����µĽ��
	if(root==NULL)
    {
     //  if(!fnode->num)
    //   printf("%dû���������\n",target);
       return  fnode->num;     //����������һ������������������������������������
    }
    j=0;
	for(i=0;i<root->num;i++)
	{
		if(target==root->k[i])  //�ҵ���
		{
            fnode->num=fnode->num+1;    //����
            fnode->pt=root;
            fnode->tag=i;
            //return fnode;
          //  printf("�����ɹ�,��%d��%d����λ��Ϊ�ڵ�%X�ĵ�%d��\n,", fnode->num, target, fnode->pt, fnode->tag);
            /*
            //��������
		    for(j=i+1;j<root->num;j++)
		    {
		        if(target==root->k[j])
		        {
                fnode->num=fnode->num+1;
                fnode->pt=root;
                fnode->tag=j;
                //return fnode;
                printf("�����ɹ�,��%d��%d����λ��Ϊ�ڵ�%X�ĵ�%d��\n,", fnode->num, target, fnode->pt, fnode->tag);
                }
			}*/
			btree_search(root->p[i],target,fnode);
			/*
			else if(j<root->num)
			{
			//printf("�������\n");
			return ;
			}*/
        }
		else if(target<root->k[i])     //ȥ��ڵ�
		{
		    if(fnode->num!=0)
            break;
            btree_search(root->p[i],target,fnode);
        }
	   //���ڵĻ������� i++
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
           printf("%dû���������\n",target);
       }
     //printf("return\n");
       return  ;     //����������һ������������������������������������
    }
    for(i=0;i<root->num;i++)
    {
        if(target==root->k[i])  //�ҵ���
        {
            fnode->num=fnode->num+1;    //����
            fnode->pt=root;
            fnode->tag=i;
          //  printf("���ҳɹ���%d����λ��Ϊ�ڵ�%X�ĵ�%d��,����ʱ��Ϊ%fms\n,", target, fnode->pt, fnode->tag);
            btree_search_num(root->p[i],target,fnode);
        }
        if(target<root->k[i]) //ȥ��ڵ�
        {
             if(fnode->num!=0)
             break;
             btree_search_num(root->p[i],target,fnode);
        }
    }
     btree_search_num(root->p[i],target,fnode);       //ȫ���������Ҿ�����
}


//ɾ��
//�ϲ�y��z��k[pos]�½�Ϊy���м�ڵ㣬2��3��
void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
	y->num = 2 * M - 1;                               // ��z�нڵ㿽����y�ĺ�벿��
	for(int i = M; i < 2 * M - 1; i++)
	{
		y->k[i] = z->k[i-M];
	}
	y->k[M-1] = root->k[pos];

	if(false == z->is_leaf)                          // ���z��Ҷ�ӣ���Ҫ����pointer
	{
		for(int i = M; i < 2 * M; i++) {
			y->p[i] = z->p[i-M];
		}
	}

	for(int j = pos + 1; j < root->num; j++)          // k[pos]�½���y�У�����ԭ��k[pos]���ڵ�key��pointer
	{
		root->k[j-1] = root->k[j];
		root->p[j] = root->p[j+1];
	}

	root->num -= 1;
	free(z);
}


btree_node *btree_delete(btree_node *root, int target)     // ���⴦������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
                                                            // ����Ψһ�ܽ������ߵ�����
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

//Ѱ��rightmost����rootΪ�������ؼ���    һֱy = y->p[y->num];֪���ҵ�Ҷ�ӣ�Ҷ�ӵĲ�����ӽ��ģ�����
int btree_search_predecessor(btree_node *root)
{
	btree_node *y = root;
	while(false == y->is_leaf) {
		y = y->p[y->num];
	}
	return y->k[y->num-1];
}

// Ѱ��leftmost����rootΪ������С�ؼ���
int btree_search_successor(btree_node *root)
{
	btree_node *z = root;
	while(false == z->is_leaf) {
		z = z->p[0];
	}
	return z->k[0];
}

 // z��y��ڵ㣬��root->k[pos]�½���z����y�����ؼ���������root��pos�� 3��1��
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

// y���ڵ㣬��root->k[pos]�½���y����z����С�ؼ���������root��pos��
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
	// ֻ����ʾ1000�����
    btree_node *queue[500000] = {NULL};
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while(front < rear) {
        btree_node *node = queue[front++];

        printf("[");
        for( i = 0; i < node->num; i++) {
            printf("%d ", node->k[i]);                  //����ؼ���
        }
        printf("]");

        for( i = 0; i <= node->num; i++) {
            if(NULL != node->p[i]) {
                queue[rear++] = node->p[i];                //ת���ӽڵ�
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
        printf("%d��������Ϊ%d\n\n",find_num[i],fnode->num);
        printf("����ʱ��Ϊ%fms\n,", (end_time-start_time)/CLK_TCK*1000);

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
        printf("%d��������Ϊ%d\n\n",find_num[i],fnode->num);
        printf("����ʱ��Ϊ%fms\n,", (end_time-start_time)/CLK_TCK*1000);

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

    //���ļ�
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
            //    printf("%d ", arr[i]);    //�������
                num = i + 1;
            }
        }
      //  printf("\n*************************%d\n", num);     //���м�������

     //   printf("***************************����b��\n");
        for( i = 0; i < num ; i++)
        {
            root = btree_insert(root, arr[i]);
            //btree_level_display(root);
        }
        //btree_level_display(root);
        all_num = all_num + num;
    }
    printf("\n%d\n", all_num);     //�ܹ��м�������
    fclose(fp);


 /*   printf("\nɾ������\n");
	//int todel[] = {15, 18, 23, 30, 31, 52, 50};     //Ҫɾ������    ɾ�������⡫���ظ���ֻ��ɾ��һ��
	int todel[] = {52,1612,1432};
	for( i = 0; i < sizeof(todel) / sizeof(int); i++)
	{
		find_node *fnode=find_node_new();
        btree_search_num(root, todel[i],fnode);
        printf("���ҵ�%d��%d\n,",fnode->num,todel[i]);
    	printf("ɾ��%d֮��\n", todel[i]);
     	for(j=0;j<fnode->num;j++)
		{
		   root = btree_delete(root, todel[i]);
		   printf("delete\n");
        }
	//	btree_level_display(root);
	}
	//btree_level_display(root);

*/

    //����

    printf("\n����\n");
  //  int find_num[] = {15, 18, 23, 30};
  //  int find_num[] = {52,640,2682,2892,2871};
    //int find_num[] = {10,23,100};
    printf("�������� \n");
	start_time_0=clock();
	 for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d��������Ϊ%d\n\n",find_num[i],fnode->num);
        printf("����ʱ��Ϊ%fms\n,", (end_time-start_time)/CLK_TCK*1000);
    }
    end_time_0=clock();
    printf("������ʱ��Ϊ%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);

    printf("\n�������� \n");
	start_time_0=clock();
   // #pragma omp parallel for

	/* for( i = 0; i < sizeof(find_num) / sizeof(int); i++)
	{
	    find_node *fnode=find_node_new();
        start_time = clock();
        fnode->num=btree_search(root, find_num[i],fnode);
        end_time = clock();
        printf("%d��������Ϊ%d\n\n",find_num[i],fnode->num);
        printf("����ʱ��Ϊ%fms\n,", (end_time-start_time)/CLK_TCK*1000);
    }*/
  //  end_time_0=clock();
//    int t= omp_get_num_threads();
   // printf("xianchengshuwei:%d\n",t);

   // printf("kaishishijian:%fms\n",start_time_0);
   // printf("jieshushijian:%fms\n",end_time_0);
   // printf("������ʱ��Ϊ%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);

    pthread_mutex_init(&mut,NULL);
    printf("I'm the main,I'm building thread\n");
    thread_create();
    printf("I'm the main,I'm waiting for thread to finish mission\n");
    thread_wait();
        end_time_0=clock();
        printf("������ʱ��Ϊ%fms\n",(end_time_0-start_time_0)/CLK_TCK*1000);
    return 0;

}
