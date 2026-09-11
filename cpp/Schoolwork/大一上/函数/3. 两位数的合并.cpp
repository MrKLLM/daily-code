#include<iostream>
#include<cmath>
#include<sstream>
using namespace std;
#ifndef MAX
	#define MAX ()
#endif
//获取数字位数
int getDigitLength(int num) {
	if (num == 0) {
		return 1;
	} int len = 0;
	num = abs(num); // 处理负数
	while (num > 0) {
		num /= 10;
		len++;
	}
	return len;
}
//分离出数字每一位
int* spilitDigit(int a) {
	
	//法一：自定义函数
//	int n = getDigitLength(a);
	
	//法二：log10函数(记得加1)
//	int n = (a == 0)? 1 : ((int)log10(abs(a)) + 1);
	
	//法三：利用stringstream流和string函数
	stringstream ss;
	ss << a;// 把整数传入字符串流
	string num_str = ss.str();// 从字符串流中提取 string 类型
	int n = num_str.size();
	
	int* arr = new int[n];
	
	for (int i = n-1; i >= 0; i--) {
		arr[i] = a % 10;//例，[1]存个位,[0]存十位
		a /= 10;
	}

	return arr;//返回指针类型，即创建出的数组的地址
}
//合并两个两位数
int mergeTwoNum(int a, int b) {
	int* a_arr = spilitDigit(a);
	int* b_arr = spilitDigit(b);
	int  result = (a_arr[0] * 1e3) + (b_arr[0] * 1e2) + (b_arr[1] * 1e1) + (a_arr[1] * 1e0);
	delete[] a_arr;
	delete[] b_arr;
	return result;
}
int main() {
	int m, n;
	cin >> m >> n;
	cout << mergeTwoNum(m, n);

	return 0;
}
