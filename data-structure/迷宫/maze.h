//maze.h(迷宫定义)

#pragma once
#include <iostream>
#include <vector>
using namespace std;

extern int maze[10][10];

void loadMaze(int m,int n);//加载迷宫

void PrintMaze();//打印迷宫

void PrintPath(const vector<Triple>& path);//打印路径

void dfsPath(int x, int y,
             int endX, int endY,
             bool visited[10][10],
             vector<Pos>& path,
             vector<vector<Triple>>& paths);

void findShortestPath(int startX, int startY, int endX, int endY);//找最短路径

void findAllPaths(int startX, int startY, int endX, int endY);//找所有路径
