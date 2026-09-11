/**prize_winner.h
 * @brief 奖项获奖者信息结构体定义和业务逻辑层函数声明
 */

#pragma once
#include <string>
#include "link.h"
#include "public_defs.h"

/**
 * @brief 显示链表中所有节点的信息
 * @param list 要显示的链表
 */
void ShowAllMsg(const LinkedList& list);

/**
 * @brief 在链表末尾插入一个新的节点
 * @param list 要插入节点的链表
 * @param winner 要插入的数据（PrizeWinner）
 */
void InsertElement(LinkedList& list, const PrizeWinner& winner);  

/**
 * @brief 删除链表中满足条件的节点
 * @param list 要删除节点的链表
 * @param id 要删除的节点的学号
 * @param competition 要删除的节点的比赛名称
 * @param prize_level 要删除的节点的奖项等级
 */
void DelElement(LinkedList& list, long long  id,std::string competition,char prize_level);

/**
 * @brief 删除链表中满足条件的节点
 * @param list 要删除节点的链表
 * @param competition 要删除的节点的比赛名称
 */
void DelCompetition(LinkedList& list,std::string competition);

/**
 * @brief 查找链表中满足条件的节点并显示其信息
 * @param list 要查找节点的链表
 * @param id 要查找的节点的学号
 */
void FindMsgByStuNO(LinkedList& list,long long id);

/**
 * @brief 查找链表中满足条件的节点并显示其信息
 * @param list 要查找节点的链表
 * @param competition 要查找的节点的比赛名称
 */
void FindMsgByCompetition(LinkedList& list,std::string competition);

/**
 * @brief 清空链表
 * @param list 要清空的链表
 */
void EmptyList(LinkedList& list);

/**
 * @brief 保存所有信息获奖信息
 * @param list 要保存信息的链表
 */
void SaveAllMsgTofile(const LinkedList& list);

/**
 * @brief 删除指定学生所有获奖信息
 * @param list 要查找节点的链表
 * @param id 某人学号
 */
void DeleteMsgByStuNo(LinkedList& list,long long id);