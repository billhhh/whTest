#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cassert>
#include <time.h>
#include <queue>
#include <map>
#include <stack>
#include <bitset>
#include <string>
#include <sstream>
#define INF 0x3f3f3f3f

using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}

//======================================================

typedef struct node
{
	int m_key;
	node * m_pLeft,*m_pRight;
}BinaryTreeNode;

//BinaryTreeNode* constructTree(int* preOrder,int preLen,int* sMidOrder, int midLen){
BinaryTreeNode* constructRoot(int* preOrder, int* midOrder, int len){

	//先根遍历（前序遍历）的第一个值就是根节点的key
	int rootKey=preOrder[0];
	BinaryTreeNode* root=new BinaryTreeNode;
	root->m_key=rootKey;
	root->m_pLeft=root->m_pRight=NULL;
	if(len==1 && *preOrder==*midOrder)//只有一个节点
		return root;

	//在中根遍历（中序遍历）中找到根节点
	int* rootMidOrder=midOrder;
	int leftLen=0; //左子树节点数
	while(*rootMidOrder!=rootKey&&rootMidOrder<=(midOrder+len-1)){ 
		++rootMidOrder;
		++leftLen;
	}
	if(*rootMidOrder!=rootKey)//在中根序列未找到根节点，输入错误
		return NULL;

	if(leftLen>0){ //构建左子树
		root->m_pLeft=constructRoot(preOrder+1,midOrder,leftLen);
	}
	if(len-leftLen-1>0){ //构建右子树
		root->m_pRight=constructRoot(preOrder+leftLen+1,rootMidOrder+1,len-leftLen-1);
	}
	return root;
}

BinaryTreeNode* construct(int* preOrder,int* midOrder,int len){
	if(preOrder==NULL||midOrder==NULL||len<=0)
		return NULL;
	return constructRoot(preOrder,midOrder,len);
}

//先根遍历
void preOrderRecursionPrint(BinaryTreeNode* root){
	if(root==NULL)
		return;
	cout<<root->m_key<<endl;   //visit
	preOrderRecursionPrint(root->m_pLeft);
	preOrderRecursionPrint(root->m_pRight);
}

int main()
{
	//freopen("input.txt","r",stdin);

	//先根序列
	int preOrder[8]={1,2,4,7,3,5,6,8};
	//中根序列
	int midOrder[8]={4,7,2,1,5,3,8,6};

	BinaryTreeNode * treeRoot = construct(preOrder,midOrder,8);

	preOrderRecursionPrint(treeRoot);

	return 0;
}