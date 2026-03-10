/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：student.h
* 文件标识：见配置管理计划书
* 摘    要：完成学生管理业务信息，主要功能有：
*         1. 从文件初始化链表；
*         2. 在控制台显示所有学生信息；
*         3. 从控制台读取一个学生信息，并存入文件
*         4. 从控制台读取一个学号，删除该学生，并在文件中也删除；
*         5. 从控制台读取一个姓名关键字，依据关键字查询学生，并在控制台显示
*         6. 依据年龄升序对学生进行排序
*
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
#include "link.h"

/*
定义extern外部变量，只声明不初始化，在定义处才赋值
，而且变量名前加global(g_)
*/
// 如果需要将某个变量开放给其它模块
//    则应在该变量的定义模块使用extern声明为外部变量
// 学生信息链表头结点
extern Node* head;

/**
 * @brief 查看所有学生
 *
 * @param head 链表头结点
 */
void showAllStudent();

/**
 * @brief 新增学生
 *
 * @param head 链表头节点
 */
void addNewStudent();

/**
 * @brief 输入一个学号，删除该学生
 */
void deleteStudentByID();

/**
 * @brief 按照名字关键字找学生
 */
void findStudentByName();

/**
 * 按照年龄升序排序
 */
void sortStudentByAge();

/// @brief 查找 key 是否为 sourceStr 的子串
/// @param sourceStr 原字符串
/// @param key 要查找的key
/// @return 找到返回偏移位置，找不到返回-1
int findSubStr(char *sourceStr, char *key);

/**
 * @brief 在sourceStr中查找是否有 key
 *
 * @param key 带匹配的关键字
 * @param sourceStr 被查找的字符串
 *
 * @return 匹配到的位置，-1 表示没找到
 */
int findSubStr2(char *sourceStr, char *key);
