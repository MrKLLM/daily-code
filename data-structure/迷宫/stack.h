//stack.h(栈定义，三元组)

#pragma once
#include <iostream>
using namespace std;

//三元组结构体
struct Triple
{
    int x,y;
    int dir;//方向:1~4
};

//栈节点
struct StackNode
{
    Triple data;
    StackNode* next;
};

//链栈
class LinkStack
{
private:
    StackNode* topPtr;//指向栈顶节点的指针
public:
    LinkStack();//构造
    ~LinkStack();//析构

    void push(int x,int y,int d);//入栈
    void pop();//出栈
    Triple top();//返回栈顶的数据
    bool empty();//判断栈是否为空
};

//方向
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

struct Pos
{
    int x,y;
};