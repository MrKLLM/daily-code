#include "link.h"
#include <cstring>

Node* createLink() {
	Node* head = new Node();
	if (head == NULL) return NULL;
	head->next = NULL;
	return head;
}

int getLinkSize(const Node* head) {
	if (head == NULL) return -1;
	int size = 0;
	Node* curr = const_cast<Node*>(head);
	while (curr->next != NULL) {
		curr = curr->next;
		size++;
	}
	return size;
}

int addAtTail(Node* const head, const ElemType* newElem) {
	if (head == NULL || newElem == NULL) return -1;
	Node* newNode = new Node();
	if (newNode == NULL) return -2;
	
	// 复制数据
	newNode->data = *newElem;
	newNode->next = NULL;
	
	// 找到链表尾部
	Node* curr = head;
	while (curr->next != NULL) curr = curr->next;
	curr->next = newNode;
	return 1;
}

Node* findPrevNode(Node* const head, int no) {
	if (head == NULL) return NULL;
	Node* prev = head;
	Node* curr = head->next;
	while (curr != NULL) {
		if (curr->data.number == no) return prev; // 返回前一个节点
		prev = curr;
		curr = curr->next;
	}
	return NULL; // 未找到
}

int deleteNode(Node* const head, Node* prev) {
	if (head == NULL || prev == NULL || prev->next == NULL) return 0;
	Node* delNode = prev->next;
	prev->next = delNode->next;
	delete delNode; // 释放内存
	return 1;
}

void clearAllNode(Node* const head) {
	if (head == NULL) return;
	Node* curr = head->next;
	while (curr != NULL) {
		Node* temp = curr;
		curr = curr->next;
		delete temp;
	}
	head->next = NULL;
}
