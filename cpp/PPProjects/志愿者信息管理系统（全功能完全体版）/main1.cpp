#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 100
using namespace std;

//志愿者结构体
struct volunteer {
	int number;
	char name[20];
	int age;
	char gender;
	char language[10];
	int grade;
	volunteer* next;
};

// ---------------------- 原有函数保留（未修改）----------------------
//显示所有志愿者信息（控制台输出）
void displayAllVolunteers(volunteer* head) {
	volunteer* curr = head;
	while (curr != NULL) {
		cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		curr = curr->next;
	}
}

//修改志愿者信息
void modifyVolunteer(volunteer* head, int number, const char* newName, int newAge, char newGender, const char* newLanguage, int newGrade) {
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->number == number) {
			strcpy(curr->name, newName);
			curr->age = newAge;
			curr->gender = newGender;
			strcpy(curr->language, newLanguage);
			curr->grade = newGrade;
			break;
		}
		curr = curr->next;
	}
}

//用序号查询志愿者信息
void queryVolunteerByNumber(volunteer* head, int number) {
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->number == number) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
			break;
		}
		curr = curr->next;
	}
}

//模糊查询志愿者姓名
void fuzzyQueryByName(volunteer* head, const char* namePart) {
	volunteer* curr = head;
	while (curr != NULL) {
		if (strstr(curr->name, namePart) != NULL) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//按姓名删除志愿者信息
volunteer* deleteVolunteerByName(volunteer* head, const char* name) {
	volunteer* prev = NULL;
	volunteer* curr = head;
	while (curr != NULL) {
		if (strcmp(curr->name, name) == 0) {
			if (prev == NULL) {
				head = head->next;
			} else {
				prev->next = curr->next;
			}
			delete curr;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	return head;
}

//按成绩删除志愿者信息
volunteer* deleteVolunteerByGrade(volunteer* head, int grade) {
	volunteer* prev = NULL;
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->grade == grade) {
			if (prev == NULL) {
				head = head->next;
			} else {
				prev->next = curr->next;
			}
			delete curr;
			// 继续查找同成绩的志愿者（可能有多个）
			curr = (prev == NULL) ? head : prev->next;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	return head;
}

//按位置删除志愿者信息（位置从0开始）
volunteer* deleteVolunteerByPosition(volunteer* head, int position) {
	if (position < 0) return head; // 无效位置直接返回
	if (position == 0) {
		if (head != NULL) {
			volunteer* temp = head;
			head = head->next;
			delete temp;
		}
		return head;
	}
	volunteer* prev = head;
	for (int i = 0; i < position - 1 && prev != NULL; i++) {
		prev = prev->next;
	}
	if (prev != NULL && prev->next != NULL) {
		volunteer* temp = prev->next;
		prev->next = prev->next->next;
		delete temp;
	}
	return head;
}

//志愿者平均年龄
double averageAge(volunteer* head) {
	int count = 0;
	int sum = 0;
	volunteer* curr = head;
	while (curr != NULL) {
		sum += curr->age;
		count++;
		curr = curr->next;
	}
	return count == 0 ? 0 : (double)sum / count;
}

//志愿者平均成绩
double averageGrade(volunteer* head) {
	int count = 0;
	double sum = 0;
	volunteer* curr = head;
	while (curr != NULL) {
		sum += curr->grade;
		count++;
		curr = curr->next;
	}
	return count == 0 ? 0 : sum / count;
}

//志愿者年龄排序 (从小到大)
volunteer* sortByAge(volunteer* head) {
	if (head == NULL) return head;
	bool swapped;
	volunteer* ptr1;
	volunteer* lptr = NULL;
	do {
		swapped = false;
		ptr1 = head;
		while (ptr1->next != lptr) {
			if (ptr1->age > ptr1->next->age) {
				// 交换整个节点数据
				int tempNumber = ptr1->number;
				char tempName[20];
				strcpy(tempName, ptr1->name);
				int tempAge = ptr1->age;
				char tempGender = ptr1->gender;
				char tempLanguage[10];
				strcpy(tempLanguage, ptr1->language);
				int tempGrade = ptr1->grade;
				
				ptr1->number = ptr1->next->number;
				strcpy(ptr1->name, ptr1->next->name);
				ptr1->age = ptr1->next->age;
				ptr1->gender = ptr1->next->gender;
				strcpy(ptr1->language, ptr1->next->language);
				ptr1->grade = ptr1->next->grade;
				
				ptr1->next->number = tempNumber;
				strcpy(ptr1->next->name, tempName);
				ptr1->next->age = tempAge;
				ptr1->next->gender = tempGender;
				strcpy(ptr1->next->language, tempLanguage);
				ptr1->next->grade = tempGrade;
				
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

//志愿者成绩排序(从低到高)
volunteer* sortByGrade(volunteer* head) {
	if (head == NULL) return head;
	bool swapped;
	volunteer* ptr1;
	volunteer* lptr = NULL;
	do {
		swapped = false;
		ptr1 = head;
		while (ptr1->next != lptr) {
			if (ptr1->grade > ptr1->next->grade) {
				// 交换整个节点数据
				int tempNumber = ptr1->number;
				char tempName[20];
				strcpy(tempName, ptr1->name);
				int tempAge = ptr1->age;
				char tempGender = ptr1->gender;
				char tempLanguage[10];
				strcpy(tempLanguage, ptr1->language);
				int tempGrade = ptr1->grade;
				
				ptr1->number = ptr1->next->number;
				strcpy(ptr1->name, ptr1->next->name);
				ptr1->age = ptr1->next->age;
				ptr1->gender = ptr1->next->gender;
				strcpy(ptr1->language, ptr1->next->language);
				ptr1->grade = ptr1->next->grade;
				
				ptr1->next->number = tempNumber;
				strcpy(ptr1->next->name, tempName);
				ptr1->next->age = tempAge;
				ptr1->next->gender = tempGender;
				strcpy(ptr1->next->language, tempLanguage);
				ptr1->next->grade = tempGrade;
				
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
	return head;
}

//所有年龄最大的志愿者（数据写入文件，中文提示输出到控制台）
void findMaxAgeVolunteers(volunteer* head, ofstream& outFile) {
	if (head == NULL) return;
	int maxAge = head->age;
	volunteer* curr = head;
	// 查找最大年龄
	while (curr != NULL) {
		if (curr->age > maxAge) {
			maxAge = curr->age;
		}
		curr = curr->next;
	}
	// 控制台输出中文提示
	cout << "年龄最大的志愿者年龄为：" << maxAge << endl;
	// out.txt仅写入数据，无汉字
	curr = head;
	while (curr != NULL) {
		if (curr->age == maxAge) {
			outFile << curr->number << " " << curr->name << " " << curr->age << " " 
			<< curr->gender << " " << curr->language << " " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有年龄最小的志愿者（数据写入文件，中文提示输出到控制台）
void findMinAgeVolunteers(volunteer* head, ofstream& outFile) {
	if (head == NULL) return;
	int minAge = head->age;
	volunteer* curr = head;
	// 查找最小年龄
	while (curr != NULL) {
		if (curr->age < minAge) {
			minAge = curr->age;
		}
		curr = curr->next;
	}
	// 控制台输出中文提示
	cout << "年龄最小的志愿者年龄为：" << minAge << endl;
	// out.txt仅写入数据，无汉字
	curr = head;
	while (curr != NULL) {
		if (curr->age == minAge) {
			outFile << curr->number << " " << curr->name << " " << curr->age << " " 
			<< curr->gender << " " << curr->language << " " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有成绩最高的志愿者（数据写入文件，中文提示输出到控制台）
void findMaxGradeVolunteers(volunteer* head, ofstream& outFile) {
	if (head == NULL) return;
	int maxGrade = head->grade;
	volunteer* curr = head;
	// 查找最高成绩
	while (curr != NULL) {
		if (curr->grade > maxGrade) {
			maxGrade = curr->grade;
		}
		curr = curr->next;
	}
	// 控制台输出中文提示
	cout << "成绩最高的志愿者成绩为：" << maxGrade << endl;
	// out.txt仅写入数据，无汉字
	curr = head;
	while (curr != NULL) {
		if (curr->grade == maxGrade) {
			outFile << curr->number << " " << curr->name << " " << curr->age << " " 
			<< curr->gender << " " << curr->language << " " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有成绩最低的志愿者（数据写入文件，中文提示输出到控制台）
void findMinGradeVolunteers(volunteer* head, ofstream& outFile) {
	if (head == NULL) return;
	int minGrade = head->grade;
	volunteer* curr = head;
	// 查找最低成绩
	while (curr != NULL) {
		if (curr->grade < minGrade) {
			minGrade = curr->grade;
		}
		curr = curr->next;
	}
	// 控制台输出中文提示
	cout << "成绩最低的志愿者成绩为：" << minGrade << endl;
	// out.txt仅写入数据，无汉字
	curr = head;
	while (curr != NULL) {
		if (curr->grade == minGrade) {
			outFile << curr->number << " " << curr->name << " " << curr->age << " " 
			<< curr->gender << " " << curr->language << " " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//当前列表中志愿者总数
int countVolunteers(volunteer* head) {
	int count = 0;
	volunteer* curr = head;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

//读取input文件并创建链表
volunteer* input(const char* fileName) {
	ifstream file(fileName);
	if (!file) {
		cerr << "无法打开文件" << fileName << endl;
		return NULL;
	}
	
	volunteer* head = NULL;
	volunteer* tail = NULL;
	
	volunteer* q = new volunteer;
	while (file >> q->number >> q->name >> q->age >> q->gender >> q->language >> q->grade) {
		q->next = NULL;
		if (head == NULL) {
			head = q;
			tail = q;
		} else {
			tail->next = q;
			tail = q;
		}
		q = new volunteer;
	}
	delete q; // 释放最后一个未使用的节点
	file.close();
	return head;
}

//查找number为no的人员，并返回该结点前一结点便于删除函数调用
volunteer* find(volunteer* head, int no) {
	volunteer* prev = NULL;
	volunteer* curr = head;
	while (curr != NULL && curr->number != no) {
		prev = curr;
		curr = curr->next;
	}
	return prev;
}

//从链表中删除number为no的人员，返回链首
volunteer* del(volunteer* head, int no) {
	volunteer* prev = find(head, no);
	if (prev == NULL) {
		if (head != NULL && head->number == no) {
			volunteer* temp = head;
			head = head->next;
			delete temp;
		}
	} else {
		if (prev->next != NULL) {
			volunteer* temp = prev->next;
			prev->next = prev->next->next;
			delete temp;
		}
	}
	return head;
}

//插入一名人员至链尾，返回链首
volunteer* append(volunteer* head, volunteer* s) {
	if (head == NULL) {
		return s;
	}
	volunteer* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = s;
	return head;
}

// ---------------------- 辅助函数（无汉字输出，仅数据）----------------------
// 将单个志愿者信息写入文件（仅数据，无汉字）
void writeVolunteerToFile(volunteer* vol, ofstream& outFile) {
	if (vol != NULL) {
		outFile << vol->number << " " << vol->name << " " << vol->age << " "
		<< vol->gender << " " << vol->language << " " << vol->grade << endl;
	}
}

// 将所有志愿者信息写入文件（仅数据，无汉字）
void writeAllToFile(volunteer* head, const char* fileName) {
	ofstream outFile(fileName);
	if (!outFile) {
		cerr << "无法打开文件" << fileName << endl;
		return;
	}
	volunteer* curr = head;
	while (curr != NULL) {
		writeVolunteerToFile(curr, outFile);
		curr = curr->next;
	}
	outFile.close();
}

// 模糊查询结果写入文件（仅数据，无汉字；中文提示输出到控制台）
void fuzzyQueryToFile(volunteer* head, const char* namePart, const char* fileName) {
	ofstream outFile(fileName);
	if (!outFile) {
		cerr << "无法打开文件" << fileName << endl;
		return;
	}
	// 控制台输出中文提示
	cout << "模糊查询包含关键词\"" << namePart << "\"的结果如下" << endl;
	// out.txt仅写入匹配的数据
	volunteer* curr = head;
	while (curr != NULL) {
		if (strstr(curr->name, namePart) != NULL) {
			writeVolunteerToFile(curr, outFile);
		}
		curr = curr->next;
	}
	outFile.close();
}

// ---------------------- 主函数（按要求修改）----------------------
int main() {
	//从input.txt文件读取志愿者信息并创建链表
	volunteer* head = input("input.txt");
	if (head == NULL) {
		cerr << "初始化链表失败" << endl;
		return 1;
	}
	
	int choice;
	ifstream menuFile("menu.txt");
	if (!menuFile) {
		cerr << "无法打开menu.txt文件" << endl;
		// 释放链表内存
		while (head != NULL) {
			volunteer* temp = head;
			head = head->next;
			delete temp;
		}
		return 1;
	}
	
	if (menuFile >> choice) {
		switch (choice) {
			// 功能1：按编号查询单个志愿者
			case 1: {
			int no;
			ifstream findFile("find.txt");
			ofstream outFile("out.txt");
			if (!findFile) {
				cerr << "无法打开find.txt文件" << endl;
				outFile.close();
				break;
			}
			if (!outFile) {
				cerr << "无法打开out.txt文件" << endl;
				findFile.close();
				break;
			}
			if (findFile >> no) {
				volunteer* prev = find(head, no);
				bool found = false;
				// 控制台输出中文提示
				if (prev != NULL || (head != NULL && head->number == no)) {
					cout << "按编号查询功能完成，查询编号为" << no << "的志愿者" << endl;
					found = true;
					if (prev != NULL) {
						writeVolunteerToFile(prev->next, outFile);
					} else {
						writeVolunteerToFile(head, outFile);
					}
				} else {
					cout << "未找到指定志愿者，按编号查询功能完成" << endl;
					found = false;
				}
				// out.txt仅写入数据，无汉字（未找到则无内容，或仅写入编号）
			} else {
				cerr << "find.txt文件格式错误" << endl;
			}
			findFile.close();
			outFile.close();
			break;
		}
			
			// 功能2：插入志愿者
			case 2: {
				volunteer* s = new volunteer;
				ifstream insertFile("insert.txt");
				if (!insertFile) {
					cerr << "无法打开insert.txt文件" << endl;
					delete s;
					break;
				}
				if (insertFile >> s->number >> s->name >> s->age >> s->gender >> s->language >> s->grade) {
					s->next = NULL;
					head = append(head, s);
					// 写入插入后的所有志愿者数据（无汉字）到out.txt
					writeAllToFile(head, "out.txt");
					cout << "志愿者插入功能完成" << endl;
				} else {
					cerr << "insert.txt文件格式错误" << endl;
					delete s; // 释放未使用的节点
				}
				insertFile.close();
				break;
			}
			
			// 功能3：按编号删除志愿者
			case 3: {
				int no;
				ifstream findFile("find.txt");
				if (!findFile) {
					cerr << "无法打开find.txt文件" << endl;
					break;
				}
				if (findFile >> no) {
					head = del(head, no);
					// 写入删除后的所有志愿者数据（无汉字）到out.txt
					writeAllToFile(head, "out.txt");
					cout << "按编号删除功能完成" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
				}
				findFile.close();
				break;
			}
			
			// 功能4：显示所有志愿者信息
			case 4: {
				writeAllToFile(head, "out.txt");
				cout << "显示所有志愿者功能完成" << endl;
				break;
			}
			
			/*
			// 功能5：修改志愿者信息（从modify.txt读取参数,只输出被修改的那条信息）
			case 5: {
			int oldNo;
			char newName[20];
			int newAge;
			char newGender;
			char newLanguage[10];
			int newGrade;
			// modify.txt格式：原编号 新姓名 新年龄 新性别 新语言 新成绩
			ifstream modifyFile("modify.txt");
			ofstream outFile("out.txt");
			if (!modifyFile) {
			cerr << "无法打开modify.txt文件" << endl;
			outFile.close();
			break;
			}
			if (!outFile) {
			cerr << "无法打开out.txt文件" << endl;
			modifyFile.close();
			break;
			}
			if (modifyFile >> oldNo >> newName >> newAge >> newGender >> newLanguage >> newGrade) {
			// 先查询原志愿者信息
			volunteer* curr = head;
			while (curr != NULL && curr->number != oldNo) {
			curr = curr->next;
			}
			if (curr == NULL) {
			cout << "未找到编号为" << oldNo << "的志愿者，修改失败" << endl;
			} else {
			// 执行修改
			modifyVolunteer(head, oldNo, newName, newAge, newGender, newLanguage, newGrade);
			cout << "修改成功" << endl;
			writeVolunteerToFile(curr, outFile);
			}
			cout << "修改志愿者功能完成" << endl;
			} else {
			cerr << "modify.txt文件格式错误" << endl;
			cout << "修改失败：文件格式错误" << endl;
			}
			modifyFile.close();
			outFile.close();
			break;
			}
			
			*/
			
			
			// 功能5：修改志愿者信息（修改后输出所有志愿者信息，out.txt无汉字）
			case 5: {
				int oldNo;
				char newName[20];
				int newAge;
				char newGender;
				char newLanguage[10];
				int newGrade;
				// modify.txt格式：原编号 新姓名 新年龄 新性别 新语言 新成绩
				ifstream modifyFile("modify.txt");
				if (!modifyFile) {
					cerr << "无法打开modify.txt文件" << endl;
					break;
				}
				if (modifyFile >> oldNo >> newName >> newAge >> newGender >> newLanguage >> newGrade) {
					// 先查询原志愿者信息
					volunteer* curr = head;
					bool found = false;
					while (curr != NULL && curr->number != oldNo) {
						curr = curr->next;
					}
					if (curr == NULL) {
						// 控制台输出中文提示，out.txt写入所有原有志愿者数据
						cout << "未找到编号为" << oldNo << "的志愿者，修改失败，修改功能完成" << endl;
					} else {
						// 执行修改
						modifyVolunteer(head, oldNo, newName, newAge, newGender, newLanguage, newGrade);
						cout << "志愿者信息修改成功，修改功能完成" << endl;
					}
					// 关键修改：修改后输出所有志愿者信息到out.txt（仅数据，无汉字）
					writeAllToFile(head, "out.txt");
				} else {
					cerr << "modify.txt文件格式错误" << endl;
				}
				modifyFile.close();
				break;
			}
			
			// 功能6：模糊查询志愿者姓名
			case 6: {
				char namePart[20];
				ifstream queryFile("find.txt");
				if (!queryFile) {
					cerr << "无法打开query_name.txt文件" << endl;
					break;
				}
				if (queryFile >> namePart) {
					fuzzyQueryToFile(head, namePart, "out.txt");
					cout << "模糊查询姓名功能完成" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
					// out.txt无汉字，若错误则留空或不写入
					ofstream outFile("out.txt");
					outFile.close();
				}
				queryFile.close();
				break;
			}
			
			// 功能7：按姓名删除志愿者
			case 7: {
				char delName[20];
				ifstream delFile("find.txt");
				if (!delFile) {
					cerr << "无法打开find.txt文件" << endl;
					break;
				}
				if (delFile >> delName) {
					head = deleteVolunteerByName(head, delName);
					// 写入删除后的所有志愿者数据（无汉字）到out.txt
					writeAllToFile(head, "out.txt");
					cout << "按姓名删除功能完成" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
					ofstream outFile("out.txt");
					outFile.close();
				}
				delFile.close();
				break;
			}
			
			// 功能8：按成绩删除志愿者
			case 8: {
				int delGrade;
				ifstream delFile("find.txt");
				if (!delFile) {
					cerr << "无法打开find.txt文件" << endl;
					break;
				}
				if (delFile >> delGrade) {
					head = deleteVolunteerByGrade(head, delGrade);
					// 写入删除后的所有志愿者数据（无汉字）到out.txt
					writeAllToFile(head, "out.txt");
					cout << "按成绩删除功能完成" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
					ofstream outFile("out.txt");
					outFile.close();
				}
				delFile.close();
				break;
			}
			
			// 功能9：按位置删除志愿者
			case 9: {
				int delPos;
				ifstream delFile("find.txt");
				if (!delFile) {
					cerr << "无法打开find.txt文件" << endl;
					break;
				}
				if (delFile >> delPos) {
					head = deleteVolunteerByPosition(head, delPos);
					// 写入删除后的所有志愿者数据（无汉字）到out.txt
					writeAllToFile(head, "out.txt");
					cout << "按位置删除功能完成" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
					ofstream outFile("out.txt");
					outFile.close();
				}
				delFile.close();
				break;
			}
			
			// 功能10：批量按编号查询
			case 10: {
				int arr[MAX];
				int m = 0;
				ifstream fileFind("find.txt", ios_base::in);
				ofstream outFile("out.txt");
				if (!fileFind) {
					cerr << "无法打开find.txt文件" << endl;
					outFile.close();
					break;
				}
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					fileFind.close();
					break;
				}
				// 控制台输出中文提示
				cout << "批量查询功能执行中，结果如下" << endl;
				// out.txt仅写入查询到的数据，无汉字
				while (fileFind >> arr[m] && m < MAX) {
					int num = arr[m];
					volunteer* curr = head;
					while (curr != NULL) {
						if (curr->number == num) {
							writeVolunteerToFile(curr, outFile);
							break;
						}
						curr = curr->next;
					}
					m++;
				}
				cout << "批量查询功能完成" << endl;
				outFile.close();
				fileFind.close();
				break;
			}
			
			// 功能11：计算平均年龄
			case 11: {
				double avg = averageAge(head);
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				// 控制台输出中文提示
				cout << "计算平均年龄功能完成" << endl;
				// out.txt仅写入数值，无汉字
				outFile << avg << endl;
				outFile.close();
				break;
			}
			
			// 功能12：计算平均成绩
			case 12: {
				double avg = averageGrade(head);
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				// 控制台输出中文提示
				cout << "计算平均成绩功能完成" << endl;
				// out.txt仅写入数值，无汉字
				outFile << avg << endl;
				outFile.close();
				break;
			}
			
			// 功能13：按年龄排序（从小到大）
			case 13: {
				head = sortByAge(head);
				writeAllToFile(head, "out.txt");
				cout << "按年龄排序功能完成" << endl;
				break;
			}
			
			// 功能14：按成绩排序（从低到高）
			case 14: {
				head = sortByGrade(head);
				writeAllToFile(head, "out.txt");
				cout << "按成绩排序功能完成" << endl;
				break;
			}
			
			// 功能15：查询所有年龄最大的志愿者
			case 15: {
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				findMaxAgeVolunteers(head, outFile);
				cout << "查询年龄最大志愿者功能完成" << endl;
				outFile.close();
				break;
			}
			
			// 功能16：查询所有年龄最小的志愿者
			case 16: {
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				findMinAgeVolunteers(head, outFile);
				cout << "查询年龄最小志愿者功能完成" << endl;
				outFile.close();
				break;
			}
			
			// 功能17：查询所有成绩最高的志愿者
			case 17: {
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				findMaxGradeVolunteers(head, outFile);
				cout << "查询成绩最高志愿者功能完成" << endl;
				outFile.close();
				break;
			}
			
			// 功能18：查询所有成绩最低的志愿者
			case 18: {
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				findMinGradeVolunteers(head, outFile);
				cout << "查询成绩最低志愿者功能完成" << endl;
				outFile.close();
				break;
			}
			
			// 功能19：查询志愿者总数
			case 19: {
				int total = countVolunteers(head);
				ofstream outFile("out.txt");
				if (!outFile) {
					cerr << "无法打开out.txt文件" << endl;
					break;
				}
				// 控制台输出中文提示
				cout << "查询志愿者总数功能完成" << endl;
				// out.txt仅写入数值，无汉字
				outFile << total << endl;
				outFile.close();
				break;
			}
			
			// 无效功能编号
			default: {
				// 控制台输出中文错误提示
				cerr << "无效的菜单选项：" << choice << endl;
				// out.txt无汉字，留空
				ofstream outFile("out.txt");
				outFile.close();
			}
		}
	} else {
		// 控制台输出中文错误提示
		cerr << "menu.txt文件格式错误" << endl;
		// out.txt无汉字，留空
		ofstream outFile("out.txt");
		outFile.close();
	}
	
	menuFile.close();
	
	//释放链表内存
	while (head != NULL) {
		volunteer* temp = head;
		head = head->next;
		delete temp;
	}
	
	return 0;
}
