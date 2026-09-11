#include<iostream>
#include<cstring>

using namespace std;

// 定义字符数组最大长度（避免输入溢出，可根据需求调整）
#define MAX_LEN 100

#ifndef DEBUG
	#define DEBUG (1)
#endif

// 字符数组转小写（直接修改原数组）
void toLower(char arr[]) {
	int len = strlen(arr); // 获取字符数组有效长度（到'\0'为止）
	for (int i = 0; i < len; i++) {
		if ('A' <= arr[i] && arr[i] <= 'Z') {
			arr[i] += ('a' - 'A'); // 大写转小写（ASCII差值固定）
		}
	}
}//cpp自带：#include <cctype> // 包含toupper/tolower

// 查找子串在主串中首次出现的索引（不存在返回-1）
int findTarget(const char* mainArr, const char* findArr) {
	int len1 = strlen(mainArr); // 主串长度
	int len2 = strlen(findArr); // 子串长度

	// 边界判断：子串为空 或 子串比主串长 → 不存在
	if (len2 == 0 || len2 > len1) {
		return -1;
	}

	// 遍历主串（剩余长度需≥子串长度）
	for (int i = 0; i <= len1 - len2; i++) {
		bool isMatch = true;
		// 逐字符匹配子串
		for (int j = 0; j < len2; j++) {
			if (mainArr[i + j] != findArr[j]) {
				isMatch = false;
				break;
			}
		}
		if (isMatch) {
			return i; // 匹配成功，返回起始索引
		}
	}
	return -1; // 无匹配
}

// 从原字符数组中删除所有指定子串（直接修改原数组）
void deleteTarget(char* orgStr, const char* subStr) {
	int subLen = strlen(subStr);
	if (subLen == 0) {
		return;
	}; // 子串为空，无需处理

	int index = findTarget(orgStr, subStr);
	while (index != -1) {

//法一
//		for (int i = 0; i <= len1 - len2; i++) {
//			orgStr[index + i] = orgStr[index + i + len2 + 1];
//		}

//法二
		// 核心：将子串后的数据整体前移，覆盖要删除的子串
		// strcpy会自动复制源字符串的'\0'，实现截断
		strcpy(orgStr + index, orgStr + index + subLen);
		// 重新查找剩余字符串中的子串（删除后可能仍有匹配）
		index = findTarget(orgStr, subStr);
	}
}

int main() {
	// 初始化字符数组（全部置0，避免乱码）
	char raw_words[MAX_LEN] = {0};
	char remembered[MAX_LEN] = {0};
	char words[MAX_LEN][MAX_LEN] = {0};// 二维数组存拆分后的单词
	char res[MAX_LEN] = {0};         // 最终结果
	int word_count = 0;              // 拆分出的单词数量

	cin >> raw_words >> remembered;
	// 统一转小写
	toLower(raw_words);
	toLower(remembered);

	int start = 0;//单词起始下标
	int len = strlen(raw_words);
	for (int i = 0; i <= len; i++) {//注意<就到不了\0了
//		截取单词
		if(raw_words[i] == ',' || raw_words[i] == '\0'){
			int word_len = i - start;
			if(word_len > 0){
				strncpy(words[word_count],raw_words + start,word_len);
				word_count++;//单词数+1
			}
		}
		start = i + 1;//更新下一个单词起始位置
	}
	
	int res_idx = 0;//结果数组的下标
	for(int i=0;i<word_count;i++){
		char tmp[MAX_LEN] = {0};
		strcpy(tmp ,words[i]);
		
		if(strcmp(tmp)){
			//TODO
		}
	}
	return 0;
}
