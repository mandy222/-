#include<iostream>
#include<string>
using namespace std;
     
typedef int ElemType;
//存储结构     
typedef struct LNode
{ 
	ElemType data;         
	struct LNode *next;    
}LNode,*LinkList;        

//输入
void creatList(LinkList &L,int i)
{
	LinkList p,r;                        
  	L = new LNode;                      
  	L->next = NULL;                      
  	r=L;				                 
	cout<<"请输入链表10个元素的值：";
	for(i=0;i<10;++i)
	{
		p=new LNode;                     
		cin>>p->data;                   
		p->next=NULL; r->next=p;         
		r=p;                                                 
	}
	
 } 

//输出 
void outList(LinkList &L)
{
	LinkList p;                 
 	p=L->next;                 
 	cout<<"新的链表为：";
 	while(p!=NULL)             
 	{
 		cout<<p->data<<" ";     
 		p=p->next;              
	 }
	cout<<endl;
} 

//冒泡排序
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
		p=L->next;          //回到头节点
	}
}

//查找
void locateElem(LinkList L,ElemType e) 
{
 	LinkList p;
	p=L->next; 
	int i=1;
	cout<<"请输入所要查找的元素值:";
	cin >> e;
	while(p && p->data!=e)    
	{
		p=p->next;
		i++;
	}
    cout<<"该元素的位置为：第"<<i<<"个"<<endl;

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
