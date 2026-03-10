#include<iostream>
#include<cstring>

using namespace std;

#ifndef DEBUG
	#define DEBUG (1)
#endif

// 改写为处理string类型：直接修改原字符串（传引用）
// 字符数组：void toLower(char arr[], int len)
void toLower(string &str) { // 注意：string必须传引用，否则改不了原字符串
	int len = str.length();
	for (int i = 0; i < len; i++) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			str[i] += ('a' - 'A');
		}
	}
}//cpp自带：#include <cctype> // 包含toupper/tolower

//找目标字符串索引(单次)
int findTarget(const string mainArr, const string findArr) {
	int len1 = strlen(mainArr.c_str());
	int len2 = findArr.size();
	if (len2 == 0 || len2 > len1) {
		return -1;//不存在
	}
	for (int i = 0; i <= len1 - len2; i++) { //遍历mainArr的字符
		bool Match = true;
		for (int j = 0; j < len2; j++) { //遍历findArr里的字符
			if (mainArr[i + j] != findArr[j]) {
				Match = false;
				break;
			}//顺利比完则Match为true
		}
		if (Match) {

			return i;
		}
	}
	return -1;//不存在
}

/*注意点：
从哪里开始符合（提供索引值）、
符合的长度是多少（提供需删除的字符串的长度）、
要删干净（对原字符串查找多次，直到返回-1，即不存在目标字符串）
要删除的字符串有多个（这个归主函数管，本函数只作用于单目标）
*/
void deleteTarget(string &orgStr, const string subStr) {

	int len1 = orgStr.size();
	int len2 = subStr.size();
	int index = findTarget(orgStr, subStr);
	while (index != -1) {
		//法一
//		for (int i = 0; i <= len1 - len2; i++) {
//			orgStr[index + i] = orgStr[index + i + len2 + 1];
//		}
		
		//法二
		// 核心：将index+len2后的字符，整体前移len2位（覆盖要删除的部分）
		// 等价于：orgStr[index] = orgStr[index+len2], orgStr[index+1] = orgStr[index+len2+1]...
		strcpy(orgStr.data() + index, orgStr.data() + index + len2);
		
		// （可选）手动补终止符（strcpy会自动带，但保险起见）
		orgStr[len1 - len2] = '\0';
		len1 -= len2;
		index = findTarget(orgStr, subStr);
	};
}

int main() {
	string raw_words;
	string remembered;
	cin >> raw_words >> remembered;
	//转小写
	toLower(raw_words);
	toLower(remembered);
	deleteTarget(raw_words, remembered);
	cout << raw_words;
	return 0;
}
