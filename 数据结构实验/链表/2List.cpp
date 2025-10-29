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
typedef int ElemType; 
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  LinkList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if (L==NULL){
		L=(LinkList )malloc(sizeof(LinkList));
		L->next=NULL;
		return OK; 
	}
	else return INFEASIBLE;
}
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		LinkList p=L,temp;
		while(p){
			temp=p->next;
			free(p);
			p=temp;
		}
		L=NULL;
		return OK;
	}
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		LinkList p=L->next,temp;
		while(p){
			temp=p->next;
			free(p);
			p=temp;
		}
		L->next=NULL;
		return OK;
	}
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		if(L->next==NULL) return TRUE;
		else return FALSE;
	}
}
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		int i=0;
		while(L){
			L=L->next;
			i++;
		}
		return i-1;
	}
}
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		int j=0;
		for(j;j<i&&L!=NULL;j++){
			L=L->next;
		}
		if(i==0||i>ListLength(L)) return ERROR;
		else{
			e=L->data;
			return OK;
		}
	}
}
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	else{
		int i=1;
		while(L){
			if(L->data==e) return i-1;
			L=L->next;
			i++;
		}
		if(i==0||L==NULL) return ERROR;
		else{
			e=L->data;
			return OK;
		}
	}
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L==NULL) return INFEASIBLE;
    if(L->next==NULL) return ERROR;
	LinkList p1=L->next,p2=p1->next;
	while(p2){
		if(p2->data==e){
			pre=p1->data;
			return OK;
		}
		p1=p1->next;
		p2=p1->next;
	}
	return ERROR;
}
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	if(L->next==NULL) return ERROR;
	LinkList p1=L->next,p2=p1->next;
	while(p2){
		if(p1->data==e){
			next=p2->data;
			return OK;
		}
		p1=p1->next;
		p2=p1->next;
	}
	return ERROR;
}
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	if(i<=0) return ERROR;
	LinkList p1=L,insert=(LinkList) malloc(sizeof(LNode));
	for(int j=0;j<i-1;j++){
		if(p1->next==NULL) return ERROR;
		p1=p1->next;
	}
	insert->data=e;
	insert->next=p1->next;
	p1->next=insert;
	return OK;
}
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	if(i==0) return ERROR;
	LinkList p1=L,p2=L->next;
	int j;
	for(int j=0;j<i-1;j++){
		if(p1->next==NULL) return ERROR;
		p1=p1->next;
		p2=p1->next;
	}
	if(p2==NULL) return ERROR;
	e=p2->data;
	p1->next=p2->next;
	free(p2);
	return OK;
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	if(L==NULL) return INFEASIBLE;
	LinkList p=L->next;
	if(p==NULL) return OK;
	printf("%d",p->data);
	p=p->next;
	while(p){
		printf(" %d",p->data);
		p=p->next;
	}
	return OK;
}
LinkList reverseList(LinkList &head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    LinkList pre = NULL, cur = head->next, next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = pre;
    
    return head;
}

status RemoveNthFromEnd(LinkList &L, int n) {
    // 如果链表为空或只有一个节点，无法删除倒数第n个节点
    if (L == NULL || L->next == NULL) {
        return INFEASIBLE;
    }

    LinkList fast = L->next, slow = L->next;
    // 快指针先移动n步
    for (int i = 0; i < n; i++) {
        if (fast == NULL) {
            return ERROR; // 链表长度小于n，删除失败
        }
        fast = fast->next;
    }

    LinkList prev = NULL;
    // 快慢指针一起移动，直到快指针到达链表尾部
    while (fast != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next;
    }

    if (prev == NULL) {
        // 如果要删除的是头节点
        LinkList temp = L->next;
        L->next = L->next->next;
        free(temp);
    } else {
        // 删除中间或尾部节点
        prev->next = slow->next;
        free(slow);
    }
    return OK; // 删除成功
}

status sortList(LinkList &L) { 
	if (L == NULL || L->next == NULL) {
        return INFEASIBLE;
    }

    LinkList p = L->next, q = NULL;
    ElemType temp;
    while (p != NULL) {
        q = p->next;
        while (q != NULL) {
            if (p->data > q->data) {
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
    return OK; 
} 
status  SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    FILE *fp;
    fp = fopen(FileName, "w");
    if (fp == NULL||L==NULL) {
        return INFEASIBLE;
    }
    LinkList p=L->next;
	if(p==NULL) return OK;
    while(p) {
        fprintf(fp, "%d ", p->data);
        p=p->next;
    }
    fclose(fp);
    return OK;
}
status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	FILE *fp;
    fp = fopen(FileName, "r");
    if (fp == NULL||L!=NULL) {
        return INFEASIBLE;
    }
	int value;
	L=(LinkList) malloc(sizeof(LNode));
	LinkList p=L;
    while (fscanf(fp, "%d", &value) != EOF) {
    	p->next=(LinkList) malloc(sizeof(LNode));
    	p=p->next;
        p->data = value;
    }
    p->next=NULL;
    fclose(fp);
    return OK;
}


status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L= NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
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
}
int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	for(int i=0;i<Lists.length;i++){
		if(strcmp(ListName,Lists.elem[i].name)==0)
			return i+1;
	}
	return 0;
}
void singleListOperation(LinkList &L){
	int op=1,op2=1,i,j,e,pre,next;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList         10. ListInsert \n");
		printf("    	  2. DestroyList      11. ListDelete \n");
		printf("    	  3. ClearList        12. ListTrabverse \n");
		printf("    	  4. ListEmpty        13. reverseList \n");
		printf("    	  5. ListLength       14. RemoveNthFromEnd \n");
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
			 else printf("线性表第%d个元素为%d！\n",j,e);     
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
			 	ListTraverse(L);
			    putchar('\n'); 
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
			 	ListTraverse(L);
			    putchar('\n'); 
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(L==NULL) printf("线性表不存在！\n");
			 else  ListTraverse(L);
			getchar();getchar();
			 break;
		   case 13:
		   	if(ListEmpty(L)!=INFEASIBLE){
		   		L=reverseList(L);
		   		printf("反转后的线性表为：");
		   		ListTraverse(L);putchar('\n'); 
			   }
			   
		   	else printf("线性表不存在！\n");  
		   	
		   	getchar();getchar();
			 break;
		   case 14:
		   	
		   	printf("请输入n的值：");
		   	scanf("%d",&j);
		   	i=RemoveNthFromEnd(L,j);
		   	if(i!=OK) printf("删除失败！\n");  
		   	else{
		   		printf("删除链表的倒数第%d个结点后的线性表为：",j);
		   		ListTraverse(L);
			    putchar('\n'); 
			   }
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(L);
		   	if(L==NULL) printf("线性表不存在！\n");  
		   	else{
		   		printf("线性表元素排序成功！\n新线性表为："); 
			 	ListTraverse(L);
			    putchar('\n'); 
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("线性表不存在！对空表进行读文件操作！读得线性表为：\n");  
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	ListTraverse(L);
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
	LinkList L=NULL;  int op=1,op2=1,i,j,e,pre,next;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList         10. ListInsert \n");
		printf("    	  2. DestroyList      11. ListDelete \n");
		printf("    	  3. ClearList        12. ListTrabverse \n");
		printf("    	  4. ListEmpty        13. reverseList \n");
		printf("    	  5. ListLength       14. RemoveNthFromEnd \n");
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
			 else if(i==ERROR) printf("序号不合法！");  
			 else printf("线性表第%d个元素为%d！\n",j,e);     
			 getchar();getchar();
			 break;
		   case 7:
		   	printf("请输入要查找的元素：");
		   	 scanf("%d",&e);
		   	 i=LocateElem(L,e);
		   	 if(i==INFEASIBLE) printf("线性表不存在！\n");  
		   	 else if(i==ERROR) printf("查找失败"); 
			 else printf("线性表指定元素%d的逻辑序号为%d！\n",e,i);     
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
			 	ListTraverse(L);
			    putchar('\n'); 
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
			 	ListTraverse(L);
			    putchar('\n'); 
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(L==NULL) printf("线性表不存在！\n");
			 else  ListTraverse(L);
			getchar();getchar();
			 break;
		   case 13:
		   	if(ListEmpty(L)!=INFEASIBLE){
		   		L=reverseList(L);
		   		printf("反转后的线性表为：");
		   		ListTraverse(L);putchar('\n'); 
			   }
			   
		   	else printf("线性表不存在！\n");  
		   	
		   	getchar();getchar();
			 break;
		   case 14:
		   	
		   	printf("请输入n的值：");
		   	scanf("%d",&j);
		   	i=RemoveNthFromEnd(L,j);
		   	if(i!=OK) printf("删除失败！\n");  
		   	else{
		   		printf("删除链表的倒数第%d个结点后的线性表为：",j);
		   		ListTraverse(L);
			    putchar('\n'); 
			   }
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(L);
		   	if(L==NULL) printf("线性表不存在！\n");  
		   	else{
		   		printf("线性表元素排序成功！\n新线性表为："); 
			 	ListTraverse(L);
			    putchar('\n'); 
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("线性表不存在！对空表进行读文件操作！读得线性表为：\n");  
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	ListTraverse(L);
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
      					ListInsert(Lists.elem[Lists.length-1].L,ListLength(Lists.elem[Lists.length-1].L)+1,e);
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
