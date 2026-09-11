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

//显示所有志愿者信息
void displayAllVolunteers(volunteer* head) {
	volunteer* curr = head;
	while (curr != NULL) {
		cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		curr = curr->next;
	}
}

//修改志愿者信息
void modifyVolunteer(volunteer* head, int number, const char* newName, int newAge, char newGender, const char* newLanguage, double newGrade) {
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
volunteer* deleteVolunteerByGrade(volunteer* head, double grade) {
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
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	return head;
}

//按位置删除志愿者信息
volunteer* deleteVolunteerByPosition(volunteer* head, int position) {
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
	return (double)sum / count;
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
	return sum / count;
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
				int tempNumber = ptr1->number;
				char tempName[20];
				strcpy(tempName, ptr1->name);
				int tempAge = ptr1->age;
				char tempGender = ptr1->gender;
				char tempLanguage[10];
				strcpy(tempLanguage, ptr1->language);
				double tempGrade = ptr1->grade;

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
				int tempNumber = ptr1->number;
				char tempName[20];
				strcpy(tempName, ptr1->name);
				int tempAge = ptr1->age;
				char tempGender = ptr1->gender;
				char tempLanguage[10];
				strcpy(tempLanguage, ptr1->language);
				double tempGrade = ptr1->grade;

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

//所有年龄最大的志愿者
void findMaxAgeVolunteers(volunteer* head) {
	if (head == NULL) return;
	int maxAge = head->age;
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->age > maxAge) {
			maxAge = curr->age;
		}
		curr = curr->next;
	}
	curr = head;
	while (curr != NULL) {
		if (curr->age == maxAge) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有年龄最小的志愿者
void findMinAgeVolunteers(volunteer* head) {
	if (head == NULL) return;
	int minAge = head->age;
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->age < minAge) {
			minAge = curr->age;
		}
		curr = curr->next;
	}
	curr = head;
	while (curr != NULL) {
		if (curr->age == minAge) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有成绩最高的志愿者
void findMaxGradeVolunteers(volunteer* head) {
	if (head == NULL) return;
	double maxGrade = head->grade;
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->grade > maxGrade) {
			maxGrade = curr->grade;
		}
		curr = curr->next;
	}
	curr = head;
	while (curr != NULL) {
		if (curr->grade == maxGrade) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
		}
		curr = curr->next;
	}
}

//所有成绩最低的志愿者
void findMinGradeVolunteers(volunteer* head) {
	if (head == NULL) return;
	double minGrade = head->grade;
	volunteer* curr = head;
	while (curr != NULL) {
		if (curr->grade < minGrade) {
			minGrade = curr->grade;
		}
		curr = curr->next;
	}
	curr = head;
	while (curr != NULL) {
		if (curr->grade == minGrade) {
			cout << "编号: " << curr->number << ", 姓名: " << curr->name << ", 年龄: " << curr->age << ", 性别: " << curr->gender << ", 语言: " << curr->language << ", 成绩: " << curr->grade << endl;
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
	delete q;
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

//将链表内容写入文件
void output(volunteer* head, const char* fileName) {
	ofstream file1(fileName);
	if (!file1) {
		cerr << "无法打开文件" << fileName << endl;
		return;
	}
	volunteer* curr = head;
	while (curr != NULL) {
		file1 << curr->number << " ";
		file1 << curr->name << " ";
		file1 << curr->age << " ";
		file1 << curr->gender << " ";
		file1 << curr->language << " ";
		file1 << curr->grade << endl;
		curr = curr->next;
	}
	file1.close();
}

int main() {
	//从input.txt文件读取志愿者信息并创建链表
	volunteer* head = input("input.txt");

	int choice;
	ifstream menuFile("menu.txt");
	if (menuFile >> choice) {
		switch (choice) {
			case 1: {
				int no;
				ifstream findFile("find.txt");
				if (findFile >> no) {
					volunteer* prev = find(head, no);
					if (prev != NULL || (head != NULL && head->number == no)) {
						cout << "找到志愿者信息" << endl;
						if (prev != NULL) {
							ofstream file("out.txt");
							file << prev->next->number << " ";
							file << prev->next->name << " ";
							file << prev->next->age << " ";
							file << prev->next->gender << " ";
							file << prev->next->language << " ";
							file << prev->next->grade;
							file.close();
							return 0;
						} else {
							ofstream file("out.txt");
							file << head->number << " ";
							file << head->name << " ";
							file << head->age << " ";
							file << head->gender << " ";
							file << head->language << " ";
							file << head->grade;
							file.close();
							return 0;
						}
					} else {
						cout << "未找到指定志愿者信息" << endl;
					}
				} else {
					cerr << "find.txt文件格式错误" << endl;
				}
				findFile.close();
				break;
			}
			case 2: {
				volunteer* s = new volunteer;
				ifstream insertFile("insert.txt");
				if (insertFile >> s->number >> s->name >> s->age >> s->gender >> s->language >> s->grade) {
					head = append(head, s);
					cout << "志愿者信息插入成功" << endl;
				} else {
					cerr << "insert.txt文件格式错误" << endl;
				}
				insertFile.close();
				break;
			}
			case 3: {
				int no;
				ifstream findFile("find.txt");
				if (findFile >> no) {
					head = del(head, no);
					cout << "志愿者信息删除成功" << endl;
				} else {
					cerr << "find.txt文件格式错误" << endl;
				}
				findFile.close();
				break;
			}
			case 10: {
				int arr[MAX];
				int m = 0;
				ifstream fileFind("find.txt", ios_base::in);
				while (fileFind >> arr[m]) {
					int num = arr[m];
					queryVolunteerByNumber(head, num);
					m++;
				}
			}

			default: {
				cerr << "无效的菜单选项" << endl;
			}
		}
	} else {
		cerr << "menu.txt文件格式错误" << endl;
	}
	menuFile.close();

	//将处理后的链表信息写入out.txt文件
	output(head, "out.txt");

	//释放链表内存
	while (head != NULL) {
		volunteer* temp = head;
		head = head->next;
		delete temp;
	}

	return 0;
}

