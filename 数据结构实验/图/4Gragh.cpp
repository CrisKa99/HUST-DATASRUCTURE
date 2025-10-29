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
	#define MAX_VERTEX_NUM 20
	typedef int status;
	typedef int KeyType; 
   typedef enum {DG,DN,UDG,UDN} GraphKind;
	typedef struct {
         KeyType  key;
         char others[20];
	} VertexType; //顶点类型定义


	typedef struct ArcNode {         //表结点类型定义
   		 int adjvex;              //顶点位置编号 
    	 struct ArcNode  *nextarc;	   //下一个表结点指针
	} ArcNode;
	typedef struct VNode{				//头结点及其数组类型定义
   		 VertexType data;       	//顶点信息
    	 ArcNode *firstarc;      	 //指向第一条弧
    	} VNode,AdjList[MAX_VERTEX_NUM];
	typedef  struct {  //邻接表的类型定义
        AdjList vertices;     	 //头结点数组
        int vexnum,arcnum;   	  //顶点数、弧数
        GraphKind  kind;        //图的类型
       } ALGraph;
status checksame(VertexType V[]){
	int i=0;
	int flag[10000]={0};
	while(V[i].key!=-1)
	{
		if(flag[V[i].key]>0){return ERROR;}
		flag[V[i].key]++;
		i++;
	}
	return OK;
}

int locatei(ALGraph G,KeyType VR){
    int i=0;
    for(i;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==VR) return i;
    }
    return -1;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]){
	int i = 0;
    while (V[i].key != -1) {
        i++;
    }
    if(i==0) return ERROR;
    if(i-1>=MAX_VERTEX_NUM) return ERROR;
    if(checksame(V)==ERROR) return ERROR;
    G.vexnum = i;
    for (i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
    }
    i = 0;
    while(VR[i][0]!=-1)
    {
        int a=locatei(G,VR[i][0]),b=locatei(G,VR[i][1]);
        if(!(a>=0&&b>=0)) return ERROR;
        ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode)) ;
        q->adjvex=b;
        q->nextarc=G.vertices[a].firstarc;
        G.vertices[a].firstarc=q;
        q=(ArcNode*)malloc(sizeof(ArcNode)) ;
        q->adjvex=a;
        q->nextarc=G.vertices[b].firstarc;
        G.vertices[b].firstarc=q;
        i++;
    }
    G.arcnum = i;
    return OK;
}


#define free free0
struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p){
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(ArcNode));
    free(p);
}

#undef free
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    ArcNode *p=NULL,*q=NULL;
    for(int k=0;k<G.vexnum;k++)
    {
        if(G.vertices[k].firstarc!=NULL)
        {
            p=G.vertices[k].firstarc;
            while(p!=NULL)
            {
                q=p->nextarc;
                free(p);
                p=q;
            }
        G.vertices[k].firstarc=NULL;
        }
    }
    G.arcnum=0;
	G.vexnum=0;
    return OK;
}


int LocateVex(ALGraph G,KeyType u){
	int i=0;
    for(i;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==u) return i;
    }
    return -1;
}


status PutVex(ALGraph &G,KeyType u,VertexType value){
	int i=LocateVex(G,u);
	if(i==-1) return ERROR;
	for(int k=0;k<G.vexnum;k++){
		if(G.vertices[k].data.key==value.key) return ERROR;
	}
	G.vertices[i].data=value;
	return OK;
}

int FirstAdjVex(ALGraph G,KeyType u){
	int i=0;
    for(i;i<G.vexnum;i++)
    {
        if(G.vertices[i].data.key==u) return G.vertices[i].firstarc->adjvex;
    }
    return -1;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w){
    int i=LocateVex(G,v),j=LocateVex(G,w);
    while(i!=-1&&j!=-1)
    {
        ArcNode *p=G.vertices[i].firstarc;
        while(p->adjvex!=j&&p)
        {
            p=p->nextarc;
        }
        if(p->nextarc)
        {
            return p->nextarc->adjvex;
        }
        else return -1;
    }
    return -1;
}


status InsertVex(ALGraph &G,VertexType v){
	if(LocateVex(G,v.key)!=-1) return ERROR;\
	if(G.vexnum==MAX_VERTEX_NUM) return ERROR;
    G.vertices[G.vexnum].data=v;
	G.vertices[G.vexnum].firstarc=NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum==1 ||G.vexnum==0) return ERROR;
	int i=LocateVex(G,v);
	if(i==-1) return ERROR;
	ArcNode *p=G.vertices[i].firstarc,*q=NULL,*temp=NULL;
	while(p){
		int j=p->adjvex;
		q=G.vertices[j].firstarc;
		if(q->adjvex==i){
            temp=q;
            G.vertices[j].firstarc=q->nextarc;
            free0(temp); 
        }
        else{
            while(q->nextarc->adjvex!=i) q=q->nextarc;
            temp=q->nextarc;
            q->nextarc=temp->nextarc;
            free0(temp);
        }
        temp=p->nextarc;
        free0(p);
        p=temp;
        G.arcnum--;
	}
	for(int k=i;k<G.vexnum;k++)   G.vertices[k]=G.vertices[k+1];
    G.vexnum--;
    for(int k=0;k<G.vexnum;k++){
		p=G.vertices[k].firstarc;
		while(p!=NULL)
		{
			if(p->adjvex>i)
			p->adjvex--;
			p=p->nextarc;
		}
	}
    return OK;
    /********** End **********/
}
int Get_index(ALGraph G, int key)
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data.key == key)
            return i;
    return -1;
}
void DeleteArc_A_Node(VNode& Node, int index)
{
    ArcNode* p = Node.firstarc;
    if (p == NULL)return;
    if (p->adjvex == index)//首个链表节点就是
    {
        Node.firstarc = Node.firstarc->nextarc;
        free(p);
        p = NULL;
        return;
    }
    ArcNode* q = Node.firstarc->nextarc;
    for (; q != NULL;)
    {
        if (q->adjvex == index)
        {
            p->nextarc = q->nextarc;
            free(q);
            q = p->nextarc;
            break;
        }
        else
        {
            p = p->nextarc;
            q = q->nextarc;
        }
    }
}



status InsertArc(ALGraph& G, KeyType v, KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int s1 = Get_index(G, v);
    int s2 = Get_index(G, w);
    if (s1 == -1 || s2 == -1) return ERROR;
    ArcNode* q = G.vertices[s1].firstarc;
    while (q) {
        if (q->adjvex == s2) return ERROR;
        q = q->nextarc;
    }

    ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = s2;
    p->nextarc = G.vertices[s1].firstarc;
    G.vertices[s1].firstarc = p;

    p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = s1;
    p->nextarc = G.vertices[s2].firstarc;
    G.vertices[s2].firstarc = p;
    ++G.arcnum;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph& G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int s1 = Get_index(G, v);
    int s2 = Get_index(G, w);
    if (s1 == -1 || s2 == -1) return ERROR;
    ArcNode* q = G.vertices[s1].firstarc;
    int flag = 0;
    while (q) {
        if (q->adjvex == s2) flag = 1;
        q = q->nextarc;
    }
    if (flag == 0) return ERROR;
    DeleteArc_A_Node(G.vertices[s1], s2);
    DeleteArc_A_Node(G.vertices[s2], s1);
    --G.arcnum;
    return OK;
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType)){
	int flag[MAX_VERTEX_NUM]={0};
	for(int i=0;i<G.vexnum;i++) flag[i]=0;
	for(int i=0;i<G.vexnum;i++){
		if(!flag[i]){
			visit(G.vertices[i].data);
			flag[i]++;
			ArcNode *p=G.vertices[i].firstarc;
			while(p){
				int k=LocateVex(G,G.vertices[p->adjvex].data.key);
				if(k==-1) break;
				else if(flag[k]!=0){
					if(p->nextarc==NULL) break;
					p=p->nextarc;
				}
				else{
					i=k;
					visit(G.vertices[i].data);
					flag[i]++;
					p=G.vertices[i].firstarc;
				}
			}
		}
		else continue;
	}
	return OK;
}

typedef struct QNode{
	VertexType data;
	struct QNode *next;
}QNode,*Queue;
typedef struct{
	Queue front;
	Queue rear;
}Linkqueue;

status BFSTraverse(ALGraph &G,void (*visit)(VertexType)){
    int flag[MAX_VERTEX_NUM];
    int i;
    for (i = 0; i < G.vexnum; i++) {
        flag[i] = 0; //初始化所有顶点为未访问状态
    }
    for (i = 0; i < G.vexnum; i++) {
        if (!flag[i]) {
            flag[i] = 1;
            visit(G.vertices[i].data); //访问顶点
            ArcNode *p=G.vertices[i].firstarc;
            while(p){
            	int k=LocateVex(G,G.vertices[p->adjvex].data.key);
				if(k==-1) break;
				else if(flag[k]!=0){
					if(p->nextarc==NULL) break;
					p=p->nextarc;
				}
				else{
					visit(G.vertices[k].data);
					flag[k]++;
					p=p->nextarc;
				}
			}
        }
    }
    return OK;
}
status InitQueue(Linkqueue &Q)
{
	Q.front=Q.rear=(QNode *)malloc(sizeof(QNode));
	if(!Q.front)return ERROR;
	Q.front->next=NULL;
	return OK;
} 
status QueueEmpty(Linkqueue Q)
{
	if(Q.front==Q.rear)return TRUE;
	else return FALSE;
}
status enQueue(Linkqueue &Q,VertexType value)
{
	Queue p=(Queue)malloc(sizeof(QNode));
	if(!p)return ERROR;
	p->data=value;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
status deQueue(Linkqueue &Q,VertexType &value)
{
	if(Q.front==Q.rear)return ERROR;
	Queue p=Q.front->next;
	value=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
	Q.rear=Q.front;
	free(p);
	return OK;
}
int distance[21];
status ShortestPathLength(ALGraph G,KeyType v,KeyType w){
	int i,j,n;
	VertexType top;
	top.key=v;
	Linkqueue Q;
	InitQueue(Q);
	for(i=0;i<G.vexnum;i++)
	distance[G.vertices[i].data.key]=20;
	distance[v]=0;
	int k=LocateVex(G,v);
	enQueue(Q,G.vertices[k].data);
	while(!QueueEmpty(Q))
	{
		deQueue(Q,top);
		if(top.key==w)break;
		for(j=FirstAdjVex(G,top.key);j>=0;j=NextAdjVex(G,top.key,G.vertices[j].data.key))//返回位序 
		{
			if(distance[G.vertices[j].data.key]==20)
			{
				distance[G.vertices[j].data.key]=distance[top.key]+1;
				enQueue(Q,G.vertices[j].data);
			}
		}
	}
	n=distance[w];
	return n;
}

void VerticesSetLessThank(ALGraph G,KeyType v,KeyType k){
	int i,j;
	for(i=0;i<G.vexnum;i++)
	{
		j=ShortestPathLength(G,v,G.vertices[i].data.key);
		if(j<k&&G.vertices[i].data.key!=v)
		visit(G.vertices[i].data);
	}
}

bool mark[20];
bool visited[MAX_VERTEX_NUM];
void dfs(ALGraph &G,KeyType v)
{
	mark[v]=TRUE;
	for(int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,G.vertices[w].data.key)) 
	{
		if(!mark[G.vertices[w].data.key])dfs(G,G.vertices[w].data.key);
	}
}
status ConnectedComponentsNums(ALGraph G)//求图中连通分量个数 
{
	int count=0,i;
	for(i=0;i<G.vexnum;i++)
	mark[G.vertices[i].data.key]=FALSE;//标记数组记录关键字 
	for(i=0;i<G.vexnum;i++)
	{
		if(!mark[G.vertices[i].data.key])
		{
			dfs(G,G.vertices[i].data.key);
			count++;
		}
	}
	return count;
 } 




status SaveGraph(ALGraph G, char FileName[]){
	FILE *fp;
    fp = fopen(FileName, "w");
    if (fp == NULL||G.vexnum==0) return ERROR;
	for(int i=0;i<G.vexnum;i++){
		fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
		ArcNode *p=G.vertices[i].firstarc;
		while(p){ 
			fprintf(fp,"%d ",p->adjvex);
			p=p->nextarc;
		}
		fprintf(fp,"%d\n",-1);
	    }
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[]){
	FILE *fp;
    fp = fopen(FileName, "r");
    if (fp == NULL) return ERROR; 
    VNode tempNode;
    int i = 0;
    G.arcnum = 0;
    G.vexnum = 0;
    while (fscanf(fp, "%d %s", &tempNode.data.key, tempNode.data.others) != EOF) {
        G.vertices[i].data = tempNode.data;
        G.vertices[i].firstarc = NULL;
        
        ArcNode *p, *q;
        int j = 0;    
        while (fscanf(fp, "%d", &j) != EOF && j != -1) {
            p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = j;
            p->nextarc = NULL;
            
            if (G.vertices[i].firstarc == NULL) {
                G.vertices[i].firstarc = p;
            } else {
                q = G.vertices[i].firstarc;
                while (q->nextarc != NULL) {
                    q = q->nextarc;
                }
                q->nextarc = p;
            }
            
            G.arcnum++;
        }
        
        i++;
        G.vexnum++;
    }
    G.arcnum = G.arcnum / 2;
    fclose(fp);
    return OK;
}

typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  ALGraph G;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 
 status Addg(LISTS &Lists, char ListName[])
{
    
    strcpy(Lists.elem[Lists.length].name, ListName); // 复制名称
    Lists.length++;
    return OK;
}
status Removeg(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
	for(int i=0;i<Lists.length;i++){
		if(strcmp(ListName,Lists.elem[i].name)==0){
			
            for(int j=i; j<Lists.length-1; j++){
                strcpy(Lists.elem[j].name, Lists.elem[j+1].name);
                Lists.elem[j].G = Lists.elem[j+1].G;
            }
            Lists.length--;
            return OK;
		}
	}
	return ERROR;
}

int Locateg(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	for(int i=0;i<Lists.length;i++){
		if(strcmp(ListName,Lists.elem[i].name)==0)
			return i+1;
	}
	return 0;
} 
void singleGraghOperation(ALGraph &G){
	VertexType V[30];
	KeyType VR[100][2];
	int op=1,op2=1,i,j,u,e,pre,next;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateCraph       10. DeleteArc \n");
		printf("    	  2. DestroyGraph      11. DFSTraverse \n");
		printf("    	  3. LocateVex         12. BFSTraverse \n");
		printf("    	  4. PutVex            13. VerticesSetLessThank \n");
		printf("    	  5. FirstAdjVex       14. ShortestPathLength \n");
		printf("    	  6. NextAdjVex        15. ConnectedComponentsNums \n");
		printf("    	  7. InsertVex         16. File \n");
		printf("    	  8. DeleteVex         17. Lists\n");
		printf("    	  9. InsertArc         \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:{
			int i=0,j;
			do {
    			scanf("%d%s",&V[i].key,V[i].others);
			} while(V[i++].key!=-1);
			i=0;
			do {
			    scanf("%d%d",&VR[i][0],&VR[i][1]);
			   } while(VR[i++][0]!=-1);
			if (CreateCraph(G,V,VR)==ERROR) printf("输入数据错，无法创建");
			else 
		    {
		         if (G.arcnum!=i-1) {
	     	    printf("边的数目错误！\n");
		     }
	        for(j=0;j<G.vexnum;j++){
	            ArcNode *p=G.vertices[j].firstarc;
	            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
            	while (p)
            	{
            	    printf(" %d",p->adjvex);
            	    p=p->nextarc;
           		 }
            	printf("\n");}
    		}
			 getchar();getchar();
			 break;}
		   case 2:{
				if(G.vexnum==0)printf("销毁失败，请先创建图！\n");
				else{
				     if(DestroyGraph(G)==OK)printf("销毁成功！\n");
					 else printf("销毁失败，请先创建图！\n"); 
				}
			 getchar();getchar();
			 break;}
		   case 3:{
		   	printf("请输入关键字！\n");
		   	scanf("%d",&u);   
		   	i=LocateVex(G,u);
			if (i!=-1) printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else printf("查找失败");
			 getchar();getchar();
			 break;}
	 	  case 4:{
	 	  	printf("请输入关键字和赋值结点！\n");
		   	scanf("%d",&u);
			VertexType V[21],value;   
			scanf("%d%s",&value.key,value.others);
		   	i=PutVex(G,u,value);
			if (i==OK)
			   for(i=0;i<G.vexnum;i++)
 			    printf(" %d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else	printf("赋值操作失败");
			 getchar();getchar();
			 break;}
		   case 5:{
		   	printf("请输入关键字！\n");
		   	scanf("%d",&u);   
		   	i=FirstAdjVex(G,u);
			if (i!=-1) printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else printf("查找失败");
			 getchar();getchar();
			 break;}
		   case 6:{
		   KeyType v,w;
		   if(G.vexnum==0)printf("图不存在！\n");
	   	  else{
		  printf("请输入要查找顶点和相对顶点的关键字！\n");
		  scanf("%d%d",&v,&w);  
		   if(NextAdjVex(G,v,w)==-1)printf("查找失败！\n");
		   else {
		   	int x=NextAdjVex(G,v,w);
		   printf("顶点%d的邻接顶点相对于%d的下一邻接顶点的位序是%d\n",v,w,x);
		   printf("其值为 %d %s\n",G.vertices[x].data.key,G.vertices[x].data.others);}}
		   getchar();getchar();
		 break;}
		   case 7:{
		   	VertexType v;
		   	printf("请输入新增的顶点！\n");
		   	scanf("%d%s",&v.key,v.others);
		   	i=InsertVex(G,v);
			if (i==OK)
				for(i=0;i<G.vexnum;i++)
				{
			     ArcNode *p=G.vertices[i].firstarc;
			     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			     while (p)
			     {
			         printf(" %d",p->adjvex);
			         p=p->nextarc;
			     }
			     printf("\n");
				}
			else printf("插入操作失败");
			getchar();getchar();
			 break;}
		   case 8:{
		   	if(G.vexnum==0)printf("图不存在！\n");
	   	   else{
	   	   	KeyType v;
		    printf("请输入要删除顶点的关键字！\n");
		    scanf("%d",&v);
		    if(DeleteVex(G,v)==OK)printf("删除成功！\n");
		    else printf("删除失败！\n");}
			getchar();getchar();
			 break;}
		   case 9:{
			KeyType v,w,arcs;
			if(G.vexnum==0)printf("图不存在！\n");
	   	else{
		   printf("请输入要插入弧对应的两个顶点！\n");
		   scanf("%d%d",&v,&w);
		   if(InsertArc(G,v,w)==OK) printf("插入弧成功！\n");
		   else printf("插入弧失败！\n");
	}
			getchar();getchar();
			 break;}
		   case 10:{
			KeyType v,w;
			            printf("请输入关键词：\n");
            int uu, vv;
            scanf("%d%d", &uu, &vv);
            int ans = DeleteArc(G, uu, vv);
            if (ans == ERROR) printf("删除失败！\n");
            else printf("删除成功！\n");

			 getchar();getchar();
			 break;}
		   case 11:{
			
			if(G.vexnum==0)printf("图不存在！\n");
	   	else
			DFSTraverse(G,visit);
			getchar();getchar();
			 break;}
		   case 12:{
			if(G.vexnum==0)printf("图不存在！\n");
	   	else
			BFSTraverse(G,visit);
			getchar();getchar();
			 break;}
		   case 13:{KeyType v,k;
			   	printf("请输入顶点的关键字及查找距离！\n");
				scanf("%d%d",&v,&k);
				printf("与顶点距离小于%d的顶点有\n",k);
				VerticesSetLessThank(G,v,k); 
				getchar();getchar();
				break;
		   }
		   case 14:
		   	{KeyType v,w,k;
		   		printf("请输入两个顶点的关键字!\n");
			scanf("%d%d",&v,&w);
			k=ShortestPathLength(G,v,w);
			if(k!=20){
			printf("这两个顶点间的最短路径是%d",k);
		}
		else
		printf("这两个顶点之间不存在路！\n");
			getchar();getchar();
			break;
			   }
		   case 15:{
			   printf("图的连通分量有%d个！\n",ConnectedComponentsNums(G));
			getchar();getchar();
			break;}
		   case 16:{
		    FILE *fp;
		    ALGraph G1;
		    SaveGraph(G,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    printf("已将图存储到文件中");
			 printf("从文件中读得G1为：\n"); 
			LoadGraph(G1,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
			for(j=0;j<G1.vexnum;j++){
	            ArcNode *p=G1.vertices[j].firstarc;
	            printf("%d %s",G1.vertices[j].data.key,G1.vertices[j].data.others);
            	while (p)
            	{
            	    printf(" %d",p->adjvex);
            	    p=p->nextarc;
           		 }
            	printf("\n");}
    		
			getchar();getchar();
			 break;}
			case 0:{
				break;
			}
		}
	}
	printf("对多图的单图操作结束！\n");
}

/*--------------------------------------------*/
int main(void){
	ALGraph G;
	VertexType V[30];
	KeyType VR[100][2];
	int op=1,op2=1,i,j,u,e,pre,next;
	int flag=1;
	while(op){
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateCraph       10. DeleteArc \n");
		printf("    	  2. DestroyGraph      11. DFSTraverse \n");
		printf("    	  3. LocateVex         12. BFSTraverse \n");
		printf("    	  4. PutVex            13. VerticesSetLessThank \n");
		printf("    	  5. FirstAdjVex       14. ShortestPathLength \n");
		printf("    	  6. NextAdjVex        15. ConnectedComponentsNums \n");
		printf("    	  7. InsertVex         16. File \n");
		printf("    	  8. DeleteVex         17. Lists\n");
		printf("    	  9. InsertArc         \n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~17]:");
		scanf("%d",&op);
    	switch(op){
	 	  case 1:{
			int i=0,j;
			do {
    			scanf("%d%s",&V[i].key,V[i].others);
			} while(V[i++].key!=-1);
			i=0;
			do {
			    scanf("%d%d",&VR[i][0],&VR[i][1]);
			   } while(VR[i++][0]!=-1);
			if (CreateCraph(G,V,VR)==ERROR) printf("输入数据错，无法创建");
			else 
		    {
		         if (G.arcnum!=i-1) {
	     	    printf("边的数目错误！\n");
		     }
	        for(j=0;j<G.vexnum;j++){
	            ArcNode *p=G.vertices[j].firstarc;
	            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
            	while (p)
            	{
            	    printf(" %d",p->adjvex);
            	    p=p->nextarc;
           		 }
            	printf("\n");}
    		}
			 getchar();getchar();
			 break;}
		   case 2:{
				if(G.vexnum==0)printf("销毁失败，请先创建图！\n");
				else{
				     if(DestroyGraph(G)==OK)printf("销毁成功！\n");
					 else printf("销毁失败，请先创建图！\n"); 
				}
			 getchar();getchar();
			 break;}
		   case 3:{
		   	printf("请输入关键字！\n");
		   	scanf("%d",&u);   
		   	i=LocateVex(G,u);
			if (i!=-1) printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else printf("查找失败");
			 getchar();getchar();
			 break;}
	 	  case 4:{
	 	  	printf("请输入关键字和赋值结点！\n");
		   	scanf("%d",&u);
			VertexType V[21],value;   
			scanf("%d%s",&value.key,value.others);
		   	i=PutVex(G,u,value);
			if (i==OK)
			   for(i=0;i<G.vexnum;i++)
 			    printf(" %d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else	printf("赋值操作失败");
			 getchar();getchar();
			 break;}
		   case 5:{
		   	printf("请输入关键字！\n");
		   	scanf("%d",&u);   
		   	i=FirstAdjVex(G,u);
			if (i!=-1) printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			else printf("查找失败");
			 getchar();getchar();
			 break;}
		   case 6:{
		   KeyType v,w;
		   if(G.vexnum==0)printf("图不存在！\n");
	   	  else{
		  printf("请输入要查找顶点和相对顶点的关键字！\n");
		  scanf("%d%d",&v,&w);  
		   if(NextAdjVex(G,v,w)==-1)printf("查找失败！\n");
		   else {
		   	int x=NextAdjVex(G,v,w);
		   printf("顶点%d的邻接顶点相对于%d的下一邻接顶点的位序是%d\n",v,w,x);
		   printf("其值为 %d %s\n",G.vertices[x].data.key,G.vertices[x].data.others);}}
		   getchar();getchar();
		 break;}
		   case 7:{
		   	VertexType v;
		   	printf("请输入新增的顶点！\n");
		   	scanf("%d%s",&v.key,v.others);
		   	i=InsertVex(G,v);
			if (i==OK)
				for(i=0;i<G.vexnum;i++)
				{
			     ArcNode *p=G.vertices[i].firstarc;
			     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
			     while (p)
			     {
			         printf(" %d",p->adjvex);
			         p=p->nextarc;
			     }
			     printf("\n");
				}
			else printf("插入操作失败");
			getchar();getchar();
			 break;}
		   case 8:{
		   	if(G.vexnum==0)printf("图不存在！\n");
	   	   else{
	   	   	KeyType v;
		    printf("请输入要删除顶点的关键字！\n");
		    scanf("%d",&v);
		    if(DeleteVex(G,v)==OK)printf("删除成功！\n");
		    else printf("删除失败！\n");}
			getchar();getchar();
			 break;}
		   case 9:{
			KeyType v,w,arcs;
			if(G.vexnum==0)printf("图不存在！\n");
	   	else{
		   printf("请输入要插入弧对应的两个顶点！\n");
		   scanf("%d%d",&v,&w);
		   if(InsertArc(G,v,w)==OK)printf("插入弧成功！\n");
		   else printf("插入弧失败！\n");
	}
			getchar();getchar();
			 break;}
		   case 10:{
			KeyType v,w;
			flag++;
			if(G.vexnum==0)printf("图不存在！\n");
	   	    else{
		     printf("请输入要删除弧对应的两个顶点！\n");
		     scanf("%d%d",&v,&w);
			 if(DeleteArc(G,v,w)==OK)printf("删除弧成功！\n");
			 else printf("删除弧失败！\n"); 
	}
			 getchar();getchar();
			 break;}
		   case 11:{
			
			if(G.vexnum==0)printf("图不存在！\n");
	   	else
			DFSTraverse(G,visit);
			getchar();getchar();
			 break;}
		   case 12:{
			if(G.vexnum==0)printf("图不存在！\n");
	   	else
			BFSTraverse(G,visit);
			getchar();getchar();
			 break;}
		   case 13:{KeyType v,k;
			   	printf("请输入顶点的关键字及查找距离！\n");
				scanf("%d%d",&v,&k);
				printf("与顶点距离小于%d的顶点有\n",k);
				VerticesSetLessThank(G,v,k); 
				getchar();getchar();
				break;
		   }
		   case 14:
		   	{KeyType v,w,k;
		   		printf("请输入两个顶点的关键字!\n");
			scanf("%d%d",&v,&w);
			k=ShortestPathLength(G,v,w);
			if(k!=20){
			printf("这两个顶点间的最短路径是%d",k);
		}
		else
		printf("这两个顶点之间不存在路！\n");
			getchar();getchar();
			break;
			   }
		   case 15:{
			   printf("图的连通分量有%d个！\n",ConnectedComponentsNums(G));
			   
			getchar();getchar();
			break;}
		   case 16:{
		    FILE *fp;
		    ALGraph G1;
		    SaveGraph(G,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
		    printf("已将图存储到文件中");
			 printf("从文件中读得G1为：\n"); 
			LoadGraph(G1,"C:\\Users\\lenovo\\Desktop\\listfile.txt");
			for(j=0;j<G1.vexnum;j++){
	            ArcNode *p=G1.vertices[j].firstarc;
	            printf("%d %s",G1.vertices[j].data.key,G1.vertices[j].data.others);
            	while (p)
            	{
            	    printf(" %d",p->adjvex);
            	    p=p->nextarc;
           		 }
            	printf("\n");}
    		
			getchar();getchar();
			 break;}
			case 17:
				LISTS Lists;
				Lists.length=0;
				int flag[100];
				for(int i=0;i<100;i++){
							flag[i]=0;
						}
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
		     	
		     	case 1:{
		     		int n,e;
		     		printf("请输入要添加的图的个数：");
					scanf("%d",&n);
					while(n--)
   					{
    					scanf("%s",name);
   						Addg(Lists,name);
   						VertexType V[30];
      					KeyType VR[100][2];
      					int i=0,j;
					do {
					    scanf("%d%s",&V[i].key,V[i].others);
					} while(V[i++].key!=-1);
					i=0;
					do {
					    scanf("%d%d",&VR[i][0],&VR[i][1]);
					   } while(VR[i++][0]!=-1);
					if (CreateCraph(Lists.elem[Lists.length-1].G,V,VR)==ERROR) flag[Lists.length-1]=1;
					
					}
   					
   					printf("添加后的多图表为：");
   					for(n=0;n<Lists.length;n++)
   					{
   						printf("%s ",Lists.elem[n].name);
   						if(flag[n]==1) printf("输入数据错误\n"); 
   						else
   						for(j=0;j<Lists.elem[n].G.vexnum;j++)
				    {
				    	
			            ArcNode *p=Lists.elem[n].G.vertices[j].firstarc;
			            printf("%d %s",Lists.elem[n].G.vertices[j].data.key,Lists.elem[n].G.vertices[j].data.others);
			            while (p)
			            {
			                printf(" %d",p->adjvex);
			                p=p->nextarc;
			            }
			            
   						putchar('\n');
   					}}
   					getchar();getchar();
			 		break;}
			 	case 2: 
			 		printf("请输入要删除的线性表的名字：");
			 		scanf("%s",name);
				   if (Removeg(Lists,name)==OK){
				   		printf("删除后的线性表为：\n");
					   for(int n=0;n<Lists.length;n++)
   					{
   						printf("%s ",Lists.elem[n].name);
   						if(flag[i]==1) printf("输入数据错误"); 
   						else
   						for(j=0;j<Lists.elem[n].G.vexnum;j++)
				    {
				    	
			            ArcNode *p=Lists.elem[n].G.vertices[j].firstarc;
			            printf("%d %s",Lists.elem[n].G.vertices[j].data.key,Lists.elem[n].G.vertices[j].data.others);
			            while (p)
			            {
			                printf(" %d",p->adjvex);
			                p=p->nextarc;
			            }
			            
   						putchar('\n');
   					}}
					   }
				   else printf("删除失败");
			 
		    getchar();getchar();
			 break;
		case 3:{
			printf("请输入要查找的图的名字：");
			 scanf("%s",name);
			 int n=Locateg(Lists,name);
			   if (n)
			   		{
			   			printf("%s ",Lists.elem[n-1].name);
			   			if(flag[n-1]==1) printf("输入数据错误"); 
   						else
			   			for(j=0;j<Lists.elem[n-1].G.vexnum;j++)
				    {
				    	
			            ArcNode *p=Lists.elem[n-1].G.vertices[j].firstarc;
			            printf("%d %s",Lists.elem[n-1].G.vertices[j].data.key,Lists.elem[n-1].G.vertices[j].data.others);
			            while (p)
			            {
			                printf(" %d",p->adjvex);
			                p=p->nextarc;
			            }
			            putchar('\n');
			   		}
					   printf("\n是否对所查到的线性表进行单表操作？（Y or N）\n");
			         	char c;getchar();
			         	scanf("%c",&c);
						if(c=='Y') singleGraghOperation(Lists.elem[n-1].G); 
   						putchar('\n');
					   }
			   else printf("查找失败");
		    getchar();getchar();
			 break;}
		case 0:
	         break;
	     }
	     
		}
		case 0:
	         break;//end of switch
	  }//end of while
	
	}
	printf("欢迎下次再使用本系统！\n");
}
