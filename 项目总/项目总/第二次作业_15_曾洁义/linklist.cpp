#include<iostream>
#include<string>
using namespace std;
     
typedef int ElemType;
//�洢�ṹ     
typedef struct LNode
{ 
	ElemType data;         
	struct LNode *next;    
}LNode,*LinkList;        

//����
void creatList(LinkList &L,int i)
{
	LinkList p,r;                        
  	L = new LNode;                      
  	L->next = NULL;                      
  	r=L;				                 
	cout<<"����������10��Ԫ�ص�ֵ��";
	for(i=0;i<10;++i)
	{
		p=new LNode;                     
		cin>>p->data;                   
		p->next=NULL; r->next=p;         
		r=p;                                                 
	}
	
 } 

//��� 
void outList(LinkList &L)
{
	LinkList p;                 
 	p=L->next;                 
 	cout<<"�µ�����Ϊ��";
 	while(p!=NULL)             
 	{
 		cout<<p->data<<" ";     
 		p=p->next;              
	 }
	cout<<endl;
} 

//ð������
void bubbleSort(LinkList &L)
{
	LinkList p;
	p=L->next;
	int t;
	int m=9;
	while(m>0)
	{
		while(p->next!=NULL)
		{
			if(p->data > p->next->data)
				{
					t=p->data;
					p->data=p->next->data;
					p->next->data=t;
				}
				p=p->next;				
		}
		m--;
		p=L->next;          //�ص�ͷ�ڵ�
	}
}

//����
void locateElem(LinkList L,ElemType e) 
{
 	LinkList p;
	p=L->next; 
	int i=1;
	cout<<"��������Ҫ���ҵ�Ԫ��ֵ:";
	cin >> e;
	while(p && p->data!=e)    
	{
		p=p->next;
		i++;
	}
    cout<<"��Ԫ�ص�λ��Ϊ����"<<i<<"��"<<endl;

}
 
int main()
{
	 LinkList L, p;
	 int n,e;
     creatList(L,n);
	 outList(L);
	 bubbleSort(L);
	 outList(L);
	 locateElem(L,e);
	 return 0;
}
