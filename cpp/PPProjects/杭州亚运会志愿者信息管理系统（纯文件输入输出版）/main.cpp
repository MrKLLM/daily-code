#include <iostream>
#include <fstream>
#include "public_defs.h"
#include "volunteer.h"
#include "input.h"
#include "output.h"
using namespace std;

// 实验要求的固定文件名
const char INPUT_FILE[] = "input.txt";
const char MENU_FILE[] = "menu.txt";
const char FIND_FILE[] = "find.txt";
const char INSERT_FILE[] = "insert.txt";
const char OUTPUT_FILE[] = "out.txt";

int main(int argc, char** argv) {
	// 1. 初始化链表
	initLink();
	if (head == NULL) {
		cout << "链表初始化失败！" << endl;
		return -1;
	}
	
	// 2. 读取菜单选项（从menu.txt）
	int menu = 0;
	int ret = input(MENU_FILE, menu);
	if (ret != 0) {
		cout << "读取菜单文件失败！错误码：" << ret << endl;
		clearAllNode(head);
		delete head;
		return ret;
	}
	
	// 3. 读取初始志愿者数据（从input.txt）
	ret = input(INPUT_FILE, head);
	if (ret != 0) {
		cout << "读取输入文件失败！错误码：" << ret << endl;
		clearAllNode(head);
		delete head;
		return ret;
	}
	
	// 4. 根据菜单执行对应功能
	switch (menu) {
		case 1: { // 查找功能：读取find.txt的编号，结果写入out.txt
		int findNo = 0;
		ret = input(FIND_FILE, findNo);
		if (ret != 0) {
			cout << "读取查找编号失败！错误码：" << ret << endl;
			break;
		}
		Volunteer* found = findVolunteerByNumber(findNo);
		if (found != NULL) {
			ret = output(found, OUTPUT_FILE);
			cout << (ret == 0 ? "查找成功，结果已写入out.txt" : "写入查找结果失败") << endl;
		} else {
			cout << "未找到编号为" << findNo << "的志愿者" << endl;
			ofstream file(OUTPUT_FILE, ios::out | ios::trunc); // 清空out.txt
			file.close();
		}
		break;
	}
		case 2: { // 插入功能：读取insert.txt的信息，结果写入out.txt
			Volunteer newVolun;
			ret = input(INSERT_FILE, &newVolun);
			if (ret != 0) {
				cout << "读取插入数据失败！错误码：" << ret << endl;
				break;
			}
			ret = insertVolunteer(&newVolun);
			if (ret == 0) {
				ret = output(head, OUTPUT_FILE);
				cout << (ret > 0 ? "插入成功，更新后数据已写入out.txt" : "写入插入结果失败") << endl;
			} else {
				cout << "插入失败！错误码：" << ret << endl;
			}
			break;
		}
		case 3: { // 删除功能：读取find.txt的编号，结果写入out.txt
			int delNo = 0;
			ret = input(FIND_FILE, delNo);
			if (ret != 0) {
				cout << "读取删除编号失败！错误码：" << ret << endl;
				break;
			}
			ret = deleteVolunteer(delNo);
			if (ret == 0) {
				ret = output(head, OUTPUT_FILE);
				cout << (ret >= 0 ? "删除成功，更新后数据已写入out.txt" : "写入删除结果失败") << endl;
			} else if (ret == -1) {
				cout << "未找到编号为" << delNo << "的志愿者" << endl;
				output(head, OUTPUT_FILE); // 输出原链表
			} else {
				cout << "删除失败！错误码：" << ret << endl;
			}
			break;
		}
	default:
		cout << "无效菜单选项！" << endl;
		output(head, OUTPUT_FILE); // 输出原链表
		break;
	}
	
	// 5. 释放资源
	clearAllNode(head);
	delete head;
	head = NULL;
	
	return 0;
}
