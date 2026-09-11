#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX (100)
#endif

//邻接表表示的有向图
struct ArcNode{ //边结点
    int adjvex; //邻接点域
    ArcNode *next; //链域
};

struct VertexNode{ //顶点结点
    int vertex; //顶点域
    ArcNode *link; //边链头指针
};

struct Graph{
    VertexNode adjlist[MAX]; //邻接表
    int n, e; //顶点数和边数
    int vertexValues[MAX]; //顶点值数组
    int valueToIndex[MAX]; //顶点值到索引的映射
};

//检测是否存在从 vertexA 到 vertexB 的边
bool CheckEdgeExistence(const Graph &g, int vertexA, int vertexB){
    //遍历顶点 vertexA 的邻接表
    ArcNode *p = g.adjlist[vertexA].link;
    while(p != NULL){
        if(p->adjvex == vertexB){
            return true; //找到边<vertexA, vertexB>
        }
        p = p->next;
    }
    return false; //未找到
}

int main(){
    Graph g;
    
    cin >> g.n >> g.e;
    
    //读取顶点值
    for(int i = 1; i <= g.n; i++){
        cin >> g.vertexValues[i];
        g.valueToIndex[g.vertexValues[i]] = i;
    }
    
    //初始化邻接表
    for(int i = 1; i <= g.n; i++){
        g.adjlist[i].vertex = g.vertexValues[i];
        g.adjlist[i].link = NULL;
    }
    
    //前插法建立邻接表
    for(int i = 0; i < g.e; i++){
        int a, b;
        cin >> a >> b;
        
        //根据顶点值找到对应的索引
        int idxA = g.valueToIndex[a];
        int idxB = g.valueToIndex[b];
        
        //创建新边结点
        ArcNode *newNode = new ArcNode();
        newNode->adjvex = b;
        
        //前插法：插入到链表头部
        newNode->next = g.adjlist[idxA].link;
        g.adjlist[idxA].link = newNode;
    }
    
    //读取需要检测的边
    int vertexA, vertexB;
    cin >> vertexA >> vertexB;
    
    //根据顶点值找到对应的索引
    int idxA = g.valueToIndex[vertexA];
    
    //检测并输出结果
    if(CheckEdgeExistence(g, idxA, vertexB)){
        cout << 1 << endl;
    }else{
        cout << 0 << endl;
    }
    
    return 0;
}
