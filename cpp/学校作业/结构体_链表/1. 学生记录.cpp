#include<bits/stdc++.h>
using namespace std;
#ifndef MAX
	#define MAX (50)
#endif

struct student {
	int id;
	string name;
	int age;
};

bool cmpByName(const student& a, const student& b) {
	return a.name < b.name;
}

bool cmpByAge(const student& a, const student& b) {
	if (a.age != b.age) {
		return a.age < b.age;// 年龄小的在前
	} else {
		return a.name < b.name;// 年龄相同则姓名小的在前
	}
}

int main() {
	
	int n = 0;
	cin >> n;

	student students[MAX];
	for (int i = 0; i < n; i++) {
		cin >> students[i].id >> students[i].name >> students[i].age;
	}

	//创建用于排序的副本
	student tmp[MAX];
	for (int i = 0; i < n; i++) {
		tmp[i] = students[i];
	}
	//按名字排
	sort(tmp, tmp + n, cmpByName);
	//学号占3位，姓名（英文）占6位，年龄占3位，均为右对齐
	for (int i = 0; i < n; i++) {
		printf("%3d%6s%3d\n", tmp[i].id, tmp[i].name.c_str(), tmp[i].age);//记得检查多余的空格
	}

	cout << endl;

	//按年龄排
	sort(tmp, tmp + n, cmpByAge);
	//C风格格式化输出
	//学号占3位，姓名（英文）占6位，年龄占3位，均为右对齐
	for (int i = 0; i < n; i++) {
		printf("%3d%6s%3d\n", tmp[i].id, tmp[i].name.c_str(), tmp[i].age);//记得检查多余的空格
	}
//// 用 cout 实现和 printf 完全相同的效果
//	cout << right  // 右对齐（默认，可省略）
//	<< setw(3) << temp[0].id    // 对应 %3d
//	<< setw(6) << temp[0].name  // 对应 %6s（cout 直接支持 string，无需 .c_str()）
//	<< setw(3) << temp[0].age   // 对应 %3d
//	<< "\n";                    // 换行（或用 endl，效果一致）
//	
	return 0;
}
