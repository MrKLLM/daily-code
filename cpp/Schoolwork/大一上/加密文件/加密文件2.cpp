#include<bits/stdc++.h>
using namespace std;


int main() {
	string key;
	cin >> key;
	// 2. 加密步骤：1.txt → 2.txt
	ifstream inputfile("1.txt", ios::binary);
	ofstream outputfile("2.txt", ios::binary);
	
	// 检查文件打开状态
	if (!inputfile.is_open()) {
		cerr << "无法打开输入文件 1.txt" << endl;
		return 1;
	}
	if (!outputfile) {
		cerr << "无法创建输出文件 2.txt" << endl;
		inputfile.close();
		return 1;
	}
	
	// 密钥为空：直接复制（不加密）
	if (key.empty()) {
		outputfile << inputfile.rdbuf();
	}
	// 密钥非空：逐字符异或加密
	else {
		char ch;
		size_t keyIndex = 0;
		while (inputfile.get(ch)) {
			char encryptedChar = ch ^ key[keyIndex];
			outputfile.put(encryptedChar);
			keyIndex = (keyIndex + 1) % key.length(); // 循环使用密钥
		}
	}
	
	// 关闭加密相关文件流（必须先关闭，才能进行后续拷贝操作）
	inputfile.close();
	outputfile.close();
	
//	// 3. 拷贝步骤：将2.txt的内容覆盖回1.txt
//	ifstream src_file("2.txt", ios::binary); // 源文件：2.txt（密文）
//	ofstream dest_file("1.txt", ios::binary | ios::trunc); // 目标文件：1.txt（覆盖原有内容）
//	
//	/*
//	不加trunc:
//	不会清空 1.txt 原有内容
//	新写入的数据会覆盖文件开头的部分内容，未被覆盖的原有内容会保留
//	*/
//	
//	// 检查拷贝用文件流
//	if (!src_file.is_open()) {
//		cerr << "无法打开源文件 2.txt 进行拷贝" << endl;
//		return 1;
//	}
//	if (!dest_file) {
//		cerr << "无法打开目标文件 1.txt 进行覆盖" << endl;
//		src_file.close();
//		return 1;
//	}
//	
//	// 一次性拷贝全部内容
//	dest_file << src_file.rdbuf();
//	
//	// 关闭拷贝相关文件流
//	src_file.close();
//	dest_file.close();
//	
	return 0;
}
