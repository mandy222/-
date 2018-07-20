#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <iomanip>
using namespace std;

#define MAXSIZE 63538
typedef char INT;
typedef unsigned char  UCHAR;
typedef unsigned short UINT;
typedef unsigned long  ULONG;

//�꺯�� 
#define MC_GET_CHAR(__data__)   (*((char *)(__data__)))
#define MC_GET_SHORT(__data__)  ((UINT)((((UINT)(*((char *)(__data__))))<<8)|(((UINT)(*((char *)(__data__)+1)))&0x00ff)))
#define MC_GET_LONG(__data__)   ((((ULONG)MC_GET_SHORT((__data__)))<<16 )|(((ULONG)MC_GET_SHORT((char *)(__data__)+2))&0x0000ffff))
#define MC_GET_3BN(__data__)    ((((ULONG)MC_GET_CHAR((__data__)))<<16)|(((ULONG)MC_GET_SHORT((char *)(__data__)+1))&0x0000ffff))

//��·��Ϣ�ṹ�� 11
typedef struct Road{
	unsigned short length;       //��ȡ�ֽڳ��� 
	unsigned long linkID;        //��·��LinkID
	unsigned long roadMessage;   //��·��Ϣ,��������flag���ֲ�·�� ������ 
	short flag;				     //����Flag
	short branchNum;		     //��·��
    short classNum;		         //����Link�б�ʾClass����
    char roadName[20];           //��·���� 
	int nameSize;                //�õ�·���Ƴߴ�
}Road;

//�˽ṹ��洢���е�·����Ϣ
struct road{
	Road elem[MAXSIZE];  
}L;
//====================================================== ����ģ�� ===================================================================
//��Ϣ���ܽ���
void intro()
{
	cout<<endl;
	cout<<"					        �Шy�y��                  �Шy�y��"<<endl;
	cout<<"					       �����z����                �����z����"<<endl;
	cout<<"					�y�y �q���t�ߨs���r�y        �y�q���t�ߨs���r�y�y  "<<endl;           
	cout<<"					��  �t�s���������t�s          �t�s���������t�s   ��"<<endl;
	cout<<"					��                                               ��"<<endl;
	cout<<"					��       ��  ���ӵ�ͼ��Ϣ����ϵͳ  ��            ��"<<endl;
	cout<<"					��                                               ��"<<endl;
	cout<<"					��                          �����塢��ѩ��       ��"<<endl;
	cout<<"					��                          2017��07��12��       ��"<<endl;
	cout<<"					�ܨy�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y�y/"<<endl<<endl<<endl;
}

//������
void mainMenu()
{
	cout<<endl;
	cout<<"				���ܣߨq�q�q�ߣ���==============================���ܣߨq�q�q�ߣ���"<<endl;
	cout<<"				������������������   �� ��ѡ���������� ��     ������������������"<<endl;
	cout<<"				������������������      1.��ȡ�ļ���            ������������������"<<endl;
	cout<<"				�������������񡡩�      2.����                  �����񡡡���������"<<endl;
	cout<<"				���� �t�ЩШs �ԩ�      3.����                  ���� �t�ЩШs �ԩ�"<<endl;
	cout<<"				������ �t�s�� ����      4.����                  ������ �t�s�� ����"<<endl;
	cout<<"				�t�У������Шs      5.��ȡ�����ļ�          �t�У������Шs"<<endl;
	cout<<"				����          ��        6.ͳ���㷨��ʱ�临�Ӷ�    ��          ��  "<<endl;
	cout<<"				���t�С������Шs        0.�˳�                    �t�С������Шs  "<<endl;
	cout<<"				    =========================================================="<<endl<<endl;
}

//����ѡ�����
void sortMenu()
{
	cout<<endl;
	cout<<"					          ���ܣߨq�ߣ���"<<endl;
	cout<<"					          �� ��    �� ��"<<endl; 
	cout<<"					          ��    ��    ��"<<endl;
	cout<<"					          �t�Уϡ��ϩШs"<<endl; 
	cout<<"					+=========================================+"<<endl;
	cout<<"					|     �� ��ѡ������ķ�ʽ ��              |"<<endl;
	cout<<"					|        1.ָ��linkID����                 |"<<endl;
	cout<<"					|        2.ָ������Link�б�ʾClass���ż���|"<<endl;
	cout<<"					|        3.ָ�����ҷֲ�·����             |"<<endl;
	cout<<"					|        4.ָ����·���Ƽ���               |"<<endl;
	cout<<"					|        0.�˳�����                       |"<<endl;
	cout<<"		 			+=========================================+"<<endl;
}

void outMenu()
{
	cout<<"					���ܣߨq�q�ߣ���===============================+"<<endl;
	cout<<"					����������������                               |"<<endl;
	cout<<"					����������������                               |"<<endl;
	cout<<"					���Ԩt�ЩШs�ԩ�      ���Ѿ��˳���ϵͳ����     |"<<endl;
	cout<<"					����  �t�s �� ��                               |"<<endl;
	cout<<"					�t�У����Шs      ��ӭ�����ٴ�ʹ�ã�����   |"<<endl;
	cout<<"					����        ��                                 |"<<endl;
	cout<<"					���t�С����Шs                                 |"<<endl;
	cout<<"					    ===========================================+"<<endl<<endl;

}
//========================================================== ��ȡ�ļ�ģ�� ==============================================================
//����������ļ���������ת����ʮ����
void read(char *path) 
{
	FILE *fp;	
	int i;

	char temp_size[2];                                                //temp_size������ĳ����·��Ϣ�Ĵ�С

	fp=fopen(path,"rb");                                              //���ļ�

	//cout<<"�ļ�����..."<<endl;
	if(fp==NULL)
	{
		cout<<"���ļ�ʧ��!"<<endl;
		return ;
	}
	
	//cout<<"�ļ���ȡ��..."<<endl;
	
	for(i=1;i<=MAXSIZE; i++)
	{
	    fread(temp_size,2,1,fp);                                       //���ֽڳ���
		L.elem[i].length=MC_GET_SHORT(temp_size);				       //ʮ������ת��Ϊʮ����
     	fread(&L.elem[i].linkID,4,1,fp);	                           //��linkID
		L.elem[i].linkID=MC_GET_LONG(&L.elem[i].linkID);
		fread(&L.elem[i].nameSize,2,1,fp);                             //����·���Ƴߴ�
		L.elem[i].nameSize=MC_GET_SHORT(&L.elem[i].nameSize);
	    fread(&L.elem[i].roadMessage,4,1,fp);                          //����·��Ϣ,��������flag���ֲ�·�� ������ 
		L.elem[i].flag=(short)( MC_GET_LONG(&L.elem[i].roadMessage)>>7 );
		L.elem[i].branchNum=(short)( (MC_GET_LONG(&L.elem[i].roadMessage)<<25)>>29 );
     	L.elem[i].classNum=(short)( (MC_GET_LONG(&L.elem[i].roadMessage)<<28)>>28 );
		if(L.elem[i].length>12)
			fread(&L.elem[i].roadName,L.elem[i].length-12,1,fp);       //����·����
	}
	fclose(fp);                                                        //�ر��ļ�
}
//===================================================  ����ģ�飨����linkID���� ======================================================================================
//��������
int partition(int low,int high)
{ 
	int pivotkey;
	L.elem[0]=L.elem[low];  
	pivotkey=L.elem[low].linkID;		   			
	while(low<high)
	{				
		while(low<high && L.elem[high].linkID >= pivotkey) 
			--high;
		L.elem[low]=L.elem[high];					
		while(low<high && L.elem[low].linkID <= pivotkey) 
			++low;
		L.elem[high]=L.elem[low];					
	}
	L.elem[low]=L.elem[0];						
	return  low;
}

//��������ݹ�
void qSort(int low,int high)
{
	int pivotloc;
    if(low<high)
	{										
       pivotloc=partition(low,high); 		//��L.elem[low..high]һ��Ϊ����pivotloc������λ��
       qSort(low,pivotloc-1);				//�����ӱ�ݹ�����
       qSort(pivotloc+1,high);              //�����ӱ�ݹ�����
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//ð������
void bubbleSort()
{
	int m,flag,j;
	m=MAXSIZE-1;
	flag=1;
	while((m>0)&&(flag==1))
	{
		flag=0;
		for(j=1;j<=m;j++)
			if(L.elem[j].linkID>L.elem[j+1].linkID)
			{
				flag=1;
				L.elem[0]=L.elem[j];
				L.elem[j]=L.elem[j+1];
				L.elem[j+1]=L.elem[0];
			}
		--m;
	}
}
	
//ֱ�Ӳ�������
void insertSort()
{
	int i,j;
	for(i=2;i<=MAXSIZE;++i)
		if(L.elem[i].linkID<L.elem[i-1].linkID)
		{   										                   
			L.elem[0]=L.elem[i];				 			
            L.elem[i]=L.elem[i-1];	            		
            for(j=i-2; L.elem[0].linkID<L.elem[j].linkID; --j)			
				L.elem[j+1]=L.elem[j];					              
            L.elem[j+1]=L.elem[0];											
		}											
}

//�۰��������
void bInsertSort()
{
	int i,j,low,high,m;
	for(i=2;i<=MAXSIZE;++i)
	{
		L.elem[0]=L.elem[i];          					
		low=1; high=i-1;        					
		while(low<=high)
		{											
			m=(low+high)/2;             			
			if(L.elem[0].linkID<L.elem[m].linkID)  
				high=m-1;	
			else  low=m+1;					   		
		}//while
		for(j=i-1;j>=high+1;--j)  L.elem[j+1]=L.elem[j];	
		L.elem[high+1]=L.elem[0];							
    }												
}

//��ѡ������
void selectSort() 
{ 
	int i,j,k;
    for(i=1;i<MAXSIZE;++i) 
	{  												
		k=i;                 
        for(j=i+1;j<=MAXSIZE;++j)
		{
			if(L.elem[j].linkID<L.elem[k].linkID)  
				k=j;
		}
		if(k!=i) 
		{
			L.elem[0]=L.elem[i];
			L.elem[i]=L.elem[k];
			L.elem[k]=L.elem[0];
		}       
     }												
}																		
//=================================================================== ����ģ�� ============================================================================
//---------------------------------------------------------------- linkID�۰���� --------------------------------------------------------------------
int searchBinLinkID(int key)
{
	int low,high,mid;
	low=1;
	high=MAXSIZE;
	while(low<=high)
	{
		mid=(high+low)/2;
		if(key==L.elem[mid].linkID) return mid;
		else if(key<L.elem[mid].linkID) high=mid-1;
		else low=mid+1;
	}
	return 0;
}

//linkID�۰���ҽ�����	
void showSortID(int result,int key)
{
	if(result==0)
		cout<<"						  �����ڸ�linkID�ĵ�·����"<<endl<<endl;
	else
	{
		cout<<"						�����ɹ�!!�����Ľ��Ϊ:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		if(L.elem[result].length>12)
		{
			cout<<result<<"\t"<<"��Ϣ��С:"<<L.elem[result].length<<"\t"<<"LinkID:"<<L.elem[result].linkID<<"\t"<<"����Flag:"<<L.elem[result].flag<<"\t"<<"�ֲ�·��:"<<L.elem[result].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[result].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[result].roadName<<endl;
		}
		else cout<<result<<"\t"<<"��Ϣ��С:"<<L.elem[result].length<<"\t"<<"LinkID:"<<L.elem[result].linkID<<"\t"<<"����Flag:"<<L.elem[result].flag<<"\t"<<"�ֲ�·��:"<<L.elem[result].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[result].classNum<<"\t"<<"�õ�·������"<<endl;
		cout<<"==================================================================================================================================="<<endl;	
	}
	cout<<endl;	
}

//---------------------------------------------------------- linkID˳����� ---------------------------------------------------------------------------
void searchLinkID(int key)
{
	int i;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].linkID==key)	
			return;
	}
}

//------------------------------------------------------- ����Class���ң�˳����ң�--------------------------------------------------------------------
void  searchClass(int classNum)
{
	int i,j=0;
	int flag=0;
	cout<<"					��������Ҫ�����ĵ�·�Ľ���Link�б�ʾClass����:";
	cin>>classNum;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].classNum==classNum)
			flag++;
	}	
	if(flag<=10 && flag>0)    //����������10������ֱ����ʾ���
	{
			
		cout<<"						�����ɹ�!!�����Ľ��Ϊ:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(L.elem[i].classNum==classNum)
			{
				if(L.elem[i].length>12)
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;
				else 
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl;
	}
	else if(flag==0)
	{
			cout<<"					����ʧ�ܣ������ڸý���Link�б�ʾClass���ŵĵ�·����"<<endl<<endl;
	}
	else if(flag>10)      //���������ݶ���10��ʱд���ļ�classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/classFind.txt","w+");      //����txt�ļ�д���ȡ������
		if(fp1==NULL)
		{
			cout<<"					������·����д��ʧ��!"<<endl;
			return ;
		}
		for(i=1;i<=MAXSIZE; i++)
		{
			if(L.elem[i].classNum==classNum)
			{
				if(L.elem[i].length>12)
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t��·����Ϊ:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t�õ�·������\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}
		fclose(fp1);                               //�ر��ļ�

		cout<<"	   ��������"<<flag<<"�����������ĵ�·��";
		cout<<"Ϊ�����鿴���㣬����Ҫ�����ĵ�·�����Ѵ洢��txt/classFind.txt��,ǰ10����·����Ϊ��"<<endl;;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)                  //��ǰʮ���������
		{
			if(L.elem[i].classNum==classNum)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)				
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;	
					else 
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
}

//------------------------------------------------------ ���ݷֲ�·���ң�˳����ң�------------------------------------------------------------------
void searchBranch(int branchNum)
{
	int i,j=0;
	int flag=0;
	cout<<"					  ��������Ҫ�����ĵ�·�ķֲ�·:";
	cin>>branchNum;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].branchNum==branchNum)
			flag++;	
	}
		
	if(flag<=10 && flag>0)    //����������10������ֱ����ʾ���
	{
		cout<<"							�����ɹ�!!�����Ľ��Ϊ:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(L.elem[i].branchNum==branchNum)
			{
				if(L.elem[i].length>12)				
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;				
				else 
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl;;
	}

	else if(flag>10)      //���������ݶ���10��ʱд���ļ�classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/branchFind.txt","w+");      //����txt�ļ�д���ȡ������
		if(fp1==NULL)
		{
			cout<<"					���ҵ�����д��ʧ��!"<<endl;
			return ;
		}

		for(i=1;i<=MAXSIZE; i++)
		{
			if(L.elem[i].branchNum==branchNum)
			{

				if(L.elem[i].length>12)
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t��·����Ϊ:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t�õ�·������\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}

		fclose(fp1);                             //�ر��ļ�

		cout<<"	  ��������"<<flag<<"�����������ĵ�·��";
		cout<<"Ϊ�����鿴���㣬��Ҫ���ҵĵ�·�����Ѵ洢��txt/branchFind.txt��,";
		cout<<"ǰ10����·����Ϊ��"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)               //��ǰʮ���������
		{
			if(L.elem[i].branchNum==branchNum)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;
					else 
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag==0)	
		cout<<"					  ����ʧ�ܣ������ڷֲ�·�ڵĵ�·����"<<endl<<endl;
}

//---------------------------------------------------- ���ݵ�·���Ʋ��ң�˳����ң�------------------------------------------------------------------------
void searchRoadName(char name[20])
{
	int i,j=0,flag=0;
	cout<<"					��������Ҫ������·�ĵ�·���ƹؼ���:";
	cin>>name;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(strstr(L.elem[i].roadName,name)!=0)
			flag++;
	}		
	if(flag<=10 && flag>0)    //����������10������ֱ����ʾ���
	{
		cout<<"								�����ɹ�!!�����Ľ��Ϊ:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{
				if(L.elem[i].length>12)			
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;				
				else 
					cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag>10)             //���������ݶ���10��ʱд���ļ�classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/nameFind.txt","w+");      //����txt�ļ�д�����������
		if(fp1==NULL)
		{
			cout<<"							����������д��ʧ��!"<<endl;
			return ;
		}
		for(i=1;i<=MAXSIZE; i++)
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{
				if(L.elem[i].length>12)			
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t��·����Ϊ:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t�õ�·������\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}

		fclose(fp1);                            //�ر��ļ�

		cout<<"	    ��������"<<flag<<"�����������ĵ�·��";
		cout<<"Ϊ�����鿴���㣬��Ҫ�����ĵ�·�����Ѵ洢��txt/nameFind.txt��,";
		cout<<"ǰ10����·����Ϊ��"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)               //���ǰ10������
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;
					else 
						cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag==0)
	{
		cout<<"					����ʧ�ܣ������ڸ����Ƶĵ�·����"<<endl<<endl;
	}
}
//================================================================ ����ģ�� =============================================================================
//���ź�����ļ�д��������ļ�
void renew()
{
   	FILE *fp2;	
	int i,temp;
	fp2=fopen("renew.dat","wb+");        //����renew.dat�ļ�
	if(fp2==NULL)
	{
		cout<<"				����ʧ��!"<<endl;
		return ;
	}
	for(i=1;i<=MAXSIZE; i++)
	{
		temp=L.elem[i].length;
		L.elem[i].length=MC_GET_SHORT(&L.elem[i].length);	     //����ת��	
		fwrite(&L.elem[i].length,2,1,fp2);                       //д���·��Ϣ���� 
		L.elem[i].linkID = MC_GET_LONG(&L.elem[i].linkID);     
		fwrite(&L.elem[i].linkID,4,1,fp2);                       //д��linkID
		L.elem[i].nameSize=MC_GET_SHORT(&L.elem[i].nameSize);
		fwrite(&L.elem[i].nameSize,2,1,fp2);                     //д���·�ߴ� 
		fwrite(&L.elem[i].roadMessage,4,1,fp2);	                 //д���·��Ϣ		
		fwrite(&L.elem[i].roadName,temp-12,1,fp2);               //д���·���Ƴߴ�  	
	}
		
	fclose(fp2);
	cout<<"						���³ɹ�!!�ѱ��浽renew.dat�С�"<<endl<<endl;
}
//=================================================== ͳ���㷨ʱ�临�Ӷ� ===============================================================================
void countTime()
{
	cout<<"						�㷨ִ��ʱ������ͳ���У������ĵȴ�..."<<endl;
	clock_t start,finish;   
	float duration1,duration2,duration3,duration4,duration5,duration6,duration7;
	read("GTBL.dat");                                            //���¶�������Ķ������ļ�
	start = clock();                                                 //��ʱ��ʼ
	qSort(1,MAXSIZE);                                            //��������ʱ��ͳ�� 
	finish = clock();                                                 //��ʱ����
	duration1 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat"); 
	start = clock();                                                   
	bubbleSort();                                                //ð������ʱ��ͳ��
	finish = clock();                                                  
	duration2 =(float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                 
	insertSort();                                                //ֱ�Ӳ�������ʱ��ͳ��
	finish = clock();                                                    
	duration3 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                   
	bInsertSort();                                               //�۰��������ʱ��ͳ�� 
	finish = clock();                                                    
	duration4 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                
	selectSort();                                                //��ѡ������ʱ��ͳ�� 
	finish = clock();                                                   
	duration5 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");                                             //����ԭ�������ļ�
	qSort(1,MAXSIZE);                                             //����
	start = clock();                                              //�۰����ʱ��ͳ��
	for(int a=0;a<=1000000;a++)
	{
		searchBinLinkID(811); 
	}
	finish = clock();                                                  
	duration6= (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	qSort(1,MAXSIZE); 
	start = clock();                                               //˳�����ʱ��ͳ��
	for(int b=0;b<=1000000;b++)
	{
		searchLinkID(811);
	}
	finish = clock();                                                   
	duration7= (float)(finish - start) / CLOCKS_PER_SEC;
	cout<<"			+===============================================================================+"<<endl;
	cout<<"			|                             �� �㷨ʱ�临�Ӷ�ͳ�� ��                          |"<<endl;
	cout<<"			+===============================================================================+"<<endl;
	cout<<"			|            |                           |      ʵ����ʱ   |    ����ʱ�临�Ӷ�  |"<<endl;
	cout<<"			+            +=============================================+====================+"<<endl;
	cout<<"			|            |       ��������            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration1<<"��     |     O(n*log2n)     |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       ð������            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration2<<"��    |        O(n2)       |"<<endl;
	cout<<"			| �������㷨 +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       ֱ�Ӳ�������        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration3<<"��    |        O(n2)       |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       �۰��������        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration4<<"��    |        O(n2)       |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       ��ѡ������        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration5<<"��    |        O(n2)       |"<<endl;
	cout<<"			+============+===========================+=================+====================+"<<endl;
	cout<<"			|            |       ˳�����            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration7<<"΢��   |         O(n)       |"<<endl;
	cout<<"			| ������㷨 +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       �۰����            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration6<<"΢��   |       O(logn)      |"<<endl;
	cout<<"			+============+===========================+======================================+"<<endl<<endl;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
// ���ǰʮ����·��Ϣ
void tenShow()
{
	int i;
	cout<<"==================================================================================================================================="<<endl;
	for(i=1;i<=10; i++)                      
	{
			if(L.elem[i].length>12)		
				cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"��·����Ϊ:"<<L.elem[i].roadName<<endl;		
			else 
				cout<<i<<"\t"<<"��Ϣ��С:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"����Flag:"<<L.elem[i].flag<<"\t"<<"�ֲ�·��:"<<L.elem[i].branchNum<<"\t"<<"����Link�б�ʾClass����:"<<L.elem[i].classNum<<"\t"<<"�õ�·������"<<endl;		
	}
	cout<<"==================================================================================================================================="<<endl;
}

//������д��txt�ļ�
void writeTxt(char *path)
{
	FILE *fp1;
	int i;
	fp1=fopen(path,"w+");                                          //���������ļ�
	if(fp1==NULL)
	{
		cout<<"					����д��ʧ��ʧ��!"<<endl;
		return ;
	}
	for(i=1;i<=MAXSIZE; i++)
	{
		if(L.elem[i].length>12)	
			fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t��·����Ϊ:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
		else
			fprintf(fp1,"%d\t��Ϣ��С:%d\tLinkID:%d\t����Flag:%d\t�ֲ�·��:%d\t����Link�б�ʾClass����:%d\t�õ�·������\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
	}
	fclose(fp1);                                                   //�ر��ļ�
	cout<<"					Ϊ�������Ĳ鿴�������Ѿ��洢��"<<path<<"�С�"<<endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//����ѡ��
void findSelect()
{	
	int key,result,classNum,branchNum,choose=-1;
	char name[20];
	while (choose!=0)
	{
		cout<<endl<<"						      ��ѡ��:";
		cin>>choose;
		if(choose>=5||choose<0)
			cout<<"						��������,����������!"<<endl;
		switch (choose)
		{
			case 1://ָ��linkID����
				cout<<"						��������Ҫ�����ĵ�·��linkID��";
				cin>>key;
				searchBinLinkID(key);             //�۰����
		    	result=searchBinLinkID(key);
				showSortID(result,key);           //����۰���ҽ��
				sortMenu();
				break;
			case 2://ָ������Link�б�ʾClass���ż���                          
				searchClass(classNum);
				sortMenu();
				break;
			case 3://ָ�����ҷֲ�·����  
				searchBranch(branchNum); 
				sortMenu();
				break;
			case 4://ָ����·���Ƽ���
				searchRoadName(name);
				sortMenu();
				break;
		}
	}
	if(choose==0)
		cout<<"						     ���˳�������"<<endl<<endl;
}
//======================================================================== ������ =============================================================================
void main()
{
	int choose=-1,flag=0;
	intro();                                                                       //ϵͳ��ʼ����
	mainMenu();                                                                    //������
	while(choose!=0)
	{
		cout<<"							    ��ѡ��";
		cin>>choose;
		if(choose>=7||choose<0)
			cout<<"							��������,����������!"<<endl<<endl;
		switch (choose)
		{
			case 1://��ȡ�ļ�
				read("GTBL.dat");                                                   //����������ļ���������ת����ʮ����
				cout<<"					�ļ���ȡ�ɹ������Ѷ���"<<MAXSIZE<<"������,ǰ10������Ϊ:"<<endl;
				tenShow();			                                                //���ǰ10������
				writeTxt("txt/read.txt");                                           //�Ѷ��������д��txt�ļ�
				flag=1;
				mainMenu();                                                         //����������
				break;
			case 2://����
				if(flag!=1)
					cout<<"						�ļ�δ��ȡ�޷������������ȶ�ȡ�ļ���"<<endl<<endl;
				else
				{
					qSort(1,MAXSIZE);                                                //��linkID��������
					flag=2;
					cout <<"					�ļ�����ɹ������Ѿ������"<<MAXSIZE<<"������,ǰ10������Ϊ:"<<endl;
					tenShow();				                                        //���������ǰ10������
					writeTxt("txt/sort.txt");                                        //����������������д��txt�ļ���
					mainMenu();                                                      //����������
				}
				break;
			case 3://����
				if(flag!=2)
					cout<<"						�ļ�δ�����޷����м�������������"<<endl<<endl;
				else
				{
					sortMenu();                                                      //��������
					findSelect();                                                    //������ʽ��ѡ��
					mainMenu();                                                      //����������
				}
				break;
			case 4://����
				if(flag!=2)
					cout<<"						�ļ�δ�����޷����и��£���������"<<endl<<endl;
				else
				{
					renew();
					mainMenu();                                                        //����������
					flag=3;
				}
				break;
			case 5://��ȡ�����ļ�
				if(flag!=3)
					cout<<"						�ļ�δ�����޷����ж�ȡ�����ļ������ȸ����ļ���"<<endl<<endl;
				else
				{
					read("renew.dat");                                                  //��ȡ�����ļ�
					cout<<"					�����ļ��Ѷ�ȡ�ɹ������Ѷ���"<<MAXSIZE<<"������."<<endl;
					writeTxt("txt/renew.txt");                                          //�Ѹ��º���ļ�д��txt�ļ�
					cout<<"					ǰ10������Ϊ��"<<endl;
					tenShow();                                                          //���ǰ10����·��Ϣ
					cout<<endl;
					mainMenu();                                                         //����������
				}
				break;
			case 6://ͳ���㷨��ʱ�临�Ӷ�
				countTime(); 
				cout<<endl;
				mainMenu();                                                             //����������
				break;
		}
	}
	if(choose==0)
		outMenu();
}
