/*
* 文件名称：volunteer.cpp
* 摘    要：完成志愿者管理业务信息，主要功能有：
*        1. 初始化志愿者信息链表；
*        2. 根据编号查询志愿者信息；
*        3. 向链表尾部插入新志愿者信息；
*        4. 根据编号删除指定志愿者信息；
*/
#include "volunteer.h"
#include "link.h"
#include "public_defs.h"
using namespace std;

// 全局链表头节点实例化
Node* head = NULL;

void initLink() {
	if (head == NULL) {
		head = createLink();
	}
}

Volunteer* findVolunteerByNumber(int no) {
	if (head == NULL) return NULL;
	Node* prev = findPrevNode(head, no);
	return (prev != NULL) ? &(prev->next->data) : NULL;
}

int insertVolunteer(const Volunteer* newVolun) {
	if (head == NULL || newVolun == NULL) return PARA_IS_NULL;
	return (addAtTail(head, newVolun) == 1) ? 0 : -2;
}

int deleteVolunteer(int no) {
	if (head == NULL) return PARA_IS_NULL;
	Node* prev = findPrevNode(head, no);
	if (prev == NULL) return -1; // 未找到目标
	return deleteNode(head, prev) ? 0 : -3; // 删除节点
}
