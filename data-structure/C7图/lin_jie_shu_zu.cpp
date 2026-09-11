#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX (100)
#endif

//邻接矩阵表示的有向图
struct Graph{
	// int vertex[MAX];
	int edge[MAX][MAX];//有边为1，无边为0
	int n,e;
};

//访问标记数组
bool visited[MAX];

//深度优先搜索（DFS）
void DFS(const Graph &g,int v){
	cout << v << ' ';
	visited[v] = 1;

	for (int i = 1; i <= g.n; i++)
	{
		if (g.edge[v][i] == 1 && !visited[i])
		{
			DFS(g,i);
		}
		
	}
	
}

//广度优先搜索
void BFS(const Graph &g,int start){
	queue<int> q;

	cout << start << ' ';
	visited[start] = 1;
	q.push(start);

	while(!q.empty()){
		int v = q.front();//存队头元素
		q.pop();//踢出去队头元素

		for (int i = 1; i <= g.n; i++)
		{
			if (g.edge[v][i] == 1 && !visited[i])
			{
				cout << i << ' ';
				visited[i] = 1;
				q.push(i);
			}
			
		}
		
	}
}

int main(){
	Graph g;

	memset(g.edge,0,sizeof(g.edge));
	memset(visited,0,sizeof(visited));

	cin >> g.n >> g.e;
	for (int i = 0; i < g.e; i++)
	{
		int a,b;
		cin >> a >> b;
		g.edge[a][b] = 1;
	}

	int start = 0;
	cin >> start;

	DFS(g,start);
	cout << endl;

	// 重置访问标记数组，为 BFS 做准备
	memset(visited,0,sizeof(visited));

	BFS(g,start);
	
	return 0;
}

    
//     // 深度优先遍历
//     DFS(g, start);
//     cout << endl;
    
//     // 重置访问标记
//     memset(visited, false, sizeof(visited));
    
//     // 广度优先遍历
//     BFS(g, start);
//     cout << endl;
    
//     return 0;
// }
