/*
* 文件名称：output.cpp
* 摘    要：完成在文件中写入志愿者信息
*/
#include "output.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//string Volun2Str(const Volunteer* volunteer) {
//	if (volunteer == NULL) return "";
//	string str;
//	// 格式：number name age gender language grade（空格分隔）
//	str += to_string(volunteer->number) + " ";
//	str += volunteer->name + string(" ");
//	str += to_string(volunteer->age) + " ";
//	str += volunteer->gender + string(" ");
//	str += volunteer->language + string(" ");
//	str += to_string(volunteer->grade);
//	return str;
//}

// 加 static：仅限 output.cpp 内部可见，避免全局符号冲突
static string int2str(int value) {
	stringstream ss;
	ss << value;
	return ss.str();
}


string Volun2Str(const Volunteer* volunteer) {
	// 仅调用本文件的 int2str
	if (volunteer == NULL) return "";
	string str;
	str += int2str(volunteer->number) + " ";
	str += volunteer->name + string(" ");
	str += int2str(volunteer->age) + " ";
	str += volunteer->gender + string(" ");
	str += volunteer->language + string(" ");
	str += int2str(volunteer->grade);
	return str;
}


int output(Node* const head, const char* fileName) {
	if (head == NULL || fileName == NULL) return PARA_IS_NULL;
	
	// 覆盖写入（实验样例要求每次功能执行后更新out.txt）
	ofstream file(fileName, ios::out | ios::trunc);
	if (!file.is_open()) return FILE_OPEN_ERROR;
	
	int cnt = 0;
	Node* curr = head->next;
	while (curr != NULL) {
		file << Volun2Str(&curr->data) << endl; // 每条记录占一行
		curr = curr->next;
		cnt++;
	}
	
	file.close();
	return cnt;
}

int output(const Volunteer* volun, const char* fileName) {
	if (volun == NULL || fileName == NULL) return PARA_IS_NULL;
	
	ofstream file(fileName, ios::out | ios::trunc);
	if (!file.is_open()) return FILE_OPEN_ERROR;
	
	file << Volun2Str(volun) << endl; // 查找结果仅输出匹配记录
	file.close();
	return 0;
}
