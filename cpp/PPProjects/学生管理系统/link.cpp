/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：link.cpp
* 文件标识：见配置管理计划书
* 摘    要：简易版单向链表，链表的首元节点之前有一个头结点
（1）仅仅完成链表的创建，以及增加、查询、删除节点功能；
（2）完成链表的计数功能
*
* 当前版本：1.0
* 作    者：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：2021年12月23日
*
* 取代版本：无
* 原作者  ：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：
*/

#include "link.h"
#include <string.h>

/// <summary>
/// 创建一个空链表，只有头结点
/// </summary>
/// <returns>如果为NULL则新增失败</returns>
Node* createLink()
{
	// 堆内存分配头结点，自动识别类型所需字节长度
	Node* head = new Node;
	
	// 判断是否成功申请堆内存
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		// 下一个节点为NULL
		head->next = NULL;
		return head;
	}
}

/// <summary>
/// 计算链表大小
/// </summary>
/// <param name="head">链表头指针,指针常量：head值不变，指向的内存区可变</param>
/// <returns>0：空链表</returns>
int getLinkSize(const Node*  head)
{
	if (head == NULL)
	{
		return -1;
	}
	
	//head = 0; 错误的
	
	// 遍历记录链表长度
	int size = 0;
	// 查找链表尾部
	Node* currNode = const_cast<Node*>(head);
	while (currNode->next != NULL)
	{
		currNode = currNode->next;
		size++;
	}
	
	return size;
}

/// <summary>
/// 在链表头部增加一个节点
/// </summary>
/// <param name="head">链表头指针</param>
/// <param name="newElem">新元素，常量指针，地址本身可变，防止该指针指向的内存区被修改</param>
/// <returns>1：新增成功；其它：失败</returns>
int addAtHead(Node* const head, const ElemType* newElem)
{
	if (head == NULL)
	{
		return 0;
	}
	
	if (newElem == NULL)
	{
		return -1;
	}
	
	//newElem = 007;
	
	// 在堆内存申请空间
	Node* newNode = new Node();   //新建新节点
	
	if (newNode == NULL)
	{
		return -2;    //申请失败
	}
	else
	{
		//    复制数据 memcpy
		newNode->data = *newElem;
		//newElem->score = 3;
		
		// 插入节点
		newNode->next = head->next;
		head->next = newNode;
		return 1;
	}
}

/// <summary>
/// 在链表尾部插入一个节点
/// </summary>
/// <param name="head">链表头指针，指针常量：防止头结点地址被修改</param>
/// <param name="newElem">新元素，防止该指针指向的内存区被修改</param>
/// <returns>1：新增成功；其它：失败</returns>
int addAtTail(Node* const head, const  ElemType* newElem)
{
	if (head == NULL)
	{
		return -1;
	}
	
	if (newElem == NULL)
	{
		return -2;
	}
	
	// 在堆内存申请空间
	Node* newNode = new Node();   //新建新节点
	
	if (newNode == NULL)
	{
		return -3;    //申请失败
	}
	else
	{
		//    复制数据
		newNode->data = *newElem;
		newNode->next = NULL;
		
		// 查找链表尾部
		Node* currNode = head;
		while (currNode->next != NULL)
		{
			currNode = currNode->next;
		}
		
		// 插入新节点
		currNode->next = newNode;
		
		return 1;
	}
}

/// <summary>
/// 查找链表index位置的元素（地址）
/// </summary>
/// <param name="head">链表头指针，指针常量：防止头结点地址被修改</param>
/// <param name="index">位置</param>
/// <returns>元素（地址）</returns>
ElemType* getElemAt(const Node*  head, int index)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	
	// 有头结点，计数需要加1 index++
	index++;        //    或者 currNode = head->next;
	
	// 查找链表
	Node* currNode = const_cast<Node*>(head);
	while (index--)
	{
		if (currNode->next != NULL)
		{
			currNode = currNode->next;
		}
		else
		{
			return NULL;
		}
	}
	
	return &(currNode->data);
}

/**
 * @brief 修改第i个节点的值
 *
 * @param head 头节点
 * @param index 修改位置
 * @param newStu 新节点的值
 *
 * @return 新节点的值
 */
ElemType* setElemAt(const Node*  head, int index, Student* newStu)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (index < 0)
	{
		return NULL;
	}
	
	// 有头结点，计数需要加1 index++
	index++;        //    或者 currNode = head->next;
	
	// 查找链表
	Node* currNode = const_cast<Node*>(head);
	while (index--)
	{
		if (currNode->next != NULL)
		{
			currNode = currNode->next;
		}
		else
		{
			return NULL;
		}
	}
	
	// 如果找到了，使用新节点内容，替换老节点内容
	if (index == -1)
	{
		//memcpy(&(currNode->data), newStu, sizeof(Student));
		currNode->data = (*newStu);
	}
	
	return &(currNode->data);//返回数据区地址
}

/// <summary>
/// 删除链表index位置的节点
/// </summary>
/// <param name="head">链表头指针，指针常量：防止头结点地址被修改</param>
/// <param name="index">位置</param>
/// <returns>1：操作成功；其它：失败</returns>
int delElemAt(Node* const head, int index)
{
	if (head == NULL)
	{
		return 0;
	}
	if (index < 0)
	{
		return -1;
	}
	
	// 查找链表
	Node* pre = head;                // 永远指向currNode的前一个节点
	Node* currNode = head->next;    // 指向需要查找的节点
	while ((index--) > 0)
	{
		if (currNode->next != NULL)
		{
			pre = currNode;                //    更新pre
			currNode = currNode->next;    //    移动到下一个节点
		}
		else
		{
			return -2;        //查无该节点
		}
	}
	
	// 删除节点
	pre->next = currNode->next;
	
	// 回收内存
	delete currNode;
	
	return 1;
}

/**
 * @brief 清空链表
 *
 * @param head 链表头结点
 */
void clearAllNode(Node* const head)
{
	int cnt = getLinkSize(head);
	while (cnt > 0)
	{
		delElemAt(head, cnt - 1);
		cnt --;
	}
}
