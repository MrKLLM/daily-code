#pragma once
#include "link.h"
#include "public_defs.h"

// 全局链表头节点（外部可见）
extern Node* head;

/**
 * 初始化链表（创建空链表头）
 */
void initLink();

/**
 * 按编号查找志愿者
 * @param no 目标编号
 * @return 匹配的志愿者指针；NULL=未找到
 */
Volunteer* findVolunteerByNumber(int no);

/**
 * 插入志愿者（从insert.txt读取数据）
 * @param newVolun 待插入志愿者信息
 * @return 0=成功；负数=错误码
 */
int insertVolunteer(const Volunteer* newVolun);

/**
 * 按编号删除志愿者
 * @param no 目标编号
 * @return 0=成功；-1=未找到；负数=错误码
 */
int deleteVolunteer(int no);
