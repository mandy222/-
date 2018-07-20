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

//宏函数 
#define MC_GET_CHAR(__data__)   (*((char *)(__data__)))
#define MC_GET_SHORT(__data__)  ((UINT)((((UINT)(*((char *)(__data__))))<<8)|(((UINT)(*((char *)(__data__)+1)))&0x00ff)))
#define MC_GET_LONG(__data__)   ((((ULONG)MC_GET_SHORT((__data__)))<<16 )|(((ULONG)MC_GET_SHORT((char *)(__data__)+2))&0x0000ffff))
#define MC_GET_3BN(__data__)    ((((ULONG)MC_GET_CHAR((__data__)))<<16)|(((ULONG)MC_GET_SHORT((char *)(__data__)+1))&0x0000ffff))

//道路信息结构体 11
typedef struct Road{
	unsigned short length;       //读取字节长度 
	unsigned long linkID;        //道路的LinkID
	unsigned long roadMessage;   //道路信息,包括有无flag、分岔路数 、番号 
	short flag;				     //有无Flag
	short branchNum;		     //岔路数
    short classNum;		         //交叉Link列表示Class番号
    char roadName[20];           //道路名称 
	int nameSize;                //该道路名称尺寸
}Road;

//此结构体存储所有道路的信息
struct road{
	Road elem[MAXSIZE];  
}L;
//====================================================== 界面模块 ===================================================================
//信息介绍界面
void intro()
{
	cout<<endl;
	cout<<"					        ⌒▂▂⌒                  ⌒▂▂⌒"<<endl;
	cout<<"					       ┃┛▃┗┃                ┃┛▃┗┃"<<endl;
	cout<<"					▂▂ ╭┛╰┻╯┗╮▂        ▂╭┛╰┻╯┗╮▂▂  "<<endl;           
	cout<<"					▏  ╰╯▔▔▔▔╰╯          ╰╯▔▔▔▔╰╯   ▏"<<endl;
	cout<<"					▏                                               ▏"<<endl;
	cout<<"					▏       ☆  电子地图信息管理系统  ☆            ▏"<<endl;
	cout<<"					▏                                               ▏"<<endl;
	cout<<"					▏                          曾洁义、林雪茹       ▏"<<endl;
	cout<<"					▏                          2017年07月12日       ▏"<<endl;
	cout<<"					＼▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂/"<<endl<<endl<<endl;
}

//主界面
void mainMenu()
{
	cout<<endl;
	cout<<"				│＼＿╭╭╭＿／│==============================│＼＿╭╭╭＿／│"<<endl;
	cout<<"				│　　　　　　　│   ◇ 请选择服务的种类 ◇     │　　　　　　　│"<<endl;
	cout<<"				│　　　　　　　│      1.读取文件；            │　　　　　　　│"<<endl;
	cout<<"				│　＞　　　●　│      2.排序                  │　●　　　＜　│"<<endl;
	cout<<"				│≡ ╰┬┬╯ ≡│      3.检索                  │≡ ╰┬┬╯ ≡│"<<endl;
	cout<<"				│　　 ╰╯　 　│      4.更新                  │　　 ╰╯　 　│"<<endl;
	cout<<"				╰┬ｏ———ｏ┬╯      5.读取更新文件          ╰┬ｏ———ｏ┬╯"<<endl;
	cout<<"				　│          │        6.统计算法的时间复杂度    │          │  "<<endl;
	cout<<"				　╰┬———┬╯        0.退出                    ╰┬———┬╯  "<<endl;
	cout<<"				    =========================================================="<<endl<<endl;
}

//检索选择界面
void sortMenu()
{
	cout<<endl;
	cout<<"					          │＼＿╭＿／│"<<endl;
	cout<<"					          │ ●    ● │"<<endl; 
	cout<<"					          │    ┬    │"<<endl;
	cout<<"					          ╰┬Ｏ—Ｏ┬╯"<<endl; 
	cout<<"					+=========================================+"<<endl;
	cout<<"					|     ◇ 请选择检索的方式 ◇              |"<<endl;
	cout<<"					|        1.指定linkID检索                 |"<<endl;
	cout<<"					|        2.指定交叉Link列表示Class番号检索|"<<endl;
	cout<<"					|        3.指定查找分岔路检索             |"<<endl;
	cout<<"					|        4.指定道路名称检索               |"<<endl;
	cout<<"					|        0.退出检索                       |"<<endl;
	cout<<"		 			+=========================================+"<<endl;
}

void outMenu()
{
	cout<<"					│＼＿╭╭＿／│===============================+"<<endl;
	cout<<"					│　　　　　　│                               |"<<endl;
	cout<<"					│　＞　　＜　│                               |"<<endl;
	cout<<"					│≡╰┬┬╯≡│      您已经退出本系统！！     |"<<endl;
	cout<<"					│　  ╰╯ 　 │                               |"<<endl;
	cout<<"					╰┬ｏ——ｏ┬╯      欢迎您的再次使用！！！   |"<<endl;
	cout<<"					　│        │                                 |"<<endl;
	cout<<"					　╰┬——┬╯                                 |"<<endl;
	cout<<"					    ===========================================+"<<endl<<endl;

}
//========================================================== 读取文件模块 ==============================================================
//读入二进制文件并把数据转换成十进制
void read(char *path) 
{
	FILE *fp;	
	int i;

	char temp_size[2];                                                //temp_size数组存放某条道路信息的大小

	fp=fopen(path,"rb");                                              //打开文件

	//cout<<"文件打开中..."<<endl;
	if(fp==NULL)
	{
		cout<<"打开文件失败!"<<endl;
		return ;
	}
	
	//cout<<"文件读取中..."<<endl;
	
	for(i=1;i<=MAXSIZE; i++)
	{
	    fread(temp_size,2,1,fp);                                       //读字节长度
		L.elem[i].length=MC_GET_SHORT(temp_size);				       //十六进制转换为十进制
     	fread(&L.elem[i].linkID,4,1,fp);	                           //读linkID
		L.elem[i].linkID=MC_GET_LONG(&L.elem[i].linkID);
		fread(&L.elem[i].nameSize,2,1,fp);                             //读道路名称尺寸
		L.elem[i].nameSize=MC_GET_SHORT(&L.elem[i].nameSize);
	    fread(&L.elem[i].roadMessage,4,1,fp);                          //读道路信息,包括有无flag、分岔路数 、番号 
		L.elem[i].flag=(short)( MC_GET_LONG(&L.elem[i].roadMessage)>>7 );
		L.elem[i].branchNum=(short)( (MC_GET_LONG(&L.elem[i].roadMessage)<<25)>>29 );
     	L.elem[i].classNum=(short)( (MC_GET_LONG(&L.elem[i].roadMessage)<<28)>>28 );
		if(L.elem[i].length>12)
			fread(&L.elem[i].roadName,L.elem[i].length-12,1,fp);       //读道路名称
	}
	fclose(fp);                                                        //关闭文件
}
//===================================================  排序模块（根据linkID排序） ======================================================================================
//快速排序
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

//快速排序递归
void qSort(int low,int high)
{
	int pivotloc;
    if(low<high)
	{										
       pivotloc=partition(low,high); 		//将L.elem[low..high]一分为二，pivotloc是枢轴位置
       qSort(low,pivotloc-1);				//对左子表递归排序
       qSort(pivotloc+1,high);              //对右子表递归排序
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//冒泡排序
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
	
//直接插入排序
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

//折半插入排序
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

//简单选择排序
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
//=================================================================== 查找模块 ============================================================================
//---------------------------------------------------------------- linkID折半查找 --------------------------------------------------------------------
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

//linkID折半查找结果输出	
void showSortID(int result,int key)
{
	if(result==0)
		cout<<"						  不存在该linkID的道路！！"<<endl<<endl;
	else
	{
		cout<<"						检索成功!!检索的结果为:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		if(L.elem[result].length>12)
		{
			cout<<result<<"\t"<<"信息大小:"<<L.elem[result].length<<"\t"<<"LinkID:"<<L.elem[result].linkID<<"\t"<<"有无Flag:"<<L.elem[result].flag<<"\t"<<"分岔路数:"<<L.elem[result].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[result].classNum<<"\t"<<"道路名称为:"<<L.elem[result].roadName<<endl;
		}
		else cout<<result<<"\t"<<"信息大小:"<<L.elem[result].length<<"\t"<<"LinkID:"<<L.elem[result].linkID<<"\t"<<"有无Flag:"<<L.elem[result].flag<<"\t"<<"分岔路数:"<<L.elem[result].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[result].classNum<<"\t"<<"该道路无名称"<<endl;
		cout<<"==================================================================================================================================="<<endl;	
	}
	cout<<endl;	
}

//---------------------------------------------------------- linkID顺序查找 ---------------------------------------------------------------------------
void searchLinkID(int key)
{
	int i;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].linkID==key)	
			return;
	}
}

//------------------------------------------------------- 番号Class查找（顺序查找）--------------------------------------------------------------------
void  searchClass(int classNum)
{
	int i,j=0;
	int flag=0;
	cout<<"					请输入需要检索的道路的交叉Link列表示Class番号:";
	cin>>classNum;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].classNum==classNum)
			flag++;
	}	
	if(flag<=10 && flag>0)    //检索数据在10条以内直接显示输出
	{
			
		cout<<"						检索成功!!检索的结果为:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(L.elem[i].classNum==classNum)
			{
				if(L.elem[i].length>12)
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;
				else 
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl;
	}
	else if(flag==0)
	{
			cout<<"					检索失败，不存在该交叉Link列表示Class番号的道路！！"<<endl<<endl;
	}
	else if(flag>10)      //检索的数据多于10条时写入文件classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/classFind.txt","w+");      //建立txt文件写入读取的数据
		if(fp1==NULL)
		{
			cout<<"					检索道路数据写入失败!"<<endl;
			return ;
		}
		for(i=1;i<=MAXSIZE; i++)
		{
			if(L.elem[i].classNum==classNum)
			{
				if(L.elem[i].length>12)
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t道路名称为:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t该道路无名称\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}
		fclose(fp1);                               //关闭文件

		cout<<"	   共检索到"<<flag<<"条符合条件的道路。";
		cout<<"为了您查看方便，你需要检索的道路数据已存储到txt/classFind.txt中,前10条道路数据为："<<endl;;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)                  //将前十条数据输出
		{
			if(L.elem[i].classNum==classNum)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)				
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;	
					else 
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
}

//------------------------------------------------------ 根据分岔路查找（顺序查找）------------------------------------------------------------------
void searchBranch(int branchNum)
{
	int i,j=0;
	int flag=0;
	cout<<"					  请输入需要检索的道路的分岔路:";
	cin>>branchNum;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(L.elem[i].branchNum==branchNum)
			flag++;	
	}
		
	if(flag<=10 && flag>0)    //检索数据在10条以内直接显示输出
	{
		cout<<"							检索成功!!检索的结果为:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(L.elem[i].branchNum==branchNum)
			{
				if(L.elem[i].length>12)				
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;				
				else 
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl;;
	}

	else if(flag>10)      //检索的数据多于10条时写入文件classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/branchFind.txt","w+");      //建立txt文件写入读取的数据
		if(fp1==NULL)
		{
			cout<<"					查找的数据写入失败!"<<endl;
			return ;
		}

		for(i=1;i<=MAXSIZE; i++)
		{
			if(L.elem[i].branchNum==branchNum)
			{

				if(L.elem[i].length>12)
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t道路名称为:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t该道路无名称\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}

		fclose(fp1);                             //关闭文件

		cout<<"	  共检索到"<<flag<<"条符合条件的道路。";
		cout<<"为了您查看方便，需要查找的道路数据已存储到txt/branchFind.txt中,";
		cout<<"前10条道路数据为："<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)               //将前十条数据输出
		{
			if(L.elem[i].branchNum==branchNum)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;
					else 
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag==0)	
		cout<<"					  检索失败，不存在分岔路口的道路！！"<<endl<<endl;
}

//---------------------------------------------------- 根据道路名称查找（顺序查找）------------------------------------------------------------------------
void searchRoadName(char name[20])
{
	int i,j=0,flag=0;
	cout<<"					请输入需要检索道路的道路名称关键字:";
	cin>>name;
	for(i=1;i<=MAXSIZE;i++)
	{
		if(strstr(L.elem[i].roadName,name)!=0)
			flag++;
	}		
	if(flag<=10 && flag>0)    //检索数据在10条以内直接显示输出
	{
		cout<<"								检索成功!!检索的结果为:"<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE;i++)
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{
				if(L.elem[i].length>12)			
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;				
				else 
					cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag>10)             //检索的数据多于10条时写入文件classFind
	{
		FILE *fp1;
		int i;
		fp1=fopen("txt/nameFind.txt","w+");      //建立txt文件写入检索的数据
		if(fp1==NULL)
		{
			cout<<"							检索的数据写入失败!"<<endl;
			return ;
		}
		for(i=1;i<=MAXSIZE; i++)
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{
				if(L.elem[i].length>12)			
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t道路名称为:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
				else
					fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t该道路无名称\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
			}
		}

		fclose(fp1);                            //关闭文件

		cout<<"	    共检索到"<<flag<<"条符合条件的道路。";
		cout<<"为了您查看方便，需要检索的道路数据已存储到txt/nameFind.txt中,";
		cout<<"前10条道路数据为："<<endl;
		cout<<"==================================================================================================================================="<<endl;
		for(i=1;i<=MAXSIZE; i++)               //输出前10条数据
		{
			if(strstr(L.elem[i].roadName,name)!=0)
			{	
				j++;
				if(j<=10)
				{
					if(L.elem[i].length>12)
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;
					else 
						cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;					
				}
			}
		}
		cout<<"==================================================================================================================================="<<endl<<endl;
	}
	else if(flag==0)
	{
		cout<<"					检索失败，不存在该名称的道路！！"<<endl<<endl;
	}
}
//================================================================ 更新模块 =============================================================================
//将排好序的文件写入二进制文件
void renew()
{
   	FILE *fp2;	
	int i,temp;
	fp2=fopen("renew.dat","wb+");        //建立renew.dat文件
	if(fp2==NULL)
	{
		cout<<"				更新失败!"<<endl;
		return ;
	}
	for(i=1;i<=MAXSIZE; i++)
	{
		temp=L.elem[i].length;
		L.elem[i].length=MC_GET_SHORT(&L.elem[i].length);	     //进制转换	
		fwrite(&L.elem[i].length,2,1,fp2);                       //写入道路信息长度 
		L.elem[i].linkID = MC_GET_LONG(&L.elem[i].linkID);     
		fwrite(&L.elem[i].linkID,4,1,fp2);                       //写入linkID
		L.elem[i].nameSize=MC_GET_SHORT(&L.elem[i].nameSize);
		fwrite(&L.elem[i].nameSize,2,1,fp2);                     //写入道路尺寸 
		fwrite(&L.elem[i].roadMessage,4,1,fp2);	                 //写入道路信息		
		fwrite(&L.elem[i].roadName,temp-12,1,fp2);               //写入道路名称尺寸  	
	}
		
	fclose(fp2);
	cout<<"						更新成功!!已保存到renew.dat中。"<<endl<<endl;
}
//=================================================== 统计算法时间复杂度 ===============================================================================
void countTime()
{
	cout<<"						算法执行时间正在统计中，请耐心等待..."<<endl;
	clock_t start,finish;   
	float duration1,duration2,duration3,duration4,duration5,duration6,duration7;
	read("GTBL.dat");                                            //重新读入无序的二进制文件
	start = clock();                                                 //计时开始
	qSort(1,MAXSIZE);                                            //快速排序时间统计 
	finish = clock();                                                 //计时结束
	duration1 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat"); 
	start = clock();                                                   
	bubbleSort();                                                //冒泡排序时间统计
	finish = clock();                                                  
	duration2 =(float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                 
	insertSort();                                                //直接插入排序时间统计
	finish = clock();                                                    
	duration3 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                   
	bInsertSort();                                               //折半插入排序时间统计 
	finish = clock();                                                    
	duration4 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	start = clock();                                                
	selectSort();                                                //简单选择排序时间统计 
	finish = clock();                                                   
	duration5 = (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");                                             //读入原二进制文件
	qSort(1,MAXSIZE);                                             //排序
	start = clock();                                              //折半查找时间统计
	for(int a=0;a<=1000000;a++)
	{
		searchBinLinkID(811); 
	}
	finish = clock();                                                  
	duration6= (float)(finish - start) / CLOCKS_PER_SEC;

	read("GTBL.dat");
	qSort(1,MAXSIZE); 
	start = clock();                                               //顺序查找时间统计
	for(int b=0;b<=1000000;b++)
	{
		searchLinkID(811);
	}
	finish = clock();                                                   
	duration7= (float)(finish - start) / CLOCKS_PER_SEC;
	cout<<"			+===============================================================================+"<<endl;
	cout<<"			|                             ◇ 算法时间复杂度统计 ◇                          |"<<endl;
	cout<<"			+===============================================================================+"<<endl;
	cout<<"			|            |                           |      实际用时   |    理论时间复杂度  |"<<endl;
	cout<<"			+            +=============================================+====================+"<<endl;
	cout<<"			|            |       快速排序            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration1<<"秒     |     O(n*log2n)     |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       冒泡排序            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration2<<"秒    |        O(n2)       |"<<endl;
	cout<<"			| ◇排序算法 +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       直接插入排序        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration3<<"秒    |        O(n2)       |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       折半插入排序        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration4<<"秒    |        O(n2)       |"<<endl;
	cout<<"			|            +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       简单选择排序        |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration5<<"秒    |        O(n2)       |"<<endl;
	cout<<"			+============+===========================+=================+====================+"<<endl;
	cout<<"			|            |       顺序查找            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration7<<"微秒   |         O(n)       |"<<endl;
	cout<<"			| ◇查找算法 +---------------------------+-----------------+--------------------+"<<endl;
	cout<<"			|            |       折半查找            |     "<<setiosflags(ios::fixed)<<setprecision(3)<<duration6<<"微秒   |       O(logn)      |"<<endl;
	cout<<"			+============+===========================+======================================+"<<endl<<endl;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
// 输出前十条道路信息
void tenShow()
{
	int i;
	cout<<"==================================================================================================================================="<<endl;
	for(i=1;i<=10; i++)                      
	{
			if(L.elem[i].length>12)		
				cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"道路名称为:"<<L.elem[i].roadName<<endl;		
			else 
				cout<<i<<"\t"<<"信息大小:"<<L.elem[i].length<<"\t"<<"LinkID:"<<L.elem[i].linkID<<"\t"<<"有无Flag:"<<L.elem[i].flag<<"\t"<<"分岔路数:"<<L.elem[i].branchNum<<"\t"<<"交叉Link列表示Class番号:"<<L.elem[i].classNum<<"\t"<<"该道路无名称"<<endl;		
	}
	cout<<"==================================================================================================================================="<<endl;
}

//把数据写进txt文件
void writeTxt(char *path)
{
	FILE *fp1;
	int i;
	fp1=fopen(path,"w+");                                          //建立并打开文件
	if(fp1==NULL)
	{
		cout<<"					数据写入失败失败!"<<endl;
		return ;
	}
	for(i=1;i<=MAXSIZE; i++)
	{
		if(L.elem[i].length>12)	
			fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t道路名称为:%s\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum,L.elem[i].roadName);
		else
			fprintf(fp1,"%d\t信息大小:%d\tLinkID:%d\t有无Flag:%d\t分岔路数:%d\t交叉Link列表示Class番号:%d\t该道路无名称\n",i,L.elem[i].length,L.elem[i].linkID,L.elem[i].flag,L.elem[i].branchNum,L.elem[i].classNum);
	}
	fclose(fp1);                                                   //关闭文件
	cout<<"					为方便您的查看，数据已经存储在"<<path<<"中。"<<endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//检索选择
void findSelect()
{	
	int key,result,classNum,branchNum,choose=-1;
	char name[20];
	while (choose!=0)
	{
		cout<<endl<<"						      请选择:";
		cin>>choose;
		if(choose>=5||choose<0)
			cout<<"						输入有误,请重新输入!"<<endl;
		switch (choose)
		{
			case 1://指定linkID检索
				cout<<"						请输入需要检索的道路的linkID：";
				cin>>key;
				searchBinLinkID(key);             //折半查找
		    	result=searchBinLinkID(key);
				showSortID(result,key);           //输出折半查找结果
				sortMenu();
				break;
			case 2://指定交叉Link列表示Class番号检索                          
				searchClass(classNum);
				sortMenu();
				break;
			case 3://指定查找分岔路检索  
				searchBranch(branchNum); 
				sortMenu();
				break;
			case 4://指定道路名称检索
				searchRoadName(name);
				sortMenu();
				break;
		}
	}
	if(choose==0)
		cout<<"						     已退出检索！"<<endl<<endl;
}
//======================================================================== 主函数 =============================================================================
void main()
{
	int choose=-1,flag=0;
	intro();                                                                       //系统起始界面
	mainMenu();                                                                    //主界面
	while(choose!=0)
	{
		cout<<"							    请选择：";
		cin>>choose;
		if(choose>=7||choose<0)
			cout<<"							输入有误,请重新输入!"<<endl<<endl;
		switch (choose)
		{
			case 1://读取文件
				read("GTBL.dat");                                                   //读入二进制文件并把数据转换成十进制
				cout<<"					文件读取成功！！已读出"<<MAXSIZE<<"条数据,前10条数据为:"<<endl;
				tenShow();			                                                //输出前10条数据
				writeTxt("txt/read.txt");                                           //把读入的数据写进txt文件
				flag=1;
				mainMenu();                                                         //返回主界面
				break;
			case 2://排序
				if(flag!=1)
					cout<<"						文件未读取无法进行排序，请先读取文件。"<<endl<<endl;
				else
				{
					qSort(1,MAXSIZE);                                                //按linkID快速排序
					flag=2;
					cout <<"					文件排序成功！！已经排序好"<<MAXSIZE<<"条数据,前10条数据为:"<<endl;
					tenShow();				                                        //输出排序后的前10条数据
					writeTxt("txt/sort.txt");                                        //把排序后的所有数据写入txt文件中
					mainMenu();                                                      //返回主界面
				}
				break;
			case 3://检索
				if(flag!=2)
					cout<<"						文件未排序无法进行检索，请先排序。"<<endl<<endl;
				else
				{
					sortMenu();                                                      //检索界面
					findSelect();                                                    //检索方式的选择
					mainMenu();                                                      //返回主界面
				}
				break;
			case 4://更新
				if(flag!=2)
					cout<<"						文件未排序无法进行更新，请先排序。"<<endl<<endl;
				else
				{
					renew();
					mainMenu();                                                        //返回主界面
					flag=3;
				}
				break;
			case 5://读取更新文件
				if(flag!=3)
					cout<<"						文件未更新无法进行读取更新文件，请先更新文件。"<<endl<<endl;
				else
				{
					read("renew.dat");                                                  //读取更新文件
					cout<<"					更新文件已读取成功！！已读出"<<MAXSIZE<<"条数据."<<endl;
					writeTxt("txt/renew.txt");                                          //把更新后的文件写入txt文件
					cout<<"					前10条数据为："<<endl;
					tenShow();                                                          //输出前10条道路信息
					cout<<endl;
					mainMenu();                                                         //返回主界面
				}
				break;
			case 6://统计算法的时间复杂度
				countTime(); 
				cout<<endl;
				mainMenu();                                                             //返回主界面
				break;
		}
	}
	if(choose==0)
		outMenu();
}
