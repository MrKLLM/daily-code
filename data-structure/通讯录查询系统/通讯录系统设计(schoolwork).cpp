#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// 联系人结构
struct Contact {
	string name;       // 姓名 
	string phone;      // 电话号码
	string address;    // 地址
	bool isEmpty;      // 是否为空位置
	bool isDeleted;    // 是否为删除位置
	
	Contact() : isEmpty(true), isDeleted(false) {}
};

// 全局变量
const int HASH_SIZE = 100;
const int PRIME = 97;   // 不超过 100 的最大质数
Contact hashTable[HASH_SIZE];
int cnt = 0;  // 实际元素个数

// 哈希函数：除留余数法
int hashFunction(const string& phone) {
	long long sum = 0;
	for (size_t i = 0; i < phone.length(); i++) {
		sum = sum * 10 + (phone[i] - '0');
	}
	return sum % PRIME;
}

// 二次探测再散列法
int probe(const string& phone, int i) {
	int base = hashFunction(phone);
	return (base + i * i) % HASH_SIZE;
}

// 插入联系人
bool insert(const Contact& contact) {
	if (cnt >= HASH_SIZE / 2) {
//		cout << "哈希表已满！" << endl;
		return false;
	}
	
	int i = 0;
	int pos;
	do {
		pos = probe(contact.phone, i);
		if (hashTable[pos].isEmpty || hashTable[pos].isDeleted) {
			hashTable[pos] = contact;
			hashTable[pos].isEmpty = false;
			hashTable[pos].isDeleted = false;
			cnt++;
			return true;
		}
//		if (hashTable[pos].phone == contact.phone) {
//			cout << "该电话号码已存在！" << endl;
//			return false;
//		}
		i++;
	} while (i < HASH_SIZE);
	
	return false;
}

// 查找联系人
int find(const string& phone) {
	int i = 0;
	int pos;
	do {
		pos = probe(phone, i);
		if (hashTable[pos].isEmpty) {
			return -1;
		}
		if (!hashTable[pos].isDeleted && hashTable[pos].phone == phone) {
			return pos;
		}
		i++;
	} while (i < HASH_SIZE);
	
	return -1;
}

// 显示菜单
void menu() {
	cout << "\n========== 通讯录查询系统 ==========" << endl;
	cout << "1. 创建新通讯录" << endl;
	cout << "2. 添加新记录" << endl;
	cout << "3. 查询记录" << endl;
	cout << "4. 修改记录" << endl;
	cout << "5. 删除记录" << endl;
	cout << "6. 显示所有记录" << endl;
	cout << "7. 保存通讯录" << endl;
	cout << "0. 退出系统" << endl;
	cout << "====================================" << endl;
	cout << "请选择操作 (0-7): ";
}

// 创建新通讯录
void create() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		Contact contact;
//		cout << "\n请输入第 " << i + 1 << " 条记录：" << endl;
		cin >> contact.name >> contact.phone >> contact.address;
		insert(contact);
	}
	
//	cout << "创建完成！共添加 " << n << " 条记录。" << endl;
}

// 添加新记录
void append() {
	Contact contact;
//	cout << "\n请输入新记录：" << endl;
	cin >> contact.name >> contact.phone >> contact.address;
	cin >> contact.address;
	
	if (insert(contact)) {
//		cout << "添加成功！" << endl;
	}
}

// 查询记录
void findContact() {
	string phone;
//	cout << "\n请输入要查询的电话号码：";
	cin >> phone;
	
	int pos = find(phone);
	if (pos != -1) {
//		cout << "\n找到记录：" << endl;
//		cout << hashTable[pos].phone << endl;
		cout << hashTable[pos].name << endl;
//		cout << hashTable[pos].address << endl;
	} else {
		cout << "No Person" << endl;
	}
}

// 修改记录
void alter() {
	string phone, newName, newAddress;
//	cout << "\n请输入要修改的电话号码：";
	cin >> phone;
	
	int pos = find(phone);
	if (pos == -1) {
		cout << "Fail" << endl;
		return;
	}
	
//	cout << "请输入新的姓名：";
	cin >> newName;
//	cout << "请输入新的地址：";
	cin >> newAddress;
	
	hashTable[pos].name = newName;
	hashTable[pos].address = newAddress;
	cout << "Success" << endl;
}

// 删除记录
void remove() {
	string phone;
//	cout << "\n请输入要删除的电话号码：";
	cin >> phone;
	
	int pos = find(phone);
	if (pos == -1) {
		cout << "No Person" << endl;
		return;
	}
	
	hashTable[pos].isDeleted = true;
	cnt--;
//	cout << "删除成功！" << endl;
}

// 显示所有记录
void list() {
	bool hasRecords = false;
	cout << "\n========== 通讯录列表 ==========" << endl;
	cout << "电话号码\t姓名\t地址" << endl;
	cout << "--------------------------------" << endl;
	
	for (int i = 0; i < HASH_SIZE; i++) {
		if (!hashTable[i].isEmpty && !hashTable[i].isDeleted) {
			cout << hashTable[i].phone << "\t" 
			<< hashTable[i].name << "\t" 
			<< hashTable[i].address << endl;
			hasRecords = true;
		}
	}
	
	if (!hasRecords) {
		cout << "通讯录为空！" << endl;
	} else {
		cout << "--------------------------------" << endl;
		cout << "共 " << cnt << " 条记录" << endl;
	}
}

// 保存通讯录
void save() {
	string filename;
	cout << "\n请输入要保存的文件名：";
	cin >> filename;
	
	ofstream outFile(filename.c_str());
	if (!outFile.is_open()) {
		cout << "无法打开文件：" << filename << endl;
		return;
	}
	
	for (int i = 0; i < HASH_SIZE; i++) {
		if (!hashTable[i].isEmpty && !hashTable[i].isDeleted) {
			outFile << hashTable[i].phone << " " 
			<< hashTable[i].name << " " 
			<< hashTable[i].address << endl;
		}
	}
	
	outFile.close();
//	cout << "通讯录已保存到文件：" << filename << endl;
}

// 从文件加载
void load() {
	ifstream inFile("contacts.txt");
	if (!inFile.is_open()) {
		return;
	}
	
	string phone, name, address;
	while (inFile >> phone >> name >> address) {
		Contact contact;
		contact.phone = phone;
		contact.name = name;
		contact.address = address;
		insert(contact);
	}
	
	inFile.close();
//	cout << "已加载通讯录文件。" << endl;
}

int main() {
	
//	int choice = -1;
	
//	cout << "欢迎使用通讯录查询系统！" << endl;
//	load();
	
	create();
	int oporation_cnt = 0;
	cin >> oporation_cnt;
	
	while(oporation_cnt > 0){
		string choice;
		cin >> choice;
		//转换成数字选择
		int choice_num = 0;
		if(choice == "search"){
			choice_num = 1;
		}else if(choice == "del"){
			choice_num = 2;
		}else if(choice == "altermessage"){
			choice_num = 3;
		}
		
		switch (choice_num) {
		case 1:
			findContact();
			break;
		case 2:
			remove();
			break;
		case 3:
			alter();
			break;
		}
		
		oporation_cnt--;
	}
//	while (choice != 0) {
//		menu();
//		cin >> choice;
//		
//		
//		switch (choice) {
//			case 1: create(); break;
//			case 2: append(); break;
//			case 3: findContact(); break;
//			case 4: alter(); break;
//			case 5: remove(); break;
//			case 6: list(); break;
//			case 7: save(); break;
//			case 0: 
//			cout << "感谢使用，再见！" << endl; 
//			break;
//		default:
//			cout << "无效的选择，请重新输入！" << endl;
//		}
//	}
	
	return 0;
}
