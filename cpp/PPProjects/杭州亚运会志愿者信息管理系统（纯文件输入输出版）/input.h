#pragma once
#include "public_defs.h"
#include "link.h"

/**
 * 从input.txt读取所有志愿者信息，初始化链表
 * @param fileName 输入文件名（固定为input.txt）
 * @param head 链表头节点
 * @return 0=成功；负数=错误码
 */
int input(const char* fileName, Node* const head);

/**
 * 从insert.txt读取一条待插入的志愿者信息
 * @param fileName 输入文件名（固定为insert.txt）
 * @param q 存储读取结果的节点指针
 * @return 0=成功；负数=错误码
 */
int input(const char* fileName, Volunteer* q);

/**
 * 从menu.txt/find.txt读取整数（菜单选项/查找/删除编号）
 * @param fileName 输入文件名（menu.txt或find.txt）
 * @param num 存储读取的整数
 * @return 0=成功；负数=错误码
 */
int input(const char* fileName, int& num);
