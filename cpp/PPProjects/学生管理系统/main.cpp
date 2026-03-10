#include <iostream>
#include "public_defs.h"
#include "student.h"
#include "link.h"
#include "input.h"
#include "output.h"
using namespace std;

int main(int argc, char** argv) {
	bool to_run = true;        // 控制是否退出系统
	while (to_run) {
		int menu = 0;
		cout << "菜单 \t 1：查看所有；2：新增；3：按照学号删除；\n \t 4：按照姓名检索；5：按照年龄排序；9：退出" << endl;
		cin >> menu;
		switch (menu) {
		case 1:
			//TODO 列出所有学生
			showAllStudent();
			break;
		case 2:
			//TODO 新增一个学生
			addNewStudent();
			break;
		case 3:
			// 依据学号删除学生
			deleteStudentByID();
			break;
		case 4:
			// 模糊查找学生
			findStudentByName();
			break;
		case 5:
			// 排序
			sortStudentByAge();
			break;
		case 9:
			// 退出系统
			to_run = false;
			break;			// switch(意为中止switch)
		default:
			//TODO 非法菜单
			break;
		}
	}
	return 0;
}
