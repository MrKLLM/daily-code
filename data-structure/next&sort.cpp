#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
#define MAX ()
#endif

struct Snode{
	int data;
	Snode* sorts;
	Snode* next;
};

void LinkList_sort(Snode* head){
	head->sorts = nullptr;
	Snode* q = head ->next;
	while(q != nullptr){
		Snode* pre = head;
		Snode* p = pre->sorts;
		while(p != nullptr && q->data>p->data){
			pre = p;
			p = p->sorts;
		}
		q->sorts = p;
		pre->sorts = q;
		q = q->next;
	}
	
	
}

int main() {
	
	
	return 0;
}
