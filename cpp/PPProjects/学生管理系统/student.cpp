/*
* Copyright (c) 2021,华北电力大学计算机系高级语言程序设计课程组
* All rights reserved.
*
* 文件名称：student.cpp
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
#include "student.h"
#include "link.h"
#include <string.h>
#include "input.h"
#include "output.h"
#include <iostream>

using namespace std;

// 默认持久化存储的文件名
const char fileName[20] = "students.txt";

// 学生信息链表头结点
Node* head = NULL;

/**
 * @brief 从文件初始化链表
 */
void reloadLinkFromFile()
{
	if (NULL == head)
	{
		head = createLink();
	}
	
	// 清空旧链表数据
	clearAllNode(head);
	// 从数据文件重新初始化链表
	read_from_csv(head, fileName);
}

/**
 * @brief 查看所有学生
 *
 * @param head 链表头结点
 */
void showAllStudent()
{
	//    从文件初始化链表
	reloadLinkFromFile();
	// 控制台打印链表
	consolePrintAllStudent(head);
}

/**
 * @brief 新增学生
 *
 * @param head 链表头节点
 */
void addNewStudent()
{
	//    从文件初始化链表
	reloadLinkFromFile();
	
	Student tmp;    // 新录入的学生节点
	// 从控制台读入学生信息
	int ret = read_from_console(&tmp);
	
	if (ret == 0)      // 如果输入正常
	{
		// 保存到链表
		addAtTail(head, &tmp);
		// 存到文件
		saveLink2file(head, fileName);
		cout << "保存成功,学号为：" << tmp.id << endl;
	}
	
}

/**
 * @brief 输入一个学号，删除该学生
 */
void deleteStudentByID()
{
	//    从文件初始化链表
	reloadLinkFromFile();
	
	cout << "请输入待删除学生学号:" << endl;
	char key[20] {};    // 缓存学号
	cin >> key;        // 读入学号
	
	bool isFind = false;    // 标记是否找到学生
	for (int i = 0; i < getLinkSize(head); i++)
	{
		// 遍历每个学生
		Student* stu = getElemAt(head, i);
		// 如果找到了该学生,如果是相等关系 使用 strcmp
		if (findSubStr(stu->id, key) >= 0)
		{
			isFind = true;
			// 提示用户是否删除
			cout << "是否删除学生?(Y删除，N跳过)" << stu->id << endl;
			char ch = 'N';
			cin >> ch;        // 读取用户输入
			if (ch == 'Y')      // 删除学生
			{
				cout << "\t 删除学生：" << stu->id << "成功！" << endl;
				delElemAt(head, i);
			}
			else          // 跳过删除
			{
				cout << "\t 跳过删除该学生(输入Y才删除)。" << endl;
			}
		}
	}
	if (isFind)      // 如果删除过学生，则持久化到文件中
	{
		saveLink2file(head, fileName);
	}
	else      // 不需要修改学生文件
	{
		cout << "没有找到学生：" << key << endl;
	}
}
/**
 * @brief 按照名字关键字找学生
 */
void findStudentByName()
{
	//    从文件初始化链表
	reloadLinkFromFile();
	
	cout << "请输入检索学生名字关键字:" << endl;
	char key[20] {};
	cin >> key;        // 输入学生名字关键字
	
	bool isFind = false;    // 标记是否找到
	for (int i = 0; i < getLinkSize(head); i++)
	{
		// 遍历每个学生
		Student* stu = getElemAt(head, i);
		// 如果找到了
		if (findSubStr2(stu->name, key) >= 0)
		{
			// 打印找到的学生清单
			cout << "找到学生：" << Stu2Str(stu) << endl;
			isFind = true;
		}
	}
	if (!isFind)      // 如果没有找到
	{
		cout << "没有找到学生：" << key << endl;
	}
}

/**
 * 按照年龄升序排序
 */
void sortStudentByAge()
{
	//    从文件初始化链表
	reloadLinkFromFile();
	//    找到学生个数
	int cnt = getLinkSize(head);
	// 排序算法，年龄升序排序
	for (int i = 0; i < cnt; i++)
	{
		for (int j = i + 1; j < cnt; j++)
		{
			if (getElemAt(head, i)->age > getElemAt(head, j)->age)
			{
				// 交换节点
				Student tmp;
				tmp = *(getElemAt(head, i));
				setElemAt(head, i, getElemAt(head, j));
				setElemAt(head, j, &tmp);
			}
		}
	}
	cout << "排序成功！" << endl;
	consolePrintAllStudent(head);    // 输出排序结果
	
	cout << "存入文件！" << endl;
	saveLink2file(head, fileName);    // 存文件
}
/// @brief 查找 key 是否为 sourceStr 的子串
/// @param sourceStr 原字符串
/// @param key 要查找的key
/// @return 找到返回偏移位置，找不到返回-1
int findSubStr(char *sourceStr, char *key)
{
	// 被查key长于原串
	if (strlen(sourceStr) < strlen(key))
	{
		return -1;
	}
	
	for (size_t offset = 0; offset <= strlen(sourceStr) - strlen(key); offset++)
	{
		bool match = true;
		for (size_t i = 0; i < strlen(key); i++)
		{
			if (*(sourceStr + offset + i) != *(key + i))
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			return offset;
		}
	}
	
	return -1;
}

/**
 * @brief 在sourceStr中查找是否有 key
 *
 * @param key 带匹配的关键字
 * @param sourceStr 被查找的字符串
 *
 * @return 匹配到的位置，-1 表示没找到
 */
int findSubStr2(char *sourceStr, char *key)
{
	// 被查key长于原串
	if (strlen(sourceStr) < strlen(key))
	{
		return -1;
	}
	
	string src(sourceStr);
	string tmp_key(key);
	
	string::size_type position = src.find(tmp_key);
	
	if (position != src.npos)
	{
		return position;
	}
	else
	{
		return -1;
	}
}
