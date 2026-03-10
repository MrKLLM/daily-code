/*
* 文件名：input.cpp
* 摘 要：完成从文件读取志愿者信息
*/

#include "input.h"
#include "public_defs.h"
#include "link.h"
#include <fstream>

using namespace std;

/**
 * 函数功能：从指定文件（input.txt）读取所有志愿者信息，加载到链表中
 * 执行步骤：1. 校验文件名、链表头节点的合法性；2. 以只读模式打开文件；
 *          3. 清空链表原有数据；4. 按格式读取文件中所有志愿者信息，逐个插入链表尾部；5. 关闭文件
 * 参数说明：fileName - 待读取的志愿者信息文件名；head - 志愿者信息链表的头节点
 * 返回值：成功返回0；参数为空返回PARA_IS_NULL；文件打开失败返回FILE_OPEN_ERROR
 */
int input(const char* fileName, Node* const head) {
	// 参数合法性检查
	if (fileName == NULL || head == NULL) return PARA_IS_NULL;
	
	//以只读模式打开文件
	//通常搭配 ifstream（输入文件流）使用（ifstream 的默认打开模式就是 ios::in，所以有时会省略，但显式写出来更清晰）。
	ifstream file(fileName, ios::in);
	if (!file.is_open()) return FILE_OPEN_ERROR;//检测是否成功打开
	
	// 清空原有链表数据
	clearAllNode(head);
	
	// 按格式读取：number name age gender language grade（空格分隔）
	Volunteer tmp;
	while (file >> tmp.number >> tmp.name >> tmp.age >> tmp.gender >> tmp.language >> tmp.grade) {
		addAtTail(head, &tmp); // 插入链表尾部
	}
	
	// 关闭已打开的文件流，断开程序与物理文件的关联，并释放该文件占用的系统资源（如文件描述符、缓冲区资源等）。
	file.close();
	return 0;
}

/**
 * 函数功能：从指定文件（如insert.txt）读取一条志愿者信息，存入目标结构体
 * 执行步骤：1. 校验文件名、目标结构体的合法性；2. 以只读模式打开文件；
 *          3. 读取一条志愿者信息到目标结构体；4. 关闭文件
 * 参数说明：fileName - 待读取的文件名；q - 存储志愿者信息的目标结构体指针
 * 返回值：成功返回0；参数为空返回PARA_IS_NULL；文件打开失败返回FILE_OPEN_ERROR
 */
int input(const char* fileName, Volunteer* q) {
	if (fileName == NULL || q == NULL) return PARA_IS_NULL;
	
	ifstream file(fileName, ios::in);
	if (!file.is_open()) return FILE_OPEN_ERROR;
	
	// 读取一条插入信息（insert.txt仅存一条记录）
	file >> q->number >> q->name >> q->age >> q->gender >> q->language >> q->grade;
	
	file.close();
	return 0;
}

/**
 * 函数功能：从指定文件读取一个整数（用于获取菜单选项或志愿者编号）
 * 执行步骤：1. 校验文件名的合法性；2. 以只读模式打开文件；
 *          3. 读取整数到目标变量；4. 关闭文件
 * 参数说明：fileName - 待读取的文件名；num - 存储整数的目标变量引用
 * 返回值：成功返回0；参数为空返回PARA_IS_NULL；文件打开失败返回FILE_OPEN_ERROR
 */
int input(const char* fileName, int& num) {
	if (fileName == NULL) return PARA_IS_NULL;
	
	ifstream file(fileName, ios::in);
	if (!file.is_open()) return FILE_OPEN_ERROR;
	
	file >> num; // 读取菜单选项或编号
	file.close();
	return 0;
}
