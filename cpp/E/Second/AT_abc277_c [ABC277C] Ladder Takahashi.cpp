#include<iostream>
#include<queue>
#include <unordered_map>
#include <unordered_set>
#include<vector>
#include <algorithm>

using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n;
    cin >> n;
    unordered_map<int,vector<int>> graph;//无向图
    for (int i = 0; i < n; i++)
    {
        int a,b;
        cin >> a >>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    unordered_set<int> visited;//到过过的楼层
    queue<int> q;
    q.push(1);
    visited.insert(1);//到过则入队
    int max_floor = 1;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();//出队
        max_floor = max(max_floor,node);//看现在所在楼层是否为历史最高

        if (graph.find(node) != graph.end() )//找得到node节点
        {
            //插入一级邻居
            for (int neighbor : graph[node])
            {
                if (visited.find(neighbor) == visited.end())//未访问过则入队
                {   
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
                
            }
            
        }
    }
    cout << max_floor<<endl;
    
	return 0;
}
