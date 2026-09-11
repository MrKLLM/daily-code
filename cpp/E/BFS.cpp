#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u); // 无向图
    }

    vector<int> dist(n + 1, -1); // -1 表示未访问
    queue<int> q;

    int start = 1;          // 假设从城市 1 开始 BFS
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (dist[v] == -1) {   // 未访问
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // 输出每个点到起点的最短距离
    for (int i = 1; i <= n; i++) {
        cout << "City " << i << ": " << dist[i] << endl;
    }

    return 0;
}