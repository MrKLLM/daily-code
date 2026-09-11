#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif

/*
1.观察题目样例输出知，用尾插法
2.先遍历链表，找到要移动的结点
3.先用临时变量保存要移动的结点，再将要移动的结点从链表中删除
4.将要移动的结点插入到链表的尾部
*/

struct Node{
    int data;
    Node *link;
};

void FindMaxAndMaxprev(Node *list,Node*& max,Node*& max_prev){
    if(list == NULL){
        return;
    }
    Node* p = list;
    Node* prev= NULL;
    while(p != NULL){
        if(p->data > max->data){
            max = p;
            max_prev = prev;
        }
		prev = p;
        p = p->link;
    }
    return;
}

void MoveNode(Node*& list,Node *&tail){
	if(list == NULL){
		return;
	}
    Node *max = list;
    Node *max_prev = NULL;
    FindMaxAndMaxprev(list,max,max_prev);
	
	if(max == tail){
		return;
	}
	//删
	if(max_prev == NULL){
		list = max->link;
	}else{
		max_prev->link = max->link;
	}
	//断max和原来链表的链接
	max->link = NULL;
    //插
    tail->link = max;
    tail = max;
	return;
}

int main() {
	Node* list = NULL;
	
    int tmp;
    Node* tail = NULL;
    while (cin >> tmp)
    {   Node* tmp_node = new Node();
        tmp_node->data = tmp;
		if(tail == NULL){
			tail = tmp_node;
			list = tail;
		}else{
			tail->link = tmp_node;
			tail = tmp_node;
		}
        
    }
    MoveNode(list,tail);
    Node* curr = list;
    while (curr != NULL)
    {
        cout << curr->data << ' ';
        curr=curr->link;
        /* code */
    }
    
	return 0;
}
