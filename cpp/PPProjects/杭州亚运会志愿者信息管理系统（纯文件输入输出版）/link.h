#pragma once
#include "public_defs.h"

// 链表节点数据类型（兼容Volunteer结构体）
typedef Volunteer ElemType;

// 单向链表节点结构
struct Node {
	ElemType data; // 节点数据
	Node* next;    // 下一个节点指针
};

/**
 * 创建空链表（仅头节点）
 * @return 头节点指针；NULL表示创建失败
 */
Node* createLink();

/**
 * 计算链表长度（有效节点数）
 * @param head 链表头节点
 * @return 节点数；负数表示错误
 */
int getLinkSize(const Node* head);

/**
 * 链表尾部插入节点（实验指导书append功能）
 * @param head 头节点（不可修改地址）
 * @param newElem 待插入数据
 * @return 1=成功；负数=失败
 */
int addAtTail(Node* const head, const ElemType* newElem);

/**
 * 查找目标编号的前一个节点（实验指导书要求，便于删除）
 * @param head 头节点
 * @param no 目标志愿者编号
 * @return 前一个节点指针；NULL=未找到
 */
Node* findPrevNode(Node* const head, int no);

/**
 * 删除指定位置节点
 * @param head 头节点
 * @param prev 目标节点的前一个节点
 * @return 1=成功；0=失败
 */
int deleteNode(Node* const head, Node* prev);

/**
 * 清空链表（保留头节点）
 * @param head 头节点
 */
void clearAllNode(Node* const head);
