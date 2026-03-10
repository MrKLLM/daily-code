/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：input.cpp
* 文件标识：见配置管理计划书
* 摘    要：完成从控制台、文件读取学生信息
*
* 当前版本：1.0
* 作    者：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：2021年12月23日
*
* 取代版本：无
* 原作者  ：华北电力大学计算机系高级语言程序设计课程组
* 完成日期：
*/
#include "public_defs.h"
#include "input.h"
#include "student.h"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include "link.h"

using namespace std;

//两个接口（函数）对外开放
/*
各模块对外暴露的可调用函数（头文件中声明的函数）
这些函数是模块之间交互的唯一入口，其他模块只能通过这些接口使用对应功能，
而无需关心功能内部的实现细节（比如文件怎么读、链表怎么遍历）
*/


/**
 * @brief 从控制台读入一个学生信息
 *
 * @param stu 学生结构体指针
 *
 * @return 0：读取正常；其它：输入有误
 */
int read_from_console(Student *stu) {
	// 参数检查(指针一定要检查是否为空)
	if (stu == NULL) {
		return PARA_IS_NULL; // 定义统一的error code
	}
	
	cout << "请输入学生信息(学号 姓名 年龄 性别(m,f) 专业)：" << endl;
	int ret = ios::goodbit;
	
	cin >> (*stu).id;  // stu->id;
	ret |= cin.rdstate();
	
	cin >> (*stu).name;
	ret |= cin.rdstate();
	
	cin >> (*stu).age;
	ret |= cin.rdstate();
	
	cin >> (*stu).sex;
	ret |= cin.rdstate();
	
	cin >> (*stu).major;
	ret |= cin.rdstate();
	
	if (ret != ios::goodbit) {
		cin.clear();
		cin.sync();
		cout << "输入有误!" << endl;
	}
	
	return ret;
}
/**
 * @brief 从文件读取学生信息
 *
 * @param fromFile 文件名称
 * @param head 链表头节点
 *
 * @return
 */
int read_from_csv( Node *head, const char *fromFile) {
	// 参数检查
	if (head == NULL) {
		return PARA_IS_NULL; // 最好定义统一的error code
	}
	// 参数合法性检查
	if (fromFile == NULL) {
		return PARA_IS_NULL; // 最好定义统一的error code
	}
	
	// 读入文件句柄
	ifstream file;
	
	// 打开文件
	file.open(fromFile, ios::in);
	
	// 文件打开失败处理
	if (!file.is_open()) {
		return FILE_OPEN_ERROR;
	}
	
	string str = "";
	// 准备读取文本数据，并转为结构体存储
	int read_count = 0;
	
	// 未知文本多少行，使用while读取每一行数据
	while (getline(file, str)) {
		// 另一种方法，适合完整的数据
		istringstream input_str(str);
		Student tmp;
		input_str >> tmp.id >> tmp.name >> tmp.age >> tmp.sex >> tmp.major;
		
		// 保存数据
		addAtTail(head, &tmp);
		read_count++;
		
		// 防错处理,防止数组越界，非常容易出的问题
		if (read_count >= MAX_COUNT) {
			break;
		}
		
	}
	
	// 关闭文件
	file.close();
	return read_count;
}
