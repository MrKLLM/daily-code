#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (0)
#endif

struct Tree{
    int val;
    Tree* lchild;
    Tree* rchild;
    Tree(int v):val(v),lchild(nullptr),rchild(nullptr){}
};

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a,b;
    cin >> a >> b;
    vector<Tree*> trees (16);//不用编号0

    //建树
    for (int i = 1; i <= 15; i++)
    {
        trees[i] = new Tree(i);//有构造函数，注意传参
        
    }
    
    //连节点
    for (int i = 1; i <= 7; i++)//倒数第二层有7个节点
    {
        trees[i]->lchild = trees[i*2];
        trees[i]->rchild = trees[i*2+1];
        
    }
    
    Tree* A = trees[a];//注意用指针
    Tree* B = trees[b];//注意用指针
    
    bool unconnected = true;
    if (A->lchild == B || A->rchild == B)
    {
        unconnected = false;
        
    }
    if (B->lchild == A || B->rchild == A)
    {
        unconnected = false;
        
    }
    
    if (unconnected)
    {
        cout << "No";
        
    }
    else
    {
        cout << "Yes";
        
    }
    

	return 0;
}
