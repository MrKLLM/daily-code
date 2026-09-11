#include<bits/stdc++.h>
using namespace std;

struct Node {
	string name;
	int age;
	Node* next;
};

bool cmpByAge(const Node& a, const Node& b) {
	return a.age < b.age;// 年龄小的在前
};

Node* creatNode(string name, int age) {
	Node* newNode = new Node();
	newNode->name = name;
	newNode->age = age;
	newNode->next = nullptr;
	return newNode;
}
int main() {
	int n = 0;
	cin >> n;

	Node* head = nullptr;
	Node* tail = nullptr;

	//构建循环链表
	for (int i = 0; i < n; i++) {
		string name;
		int age;
		cin >> name >> age;

		Node* newNode = creatNode(name, age);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		} else {
			tail->next = newNode;
			//节点的 next 指针：
			//每个 “人”（节点）手里拿的 “下一个人的地址”（比如 A 手里拿 B 的地址，B 手里拿 C 的地址)
			//—— 这是节点内部的成员，负责连接 “当前人” 和 “下一个人”，是链表的 “连接线”。
			tail = newNode;
			//尾指针（tail）：
			//用来记录 “当前队伍最后一个人” 的 “工具指针”
			//—— 它不是节点的成员，只是我们用来快速找到队尾、方便加新人的 “标记”，和节点内部的连接逻辑无关。
		}
	}

	tail->next = head;//连成环

	Node* minNode = head;//假设头节点为最小年龄节点（初始化）
	Node* current = head->next;//从第二个节点开始遍历

	//循环遍历所有节点找到最小年龄节点（因为是循环链表，用current != head判断结束）
	while (current != head) {
		if (current->age < minNode->age) {
			minNode = current;
		}

		current = current->next;//移动到下一节点
	}

	//从最小开始输出
	current = minNode;//起点
	for (int i = 0; i < n; i++) {
		cout << current->name << endl;
		current = (*current).next;//解引用先
	}
	
	//释放内存
	for(int i=0;i<n;i++){
		Node* tmp = current;
		delete tmp;
		current = current->next;
	}
	return 0;
}
