//stack.cpp(方法实现)

#include <iostream>
#include "stack.h"

using namespace std;

//在函数名前添加 LinkStack:: 作用域限定符，表明这是 LinkStack 类的成员函数
void LinkStack::push(int x,int y,int d)
{
    StackNode* newnode = new StackNode();
    newnode->data.x = x;
    newnode->data.y = y;
    newnode->data.dir = d;
    newnode->next = topPtr;
    topPtr = newnode;
}
//出栈
void LinkStack::pop()
{
    if(empty())
    {
        throw runtime_error("栈空");
    }
    StackNode* temp = topPtr;
    topPtr = topPtr->next;
    delete temp;
}
//返回栈顶的数据
Triple LinkStack::top()
{
    if(empty())
    {
        throw runtime_error("栈空");
    }
    return topPtr->data;
}

//判断栈是否为空
bool LinkStack::empty()
{
    return topPtr == nullptr;
}