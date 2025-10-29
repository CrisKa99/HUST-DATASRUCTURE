#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  SqList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL){
		L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
		L.length=0;
		L.listsize=LIST_INIT_SIZE;
		return OK;
	}
	else return INFEASIBLE;

    /********** End **********/
}
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		free(L.elem);
		L.elem=NULL;
		int length;
	    int listsize;
	    return OK;
	}

    /********** End **********/
}
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		L.length=0;
		free(L.elem);
		L.elem=(ElemType *) malloc(sizeof(ElemType));
		return OK;
	}
    /********** End **********/
}
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		if(!L.length) return TRUE;
		else return FALSE;
	}

    /********** End **********/
}
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else return L.length;

    /********** End **********/
}
status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else if(i<1||i>L.length) return ERROR;
	else{
		e=L.elem[i-1];
		return OK;
	}

    /********** End **********/
}
int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		for(int i=0;i<=L.length;i++){
			if(e==L.elem[i]) return i+1;
		}
		return ERROR;
	}

    /********** End **********/
}
status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		int i=0;
		for(i;i<=L.length;i++){
			if(e==L.elem[i]) break;
		}
		if(i==0||e!=L.elem[i]) return ERROR;
		else{
			pre=L.elem[i-1];
			return OK;
		}
	}

    /********** End **********/
}
status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		int i=0;
		for(i;i<L.length;i++){
			if(e==L.elem[i]) break;
		}
		if(i>=L.length-1) return ERROR;
		else{
			next=L.elem[i+1];
			return OK;
		}
	}
    /********** End **********/
}
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		if(i>=1&&i<=L.length+1){
			if(L.length >= L.listsize){
				L.listsize+=LISTINCREMENT;
				L.elem=(ElemType *) realloc(L.elem,sizeof(ElemType)*L.listsize);
			}
			for(int j=L.length;j>=i;j--){
				L.elem[j]=L.elem[j-1];
			}
			L.elem[i-1]=e;
			L.length++;
			return OK;
		}
		else return ERROR;
	}
    /********** End **********/
}
status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		if(i>=1&&i<=L.length){
			e=L.elem[i-1];
			for(int j=i-1;j<L.length-1;j++){
				L.elem[j]=L.elem[j+1];
			}
			
			L.length--;
			return OK;
		}
		else return ERROR;
	}

    /********** End **********/
}
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		if(!L.length) return OK;
		else{
			for(int i=0;i<L.length;i++){
				if(i<L.length-1) printf("%d ",L.elem[i]);
                else printf("%d",L.elem[i]);
			}
            return OK;
		}
	}

    /********** End **********/
}
int MaxSubArray(SqList L) {
    // 检查线性表是否非空
    if (L.length == 0) {
        return 0;
    }

    int maxSum = L.elem[0]; // 全局最大和
    int currentSum = L.elem[0]; // 当前子数组的最大和

    // 从第二个元素开始遍历数组
    for (int i = 1; i < L.length; i++) {
        // 更新当前子数组的最大和
        currentSum = (currentSum > 0) ? currentSum + L.elem[i] : L.elem[i];
        
        // 更新全局最大和
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    // 返回最大和
    return maxSum;
}
#define MAX_SIZE 10001

int SubArrayNum(SqList L, int k) {
    // 检查线性表是否非空
    if (L.length == 0) {
        return 0;
    }

    int count = 0; // 计数器
    int sum = 0; // 前缀和
    int prefixSum[MAX_SIZE] = {0}; // 用于存储前缀和及其出现次数

    // 遍历线性表，计算前缀和
    for (int i = 0; i < L.length; i++) {
        sum += L.elem[i];
        
        // 如果前缀和等于 k，直接将计数器加一
        if (sum == k) {
            count++;
        }
        
        // 如果前缀和减去 k 在前缀和表中存在，则说明存在连续子数组和为 k
        if (sum - k >= 0 && sum - k < MAX_SIZE) {
            count += prefixSum[sum - k];
        }
        
        // 更新前缀和表
        prefixSum[sum]++;
    }

    // 返回结果
    return count;
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortList(SqList *L) {
    int i, j;
    for (i = 0; i < L->length - 1; i++) {
        for (j = 0; j < L->length - 1 - i; j++) {
            if (L->elem[j] > L->elem[j + 1]) {
                swap(&L->elem[j], &L->elem[j + 1]);
            }
        }
    }
}
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    FILE *fp;
    fp = fopen(FileName, "w");
    if (fp == NULL||L.elem==NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);
    return OK;
    /********** End **********/
}

status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    FILE *fp;
    fp = fopen(FileName, "r");
    if (fp == NULL||L.elem!=NULL) {
        return INFEASIBLE;
    }
    L.elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    int value;
    int i = 0;
    while (fscanf(fp, "%d", &value) != EOF) {
        L.elem[i] = value;
        i++;
    }
    L.length = i;
    fclose(fp);
    return OK;
    /********** End **********/
}
status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
    /********** End **********/
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	for(int i=0;i<Lists.length;i++){
		if(strcmp(ListName,Lists.elem[i].name)==0){
			DestroyList(Lists.elem[i].L);
            for(int j=i; j<Lists.length-1; j++){
                strcpy(Lists.elem[j].name, Lists.elem[j+1].name);
                Lists.elem[j].L = Lists.elem[j+1].L;
            }
            
            Lists.length--;
            return OK;
		}
	}
	return ERROR;
    /********** End **********/
}
int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	for(int i=0;i<Lists.length;i++){
		if(strcmp(ListName,Lists.elem[i].name)==0)
			return i+1;
	}
	return 0;

    /********** End **********/
}
void singleListOperation(SqList &L){
  int op=1,op2=1,i,j,e,pre,next;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList         10. ListInsert \n");
		printf("    	  2. DestroyList      11. ListDelete \n");
		printf("    	  3. ClearList        12. ListTrabverse \n");
		printf("    	  4. ListEmpty        13. MaxSubArray \n");
		printf("    	  5. ListLength       14. SubArrayNum \n");
		printf("    	  6. GetElem          15. sortList \n");
		printf("    	  7. LocateElem       16. File \n");
		printf("    	  8. PriorElem        \n");
		printf("    	  9. NextElem         \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:
			 
			 getchar();getchar();
			 break;
		   case 2:
			 if(DestroyList(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else  printf("线性表销毁成功！\n");
			 getchar();getchar();
			 break;
		   case 3:
			 if(ClearList(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else  printf("线性表删除成功！\n");
			 getchar();getchar();
			 break;
	 	  case 4:
			 if(ListEmpty(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else if(ListEmpty(L)==TRUE) printf("线性表判断为空！\n");
			 else  printf("线性表判断不为空！\n");
			 getchar();getchar();
			 break;
		   case 5:
		   	 i=ListLength(L); 
			 if(i==INFEASIBLE) printf("线性表不存在！\n");      
			 else printf("线性表长度为%d!\n",i);
			 getchar();getchar();
			 break;
		   case 6:
		   	 printf("请输入要获取的元素的序号：");
		   	 scanf("%d",&j);
		   	 i=GetElem(L,j,e); 
			 if(i==INFEASIBLE) printf("线性表不存在！\n");    
			 else if(j<=L.length) printf("线性表第%d个元素为%d！\n",j,e);     
			 else printf("序号超限");
			 getchar();getchar();
			 break;
		   case 7:
		   	printf("请输入要查找的元素：");
		   	 scanf("%d",&e);
		   	 i=LocateElem(L,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("查找失败"); 
			 else printf("线性表指定%d元素的逻辑序号为%d！\n",e,j);     
			 getchar();getchar();
			 break;
		   case 8:
		   	printf("请输入要获取前驱元素的元素：");
		   	 scanf("%d",&e);
		   	 i=PriorElem(L,e,pre);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表中不存在指定元素%d的前驱元素！\n",e);  
			 else printf("线性表中指定元素%d的前驱元素为%d！\n",e,pre);     
			 getchar();getchar();
			 break;
		   case 9:
		   	printf("请输入要获取后继元素的元素：");
			 scanf("%d",&e);
		   	 i=NextElem(L,e,next);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表中不存在指定元素%d的后继元素！\n",e);  
			 else printf("线性表中指定元素%d的后继元素为%d！\n",e,next);     
			 getchar();getchar();
			 break;
		   case 10:
		   	printf("请输入要在线性表中插入元素的序号和要插入的元素：");
		   	 scanf("%d%d",&j,&e);
		   	 i=ListInsert(L,j,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表元素插入失败！\n"); 
			 else{
			 	printf("线性表元素插入成功！\n新线性表为："); 
			 	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
     		 }   
			 getchar();getchar();
			 break;
		   case 11:
		   	printf("请输入要在线性表中删除的元素：");
		   	 scanf("%d",&j);
		   	 i=ListDelete(L,j,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表元素删除失败！\n"); 
			 else{
			 	printf("线性表元素删除成功！\n删除元素为：%d\n新线性表为：",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(!ListTraverse(L)) printf("线性表是空表！\n");
			getchar();getchar();
			 break;
		   case 13:
		   	i=MaxSubArray(L);
		   	if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	else printf("连续子数组的最大和为：%d",i);
		   	getchar();getchar();
			 break;
		   case 14:
		   	printf("请输入连续子数组的和k：");
		   	scanf("%d",&j);
		   	i=SubArrayNum(L,j);
		   	if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	else printf("该线性表中和为%d的连续子数组的个数为：%d",j,i);
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(&L);
		   	if(L.elem==NULL) printf("线性表不存在！\n");  
		   	else{
		   		printf("线性表元素排序成功！\n新线性表为：",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("线性表不存在！对空表进行读文件操作！读得线性表为：\n"); 
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	
		    	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
			} 
		    else{
		    	printf("线性表判断存在！对线性表进行写文件操作！\n");
		    	SaveList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
				
			}
			
			getchar();getchar();
			 break;
			case 0:
	         break;
		}
	}
	printf("对多表的单表操作结束！\n");
}	
/*--------------------------------------------*/
int main(void){
	SqList L;  int op=1,op2=1,i,j,e,pre,next;
	L.elem=NULL;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList         10. ListInsert \n");
		printf("    	  2. DestroyList      11. ListDelete \n");
		printf("    	  3. ClearList        12. ListTrabverse \n");
		printf("    	  4. ListEmpty        13. MaxSubArray \n");
		printf("    	  5. ListLength       14. SubArrayNum \n");
		printf("    	  6. GetElem          15. sortList \n");
		printf("    	  7. LocateElem       16. File \n");
		printf("    	  8. PriorElem        17. Lists\n");
		printf("    	  9. NextElem         \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:
			 //printf("\n----IntiList功能待实现！\n");
			 
			 if(InitList(L)==OK) printf("线性表创建成功！\n");
		     else printf("线性表创建失败！\n");
			 getchar();getchar();
			 break;
		   case 2:
			 if(DestroyList(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else  printf("线性表销毁成功！\n");
			 getchar();getchar();
			 break;
		   case 3:
			 if(ClearList(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else  printf("线性表删除成功！\n");
			 getchar();getchar();
			 break;
	 	  case 4:
			 if(ListEmpty(L)==INFEASIBLE) printf("线性表不存在！\n");     
			 else if(ListEmpty(L)==TRUE) printf("线性表判断为空！\n");
			 else  printf("线性表判断不为空！\n");
			 getchar();getchar();
			 break;
		   case 5:
		   	 i=ListLength(L); 
			 if(i==INFEASIBLE) printf("线性表不存在！\n");      
			 else printf("线性表长度为%d!\n",i);
			 getchar();getchar();
			 break;
		   case 6:
		   	 printf("请输入要获取的元素的序号：");
		   	 scanf("%d",&j);
		   	 i=GetElem(L,j,e); 
			 if(i==INFEASIBLE) printf("线性表不存在！\n");    
			 else if(j<=L.length) printf("线性表第%d个元素为%d！\n",j,e);     
			 else printf("序号超限");
			 getchar();getchar();
			 break;
		   case 7:
		   	printf("请输入要查找的元素：");
		   	 scanf("%d",&e);
		   	 i=LocateElem(L,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("查找失败"); 
			 else printf("线性表指定%d元素的逻辑序号为%d！\n",e,j);     
			 getchar();getchar();
			 break;
		   case 8:
		   	printf("请输入要获取前驱元素的元素：");
		   	 scanf("%d",&e);
		   	 i=PriorElem(L,e,pre);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表中不存在指定元素%d的前驱元素！\n",e);  
			 else printf("线性表中指定元素%d的前驱元素为%d！\n",e,pre);     
			 getchar();getchar();
			 break;
		   case 9:
		   	printf("请输入要获取后继元素的元素：");
			 scanf("%d",&e);
		   	 i=NextElem(L,e,next);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表中不存在指定元素%d的后继元素！\n",e);  
			 else printf("线性表中指定元素%d的后继元素为%d！\n",e,next);     
			 getchar();getchar();
			 break;
		   case 10:
		   	printf("请输入要在线性表中插入元素的序号和要插入的元素：");
		   	 scanf("%d%d",&j,&e);
		   	 i=ListInsert(L,j,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表元素插入失败！\n"); 
			 else{
			 	printf("线性表元素插入成功！\n新线性表为："); 
			 	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
     		 }   
			 getchar();getchar();
			 break;
		   case 11:
		   	printf("请输入要在线性表中删除的元素序号：");
		   	 scanf("%d",&j);
		   	 i=ListDelete(L,j,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("线性表元素删除失败！\n"); 
			 else{
			 	printf("线性表元素删除成功！\n删除元素为：%d\n新线性表为：",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 ListTraverse(L);
			getchar();getchar();
			 break;
		   case 13:
		   	i=MaxSubArray(L);
		   	if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	else printf("连续子数组的最大和为：%d",i);
		   	getchar();getchar();
			 break;
		   case 14:
		   	printf("请输入连续子数组的和k：");
		   	scanf("%d",&j);
		   	i=SubArrayNum(L,j);
		   	if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	else printf("该线性表中和为%d的连续子数组的个数为：%d",j,i);
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(&L);
		   	if(L.elem==NULL) printf("线性表不存在！\n");  
		   	else{
		   		printf("线性表元素排序成功！\n新线性表为：",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("线性表不存在！对空表进行读文件操作！读得线性表为：\n"); 
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	
		    	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
			} 
		    else{
		    	printf("线性表判断存在！对线性表进行写文件操作！\n");
		    	SaveList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
				
			}
			
			getchar();getchar();
			 break;
			case 17:
				LISTS Lists;
			Lists.length=0;
				while(op2){
					
				
			
			 printf("          Management Of Multiple Linear Tables   \n");
			 printf("-------------------------------------------------\n");
			 printf("    	  1. AddList         3.LocateList \n");
			 printf("    	  2. RemoveList      0.Exit\n");
			 printf("-------------------------------------------------\n");
			 printf("    请选择你的操作[0~3]:");
		     
		     scanf("%d",&op2);
		     char name[30];
		     switch(op2){
		     	
		     	case 1:
		     		int n,e;
		     		
		     		printf("请输入要添加的线性表的个数：");
					scanf("%d",&n);
					while(n--)
   					{
    					scanf("%s",name);
   						AddList(Lists,name);
      					scanf("%d",&e);
      					while (e)
      					{
      					ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
      					scanf("%d",&e);
      					}
   					}
   					printf("添加后的多线性表为：");
   					for(n=0;n<Lists.length;n++)
   					{
   						printf("%s ",Lists.elem[n].name);
   						ListTraverse(Lists.elem[n].L);
   						putchar('\n');
   					}
   					getchar();getchar();
			 		break;
			 	case 2: 
			 		printf("请输入要删除的线性表的名字：");
			 		scanf("%s",name);
				   if (RemoveList(Lists,name)==OK){
				   		printf("删除后的线性表为：\n");
					   for(n=0;n<Lists.length;n++)
				   		{
				   			printf("%s ",Lists.elem[n].name);
				   			ListTraverse(Lists.elem[n].L);
				        	putchar('\n');
				   		}
				   		}
				   else printf("删除失败");
							 
		    getchar();getchar();
			 break;
		case 3:
			printf("请输入要查找的线性表的名字：");
			 scanf("%s",name);
		   if (n=LocateList(Lists,name))
		   		{
		   			printf("%s ",Lists.elem[n-1].name);
		   			ListTraverse(Lists.elem[n-1].L);
		   			printf("\n是否对所查到的线性表进行单表操作？（Y or N）\n");
		         	char c;getchar();
		         	scanf("%c",&c);
					if(c=='Y') singleListOperation(Lists.elem[n-1].L); 
		         putchar('\n');
		   		}
		   else printf("查找失败");
		    getchar();getchar();
			 break;
		case 0:
	         break;
	     }
	     
		}
		case 0:
	         break;//end of switch
	  }//end of while
	
	}//end of main()
	printf("欢迎下次再使用本系统！\n");
}
