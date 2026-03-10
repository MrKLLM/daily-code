/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：output.h
* 文件标识：见配置管理计划书
* 摘    要：完成在控制台输出学生信息、在文件中写入学生信息
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
#include "link.h"
#include "student.h"
#include <string>
#include <sstream>
using namespace std;

/// <summary>
/// 终端打印
/// </summary>
/// <param name="toData">数据来源</param>
int consolePrint(const Student* toData);
/// <summary>
/// 学生转字符串
/// </summary>
/// <param name="outData">学生结构体</param>
/// <returns>学生字符串</returns>
string Stu2Str(const Student *student);

/**
 * @brief 在控制台打印一个链表的学生数据
 *
 * @param head 链表头结点
 *
 * @return 是否打印成功,负数：错误码，正数：打印学生个数
 */
int consolePrintAllStudent(const Node *head);

/// <summary>
/// 保存到assic文件
/// </summary>
/// <param name="toData">数据</param>
/// <param name="toFile">目标文件</param>
/// <returns></returns>
int save2file(const Student* toData, const char* toFile);

/// <summary>
/// 将链表保存到新的文件
/// </summary>
/// <param name="linkHead">链表头</param>
/// <param name="toFile">文件名</param>
/// <returns>是否保存成功</returns>
int saveLink2file(Node* const linkHead, const char* toFile);
