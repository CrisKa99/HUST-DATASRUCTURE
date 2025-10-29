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
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;
typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
     		  SqList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else{
		if(!L.length) return TRUE;
		else return FALSE;
	}

    /********** End **********/
}
status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	if(L.elem==NULL) return INFEASIBLE;
	else return L.length;

    /********** End **********/
}
status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
    // ������Ա��Ƿ�ǿ�
    if (L.length == 0) {
        return 0;
    }

    int maxSum = L.elem[0]; // ȫ������
    int currentSum = L.elem[0]; // ��ǰ�����������

    // �ӵڶ���Ԫ�ؿ�ʼ��������
    for (int i = 1; i < L.length; i++) {
        // ���µ�ǰ�����������
        currentSum = (currentSum > 0) ? currentSum + L.elem[i] : L.elem[i];
        
        // ����ȫ������
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    // ��������
    return maxSum;
}
#define MAX_SIZE 10001

int SubArrayNum(SqList L, int k) {
    // ������Ա��Ƿ�ǿ�
    if (L.length == 0) {
        return 0;
    }

    int count = 0; // ������
    int sum = 0; // ǰ׺��
    int prefixSum[MAX_SIZE] = {0}; // ���ڴ洢ǰ׺�ͼ�����ִ���

    // �������Ա�����ǰ׺��
    for (int i = 0; i < L.length; i++) {
        sum += L.elem[i];
        
        // ���ǰ׺�͵��� k��ֱ�ӽ���������һ
        if (sum == k) {
            count++;
        }
        
        // ���ǰ׺�ͼ�ȥ k ��ǰ׺�ͱ��д��ڣ���˵�����������������Ϊ k
        if (sum - k >= 0 && sum - k < MAX_SIZE) {
            count += prefixSum[sum - k];
        }
        
        // ����ǰ׺�ͱ�
        prefixSum[sum]++;
    }

    // ���ؽ��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
    /********** End **********/
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    // �������ﲹ����룬��ɱ�������
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
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    // �������ﲹ����룬��ɱ�������
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
		printf("    ��ѡ����Ĳ���[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:
			 
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
			 else if(j<=L.length) printf("���Ա��%d��Ԫ��Ϊ%d��\n",j,e);     
			 else printf("��ų���");
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
			 	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
     		 }   
			 getchar();getchar();
			 break;
		   case 11:
		   	printf("������Ҫ�����Ա���ɾ����Ԫ�أ�");
		   	 scanf("%d",&j);
		   	 i=ListDelete(L,j,e);
		   	 if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	 else if(i==ERROR) printf("���Ա�Ԫ��ɾ��ʧ�ܣ�\n"); 
			 else{
			 	printf("���Ա�Ԫ��ɾ���ɹ���\nɾ��Ԫ��Ϊ��%d\n�����Ա�Ϊ��",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			 }
			 getchar();getchar();
			 break;
		   case 12:
			 if(!ListTraverse(L)) printf("���Ա��ǿձ�\n");
			getchar();getchar();
			 break;
		   case 13:
		   	i=MaxSubArray(L);
		   	if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	else printf("���������������Ϊ��%d",i);
		   	getchar();getchar();
			 break;
		   case 14:
		   	printf("����������������ĺ�k��");
		   	scanf("%d",&j);
		   	i=SubArrayNum(L,j);
		   	if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	else printf("�����Ա��к�Ϊ%d������������ĸ���Ϊ��%d",j,i);
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(&L);
		   	if(L.elem==NULL) printf("���Ա����ڣ�\n");  
		   	else{
		   		printf("���Ա�Ԫ������ɹ���\n�����Ա�Ϊ��",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("���Ա����ڣ��Կձ���ж��ļ��������������Ա�Ϊ��\n"); 
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	
		    	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
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
			 else if(j<=L.length) printf("���Ա��%d��Ԫ��Ϊ%d��\n",j,e);     
			 else printf("��ų���");
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
			 	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
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
		   	if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	else printf("���������������Ϊ��%d",i);
		   	getchar();getchar();
			 break;
		   case 14:
		   	printf("����������������ĺ�k��");
		   	scanf("%d",&j);
		   	i=SubArrayNum(L,j);
		   	if(i==INFEASIBLE) printf("���Ա����ڣ�\n");  
		   	else printf("�����Ա��к�Ϊ%d������������ĸ���Ϊ��%d",j,i);
		   	getchar();getchar();
			 break;
		   case 15:
		   	sortList(&L);
		   	if(L.elem==NULL) printf("���Ա����ڣ�\n");  
		   	else{
		   		printf("���Ա�Ԫ������ɹ���\n�����Ա�Ϊ��",e); 
			 	for(i=0;i<L.length;i++)
        		printf("%d ",L.elem[i]);
			   }
			   getchar();getchar();
			 break;
		   case 16:
		    FILE *fp;
		    i=ListEmpty(L);
		    if(i==INFEASIBLE){
		    	printf("���Ա����ڣ��Կձ���ж��ļ��������������Ա�Ϊ��\n"); 
		    	LoadList(L,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    	
		    	for(i=0;i<L.length;i++)
        			printf("%d ",L.elem[i]);
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
      					ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
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
