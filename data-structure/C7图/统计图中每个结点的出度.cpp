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

//统计每个顶点的出度
void CountOutDegree(const Graph &g){
    for(int i = 1; i <= g.n; i++){
        int degree = 0;
        ArcNode *p = g.adjlist[i].link;
        
        //遍历链表，统计边结点个数
        while(p != NULL){
            degree++;
            p = p->next;
        }
        
        cout << g.adjlist[i].vertex << " " << degree << endl;
    }
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
    
    //统计并输出每个顶点的出度
    CountOutDegree(g);
    
    return 0;
}