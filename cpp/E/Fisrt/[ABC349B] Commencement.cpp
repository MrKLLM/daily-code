#include<bits/stdc++.h>
using namespace std;

int main(){
	char str[105];	//先存字母
	cin >> str ;
	
	//用ascll码差值标记字母索引，对着索引统计出现次数
	
	int char_count[26]={0};	//出现次数
	for(int i=0;str[i]!='\0';i++){
		
		char c = str[i];	//字符串第几个字符
		
		int id = c - 'a';	//用ascll码差值标记字母索引
		
		char_count [id]++;	//对着索引统计出现次数
	}
	
	//统计每种出现次数有几个字母
	
	int freq[105] = {0}; 	//几个字母
	for(int j=0;j<26;j++){
		
		int d = char_count[j];	//出现次数
		if(d>0){
			freq[d]++;	//统计每种出现次数有几个字母
		}
	}
	
	//判断每种出现次数的字母数是否为0 or 2
	
	bool isGood = true;
	int len = strlen(str);
	for(int i=1;i<=len;i++){
		if(freq[i]!=0 && freq[i]!=2){
			isGood = false;
		}
	}
	
	if(isGood==true){
		cout << "Yes";
	}else if(isGood==false){
		cout << "No";
	return 0;
	}
}
