#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n,m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);//不用0，n个城市
    for (size_t i = 0; i < m; i++)//m条边
    {
        int a,b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);//无向图
    }
    
    for (size_t i = 1; i <= n; i++)
    {
        sort(graph[i].begin(),graph[i].end());
    }
    
    for (size_t i = 1; i <= n; i++)
    {
        int city_cnt = graph[i].size();
        cout << city_cnt << " ";
        for (size_t j = 0; j < city_cnt; j++)
        {
            cout << graph[i][j] << " ";
            /* code */
        }
        cout << endl;
        /* code */
    }
    
	return 0;
}
