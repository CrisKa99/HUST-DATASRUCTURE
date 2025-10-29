#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define REPEATED -3
#define MAX_BiTree_SIZE 1000
#define LIST_INIT_SIZE 50
#define NAMESIZE 50
#define LISTINCREMENT 10
typedef int status;
typedef int KeyType; 
typedef struct {
	KeyType  key;
	char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode{  //����������Ķ���
	TElemType  data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
typedef struct Stack{
	BiTree list[MAX_BiTree_SIZE];
	int top;
}Stack;
typedef struct{
	char name[NAMESIZE];
	BiTree root;
}NamedBiTree;//�����ƶ������Ķ���
typedef NamedBiTree ListElem;
typedef struct{  //��������������
	ListElem* elem;
	int length;
	int listsize;
}List;
//���������� 
void visit(BiTree T);//���ʽ�� 
status keycheck(TElemType definition[]){
	for(int i=0;definition[i].key!=-1;i++){
		if(definition[i].key==0) continue;
		for(int j=i+1;definition[j].key!=-1;j++){
			if(definition[i].key==definition[j].key) return ERROR;
		}
	}
	return OK;
}
status CreateBiTree1(BiTree &T, TElemType definition[])
{
	if(keycheck(definition)==ERROR) return ERROR;
	static int i = 0;
	if(definition[0].key==0) return OK;
	TElemType ch = definition[i];
	if (ch.key == -1) {
		T = NULL;
		return OK;
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	if (!T) {
		exit(OVERFLOW);
	}
	T->data = ch;
	T->lchild = NULL;
	T->rchild = NULL;
	i++;
	if (definition[i].key != 0) {
		
		CreateBiTree1(T->lchild, definition);
	}
	i++;
	if (definition[i].key != 0) {
		
		CreateBiTree1(T->rchild, definition);
	}
	return OK;
}

status CreateBiTree2(BiTree &T, TElemType preOrder[], TElemType inOrder[], 
int preStart, int preEnd, int inStart, int inEnd) {
	if (preStart > preEnd || inStart > inEnd) { 
		T = NULL;
		return OK;
	}
	
	// �������ڵ㣬����ǰ��������еĵ�һ��Ԫ��ȷ��
	T = (BiTree)malloc(sizeof(BiTNode));
	if (!T) {
		exit(OVERFLOW);
	}
	T->data = preOrder[preStart];
	T->lchild = NULL;
	T->rchild = NULL;
	
	// ����������������ҵ����ڵ��λ��
	int rootIndex;
	for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
		if (inOrder[rootIndex].key == preOrder[preStart].key) {
			break;
		}
	}
	
	// �������ĳ���
	int leftLength = rootIndex - inStart;
	
	// �ݹ鹹��������
	CreateBiTree2(T->lchild, preOrder, inOrder, preStart + 1, preStart + 
	leftLength, inStart, rootIndex - 1);
	
	// �ݹ鹹��������
	CreateBiTree2(T->rchild, preOrder, inOrder, preStart + leftLength +
	 1, preEnd, rootIndex + 1, inEnd);
	
	return OK;
}

status CreateBiTree3(BiTree &T, TElemType inOrder[], TElemType postOrder[],
 int inStart, int inEnd, int postStart, int postEnd) {
	if (inStart == inEnd && postStart == postEnd) {
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T) {
			exit(OVERFLOW);
		}
		T->data = postOrder[postEnd]; 
		// ��ǰ�ڵ�ΪҶ�ӽڵ㣬ֱ��ʹ�ú������е����һ��Ԫ����Ϊ�ڵ�����
		T->lchild = NULL;
		T->rchild = NULL;
		return OK;
	}
	
	if (inStart > inEnd || postStart > postEnd ||
	 (inEnd - inStart) != (postEnd - postStart)) {
		T = NULL;
		return OK;
	}
	
	// �ں����������ҵ����ڵ�
	TElemType root = postOrder[postEnd];
	
	// �������������ҵ����ڵ��λ��
	int rootIndex;
	for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
		if (inOrder[rootIndex].key == root.key) {
			break;
		}
	}
	
	// �������ڵ�
	T = (BiTree)malloc(sizeof(BiTNode));
	if (!T) {
		exit(OVERFLOW);
	}
	T->data = root;
	T->lchild = NULL;
	T->rchild = NULL;
	
	// �������������������Ĵ�С
	int leftTreeSize = rootIndex - inStart;
	int rightTreeSize = inEnd - rootIndex;
	
	// �ݹ�ع�����������������
	if (leftTreeSize > 0) {
		CreateBiTree3(T->lchild, inOrder, postOrder, inStart, 
		rootIndex - 1, postStart, postStart + leftTreeSize - 1);
	}
	if (rightTreeSize > 0) {
		CreateBiTree3(T->rchild, inOrder, postOrder, rootIndex + 1,
		 inEnd, postStart + leftTreeSize, postEnd - 1);
	}
	
	return OK;
}

status CreateBiTree(BiTree &T,TElemType definition[]); 
status isRepeat(TElemType definition[]);
status checkedCreateBiTree(BiTree &T,TElemType definition[], int &i);
status DestroyBiTree(BiTree &T); 
status ClearBiTree(BiTree &T); 
int BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
BiTNode* FatherNode(BiTree &T, KeyType e, int &i);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)); 
void filePreTraverse(BiTree T, FILE *fp);
status SaveBiTree(BiTree T, char FileName[]);
void filePreCreateBiTree(BiTree &T, FILE *fp);
status LoadBiTree(BiTree &T,  char FileName[]);
int MaxPathSum(BiTree &T);
status InvertTree(BiTree &T);
BiTNode* LowestCommonAncestor(BiTree &T, KeyType e1, KeyType e2);
status findAncestors(BiTree T, KeyType e, Stack &stack);
void SingleTree_Operation(BiTree &T);
status InitList(List &L);
status EnterTree(List &TreesList, char TreeName[NAMESIZE]);
status AddTree(List &TreesList, char TreeName[NAMESIZE]);
status RemoveTree(List &TreesList, char TreeName[NAMESIZE]);
int LocateTree(List &TreesList, char TreeName[NAMESIZE]);
//������ 
int main(void){
	BiTree T = NULL;
	int op=1, reValue, i;
	char FileName[NAMESIZE], c, TreeName[NAMESIZE];
	List TreesList;
	InitList(TreesList);//���������������
	void(*pvisit)(BiTree) = visit;//���ʽ�㺯����ָ�� 
	while(op){
		system("cls");//����
		printf("\n\n");
		printf("   �����������˵�: \n");
		printf("------------------------------------------------------------------\n");
		printf("1. SingleTree_Operation	 2. EnterTreeByName	3. TreesTraverse\n");
		printf("    	4. ListLength	  	 5. AddTree		6. RemoveTree\n");
		printf("    	7. LocateTreeByName      0. Exit\n");
		printf("-----------------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~8]:");		
		scanf("%d",&op);
		switch(op){
			case 1:{
				SingleTree_Operation(T);
				break;
			}
			case 2:{
				printf("����������Ҫ�����ٿصĶ������ڹ�����е����ƣ�");
				scanf("%s", &TreeName);
				reValue = EnterTree(TreesList, TreeName);
				if(reValue == ERROR) printf("�����ڸö�������\n");
				break;
			} 
			case 3:{
				if(TreesList.length==0) {
					printf("�����Ϊ�գ��޶������ɹ�������\n");
					break;
				}
				for(int i=0; i<TreesList.length; i++){
					printf("\n���Ϊ%d, ����Ϊ%s�Ķ�����", i+1, TreesList.elem[i].name);
					if(TreesList.elem[i].root==NULL){//�ն������������ 
						printf("Ϊ������");
						continue;
					}
					printf("\nǰ�������");PreOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n���������");InOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n���������");PostOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n���������");LevelOrderTraverse(TreesList.elem[i].root, pvisit);
				}
				printf("\n���ж�����������ɣ�\n");
				break;
			}
			case 4:
			printf("����������������%d����������\n", TreesList.length);
			break;
			case 5:
			printf("��������Ҫ���ӵĶ����������ƣ�");
			scanf("%s", TreeName);
			reValue = AddTree(TreesList, TreeName);//���Ӷ����� 
			if(reValue == OK) printf("���Ӷ������ɹ���\n");
			else if(reValue == REPEATED) printf("�Ѵ���ͬ�����������޷���ӣ�\n"); 
			else printf("���Ӷ��������ִ���\n");
			break;
			case 6:
			printf("��������Ҫɾ���Ķ����������ƣ�");
			scanf("%s", TreeName);
			reValue = RemoveTree(TreesList, TreeName);
			if(reValue == OK)printf("ɾ���������ɹ���\n");
			else printf("�����ڸö�������ɾ��������ʧ��!\n");
			break;
			case 7:
			printf("��������Ҫ���ҵĶ����������ƣ�");
			scanf("%s", TreeName);
			reValue = LocateTree(TreesList, TreeName);
			if(reValue == 0)printf("�����ҵĶ����������ڣ�\n");
			else printf("����Ϊ%s�Ķ������ڶ����Ա����ǵ�%d����\n", TreeName, reValue);
			break;
			case 0:
			break;
		}//end of switch
		getchar();getchar();//���������ַ���س�����ѭ�� 
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}

//�����Ķ��� 
void visit(BiTree T)//���ʽ�� 
{
	printf(" %d,%s",T->data.key,T->data.others);
}
status CreateBiTree(BiTree &T,TElemType definition[])
{
	if(T) return INFEASIBLE; 
	int reValue = isRepeat(definition);
	if(reValue) return ERROR;	
	int i = 0;
	checkedCreateBiTree(T, definition, i);
	return OK;
}
status isRepeat(TElemType definition[])// �����Ƿ�����ظ��ؼ��� 
{
	int i = 0, j;
	for(; definition[i].key!=-1; i++){
		if(definition[i].key==0)continue;// �ؼ���Ϊ0������ս�㣬ֱ������ 
		for(j=i+1; definition[j].key!=-1; j++){
			if(definition[j].key==definition[i].key)return TRUE;// �����ظ��ؼ��� 
		}
	}
	return FALSE;
}
status checkedCreateBiTree(BiTree &T, TElemType definition[], int &i)
{
	if(definition[i].key==0){
		T = NULL;
		i++;
	}
	else{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data.key = definition[i].key;
		strcpy(T->data.others, definition[i].others);
		i++;
		checkedCreateBiTree(T->lchild, definition, i);
		checkedCreateBiTree(T->rchild, definition, i);
	}   
	return OK;
}
status DestroyBiTree(BiTree &T){
	if(T==NULL) return OK;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	return OK;
}

status ClearBiTree(BiTree &T){
	if(T == NULL){
		return OK;
	}
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	T=NULL;
	return OK;
}
int BiTreeEmpty(BiTree T)
{
	if(T) return FALSE;
	else return TRUE;
}
int BiTreeDepth(BiTree T)
//�������T�����
{
	if(!T) return 0;
	int d=0,dr=0,dl=0;
	dl=BiTreeDepth(T->lchild);
	dr=BiTreeDepth(T->rchild);
	d=dl>dr?dl:dr;
	return d+1;
}
BiTNode* LocateNode(BiTree T,KeyType e){
	if(T==NULL) return NULL;
	if(T->data.key==e) return T;
	if(LocateNode(T->lchild,e)==NULL){
		if(LocateNode(T->rchild,e)!=NULL) return T->rchild;
	}
	else return T->lchild;
	return NULL;
}
status Assign(BiTree &T,KeyType e,TElemType value)
//ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
{
	if(LocateNode(T,value.key)&&(value.key!=e)) return ERROR;
	BiTree p=LocateNode(T,e);
	if(p)
	{
		p->data=value;
		return OK;
	}    
	return ERROR;
}
BiTNode* GetSibling(BiTree T,KeyType e){
	if(T == NULL || T->lchild == NULL || T->rchild == NULL) return NULL;
	BiTree parent=T;
	if(parent->lchild->data.key==e) return parent->rchild;
	if(parent->rchild->data.key==e) return parent->lchild;
	if(GetSibling(parent->lchild,e)==NULL){
		if(GetSibling(parent->rchild,e)!=NULL) return GetSibling(parent->rchild,e);
	}
	else return GetSibling(parent->lchild,e);
	return NULL;
}
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c){
	if (T == NULL)
	{
		BiTree neww = (BiTNode *)malloc(sizeof(BiTNode));
		neww->data.key = c.key;
		strcpy(neww->data.others, c.others);
		neww->lchild = NULL;
		neww->rchild = NULL;
		T = neww;
		return OK;
	}
	// ����Ƿ������ͬ�ؼ��ֵĽ��
	if (LocateNode(T, c.key) != NULL)
	{
		return ERROR; // ������ͬ�ؼ��ֵĽ�㣬����ERROR
	}
	BiTree IT = LocateNode(T, e);
	if (IT == NULL)
	{
		return ERROR;
	}
	BiTree neww = (BiTNode *)malloc(sizeof(BiTNode));
	neww->data.key = c.key;
	strcpy(neww->data.others, c.others);
	neww->lchild = NULL;
	neww->rchild = NULL;
	if (LR == 0)
	{
		neww->rchild = IT->lchild;
		IT->lchild = neww;
		return OK;
	}
	else if (LR == 1)
	{
		neww->rchild = IT->rchild;
		IT->rchild = neww;
		return OK;
	}
	else if (LR == -1)
	{
		neww->rchild = T;
		T = neww;
		return OK;
	}
	return ERROR;
	
	/********** End **********/
}

BiTNode* FatherNode(BiTree &T, KeyType e, int &i)// Ѱ�ҽ��e��˫�׽��
// i����ֵΪ0����e�����ӣ�i����ֵΪ1����e���Һ��ӷ���1��-1��������  
{
	if(!T || T->data.key==e){// TΪ����������Ϊeʱ�����e��˫�׽��
		i = -1;
		return NULL;
	}
	// ���Һ����Ƿ�Ϊ���e 
	if(T->lchild && T->lchild->data.key==e){
		i = 0;
		return T;
	}
	if(T->rchild && T->rchild->data.key==e){
		i = 1;
		return T;
	}
	// ���Һ��Ӿ���Ϊ���e���������������������� 
	BiTNode* tmp;
	tmp = FatherNode(T->lchild, e, i);
	if(tmp) return tmp;
	tmp = FatherNode(T->rchild, e, i);
	if(tmp) return tmp;
	//���������о�û�������������ؿ�ָ�� 
	return NULL;
}
status DeleteNode(BiTree &T, KeyType e)//ɾ����㣺���Բ����Ҹ���� 
{
	if(!T) return INFEASIBLE;
	BiTNode *tmp = LocateNode(T, e), *father;
	int i = -1;
	if(!tmp) return ERROR;// û���ҵ��ؼ���Ϊe�Ľ�㣬�޷�ɾ�������������� 
	father = FatherNode(T, e, i);
	if(!tmp->lchild && !tmp->rchild){// 
		if(i==-1 && T==tmp) T = NULL;// 
		else if(father && i!=-1){
			if(i==0) father->lchild = NULL;
			else if(i==1) father->rchild = NULL;
		}
		free(tmp);
	}
	else if(tmp->lchild && tmp->rchild){//�ؼ���Ϊe�Ľ���Ϊ2
		BiTNode* LCrTree;
		if(T==tmp){
			T = tmp->lchild;
			LCrTree = tmp->lchild;
			while(LCrTree->rchild) LCrTree = LCrTree->rchild;
			LCrTree->rchild = tmp->rchild;
		}
		else if(father && i!=-1){//�ؼ���Ϊe�Ľ�㲻�Ǹ���� 
			
			if(i==0) father->lchild = tmp->lchild;
			else if(i==1) father->rchild = tmp->lchild;
			LCrTree = tmp->lchild;
			while(LCrTree->rchild) LCrTree = LCrTree->rchild;// �ҵ��Һ���Ϊ�յĽ�� 
			LCrTree->rchild = tmp->rchild;
		}
		free(tmp);
	}
	else if(tmp->lchild){// ���ӽ��ǿգ��Һ��ӽ��Ϊ�� 
		if(T==tmp)// �ؼ���Ϊe�Ľ���Ǹ���� 
		T = tmp->lchild;//��e�����������汻ɾ����eλ��
		else if(father && i!=-1){//�ؼ���Ϊe�Ľ�㲻�Ǹ���� 
			if(i==0) father->lchild = tmp->lchild;
			else if(i==1) father->rchild = tmp->lchild;
		}
		free(tmp);
	} 
	else if(tmp->rchild){
		if(T==tmp)
		T = tmp->rchild;
		else if(father && i!=-1){
			if(i==0) father->lchild = tmp->rchild;
			else if(i==1) father->rchild = tmp->rchild;
		}
		free(tmp);
	} 
	return OK;
}
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))//�������������T
{
	if(!T) return OK;
	visit(T);
	PreOrderTraverse(T->lchild, visit);
	PreOrderTraverse(T->rchild, visit);
	return OK;
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))//�������������T
{
	BiTree stack[MAX_BiTree_SIZE];
	int top = 0;
	stack[top++] = T;
	while(top){
		T = stack[top-1];
		while(T){
			T = T->lchild;
			stack[top++] = T;
		}
		top--;
		if(top){
			T = stack[--top]; 
			visit(T); 
			stack[top++]=T->rchild; 
		}
	}
	return OK; 
}
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))//�������������T
{
	BiTree stack[MAX_BiTree_SIZE];
	int top = 0;
	stack[top++] = T;
	while(top){
		T = stack[top-1];
		while(T){
			T = T->lchild;
			stack[top++] = T;
		}
		top--;
		if(top){
			T = stack[top-1];
			if(T->rchild==NULL){
				do{
					T = stack[--top];
					
				}while(top && (T == stack[top-1]->rchild));
			}
			if(top){
				stack[top] = stack[top-1]->rchild;
				top++;
			}
		}
	}
	return OK; 
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) 
{ 
	BiTree Queue[MAX_BiTree_SIZE]; 
	int front=0, rear=0; 
	if(T) Queue[rear++]=T; 
	while(front != rear) 
	{ 
		T=Queue[front]; 
		front=(front+1) % MAX_BiTree_SIZE; 
		visit(T); 
		if(T->lchild) {
			Queue[rear]=T->lchild;
			rear=(rear+1) % MAX_BiTree_SIZE; 
		}
		if(T->rchild) {
			Queue[rear]=T->rchild; 
			rear=(rear+1) % MAX_BiTree_SIZE; 
		}
	} 
	return OK; 
}
void filePreTraverse(BiTree T, FILE *fp)
{
	if(T==NULL) fprintf(fp, "0,null ");
	else {
		fprintf(fp, "%d,%s ",T->data.key,T->data.others);
		filePreTraverse(T->lchild, fp);
		filePreTraverse(T->rchild, fp);
	}
}
status SaveBiTree(BiTree T, char FileName[])
{
	if(!T) return OK;
	FILE * fp;
	if((fp=fopen(FileName,"wb"))==NULL){     
		return ERROR;
	}
	filePreTraverse(T, fp);
	fclose(fp); 
	return OK;
}
void filePreCreateBiTree(BiTree &T, FILE *fp)//������������������������ļ��� 
{
	int tmpkey, reValue;
	char tmpOthers[50];
	reValue = fscanf(fp, "%d,%s ", &tmpkey, tmpOthers);// ��ȡ����
	if(reValue){
		if(tmpkey==0) T = NULL;
		else{
			if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);//���ɸ����
			T->data.key = tmpkey;//Ϊ����㸳ֵ 
			strcpy(T->data.others, tmpOthers);
			filePreCreateBiTree(T->lchild, fp);//����������
			filePreCreateBiTree(T->rchild, fp);//����������
		}
	}
}
status LoadBiTree(BiTree &T, char FileName[])//��ȡ�ļ��еĶ����� 
{
	if(T) return INFEASIBLE;//�������Ѵ��� 
	FILE * fp;
	if((fp=fopen(FileName,"rb"))==NULL){     
		return ERROR;// �ļ���ʧ��
	}
	filePreCreateBiTree(T, fp);
	fclose(fp);  // �ر��ļ����
	return OK;// ������� 
}
int MaxPathSum(BiTree &T)//���ظ��ڵ㵽Ҷ�ӽ������·����
{
	if(!T) return 0;
	int lSum = MaxPathSum(T->lchild), rSum = MaxPathSum(T->rchild);
	if(lSum>rSum) return lSum+T->data.key;
	else return rSum+T->data.key;
}
status InvertTree(BiTree &T)
{
	if(!T) return OK;
	BiTNode *tmp;
	tmp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = tmp;
	InvertTree(T->lchild);
	InvertTree(T->rchild);
	return OK;
}
status findAncestors(BiTree T, KeyType e, Stack &stack)
{
	stack.top = 0;
	stack.list[stack.top++] = T;
	while(stack.top){
		T = stack.list[stack.top-1];
		while(T){
			T = T->lchild;
			stack.list[stack.top++] = T;
		}
		stack.top--;
		if(stack.top){
			T = stack.list[stack.top-1];
			if(T->rchild==NULL){
				do{
					T = stack.list[--stack.top];
					if(T->data.key==e){
						stack.list[stack.top++] = T;
						return OK;
					}
					
				}while(stack.top && (T == stack.list[stack.top-1]->rchild));
			}
			if(stack.top){
				stack.list[stack.top] = stack.list[stack.top-1]->rchild;
				stack.top++;
			}
		}
	}
	return ERROR;
} 
BiTNode* LowestCommonAncestor(BiTree &T, KeyType e1, KeyType e2)//�����������
{
	Stack s1, s2;//Ϊe1��e2��������ָ��ջ 
	if(findAncestors(T, e1, s1)==ERROR || findAncestors(T, e2, s2)==ERROR)
	return NULL; 
	int i = 0, top = (s1.top>s2.top)?s2.top:s1.top;
	for(i=0;i<top && (s1.list[i]->data.key == s2.list[i]->data.key);i++);
	return s2.list[i-1];
}
void SingleTree_Operation(BiTree &T){
	int op=1, reValue, i;
	KeyType e;
	char FileName[NAMESIZE], c;
	while(op){
		system("cls");//����
		printf("\n\n");
		printf("   ���������������˵�: \n");
		printf("------------------------------------------------------------\n");
		printf("    1. CreateBiTree			2. DestroyBiTree  		3. ClearBiTree\n");
		printf("    4. BiTreeEmpty			5. BiTreeDepth		6. LocateNode\n");
		printf("    7. Assign 			8. GetSibling		9. InsertNode\n");
		printf("    10.DeleteNode			11.PreOrderTraverse  12.InOrderTraverse\n");
		printf("    13.PostOrderTraverse	14.LevelOrderTraverse	15.MaxPathSum\n");
		printf("    16.LowestCommonAncestor 	17.InvertTree		18.SaveBiTree\n");
		printf("    19.LoadBiTree			0. Return��\n");
		printf("------------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~17]:");		
		scanf("%d",&op);
		switch(op){
			case 1:{
				if(T) {
					printf("�������ǿգ��������٣�\n");
					break;
				}
				TElemType definition[100],preOrder[100],inOrder[100],postOrder[100];
				int i = 0,j=0; 
				printf("������������Ķ��壨1����ǰ���������2��ǰ��+���򣻣�3������+����");
				int op3,ans;	
				scanf("%d",&op3); 
				switch(op3){
					case 1:{
						do {
							scanf("%d%s",&definition[i].key,definition[i].others);
						} while (definition[i++].key!=-1);
						ans=CreateBiTree1(T,definition);break;}
					case 2:{
						do {
							scanf("%d%s",&preOrder[i].key,preOrder[i].others);
						} while (preOrder[i++].key!=-1);
						do {
							scanf("%d%s",&inOrder[j].key,inOrder[j].others);
						} while (inOrder[j++].key!=-1);
						ans = CreateBiTree2(T, preOrder, inOrder, 0, i - 2, 0, j - 2);break;}
					case 3:{
						do {
							scanf("%d%s",&postOrder[i].key,postOrder[i].others);
						} while (postOrder[i++].key!=-1);
						do {
							scanf("%d%s",&inOrder[j].key,inOrder[j].others);
						} while (inOrder[j++].key!=-1);
						ans = CreateBiTree3(T, inOrder, postOrder, 0, i - 2, 0, j - 2);break;	
				}}
				if (ans==OK) printf("�����������ɹ�");else printf("�ؼ��ֲ�Ψһ");
				getchar();getchar();
				break;
			}
			case 2: 
			reValue = DestroyBiTree(T);
			if(reValue == OK) printf("���������ٳɹ���\n");
			else if(reValue == INFEASIBLE) printf("������Ϊ�գ�\n");
			break;
			case 3:
			reValue = ClearBiTree(T);
			if(reValue == OK) printf("���������ٳɹ���\n");
			else if(reValue == INFEASIBLE) printf("������Ϊ�գ�\n");
			break;
			case 4:
			reValue = BiTreeEmpty(T);
			if(reValue == TRUE) printf("������Ϊ�ա�\n");
			else if(reValue == FALSE) printf("�������ǿա�\n");
			break;
			case 5:
			reValue = BiTreeDepth(T);
			if(reValue == 0) printf("������Ϊ�գ����Ϊ0��\n");
			else printf("���������Ϊ%d��\n", reValue);
			break;
			case 6:{	
				printf("��������Ҫ��ȡ�Ľ��Ĺؼ��֣�");
				scanf("%d", &e);
				BiTNode *pNode = LocateNode(T, e);
				if(!pNode) printf("����ʧ�ܣ��������в����ڹؼ���Ϊ%d�Ľ�㣡\n", e);
				else printf("�������йؼ���Ϊ%d�Ľ������Ϊ%s��\n", e, pNode->data.others);
				break;
			}
			case 7:{
				TElemType value;
				printf("��������Ҫ��ֵ�Ľ��Ĺؼ��֣�");
				scanf("%d", &e);
				printf("��������Ҫ��ֵ�Ľ����¹ؼ��֣�");
				scanf("%d", &value.key);
				printf("��������Ҫ��ֵ�Ľ��������ƣ�");
				scanf("%s", value.others);
				reValue = Assign(T, e, value);
				if(reValue == INFEASIBLE) 
				printf("������Ϊ�գ���ֵʧ�ܣ�\n");
				else if(reValue == ERROR) 
				printf("�������в����ڹؼ���Ϊ%d�Ľ�㣬��ֵʧ�ܣ�\n", e);
				else if(reValue == REPEATED) 
				printf("���������Ѿ����ڹؼ���Ϊ%d�Ľ�㣬��ֵʧ�ܣ�\n", value.key);
				else  printf("��ֵ�ɹ���\n");
				break;
			}
			case 8:{
				printf("��������Ҫ�����ֵܵĽ��ؼ��֣�");
				scanf("%d", &e);
				BiTNode *pNode = GetSibling(T,e);
				if(!pNode) printf("����ʧ�ܣ��������в����ڸ�Ԫ�ص��ֵܣ�\n");
				else printf("�������йؼ���Ϊ%d���ֵܽ���ǣ�����Ϊ%s���ؼ���Ϊ%d�Ľ�㡣\n", e, pNode->data.others, pNode->data.key);
				break;
			}
			case 9:{
				TElemType value;
				int LR; 
				scanf("%d", &LR);
				if(LR!=-1){
					printf("���������λ�õĽ��ؼ���e��");
					scanf("%d", &e);
				}
				else e=0;//LRΪ-1��ʱ��e����ȡ�κ�ֵ(û������)����ֵΪ0 
				printf("��������Ҫ������Ľ��ؼ��֣�");
				scanf("%d", &value.key);
				printf("��������Ҫ������Ľ�����ƣ�");
				scanf("%s", value.others);
				reValue = InsertNode(T, e, LR, value);
				if(reValue == INFEASIBLE) printf("������Ϊ�գ�����ʧ�ܣ�\n");
				else if(reValue == ERROR) 
				printf("�������в����ڹؼ���Ϊ%d�Ľ�㣬����ʧ�ܣ�\n", e);
				else if(reValue == REPEATED) 
				printf("���������Ѿ����ڹؼ���Ϊ%d�Ľ�㣬����ʧ�ܣ�\n", value.key);
				else  printf("����ɹ���\n");
				break;
			}
			case 10:
			printf("��������Ҫɾ���Ľ��ؼ��֣�");
			scanf("%d", &e);
			reValue = DeleteNode(T,  e);//ɾ�����
			if(reValue == INFEASIBLE) 
			printf("������Ϊ�գ�ɾ��ʧ�ܣ�\n");
			else if(reValue == ERROR) 
			printf("�������в����ڹؼ���Ϊ%d�Ľ�㣬ɾ��ʧ�ܣ�\n", e);
			else printf("ɾ���ɹ���\n");
			break;
			case 11:{
				if(!T) printf("������Ϊ�գ�\n");
				else {
					printf("��������ȫ���������������£�\n");
					PreOrderTraverse(T, visit);//�������������T
					printf("������ɣ�\n");
				}
				break;
			}
			case 12:{
				if(!T) printf("������Ϊ�գ�\n");
				else {
					printf("��������ȫ���������������£�\n");
					InOrderTraverse(T, visit);//�������������T
					printf("������ɣ�\n");
				}
				break;
			}
			case 13:{
				if(!T) printf("������Ϊ�գ�\n");
				else {
					printf("��������ȫ��������������£�\n");
					PostOrderTraverse(T, visit);//�������������T
					printf("������ɣ�\n");
				}
				break;
			} 
			case 14:{
				if(!T) printf("������Ϊ�գ�\n");
				else {
					printf("��������ȫ��������������£�\n");
					LevelOrderTraverse(T, visit);//�������������T
					printf("������ɣ�\n");
				}
				break;
			} 
			case 15:{
				if(!T)
				printf("������Ϊ������\n");
				else//���㲢������ڵ㵽Ҷ�ӽ������·����
				printf("�������ĸ��ڵ㵽Ҷ�ӽ������·����Ϊ%d", MaxPathSum(T));
				break;
			}	
			case 16:{
				int e1, e2;
				printf("����������ҹ������ȵ��������Ĺؼ��֣��Կո������Իس���β����");
				scanf("%d %d", &e1, &e2);
				if(!T){
					printf("������Ϊ������\n");
				}
				else{
					BiTNode* tmp = LowestCommonAncestor(T, e1, e2);//���������������
					if(!tmp){
						printf("û���ҵ�����������ȣ���㲻�����ڶ������У�\n");
						break;
					}
					else printf("������������ǹؼ���Ϊ%d�Ľ�㣬����Ϊ%s��\n", tmp->data.key, tmp->data.others);
				}
				break;
			}
			case 17:{
				if(!T)
				printf("������Ϊ������\n");
				else{
					InvertTree(T);//���нڵ�����ҽڵ㻥��
					printf("��ת�ɹ���\n");
				}
				break;
			}
			case 18:{
				if(!T) printf("������Ϊ������\n");
				else{
					
					reValue = SaveBiTree(T, "C:\\Users\\lenovo\\Desktop\\listfile.txt");
					if(reValue == ERROR) printf("�ļ���ʧ�ܣ�\n");
					else {
						printf("�洢�������ɹ���\n");
					}
				}
				break;
			}
			case 19:{
				
				reValue = LoadBiTree(T, "C:\\Users\\lenovo\\Desktop\\listfile.txt");
				if(reValue == INFEASIBLE) printf("�������Ѿ����ڣ����ɸ��� ��\n");
				else if(reValue == ERROR) printf("�ļ���ʧ�ܣ�\n");
				else {
					printf("��ȡ�������ɹ���\n");
				}
				break;
			}
			case 0:
			return;
		}//end of switch
		getchar();getchar();//���������ַ����� 
	}//end of while
	return;
}
status InitList(List &L)//���������Ա�����
{
	L.elem=(ListElem*)malloc(sizeof(ListElem)*LIST_INIT_SIZE);
	L.listsize=LIST_INIT_SIZE;// ���ÿռ�����ΪĬ�ϳ�ʼ��ֵ
	L.length=0;// Ԫ�ظ�����ʼֵΪ0   
	if (L.elem == NULL)
	return OVERFLOW;  // �ڴ����ʧ��
	for(int i=0; i<LIST_INIT_SIZE; i++)
	L.elem[i].root = NULL;// ��Ϊ��ָ�룬����Ұָ��ĳ��ֵ��·Ƿ����� 
	return OK;
}
status EnterTree(List &TreesList, char TreeName[NAMESIZE])//�ٿ��ض����ƵĶ����� 
{
	for(int i=0; i<TreesList.length; i++){
		if(strcmp(TreeName, TreesList.elem[i].name)==0){
			printf("�㼴����������Ϊ%s�Ķ�������\n���س�������������ٿء�\n", TreeName);
			getchar();getchar();
			SingleTree_Operation(TreesList.elem[i].root);
			return OK;
		}
	}
	return ERROR;//û�ҵ��������ƵĶ����� 
} 
status AddTree(List &L, char ElemName[])// ��Listβ������һ������ΪElemName��Ԫ�� 
{
	if(LocateTree(L, ElemName))return REPEATED;
	if(L.length >= L.listsize){// ���ʱ���� 
		ListElem *newelem = (ListElem*)realloc(L.elem,
		 (L.listsize+LISTINCREMENT)*sizeof(ListElem));
		if(newelem==NULL)
		return OVERFLOW;// ����ʧ�� 
		int i=L.listsize;
		L.elem = newelem;
		L.listsize += LISTINCREMENT;// �ռ��������� 
		for(i=0; i<LIST_INIT_SIZE; i++)
		L.elem[i].root = NULL;// ��Ϊ��ָ�룬����Ұָ��ĳ��ֵ��·Ƿ����� 
		return OK;
	}
	//�����ַ��������ö��������� 
	strcpy(L.elem[L.length].name, ElemName);
	L.elem[L.length].root = NULL;//�ն����� 
	
	printf("�����������!�Ƿ������ȸ����������Լ�������������1����0��\n");
	int tmp;
	scanf("%d", &tmp);
	if(!tmp){
		L.length++;	
		return OK;	
	} 
	TElemType definition[100];
	int i = 0; 
	for(i=0;i<100;i++){
		definition[i].key = 0;//�ؼ�����Ϊ0 
	}
	i = 0;
	do {
		scanf("%d%s",&definition[i].key,definition[i].others);
	} while (definition[i++].key!=-1);
	int reValue = CreateBiTree(L.elem[L.length].root,definition);
	L.length++;
	if(reValue ==OK)printf("�����������ɹ���\n");
	else if(reValue == ERROR) printf("�ؼ��ֲ�Ψһ��\n"); 
	else if(reValue == INFEASIBLE) printf("�������ǿգ��������٣�\n");
	return OK; 
}
status RemoveTree(List &TreesList, char TreeName[NAMESIZE])//ɾ���������ƵĶ�����
{
	int len = TreesList.length, i, j, tmp;// �������ѭ������ 
	for (i = 0; i < len; i++) {
		if (strcmp(TreesList.elem[i].name, TreeName) == 0) {// �ȶ� 
			tmp = DestroyBiTree(TreesList.elem[i].root);
			TreesList.elem[i].root = NULL;//�������Ϊ��ָ�� 
			TreesList.elem[i].name[0] = '\0';// ��ն��������� 
			for (j = i; j < len; j++)// ����i��Ԫ�غ�֮���Ԫ��ǰ�� 
			TreesList.elem[j] = TreesList.elem[j + 1];
			TreesList.length--;// ��������һ 
			return OK;
		}
	}
	return ERROR;//δ�ҵ��������ƵĶ����� 
}
int LocateTree(List &ElemList, char ElemName[NAMESIZE])
{
	int  i;
	for (i = 0; i < ElemList.length; i++) {
		if (strcmp(ElemList.elem[i].name, ElemName) == 0) {
			return i + 1;
		}
	}
	return 0;
}
	
