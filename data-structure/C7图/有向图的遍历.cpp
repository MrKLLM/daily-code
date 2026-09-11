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
};

//访问标记数组
bool visited[MAX];

//深度优先搜索（DFS）
void DFS(const Graph &g,int v){
    cout << v << ' ';
    visited[v] = 1;
    
    ArcNode *p = g.adjlist[v].link;
    while(p != NULL){
        int w = p->adjvex;
        if(!visited[w]){
            DFS(g, w);
        }
        p = p->next;
    }
}

//广度优先搜索
void BFS(const Graph &g,int start){
    queue<int> q;
    
    cout << start << ' ';
    visited[start] = 1;
    q.push(start);
    
    while(!q.empty()){
        int v = q.front();
        q.pop();
        
        ArcNode *p = g.adjlist[v].link;
        while(p != NULL){
            int w = p->adjvex;
            if(!visited[w]){
                cout << w << ' ';
                visited[w] = 1;
                q.push(w);
            }
            p = p->next;
        }
    }
}

int main(){
    Graph g;
    memset(visited, 0, sizeof(visited));
    
    cin >> g.n >> g.e;
    
    //初始化邻接表
    for(int i = 1; i <= g.n; i++){
        g.adjlist[i].vertex = i;
        g.adjlist[i].link = NULL;
    }
    
    //前插法建立邻接表
    for(int i = 0; i < g.e; i++){
        int a, b;
        cin >> a >> b;
        
        //创建新边结点
        ArcNode *newNode = new ArcNode();
        newNode->adjvex = b;
        
        //前插法：插入到链表头部
        newNode->next = g.adjlist[a].link;
        g.adjlist[a].link = newNode;
    }
    
    int start = 0;
    cin >> start;
    
    DFS(g, start);
    cout << endl;
    
    //重置访问标记数组
    memset(visited, 0, sizeof(visited));
    
    BFS(g, start);
    
    return 0;
}