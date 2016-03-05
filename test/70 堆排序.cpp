#include <iostream>

//�ѳ���
int heapsize;

//�󶥶ѻ�
void MAX_HEAPIFY(int A[],int i)
{
	int l=2*i;		//�� i ������� �±� ����l
	int r=2*i+1;		//�� i ������� �±� ����r
	int largest;	//3�����������±�

	if(l<=heapsize && A[l]>A[i])
		largest=l;
	else
		largest=i;

	if(r<=heapsize && A[r]>A[largest])
		largest=r;

	if(largest!=i)
	{
		//���� A[largest] �� A[i]
		int tmp=A[largest];
		A[largest]=A[i];
		A[i]=tmp;

		MAX_HEAPIFY(A,largest);
	}
}

//����
void BUILD_MAX_HEAP(int A[])
{
	int i;
	for(i=(int)(heapsize/2);i>=1;i--)
		MAX_HEAPIFY(A,i);
}

//������
void HEAPSORT(int A[])
{
	BUILD_MAX_HEAP(A);		//ok

	int i;
	int tmp;
	for(i=heapsize;i>=2;i--)		//A[1] �ض�������
	{
		//���� A[1] �� A[i]
		tmp=A[1];
		A[1]=A[i];
		A[i]=tmp;

		heapsize--;
		MAX_HEAPIFY(A,1);
	}
}

int main()
{
	int A[6]={0,5,3,2,1,4};
	//ok
	int n=sizeof(A)/sizeof(int)-1;
	heapsize=n;

	HEAPSORT(A);

	for(int i=1;i<=n;i++)
		printf("%d ",A[i]);

	return 0;
}