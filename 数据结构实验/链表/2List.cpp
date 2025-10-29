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
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
     		  LinkList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;

status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	if (L==NULL){
		L=(LinkList )malloc(sizeof(LinkList));
		L->next=NULL;
		return OK; 
	}
	else return INFEASIBLE;
}
status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(L==NULL) return INFEASIBLE;
	else{
		if(L->next==NULL) return TRUE;
		else return FALSE;
	}
}
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
    // �������Ϊ�ջ�ֻ��һ���ڵ㣬�޷�ɾ��������n���ڵ�
    if (L == NULL || L->next == NULL) {
        return INFEASIBLE;
    }

    LinkList fast = L->next, slow = L->next;
    // ��ָ�����ƶ�n��
    for (int i = 0; i < n; i++) {
        if (fast == NULL) {
            return ERROR; // ������С��n��ɾ��ʧ��
        }
        fast = fast->next;
    }

    LinkList prev = NULL;
    // ����ָ��һ���ƶ���ֱ����ָ�뵽������β��
    while (fast != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next;
    }

    if (prev == NULL) {
        // ���Ҫɾ������ͷ�ڵ�
        LinkList temp = L->next;
        L->next = L->next->next;
        free(temp);
    } else {
        // ɾ���м��β���ڵ�
        prev->next = slow->next;
        free(slow);
    }
    return OK; // ɾ���ɹ�
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L= NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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
		printf("    ��ѡ����Ĳ���[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:
			 //printf("\n----IntiList���ܴ�ʵ�֣�\n");
			 
			 if(InitList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
		   case 2:
			 if(DestroyList(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else  printf("���Ա����ٳɹ���\n");
			 getchar();getchar();
			 break;
		   case 3:
			 if(ClearList(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else  printf("���Ա�ɾ���ɹ���\n");
			 getchar();getchar();
			 break;
	 	  case 4:
			 if(ListEmpty(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else if(ListEmpty(L)==TRUE) printf("���Ա��ж�Ϊ�գ�\n");
			 else  printf("���Ա��жϲ�Ϊ�գ�\n");
			 getchar();getchar();
			 break;
		   case 5:
		   	 i=ListLength(L); 
			 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");      
			 else printf("���Ա���Ϊ%d!\n",i);
			 getchar();getchar();
			 break;
		   case 6:
		   	 printf("������Ҫ��ȡ��Ԫ�ص���ţ�");
		   	 scanf("%d",&j);
		   	 i=GetElem(L,j,e); 
			 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");    
			 else printf("���Ա��%d��Ԫ��Ϊ%d��\n",j,e);     
			 getchar();getchar();
			 break;
		   case 7:
		   	printf("������Ҫ���ҵ�Ԫ�أ�");
		   	 scanf("%d",&e);
		   	 i=LocateElem(L,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("����ʧ��"); 
			 else printf("���Ա�ָ��%dԪ�ص��߼����Ϊ%d��\n",e,j);     
			 getchar();getchar();
			 break;
		   case 8:
		   	printf("������Ҫ��ȡǰ��Ԫ�ص�Ԫ�أ�");
		   	 scanf("%d",&e);
		   	 i=PriorElem(L,e,pre);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա��в�����ָ��Ԫ��%d��ǰ��Ԫ�أ�\n",e);  
			 else printf("���Ա���ָ��Ԫ��%d��ǰ��Ԫ��Ϊ%d��\n",e,pre);     
			 getchar();getchar();
			 break;
		   case 9:
		   	printf("������Ҫ��ȡ���Ԫ�ص�Ԫ�أ�");
			 scanf("%d",&e);
		   	 i=NextElem(L,e,next);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա��в�����ָ��Ԫ��%d�ĺ��Ԫ�أ�\n",e);  
			 else printf("���Ա���ָ��Ԫ��%d�ĺ��Ԫ��Ϊ%d��\n",e,next);     
			 getchar();getchar();
			 break;
		   case 10:
		   	printf("������Ҫ�����Ա��в���Ԫ�ص���ź�Ҫ�����Ԫ�أ�");
		   	 scanf("%d%d",&j,&e);
		   	 i=ListInsert(L,j,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա�Ԫ�ز���ʧ�ܣ�\n"); 
			 else{
			 	printf("���Ա�Ԫ�ز���ɹ���\n�����Ա�Ϊ��"); 
			 	ListTraverse(L);
			    putchar('\n'); 
     		 }   
			 getchar();getchar();
			 break;
		   case 11:
		   	printf("������Ҫ�����Ա���ɾ����Ԫ����ţ�");
		   	 scanf("%d",&j);
		   	 i=ListDelete(L,j,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա�Ԫ��ɾ��ʧ�ܣ�\n"); 
			 else{
			 	printf("���Ա�Ԫ��ɾ���ɹ���\nɾ��Ԫ��Ϊ��%d\n�����Ա�Ϊ��",e); 
			 	ListTraverse(L);
			    putchar('\n'); 
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(L==NULL) printf("���Ա����ڣ�\n");
			 else  ListTraverse(L);
			getchar();getchar();
			 break;
		   case 13:
		   	if(ListEmpty(L)!=INFEASIBLE){
		   		L=reverseList(L);
		   		printf("��ת������Ա�Ϊ��");
		   		ListTraverse(L);putchar('\n'); 
			   }
			   
		   	else printf("���Ա����ڣ�\n");  
		   	
		   	getchar();getchar();
			 break;
		   case 14:
		   	
		   	printf("������n��ֵ��");
		   	scanf("%d",&j);
		   	i=RemoveNthFromEnd(L,j);
		   	if(i!=OK) printf("ɾ��ʧ�ܣ�\n");  
		   	else{
		   		printf("ɾ������ĵ�����%d����������Ա�Ϊ��",j);
		   		ListTraverse(L);
			    putchar('\n'); 
			   }
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(L);
		   	if(L==NULL) printf("���Ա����ڣ�\n");  
		   	else{
		   		printf("���Ա�Ԫ������ɹ���\n�����Ա�Ϊ��"); 
			 	ListTraverse(L);
			    putchar('\n'); 
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("���Ա����ڣ��Կձ���ж��ļ��������������Ա�Ϊ��\n");  
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	ListTraverse(L);
			}
		    
			else{
				printf("���Ա��жϴ��ڣ������Ա����д�ļ�������\n");
				SaveList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
			}
			getchar();getchar();
			 break;
			case 0:
				break;
		}
	}
	printf("�Զ��ĵ������������\n");
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
		printf("    ��ѡ����Ĳ���[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:
			 //printf("\n----IntiList���ܴ�ʵ�֣�\n");
			 
			 if(InitList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
			 getchar();getchar();
			 break;
		   case 2:
			 if(DestroyList(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else  printf("���Ա����ٳɹ���\n");
			 getchar();getchar();
			 break;
		   case 3:
			 if(ClearList(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else  printf("���Ա�ɾ���ɹ���\n");
			 getchar();getchar();
			 break;
	 	  case 4:
			 if(ListEmpty(L)==INFEASIBLE) printf("���Ա����ڣ�\n");     
			 else if(ListEmpty(L)==TRUE) printf("���Ա��ж�Ϊ�գ�\n");
			 else  printf("���Ա��жϲ�Ϊ�գ�\n");
			 getchar();getchar();
			 break;
		   case 5:
		   	 i=ListLength(L); 
			 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");      
			 else printf("���Ա���Ϊ%d!\n",i);
			 getchar();getchar();
			 break;
		   case 6:
		   	 printf("������Ҫ��ȡ��Ԫ�ص���ţ�");
		   	 scanf("%d",&j);
		   	 i=GetElem(L,j,e); 
			 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
			 else if(i==ERROR) printf("��Ų��Ϸ���");  
			 else printf("���Ա��%d��Ԫ��Ϊ%d��\n",j,e);     
			 getchar();getchar();
			 break;
		   case 7:
		   	printf("������Ҫ���ҵ�Ԫ�أ�");
		   	 scanf("%d",&e);
		   	 i=LocateElem(L,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("����ʧ��"); 
			 else printf("���Ա�ָ��Ԫ��%d���߼����Ϊ%d��\n",e,i);     
			 getchar();getchar();
			 break;
		   case 8:
		   	printf("������Ҫ��ȡǰ��Ԫ�ص�Ԫ�أ�");
		   	 scanf("%d",&e);
		   	 i=PriorElem(L,e,pre);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա��в�����ָ��Ԫ��%d��ǰ��Ԫ�أ�\n",e);  
			 else printf("���Ա���ָ��Ԫ��%d��ǰ��Ԫ��Ϊ%d��\n",e,pre);     
			 getchar();getchar();
			 break;
		   case 9:
		   	printf("������Ҫ��ȡ���Ԫ�ص�Ԫ�أ�");
			 scanf("%d",&e);
		   	 i=NextElem(L,e,next);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա��в�����ָ��Ԫ��%d�ĺ��Ԫ�أ�\n",e);  
			 else printf("���Ա���ָ��Ԫ��%d�ĺ��Ԫ��Ϊ%d��\n",e,next);     
			 getchar();getchar();
			 break;
		   case 10:
		   	printf("������Ҫ�����Ա��в���Ԫ�ص���ź�Ҫ�����Ԫ�أ�");
		   	 scanf("%d%d",&j,&e);
		   	 i=ListInsert(L,j,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա�Ԫ�ز���ʧ�ܣ�\n"); 
			 else{
			 	printf("���Ա�Ԫ�ز���ɹ���\n�����Ա�Ϊ��"); 
			 	ListTraverse(L);
			    putchar('\n'); 
     		 }   
			 getchar();getchar();
			 break;
		   case 11:
		   	printf("������Ҫ�����Ա���ɾ����Ԫ����ţ�");
		   	 scanf("%d",&j);
		   	 i=ListDelete(L,j,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա�Ԫ��ɾ��ʧ�ܣ�\n"); 
			 else{
			 	printf("���Ա�Ԫ��ɾ���ɹ���\nɾ��Ԫ��Ϊ��%d\n�����Ա�Ϊ��",e); 
			 	ListTraverse(L);
			    putchar('\n'); 
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(L==NULL) printf("���Ա����ڣ�\n");
			 else  ListTraverse(L);
			getchar();getchar();
			 break;
		   case 13:
		   	if(ListEmpty(L)!=INFEASIBLE){
		   		L=reverseList(L);
		   		printf("��ת������Ա�Ϊ��");
		   		ListTraverse(L);putchar('\n'); 
			   }
			   
		   	else printf("���Ա����ڣ�\n");  
		   	
		   	getchar();getchar();
			 break;
		   case 14:
		   	
		   	printf("������n��ֵ��");
		   	scanf("%d",&j);
		   	i=RemoveNthFromEnd(L,j);
		   	if(i!=OK) printf("ɾ��ʧ�ܣ�\n");  
		   	else{
		   		printf("ɾ������ĵ�����%d����������Ա�Ϊ��",j);
		   		ListTraverse(L);
			    putchar('\n'); 
			   }
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(L);
		   	if(L==NULL) printf("���Ա����ڣ�\n");  
		   	else{
		   		printf("���Ա�Ԫ������ɹ���\n�����Ա�Ϊ��"); 
			 	ListTraverse(L);
			    putchar('\n'); 
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("���Ա����ڣ��Կձ���ж��ļ��������������Ա�Ϊ��\n");  
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	ListTraverse(L);
			}
			else{
				printf("���Ա��жϴ��ڣ������Ա����д�ļ�������\n");
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
				 printf("    ��ѡ����Ĳ���[0~3]:");
			     scanf("%d",&op2);
			     char name[30];
			     switch(op2){
		     	case 1:
		     		int n,e;
		     		printf("������Ҫ��ӵ����Ա�ĸ�����");
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
   					printf("��Ӻ�Ķ����Ա�Ϊ��");
   					for(n=0;n<Lists.length;n++)
   					{
   						printf("%s ",Lists.elem[n].name);
   						ListTraverse(Lists.elem[n].L);
   						putchar('\n');
   					}
   					getchar();getchar();
			 		break;
			 	case 2: 
			 		printf("������Ҫɾ�������Ա�����֣�");
			 		scanf("%s",name);
				   if (RemoveList(Lists,name)==OK){
				   		printf("ɾ��������Ա�Ϊ��\n");
					   for(n=0;n<Lists.length;n++)
				   		{
				   			printf("%s ",Lists.elem[n].name);
				   			ListTraverse(Lists.elem[n].L);
				        	putchar('\n');
				   		}
				   		}
				   else printf("ɾ��ʧ��");
		    		getchar();getchar();
			 break;
				case 3:
					printf("������Ҫ���ҵ����Ա�����֣�");
					 scanf("%s",name);
				   if (n=LocateList(Lists,name))
				   		{
				   			printf("%s ",Lists.elem[n-1].name);
				   			ListTraverse(Lists.elem[n-1].L);
				   			printf("\n�Ƿ�����鵽�����Ա���е����������Y or N��\n");
				         	char c;getchar();
				         	scanf("%c",&c);
							if(c=='Y') singleListOperation(Lists.elem[n-1].L); 
				         putchar('\n');
				   		}
				   else printf("����ʧ��");
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
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}
