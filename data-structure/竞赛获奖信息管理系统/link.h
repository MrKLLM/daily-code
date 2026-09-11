//link.h
//链表数据结构定义和基本操作函数声明

#pragma once
#include <string>
#include "public_defs.h"

using namespace std;

/**
 * @brief 链表的基本数据节点
 * @details 用于存储实际数据（PrizeWinner）并维护指向下一个节点的指针，
 *          是构成整个链表的最小单元。
 */
struct Node
{
    PrizeWinner data;//节点数据
    Node* next;//指向下一个节点的指针
};

/**
 * @brief 链表的管理控制器
 * @details 包含头指针（head）、尾指针（tail）和长度（size），
 *          用于统一管理链表的状态，提供高效的插入、删除和查询操作。
 */
struct LinkedList
{
    Node* head;//指向链表头节点的指针
    Node* tail;//指向链表尾节点的指针(从尾部插入时使用)
    int size;//链表长度
};

//链表操作函数声明

/**
 * @brief 初始化链表
 * @param list 要初始化的链表
 */
Node* InitList(LinkedList& list);

/**
 * @brief 在链表末尾插入一个新的节点
 * @param list 要插入节点的链表
 * @param winner 要插入的数据（PrizeWinner）
 */
Node* InsertNode(LinkedList& list,Node* newNode);

/**
 * @brief 删除链表中满足条件的节点  
 * @param list 要删除节点的链表
 * @param winner 要删除的数据（PrizeWinner）
 */
void del_by_id_comp_lvl(LinkedList& list, const PrizeWinner& winner);

/**
 * @brief 创建一个新的节点
 * @param winner 要存储的数据（PrizeWinner）
 * @return 成功返回新节点的指针，失败返回nullptr
 */
Node* CreateNode(const PrizeWinner& winner);


 
