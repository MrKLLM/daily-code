//main.cpp(主函数)

#include "maze.h"
#include "stack.h"
#include <iostream>
using namespace std;

int main()
{
    int m,n;
    cin >> m >> n;
    int startX, startY, endX, endY;
    cin >> startX >> startY >> endX >> endY;
    loadMaze(m,n);
    PrintMaze();
    findShortestPath(startX, startY, endX, endY);
    findAllPaths(startX, startY, endX, endY);
    return 0;
}