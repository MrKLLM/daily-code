#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int m, n;
vector<vector<int> > maze;
int sx, sy, ex, ey;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

/* ========= BFS ========= */
int bfs() {
    if (maze[sx][sy] == 1 || maze[ex][ey] == 1)
        return -1;

    vector<vector<int> > dist(m + 1, vector<int>(n + 1, -1));
    queue<pair<int, int> > q;

    q.push(make_pair(sx, sy));
    dist[sx][sy] = 0;

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        int x = cur.first;
        int y = cur.second;

        if (x == ex && y == ey)
            return dist[x][y];

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
            if (maze[nx][ny] == 1) continue;
            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
    return -1;
}

/* ========= DFS ========= */
long long pathCount = 0;
vector<vector<bool> > vis;

void dfs(int x, int y) {
    if (x == ex && y == ey) {
        pathCount++;
        return;
    }

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
        if (maze[nx][ny] == 1) continue;
        if (vis[nx][ny]) continue;

        vis[nx][ny] = true;
        dfs(nx, ny);
        vis[nx][ny] = false;
    }
}

/* ========= main ========= */
int main() {
    cin >> m >> n;
    maze.resize(m + 1, vector<int>(n + 1));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> maze[i][j];

    cin >> sx >> sy >> ex >> ey;

    int shortest = bfs();
    cout << shortest << endl;

    if (shortest == -1) {
        cout << 0 << endl;
    } else {
        vis.assign(m + 1, vector<bool>(n + 1, false));
        vis[sx][sy] = true;
        dfs(sx, sy);
        cout << pathCount << endl;
    }

    return 0;
}