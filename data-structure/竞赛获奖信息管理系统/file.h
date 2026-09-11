//file.h
//文件操作的头文件，包含文件读写函数的声明 

#pragma once
#include <string>
#include "link.h"

/**
 * @brief 从文件读取获奖信息
 * @param filename 文件名
 * @param list 链表
 * @return 成功返回true，失败返回false
 */
void ReadFromFile(const std::string& filename, LinkedList& list);

/**
 * @brief 将获奖信息保存到文件
 * @param filename 文件名
 * @param list 链表
 * @return 成功返回true，失败返回false
 */
bool WriteToFile(const std::string& filename, const LinkedList& list);

/**
 * @brief 清空文件内容
 * @param filename 文件名
 * @return 成功返回true，失败返回false
 */
bool EmptyFileDate(const std::string& filename);
