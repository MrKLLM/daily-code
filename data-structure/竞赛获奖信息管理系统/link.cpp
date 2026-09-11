//link.cpp
//底层链表操作函数定义


#include <string.h>
#include "link.h"

/**
 * @brief 初始化链表
 */
Node* InitList(LinkedList& list){
    list.head = new Node();
    if (list.head == nullptr)
    {
       return nullptr;
    }
    list.head->next=nullptr;
    list.tail = list.head;
    list.size=0;
    return list.head;
}

/**
 * @brief 在链表末尾插入一个新的节点
 */
Node* InsertNode(LinkedList& list,Node* newNode){
    list.tail->next = newNode;
    list.tail = newNode;
	return newNode;
}

/**
 * @brief 删除链表中满足条件的节点  
 */
void del_by_id_comp_lvl(LinkedList& list, const PrizeWinner& winner){
    Node* current = list.head;
    Node* pre = nullptr;
    
    while (current != nullptr)
    {
        if (current->data.id == winner.id && 
           current->data.competition == winner.competition && 
           current->data.prize_level == winner.prize_level)
        {	Node* next = current->next;
            if (pre != nullptr)
            {
                pre->next = next;
            }else {
				list.head = next;   // 删除的是头节点后的第一个数据节点
			}
			if (current == list.tail)
			{
				list.tail = pre;
				/* code */
			}
            delete current;
            list.size--;
			current = next;
        }
        pre = current;
        current = current->next;
    }
    return;
};

//创建节点
Node* CreateNode(const PrizeWinner& winner){
    Node* newNode = new Node();
    if (newNode == nullptr) {
        return nullptr;
    }
    newNode->data = winner;
    newNode->next = nullptr;
    return newNode;
}


