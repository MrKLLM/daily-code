#include<iostream>
#include<cstring>
#include<cctype>

using namespace std;

#ifndef MAX
	#define MAX (100)
#endif

#ifndef DEBUG
	#define DEBUG (1)
#endif

int main() {
	string wordsbook;
	string remembered;
	// 注意：输入是两行（生词本是第一行，记住的单词是第二行），所以要用getline读取！
	// （如果用cin >> 会被换行符截断，这里必须用getline）
	getline(cin, wordsbook);
	cin.ignore();
	getline(cin, remembered);
//	//转小写
//	for (size_t i = 0; i < remembered.size(); i++) {
//		remembered[i] = tolower(static_cast<unsigned char> (remembered[i]));
//	}
//	for (size_t i = 0; i < wordsbook.size(); i++) {
//		wordsbook[i] = tolower(static_cast<unsigned char> (wordsbook[i]));
//	}

	//存单词到字符串数组里
	string tmp = "";

	string wordsbook_2[MAX];
	int words_cnt1 = 0;//生词本中单词个数
	for (size_t i = 0; i < wordsbook.size(); i++) {
		char c = wordsbook[i];

		if (c != ',') {
			tmp += tolower(static_cast <unsigned char> (c));
		} else {
			wordsbook_2[words_cnt1++] = tmp;
			tmp.clear();
		}
	}
	if (!tmp.empty()) {
		wordsbook_2[words_cnt1++] = tmp;
		tmp.clear();
	}

	string remembered_2[MAX];
	int words_cnt2 = 0;
	for (size_t i = 0; i < remembered.size(); i++) {
		char c = remembered[i];

		if (c != ',') {
			tmp += tolower(static_cast <unsigned char> (c));
		} else {
			remembered_2[words_cnt2++] = tmp;
			tmp.clear();
		}
	}
	if (!tmp.empty()) {
		remembered_2[words_cnt2++] = tmp;
		tmp.clear();
	}
	// 与remembered_2比较单词本字符串数组（wordsbook_2）的每个元素（一个单词），有相同的就置空
	for (int i = 0; i < words_cnt2; i++) {

		for (int j = 0; j < words_cnt1; j++) {
			if (wordsbook_2[j] == remembered_2[i]) {
				wordsbook_2[j] = "";
			}
		}
	}

	for (int i = 0; i < words_cnt1; i++) {
		if (wordsbook_2[i] != "") {
			cout << wordsbook_2[i];
			if (i != words_cnt1 - 1) {
				cout << ',';
			}
		}
	}
	return 0;
}
