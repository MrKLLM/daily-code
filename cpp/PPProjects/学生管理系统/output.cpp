/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：output.cpp
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
#include "output.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "link.h"
#include "student.h"
#include "public_defs.h"
using namespace std;

/// <summary>
/// 终端打印一个结构体的值
/// </summary>
/// <param name="toData">数据来源</param>
int consolePrint(const Student *student) {
	// 参数合法性检查
	if (student == NULL) {
		return PARA_IS_NULL;
	}
	// cout << "......STATS OUT......" << endl;
	cout << "学号:" << student->id << ' ';
	cout << "姓名:" << student->name << ' ';
	cout << "年龄:" << student->age << ' ';
	cout << "性别:" << student->sex << ' ';
	cout << "专业:" << student->major << ' ';
	
	cout << endl;
	return 1;
}

/// <summary>
/// 学生转字符串
/// </summary>
/// <param name="outData">学生结构体</param>
/// <returns>学生字符串</returns>
string Stu2Str(const Student *student) {
	// 参数合法性检查
	if (student == NULL) {
		return NULL;
	}
	// 组合输出信息
	stringstream str;
	str << student->id << '\t';
	str << student->name << '\t';
	str << student->age << '\t';
	str << student->sex <<    '\t';
	str << student->major << '\t';
	return str.str();
}

/**
 * @brief 在控制台打印一个链表的学生数据
 *
 * @param head 链表头结点
 *
 * @return 是否打印成功,负数：错误码，正数：打印学生个数
 */
int consolePrintAllStudent(const Node *head) {
	// 参数合法性检查
	if (head == NULL) {
		return PARA_IS_NULL;
	}
	
	// 当前链表有多少学生
	int cnt = getLinkSize(head);
	cout << "学号 姓名 年龄 性别(m,f) 专业：" << endl;
	for (int i = 0; i < cnt; i++) {
		Student* tmp = getElemAt(head, i);
		string str = Stu2Str(tmp);
		cout << str << endl;
	}
	return cnt;
}

/// <summary>
/// 保存一个学生到文件
/// </summary>
/// <param name="toData">数据</param>
/// <param name="toFile">目标文件</param>
/// <returns></returns>
int save2file(const Student *outSingleStudent, const char *toFile) {
	// 参数检查，为什么反着写？
	if (NULL == outSingleStudent) {
		return PARA_IS_NULL;
	}
	if (NULL == toFile) {
		return PARA_IS_NULL;
	}
	
	// 读入文件句柄
	ofstream file;
	
	// 打开文件
	file.open(toFile, ios::out);
	
	// 文件打开失败处理
	if (!file.is_open()) {
		return FILE_OPEN_ERROR;
	}
	// 跳到文件结尾
	file.seekp(ios::end);
	
	// 写入数据
	file << Stu2Str(outSingleStudent) << endl;
	
	// 关闭文件
	file.close();
	return 1;
}

/// <summary>
/// 将链表保存到新的文件
/// </summary>
/// <param name="linkHead">链表头</param>
/// <param name="toFile">文件名</param>
/// <returns>是否保存成功</returns>
int saveLink2file(Node *const linkHead, const char *toFile) {
	// 参数检查，为什么反着写？
	if (NULL == linkHead) {
		return PARA_IS_NULL; // 以后定义errcode文件，用枚举
	}
	if (NULL == toFile) {
		return PARA_IS_NULL; // 以后定义errcode文件，用枚举
	}
	// 读入文件句柄
	ofstream file;
	
	// 打开文件，请大家思考为什么不是app模式
	file.open(toFile, ios::out);
	
	// 文件打开失败处理
	if (!file.is_open()) {
		return FILE_OPEN_ERROR;
	}
	
	int cnt = getLinkSize(linkHead);
	for (int i = 0; i < cnt; i++) {
		if (i > 0) {
			file << endl;
		}
		
		Student *stu = getElemAt(linkHead, i);
		// 写入数据
		file << Stu2Str(stu);
	}
	
	// 关闭文件
	file.close();
	return cnt;
}
