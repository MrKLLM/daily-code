/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：link.h
* 文件标识：见配置管理计划书
* 摘    要：简易版单向链表。
*
* 当前版本：1.0
* 作    者：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：2021年12月23日
*
* 取代版本：无
* 原作者  ：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：
*/
#pragma once
#include "public_defs.h"

#ifndef NULL    //判断这个宏是否被定义
#define NULL  (0)
#endif

// 类型定义方式，兼容C
typedef  Student ElemType;

// 单向链表节点
struct Node
{
	ElemType data;    // 自定义数据节点，使用typedef  Student ElemType;定义
	
	Node* next;        //指向 下一个节点
};



/**
 * 创建一个空队列，只有头结点
 */
Node* createLink();


/**
 * @brief 计算链表大小
 *
 * @param head 链表头指针
 *
 * @return 0：空链表
 */
int getLinkSize( const Node* head);

/// <summary>
/// 在链表头部增加一个节点
/// </summary>
/// <param name="head">队列头指针，指针常量，放置头结点地址被修改</param>
/// <param name="newElem">新元素，常量指针，防止该指针指向的内存区被修改</param>
/// <returns>1：新增成功；其它：失败</returns>
int addAtHead(Node* const head, const ElemType* newElem);

/// <summary>
/// 在链表尾部插入一个节点
/// </summary>
/// <param name="head">队列头指针，指针常量，放置头结点地址被修改</param>
/// <param name="newElem">新元素，常量指针，防止该指针指向的内存区被修改</param>
/// <returns>1：新增成功；其它：失败</returns>
int addAtTail(Node* const head, const  ElemType* newElem);

/// <summary>
/// 查找链表index位置的元素（返回地址）
/// </summary>
/// <param name="head">队列头指针，指针常量，放置头结点地址被修改</param>
/// <param name="index">位置</param>
/// <returns>元素（地址）</returns>
ElemType* getElemAt(const Node* head, int index);

/**
 * @brief 修改第i个节点的值
 *
 * @param head 头节点
 * @param index 修改位置
 * @param newStu 新节点的值
 *
 * @return 新节点的值
 */
ElemType* setElemAt(const Node*  head, int index, Student* newStu);

/// <summary>
/// 删除链表index位置的节点
/// </summary>
/// <param name="head">队列头指针，指针常量，放置头结点地址被修改</param>
/// <param name="index">位置</param>
/// <returns>1：操作成功；其它：失败</returns>
int delElemAt(Node* const head, int index);

/**
 * @brief 清空链表
 *
 * @param head 链表头结点
 */
void clearAllNode(Node* const head);
