//maze.cpp(方法实现)

#include "maze.h"
#include "stack.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//加载迷宫
void loadMaze(int m,int n)
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            maze[i][j] = 1;  // 默认为墙
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> maze[i][j];
        }   
    }
}

//打印路径，逆序输出
void PrintPath(const vector<Triple>& path)
{
    for (auto& t : path)
        cout << "(" << t.x << "," << t.y << "," << t.dir << ") ";
}

//打印迷宫
void PrintMaze()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

queue<Pos> q;

void findShortestPath(int startX, int startY, int endX, int endY)
{
    bool visited[10][10] = {false};
    Pos prev[10][10];  // 记录前驱节点
    
    // 初始化 prev 为 (-1,-1)
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            prev[i][j] = {-1, -1};
    
    queue<Pos> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    
    while (!q.empty()) {
        Pos cur = q.front();
        q.pop();
        
        // 方法1：出队时判断（更常见）
        if (cur.x == endX && cur.y == endY) {
            break;  // 找到终点，退出循环
        }
        
        for (int d = 1; d <= 4; d++) {
            int nx = cur.x + dx[d-1];
            int ny = cur.y + dy[d-1];
            
            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 &&
                !visited[nx][ny] && maze[nx][ny] == 0) {
                
                visited[nx][ny] = true;
                prev[nx][ny] = cur;  // ★ 记录：是谁带我来的
                q.push({nx, ny});
                
                // 方法2：入队时判断（也可以）
                // if (nx == endX && ny == endY) {
                //     // 找到终点，可以提前结束
                //     // 但要小心，可能队列里还有其他节点
                // }
            }
        }
    }
    
    // 还原路径
    vector<Triple> path;
    int x = endX, y = endY;
    
    // 从终点倒着走回起点
    while (!(x == -1 && y == -1)) {
        path.push_back({x, y, 0});
        Pos p = prev[x][y];
        x = p.x;
        y = p.y;
    }
    
    // 反转得到正确顺序
    reverse(path.begin(), path.end());
    
    // 输出
    cout << "最短路径（共" << path.size() << "步）：" << endl;
    for (auto& p : path) {
        cout << "(" << p.x << "," << p.y << ") ";
    }
    cout << endl;
}

void dfsPath(int x, int y,
             int endX, int endY,
             bool visited[10][10],
             LinkStack& path,
             vector<vector<Triple>>& paths)
{
    // 把栈里的路径导出来
    vector<Triple> onePath;
    // 从栈底到栈顶
    LinkStack temp = path;
    while (!temp.empty()) {
        Triple t = temp.top();
        onePath.push_back(t);
        temp.pop();
    }
    reverse(onePath.begin(), onePath.end());
    paths.push_back(onePath);

    visited[x][y] = true;
    
    for (int d = 1; d <= 4; d++)
    {
        int nx = x + dx[d-1];
        int ny = y + dy[d-1];

        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && 
            !visited[nx][ny] && maze[nx][ny] == 0)
        {
            //记录这一步
            path.push(nx,ny,d);
            //探索当前方向
            dfsPath(nx,ny,endX,endY,visited,path,paths);
            //回溯：弹出这一步
            path.pop();
            // visited[nx][ny] 不需要在这里重置，因为会在递归函数开头重置
        }
    }
    visited[x][y] = false;
}

void findAllPaths(int startX, int startY, int endX, int endY)
{
    LinkStack path;
    path.push(startX,startY,0);

    bool visited[10][10] = {false};
    vector<vector<Triple>> paths;

    dfsPath(startX,startY,endX,endY,visited,path,paths);

    for(int i = 0;i < paths.size();i++)
    {
        PrintPath(paths[i]);
        cout << endl;
    }
}