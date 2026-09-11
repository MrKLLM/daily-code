#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUG
	#define DEBUG (1)
#endif

//文件是数据的来源/目的地，流是数据的传输通道，程序只和流交互，不直接接触文件。
int main() {
//	cout << "输入密钥为：" << endl;
	string key;
	getline(cin, key);
//	cin.ignore();//清楚缓冲区换行符
//	cout << endl << "1.txt文件内容为" << endl;
//	string content;
//	getline(cin,content);
//	ofstream write_in_1("1.txt",ios::binary);
//	if (!write_in_1) {
//		cerr << "无法打开输入文件 1.txt" << endl;
//		return 1;
//	}
//	int cntnt_index = 0;
//	while(content[cntnt_index] != '\0'){
//		char ch = content[cntnt_index];
//		write_in_1.put(ch);
//		cntnt_index++;
//	}
//	write_in_1.close();
	
	//密钥为空，不用加密
	if (key.empty()) { //空则返回true，非空返回false
		ifstream inputfile("1.txt", ios::binary);
		/*
		创建流对象：ifstream inputFile; 相当于造了一根 “只读水管”（ifstream是输入流，只能从文件往程序传数据）；
		关联并打开文件：括号中的"1.txt"是文件路径，ios::binary是打开模式
		*/
		/*
		第一个参数"1.txt"：要打开的文件路径
		（这里是当前程序所在目录，若文件不在此目录，需写绝对路径，比如"C:/test/1.txt"）。
		第二个参数ios::binary：以 “二进制模式” 打开文件。
		*/
		ofstream outputfile("2.txt", ios::binary);
		//若文件不存在则自动创建，若已存在则覆盖原有内容

		/*
		inputfile是文件流对象，
		当文件不存在、权限不足等原因导致打开失败时，
		inputfile会被视为 “假值”，!inputfile就会为true。
		*/
		if (!inputfile.is_open()) {
			cerr << "无法打开输入文件 1.txt" << endl;
			/*
			cerr：标准错误输出流，专门用于打印错误信息，
			和cout的区别是：cerr不缓冲，错误信息会立即显示，不会被延迟。
			*/
			return 1;//返回非 0 值告知操作系统 “程序运行失败”
		}
		if (!outputfile.is_open()) {
			cerr << "无法创建输出文件 2.txt" << endl;
			return 1;
		}
		outputfile << inputfile.rdbuf();
		/*.rdbuf()
		返回inputfile的文件缓冲区指针，相当于 “指向中转站的地址”，
		通过这个指针可以直接访问缓冲区里的所有文件数据。*/
		/*
		outputfile << 缓冲区指针 的作用：
		把inputfile缓冲区中的所有数据，一次性 “搬运” 到outputfile的缓冲区中，最终会写入2.txt。
		*/
		//清空各自的缓存区
		inputfile.close();
		outputfile.close();
		return 0;
	}

	//key不为空
	ifstream inputfile("1.txt", ios::binary);
	//检查，实际上没有会自己创建的
	if (!inputfile.is_open()) {
		cerr << "无法打开输入文件 1.txt" << endl;
		return 1;
	}
	ofstream outputfile("2.txt", ios::binary);
	//检查
	if (!outputfile) {
		cerr << "无法创建输出文件 2.txt" << endl;
		inputfile.close();//已经在inputfile的缓存区复制有数据了
		return 1;
	}
	
	//通过检查后,读取文件内容
	vector<char> duqu_content;
	char ch;
	//.get()返回值：读取成功则返回 “真值”，读取到文件末尾（EOF）或读取失败则返回 “假值”
	while (inputfile.get(ch)) {
		duqu_content.push_back(ch);
	}
	
	//异或加密
	size_t keyIndex = 0;//密钥下标
	for (size_t i = 0; i < duqu_content.size(); i++) {
		char encryptedChar = duqu_content[i] ^ key[keyIndex];
		outputfile.put(encryptedChar);
		keyIndex = (keyIndex + 1) % key.length();//不够长则循环用密钥
	}
	inputfile.close();
	outputfile.close();
	
//	//从2.txt中读取数据输出
//	cout << "2.txt文件内容为" << endl;
//	ifstream resultfile("2.txt");
//	if (!resultfile) {
//		cerr << "无法打开 2.txt 进行输出" << endl;
//		return 1;
//	}
//	string line;
//	while(getline(resultfile,line)){
//		cout << line << endl;
//	}
//	resultfile.close();
	return 0;
}
