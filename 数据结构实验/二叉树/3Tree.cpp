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
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{  //二叉链表结点的定义
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
}NamedBiTree;//有名称二叉树的定义
typedef NamedBiTree ListElem;
typedef struct{  //多二叉树管理表定义
	ListElem* elem;
	int length;
	int listsize;
}List;
//函数的声明 
void visit(BiTree T);//访问结点 
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
	
	// 创建根节点，根据前序遍历序列的第一个元素确定
	T = (BiTree)malloc(sizeof(BiTNode));
	if (!T) {
		exit(OVERFLOW);
	}
	T->data = preOrder[preStart];
	T->lchild = NULL;
	T->rchild = NULL;
	
	// 在中序遍历序列中找到根节点的位置
	int rootIndex;
	for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
		if (inOrder[rootIndex].key == preOrder[preStart].key) {
			break;
		}
	}
	
	// 左子树的长度
	int leftLength = rootIndex - inStart;
	
	// 递归构建左子树
	CreateBiTree2(T->lchild, preOrder, inOrder, preStart + 1, preStart + 
	leftLength, inStart, rootIndex - 1);
	
	// 递归构建右子树
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
		// 当前节点为叶子节点，直接使用后序序列的最后一个元素作为节点数据
		T->lchild = NULL;
		T->rchild = NULL;
		return OK;
	}
	
	if (inStart > inEnd || postStart > postEnd ||
	 (inEnd - inStart) != (postEnd - postStart)) {
		T = NULL;
		return OK;
	}
	
	// 在后序序列中找到根节点
	TElemType root = postOrder[postEnd];
	
	// 在中序序列中找到根节点的位置
	int rootIndex;
	for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
		if (inOrder[rootIndex].key == root.key) {
			break;
		}
	}
	
	// 创建根节点
	T = (BiTree)malloc(sizeof(BiTNode));
	if (!T) {
		exit(OVERFLOW);
	}
	T->data = root;
	T->lchild = NULL;
	T->rchild = NULL;
	
	// 计算左子树和右子树的大小
	int leftTreeSize = rootIndex - inStart;
	int rightTreeSize = inEnd - rootIndex;
	
	// 递归地构建左子树和右子树
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
//主函数 
int main(void){
	BiTree T = NULL;
	int op=1, reValue, i;
	char FileName[NAMESIZE], c, TreeName[NAMESIZE];
	List TreesList;
	InitList(TreesList);//创建二叉树管理表
	void(*pvisit)(BiTree) = visit;//访问结点函数的指针 
	while(op){
		system("cls");//清屏
		printf("\n\n");
		printf("   多二叉树管理菜单: \n");
		printf("------------------------------------------------------------------\n");
		printf("1. SingleTree_Operation	 2. EnterTreeByName	3. TreesTraverse\n");
		printf("    	4. ListLength	  	 5. AddTree		6. RemoveTree\n");
		printf("    	7. LocateTreeByName      0. Exit\n");
		printf("-----------------------------------------------------------------\n");
		printf("    请选择你的操作[0~8]:");		
		scanf("%d",&op);
		switch(op){
			case 1:{
				SingleTree_Operation(T);
				break;
			}
			case 2:{
				printf("请输入你需要单独操控的二叉树在管理表中的名称：");
				scanf("%s", &TreeName);
				reValue = EnterTree(TreesList, TreeName);
				if(reValue == ERROR) printf("不存在该二叉树！\n");
				break;
			} 
			case 3:{
				if(TreesList.length==0) {
					printf("管理表为空，无二叉树可供遍历！\n");
					break;
				}
				for(int i=0; i<TreesList.length; i++){
					printf("\n序号为%d, 名称为%s的二叉树", i+1, TreesList.elem[i].name);
					if(TreesList.elem[i].root==NULL){//空二叉树不予遍历 
						printf("为空树！");
						continue;
					}
					printf("\n前序遍历：");PreOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n中序遍历：");InOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n后序遍历：");PostOrderTraverse(TreesList.elem[i].root, pvisit);
					printf("\n层序遍历：");LevelOrderTraverse(TreesList.elem[i].root, pvisit);
				}
				printf("\n所有二叉树遍历完成！\n");
				break;
			}
			case 4:
			printf("多二叉树管理表中有%d个二叉树。\n", TreesList.length);
			break;
			case 5:
			printf("请输入需要增加的二叉树的名称：");
			scanf("%s", TreeName);
			reValue = AddTree(TreesList, TreeName);//增加二叉树 
			if(reValue == OK) printf("增加二叉树成功！\n");
			else if(reValue == REPEATED) printf("已存在同名二叉树，无法添加！\n"); 
			else printf("增加二叉树出现错误！\n");
			break;
			case 6:
			printf("请输入需要删除的二叉树的名称：");
			scanf("%s", TreeName);
			reValue = RemoveTree(TreesList, TreeName);
			if(reValue == OK)printf("删除二叉树成功！\n");
			else printf("不存在该二叉树，删除二叉树失败!\n");
			break;
			case 7:
			printf("请输入需要查找的二叉树的名称：");
			scanf("%s", TreeName);
			reValue = LocateTree(TreesList, TreeName);
			if(reValue == 0)printf("所查找的二叉树不存在！\n");
			else printf("名称为%s的二叉树在多线性表中是第%d个。\n", TreeName, reValue);
			break;
			case 0:
			break;
		}//end of switch
		getchar();getchar();//键入任意字符或回车结束循环 
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}

//函数的定义 
void visit(BiTree T)//访问结点 
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
status isRepeat(TElemType definition[])// 查找是否存在重复关键字 
{
	int i = 0, j;
	for(; definition[i].key!=-1; i++){
		if(definition[i].key==0)continue;// 关键字为0，代表空结点，直接跳过 
		for(j=i+1; definition[j].key!=-1; j++){
			if(definition[j].key==definition[i].key)return TRUE;// 存在重复关键字 
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
//求二叉树T的深度
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
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
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
	// 检查是否存在相同关键字的结点
	if (LocateNode(T, c.key) != NULL)
	{
		return ERROR; // 存在相同关键字的结点，返回ERROR
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

BiTNode* FatherNode(BiTree &T, KeyType e, int &i)// 寻找结点e的双亲结点
// i最后的值为0则结点e是左孩子，i最后的值为1则结点e是右孩子返回1，-1代表不存在  
{
	if(!T || T->data.key==e){// T为空树或根结点为e时，结点e无双亲结点
		i = -1;
		return NULL;
	}
	// 左右孩子是否为结点e 
	if(T->lchild && T->lchild->data.key==e){
		i = 0;
		return T;
	}
	if(T->rchild && T->rchild->data.key==e){
		i = 1;
		return T;
	}
	// 左右孩子均不为结点e，依次在左右子树中搜索 
	BiTNode* tmp;
	tmp = FatherNode(T->lchild, e, i);
	if(tmp) return tmp;
	tmp = FatherNode(T->rchild, e, i);
	if(tmp) return tmp;
	//左右子树中均没有搜索到，返回空指针 
	return NULL;
}
status DeleteNode(BiTree &T, KeyType e)//删除结点：可以不查找父结点 
{
	if(!T) return INFEASIBLE;
	BiTNode *tmp = LocateNode(T, e), *father;
	int i = -1;
	if(!tmp) return ERROR;// 没有找到关键字为e的结点，无法删除（包含空树） 
	father = FatherNode(T, e, i);
	if(!tmp->lchild && !tmp->rchild){// 
		if(i==-1 && T==tmp) T = NULL;// 
		else if(father && i!=-1){
			if(i==0) father->lchild = NULL;
			else if(i==1) father->rchild = NULL;
		}
		free(tmp);
	}
	else if(tmp->lchild && tmp->rchild){//关键字为e的结点度为2
		BiTNode* LCrTree;
		if(T==tmp){
			T = tmp->lchild;
			LCrTree = tmp->lchild;
			while(LCrTree->rchild) LCrTree = LCrTree->rchild;
			LCrTree->rchild = tmp->rchild;
		}
		else if(father && i!=-1){//关键字为e的结点不是根结点 
			
			if(i==0) father->lchild = tmp->lchild;
			else if(i==1) father->rchild = tmp->lchild;
			LCrTree = tmp->lchild;
			while(LCrTree->rchild) LCrTree = LCrTree->rchild;// 找到右孩子为空的结点 
			LCrTree->rchild = tmp->rchild;
		}
		free(tmp);
	}
	else if(tmp->lchild){// 左孩子结点非空，右孩子结点为空 
		if(T==tmp)// 关键字为e的结点是根结点 
		T = tmp->lchild;//用e的左子树代替被删除的e位置
		else if(father && i!=-1){//关键字为e的结点不是根结点 
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
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))//先序遍历二叉树T
{
	if(!T) return OK;
	visit(T);
	PreOrderTraverse(T->lchild, visit);
	PreOrderTraverse(T->rchild, visit);
	return OK;
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))//中序遍历二叉树T
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
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))//后序遍历二叉树T
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
void filePreCreateBiTree(BiTree &T, FILE *fp)//基于先序遍历创建二叉树（文件） 
{
	int tmpkey, reValue;
	char tmpOthers[50];
	reValue = fscanf(fp, "%d,%s ", &tmpkey, tmpOthers);// 读取数据
	if(reValue){
		if(tmpkey==0) T = NULL;
		else{
			if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);//生成根结点
			T->data.key = tmpkey;//为根结点赋值 
			strcpy(T->data.others, tmpOthers);
			filePreCreateBiTree(T->lchild, fp);//构造左子树
			filePreCreateBiTree(T->rchild, fp);//构造右子树
		}
	}
}
status LoadBiTree(BiTree &T, char FileName[])//读取文件中的二叉树 
{
	if(T) return INFEASIBLE;//二叉树已存在 
	FILE * fp;
	if((fp=fopen(FileName,"rb"))==NULL){     
		return ERROR;// 文件打开失败
	}
	filePreCreateBiTree(T, fp);
	fclose(fp);  // 关闭文件句柄
	return OK;// 读入完成 
}
int MaxPathSum(BiTree &T)//返回根节点到叶子结点的最大路径和
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
BiTNode* LowestCommonAncestor(BiTree &T, KeyType e1, KeyType e2)//最近公共祖先
{
	Stack s1, s2;//为e1和e2定义两个指针栈 
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
		system("cls");//清屏
		printf("\n\n");
		printf("   单个二叉树操作菜单: \n");
		printf("------------------------------------------------------------\n");
		printf("    1. CreateBiTree			2. DestroyBiTree  		3. ClearBiTree\n");
		printf("    4. BiTreeEmpty			5. BiTreeDepth		6. LocateNode\n");
		printf("    7. Assign 			8. GetSibling		9. InsertNode\n");
		printf("    10.DeleteNode			11.PreOrderTraverse  12.InOrderTraverse\n");
		printf("    13.PostOrderTraverse	14.LevelOrderTraverse	15.MaxPathSum\n");
		printf("    16.LowestCommonAncestor 	17.InvertTree		18.SaveBiTree\n");
		printf("    19.LoadBiTree			0. Return返\n");
		printf("------------------------------------------------------------\n");
		printf("    请选择你的操作[0~17]:");		
		scanf("%d",&op);
		switch(op){
			case 1:{
				if(T) {
					printf("二叉树非空，请先销毁！\n");
					break;
				}
				TElemType definition[100],preOrder[100],inOrder[100],postOrder[100];
				int i = 0,j=0; 
				printf("请输入二叉树的定义（1）：前序遍历；（2）前序+中序；（3）后序+中序");
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
				if (ans==OK) printf("二叉树创建成功");else printf("关键字不唯一");
				getchar();getchar();
				break;
			}
			case 2: 
			reValue = DestroyBiTree(T);
			if(reValue == OK) printf("二叉树销毁成功！\n");
			else if(reValue == INFEASIBLE) printf("二叉树为空！\n");
			break;
			case 3:
			reValue = ClearBiTree(T);
			if(reValue == OK) printf("二叉树销毁成功！\n");
			else if(reValue == INFEASIBLE) printf("二叉树为空！\n");
			break;
			case 4:
			reValue = BiTreeEmpty(T);
			if(reValue == TRUE) printf("二叉树为空。\n");
			else if(reValue == FALSE) printf("二叉树非空。\n");
			break;
			case 5:
			reValue = BiTreeDepth(T);
			if(reValue == 0) printf("二叉树为空，深度为0。\n");
			else printf("二叉树深度为%d。\n", reValue);
			break;
			case 6:{	
				printf("请输入需要获取的结点的关键字：");
				scanf("%d", &e);
				BiTNode *pNode = LocateNode(T, e);
				if(!pNode) printf("查找失败，二叉树中不存在关键字为%d的结点！\n", e);
				else printf("二叉树中关键字为%d的结点名称为%s。\n", e, pNode->data.others);
				break;
			}
			case 7:{
				TElemType value;
				printf("请输入需要赋值的结点的关键字：");
				scanf("%d", &e);
				printf("请输入需要赋值的结点的新关键字：");
				scanf("%d", &value.key);
				printf("请输入需要赋值的结点的新名称：");
				scanf("%s", value.others);
				reValue = Assign(T, e, value);
				if(reValue == INFEASIBLE) 
				printf("二叉树为空，赋值失败！\n");
				else if(reValue == ERROR) 
				printf("二叉树中不存在关键字为%d的结点，赋值失败！\n", e);
				else if(reValue == REPEATED) 
				printf("二叉树中已经存在关键字为%d的结点，赋值失败！\n", value.key);
				else  printf("赋值成功！\n");
				break;
			}
			case 8:{
				printf("请输入需要查找兄弟的结点关键字：");
				scanf("%d", &e);
				BiTNode *pNode = GetSibling(T,e);
				if(!pNode) printf("查找失败，二叉树中不存在该元素的兄弟！\n");
				else printf("二叉树中关键字为%d的兄弟结点是：名称为%s而关键字为%d的结点。\n", e, pNode->data.others, pNode->data.key);
				break;
			}
			case 9:{
				TElemType value;
				int LR; 
				scanf("%d", &LR);
				if(LR!=-1){
					printf("请输入插入位置的结点关键字e：");
					scanf("%d", &e);
				}
				else e=0;//LR为-1的时候，e可以取任何值(没有意义)，赋值为0 
				printf("请输入需要待插入的结点关键字：");
				scanf("%d", &value.key);
				printf("请输入需要待插入的结点名称：");
				scanf("%s", value.others);
				reValue = InsertNode(T, e, LR, value);
				if(reValue == INFEASIBLE) printf("二叉树为空，插入失败！\n");
				else if(reValue == ERROR) 
				printf("二叉树中不存在关键字为%d的结点，插入失败！\n", e);
				else if(reValue == REPEATED) 
				printf("二叉树中已经存在关键字为%d的结点，插入失败！\n", value.key);
				else  printf("插入成功！\n");
				break;
			}
			case 10:
			printf("请输入需要删除的结点关键字：");
			scanf("%d", &e);
			reValue = DeleteNode(T,  e);//删除结点
			if(reValue == INFEASIBLE) 
			printf("二叉树为空，删除失败！\n");
			else if(reValue == ERROR) 
			printf("二叉树中不存在关键字为%d的结点，删除失败！\n", e);
			else printf("删除成功！\n");
			break;
			case 11:{
				if(!T) printf("二叉树为空！\n");
				else {
					printf("二叉树中全部结点先序遍历如下：\n");
					PreOrderTraverse(T, visit);//先序遍历二叉树T
					printf("遍历完成！\n");
				}
				break;
			}
			case 12:{
				if(!T) printf("二叉树为空！\n");
				else {
					printf("二叉树中全部结点中序遍历如下：\n");
					InOrderTraverse(T, visit);//中序遍历二叉树T
					printf("遍历完成！\n");
				}
				break;
			}
			case 13:{
				if(!T) printf("二叉树为空！\n");
				else {
					printf("二叉树中全部结点后序遍历如下：\n");
					PostOrderTraverse(T, visit);//后序遍历二叉树T
					printf("遍历完成！\n");
				}
				break;
			} 
			case 14:{
				if(!T) printf("二叉树为空！\n");
				else {
					printf("二叉树中全部结点层序遍历如下：\n");
					LevelOrderTraverse(T, visit);//后序遍历二叉树T
					printf("遍历完成！\n");
				}
				break;
			} 
			case 15:{
				if(!T)
				printf("二叉树为空树！\n");
				else//计算并输出根节点到叶子结点的最大路径和
				printf("二叉树的根节点到叶子结点的最大路径和为%d", MaxPathSum(T));
				break;
			}	
			case 16:{
				int e1, e2;
				printf("请输入待查找公共祖先的两个结点的关键字（以空格间隔，以回车结尾）：");
				scanf("%d %d", &e1, &e2);
				if(!T){
					printf("二叉树为空树！\n");
				}
				else{
					BiTNode* tmp = LowestCommonAncestor(T, e1, e2);//查找最近公共祖先
					if(!tmp){
						printf("没有找到最近公共祖先！结点不存在于二叉树中！\n");
						break;
					}
					else printf("最近公共祖先是关键字为%d的结点，名称为%s。\n", tmp->data.key, tmp->data.others);
				}
				break;
			}
			case 17:{
				if(!T)
				printf("二叉树为空树！\n");
				else{
					InvertTree(T);//所有节点的左右节点互换
					printf("翻转成功！\n");
				}
				break;
			}
			case 18:{
				if(!T) printf("二叉树为空树！\n");
				else{
					
					reValue = SaveBiTree(T, "C:\\Users\\lenovo\\Desktop\\listfile.txt");
					if(reValue == ERROR) printf("文件打开失败！\n");
					else {
						printf("存储二叉树成功！\n");
					}
				}
				break;
			}
			case 19:{
				
				reValue = LoadBiTree(T, "C:\\Users\\lenovo\\Desktop\\listfile.txt");
				if(reValue == INFEASIBLE) printf("二叉树已经存在，不可覆盖 ！\n");
				else if(reValue == ERROR) printf("文件打开失败！\n");
				else {
					printf("读取二叉树成功！\n");
				}
				break;
			}
			case 0:
			return;
		}//end of switch
		getchar();getchar();//键入任意字符清屏 
	}//end of while
	return;
}
status InitList(List &L)//创建多线性表管理表
{
	L.elem=(ListElem*)malloc(sizeof(ListElem)*LIST_INIT_SIZE);
	L.listsize=LIST_INIT_SIZE;// 设置空间容量为默认初始化值
	L.length=0;// 元素个数初始值为0   
	if (L.elem == NULL)
	return OVERFLOW;  // 内存分配失败
	for(int i=0; i<LIST_INIT_SIZE; i++)
	L.elem[i].root = NULL;// 设为空指针，避免野指针的出现导致非法访问 
	return OK;
}
status EnterTree(List &TreesList, char TreeName[NAMESIZE])//操控特定名称的二叉树 
{
	for(int i=0; i<TreesList.length; i++){
		if(strcmp(TreeName, TreesList.elem[i].name)==0){
			printf("你即将进入名称为%s的二叉树。\n按回车键进入二叉树操控。\n", TreeName);
			getchar();getchar();
			SingleTree_Operation(TreesList.elem[i].root);
			return OK;
		}
	}
	return ERROR;//没找到符合名称的二叉树 
} 
status AddTree(List &L, char ElemName[])// 在List尾部增加一个名称为ElemName的元素 
{
	if(LocateTree(L, ElemName))return REPEATED;
	if(L.length >= L.listsize){// 溢出时扩充 
		ListElem *newelem = (ListElem*)realloc(L.elem,
		 (L.listsize+LISTINCREMENT)*sizeof(ListElem));
		if(newelem==NULL)
		return OVERFLOW;// 扩充失败 
		int i=L.listsize;
		L.elem = newelem;
		L.listsize += LISTINCREMENT;// 空间容量增加 
		for(i=0; i<LIST_INIT_SIZE; i++)
		L.elem[i].root = NULL;// 设为空指针，避免野指针的出现导致非法访问 
		return OK;
	}
	//复制字符串，设置二叉树名称 
	strcpy(L.elem[L.length].name, ElemName);
	L.elem[L.length].root = NULL;//空二叉树 
	
	printf("空树创建完成!是否输入先根遍历序列以继续创建？（是1，否0）\n");
	int tmp;
	scanf("%d", &tmp);
	if(!tmp){
		L.length++;	
		return OK;	
	} 
	TElemType definition[100];
	int i = 0; 
	for(i=0;i<100;i++){
		definition[i].key = 0;//关键字置为0 
	}
	i = 0;
	do {
		scanf("%d%s",&definition[i].key,definition[i].others);
	} while (definition[i++].key!=-1);
	int reValue = CreateBiTree(L.elem[L.length].root,definition);
	L.length++;
	if(reValue ==OK)printf("二叉树创建成功！\n");
	else if(reValue == ERROR) printf("关键字不唯一！\n"); 
	else if(reValue == INFEASIBLE) printf("二叉树非空，请先销毁！\n");
	return OK; 
}
status RemoveTree(List &TreesList, char TreeName[NAMESIZE])//删除给定名称的二叉树
{
	int len = TreesList.length, i, j, tmp;// 定义表长与循环变量 
	for (i = 0; i < len; i++) {
		if (strcmp(TreesList.elem[i].name, TreeName) == 0) {// 比对 
			tmp = DestroyBiTree(TreesList.elem[i].root);
			TreesList.elem[i].root = NULL;//根结点设为空指针 
			TreesList.elem[i].name[0] = '\0';// 清空二叉树名称 
			for (j = i; j < len; j++)// 将第i个元素和之后的元素前移 
			TreesList.elem[j] = TreesList.elem[j + 1];
			TreesList.length--;// 管理表表长减一 
			return OK;
		}
	}
	return ERROR;//未找到给定名称的二叉树 
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
	
