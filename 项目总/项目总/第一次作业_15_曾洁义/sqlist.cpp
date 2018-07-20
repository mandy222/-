#include<iostream>
#include<string>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;      
typedef int ElemType;
#define MAXSIZE 20
typedef struct
{
	ElemType *elem;
	int length;
}SqList;

Status InitList(SqList &L)
{//��ʼ��
	L.elem=new ElemType[MAXSIZE];
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	return OK;
}

Status Input(SqList &L, int i)
{//����
	int n;
	cout<<"������10����:";
	for(i=0;i<10;i++)
	{
		cin>>n ;
		L.elem[i]=n;
		++L.length;
	}
	return OK;
}

Status Output(SqList &L, int i)
{//���
	cout<<"��ǰ���ݵ�����Ϊ��";
	for(i=0;i<10;i++)
	{
		cout<<" "<<L.elem[i];
	}
	cout<<endl;
	return OK;
}

void BubbleSort(SqList &L)
{//ð������
	int m,flag,t,j;
	m=L.length-1;
	flag=1;
	while((m>0)&&(flag==1))
	{
		flag=0;
		for(j=0;j<m;j++)
			if(L.elem[j]>L.elem[j+1])
			{
				flag=1;
				t=L.elem[j];
				L.elem[j]=L.elem[j+1];
				L.elem[j+1]=t;
			}
		--m;
	}
}

int Search_Bin(SqList L,int key)
{//�۰����
	int low,high,mid;
	cout<<"������ؼ��֣�";
	cin>>key;
	low=1;
	high=L.length;
	while(low<=high)
	{
		mid=(high+low)/2;
		if(key==L.elem[mid]) break;
		else if(key<L.elem[mid]) high=mid-1;
		else low=mid+1;
	}
	cout<<"���ҵĹؼ��ֵ�λ��Ϊ"<<mid+1;
	cout<<endl;
	return 0;
}



int main()
{
	SqList L;
	int i,key;
	InitList(L);
	Input(L,i);
	Output(L,i);
	BubbleSort(L);
	Output(L,i);
	Search_Bin(L,key);
	return OK;
}